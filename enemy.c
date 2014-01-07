#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>
#include "enemy.h"
#include "globals.h"
#include "item.h"
#include "magic.h"
#include "status.h"
#include "formula.h"

/** 
 *  Called when the enemy dies.
 * 
 * Runs whenever an enemy is killed; handles rewarding the player
 * and generating a new enemy.
*/
void kill_enemy() {
    /** @todo
     * This functions badly needs to be split up.
     */ 
    double xp_mod = 1;
    double lv_diff;
    int roll;
    double e_SP,e_bonus_SP;
    /* XP reward*/
    /** @todo
     * XP reward needs balance!
     */
    e.xp = 0;
    /*e_xp = round((e_maxhp + e_maxmp) / 2);*/ /* average of max HP/MP */
    /*e_xp=e_xp + round((e_STR+e_DEF + e_MAG) / 3);*/ /* average of stats */
    /*e_xp=e_xp + round(max(0,500 - e_maxwait));*/ /* +1 per wait below 500 */
    /*e_xp=e_xp + ((e_dice * 2) + e_dice_sides);*/ /* +2 per die, +1 per side */
    e.xp = e.xp + (e.lv * 10); /* +10 per level */
    lv_diff = e.lv - p.lv;

    while (lv_diff > 0) {
        xp_mod = xp_mod + 0.01; /* +1% per lv */
        --lv_diff;
    }
    while (lv_diff < 0) {
        xp_mod = xp_mod - 0.01; /* -1% per lv */
        ++lv_diff;
    }

    if (xp_mod > 2.0) xp_mod = 2.0; /* max +100% */
    if (xp_mod < 0.01) xp_mod = 0.01; /* max -99% */

    p.xp = p.xp + max(1,round(e.xp * xp_mod)); /* reward xp */
    ++stat_kills; /* increase kills by 1. */
    e.name[0] = 0;

    roll = roll_die(100);
    if (roll <= ITEM_DROP_CHANCE) {
        loot_req = ITEM_STAT_MAX;
        loot_lootable = 0;
        loot = roll_die(item_max); /* Equal chance for all items. */
        
        loot_type = item_db[loot].type;
        loot_req = item_db[loot].lv;
        loot_lootable = item_db[loot].lootable;
        loot_ap = item_db[loot].ap;
        loot_wait = item_db[loot].wait;
        loot_atk = item_db[loot].atk;
        loot_maxcon = item_db[loot].condition;
        loot_con = item_db[loot].condition;
        loot_str = item_db[loot].str;
        loot_eff = item_db[loot].effect;
        loot_part = item_db[loot].body_part;

        get_adjval();

        if (p.lv >= loot_req && loot_lootable == 1) {
            give_item(loot,loot_type,get_loot_mod(loot_req),item_adjval,loot_atk,\
            loot_ap + item_ap,loot_wait + item_wait,loot_maxcon * item_con,\
            loot_con * item_con,loot_str,loot_eff,loot_part);
        }
    }

    /* *** GENERATING NEW ENEMY STARTS HERE *** */

    e_bonus_SP = 0;
    lv_diff = 0;

    /* 10% chance to go down 1 lv*/
    if (roll_die(100) <= 10 && e.lv > 1) --e.lv;
    else {
        if (roll_die(100) <= LV_UP_CHANCE) ++e.lv;
    }

    /* difference in lv between player and enemy,
    every 10 gives enemy 1 extra SP. */
    lv_diff = p.lv - e.lv; /* recalculate for new e_lv */
    while (lv_diff >= 10) {
        ++e_bonus_SP;
        lv_diff = lv_diff - 5;
    }

    generate_name();

    /* reset to base stats
     Enemies don't have classes, so +1 to all per lv. */
    e.hp = e.lv + 25;
    e.maxhp = e.lv + 25;
    e.mp = e.lv + 10;
    e.maxmp = e.lv + 10;
    e.str = e.lv + 8;
    e.tou = e.lv + 8;
    e.mag = e.lv + 8;
    e.wait = round(e.lv / 5) + 500;
    e.max_wait = round(e.lv / 5) + 500;
    e.bonus_damage = 0.00;
    e.ap = 0;
    //e.atk = 0;
    e.status_id = 0;
    e.status_str = 0;
    e.status_dur = 0;

    /* Distribute SP */
    e_SP = e.lv - 1;
    e_SP = e_SP + e_bonus_SP;
    e_SP += 1;
    while (e_SP > 0) {
        if (e.maxhp < STAT_MAX) e.maxhp = e.maxhp + 2;
        if (e.maxmp < STAT_MAX) e.maxmp = e.maxmp + 2;
        if (e.str < STAT_MAX) ++e.str;
        if (e.tou < STAT_MAX) ++e.tou;
        if (e.mag < STAT_MAX) ++e.mag;
        if (e.max_wait < 9999) e.max_wait = e.max_wait + 5;
        if (e.max_wait > 9999) e.max_wait = 9999;

        roll = roll_die(9);
        if (roll == 1) {
            ++e.str;
            e.tou = e.tou - 2;
            e.mag = e.mag - 2;
        }
        else if (roll == 2) {
            e.str = e.str - 2;
            ++e.tou;
            e.mag = e.mag - 2;
        }
        else if (roll == 3) {
            e.str = e.str - 2;
            e.tou = e.tou - 2;
            ++e.mag;
        }
        else if (roll == 4) {
            /// @todo increase atk.
        }
        else if (roll == 5) {
            ++e.maxhp;
            e.maxmp = e.maxmp - 3;
        }
        else if (roll == 6) {
            ++e.maxmp;
            e.maxhp = e.maxhp - 3;
        }
        else if (roll == 7) {
            e.max_wait = e.max_wait - 20;
        }
        else if (roll == 8) {
            e.bonus_damage = e.bonus_damage + 0.15;
        }
        else if (roll == 9) {
            ++e.ap;
        }
        --e_SP;

        if (e.maxhp > STAT_MAX) e.maxhp = STAT_MAX;
        if (e.maxmp > STAT_MAX) e.maxmp = STAT_MAX;
        if (e.str > STAT_MAX) e.str = STAT_MAX;
        if (e.tou > STAT_MAX) e.tou = STAT_MAX;
        if (e.mag > STAT_MAX) e.mag = STAT_MAX;
        //if (e.atk > STAT_MAX) e.atk = STAT_MAX;
        if (e.max_wait > 9999) e.max_wait = 9999;
        if (e.bonus_damage > STAT_MAX) e.bonus_damage = STAT_MAX;
        if (e.ap > STAT_MAX) e.ap = STAT_MAX;

        if (e.str < 1) e.str = 1;
        if (e.tou < 1) e.tou = 1;
        if (e.mag < 1) e.mag = 1;
        if (e.max_wait < 100) e.max_wait = 100;
    }
    e.hp = e.maxhp;
    e.mp = e.maxmp;
    e.wait = e.max_wait;
}

