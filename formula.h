/* Describes and defines various formulas */

#define MAX_ATTACK_PER 100.00 /* 10000% */
#define MIN_ATTACK_PER 0.01 /* 1% */

int get_sk_chances(int primary, int secondary);
int roll_sk_bonus(int old_r, int chances);
void attack_formula(int target);
void magic_formula(int sid, int user);
double percentage(double diff,float min_per,float max_per);
double percentage_str(double str,double diff,float min_per,float max_per);