#ifndef H_GLOBAL
#define H_GLOBAL

#ifdef __linux__
    #include <ncurses.h>
#else
    #include <curses.h>
#endif

/** @def STAT_MAX
 * Where pretty much everything caps at.
 *
 * Note however, that this is for 32-bit systems.
 * If you're on a 64-bit system, you may increase
 * this by quite a bit!
 */
#define STAT_MAX 922337203685477580.0 /* =((2 ^ 63) - 1) / 10 */

/** @def SKILL_MAX_LEVEL
 *
 * The highest level a skill can achieve.
 */

/** @def SKILL_MAX_XP_NEEDED
 *
 * The most XP that a skill can require to go up.
 */

/* skills */
#define SKILL_MAX_LEVEL 100000000
#define SKILL_MAX_XP_NEEDED 100000000

#define SKILL_FIGHTING 0

#define SKILL_CRAFTING_GEN 1
#define SKILL_CRAFTING_HEA 2
#define SKILL_CRAFTING_ATT 3
#define SKILL_CRAFTING_WAA 4
#define SKILL_CRAFTING_OTH 5

#define SKILL_CASTING_GEN 6
#define SKILL_CASTING_HEA 7
#define SKILL_CASTING_ATT 8
#define SKILL_CASTING_STA 9
#define SKILL_CASTING_FIR 10
#define SKILL_CASTING_WAT 11
#define SKILL_CASTING_EAR 12

#define NUM_SPECIES 6

#define SPECIES_DRACONIAN 1
#define SPECIES_MINOTAUR 2
#define SPECIES_HUMAN 0
#define SPECIES_FAIRY 5
#define SPECIES_GOLEM 4
#define SPECIES_KOBOLD 3

#define NUM_CLASSES 3

#define CLASS_FIGHTER 0
#define CLASS_MAGE 1
#define CLASS_THIEF 2

#define MAIN_WIDTH 50
#define MAIN_HEIGHT 15
#define STAT_WIDTH 30
#define STAT_HEIGHT 18
#define CHOICE_WIDTH 20
#define CHOICE_HEIGHT 18
#define SIDEBAR_WIDTH 50
#define SIDEBAR_HEIGHT 33

#define RED 1
#define CYAN 2
#define GREEN 3
#define YELLOW 4
#define MAGENTA 5
#define WHITE 6
#define BLUE 7

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

void init_globals();
int roll_die(int sides);
void early_termination(char str[]);
void award_sk_xp(int id,int amount);
void clean_sidebar(WINDOW *w);
void print_desc(WINDOW *w, char desc[], int y, int x);
void add_msg(char m[],int c);

struct Character {
    char name[21];
    int pclass;
    int species;
    double hp;
    double maxhp;
    double mp;
    double maxmp;
    double hp_regen_time;
    double hp_regen_cur;
    double hp_regen_amount;
    double mp_regen_time;
    double mp_regen_cur;
    double mp_regen_amount;
    double str;
    double tou;
    double mag;
    double bonus_damage;
    double lv;
    double xp;
    double next_xp;
    int wait;
    int max_wait;
    double head_ap;
    double body_ap;
    double legs_ap;
    double feet_ap;
    double hands_ap;
    int head_id;
    int body_id;
    int legs_id;
    int feet_id;
    int hands_id;
    double head_wait;
    double body_wait;
    double legs_wait;
    double feet_wait;
    double hands_wait;
    double head_con;
    double body_con;
    double legs_con;
    double feet_con;
    double hands_con;
    double head_maxcon;
    double body_maxcon;
    double legs_maxcon;
    double feet_maxcon;
    double hands_maxcon;
    int equip_id;
    double equip_wait;
    double equip_atk;
    double equip_ap;
    double equip_mod;
    double equip_con;
    double equip_maxcon;
    int status_id;
    double status_dur;
    double status_str;
};

struct Inventory {
    int id;
    double amount;
    double mod;
    double adj;
    double atk;
    double ap;
    int wait;
    double maxcon;
    double con;
    double str;
    int type;
    double part;
    double effect;
};

struct Character p,e;
struct Inventory inv[10];

int p_creation; /**< if player has entered name/species */
int p_waiting; /**< if player is waiting */
int endgame; /**< end game */

int skill[13][3]; /**< skill levels and xp */
double species[7][8]; /**< species base values */
double classes[4][8]; /**< classes base values */

int global_wait; /**< global time flow */
double turn,turns_since_load; /**< turns, 500 wait = 1 turn */
int e_killed; /**< enemy was killed this turn. used for the turn summary. */

/* message vars */
struct msg_log {
    char message[50];
    int color;
};

struct msg_log msg[30];

char p_buffer[50];
char e_buffer[50];

/* gameplay stats */
double stat_kills; /**< enemies killed */
double stat_m_casts; /**< number of magic castings */
double stat_i_used; /**< number of items used */
double stat_p_dam_dealt; /**< total amount of damage dealt. */
double stat_p_dam_taken; /**< total amount of damage taken. */

#endif
