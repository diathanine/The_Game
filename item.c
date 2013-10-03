#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <math.h>
#include "formula.h"
#include "item.h"
#include "globals.h"

/**
 * Creates the items.
 * 
 * On startup, item_db[] is set to contain
 * the base stats of all the items in the game.
 */
int init_items() {
    /* Many places in the code start at item_db[1]
     *
     * There is no need to include line feeds in the descriptions.
     */
    int cur_id = 1;

    strcpy(item_db[0].iname,"Object 0");
    item_db[0].id = 0;
    item_db[0].type = 1;
    item_db[0].skl = SKILL_CRAFTING_HEA;
    item_db[0].str = 0;
    item_db[0].effect = EFF_HEALHP;
    item_db[0].cost = 0;
    item_db[0].diff = 1;
    item_db[0].lv = 1;
    item_db[0].lootable = 0;
    item_db[0].dice = 0;
    item_db[0].dice_sides = 0;
    item_db[0].ap = 0;
    item_db[0].body_part = 0;
    item_db[0].condition = 0;
    item_db[0].wait = 0;
    strcpy(item_db[0].desc,"Fake item.");
    
    strcpy(item_db[cur_id].iname,"Tiny Red Potion");
    item_db[cur_id].id = cur_id;
    item_db[cur_id].type = 1;
    item_db[cur_id].skl = SKILL_CRAFTING_HEA;
    item_db[cur_id].str = 100;
    item_db[cur_id].effect = EFF_HEALHP;
    item_db[cur_id].cost = 10;
    item_db[cur_id].diff = 5;
    item_db[cur_id].lv = 1;
    item_db[cur_id].lootable = 1;
    item_db[cur_id].dice = 0;
    item_db[cur_id].dice_sides = 0;
    item_db[cur_id].ap = 0;
    item_db[cur_id].body_part = 0;
    item_db[cur_id].condition = 0;
    item_db[cur_id].wait = 0;
    strcpy(item_db[cur_id].desc,"A tiny vial of some healing fluid.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Tiny Blue Potion");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_HEA;
    item_db[cur_id].str=25;
    item_db[cur_id].effect=EFF_HEALMP;
    item_db[cur_id].cost=10;
    item_db[cur_id].diff=5;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"A tiny vial of some magical fluid.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Small Red Potion");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].str=250;
    item_db[cur_id].effect=EFF_HEALHP;
    item_db[cur_id].cost=50;
    item_db[cur_id].diff=25;
    item_db[cur_id].lv=20;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"A small vial of some healing fluid.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Small Blue Potion");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_HEA;
    item_db[cur_id].str=50;
    item_db[cur_id].effect=EFF_HEALMP;
    item_db[cur_id].cost=20;
    item_db[cur_id].diff=10;
    item_db[cur_id].lv=20;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"A small vial of some magical fluid.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Grenade");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_ATT;
    item_db[cur_id].str=75;
    item_db[cur_id].effect=EFF_DAMAGE;
    item_db[cur_id].cost=20;
    item_db[cur_id].diff=15;
    item_db[cur_id].lv=5;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"A small thrown explosive.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Copper Dagger");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=2;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=5;
    item_db[cur_id].effect=EFF_DAMAGE;
    item_db[cur_id].cost=7;
    item_db[cur_id].diff=3;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=2;
    item_db[cur_id].dice_sides=4;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=5000;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"A small dagger made of copper.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Copper Short Sword");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=2;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=22;
    item_db[cur_id].effect=EFF_DAMAGE;
    item_db[cur_id].cost=30;
    item_db[cur_id].diff=25;
    item_db[cur_id].lv=5;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=2;
    item_db[cur_id].dice_sides=5;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=20000;
    item_db[cur_id].wait=1;
    strcpy(item_db[cur_id].desc,"A sword with a copper blade.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Copper Axe");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=2;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=25;
    item_db[cur_id].effect=EFF_DAMAGE;
    item_db[cur_id].cost=40;
    item_db[cur_id].diff=30;
    item_db[cur_id].lv=7;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=1;
    item_db[cur_id].dice_sides=8;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=22000;
    item_db[cur_id].wait=2;
    strcpy(item_db[cur_id].desc,"A light-weight axe made of copper.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Paper Cap");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=5;
    item_db[cur_id].diff=2;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=1;
    item_db[cur_id].body_part=1;
    item_db[cur_id].condition=300;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"{Head} Conical and comical.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Paper Armor");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=8;
    item_db[cur_id].diff=4;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=3;
    item_db[cur_id].body_part=2;
    item_db[cur_id].condition=425;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"{Body} Armor fashioned from paper. Won't stop much.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Paper Gloves");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=1;
    item_db[cur_id].diff=1;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=1;
    item_db[cur_id].body_part=5;
    item_db[cur_id].condition=120;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"{Hands} Paper gloves. Provides immunity to paper cuts.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Paper Greaves");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=2;
    item_db[cur_id].diff=3;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=2;
    item_db[cur_id].body_part=3;
    item_db[cur_id].condition=200;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"{Legs} Made of paper.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Paper Boots");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=1;
    item_db[cur_id].diff=1;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=1;
    item_db[cur_id].body_part=4;
    item_db[cur_id].condition=110;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"{Feet} Made of paper.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Leather Cap");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=3;
    item_db[cur_id].diff=2;
    item_db[cur_id].lv=1;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=1;
    item_db[cur_id].body_part=1;
    item_db[cur_id].condition=2500;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"{Head} A cap made of leather.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Leather Armor");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=12;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=100;
    item_db[cur_id].diff=100;
    item_db[cur_id].lv=30;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=10;
    item_db[cur_id].body_part=2;
    item_db[cur_id].condition=1200;
    item_db[cur_id].wait=5;
    strcpy(item_db[cur_id].desc,"{Body} Basically just a vest.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Leather Gloves");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=16;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=60;
    item_db[cur_id].diff=60;
    item_db[cur_id].lv=20;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=7;
    item_db[cur_id].body_part=5;
    item_db[cur_id].condition=800;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"{Hands} A set of leather gloves.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Leather Greaves");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=19;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=100;
    item_db[cur_id].diff=150;
    item_db[cur_id].lv=45;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=9;
    item_db[cur_id].body_part=3;
    item_db[cur_id].condition=1050;
    item_db[cur_id].wait=2;
    strcpy(item_db[cur_id].desc,"{Legs} Made of leather.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Leather Boots");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=3;
    item_db[cur_id].skl=SKILL_CRAFTING_WAA;
    item_db[cur_id].str=12;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=35;
    item_db[cur_id].diff=25;
    item_db[cur_id].lv=15;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=7;
    item_db[cur_id].body_part=4;
    item_db[cur_id].condition=600;
    item_db[cur_id].wait=1;
    strcpy(item_db[cur_id].desc,"{Feet} Boots with leather padding.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Tofu");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=2;
    item_db[cur_id].effect=EFF_HPUP;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=100;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Permanently raise HP by 2.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Rice");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=2;
    item_db[cur_id].effect=EFF_MPUP;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=1000;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Permanently increase MP by 2.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Steak");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_STRUP;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=1000;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Permanently increase STR by 1.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Milk");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_DEFUP;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=1000;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Permanently increase DEF by 1.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Apple");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_MAGUP;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=1000;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Permanently increase MAG by 1.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Carrot");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=15;
    item_db[cur_id].effect=EFF_WTDOWN;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=1000;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Drop Wait by 15. Can't go below 100.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Pumpkin");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_HPREG;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=1000;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"HP regens 1 turn faster.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Squash");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=1;
    item_db[cur_id].effect=EFF_MPREG;
    item_db[cur_id].cost=2000;
    item_db[cur_id].diff=2000;
    item_db[cur_id].lv=1000;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"MP regens 1 turn faster.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Orb of Safety");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=-5;
    item_db[cur_id].effect=EFF_ELV;
    item_db[cur_id].cost=150;
    item_db[cur_id].diff=80;
    item_db[cur_id].lv=35;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Makes things safer.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Orb of Danger");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=5;
    item_db[cur_id].effect=EFF_ELV;
    item_db[cur_id].cost=150;
    item_db[cur_id].diff=80;
    item_db[cur_id].lv=35;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Makes things dangerous.");

    ++cur_id;

    strcpy(item_db[cur_id].iname,"Orb of Balance");
    item_db[cur_id].id=cur_id;
    item_db[cur_id].type=1;
    item_db[cur_id].skl=SKILL_CRAFTING_OTH;
    item_db[cur_id].str=5;
    item_db[cur_id].effect=EFF_ELVBAL;
    item_db[cur_id].cost=200;
    item_db[cur_id].diff=110;
    item_db[cur_id].lv=45;
    item_db[cur_id].lootable=1;
    item_db[cur_id].dice=0;
    item_db[cur_id].dice_sides=0;
    item_db[cur_id].ap=0;
    item_db[cur_id].body_part=0;
    item_db[cur_id].condition=0;
    item_db[cur_id].wait=0;
    strcpy(item_db[cur_id].desc,"Makes things balanced.");

    return cur_id;
}

