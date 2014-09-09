#include <stdio.h>
#include <stdlib.h>
#ifdef __linux__
    #include <ncurses.h>
#else
    #include <curses.h>
#endif
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

void attack_formula(struct Character *at,struct Character *de) {
    /* target = 1 if player being attacked, enemy otherwise */
    double dmg = 0; /* damage */
    double ap = de->head_ap + de->body_ap + de->legs_ap + de->feet_ap + de->hands_ap + de->equip_ap;
    int roll = 0,has_armor = 0;
    double rdmg = 0,a = 0;
    char m[50];

    /* Find damage */
    dmg = round((at->str + at->equip_atk) - ((de->tou + ap) / 2));

    /* Vary damage by a random amount */
    a = roll_die(21);
    while (a > 1) {
        roll = roll_die(2);
        if (roll == 1) rdmg = rdmg + 0.01;
        else rdmg = rdmg - 0.01;
        --a;
    }
    if (rdmg > 1.2) rdmg = 1.2;
    if (rdmg < 0.8) rdmg = 0.8;
    dmg = round(dmg * rdmg);

    if (dmg < 1) dmg = 1;

    int hit = 0;
    de->hp = de->hp - dmg;

    if (de->body_id != 0 || de->head_id != 0 || de->feet_id != 0 || de->hands_id != 0 || de->legs_id != 0) has_armor = 1;
    if (has_armor == 1) {
        while (1) {
            roll = roll_die(5);

            while (hit == 0) {
                /* If there's no armor in the chosen slot, move damage
                    to next slot. */
                if (roll == 1 && de->head_id == 0 && hit == 0) roll = 2;
                else hit = 1;

                if (roll == 2 && de->body_id == 0 && hit == 0) roll = 3;
                else hit = 1;

                if (roll == 3 && de->legs_id == 0 && hit == 0) roll = 4;
                else hit = 1;

                if (roll == 4 && de->feet_id == 0 && hit == 0) roll = 5;
                else hit =  1;

                if (roll == 5 && de->hands_id == 0 && hit == 0) roll = 1;
                else hit = 1;
            }


            if (roll == 1 && de->head_id != 0) {
                de->head_con = de->head_con - dmg;
                if (de->head_con <= 0) unequip_item(de, 2);
                break;
            }
            else if (roll == 2 && de->body_id != 0) {
                de->body_con = de->body_con - dmg;
                if (de->body_con <= 0) unequip_item(de, 3);
                break;
            }
            else if (roll == 3 && de->hands_id != 0) {
                de->hands_con = de->hands_con - dmg;
                if (de->hands_con <= 0) unequip_item(de, 6);
                break;
            }
            else if (roll == 4 && de->legs_id != 0) {
                de->legs_con = de->legs_con - dmg;
                if (de->legs_con <= 0) unequip_item(de, 4);
                break;
            }
            else if (roll == 5 && de->feet_id != 0) {
                de->feet_con = de->feet_con - dmg;
                if (de->feet_con <= 0) unequip_item(de, 5);
                break;
            }
        }
    }

    /* Temp kludge to check if enemy is attacking. */
    if (at->species == -1) {
        sprintf(m,"Enemy attacks! Damage: %.0f",dmg);
        add_msg(m,RED);
        stat_p_dam_taken = stat_p_dam_taken + dmg; /* stat */
    }
    else {
        sprintf(m,"You attack! Damage: %.0f",dmg);
        add_msg(m,GREEN);
        stat_p_dam_dealt = stat_p_dam_dealt + dmg;
        award_sk_xp(SKILL_FIGHTING,max(1,dmg / 10));
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
    char m[50];

    struct Magic stc;
    stc = magic_db[sid];

    if (user == 0) {
        p.mp = p.mp - stc.cost;
        sprintf(m,"Casting %s...",stc.name);
        add_msg(m,GREEN);
    }
    else {
        e.mp = e.mp - stc.cost;
        sprintf(m,"Enemy is casting %s...",stc.name);
        add_msg(m,YELLOW);
    }

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
                sprintf(m,"You heal yourself for %.0f damage.",result);
                add_msg(m,CYAN);
            }
            else {
                e.hp = e.hp + result;
                if (e.hp > e.maxhp) e.hp = e.maxhp;
                sprintf(m,"The enemy is healed for %.0f damage.",result);
                add_msg(m,YELLOW);
            }
        }
        else {
            minn = min(e.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);

            if (stc.invert == 0) {
                e.hp = e.hp + result;
                if (e.hp > e.maxhp) e.hp = e.maxhp;
                sprintf(m,"The enemy heals itself for %.0f damage.",result);
                add_msg(m,YELLOW);
            }
            else {
                p.hp = p.hp + result;
                if (p.hp > p.maxhp) p.hp = p.maxhp;
                sprintf(m,"You are healed for %.0f damage.",result);
                add_msg(m,GREEN);
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
                sprintf(m,"You blast the enemy for %.0f damage.",result);
                add_msg(m,GREEN);
            }
            else {
                p.hp = p.hp - result;
                sprintf(m,"You blast yourself for %.0f damage.",result);
                add_msg(m,RED);
            }
        }
        else {
            minn = min(e.mag / stc.diff,MAGIC_MAX_PERCENT);
            maxx = max(MAGIC_MIN_PERCENT,minn);
            result = round(stc.str * maxx);

            if (stc.invert == 0) {
                p.hp = p.hp - result;
                sprintf(m,"You are blasted for %.0f damage.",result);
                add_msg(m,GREEN);
            }
            else {
                e.hp = e.hp - result;
                sprintf(m,"The enemy blasted itself for %.0f damage.",result);
                add_msg(m,GREEN);
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
            while (1) {
                p.equip_maxcon = p.equip_maxcon - 2;
                p.equip_con = p.equip_con + 1;
                if (p.equip_con > p.equip_maxcon) p.equip_con = p.equip_maxcon;
                if (p.equip_con == p.equip_maxcon) break;
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
