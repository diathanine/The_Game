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
    for (i = 39;i <= 39;++i) {
        p_buffer[i] = 0;
        p_msg_one[i] = 0;
        p_msg_two[i] = 0;
        p_msg_three[i] = 0;
        e_buffer[i] = 0;
        e_buffer_two[i] = 0;
        e_msg_one[i] = 0;
        e_msg_two[i] = 0;
        e_msg_three[i] = 0;
        if (i <= 20) {
            e_kill_msg_one[i] = 0;
            e_kill_msg_two[i] = 0;
            e_kill_msg_three[i] = 0;
            e_kill_msg[i] = 0;
        }
    }
    p_dmg_dealt = 0;
    p_dmg_healed = 0;
    p_mp_healed = 0;
    e_dmg_dealt = 0;
    e_dmg_healed = 0;
    p_msg_one_color = 0;
    p_msg_two_color = 0;
    p_msg_three_color = 0;
    e_msg_one_color = 0;
    e_msg_two_color = 0;
    e_msg_three_color = 0;
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
     * Will wrap based on letters, not whole words.
     * space has "-2" because of the border around the window.
     */
    int space = SIDEBAR_WIDTH - 2, cur = 0;
    size_t len = 0;

    len = strlen(desc);

    move(y,x);
    while (len != 0) {
        if (space != 0) {
            mvwprintw(w,y,x,"%c",desc[cur]);
            space = space - 1;
            ++x;
        }
        else {
            ++y;
            x = 1;
            space = SIDEBAR_WIDTH - 2;
        }
        ++cur;
        --len;
    }
}