/**
 * Gets an adjective name by id.
 *
 */
void get_adjname(int adjid) {
    if (adjid < 1) strcpy(p_buffer,"ADJ ID TOO LOW!");
    else if (adjid == 1) strcpy(p_buffer,"GREAT!");
    else if (adjid == 2) strcpy(p_buffer,"AWESOME");
    else if (adjid == 3) strcpy(p_buffer,"Wonderful");
    else if (adjid == 4) strcpy(p_buffer,"Inspiring");
    else if (adjid == 5) strcpy(p_buffer,"Immaculate");
    else if (adjid == 1 + GREAT_ADJ) strcpy(p_buffer,"Good");
    else if (adjid == 2 + GREAT_ADJ) strcpy(p_buffer,"Neat");
    else if (adjid == 3 + GREAT_ADJ) strcpy(p_buffer,"Interesting");
    else if (adjid == 4 + GREAT_ADJ) strcpy(p_buffer,"Better");
    else if (adjid == 5 + GREAT_ADJ) strcpy(p_buffer,"B+");
    else if (adjid == 1 + GREAT_ADJ + GOOD_ADJ) strcpy(p_buffer,"Average");
    else if (adjid == 2 + GREAT_ADJ + GOOD_ADJ) strcpy(p_buffer,"Dull");
    else if (adjid == 3 + GREAT_ADJ + GOOD_ADJ) strcpy(p_buffer,"Meh");
    else if (adjid == 4 + GREAT_ADJ + GOOD_ADJ) strcpy(p_buffer,"Drab");
    else if (adjid == 5 + GREAT_ADJ + GOOD_ADJ) strcpy(p_buffer,"Common");
    else if (adjid == 1 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) strcpy(p_buffer,"Bad");
    else if (adjid == 2 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) strcpy(p_buffer,"Confused");
    else if (adjid == 3 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) strcpy(p_buffer,"Ignorable");
    else if (adjid == 4 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) strcpy(p_buffer,"Angry");
    else if (adjid == 5 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) strcpy(p_buffer,"D-");
    else if (adjid == 1 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) strcpy(p_buffer,"Horrible");
    else if (adjid == 2 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) strcpy(p_buffer,"Atrocious");
    else if (adjid == 3 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) strcpy(p_buffer,"Terrible");
    else if (adjid == 4 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) strcpy(p_buffer,"Laughable");
    else if (adjid == 5 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) strcpy(p_buffer,"Failsauce");
    else strcpy(p_buffer,"ADJ ID TOO HIGH!");
}