void generate_name() {
    int roll;
    /* give the enemy a random name based on level.
     names should be nonsensical (at first)
     Anything from inanimate objects to abstract thoughts
     later on, more "realistic" enemies will start to show up.

    enemy name ideas - I have terrible memory, so I made a list
    of names I think of when I'm doing something else, and have
    been to lazy to actually implement.

    Stale/Regular/Fresh Muffin
    (Land) Shark
    <color/type> Flower
    glacier
    Algebra/Trig/Cal
    Hawk
    Falcon
    scum
    (newb/leet/uber) hacker/cracker
    (crunchy) foobar
    (chocolate) kludge
    (paper) airplane
    reticulated spline
    peltist
    peasant
    slot machine
    jumping rope
    murmillo
    various shapes
    various fruit/vegi
    attacker
    various emotes
    (sparkly) disco ball
    DJ
    MC
    tax collector
    killer
    */

    /** @note
     * Is there a better way to do this? It'll get unwieldy very fast.
     */

    while (e.name[0] == 0) {
        roll = roll_die(20);
        if (roll == 1) e.name[0] = 1;
        else if (roll == 2 && e.lv >= 3) e.name[0] = 2;
        else if (roll == 3 && e.lv >= 5) e.name[0] = 3;
        else if (roll == 4 && e.lv >= 8) e.name[0] = 4;
        else if (roll == 5 && e.lv >= 10) e.name[0] = 5;
        else if (roll == 6 && e.lv >= 12) e.name[0] = 6;
        else if (roll == 7 && e.lv >= 16) e.name[0] = 7;
        else if (roll == 8 && e.lv >= 20) e.name[0] = 8;
        else if (roll == 9 && e.lv >= 23) e.name[0] = 9;
        else if (roll == 10 && e.lv >= 25) e.name[0] = 10;
        else if (roll == 11 && e.lv >= 26) e.name[0] = 11;
        else if (roll == 12 && e.lv >= 28) e.name[0] = 12;
        else if (roll == 13 && e.lv >= 30) e.name[0] = 13;
        else if (roll == 14 && e.lv >= 33) e.name[0] = 14;
        else if (roll == 15 && e.lv >= 37) e.name[0] = 15;
        else if (roll == 16 && e.lv >= 41) e.name[0] = 16;
        else if (roll == 17 && e.lv >= 45) e.name[0] = 17;
        else if (roll == 18 && e.lv >= 47) e.name[0] = 18;
        else if (roll == 19 && e.lv >= 50) e.name[0] = 19;
        //else if (roll == 20 && e.lv >= 51) e.name[0] = 20;
    }
}

/**
 * Gets an enemy name from the name
 * array.
 *
 * It prints the name at the cursor's
 * position when found.
 */
