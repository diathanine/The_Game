#ifndef H_ENEMY
#define H_ENEMY

/* stuff relating to the enemy */

#define LV_UP_CHANCE 25
#define ITEM_DROP_CHANCE 15

void generate_name();
void get_e_name(WINDOW *w);
double get_loot_mod(double i_lv);
void kill_enemy();
void generate_name();
void get_e_name(WINDOW *w);
void init_e_names();
/*void set_enemy(double new_hp, double new_mp, double new_STR, double new_DEF, double new_MAG,\
 double new_dice, double new_dice_sides, double new_bonus_damage, double new_lv, double new_AP,\
 double new_maxwait);*/
void enemy_turn();

struct EnemyName {
    char name[30];
    unsigned int color;
};

struct EnemyName e_namedb[20];

double loot_req,loot_ap,loot_atk,loot_maxcon,loot_con,loot_str,loot_eff;
    
int loot,loot_type,loot_lootable,loot_wait,loot_part;

#endif