/**
 * Returns the values of an adjective.
 * 
 * These values determine how an adjective
 * affects an item.
 */
void get_adjval() {
    int adjid;
    
    /*
     * Just a random formula I thought up. Not tested
     * for balance.
     */
    item_adjval = (e.lv / 3) - (p.lv * 2);
    if (item_adjval >= 75) {
        adjid = roll_die(GREAT_ADJ);
    }
    else if (item_adjval < 75 && item_adjval >= 25) {
        adjid = roll_die(GOOD_ADJ) + GREAT_ADJ; /* Need to take previous category in consideration. */
    }
    else if (item_adjval < 25 && item_adjval >= -25) {
        adjid = roll_die(AVG_ADJ) + GREAT_ADJ + GOOD_ADJ;
    }
    else if (item_adjval < -25 && item_adjval >= -75) {
        adjid = roll_die(BAD_ADJ) + GREAT_ADJ + GOOD_ADJ + AVG_ADJ;
    }
    else {
        adjid = roll_die(HOR_ADJ) + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ;
    }
    
    item_adjval = adjid;
    if (adjid == 1) { /*GREAT!*/
        item_ap = 5;
        item_wait = -5;
        item_dice = 1;
        item_dicesides = 6;
        item_con = 1.45;
    }
    else if (adjid == 2) { /*AWESOME*/
        item_ap = 6;
        item_wait = -5;
        item_dice = 0;
        item_dicesides = 7;
        item_con = 1.65;
    }
    else if (adjid == 3) { /* Wonderful */
        item_ap = 5;
        item_wait = -1;
        item_dice = 2;
        item_dicesides = 1;
        item_con = 1.5;
    }
    else if (adjid == 4) { /*Inspiring*/
        item_ap = 10;
        item_wait = -8;
        item_dice = 3;
        item_dicesides = 3;
        item_con = 1.9;
    }
    else if (adjid == 5) { /*Immaculate*/
        item_ap = 9;
        item_wait = -6;
        item_dice = 1;
        item_dicesides = 1;
        item_con = 1.6;
    }
    else if (adjid == 1 + GREAT_ADJ) { /*Good*/
        item_ap = 3;
        item_wait = -2;
        item_dice = 0;
        item_dicesides = 2;
        item_con = 1.1;
    }
    else if (adjid == 2 + GREAT_ADJ) { /*Neat*/
        item_ap = 1;
        item_wait = -1;
        item_dice = 0;
        item_dicesides = 2;
        item_con = 1.05;
    }
    else if (adjid == 3 + GREAT_ADJ) { /*Interesting*/
        item_ap = 4;
        item_wait = 0;
        item_dice = 1;
        item_dicesides = 0;
        item_con = 1.2;
    }
    else if (adjid == 4 + GREAT_ADJ) { /*Better*/
        item_ap = 5;
        item_wait = -3;
        item_dice = 1;
        item_dicesides = 1;
        item_con = 1.25;
    }
    else if (adjid == 5 + GREAT_ADJ) { /*B+*/
        item_ap = 1;
        item_wait = -1;
        item_dice = 0;
        item_dicesides = 3;
        item_con = 1.12;
    }
    else if (adjid == 1 + GREAT_ADJ + GOOD_ADJ) { /*Average*/
        item_ap = 0;
        item_wait = 0;
        item_dice = 0;
        item_dicesides = 0;
        item_con = 1.0;
    }
    else if (adjid == 2 + GREAT_ADJ + GOOD_ADJ) { /*Dull*/
        item_ap = 0;
        item_wait = -1;
        item_dice = 0;
        item_dicesides = 0;
        item_con = 1.02;
    }
    else if (adjid == 3 + GREAT_ADJ + GOOD_ADJ) { /*Meh*/
        item_ap = 0;
        item_wait = 0;
        item_dice = 0;
        item_dicesides = 1;
        item_con = 1.01;
    }
    else if (adjid == 4 + GREAT_ADJ + GOOD_ADJ) { /*Drab*/
        item_ap = 0;
        item_wait = 0;
        item_dice = 0;
        item_dicesides = 2;
        item_con = 1.05;
    }
    else if (adjid == 5 + GREAT_ADJ + GOOD_ADJ) { /*Common*/
        item_ap = 0;
        item_wait = -1;
        item_dice = 0;
        item_dicesides = 0;
        item_con = 1.03;
    }
    else if (adjid == 1 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) { /*Bad*/
        item_ap = -3;
        item_wait = 4;
        item_dice = -1;
        item_dicesides = -3;
        item_con = 0.75;
    }
    else if (adjid == 2 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) { /*Confused*/
        item_ap = -3;
        item_wait = 6;
        item_dice = -1;
        item_dicesides = -6;
        item_con = 0.65;
    }
    else if (adjid == 3 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) { /*Ignorable*/
        item_ap = -4;
        item_wait = 2;
        item_dice = -2;
        item_dicesides = -3;
        item_con = 0.5;
    }
    else if (adjid == 4 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) { /*Angry*/
        item_ap = -1;
        item_wait = 3;
        item_dice = -1;
        item_dicesides = -2;
        item_con = 0.52;
    }
    else if (adjid == 5 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ) { /*D-*/
        item_ap = -7;
        item_wait = 10;
        item_dice = -2;
        item_dicesides = -2;
        item_con = 0.61;
    }
    else if (adjid == 1 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) { /*Horrible*/
        item_ap = -10;
        item_wait = 20;
        item_dice = -3;
        item_dicesides = -8;
        item_con = 0.3;
    }
    else if (adjid == 2 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) { /*Atrocious*/
        item_ap = -15;
        item_wait = 25;
        item_dice = -3;
        item_dicesides = -10;
        item_con = 0.2;
    }
    else if (adjid == 3 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) { /*Terrible*/
        item_ap = -8;
        item_wait = 15;
        item_dice = -2;
        item_dicesides = -12;
        item_con = 0.35;
    }
    else if (adjid == 4 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) { /*Laughable*/
        item_ap = -17;
        item_wait = 30;
        item_dice = -3;
        item_dicesides = -9;
        item_con = 0.15;
    }
    else if (adjid == 5 + GREAT_ADJ + GOOD_ADJ + AVG_ADJ + BAD_ADJ) { /*Failsause*/
        item_ap = -40;
        item_wait = 100;
        item_dice = -7;
        item_dicesides = -20;
        item_con = 0.01;
    }
    
    /*
     * Are these needed?
    if (item_ap > ITEM_STAT_MAX) item_ap = ITEM_STAT_MAX;
    if (item_wait > ITEM_STAT_MAX) item_wait = ITEM_STAT_MAX;
    if (item_dice > ITEM_STAT_MAX) item_dice = ITEM_STAT_MAX;
    if (item_dicesides > ITEM_STAT_MAX) item_dicesides = ITEM_STAT_MAX;
    if (item_con > ITEM_STAT_MAX) item_con = ITEM_STAT_MAX;
    if (item_ap < ITEM_STAT_MAX * -1) item_ap = ITEM_STAT_MAX * -1;
    if (item_wait < -9999) item_wait = -9999;
    if (item_dice < 1) item_dice = 1;
    if (item_dicesides < 1) item_dicesides = 1;
    if (item_con < 0.01) item_con = 0.01;
    */
}