void get_e_name(WINDOW *w) {
    wattron(w,COLOR_PAIR(e_namedb[e.name[0]].color));
    wprintw(w,"%s",e_namedb[e.name[0]].name);
    wattron(w,COLOR_PAIR(6));
}

void init_e_names() {
    int cur_id = 0;

    strcpy(e_namedb[cur_id].name,"Dummy");
    e_namedb[cur_id].color = 5;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"an apple");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a balloon");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a cat");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a stapler");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a slug");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a spoon");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a purse");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a pebble");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a napkin");
    e_namedb[cur_id].color = 6;

    ++cur_id;

    strcpy(e_namedb[cur_id].name,"a killer ampersand");
    e_namedb[cur_id].color = 1;

    ++cur_id;
    
    while (cur_id < 20) {
    	strcpy(e_namedb[cur_id].name,"Unnamed");
    	e_namedb[cur_id].color = 2;
    	++cur_id;
    }
}

/**
 * Gets mod value of looted item.
 *
 * This is the value after an item name,
 * for example potion +5.
 *
 * @param i_lv level of item
 * @returns final mod value
 */
double get_loot_mod(double i_lv) {
    double total_mod = 0;
    double chances = 0;
    
    chances = e.lv - p.lv; /* Enemy is higher lv; good */
    if (chances < 0) chances = 0;

    chances = chances + (p.lv-i_lv); /* Player should be a higher lv than the item */
    if (chances < 0) chances = 0;

    while (chances > 0) {
        if (roll_die(100) <= 20) { /* 20% chance of mod changing */
            if (roll_die(100) <= 50) ++total_mod; /* 50% for +1, else -1 */
            else --total_mod;
        }
        --chances;
    }
    return total_mod;
}

void enemy_turn() {
    int i,j,sc = 0,mid,cc;
    /** @note
      * The enemy requires being 5 levels higher than the player to cast a certain spell -
      * Not sure how I feel about that...
      */
    if (e.wait == 0 && (p.wait > 0 || p.status_id == STUN_ID) && e.status_id != STUN_ID) {
        /* enemy is ready to act. */
        if (e.hp > 0) {
            /* 50% chance to cast any may magic. */
            cc = roll_die(100);
            if (cc <= 50) {
                /* cast Heal if HP <= 50% MaxHP. Lv >= HEAL_LV+5 required.
                Will always cast heal if necessary.*/
                mid = 0;
                for (i = 0;i <= MAGIC_MAX;++i) {
                    if (strcmp("Heal",magic_db[i].name) == 0) {
                        mid = i;
                        break;
                    }
                }
                if (e.hp < (e.maxhp / 2) && e.mp >= magic_db[mid].cost && e.lv >= magic_db[mid].lv + 5) {
                    magic_formula(mid,1);
                    sc = 1;
                }
                /* Reset mid and find a new spell. */
                if (sc == 0) {
                	mid = 0;
                	i = -1;
                	for (j = 0;j <= MAGIC_MAX;++j) {
                        if (roll_die(100) <= 20) {
                            mid = j;
                            i = 0;
                            break;
                        }
                    }
                    if (i != -1) {
                	    /* Only if a spell was chosen */
                	    cc = roll_die(100);
                        if (cc <= 50 && e.mp >= magic_db[mid].cost && e.lv >= magic_db[mid].lv + 5) {
                            magic_formula(mid,1);
                            sc = 1;
                        }
                    }
                }
            }
            if (cc > 50 || (cc <= 50 && sc == 0)) {
                /* The enemy chose to attack OR they didn't cast something when that
                was chosen. */
                attack_formula(1);
            }
            if (e.status_id == HASTE_ID) {
                e.wait = e.max_wait - e.status_str > 9999 ? 9999 : (int)e.status_str;
            }
            else e.wait = e.max_wait;
        }
    } /* end of enemy's turn */
    else if (e.wait == 0 && p.wait > 0) {
        e.wait = e.max_wait;
    }
}
/*
void set_enemy(double new_hp, double new_mp, double new_STR, double new_DEF, double new_MAG,\
 double new_dice, double new_dice_sides, double new_bonus_damage, double new_lv, double new_AP,\
 double new_maxwait) {
    e.hp=new_hp;
    e.maxhp=new_hp;
    e.mp=new_mp;
    e.maxmp=new_mp;
    e.str=new_STR;
    e.def=new_DEF;
    e.mag=new_MAG;
    e.dice=new_dice;
    e.dice_sides=new_dice_sides;
    e.bonus_damage=new_bonus_damage;
    e.lv=new_lv;
    e.ap=new_AP;
    e.max_wait=new_maxwait;
    e.status=0;
    e.status_dur=0;
    e.status_str=0;
    e.wait=e_max_wait;
}*/
