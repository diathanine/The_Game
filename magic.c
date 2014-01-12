#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "magic.h"
#include "status.h"
#include "globals.h"

void init_magic() {
    int cur_id = 0;

    strcpy(magic_db[cur_id].name,"Heal");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_HEAL;
    magic_db[cur_id].status = 0;
    magic_db[cur_id].invert = 0;
    magic_db[cur_id].cost = 10;
    magic_db[cur_id].str = 20;
    magic_db[cur_id].diff = 60;
    magic_db[cur_id].lv = 1;
    magic_db[cur_id].skill = SKILL_CASTING_HEA;
    strcpy(magic_db[cur_id].desc,"(Healing) Restores a small amount of HP.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Fire");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_DMG;
    magic_db[cur_id].status = 0;
    magic_db[cur_id].invert = 0;
    magic_db[cur_id].cost = 8;
    magic_db[cur_id].str = 15;
    magic_db[cur_id].diff = 60;
    magic_db[cur_id].lv = 1;
    magic_db[cur_id].skill = SKILL_CASTING_FIR;
    strcpy(magic_db[cur_id].desc,"(Fire) Singe your foes for minor damage.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Ice");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_DMG;
    magic_db[cur_id].status = 0;
    magic_db[cur_id].invert = 0;
    magic_db[cur_id].cost = 6;
    magic_db[cur_id].str = 10;
    magic_db[cur_id].diff = 50;
    magic_db[cur_id].lv = 1;
    magic_db[cur_id].skill = SKILL_CASTING_WAT;
    strcpy(magic_db[cur_id].desc,"(Water) Chill your enemies for little damage.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Earth");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_DMG;
    magic_db[cur_id].status = 0;
    magic_db[cur_id].invert = 0;
    magic_db[cur_id].cost = 10;
    magic_db[cur_id].str = 20;
    magic_db[cur_id].diff = 70;
    magic_db[cur_id].lv = 1;
    magic_db[cur_id].skill = SKILL_CASTING_EAR;
    strcpy(magic_db[cur_id].desc,"(Earth) Pelt your enemy with pebbles for small damage.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Poison");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_STA;
    magic_db[cur_id].status = POISON_ID;
    magic_db[cur_id].invert = 1;
    magic_db[cur_id].cost = 30;
    magic_db[cur_id].str = 5;
    magic_db[cur_id].diff = 80;
    magic_db[cur_id].lv = 3;
    magic_db[cur_id].skill = SKILL_CASTING_STA;
    strcpy(magic_db[cur_id].desc,"(Status) Poisons your enemy, doing damage over time.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Stun");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_STA;
    magic_db[cur_id].status = STUN_ID;
    magic_db[cur_id].invert = 1;
    magic_db[cur_id].cost = 150;
    magic_db[cur_id].str = 3;
    magic_db[cur_id].diff = 200;
    magic_db[cur_id].lv = 7;
    magic_db[cur_id].skill = SKILL_CASTING_STA;
    strcpy(magic_db[cur_id].desc,"(Status) Prevents the enemy from doing anything.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Sap");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_STA;
    magic_db[cur_id].status = SAP_ID;
    magic_db[cur_id].invert = 1;
    magic_db[cur_id].cost = 50;
    magic_db[cur_id].str = 5;
    magic_db[cur_id].diff = 100;
    magic_db[cur_id].lv = 10;
    magic_db[cur_id].skill = SKILL_CASTING_STA;
    strcpy(magic_db[cur_id].desc,"(Status) Like Poison, but for MP.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Haste");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_STA;
    magic_db[cur_id].status = HASTE_ID;
    magic_db[cur_id].invert = 0;
    magic_db[cur_id].cost = 120;
    magic_db[cur_id].str = 25;
    magic_db[cur_id].diff = 250;
    magic_db[cur_id].lv = 25;
    magic_db[cur_id].skill = SKILL_CASTING_STA;
    strcpy(magic_db[cur_id].desc,"(Status) Temporarly lowers Wait.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Wall");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_STA;
    magic_db[cur_id].status = WALL_ID;
    magic_db[cur_id].invert = 0;
    magic_db[cur_id].cost = 80;
    magic_db[cur_id].str = 15;
    magic_db[cur_id].diff = 150;
    magic_db[cur_id].lv = 18;
    magic_db[cur_id].skill = SKILL_CASTING_STA;
    strcpy(magic_db[cur_id].desc,"(Status) Temporarly raises AP.");

    ++cur_id;

    strcpy(magic_db[cur_id].name,"Repair Weapon");
    magic_db[cur_id].id = cur_id;
    magic_db[cur_id].effect = MEF_RPW;
    magic_db[cur_id].status = 0;
    magic_db[cur_id].invert = 0;
    magic_db[cur_id].cost = 25;
    magic_db[cur_id].str = 0;
    magic_db[cur_id].diff = 1;
    magic_db[cur_id].lv = 15;
    magic_db[cur_id].skill = SKILL_CASTING_HEA;
    strcpy(magic_db[cur_id].desc,"(Healing) Repairs your weapon; makes it more brittle, however.");

    ++cur_id;
}

