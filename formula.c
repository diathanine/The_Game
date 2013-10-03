#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "formula.h"
#include "globals.h"
#include "item.h"
#include "magic.h"

int get_sk_chances(int primary, int secondary) {
    /* Secondary is assumed to be the "specific" skill, which gives
    a bigger bonus. */
    int total=0;

    while (primary>=10) {
        ++total;
        primary=primary-10;
    }
    while (secondary>=5) {
        ++total;
        secondary=secondary-5;
    }

    return total;
}

int roll_sk_bonus(int old_r, int chances) {
    int result=old_r;
    while (chances > 0) {
        if (roll_die(100) <= 50) ++result;
        --chances;
    }

    return result;
}

void attack_formula(int target) {
    /* target=1 if player being attacked, enemy otherwise */
    double D=0; /* Final damage */
    double R=0; /* Modifier */
    double i=0; /* dice */
    int roll=0,has_armor=0;
    /* Find % difference between STR and DEF */
    if (target==1) {
        R=e.str / p.def;
        /* MIN_PER < R < MAX_PER; check if R is higher then MIN with max(),
        then check if it's lower than MAX with min().*/
        R = max(R,MIN_ATTACK_PER);
        R = min(R,MAX_ATTACK_PER);
    }
    else {
        R = p.str / e.def;
        R = max(R,MIN_ATTACK_PER);
        R = min(R,MAX_ATTACK_PER);
    }

    if (target == 1) {
        i = e.dice;
        while (i > 0) {
            D = D +(rand() % (unsigned int)e.dice_sides) + 1;
            --i;
        }
        D = D + e.bonus_damage;
    }
    else {
        i = p.dice;
        while (i > 0) { /* roll for each die player has */
            D = D + (rand() % (unsigned int)p.dice_sides) + 1; /* die has no "0" side, so add 1 */
            --i;
        }
        D = D +p.bonus_damage;
        D = roll_sk_bonus(D,get_sk_chances(skill[SKILL_FIGHTING][0],0));
    }

    D = max(1,round(D * R));

    if (target == 1) {        
        double ap = p.head_ap + p.body_ap + p.legs_ap + p.feet_ap + p.hands_ap + p.equip_ap;
        int hit = 0;
        D = D - ap;
        D = max(1,D);
        p.hp = p.hp - D; /* Final damage, D. */

        if (p.body_id != 0 || p.head_id != 0 || p.feet_id != 0 || p.hands_id != 0 || p.legs_id != 0) has_armor = 1;
        if (has_armor == 1) {
            while (true) {
                roll = roll_die(5);

                while (hit == 0) {
                    /* If there's no armor in the chosen slot, move damage
                       to next slot. */
                    if (roll == 1 && p.head_id == 0 && hit == 0) roll = 2;
                    else hit = 1;
                    
                    if (roll == 2 && p.body_id == 0 && hit == 0) roll = 3;
                    else hit = 1;
                    
                    if (roll == 3 && p.legs_id == 0 && hit == 0) roll = 4;
                    else hit = 1;
                    
                    if (roll == 4 && p.feet_id == 0 && hit == 0) roll = 5;
                    else hit =  1;
                    
                    if (roll == 5 && p.hands_id == 0 && hit == 0) roll = 1;
                    else hit = 1;
                }


                if (roll == 1 && p.head_id != 0) {
                    p.head_con = p.head_con - D;
                    if (p.head_con <= 0) unequip_item(2);
                    break;
                }
                else if (roll == 2 && p.body_id != 0) {
                    p.body_con = p.body_con - D;
                    if (p.body_con <= 0) unequip_item(3);
                    break;
                }
                else if (roll == 3 && p.hands_id != 0) {
                    p.hands_con = p.hands_con - D;
                    if (p.hands_con <= 0) unequip_item(6);
                    break;
                }
                else if (roll == 4 && p.legs_id != 0) {
                    p.legs_con = p.legs_con - D;
                    if (p.legs_con <= 0) unequip_item(4);
                    break;
                }
                else if (roll == 5 && p.feet_id != 0) {
                    p.feet_con = p.feet_con - D;
                    if (p.feet_con <= 0) unequip_item(5);
                    break;
                }
            }
        }
    }
    else {
        D = max(1,D - e.ap);
        e.hp = e.hp - D;
        if (p.equip_id != 0) {
            p.equip_con = p.equip_con - ceil(D / 10);
            if (p.equip_con <= 0) {
                unequip_item(1);
            }
        }
    }

    if (target == 1) {
        stat_p_dam_taken = stat_p_dam_taken + D; /* stat */
        e_dmg_dealt = e_dmg_dealt + D; /* this turn */
    }
    else {
        stat_p_dam_dealt = stat_p_dam_dealt + D;
        p_dmg_dealt = p_dmg_dealt + D;
        award_sk_xp(SKILL_FIGHTING,max(1,D / 10));
    }
}

