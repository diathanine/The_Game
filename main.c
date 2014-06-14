/** @file main.c
 *
 * Where most of the code is at,
 * unfortunately.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#ifdef __linux__
    #include <ncurses.h>
#else
    #include <curses.h>
#endif

#include "globals.h"  /* stuff that's used everwur */
#include "status.h" /* status effects */
#include "item.h" /* defines/item and crafting menus */
#include "enemy.h" /* enemy killing/spawning and drawing */
#include "magic.h" /* defines/magic menu */
#include "formula.h" /* various formulas */
#include "file.h" /* saving, loading, resetting */

#define VERSION "Version 0.12.1 2014-04-12"

/* MISC */
/**
 * Rolls a die and returns the result.
 *
 * To roll multiple dice, use a loop.
 *
 * @param sides number of sides on die.
 *
 * @returns A result between 1 and sides.
 */
int roll_die(int sides) {
    int result;

    /* +1 so that result = 1 thru # of sides */
    if (sides > 1) result = (rand() % sides) + 1;
    else return 1;

    return result;
}

void init_skills() {
    int i;
    for (i = 0;i <= 12;++i) {
        skill[i][0] = 0; /* lv */
        skill[i][1] = 0; /* xp */
        skill[i][2] = 100; /* next */
    }
}

void draw_sk_bar(WINDOW *w, int xp, int xpn) {
    int a,b = 10;

    a = ((xp * 10) / xpn);
    while (a > 0) {
        wprintw(w,"#");
        --a;
        --b;
    }
    while (b > 0) {
        wprintw(w," ");
        --b;
    }
    wprintw(w,"] % 9d/% 9d",xp,xpn);
}

void draw_con_bar(WINDOW *w, double con, double maxcon) {
    int a,b = 10;

    a = ((con * 10) / maxcon);
    while (a > 0) {
        wprintw(w,"#");
        --a;
        --b;
    }
    while (b > 0) {
        wprintw(w," ");
        --b;
    }
    wprintw(w,"] %.0f/%.0f",con,maxcon);
}

void draw_stat_win(WINDOW *w) {
    double a;
    int b,stat_line;

    wclear(w);
    box(w,0,0);
    mvwprintw(w,0,2,"Status");
    stat_line = 1;
    wattron(w,COLOR_PAIR(2));
    mvwprintw(w,stat_line,1,"Name :");
    for (b = 0;b < 21;++b) {
        mvwprintw(w,stat_line,b + 8,"%c",p.name[b]);
    }

    stat_line++;
    if (p.hp < p.maxhp * .2) wattron(w,COLOR_PAIR(1) | A_BOLD | A_BLINK);
    mvwprintw(w,stat_line++,1,"HP   : %.0f",p.hp);
    wattron(w,COLOR_PAIR(2));
    wattroff(w,A_BOLD | A_BLINK);

    mvwprintw(w,stat_line++,1,"MaxHP: %.0f",p.maxhp);

    if (p.mp < p.maxmp * .2) wattron(w,COLOR_PAIR(1) | A_BOLD);
    mvwprintw(w,stat_line++,1,"MP   : %.0f",p.mp);
    wattron(w,COLOR_PAIR(2));
    wattroff(w,A_BOLD);

    mvwprintw(w,stat_line++,1,"MaxMP: %.0f",p.maxmp);

    a = 0.00;
    a = p.equip_atk + round(p.bonus_damage);

    mvwprintw(w,stat_line++,1,"STR  : %.0f",p.str);
    if (a != 0.00) wprintw(w,"%+.0f",a);

    mvwprintw(w,stat_line++,1,"TOU  : %.0f",p.tou);
    mvwprintw(w,stat_line++,1,"MAG  : %.0f",p.mag);
    mvwprintw(w,stat_line++,1,"Wait : %d/%d",p.wait,p.max_wait);

    b = 0;
    b = (p.status_id == HASTE_ID) ? p.status_str * -1 : 0;
    b = b + p.equip_wait + p.head_wait + p.body_wait + p.legs_wait + p.feet_wait + p.hands_wait;

    if (b != 0) {
        if (b > 0) wattron(w,COLOR_PAIR(1));
        else if (b < 0) wattron(w,COLOR_PAIR(3));
        wprintw(w,"%+d",b);
        wattron(w,COLOR_PAIR(2));
    }

    /*
    * A status effect will work if it's ID isn't regisered here,
    * but won't display properly. */
    if (p.status_id == FINE_ID) mvwprintw(w,stat_line,1,"Staus: Fine");
    else if (p.status_id == POISON_ID) {
        wattron(w,COLOR_PAIR(5));
        mvwprintw(w,stat_line,1,"Staus: Poisoned!");
    }
    else if (p.status_id == STUN_ID) {
        wattron(w,COLOR_PAIR(6));
        mvwprintw(w,stat_line,1,"Staus: Stunned!");
    }
    else if (p.status_id == SAP_ID) {
        wattron(w,COLOR_PAIR(7));
        mvwprintw(w,stat_line,1,"Staus: MP Sap!");
    }
    else if (p.status_id == WALL_ID) {
        wattron(w,COLOR_PAIR(6) | A_REVERSE);
        mvwprintw(w,stat_line,1,"Staus: Wall!");
        wattroff(w,A_REVERSE);
    }
    else if (p.status_id == HASTE_ID) {
        wattron(w,COLOR_PAIR(3));
        mvwprintw(w,stat_line,1,"Staus: Haste!");
    }
    else mvwprintw(w,stat_line,1,"Staus: ID:#%d:BUG",p.status_id);
    if (p.status_id != FINE_ID) wprintw(w," - %.0f turns",p.status_dur);
    wattron(w,COLOR_PAIR(2));

    stat_line++;
    a = p.equip_ap;
    if (p.status_id == WALL_ID) a = a + p.status_str;
    a = a + p.head_ap + p.body_ap + p.legs_ap + p.feet_ap + p.hands_ap;

    if (a > 0.0) wattron(w,COLOR_PAIR(3));
    else if (a < 0.0) wattron(w,COLOR_PAIR(1));
    mvwprintw(w,stat_line++,1,"AP   : %+.0f",a);
    wattron(w,COLOR_PAIR(2));

    mvwprintw(w,stat_line++,1,"LV   : %.0f",p.lv);
    mvwprintw(w,stat_line++,1,"XP   : %.0f",p.xp);
    mvwprintw(w,stat_line++,1,"NxtLv: %.0f",p.next_xp);

    wrefresh(w);
}

void draw_enemy_win(WINDOW *w) {
    int stat_line;

    wclear(w);
    box(w,0,0);
    mvwprintw(w,0,2,"Enemy");

    stat_line = 1;
    mvwprintw(w,stat_line++,1,"Enemy: ");
    get_e_name(w,(int)e.name[0]);

    if (e.hp < e.maxhp * .2) wattron(w,COLOR_PAIR(1));
    mvwprintw(w,stat_line++,1,"HP   : %.0f",e.hp);
    wattron(w,COLOR_PAIR(6));

    mvwprintw(w,stat_line++,1,"MaxHP: %.0f",e.maxhp);

    if (e.mp < e.maxmp * .2) wattron(w,COLOR_PAIR(1));
    mvwprintw(w,stat_line++,1,"MP   : %.0f",e.mp);
    wattron(w,COLOR_PAIR(6));

    mvwprintw(w,stat_line++,1,"MaxMP: %.0f",e.maxmp);
    mvwprintw(w,stat_line++,1,"STR  : %.0f",e.str);
    mvwprintw(w,stat_line++,1,"TOU  : %.0f",e.tou);
    mvwprintw(w,stat_line++,1,"MAG  : %.0f",e.mag);
    mvwprintw(w,stat_line++,1,"Wait : %d/%d%+.0f",e.wait,e.max_wait,\
                (e.status_id == HASTE_ID) ? e.status_str : 0.0);

    if (e.status_id == FINE_ID) mvwprintw(w,stat_line,1,"Staus: Fine");
    else if (e.status_id == POISON_ID) {
        wattron(w,COLOR_PAIR(5));
        mvwprintw(w,stat_line,1,"Staus: Poisoned!");
    }
    else if (e.status_id == STUN_ID) mvwprintw(w,stat_line,1,"Staus: Stunned!");
    else if (e.status_id == SAP_ID) {
        wattron(w,COLOR_PAIR(7));
        mvwprintw(w,stat_line,1,"Staus: MP Sap!");
    }
    else if (e.status_id == WALL_ID) {
        wattron(w,COLOR_PAIR(6) || A_REVERSE);
        mvwprintw(w,stat_line,1,"Staus: Wall!");
        wattroff(w,A_REVERSE);
    }
    else if (e.status_id == HASTE_ID) {
        wattron(w,COLOR_PAIR(3));
        mvwprintw(w,stat_line,1,"Staus: Haste!");
    }
    else mvwprintw(w,stat_line,1,"Staus: ID:#%dBUG",e.status_id);
    if (e.status_id != FINE_ID) wprintw(w," - %.0f turns",e.status_dur);
    wattron(w,COLOR_PAIR(6));

    stat_line++;
    mvwprintw(w,stat_line++,1,"AP   : %.0f",e.ap);
    mvwprintw(w,stat_line++,1,"LV   : %.0f",e.lv);

    wrefresh(w);
}

