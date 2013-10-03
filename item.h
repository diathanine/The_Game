#ifndef H_ITEM
#define H_ITEM

/** @file item.h
 * Definitions and functions related to items.
 * 
 */

/* defines all items
 defines:
  id
  strength (if item)
  dice (if weapon)
  dice sides (if weapon)
  condition (if equip)
  AP (if armor)
  crafting cost
  crafting difficulty
  level requirement to get as a drop/crafting
  long description

 Body part ids:
  1. head
  2. body
  3. legs
  4. feet
  5. hands

 Item types:
  1. Item (potions, grenade, etc.)
  2. Weapon
  3. Armor
  */

#define GREAT_ADJ 5
#define GOOD_ADJ 5
#define AVG_ADJ 5
#define BAD_ADJ 5
#define HOR_ADJ 5
#define DESC_X 35
#define CRAFTMENU_DESCX 40
#define CRAFT_PAGES 3 /* Number of pages in craft menu */
#define CRAFT_PER_PAGE 10 /* Entries per craft page */
/* Maximums for items - they can't reach STAT_MAX
 Temp until it's all converted to double. */
#define ITEM_STAT_MAX 2147000000

#define INVEN_MAX 9
#define INVEN_MAXB 13

#define INVEN_ID 0 /* ID of item */
#define INVEN_AMOUNT 1 /* How many in stack */
#define INVEN_MOD 2 /* Modifier */
#define INVEN_ADJ 3 /* adjectival */
#define INVEN_DICE 4 /* number of dice for weapon */
#define INVEN_DICESIDES 5 /* number of sides per die for weapon */
#define INVEN_AP 6 /* AP for armor */
#define INVEN_WAIT 7 /* wait added to base. Weapon/armor */
#define INVEN_MAXCON 8 /* Max condition */
#define INVEN_CON 9 /* current condition */
#define INVEN_STR 10 /* STR of regular items */
#define INVEN_TYP 11 /* for storing what type of item it is */
#define INVEN_PAR 12 /* body part for armor */
#define INVEN_EFF 13 /* effect of regular items. */

/* item effects */
#define EFF_HEALHP 1
#define EFF_HEALMP 2
#define EFF_DAMAGE 3
#define EFF_HPUP 4
#define EFF_MPUP 5
#define EFF_STRUP 6
#define EFF_DEFUP 7
#define EFF_MAGUP 8
#define EFF_WTDOWN 9
#define EFF_HPREG 10
#define EFF_MPREG 11
#define EFF_ELV 12
#define EFF_ELVBAL 13

int init_items();
void get_adjname(int adjid);
void get_adjval();
void item_menu(WINDOW *sb);
void craft_entry_item(WINDOW *s, int pos, double lv, double diff, double cost);
void craft_menu(WINDOW *s, int p);
int item_info(WINDOW *win, int ycor, int hb, char idesc[]);
void draw_item(WINDOW *s, int h);
int get_craft_mod(double diff);
void equip_armor(int part, double armap, double armcon, int armid, double armwait);
void equip_weapon(double weadice, double weadisi, double weacon, double weaap, double weawait, double weabdam, int weaid);
void item_effect(int ti, int effect, int istr);
void use_item(int b, int toss);
void give_item(int id, int typ, double mod, int adj, double dice, double dicesides,\
                double ap, int iwait, double maxcon, double con, double str, double eff,\
                int part);
void unequip_item(int slot);
int item_main(WINDOW *w);
int craft_main(WINDOW *w);

int item_max; /* highest item id */

/* Currently transfering all item constants to use new struct. */

/** @struct Item
 * 
 * Stores the data for all the items.
 * 
 */
struct Item {
    char iname[50];
    int id;
    int type;
    double skl;
    double str;
    double effect;
    double cost;
    double diff;
    double lv;
    int lootable;
    double dice;
    double dice_sides;
    double ap;
    int body_part;
    double condition;
    int wait;
    char desc[100];
};

struct Item item_db[50]; /**< Contains values for all items */

/* used when an item is given. */
double item_adj,item_dice,item_dicesides,item_ap,item_wait,item_str,item_part,item_eff;
double item_adjval;
double item_con,item_maxcon;

#endif