/**
 * Handles casting of magic.
 * 
 * @param sid ID of spell.
 * @param user 0 = player, else enemy.
 */
void magic_formula(int sid, int user) {
    double minn,maxx,result;

    struct Magic stc;
    stc = magic_db[sid];
    
    if (user == 0) p.mp = p.mp - stc.cost;
    else e.mp = e.mp - stc.cost;
    
    if (p.mp < 0) p.mp = 0;
    if (e.mp < 0) e.mp = 0;

    if (stc.effect==MEF_HEAL) {
        if (user == 0) {
            minn = min(p.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);
            result = roll_sk_bonus(result,get_sk_chances(skill[SKILL_CASTING_GEN][0],skill[stc.skill][0]));
            
            if (stc.invert == 0) {
                p.hp = p.hp + result;
                if (p.hp > p.maxhp) p.hp = p.maxhp;
            }
            else {
                e.hp = e.hp + result;
                if (e.hp > e.maxhp) e.hp = e.maxhp;
            }
        }
        else {
            minn = min(e.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);

            if (stc.invert == 0) {
                e.hp = e.hp + result;
                if (e.hp > e.maxhp) e.hp = e.maxhp;
            }
            else {
                p.hp = p.hp + result;
                if (p.hp > p.maxhp) p.hp = p.maxhp;
            }
        }
    }
    else if (stc.effect == MEF_DMG) {
        if (user == 0) {
            minn = min(p.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);
            result = roll_sk_bonus(result,get_sk_chances(skill[SKILL_CASTING_GEN][0],skill[stc.skill][0]));

            if (stc.invert == 0) {
                e.hp = e.hp - result;
            }
            else {
                p.hp = p.hp - result;
            }
        }
        else {
            minn = min(e.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);

            if (stc.invert == 0) {
                p.hp = p.hp - result;
            }
            else {
                e.hp = e.hp - result;
            }
        }
    }
    else if (stc.effect == MEF_STA) {
        if (user == 0) {
            minn = min(p.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);
            result = roll_sk_bonus(result,get_sk_chances(skill[SKILL_CASTING_GEN][0],skill[stc.skill][0]));

            if (stc.invert == 0) {
                p.status_id = stc.status;
                p.status_str = result;
                p.status_dur = 5 + round(result / 3);
            }
            else {
                e.status_id = stc.status;
                e.status_str = result;
                e.status_dur = 5 + round(result / 3);
            }
        }
        else {
            minn = min(e.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);

            if (stc.invert == 0) {
                e.status_id = stc.status;
                e.status_str = result;
                e.status_dur = 5 + round(result / 3);
            }
            else {
                p.status_id = stc.status;
                p.status_str = result;
                p.status_dur = 5 + round(result / 3);
            }
        }
    }
    else if (stc.effect == MEF_RPW) {
        if (user == 0) {
            minn = min(p.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);
            result = roll_sk_bonus(result,get_sk_chances(skill[SKILL_CASTING_GEN][0],skill[stc.skill][0]));

            while (result > 0) {
                p.equip_maxcon = p.equip_maxcon - 2;
                p.equip_con = p.equip_con + 1;
                --result;
            }

            if (p.equip_con > p.equip_maxcon) p.equip_con = p.equip_maxcon;
            if (p.equip_maxcon <= 0) p.equip_id = 0;
        }
    }
    
    if (user == 0) ++stat_m_casts;
}

/**
 * Returns a percentage for magic menu.
 * 
 */
/** @todo
 * This should be made into a function
 * for general use, not just spells.
 */
double percentage(double diff,float min_per,float max_per) { /* for giving an actual % */
    double minn,maxx,final;

    minn = min(p.mag / diff,max_per);
    maxx = max(minn,min_per);
    final = maxx;
    final = final * 100;

    return final;
}

/**
 * Returns the modified str of a spell.
 * 
 */
/** @todo
 * This should be repurposed to be
 * a general percentage finder, not
 * just for spells.
 */ 
double percentage_str(double str,double diff,float min_per,float max_per) { /* For giving a number based on a % */
    double minn,maxx,final;

    minn = min(p.mag/diff,max_per);
    maxx = max(minn,min_per);
    final = round(str * maxx);

    return final;
}