/**
 * A simple function to return the terminal to a usable state before crashing.
 *
 * @param str The error message to print.
 */
void early_termination(char str[]) {
    echo();
    printw("The_Game has crashed...\n%s",str);
    refresh();
    getch();
    endwin();
    exit(1);
}

/**
 * Gives XP to skills.
 *
 * @param id ID of the skill.
 * @param amount Amount of XP to give.
 */
void award_sk_xp(int id,int amount) {
    /* award xp */
    skill[id][1] = skill[id][1] + amount;
    while (skill[id][1] >= skill[id][2]) {
        if (skill[id][0] < SKILL_MAX_LEVEL) {
            ++skill[id][0];
            if (id == SKILL_FIGHTING) {
                ++p.maxhp;
                if (skill[id][0] % 3 == 0) ++p.str;
                if (skill[id][0] % 3 == 0) ++p.tou;
                if (skill[id][0] % 5 == 0) ++p.bonus_damage;
            }
            else if (id == SKILL_CRAFTING_GEN) {
                ++p.maxhp;
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
            }
            else if (id == SKILL_CRAFTING_HEA) {
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
                if (skill[id][0] % 2 == 0) --p.wait;
            }
            else if (id == SKILL_CRAFTING_ATT) {
                ++p.maxhp;
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.str;
            }
            else if (id == SKILL_CRAFTING_WAA) {
                ++p.maxhp;
                if (skill[id][0] % 3 == 0) ++p.str;
                if (skill[id][0] % 3 == 0) ++p.tou;
                if (skill[id][0] % 5 == 0) ++p.bonus_damage;
            }
            else if (id == SKILL_CRAFTING_OTH) {
                ++p.maxhp;
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
            }
            else if (id == SKILL_CASTING_GEN) {
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
            }
            else if (id == SKILL_CASTING_HEA) {
                ++p.maxhp;
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
            }
            else if (id == SKILL_CASTING_ATT) {
                ++p.maxhp;
                if (skill[id][0] % 3 == 0) ++p.mag;
            }
            else if (id == SKILL_CASTING_STA) {
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.tou;
                if (skill[id][0] % 3 == 0) ++p.mag;
            }
            else if (id == SKILL_CASTING_FIR) {
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
                if (skill[id][0] % 5 == 0) ++p.bonus_damage;
            }
            else if (id == SKILL_CASTING_WAT) {
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
            }
            else if (id == SKILL_CASTING_EAR) {
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.mag;
                if (skill[id][0] % 3 == 0) ++p.tou;
            }
            else {
                ++p.maxhp;
                ++p.maxmp;
                if (skill[id][0] % 3 == 0) ++p.str;
                if (skill[id][0] % 3 == 0) ++p.tou;
                if (skill[id][0] % 3 == 0) ++p.mag;
                if (skill[id][0] % 5 == 0) ++p.bonus_damage;
            }
            skill[id][1] = skill[id][1] - skill[id][2];
            if (skill[id][2] < SKILL_MAX_XP_NEEDED) skill[id][2] = skill[id][2] + 50;
        }
        else skill[id][1] = 0;
    }
}

char *choices[]={
    "Attack",
    "Magic",
    "Item",
    "Craft",
    "Stats",
    "SAVE & QUIT",
};

#define MAX_CHOICES 6 /* Number of choices in above array. Start counting at 1! */

int n_choices = sizeof(choices)/sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight, int x, int y);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int stat_win_startx = 0,stat_win_starty = 0;
int choice_win_startx = 30,choice_win_starty = 0;
int enemy_win_startx = 0,enemy_win_starty = 18;
int sidebar_startx = 50,sidebar_starty = 0;

/** @todo
 * Everything used to be defined outside functions;
 * this was changed, so these can be moved where they are
 * actually needed.
 */
int a,b,c,d,i,f,g; /* ints for random use */
double v,w,x,y,z; /* doubles for random use */
int ii = 0,sizeofname = 0;

