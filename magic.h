#ifndef H_MAGIC
#define H_MAGIC

/** @file magic.h
 * defines for all the magic
*/

/*
 * magic effectiveness ranges from .1% - 500%
 *  1    = 100%
 *  .1   = 10%
 *  .01  = 1%
 *  .001 = .1%
 */

#define MAGIC_MAX 10
#define MAGIC_MIN_PERCENT .001 /* .1% */
#define MAGIC_MAX_PERCENT 5 /* 500% */

#define MEF_HEAL 1
#define MEF_DMG 2
#define MEF_STA 3
#define MEF_RPW 4

/** @struct Magic
 * Holds the data for the various spells
 * in the game.
 */
struct Magic {
    char name[30];
    double id;
    int effect;
    int status;
    int invert;
    double cost;
    double str;
    double diff;
    double lv;
    int skill;
    char desc[100];
};

struct Magic magic_db[MAGIC_MAX];

void init_magic();
void magic_entry_item(WINDOW *s, int pos, int m);
void magic_menu(WINDOW *s, int cur);
int magic_main(WINDOW *w);

#endif