/**
 * Prints out the item menu.
 * 
 * This is the list the player sees when
 * they select "Item" from the menu.
 * 
 */
void item_menu(WINDOW *sb) {
    int i = -1,o = 0,lo = 1;
    while (o <= INVEN_MAX) {
        /* o = current slot,lo = last o
        i isn't immediately reset because the next item slot might be a match
        anyway. */
        if (inventory[o][INVEN_ID] == i && i == 0) {
            mvwprintw(sb,o + 2,4,"Nothing    ");
            mvwprintw(sb,o + 2,DESC_X,"                    ");
            ++o;
        }
        else if (inventory[o][INVEN_ID] == i) {
            mvwprintw(sb,o + 2,4,"%s",item_db[i].iname);
            mvwprintw(sb,o + 2,30,"%+.0f",inventory[o][INVEN_MOD]);
            mvwprintw(sb,o + 2,38,"x%03.0f",inventory[o][INVEN_AMOUNT]);
            ++o;
        }

        if (o != lo) {
            /* if we found the correct item to display,
            we move on to the next slot, and reset i.*/
            lo = o;
            i = -1;
        }
        ++i;
    }
}

/**
 * Displays an entry in the crafting menu.
 *
 * @param s Window to print to.
 * @param pos Current line.
 * @param lv Level of item.
 * @param diff Difficulty of item.
 * @param cost Cost of item.
 */
void craft_entry_item(WINDOW *s, int pos, double lv, double diff, double cost) {
    if (p.lv < lv) {
        wattron(s,COLOR_PAIR(1));
        mvwprintw(s,pos,4,"??? Lv:%.0f",lv);
    }
    else {
        if (p.mag < (diff * .15)) wattron(s,COLOR_PAIR(1)); /* red */
        else if (p.mag < (diff * .30)) wattron(s,COLOR_PAIR(4)); /* yellow */
        else if (p.mag < (diff * .45)) wattron(s,COLOR_PAIR(6)); /* white */
        else if (p.mag < (diff * .60)) wattron(s,COLOR_PAIR(3)); /* green */
        else if (p.mag < (diff * .75)) wattron(s,COLOR_PAIR(2)); /* cyan */
        else if (p.mag < (diff * .90)) wattron(s,COLOR_PAIR(7)); /* blue */
        else wattron(s,COLOR_PAIR(5)); /* magenta */

        mvwprintw(s,pos,30,"%.0fMP % 3.2f%%",cost,percentage(diff,.01,1));
    }
}

/**
 * Prints the crafting menu.
 *
 * @param s Window to print to.
 * @param pg Current page of menu.
 */
void craft_menu(WINDOW *s, int pg) {
    int c,pos = 4;

    for (c = ((pg - 1) * CRAFT_PER_PAGE) + 1;c < (pg * CRAFT_PER_PAGE) + 1;++c) {
        if (c <= item_max) {
            craft_entry_item(s,pos,item_db[c].lv,item_db[c].diff,item_db[c].cost);
            if (p.lv >= item_db[c].lv) {
                mvwprintw(s,pos,4,"%s",item_db[c].iname);
            }
            else {
                mvwprintw(s,pos,4,"Your level is to low. Need: %.0f",item_db[c].lv);
            }
            wattron(s,COLOR_PAIR(3));
            ++pos;
        }
        else if (c > item_max) {
            mvwprintw(s,pos,4,"---");
        }
    }
}

/**
 * Prints the info for the highlighted
 * item in the player's inventory.
 *
 * @param win Window to print to.
 * @param ycor Y-coor of win.
 * @param h Current inventory slot.
 * @param idesc The description of the current item.
 */