int main(int argc, char *argv[]) {
	WINDOW *stat_win,*choice_win,*enemy_win,*sidebar;
	int highlight = 1,shl = 1,choice = 0,schoice = 0;
	int ch,i,pg;

	/* schoice: (sidebar choice)
        -1: Cancel action without taking player's turn
         0: Waiting for choice
        >0: Choice made
	*/

	srand(time(NULL));

    init_globals(); /* set global stuff to default values */
    item_max = init_items(); /* create the items. */
    init_magic(); /* create the spells. */
    init_skills(); /* set the skills */
    init_e_names(); /* set enemy names */

	initscr(); /* Start curses mode */

	cbreak();
	noecho();
	clear();
	keypad(stdscr,TRUE);

	stat_win = newwin(STAT_HEIGHT,STAT_WIDTH,stat_win_starty,stat_win_startx);
	choice_win = newwin(CHOICE_HEIGHT,CHOICE_WIDTH,choice_win_starty,choice_win_startx);
	enemy_win = newwin(MAIN_HEIGHT,MAIN_WIDTH,enemy_win_starty,enemy_win_startx);
	sidebar = newwin(SIDEBAR_HEIGHT,SIDEBAR_WIDTH,sidebar_starty,sidebar_startx); /* y = statwin + mainwin, x = 120 - mainwin */

	while (COLS <= (STAT_WIDTH + CHOICE_WIDTH + SIDEBAR_WIDTH)\
            || LINES <= (STAT_HEIGHT + MAIN_HEIGHT)) {
        mvprintw(0,0,"Window is not big enough! (Needs %dx%d)",STAT_HEIGHT + MAIN_HEIGHT,\
                  STAT_WIDTH + CHOICE_WIDTH + SIDEBAR_WIDTH);
        mvprintw(1,0,"Current HeightxWidth: %dx%d",LINES,COLS);
        refresh();
        p.name[0] = getch(); /* Resizing the window creates input(?) */
    }

    p.name[0] = ' '; /* gets rid of above input */

	keypad(choice_win,TRUE);
	keypad(sidebar,TRUE);

	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_CYAN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	init_pair(5,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(6,COLOR_WHITE,COLOR_BLACK);
	init_pair(7,COLOR_BLUE,COLOR_BLACK);

	wattron(stat_win,COLOR_PAIR(2));
	wattron(choice_win,COLOR_PAIR(4));
	wattron(enemy_win,COLOR_PAIR(6));
	wattron(sidebar,COLOR_PAIR(3));

    load_game(); /* Always load the save game. */

    #ifdef DEBUG
        /* Give super healing item so tester can live more easily. */
        inv[9].id = 1;
        inv[9].str = 1337;
        inv[9].mod = 9001;
        inv[9].amount = 777;
        inv[9].type = 1;
        inv[9].effect = EFF_HEALHP;

        /* Allow test to give xp at command line:
         * ./The_Game [xp]
         */
        if (argc > 1) {
            if (argv[1] != NULL) {
                p.xp = atof(argv[1]);
            }
        }
    #endif

    clear();

    if (p_creation == 0) {
        mvprintw(1,1,  "    ##### #   # #####        ####   ###  #   # #####"    );
        mvprintw(2,1,  "      #   #   # #           #      #   # ## ## #      #" );
        mvprintw(3,1,  "      #   ##### #####       #  ##  ##### # # # #####"    );
        mvprintw(4,1,  "      #   #   # #           #    # #   # #   # #      #" );
        mvprintw(5,1,  "      #   #   # ##### #####  ####  #   # #   # #####"    );
        mvprintw(6,1,  "                 A Game For Munchkins!"                  );
        mvprintw(7,1,  ""                                                        );
        mvprintw(8,1,  "" );
        mvprintw(9,1,  ",.;:=-''-=:;.,,.;:=-''-=:;.,,.;:=-''-=:;.,,.;:=-''-=:;.");

        a = roll_die(13);
        mvprintw(10,1,"Random tip: ");
        if (a == 1) printw("Don't believe what The_Game tells you. It's all lies.");
        else if (a == 2) printw("If you hate grinding, you'll LOVE The_Game.");
        else if (a == 3) printw("Wielding two weapons at once is for losers.");
        else if (a == 4) printw("If you think leveling is easy, you are not Lv 1000 yet.");
        else if (a == 5) printw("Have you maxed any stats today?");
        else if (a == 6) printw("The Average adjectival is the only one with base stats!");
        else if (a == 7) printw("Trying to cast a spell when you don't have the MP wastes a turn.");
        else if (a == 8) printw("Always keep an inventory slot free for loot.");
        else if (a == 9) printw("You can only delete entire item stacks at a time.");
        else if (a == 10) printw("The XP you earn is adjusted; fighting higher level enemies grants a bonus.");
        else if (a == 11) printw("Who has a name longer than 21 letters?");
        else if (a == 12) printw("An item's adjectival is determined by the level difference between fighters.");
        else if (a == 13) printw("Draconian draconian is draconian.");

        mvprintw(11,1,"Enter a name (Max 21 letters):");

        mvprintw(14,1,"Copyright © 2014 William McFadden, under the WTFPL; see COPYING for more info.");

        move(12,1);
        refresh();

        i = 0;

        while (p_creation == 0 && i < 21) {
            for (ii = 0;ii < 21;++ii) {
                mvprintw(12,ii,"%c",p.name[ii]);
            }
            move(12,i);
            refresh();
            ch = getch();
            /* resizing terminal win prints gibberish; this should fix. */
            if (ch < 0x00 || ch > 0x14D) ch = 0x00;
            switch (ch) {
                case 0x00:
                    break;
                case 0x0A: /* Enter */
                    if (i != 0) p_creation = 1;
                    break;
                case 0x08: /* ASCII Backspace */
                case 0x7F: /* ASCII Delete */
                case 0x0107: /* BS/DEL */
                case 0x014D: /* BS/DEL */
                    if (i >= 0) {
                        p.name[i - 1] = ' ';
                        if (i > 0) --i;
                    }
                    break;
                default:
                    p.name[i] = ch;
                    ++i;
                    if (i == 21) p_creation = 1;
                    break;
            }
        }
    }

    a = 0;
    clear();

    /* Define the species */

    species[SPECIES_DRACONIAN][0] = SPECIES_DRACONIAN; /* Draconian */
    species[SPECIES_DRACONIAN][1] = 150; /* HP */
    species[SPECIES_DRACONIAN][2] = 10; /* MP */
    species[SPECIES_DRACONIAN][3] = 18; /* STR */
    species[SPECIES_DRACONIAN][4] = 17; /* TOU */
    species[SPECIES_DRACONIAN][5] = 5; /* MAG */
    species[SPECIES_DRACONIAN][6] = 550; /* WAI */
    species[SPECIES_DRACONIAN][7] = 2.00; /* DAM */

    species[SPECIES_KOBOLD][0] = SPECIES_KOBOLD; /* Kobold */
    species[SPECIES_KOBOLD][1] = 60; /* HP */
    species[SPECIES_KOBOLD][2] = 45; /* MP */
    species[SPECIES_KOBOLD][3] = 12; /* STR */
    species[SPECIES_KOBOLD][4] = 11; /* TOU */
    species[SPECIES_KOBOLD][5] = 17; /* MAG */
    species[SPECIES_KOBOLD][6] = 425; /* WAI */
    species[SPECIES_KOBOLD][7] = 0.50; /* DAM */

    species[SPECIES_HUMAN][0] = SPECIES_HUMAN; /* Human */
    species[SPECIES_HUMAN][1] = 100; /* HP */
    species[SPECIES_HUMAN][2] = 30; /* MP */
    species[SPECIES_HUMAN][3] = 15; /* STR */
    species[SPECIES_HUMAN][4] = 15; /* TOU */
    species[SPECIES_HUMAN][5] = 15; /* MAG */
    species[SPECIES_HUMAN][6] = 500; /* WAI */
    species[SPECIES_HUMAN][7] = 0.00; /* DAM */

    species[SPECIES_MINOTAUR][0] = SPECIES_MINOTAUR; /* Minotaur */
    species[SPECIES_MINOTAUR][1] = 130; /* HP */
    species[SPECIES_MINOTAUR][2] = 20; /* MP */
    species[SPECIES_MINOTAUR][3] = 17; /* STR */
    species[SPECIES_MINOTAUR][4] = 17; /* TOU */
    species[SPECIES_MINOTAUR][5] = 9; /* MAG */
    species[SPECIES_MINOTAUR][6] = 525; /* WAI */
    species[SPECIES_MINOTAUR][7] = 1.20; /* DAM */

    species[SPECIES_GOLEM][0] = SPECIES_GOLEM; /* Golem */
    species[SPECIES_GOLEM][1] = 220; /* HP */
    species[SPECIES_GOLEM][2] = 5; /* MP */
    species[SPECIES_GOLEM][3] = 20; /* STR */
    species[SPECIES_GOLEM][4] = 24; /* TOU */
    species[SPECIES_GOLEM][5] = 1; /* MAG */
    species[SPECIES_GOLEM][6] = 650; /* WAI */
    species[SPECIES_GOLEM][7] = 1.50; /* DAM */

    species[SPECIES_FAIRY][0] = SPECIES_FAIRY; /* Fairy */
    species[SPECIES_FAIRY][1] = 20; /* HP */
    species[SPECIES_FAIRY][2] = 70; /* MP */
    species[SPECIES_FAIRY][3] = 1; /* STR */
    species[SPECIES_FAIRY][4] = 1; /* TOU */
    species[SPECIES_FAIRY][5] = 35; /* MAG */
    species[SPECIES_FAIRY][6] = 250; /* WAI */
    species[SPECIES_FAIRY][7] = 0.00; /* DAM */

    while (p_creation == 1) {
        for (i = 1;i <= 40;++i) {
            mvprintw(i,0,"                                                                                ");
        }

        mvprintw(1,1,"Choose a species:");
        mvprintw(SPECIES_DRACONIAN + 2,4,"Draconian");
        mvprintw(SPECIES_KOBOLD + 2,4,"Kobold");
        mvprintw(SPECIES_HUMAN + 2,4,"Human");
        mvprintw(SPECIES_MINOTAUR + 2,4,"Minotaur");
        mvprintw(SPECIES_GOLEM + 2,4,"Golem");
        mvprintw(SPECIES_FAIRY + 2,4,"Fairy");

        mvprintw(9,20,"Starting value (compared to human)");

        if (species[a][1] - species[SPECIES_HUMAN][1] > 0) attron(COLOR_PAIR(3));
        else if (species[a][1] - species[SPECIES_HUMAN][1] == 0) attron(COLOR_PAIR(6));
        else attron(COLOR_PAIR(1));
        mvprintw(10,20,"HP    : %.0f (%+.0f)",species[a][1],species[a][1] - species[SPECIES_HUMAN][1]);

        if (species[a][2] - species[SPECIES_HUMAN][2] > 0) attron(COLOR_PAIR(3));
        else if (species[a][2] - species[SPECIES_HUMAN][2] == 0) attron(COLOR_PAIR(6));
        else attron(COLOR_PAIR(1));
        mvprintw(11,20,"MP    : %.0f (%+.0f)",species[a][2],species[a][2] - species[SPECIES_HUMAN][2]);

        if (species[a][3]-species[SPECIES_HUMAN][3] > 0) attron(COLOR_PAIR(3));
        else if (species[a][3] - species[SPECIES_HUMAN][3] == 0) attron(COLOR_PAIR(6));
        else attron(COLOR_PAIR(1));
        mvprintw(12,20,"STR   : %.0f (%+.0f)",species[a][3],species[a][3] - species[SPECIES_HUMAN][3]);

        if (species[a][4] - species[SPECIES_HUMAN][4] > 0) attron(COLOR_PAIR(3));
        else if (species[a][4] - species[SPECIES_HUMAN][4] == 0) attron(COLOR_PAIR(6));
        else attron(COLOR_PAIR(1));
        mvprintw(13,20,"TOU   : %.0f (%+.0f)",species[a][4],species[a][4] - species[SPECIES_HUMAN][4]);

        if (species[a][5] - species[SPECIES_HUMAN][5] > 0) attron(COLOR_PAIR(3));
        else if (species[a][5] - species[SPECIES_HUMAN][5] == 0) attron(COLOR_PAIR(6));
        else attron(COLOR_PAIR(1));
        mvprintw(14,20,"MAG   : %.0f (%+.0f)",species[a][5],species[a][5] - species[SPECIES_HUMAN][5]);

        if (species[a][6] - species[SPECIES_HUMAN][6] < 0) attron(COLOR_PAIR(3));
        else if (species[a][6] - species[SPECIES_HUMAN][6] == 0) attron(COLOR_PAIR(6));
        else attron(COLOR_PAIR(1));
        mvprintw(15,20,"Wait  : %.0f (%+.0f)",species[a][6],species[a][6] - species[SPECIES_HUMAN][6]);

        if (species[a][7] - species[SPECIES_HUMAN][7] > 0) attron(COLOR_PAIR(3));
        else if (species[a][7] - species[SPECIES_HUMAN][7] == 0) attron(COLOR_PAIR(6));
        else attron(COLOR_PAIR(1));
        mvprintw(16,20,"Damage: %.0f (%+.0f)",species[a][7],species[a][7] - species[SPECIES_HUMAN][7]);

        attron(COLOR_PAIR(6));
        mvprintw(a + 2,1,"->");

        if (a == species[SPECIES_DRACONIAN][0]) {
            mvprintw(1,20,"Draconians use their big size to  ");
            mvprintw(2,20,"pommel things into submission.    ");
            mvprintw(3,20,"Thus, they tend to forego any     ");
            mvprintw(4,20,"magic use.                        ");
            mvprintw(5,20,"                                  ");
        }
        else if (a == species[SPECIES_KOBOLD][0]) {
            mvprintw(1,20,"Kobolds are rather small, so their");
            mvprintw(2,20,"ability to cause physical damage  ");
            mvprintw(3,20,"suffers. They do have decent      ");
            mvprintw(4,20,"control of magic, so they can     ");
            mvprintw(5,20,"still wreck some havoc that way.  ");
            mvprintw(6,20,"They are also pretty quick.       ");
        }
        else if (a == species[SPECIES_HUMAN][0]) {
            mvprintw(1,20,"Humans are good at adapting to    ");
            mvprintw(2,20,"whatever the current challenge    ");
            mvprintw(3,20,"requires, but have no statistical ");
            mvprintw(4,20,"advantage or disadvantage. From   ");
            mvprintw(5,20,"fighter to Mage, and everything   ");
            mvprintw(6,20,"inbetween.                        ");
        }
        else if (a == species[SPECIES_MINOTAUR][0]) {
            mvprintw(1,20,"No                                ");
            mvprintw(2,20,"description                       ");
            mvprintw(3,20,"yet!                              ");
            mvprintw(4,20,"                                  ");
            mvprintw(5,20,"                                  ");
            mvprintw(6,20,"                                  ");
        }
        else if (a == species[SPECIES_FAIRY][0]) {
            mvprintw(1,20,"No                                ");
            mvprintw(2,20,"description                       ");
            mvprintw(3,20,"yet!                              ");
            mvprintw(4,20,"                                  ");
            mvprintw(5,20,"                                  ");
            mvprintw(6,20,"                                  ");
        }
        else if (a == species[SPECIES_GOLEM][0]) {
            mvprintw(1,20,"No                                ");
            mvprintw(2,20,"description                       ");
            mvprintw(3,20,"yet!                              ");
            mvprintw(4,20,"                                  ");
            mvprintw(5,20,"                                  ");
            mvprintw(6,20,"                                  ");
        }

        ch = getch();
        switch (ch) {
            case KEY_DOWN:
                if (a < 5) ++a;
                else a=0;
                break;
            case KEY_UP:
                if (a == 0) a = 5;
                else --a;
                break;
            case 0x0A: /* Enter */
                p_creation = 2;
                break;
            default:
                break;
        };
        attron(COLOR_PAIR(6));
        if (p_creation == 2) {
            p.hp = species[a][1];
            p.maxhp = species[a][1];
            p.mp = species[a][2];
            p.maxmp = species[a][2];
            p.str = species[a][3];
            p.tou = species[a][4];
            p.mag = species[a][5];
            p.max_wait = species[a][6];
            p.bonus_damage = species[a][7];
            p.species = a;
        }
    }

    a = 0;

    /* Define the classes */

    classes[CLASS_FIGHTER][0] = CLASS_FIGHTER; /* Fighter */
    classes[CLASS_FIGHTER][1] = 50; /* HP */
    classes[CLASS_FIGHTER][2] = 20; /* MP */
    classes[CLASS_FIGHTER][3] = 20; /* STR */
    classes[CLASS_FIGHTER][4] = 20; /* TOU */
    classes[CLASS_FIGHTER][5] = 10; /* MAG */
    classes[CLASS_FIGHTER][6] = 50; /* WAI */
    classes[CLASS_FIGHTER][7] = 3; /* DAM */

    classes[CLASS_MAGE][0] = CLASS_MAGE; /* Mage */
    classes[CLASS_MAGE][1] = 20; /* HP */
    classes[CLASS_MAGE][2] = 50; /* MP */
    classes[CLASS_MAGE][3] = 10; /* STR */
    classes[CLASS_MAGE][4] = 10; /* TOU */
    classes[CLASS_MAGE][5] = 30; /* MAG */
    classes[CLASS_MAGE][6] = 30; /* WAI */
    classes[CLASS_MAGE][7] = 1; /* DAM */

    classes[CLASS_THIEF][0] = CLASS_THIEF; /* Thief */
    classes[CLASS_THIEF][1] = 30; /* HP */
    classes[CLASS_THIEF][2] = 25; /* MP */
    classes[CLASS_THIEF][3] = 25; /* STR */
    classes[CLASS_THIEF][4] = 15; /* TOU */
    classes[CLASS_THIEF][5] = 20; /* MAG */
    classes[CLASS_THIEF][6] = 10; /* WAI */
    classes[CLASS_THIEF][7] = 2; /* DAM */

    while (p_creation == 2) {
        for (i = 1;i <= 40;++i) {
            mvprintw(i,0,"                                                                                ");
        }

        attron(COLOR_PAIR(6));
        mvprintw(1,1,"Choose a class:");
        mvprintw(2,4,"Fighter");
        mvprintw(3,4,"Mage");
        mvprintw(4,4,"Thief");

        mvprintw(a + 2,1,"->");

        mvprintw(9,20,"Chance to increase per level:");
        mvprintw(10,20,"HP    : %.0f%%",classes[a][1]);
        mvprintw(11,20,"MP    : %.0f%%",classes[a][2]);
        mvprintw(12,20,"STR   : %.0f%%",classes[a][3]);
        mvprintw(13,20,"TOU   : %.0f%%",classes[a][4]);
        mvprintw(14,20,"MAG   : %.0f%%",classes[a][5]);
        mvprintw(15,20,"Wait  : %.0f%%",classes[a][6]);
        mvprintw(16,20,"Damage: %.0f%%",classes[a][7]);

        if (a == classes[CLASS_FIGHTER][0]) {
            mvprintw(1,20,"No                                ");
            mvprintw(2,20,"description                       ");
            mvprintw(3,20,"yet!                              ");
            mvprintw(4,20,"                                  ");
            mvprintw(5,20,"                                  ");
        }
        else if (a == classes[CLASS_MAGE][0]) {
            mvprintw(1,20,"No                                ");
            mvprintw(2,20,"description                       ");
            mvprintw(3,20,"yet!                              ");
            mvprintw(4,20,"                                  ");
            mvprintw(5,20,"                                  ");
        }
        else if (a == classes[CLASS_THIEF][0]) {
            mvprintw(1,20,"No                                ");
            mvprintw(2,20,"description                       ");
            mvprintw(3,20,"yet!                              ");
            mvprintw(4,20,"                                  ");
            mvprintw(5,20,"                                  ");
        }

        ch = getch();
        switch (ch) {
            case KEY_DOWN:
                if (a < 2) ++a;
                else a = 0;
                break;
            case KEY_UP:
                if (a == 0) a = 2;
                else --a;
                break;
            case 0x0A: /* Enter */
                p_creation = 3;
                break;
            default:
                break;
        };
        if (p_creation == 3) {
            p.pclass = classes[a][0];
        }
    }

    if (p.hp < 1) p.hp = 1;
    if (p.maxhp < 1) p.maxhp = 1;
    if (p.mp < 1) p.mp = 1;
    if (p.maxmp < 1) p.maxmp = 1;
    if (p.str < 1) p.str = 1;
    if (p.tou < 1) p.tou = 1;
    if (p.mag < 1) p.mag = 1;
    if (p.max_wait < 100) p.max_wait = 100;

    curs_set(0);

	while (endgame != 1) {
        if (p.wait == 0 && p.status_id != STUN_ID) { /* if player is stunned, they lose their turn */
            draw_stat_win(stat_win);
            draw_enemy_win(enemy_win);

            wclear(sidebar);
            wattron(sidebar,COLOR_PAIR(3));
            mvwprintw(sidebar,1,1,"%s",VERSION);

            mvwprintw(sidebar,3,1,"Turn: %.0f (%03d Wait left)",turn,500 - global_wait);

            if (turns_since_load > 0) {
                mvwprintw(sidebar,5,1,"---Turn %.0f Summary---",turn - 1);

                wattron(sidebar,p_msg_one_color);
                mvwprintw(sidebar,7,1,"%s",p_msg_one);
                wattron(sidebar,COLOR_PAIR(3));

                wattron(sidebar,e_msg_one_color);
                mvwprintw(sidebar,8,1,"%s",e_msg_one);
                wattron(sidebar,COLOR_PAIR(3));

                wattron(sidebar,COLOR_PAIR(1));
                mvwprintw(sidebar,9,1,"%s",e_kill_msg_one);
                wattron(sidebar,COLOR_PAIR(3));
            }
            if (turns_since_load > 1) {
                mvwprintw(sidebar,11,1,"---Turn %.0f Summary---",turn - 2);

                wattron(sidebar,p_msg_two_color);
                mvwprintw(sidebar,13,1,"%s",p_msg_two);
                wattron(sidebar,COLOR_PAIR(3));

                wattron(sidebar,e_msg_two_color);
                mvwprintw(sidebar,14,1,"%s",e_msg_two);
                wattron(sidebar,COLOR_PAIR(3));

                wattron(sidebar,COLOR_PAIR(1));
                mvwprintw(sidebar,15,1,"%s",e_kill_msg_two);
                wattron(sidebar,COLOR_PAIR(3));
            }
            if (turns_since_load > 2) {
                mvwprintw(sidebar,17,1,"---Turn %.0f Summary---",turn - 3);

                wattron(sidebar,p_msg_three_color);
                mvwprintw(sidebar,19,1,"%s",p_msg_three);
                wattron(sidebar,COLOR_PAIR(3));

                wattron(sidebar,e_msg_three_color);
                mvwprintw(sidebar,20,1,"%s",e_msg_three);
                wattron(sidebar,COLOR_PAIR(3));

                wattron(sidebar,COLOR_PAIR(1));
                mvwprintw(sidebar,21,1,"%s",e_kill_msg_three);
                wattron(sidebar,COLOR_PAIR(3));
            }

            wattron(sidebar,COLOR_PAIR(3));

            for (i = 0;i <= 39;++i) {
                mvwprintw(choice_win,i,1,"               ");
            }

            attron(COLOR_PAIR(4)); // ?

            box(sidebar,0,0);
            mvwprintw(sidebar,0,2,"Sidebar");
            wrefresh(sidebar);

            box(choice_win,0,0);
            mvwprintw(choice_win,0,2,"Action");
            print_menu(choice_win,highlight,1,1);
            wrefresh(choice_win);

            ch = wgetch(choice_win);
            switch (ch) {
                case KEY_DOWN:
                    if (highlight < MAX_CHOICES) highlight = highlight + 1;
                    else highlight = 1;
                    break;
                case KEY_UP:
                    if (highlight > 1) highlight = highlight - 1;
                    else highlight = MAX_CHOICES;
                    break;
                case 0x0A: /* Enter */
                    choice = highlight;
                    break;
                case 0x71: /* q */
                    endgame = 1;
                    break;
                default:
                    break;
            };
        }

        switch (choice) {
            case 1: /* Attack */
                if (p.hp > 0) {
                    attack_formula(2);
                }
                break;
            case 2: /* Magic */
                schoice = magic_main(sidebar);
                break;
            case 3: /* Item */
                schoice = item_main(sidebar);
                break;
            case 4: /* Craft */
                schoice = craft_main(sidebar);
                break;
            case 5: /* Stats */
                pg = 1;

                while (schoice == 0) {
                    wclear(sidebar);
                   // draw_stat_win(stat_win);
                   // draw_enemy_win(enemy_win);
                    mvwprintw(sidebar,1,1,"Press c to go back, up/down changes page,\n # to unequip.");

                    if (pg == 1) {
                        mvwprintw(sidebar,3,1,"Enemies killed..% 12.0f",stat_kills);
                        mvwprintw(sidebar,4,1,"Spells cast.....% 12.0f",stat_m_casts);
                        mvwprintw(sidebar,5,1,"Items used......% 12.0f",stat_i_used);
                        mvwprintw(sidebar,6,1,"Damage given....% 12.0f",stat_p_dam_dealt);
                        mvwprintw(sidebar,7,1,"Damage recieved.% 12.0f",stat_p_dam_taken);
                    }
                    else if (pg == 2) {
                        if (p.species == species[SPECIES_DRACONIAN][0]) mvwprintw(sidebar,3,1,"Lv, Species, Class: Lv.%.0f Draconian ",p.lv);
                        else if (p.species == species[SPECIES_KOBOLD][0]) mvwprintw(sidebar,3,1,"Lv, Species, Class: Lv.%.0f Kobold ",p.lv);
                        else if (p.species == species[SPECIES_HUMAN][0]) mvwprintw(sidebar,3,1,"Lv, Species, Class: Lv.%.0f Human ",p.lv);
                        else if (p.species == species[SPECIES_MINOTAUR][0]) mvwprintw(sidebar,3,1,"Lv, Species, Class: Lv.%.0f Minotaur ",p.lv);
                        else if (p.species == species[SPECIES_GOLEM][0]) mvwprintw(sidebar,3,1,"Lv, Species, Class: Lv.%.0f Golem ",p.lv);
                        else if (p.species == species[SPECIES_FAIRY][0]) mvwprintw(sidebar,3,1,"Lv, Species, Class: Lv.%.0f Fairy ",p.lv);
                        else mvwprintw(sidebar,3,1,"Lv, Species, Class: Lv.%.0f Unused id:%d ",p.lv,p.species);

                        if (p.pclass == classes[CLASS_FIGHTER][0]) wprintw(sidebar,"Fighter");
                        else if (p.pclass == classes[CLASS_MAGE][0]) wprintw(sidebar,"Mage");
                        else if (p.pclass == classes[CLASS_THIEF][0]) wprintw(sidebar,"Thief");

                        mvwprintw(sidebar,5,1,"HP Regen: %.0f every %.0f turns",p.hp_regen_amount,p.hp_regen_time);
                        mvwprintw(sidebar,6,1,"MP Regen: %.0f every %.0f turns",p.mp_regen_amount,p.mp_regen_time);
                    }
                    else if (pg == 3) {
                        a = 3; /* starting y-coord of equip list */

                        if (p.equip_id > 0 && p.equip_id <= item_max) {
                            sprintf(p_buffer,"%s",item_db[p.equip_id].iname);
                        }
                        else if (p.equip_id == 0) {
                            strcpy(p_buffer,"Unarmed");
                        }
                        else {
                            sprintf(p_buffer,"Unused id:%d",p.equip_id);
                        }

                        if (p.equip_id != 0) {
                            mvwprintw(sidebar,a++,1,"1. Weapon: %s%+.0f; ",p_buffer,p.equip_mod);
                            mvwprintw(sidebar,a++,3,"Condition: [");
                            draw_con_bar(sidebar,p.equip_con,p.equip_maxcon);
                        }
                        else mvwprintw(sidebar,a++,1,"1. Weapon: %s",p_buffer);

                        z = 0;
                        if (p.head_id > 0 && p.head_id <= item_max) {
                            sprintf(p_buffer,"%s",item_db[p.head_id].iname);
                            z = item_db[p.head_id].ap;
                        }
                        else if (p.head_id == 0) {
                            strcpy(p_buffer,"Nothing");
                        }
                        else {
                            sprintf(p_buffer,"Unused ID: %d",p.head_id);
                        }

                        if (z != 0.0) {
                            mvwprintw(sidebar,a++,1,"2. Head  : %s%+.0f; AP: %+.0f; Wait: %+.0f",p_buffer,p.head_ap - z,p.head_ap,p.head_wait);
                            mvwprintw(sidebar,a++,3,"Condition: [");
                            draw_con_bar(sidebar,p.head_con,p.head_maxcon);
                        }
                        else mvwprintw(sidebar,a++,1,"2. Head  : %s; AP: +0; Wait: +0",p_buffer);

                        z = 0;
                        if (p.body_id > 0 && p.body_id <= item_max) {
                            sprintf(p_buffer,"%s",item_db[p.body_id].iname);
                            z = item_db[p.body_id].ap;
                        }
                        else if (p.body_id == 0) {
                            strcpy(p_buffer,"Nothing");
                        }
                        else {
                            sprintf(p_buffer,"Unused ID: %d",p.body_id);
                        }

                        if (z != 0.0) {
                            mvwprintw(sidebar,a++,1,"3. Body  : %s%+.0f; AP: %+.0f; Wait: %+.0f",p_buffer,p.body_ap - z,p.body_ap,p.body_wait);
                            mvwprintw(sidebar,a++,3,"Condition: [");
                            draw_con_bar(sidebar,p.body_con,p.body_maxcon);
                        }
                        else mvwprintw(sidebar,a++,1,"3. Body  : %s; AP: +0; Wait: +0",p_buffer);

                        z = 0;
                        if (p.legs_id > 0 && p.legs_id <= item_max) {
                            sprintf(p_buffer,"%s",item_db[p.legs_id].iname);
                            z = item_db[p.legs_id].ap;
                        }
                        else if (p.legs_id == 0) {
                            strcpy(p_buffer,"Nothing");
                        }
                        else {
                            sprintf(p_buffer,"Unused ID: %d",p.legs_id);
                        }

                        if (z != 0.0) {
                            mvwprintw(sidebar,a++,1,"4. Legs  : %s%+.0f; AP: %+.0f; Wait: %+.0f",p_buffer,p.legs_ap - z,p.legs_ap,p.legs_wait);
                            mvwprintw(sidebar,a++,3,"Condition: [");
                            draw_con_bar(sidebar,p.legs_con,p.legs_maxcon);
                        }
                        else mvwprintw(sidebar,a++,1,"4. Legs  : %s; AP: +0; Wait: +0",p_buffer);

                        z = 0;
                        if (p.feet_id > 0 && p.feet_id <= item_max) {
                            sprintf(p_buffer,"%s",item_db[p.feet_id].iname);
                            z = item_db[p.feet_id].ap;
                        }
                        else if (p.feet_id == 0) {
                            strcpy(p_buffer,"Nothing");
                        }
                        else {
                            sprintf(p_buffer,"Unused ID: %d",p.feet_id);
                        }

                        if (z != 0.0) {
                            mvwprintw(sidebar,a++,1,"5. Feet  : %s%+.0f; AP: %+.0f; Wait: %+.0f",p_buffer,p.feet_ap - z,p.feet_ap,p.feet_wait);
                            mvwprintw(sidebar,a++,3,"Condition: [");
                            draw_con_bar(sidebar,p.feet_con,p.feet_maxcon);
                        }
                        else mvwprintw(sidebar,a++,1,"5. Feet  : %s; AP: +0; Wait: +0",p_buffer);

                        z = 0;
                        if (p.hands_id > 0 && p.hands_id <= item_max) {
                            sprintf(p_buffer,"%s",item_db[p.hands_id].iname);
                            z = item_db[p.hands_id].ap;
                        }
                        else if (p.hands_id == 0) {
                            strcpy(p_buffer,"Nothing");
                        }
                        else {
                            sprintf(p_buffer,"Unused ID: %d",p.hands_id);
                        }

                        if (z != 0.0) {
                            mvwprintw(sidebar,a++,1,"6. Hands : %s%+.0f; AP: %+.0f; Wait: %+.0f",p_buffer,p.hands_ap - z,p.hands_ap,p.hands_wait);
                            mvwprintw(sidebar,a++,3,"Condition: [");
                            draw_con_bar(sidebar,p.hands_con,p.hands_maxcon);
                        }
                        else mvwprintw(sidebar,a++,1,"6. Hands : %s; AP: +0; Wait: +0",p_buffer);

                        a++; /* blank line; hopefully makes it look less clutered */
                        mvwprintw(sidebar,a++,1,"Base Damage: %.0f%+.2f",p.str + p.equip_atk,p.bonus_damage + p.equip_mod);
                        mvwprintw(sidebar,a++,1,"Approx. Damage: %.0f - %.0f",\
                                   max(1,(((p.str + p.equip_atk) - round(e.tou / 2)) + p.bonus_damage) * .8),\
                                   max(1,(((p.str + p.equip_atk) - round(e.tou / 2)) + p.bonus_damage) * 1.2));
                        a++; /* another blank line */
                        mvwprintw(sidebar,a++,1,"Total AP : %+.0f; Total Wait: %+.0f",p.head_ap + p.body_ap + p.legs_ap +\
                                p.feet_ap + p.hands_ap + p.equip_ap,p.head_wait + p.body_wait + p.feet_wait + p.legs_wait + p.hands_wait + p.equip_wait);

                        /** @note
                         * Check how much space the sidebar has when player
                         * is wearing a full set of equipment.
                         * There should be plenty...
                         */
                    }
                    else if (pg == 4) {
                        a = 3;
                        wattron(sidebar,A_BOLD);
                        mvwprintw(sidebar,a++,1,"Skills:");
                        wattroff(sidebar,A_BOLD);

                        wattron(sidebar,COLOR_PAIR(1));
                        mvwprintw(sidebar,a++,3,"1. Fighting: Lv. % 9d\n     [",skill[SKILL_FIGHTING][0]);
                        draw_sk_bar(sidebar,skill[SKILL_FIGHTING][1],skill[SKILL_FIGHTING][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(6));
                        mvwprintw(sidebar,a++,3,"2. Crafting: Lv. % 9d\n     [",skill[SKILL_CRAFTING_GEN][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CRAFTING_GEN][1],skill[SKILL_CRAFTING_GEN][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(6));
                        mvwprintw(sidebar,a++,3," a. Healing: Lv. % 9d\n     [",skill[SKILL_CRAFTING_HEA][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CRAFTING_HEA][1],skill[SKILL_CRAFTING_HEA][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(1));
                        mvwprintw(sidebar,a++,3," b.  Attack: Lv. % 9d\n     [",skill[SKILL_CRAFTING_ATT][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CRAFTING_ATT][1],skill[SKILL_CRAFTING_ATT][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(4));
                        mvwprintw(sidebar,a++,3," c.  Wep&Ar: Lv. % 9d\n     [",skill[SKILL_CRAFTING_WAA][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CRAFTING_WAA][1],skill[SKILL_CRAFTING_WAA][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(6));
                        mvwprintw(sidebar,a++,3," d.   Other: Lv. % 9d\n     [",skill[SKILL_CRAFTING_OTH][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CRAFTING_OTH][1],skill[SKILL_CRAFTING_OTH][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(2));
                        mvwprintw(sidebar,a++,3,"3.  Casting: Lv. % 9d\n     [",skill[SKILL_CASTING_GEN][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CASTING_GEN][1],skill[SKILL_CASTING_GEN][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(6));
                        mvwprintw(sidebar,a++,3," a. Healing: Lv. % 9d\n     [",skill[SKILL_CASTING_HEA][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CASTING_HEA][1],skill[SKILL_CASTING_HEA][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(1));
                        mvwprintw(sidebar,a++,3," b.  Attack: Lv. % 9d\n     [",skill[SKILL_CASTING_ATT][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CASTING_ATT][1],skill[SKILL_CASTING_ATT][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(4));
                        mvwprintw(sidebar,a++,3," c.  Status: Lv. % 9d\n     [",skill[SKILL_CASTING_STA][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CASTING_STA][1],skill[SKILL_CASTING_STA][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(1));
                        mvwprintw(sidebar,a++,3," d.    Fire: Lv. % 9d\n     [",skill[SKILL_CASTING_FIR][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CASTING_FIR][1],skill[SKILL_CASTING_FIR][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(7));
                        mvwprintw(sidebar,a++,3," e.   Water: Lv. % 9d\n     [",skill[SKILL_CASTING_WAT][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CASTING_WAT][1],skill[SKILL_CASTING_WAT][2]);
                        a++;

                        wattron(sidebar,COLOR_PAIR(3));
                        mvwprintw(sidebar,a++,3," f.   Earth: Lv. % 9d\n     [",skill[SKILL_CASTING_EAR][0]);
                        draw_sk_bar(sidebar,skill[SKILL_CASTING_EAR][1],skill[SKILL_CASTING_EAR][2]);
                        a++;
                    }

                    wattron(sidebar,COLOR_PAIR(3));
                    box(sidebar,0,0);
                    wrefresh(sidebar);
                    ch = wgetch(sidebar);
                    switch (ch) {
                        case KEY_UP:
                            if (pg > 1) --pg;
                            else pg = 4;
                            break;
                        case KEY_DOWN:
                            if (pg < 4) ++pg;
                            else pg = 1;
                            break;
                        case 0x63: /* c */
                            schoice = -1;
                            break;
                        case 0x31: /* 1 */
                            schoice = 1;
                            unequip_item(1);
                            break;
                        case 0x32: /* 2 */
                            schoice = 2;
                            unequip_item(2);
                            break;
                        case 0x33: /* 3 */
                            schoice = 3;
                            unequip_item(3);
                            break;
                        case 0x34: /* 4 */
                            schoice = 4;
                            unequip_item(4);
                            break;
                        case 0x35: /* 5 */
                            schoice = 5;
                            unequip_item(5);
                            break;
                        case 0x36: /* 6 */
                            schoice = 6;
                            unequip_item(6);
                            break;
                        default:
                            break;
                    };
                }
                break;
            case MAX_CHOICES: /* Save & Quit */
                endgame = 1;
                break;
            default:
                break;
        };

        enemy_turn();

        if (p.wait == 0 && choice != 0 && schoice != -1 && choice != MAX_CHOICES) {
            v = 0.0;
            v = p.max_wait + p.equip_wait;
            v = v + p.head_wait + p.body_wait + p.legs_wait + p.feet_wait + p.hands_wait;
            if (p.status_id == HASTE_ID) v = v - p.status_str;
            p.wait = v;
        }

		if (e.hp <= 0) {
		    e_killed = 1;
			kill_enemy();

			while (p.xp >= p.next_xp) {
			    schoice = 0;
                ++p.lv;
                p.xp = p.xp - p.next_xp;
                if (p.lv < STAT_MAX) {
                        /*
                        increase next xp
                        subtract cur xp
                        roll die for HP, see if < class chance
                        repeat for each class stat.
                        display stats that increased.
                        eventually, classes will have multiple roll chances.
                        */
                    a = 0;
                    b = 0;
                    c = 0;
                    d = 0;
                    i = 0;
                    f = 0;
                    g = 0;

                    p.next_xp = ceil(p.next_xp * 1.10); /* 10% more xp needed, rounded up. */
                    if (p.next_xp > STAT_MAX) p.next_xp = STAT_MAX;

                    if (roll_die(100) <= classes[p.pclass][1]) {
                        if (p.maxhp < STAT_MAX) {
                            ++p.maxhp;
                            ++p.hp;
                        }
                        ++a;
                    }

                    if (roll_die(100) <= classes[p.pclass][2]) {
                        if (p.maxmp < STAT_MAX) {
                            ++p.maxmp;
                            ++p.mp;
                        }
                        ++b;
                    }

                    if (roll_die(100) <= classes[p.pclass][3]) {
                        if (p.str < STAT_MAX) ++p.str;
                        ++c;
                    }

                    if (roll_die(100) <= classes[p.pclass][4]) {
                        if (p.tou < STAT_MAX) ++p.tou;
                        ++d;
                    }

                    if (roll_die(100) <= classes[p.pclass][5]) {
                        if (p.mag < STAT_MAX) ++p.mag;
                        ++i;
                    }

                    if (roll_die(100) <= classes[p.pclass][6]) {
                        if (p.max_wait < 9999) ++p.max_wait;
                        ++f;
                    }

                    if (roll_die(100) <= classes[p.pclass][7]) {
                        if (p.bonus_damage < STAT_MAX) ++p.bonus_damage;
                        ++g;
                    }

                    wclear(sidebar);
                    draw_stat_win(stat_win);
                    draw_enemy_win(enemy_win);

                    wmove(sidebar,1,1);
                    wprintw(sidebar,"Lv up!");
                    mvwprintw(sidebar,3,1,"HP+%d",a);
                    mvwprintw(sidebar,3,12,"-> %.0f",p.maxhp);
                    mvwprintw(sidebar,4,1,"MP+%d",b);
                    mvwprintw(sidebar,4,12,"-> %.0f",p.maxmp);
                    mvwprintw(sidebar,5,1,"STR+%d",c);
                    mvwprintw(sidebar,5,12,"-> %.0f",p.str);
                    mvwprintw(sidebar,6,1,"TOU+%d",d);
                    mvwprintw(sidebar,6,12,"-> %.0f",p.tou);
                    mvwprintw(sidebar,7,1,"MAG+%d",i);
                    mvwprintw(sidebar,7,12,"-> %.0f",p.mag);
                    mvwprintw(sidebar,8,1,"Wait+%d",f);
                    mvwprintw(sidebar,8,12,"-> %d",p.max_wait);
                    mvwprintw(sidebar,9,1,"Damage+%d",g);
                    mvwprintw(sidebar,9,12,"-> %.2f",p.bonus_damage);

                    box(sidebar,0,0);
                    wrefresh(sidebar);
                    ch = wgetch(sidebar);

                    wclear(sidebar);
                    wmove(sidebar,1,4);
                    wprintw(sidebar,"Choose a bonus:");
                    mvwprintw(sidebar,3,4,"STR + 2,TOU - 1,MAG - 1");
                    mvwprintw(sidebar,4,4,"STR - 1,TOU + 2,MAG - 1");
                    mvwprintw(sidebar,5,4,"STR - 1,TOU - 1,MAG + 2");
                    mvwprintw(sidebar,6,4,"HP + 3,MP - 3");
                    mvwprintw(sidebar,7,4,"HP - 3,MP + 3");
                    mvwprintw(sidebar,8,4,"Wait - 15");
                    mvwprintw(sidebar,9,4,"Damage + 0.2");
                    mvwprintw(sidebar,10,4,"HP regen +1, takes 5 turns longer");
                    mvwprintw(sidebar,11,4,"MP regen +1, takes 5 turns longer");

                    mvwprintw(sidebar,3,1,"-> ");

                    box(sidebar,0,0);
                    wrefresh(sidebar);
                    while (schoice == 0) {
                        for (i = 1;i <= 20;++i) {
                            mvwprintw(sidebar,i,1,"  ");
                        }
                        mvwprintw(sidebar,shl + 2,1,"-> ");

                        ch = wgetch(sidebar);
                        switch (ch) {
                            case KEY_DOWN:
                                if (shl < 9) shl = shl + 1;
                                else shl = 1;
                                break;
                            case KEY_UP:
                                if (shl > 1) shl = shl - 1;
                                else shl = 9;
                                break;
                            case 0x0A: /* Enter */
                                schoice = shl;
                                break;
                            default:
                                break;
                        };
                    }
                    if (schoice == 1 && p.str < STAT_MAX) {
                        p.str = p.str + 2;
                        p.tou = p.tou - 1;
                        p.mag = p.mag - 1;
                    }
                    else if (schoice == 2 && p.tou < STAT_MAX) {
                        p.str = p.str - 1;
                        p.tou = p.tou + 2;
                        p.mag = p.mag - 1;
                    }
                    else if (schoice == 3 && p.mag < STAT_MAX) {
                        p.str = p.str - 1;
                        p.tou = p.tou - 1;
                        p.mag = p.mag + 2;
                    }
                    else if (schoice == 4) {
                        p.maxhp = p.maxhp + 3;
                        p.hp = p.hp + 3;
                        p.maxmp = p.maxmp - 3;
                        p.mp = p.mp - 3;
                    }
                    else if (schoice == 5) {
                        p.maxhp = p.maxhp - 3;
                        p.hp = p.hp - 3;
                        p.maxmp = p.maxmp + 3;
                        p.mp = p.mp + 3;
                    }
                    else if (schoice == 6) {
                        p.max_wait = p.max_wait - 15;
                    }
                    else if (schoice == 7) {
                        p.bonus_damage = p.bonus_damage + 0.2;
                    }
                    else if (schoice == 8) {
                        ++p.hp_regen_amount;
                        p.hp_regen_time = p.hp_regen_time + 5;
                    }
                    else if (schoice == 9) {
                        ++p.mp_regen_amount;
                        p.mp_regen_time = p.mp_regen_time + 5;
                    }

                    if (p.max_wait < 100) p.max_wait = 100;
                    if (p.max_wait > 9999) p.max_wait = 9999;

                    if (p.maxhp > STAT_MAX) p.maxhp = STAT_MAX;
                    if (p.hp > STAT_MAX) p.hp = STAT_MAX;
                    if (p.maxmp > STAT_MAX) p.maxmp = STAT_MAX;
                    if (p.mp > STAT_MAX) p.mp = STAT_MAX;
                    if (p.str > STAT_MAX) p.str = STAT_MAX;
                    if (p.tou > STAT_MAX) p.tou = STAT_MAX;
                    if (p.mag > STAT_MAX) p.mag = STAT_MAX;
                    if (p.bonus_damage > STAT_MAX) p.bonus_damage = STAT_MAX;
                    if (p.maxhp < 1) p.maxhp = 1;
                    if (p.hp < 1) p.hp = 1;
                    if (p.maxmp < 1) p.maxmp = 1;
                    if (p.mp < 1) p.mp = 1;
                    if (p.str < 1) p.str = 1;
                    if (p.tou < 1) p.tou = 1;
                    if (p.mag < 1) p.mag = 1;
                }
            }
		}

		if (e.hp > e.maxhp) e.hp = e.maxhp;

		if (choice != MAX_CHOICES) choice = 0; /* if the player didn't choose SAVE & QUIT, reset their choice */

		/*if (p_status==STUN_ID) choice=99; Forces the player to skip their turn. Needed for the
                                           if statements above. Or not?*/

		if (p.hp <= 0) {
            endgame = 1;
		}

		if (p.hp > p.maxhp) p.hp = p.maxhp;
		if (p.mp > p.maxmp) p.mp = p.maxmp;

		schoice = 0;
		shl = 1;

		if (p.wait > 0 && p.status_id != STUN_ID) {
		    --p.wait;
		    ++global_wait;
		    p_waiting = 1;
		}
		if (p.status_id == STUN_ID) {
            ++global_wait;
            p_waiting = 1;
		}
		if (e.wait > 0 && p_waiting == 1) {
		    if (e.status_id != STUN_ID) --e.wait;
		    /* reset it in case it isn't true next time round. */
		    p_waiting = 0;
		}
		/* global end of turn stuff */

		if (global_wait == 500) {
		    ++turn;
		    ++turns_since_load;

            if (p.hp_regen_cur > 0) --p.hp_regen_cur;
            if (p.mp_regen_cur > 0) --p.mp_regen_cur;
            if (p.status_dur > 0) --p.status_dur;
            if (e.status_dur > 0) --e.status_dur;

            if (p.hp_regen_cur <= 0) {
                p.hp_regen_cur = p.hp_regen_time;
                p.hp = p.hp + p.hp_regen_amount;
            }
            if (p.mp_regen_cur <= 0) {
                p.mp_regen_cur = p.mp_regen_time;
                p.mp = p.mp + p.mp_regen_amount;
            }

            /* turn based statuses */
            /* -1 means dispel was used, and effect should be skipped */
            if (p.status_id == POISON_ID && p.status_dur > -1) {
                p.hp = p.hp - p.status_str;
            }

            if (p.status_id == SAP_ID && p.status_dur > -1) {
                p.mp = p.mp - p.status_str;
                if (p.mp <= 0) p.mp = 0;
            }

            if (p.status_dur <= 0) {
                p.status_id = FINE_ID;
                p.status_str = 0;
            }

            /* enemy status checks */
            if (e.status_id == POISON_ID && e.status_dur > -1) {
                e.hp = e.hp - e.status_str;
            }

            if (e.status_id == SAP_ID && e.status_dur > -1) {
                e.mp = e.mp - e.status_str;
                if (e.mp <= 0) e.mp = 0;
            }

            if (e.status_dur <= 0) {
                e.status_id = FINE_ID;
                e.status_str = 0;
            }

            p_msg_three_color = p_msg_two_color;
            e_msg_three_color = e_msg_two_color;
            p_msg_two_color = p_msg_one_color;
            e_msg_two_color = e_msg_one_color;

            strcpy(p_buffer,"");

            sprintf(p_buffer,"Dealt %.0f damage, healed %.0f/%.0f HP/MP.",p_dmg_dealt,p_dmg_healed,p_mp_healed);
            if (p_dmg_healed < e_dmg_dealt) e_msg_one_color = COLOR_PAIR(1);
            else if (p_dmg_healed == e_dmg_dealt) e_msg_one_color = COLOR_PAIR(4);
            else e_msg_one_color = COLOR_PAIR(3);

            sprintf(e_buffer,"Received %.0f damage, enemy healed %.0f.",e_dmg_dealt,e_dmg_healed);
            if (e_dmg_healed < p_dmg_dealt) p_msg_one_color = COLOR_PAIR(3);
            else if (e_dmg_healed == p_dmg_dealt) p_msg_one_color = COLOR_PAIR(4);
            else p_msg_one_color = COLOR_PAIR(1);

            if (e_killed == 1) {
                wattron(sidebar,COLOR_PAIR(1));
                sprintf(e_kill_msg,"Enemy killed!");
            }
            wattron(sidebar,COLOR_PAIR(3));

            strcpy(p_msg_three,p_msg_two); /* start at the "bottom"; */
            strcpy(e_msg_three,e_msg_two);
            strcpy(e_kill_msg_three,e_kill_msg_two);

            strcpy(p_msg_two,p_msg_one); /* now that two has been copied, move one down; */
            strcpy(e_msg_two,e_msg_one);
            strcpy(e_kill_msg_two,e_kill_msg_one);

            strcpy(p_msg_one,p_buffer); /* bring the buffer in. */
            strcpy(e_msg_one,e_buffer);
            strcpy(e_kill_msg_one,e_kill_msg);

            strcpy(e_buffer,"");
            strcpy(p_buffer,"");
            strcpy(e_kill_msg,"");

            e_killed = 0;

            e_dmg_dealt = 0;
            e_dmg_healed = 0;
            p_dmg_dealt = 0;
            p_dmg_healed = 0;
            p_mp_healed = 0;

            global_wait = 0;
		}
		else if (global_wait > 500) {
            /** @bug
             * global_wait can display as negative;
             * needs looking into.
             */
            global_wait = 0;
        }
	}
	/* Main game loop has ended */
	clear();
	clrtoeol();
	refresh();

	if (p.hp <= 0) {
	    attron(COLOR_PAIR(1));
        for (a = 20;a > 0;--a) {
            if (p.name[a] != ' ') break;
        }
        b = 0;
        move(0,0);
	    printw("R.I.P., ");
	    while (b <= a) {
            printw("%c",p.name[b]);
            ++b;
	    }
	    printw(", killed by ");
        get_e_name(stdscr,(int)e.name[0]);
        if (e.name[0] == 0) wprintw(stdscr," (how sad...)");

        remove("./savefile");
	}
	else {
	    attron(COLOR_PAIR(6));
	    mvprintw(0,0,(p.hp > p.maxhp * .2) ? "See Ya!" : "!!!");
	}

	getch();

	wattroff(stat_win,COLOR_PAIR(2));
	wattroff(choice_win,COLOR_PAIR(4));
	wattroff(enemy_win,COLOR_PAIR(6));
	wattroff(sidebar,COLOR_PAIR(3));

    if (p.hp > 0) save_game(); /* only save if player isn't dead. */

	endwin();
    delwin(enemy_win);
    delwin(stat_win);
    delwin(choice_win);
    delwin(sidebar);

	return 0; /* The game didn't crash! */
}

void print_menu(WINDOW *win, int hl, int x, int y) {
	int i;

	for(i = 0; i < n_choices; ++i) {
		if (hl == i + 1) {
			wattron(win, A_REVERSE);
			mvwprintw(win, y, x, "%s", choices[i]);
			wattroff(win, A_REVERSE);
		}
		else
			mvwprintw(win, y, x, "%s", choices[i]);
		++y;
	}
}

WINDOW *create_newwin(int h, int w, int starty, int startx) {
	WINDOW *win;

	win = newwin(h, w, starty, startx);
	box(win, 0 , 0);
	wrefresh(win);

	return win;
}
