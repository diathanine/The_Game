/** @file globals.c
 * Defines functions that are either
 * global in scope.
 */

#include <string.h>
#include "globals.h"
#include "item.h"

/**
 * Inits the global vars.
 */
void init_globals() {
    int i,j;

    p_creation = 0;
    p_waiting = 0;
    endgame = 0;
    for (i = 0;i <= INVEN_MAX;++i) {
        inv[i].id = 0;
        inv[i].amount = 0;
        inv[i].mod = 0;
        inv[i].adj = 0;
        inv[i].atk = 0;
        inv[i].ap = 0;
        inv[i].wait = 0;
        inv[i].maxcon = 0;
        inv[i].con = 0;
        inv[i].str = 0;
        inv[i].type = 0;
        inv[i].part = 0;
        inv[i].effect = 0;
    }
    for (i = 0;i <= 12;++i) {
        for (j = 0;j <= 2;++j) {
            skill[i][j] = 0;
        }
    }
    global_wait = 0;
    turn = 1;
    turns_since_load = 0;
    e_killed = 0;
    e.species = -1;
    e.equip_ap = 0;
    for (i = 19;i > 0;--i) {
        strcpy(msg[i].message,"\0");
        msg[i].color = GREEN;
    }
    stat_kills = 0;
    stat_m_casts = 0;
    stat_i_used = 0;
    stat_p_dam_dealt = 0;
    stat_p_dam_taken = 0;
}

/**
 * Prints a description.
 *
 * Prints the description associated
 * with an item or spell.
 *
 * @param w The window to print to.
 * @param desc The description to print.
 * @param y y-coor to start at.
 * @param x x-coor to start at.
 */
void print_desc(WINDOW *w, char desc[], int y, int x) {
    /*
     * Some notes:
     * No matter the starting x, will return to the far left
     *  when wrapping.
     * space has "-2" because of the border around the window.
     */
    int space = SIDEBAR_WIDTH - 2, first = 1, cont = 1;
    char *tdesc, mdesc[100];
    size_t len = 0, cur = 0;

    /* Don't modify the item_db desc. ;P */
    strcpy(mdesc,desc);
    len = strlen(desc);

    move(y,x);
    while (len > 0 && y < SIDEBAR_HEIGHT - 1) {
        if (first == 1) tdesc = strtok(mdesc," ");
        else if (cont == 1) tdesc = strtok(NULL," ");

        if (tdesc == NULL) break;
        cur = strlen(tdesc);

        if (space > 0 && cur <= space) {
            mvwprintw(w,y,x,"%s",tdesc);
            /* An extra 1 for space between words. */
            space = space - cur - 1;
            x = x + cur + 1;
            len = len - cur + 1;
            cont = 1;
        }
        else {
            cont = 0;
            ++y;
            x = 1;
            space = SIDEBAR_WIDTH - 2;
        }

        if (first == 1) first = 0;
    }
}

void add_msg(char m[], int c) {
    int i;
    for (i = 28;i >= 0;--i) {
        strcpy(msg[i + 1].message,msg[i].message);
        msg[i + 1].color = msg[i].color;
    }
    strcpy(msg[0].message,m);
    msg[0].color = c;
}