void magic_entry_item(WINDOW *s, int pos, int m) {
    struct Magic ms = magic_db[m];
    
    if (p.lv < ms.lv) {
        wattron(s,COLOR_PAIR(1));
        mvwprintw(s,pos,4,"??? Lv:%.0f",ms.lv);
    }
    else {
        if (p.mag <= (ms.diff * .25)) wattron(s,COLOR_PAIR(1));
        else if (p.mag <= (ms.diff * .5)) wattron(s,COLOR_PAIR(4));
        else if (p.mag <= (ms.diff)) wattron(s,COLOR_PAIR(6));
        else if (p.mag <= (ms.diff * 2)) wattron(s,COLOR_PAIR(3));
        else if (p.mag <= (ms.diff * 3)) wattron(s,COLOR_PAIR(2));
        else if (p.mag <= (ms.diff * 4)) wattron(s,COLOR_PAIR(7));
        else wattron(s,COLOR_PAIR(5));
    
        mvwprintw(s,pos,4,"%s",ms.name);
    }
}

/**
 * Displays the magic menu.
 * 
 * This is the list of spells the player sees when
 * they select "Magic" from the menu.
 * Takes an ncurses window as it's only argument.
 */
void magic_menu(WINDOW *s, int cur) {
    /*
    The for loop goes through all the ids, writing the current entry when it gets to it.
    IDs are ints.
    */
    /** @todo
     * MAGIC_MAX doesn't auto-update.
     */
    int m,pos = 2;
    struct Magic ms = magic_db[cur - 2];
    
    for (m = 0;m < MAGIC_MAX;++m) {
        magic_entry_item(s,pos,m);
        wattron(s,COLOR_PAIR(3));
        ++pos;
    }
    
    /** @bug
     * Descriptions do not wrap to the
     * next line nicely.
     */
    if (p.lv >= ms.lv) {
        mvwprintw(s,15,1,"Cost      : %.0f",ms.cost);
        mvwprintw(s,16,1,"Difficulty: %.0f MAG",ms.diff);
        mvwprintw(s,17,1,"Power     : %.0f",ms.str * (p.mag / ms.diff));
        mvwprintw(s,18,1,"Base Power: %.0f",ms.str);
        print_desc(s,ms.desc,20,1);
    }
}

int magic_main(WINDOW *w) {
    int i,ch,cho,hl;
    
    for (i = 0;i <= 39;++i) {
        mvwprintw(w,i,1,"                                                                            ");
    }
    
    hl = 2;
    cho = 0;
    
    while (cho == 0) {
        clean_sidebar(w);

        box(w,0,0);
        mvwprintw(w,hl,1,"-> ");
            
        mvwprintw(w,1,4,"Press c to cancel");
        magic_menu(w,hl);
                    
        wrefresh(w);
                    
        ch = wgetch(w);
        switch (ch) {
            case KEY_DOWN:
                if (hl < MAGIC_MAX + 1) hl = hl + 1;
                else hl = 2;
                break;
            case KEY_UP:
                if (hl > 2) hl = hl - 1;
                else hl = MAGIC_MAX + 1;
                break;
            case 0x0A: /* Enter */
                cho = hl;
                break;
            case 0x63: /* c */
                cho = -1;
                break;
            default:
                break;
        };
    }

    if (cho != -1 && cho > 1 && p.mp >= magic_db[cho - 2].cost) {
        if (p.lv >= magic_db[cho - 2].lv) {
            magic_formula(magic_db[cho - 2].id,0);
            award_sk_xp(SKILL_CASTING_GEN,max(1,(magic_db[cho - 2].cost / p.maxmp) * 1));
            award_sk_xp(magic_db[cho - 2].skill,max(1,(magic_db[cho - 2].cost / p.maxmp) * 1));
        }
        else cho = -1; /* Not high enough level; cancel choice */
    }
    else cho = -1; /* Not enough MP; cancel choice */
    
    return cho;
}