int item_info(WINDOW *win, int ycor, int h, char idesc[]) {
    if (inventory[h][INVEN_ADJ] != 0) {
        get_adjname(inventory[h][INVEN_ADJ]);
        mvwprintw(win,ycor++,1,"Adjectival: %s",p_buffer);
    }
    
    if (inventory[h][INVEN_TYP] == 1) {
        if (inventory[h][INVEN_EFF] == EFF_HEALHP)
         mvwprintw(win,ycor++,1,"Restores HP: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_HEALMP)
         mvwprintw(win,ycor++,1,"Restores MP: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_DAMAGE)
         mvwprintw(win,ycor++,1,"Causes damage: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_HPUP)
         mvwprintw(win,ycor++,1,"Permanent HP boost: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_MPUP)
         mvwprintw(win,ycor++,1,"Permanent MP boost: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_STRUP)
         mvwprintw(win,ycor++,1,"Permanent STR boost: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_DEFUP)
         mvwprintw(win,ycor++,1,"Permanent DEF boost: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_MAGUP)
         mvwprintw(win,ycor++,1,"Permanent MAG boost: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_WTDOWN)
         mvwprintw(win,ycor++,1,"Permanently lowers Wait: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_HPREG)
         mvwprintw(win,ycor++,1,"Permanently boosts HP regen: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_MPREG)
         mvwprintw(win,ycor++,1,"Permanently boosts MP regen: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_ELV)
         mvwprintw(win,ycor++,1,"Changes enemy's level: %.0f",inventory[h][INVEN_STR]);
        else if (inventory[h][INVEN_EFF] == EFF_ELVBAL)
         mvwprintw(win,ycor++,1,"Draws enemy level towards yours: %.0f",inventory[h][INVEN_STR]);
        else mvwprintw(win,ycor++,1,"Unknown effect %d",inventory[h][INVEN_EFF]);
    }
    
    if (inventory[h][INVEN_MAXCON] != 0)
     mvwprintw(win,ycor++,1,"Condition: %.0f/%.0f",inventory[h][INVEN_CON],inventory[h][INVEN_MAXCON]);

    if (inventory[h][INVEN_DICE] != 0 || inventory[h][INVEN_DICESIDES] != 0)
     mvwprintw(win,ycor++,1,"Damage: %.0fd%.0f%+.0f",inventory[h][INVEN_DICE],inventory[h][INVEN_DICESIDES],inventory[h][INVEN_MOD]);

    if (inventory[h][INVEN_AP] != 0)
     mvwprintw(win,ycor++,1,"AP: %.0f",inventory[h][INVEN_AP] + inventory[h][INVEN_MOD]);

    if (inventory[h][INVEN_WAIT] != 0)
     mvwprintw(win,ycor++,1,"Wait: %+d",inventory[h][INVEN_WAIT]);

    print_desc(win,(char *)idesc,ycor++,1);

    return ycor + 2;
}

void draw_item(WINDOW *s,int h) {
    int id = inventory[h][INVEN_ID];
    if (id != 0) item_info(s,15,h,item_db[id].desc);
}

/**
 * Returns the mod value of a crafted
 * item.
 *
 * @param diff Difficulty of item.
 */
int get_craft_mod(double diff) {
    int total_mod = 0;
    double chances;

    chances = round(p.mag / (diff * 3));
    while (chances > 0) {
        if (roll_die(100) <= 30) { /* 30% of mod changing */
            if (roll_die(100) <= 50) ++total_mod; /* 50% for +1, else -1 */
            else --total_mod;
        }
        --chances;
    }
    return total_mod;
}

/**
 * Equips a piece of armor.
 *
 * @param part The body part to place the armor.
 * @param armap The AP of the armor.
 * @param armcon Condition of the armor.
 * @param armid ID of the armor.
 * @param armwait The Wait of the armor.
 */
void equip_armor(int part, double armap, double armcon, int armid, double armwait) {
    if (part == 1) {
        p.head_ap = armap;
        p.head_maxcon = armcon;
        p.head_con = p.head_maxcon;
        p.head_id = armid;
        p.head_wait = armwait;
    }
    else if (part == 2) {
        p.body_ap = armap;
        p.body_maxcon = armcon;
        p.body_con = p.body_maxcon;
        p.body_id = armid;
        p.body_wait = armwait;
    }
    else if (part == 3) {
        p.legs_ap = armap;
        p.legs_maxcon = armcon;
        p.legs_con = p.legs_maxcon;
        p.legs_id = armid;
        p.legs_wait = armwait;
    }
    else if (part == 4) {
        p.feet_ap = armap;
        p.feet_maxcon = armcon;
        p.feet_con = p.feet_maxcon;
        p.feet_id = armid;
        p.feet_wait = armwait;
    }
    else if (part == 5) {
        p.hands_ap = armap;
        p.hands_maxcon = armcon;
        p.hands_con = p.hands_maxcon;
        p.hands_id = armid;
        p.hands_wait = armwait;
    }
    else early_termination("Invalid body part while equipping.");
}

/**
 * Equips a weapon.
 *
 * @param weadice Number of dice.
 * @param weadisi Number of dicesides.
 * @param weacon Condition of weapon.
 * @param weaap Bonus AP from weapon.
 * @param weawait Weapon's Wait.
 * @param weabdam Weapon's bonus damage.
 * @param weaid ID of weapon.
 */
void equip_weapon(double weadice, double weadisi, double weacon, double weaap, double weawait, double weabdam, int weaid) {
    p.dice = weadice;
    p.dice_sides = weadisi;
    p.equip_maxcon = weacon;
    p.equip_con = p.equip_maxcon;
    p.equip_ap = weaap;
    p.equip_wait = weawait;
    p.equip_mod = weabdam;
    p.equip_id = weaid;
}

/**
 * Where the actual effects happen.
 *
 * This is for usable items only, not
 * weapons and armor.
 *
 * @param ti If item was thrown.
 * @param effect The effect that the item causes.
 * @param istr Power of item.
 */
void item_effect(int ti, int effect, int istr) {
    /*
    ti:
     1=throwing item
    */

    if (effect == EFF_HEALHP) {
        if (ti == 0) {
            p.hp = p.hp + istr;
            p_dmg_healed = p_dmg_healed + istr;
        }
        else {
            e.hp = e.hp + istr;
        }
    }
    else if (effect == EFF_HEALMP) {
        if (ti == 0) {
            p.mp = p.mp + istr;
            p_mp_healed = p_mp_healed + istr;
        }
        else {
            e.mp = e.mp + istr;
        }
    }
    else if (effect == EFF_DAMAGE) {
        e.hp = e.hp - istr;
        p_dmg_dealt = p_dmg_dealt + istr;
        stat_p_dam_dealt = stat_p_dam_dealt + istr;
    }
    else if (effect == EFF_HPUP) {
        if (ti == 0) {
            p.maxhp = p.maxhp + istr;
            p.hp = p.hp + istr;
        }
        else {
            e.maxhp = e.maxhp+istr;
            e.hp = e.hp + istr;
        }
    }
    else if (effect == EFF_MPUP) {
        if (ti == 0) {
            p.maxmp = p.maxmp + istr;
            p.mp = p.mp+istr;
        }
        else {
            e.maxmp = e.maxmp + istr;
            e.mp = e.mp + istr;
        }
    }
    else if (effect == EFF_STRUP) {
        if (ti == 0) p.str = p.str + istr;
        else e.str = e.str + istr;
    }
    else if (effect == EFF_DEFUP) {
        if (ti == 0) p.def = p.def + istr;
        else e.def = e.def + istr;
    }
    else if (effect == EFF_MAGUP) {
        if (ti == 0) p.mag = p.mag + istr;
        else e.mag = e.mag + istr;
    }
    else if (effect == EFF_WTDOWN) {
        if (ti == 0) p.max_wait = p.max_wait - istr;
        else e.max_wait = e.max_wait - istr;
    }
    else if (effect == EFF_HPREG) {
        if (ti == 0) p.hp_regen_time = p.hp_regen_time - istr;
        else e.hp_regen_time = e.hp_regen_time - istr;
    }
    else if (effect == EFF_MPREG) {
        if (ti == 0) p.mp_regen_time = p.mp_regen_time - istr;
        else e.mp_regen_time = e.mp_regen_time - istr;
    }
    else if (effect == EFF_ELV) {
        e.lv = e.lv + istr;
    }
    else if (effect == EFF_ELVBAL) {
        if (e.lv < p.lv) {
            if (p.lv - istr >= e.lv) e.lv = e.lv + istr;
            else e.lv = p.lv;
        }
        else {
            if (p.lv + istr <= e.lv) e.lv = e.lv - istr;
            else e.lv = p.lv;
        }
    }
    else early_termination("Unknown item effect.");
    ++stat_i_used;
}

/**
 * Checks the type of item being used.
 *
 * It calls the appropriate function based
 * on item type, then checks stats to make
 * sure item use hasn't made them out-of-bounds,
 * and finally removes one of the item.
 */
void use_item(int b, int toss) {
    if (inventory[b][INVEN_TYP] == 1) {
        item_effect(toss,inventory[b][INVEN_EFF],inventory[b][INVEN_STR]+inventory[b][INVEN_MOD]);
    }
    else if (inventory[b][INVEN_TYP] == 2) {
        if (toss == 0) equip_weapon(inventory[b][INVEN_DICE], inventory[b][INVEN_DICESIDES],\
         inventory[b][INVEN_CON], inventory[b][INVEN_AP], inventory[b][INVEN_WAIT],\
         inventory[b][INVEN_MOD], inventory[b][INVEN_ID]);
        else item_effect(toss,EFF_DAMAGE,(inventory[b][INVEN_DICE] * inventory[b][INVEN_DICESIDES])+inventory[b][INVEN_MOD]);
    }
    else if (inventory[b][INVEN_TYP] == 3) {
        if (toss == 0) equip_armor(inventory[b][INVEN_PAR],inventory[b][INVEN_AP]+inventory[b][INVEN_MOD],\
         inventory[b][INVEN_CON],inventory[b][INVEN_ID],inventory[b][INVEN_WAIT]);
        else item_effect(toss,EFF_DAMAGE,inventory[b][INVEN_AP] + inventory[b][INVEN_WAIT]+inventory[b][INVEN_MOD]);
    }

    if (p.hp > p.maxhp) p.hp = p.maxhp;
    if (p.mp > p.maxmp) p.mp = p.maxmp;
    if (p.str > STAT_MAX) p.str = STAT_MAX;
    if (p.def > STAT_MAX) p.def = STAT_MAX;
    if (p.mag > STAT_MAX) p.mag = STAT_MAX;
    if (p.wait > 9999) p.wait = 9999;
    if (p.max_wait < 100) p.max_wait = 100;
    if (p.hp_regen_time < 1) p.hp_regen_time = 1;
    if (p.mp_regen_time < 1) p.mp_regen_time = 1;
    if (e.lv < 1) e.lv = 1;
    if (e.lv > STAT_MAX) e.lv = STAT_MAX;

    inventory[b][INVEN_AMOUNT] = inventory[b][INVEN_AMOUNT] - 1;
    if (inventory[b][INVEN_AMOUNT] <= 0) {
        inventory[b][INVEN_ID] = 0;
        inventory[b][INVEN_AMOUNT] = 0;
        inventory[b][INVEN_MOD] = 0;
        inventory[b][INVEN_ADJ] = 0;
        inventory[b][INVEN_DICE] = 0;
        inventory[b][INVEN_DICESIDES] = 0;
        inventory[b][INVEN_AP] = 0;
        inventory[b][INVEN_WAIT] = 0;
        inventory[b][INVEN_MAXCON] = 0;
        inventory[b][INVEN_CON] = 0;
        inventory[b][INVEN_STR] = 0;
        inventory[b][INVEN_TYP] = 0;
        inventory[b][INVEN_PAR] = 0;
        inventory[b][INVEN_EFF] = 0;
    }
}

/**
 * Gives an item to the player.
 */
void give_item(int id, int typ, double mod, int adj, double dice, double dicesides,\
                double ap, int iwait, double maxcon, double con, double str, double eff,\
                int part) {

    int a,item_given = 0;

    if (typ == 1) { /* regular item */
        adj = 0;
        dice = 0;
        dicesides = 0;
        ap = 0;
        iwait = 0;
        maxcon = 0;
        con = 0;
        part = 0;
    }
    else if (typ == 2) { /* weapon */
        part = 0;
        eff = 0;
    }
    else if (typ == 3) { /* armor */
        dice = 0;
        dicesides = 0;
        eff = 0;
    }

    if (maxcon > ITEM_STAT_MAX) maxcon = ITEM_STAT_MAX;
    if (con > ITEM_STAT_MAX) con = ITEM_STAT_MAX;

    for (a = 0;a <= INVEN_MAX;++a) {
        if (inventory[a][INVEN_ID] == id && inventory[a][INVEN_AMOUNT] < 999 &&\
            inventory[a][INVEN_MOD] == mod && inventory[a][INVEN_ADJ] == adj &&\
            inventory[a][INVEN_DICE] == dice && inventory[a][INVEN_DICESIDES] == dicesides &&\
            inventory[a][INVEN_AP] == ap && inventory[a][INVEN_WAIT] == iwait && \
            inventory[a][INVEN_MAXCON] == maxcon && inventory[a][INVEN_CON] == con && item_given == 0) {
                /* most of this is unnecessary? */
                inventory[a][INVEN_ID] = id;
                inventory[a][INVEN_AMOUNT] = inventory[a][INVEN_AMOUNT] + 1;
                inventory[a][INVEN_MOD] = mod;
                inventory[a][INVEN_ADJ] = adj;
                inventory[a][INVEN_DICE] = dice;
                inventory[a][INVEN_DICESIDES] = dicesides;
                inventory[a][INVEN_AP] = ap;
                inventory[a][INVEN_WAIT] = iwait;
                inventory[a][INVEN_MAXCON] = maxcon;
                inventory[a][INVEN_CON] = con;
                inventory[a][INVEN_STR] = str;
                inventory[a][INVEN_EFF] = eff;
                inventory[a][INVEN_TYP] = typ;
                inventory[a][INVEN_PAR] = part;
                item_given = 1;
                break;
        }
    } /* No existing stacks of this item, check for empty slot to create one. */
    if (item_given == 0) {
        for (a = 0;a <= INVEN_MAX;++a) {
            if (inventory[a][INVEN_ID] == 0 && inventory[a][INVEN_AMOUNT] == 0) {
                inventory[a][INVEN_ID] = id;
                inventory[a][INVEN_AMOUNT] = 1;
                inventory[a][INVEN_MOD] = mod;
                inventory[a][INVEN_ADJ] = adj;
                inventory[a][INVEN_DICE] = dice;
                inventory[a][INVEN_DICESIDES] = dicesides;
                inventory[a][INVEN_AP] = ap;
                inventory[a][INVEN_WAIT] = iwait;
                inventory[a][INVEN_MAXCON] = maxcon;
                inventory[a][INVEN_CON] = con;
                inventory[a][INVEN_STR] = str;
                inventory[a][INVEN_EFF] = eff;
                inventory[a][INVEN_TYP] = typ;
                inventory[a][INVEN_PAR] = part;
                break;
            }
        }
    }
}

/**
 * Unequips an item.
 *
 * For now, the item is simply deleted.
 */
void unequip_item(int slot) {
    /** @todo
     * Give the unequipped item back.
     */
    if (slot == 1) {
        p.equip_id = 0;
        p.equip_ap = 0;
        p.equip_mod = 0;
        p.equip_wait = 0;
        p.dice = 1;
        p.dice_sides = 5;
        p.equip_maxcon = 0;
        p.equip_con = 0;
    }
    if (slot == 2) {
        p.head_id = 0;
        p.head_wait = 0;
        p.head_ap = 0;
        p.head_maxcon = 0;
        p.head_con = 0;
    }
    if (slot == 3) {
        p.body_id = 0;
        p.body_wait = 0;
        p.body_ap = 0;
        p.body_maxcon = 0;
        p.body_con = 0;
    }
    if (slot == 4) {
        p.legs_id = 0;
        p.legs_wait = 0;
        p.legs_ap = 0;
        p.legs_maxcon = 0;
        p.legs_con = 0;
    }
    if (slot == 5) {
        p.feet_id = 0;
        p.feet_wait = 0;
        p.feet_ap = 0;
        p.feet_maxcon = 0;
        p.feet_con = 0;
    }
    if (slot == 6) {
        p.hands_id = 0;
        p.hands_wait = 0;
        p.hands_ap = 0;
        p.hands_maxcon = 0;
        p.hands_con = 0;
    }
}

/**
 * The main loop for the item command.
 */
int item_main(WINDOW *w) {
    int ch,cho = 0,hl = 1,di = 0,ti = 0;
    
    while (cho == 0) {
        clean_sidebar(w);

        item_menu(w);

        mvwprintw(w,1,4,"Cancel");
        mvwprintw(w,hl,1,"-> ");

        if (hl >= 2) draw_item(w,hl - 2);

        box(w,0,0);
        refresh();
        ch = wgetch(w);
        switch (ch) {
            case KEY_DOWN:
                if (hl < 11) hl = hl + 1;
                else hl = 1;
                break;
            case KEY_UP:
                if (hl > 1) hl = hl - 1;
                else hl = 11;
                break;
            case 0x0A: /* Enter */
                cho = hl;
                di = 0;
                ti = 0;
                break;
            case 0x64: /* d */
                cho = hl;
                di = 1;
                ti = 0;
                break;
            case 0x74: /* t */
                cho = hl;
                di = 0;
                ti = 1;
                break;
            default:
                break;
        };
    }
    
    if (cho > 1 && di == 0) {
        if (inventory[cho - 2][0] == 0) cho = -1; /* if the slot chosen is empty. */
        else {
            use_item(cho - 2,ti);
        }
    }
    else if (cho > 1 && di == 1) {
        if (inventory[cho - 2][0] == 0) cho =- 1;
        else {
            inventory[cho - 2][INVEN_ID] = 0;
            inventory[cho - 2][INVEN_AMOUNT] = 0;
            inventory[cho - 2][INVEN_MOD] = 0;
            inventory[cho - 2][INVEN_ADJ] = 0;
            inventory[cho - 2][INVEN_DICE] = 0;
            inventory[cho - 2][INVEN_DICESIDES] = 0;
            inventory[cho - 2][INVEN_AP] = 0;
            inventory[cho - 2][INVEN_WAIT] = 0;
            inventory[cho - 2][INVEN_MAXCON] = 0;
            inventory[cho - 2][INVEN_CON] = 0;
            inventory[cho - 2][INVEN_STR] = 0;
            inventory[cho - 2][INVEN_TYP] = 0;
            inventory[cho - 2][INVEN_PAR] = 0;
            inventory[cho - 2][INVEN_EFF] = 0;
        }
    }
    if (cho == 1) cho = -1;
    
    return cho;
}

/**
 * The main loop for crafting.
 */
int craft_main(WINDOW *w) {
    int i,j,ch,cho = 0,hl = 1,pg;

    mvwprintw(w,4,1,"->");
    pg = 1;
    while (cho == 0) {
        clean_sidebar(w);
        j = 0;
        for (i = 0;i <= INVEN_MAX;++i) {
            if (inventory[i][INVEN_ID] == 0) ++j;
        }
        mvwprintw(w,1,4,"NUMBER OF EMPTY");
        mvwprintw(w,2,4,"INVENTORY SLOTS: %d; Page %d/%d",j,pg,CRAFT_PAGES);
        mvwprintw(w,3,4,"Press c to cancel");

        craft_menu(w,pg);

        for (i = 1;i <= 14;++i) {
            mvwprintw(w,i,1,"  ");
        }

        mvwprintw(w,hl + 3,1,"-> ");
        
        i = hl + ((pg - 1) * CRAFT_PER_PAGE);
        if (item_db[i].type == 1 && p.lv >= item_db[i].lv) {
            if (item_db[i].effect == EFF_HEALHP)
                mvwprintw(w,20,1,"Heals HP.");
            else if (item_db[i].effect == EFF_HEALMP)
                mvwprintw(w,20,1,"Heals MP.");
            else if (item_db[i].effect == EFF_DAMAGE)
                mvwprintw(w,20,1,"Causes damage.");
            else if (item_db[i].effect == EFF_HPUP)
                mvwprintw(w,20,1,"Permanent HP boost.");
            else if (item_db[i].effect == EFF_MPUP)
                mvwprintw(w,20,1,"Permanent MP boost.");
            else if (item_db[i].effect == EFF_STRUP)
                mvwprintw(w,20,1,"Permanent STR boost.");
            else if (item_db[i].effect == EFF_DEFUP)
                mvwprintw(w,20,1,"Permanent DEF boost.");
            else if (item_db[i].effect == EFF_MAGUP)
                mvwprintw(w,20,1,"Permanent MAG boost.");
            else if (item_db[i].effect == EFF_WTDOWN)
                mvwprintw(w,20,1,"Lowers Wait.");
            else if (item_db[i].effect == EFF_HPREG)
                mvwprintw(w,20,1,"Boosts HP regen.");
            else if (item_db[i].effect == EFF_MPREG)
                mvwprintw(w,20,1,"Boosts MP regen.");
            else if (item_db[i].effect == EFF_ELV)
                mvwprintw(w,20,1,"Modifies the enemy's level.");
            else if (item_db[i].effect == EFF_ELVBAL)
                mvwprintw(w,20,1,"Brings enemy's level towards your own.");
            else mvwprintw(w,20,1,"Unknown effect. %d",item_db[i].effect);
        }

        box(w,0,0);
        refresh();
        ch = wgetch(w);
        switch (ch) {
            case KEY_DOWN:
                if (hl == CRAFT_PER_PAGE && pg < CRAFT_PAGES) { /* Next page */
                    ++pg;
                    hl = 1;
                }
                else if (hl == CRAFT_PER_PAGE && pg == CRAFT_PAGES) { /* Top of list */
                    pg = 1;
                    hl = 1;
                }
                else ++hl; /* Move down */
                break;
            case KEY_UP:
                if (hl == 1 && pg > 1) { /* Previous page */
                    --pg;
                    hl = CRAFT_PER_PAGE;
                }
                else if (hl == 1 && pg == 1) { /* Bottom of list */
                    pg = CRAFT_PAGES;
                    hl = CRAFT_PER_PAGE;
                }
                else --hl; /* Move up */
                break;
            case 0x0A: /* Enter */
                cho = ((pg - 1) * CRAFT_PER_PAGE) + hl;
                if (cho >= item_max) cho = -1;
                break;
            case 0x63: /* c */
                cho = -1;
                break;
            default:
                break;
        };
    }

    if (cho != -1 && p.mp >= item_db[cho].cost && p.lv >= item_db[cho].lv) {
        get_adjval();
        p.mp = p.mp - item_db[cho].cost;
        if (roll_die(100) <= ((p.mag / item_db[cho].diff) * 100)) {
            struct Item it = item_db[cho];
            
            give_item(it.id,it.type,get_craft_mod(it.diff),item_adjval,it.dice + item_dice,\
            it.dice_sides + item_dicesides,it.ap + item_ap,it.wait + item_wait,it.condition * item_con,\
            it.condition * item_con,it.str,it.effect,it.body_part);
            
            award_sk_xp(SKILL_CRAFTING_GEN,max(1,(item_db[cho].cost / p.maxmp) * item_db[cho].diff));
            award_sk_xp(item_db[cho].skl,max(1,(item_db[cho].cost / p.maxmp) * item_db[cho].diff));
        }
    }
    else cho = -1;
    
    return cho;
}
