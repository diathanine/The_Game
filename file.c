#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "file.h"
#include "item.h"
#include "globals.h"

void load_game() {
    int a,invslot = 0;
    FILE *save;

    refresh();
    save = fopen("./savefile","r");
    if (save == NULL) {
        reset_save();
        save = fopen("./savefile","r");
    }
    printw("Loading...\n");
    refresh();

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else if (atoi(p_buffer) != SAVE_VERSION) {
        reset_save();
        early_termination("Save is no longer compatible; it will be reset.\nPlease restart The_Game.");
    }
    
    for (a = 0;a < 21;++a) {
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else p.name[a] = atoi(p_buffer);
    }
    
    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hp = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.maxhp = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.mp = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.maxmp = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.str = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.def = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.mag = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.wait = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.max_wait = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.dice = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.dice_sides = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.bonus_damage = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.equip_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.equip_wait = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.equip_ap = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.equip_maxcon = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.equip_con = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.head_ap = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.body_ap = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.legs_ap = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.feet_ap = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hands_ap = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.head_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.body_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.legs_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.feet_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hands_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.head_wait = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.body_wait = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.legs_wait = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.feet_wait = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hands_wait = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.head_maxcon = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.body_maxcon = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.legs_maxcon = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.feet_maxcon = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hands_maxcon = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.head_con = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.body_con = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.legs_con = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.feet_con = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hands_con = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.status_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.status_dur = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.status_str = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.lv = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.xp = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.next_xp = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hp_regen_time = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hp_regen_cur = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.hp_regen_amount = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.mp_regen_time = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.mp_regen_cur = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.mp_regen_amount = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else stat_kills = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else stat_m_casts = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else stat_i_used = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else stat_p_dam_dealt = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else stat_p_dam_taken = strtod(p_buffer,NULL);

    for (a = 0;a <= 12;++a) {
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else skill[a][0] = atoi(p_buffer);

        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else skill[a][1] = atoi(p_buffer);

        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else skill[a][2] = atoi(p_buffer);
    }

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p_creation = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.species = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else p.pclass = atoi(p_buffer);
    
    while (invslot <= INVEN_MAX) {
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].id = atoi(p_buffer);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].amount = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].mod = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].adj = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].dice = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].dicesides = strtod(p_buffer,NULL);
        
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].ap = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].wait = atoi(p_buffer);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].maxcon = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].con = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].str = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].type = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].part = strtod(p_buffer,NULL);
    
        if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
        else inv[invslot].effect = strtod(p_buffer,NULL);
        ++invslot;
    }

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.name[0] = atoi(e_buffer);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.hp = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.maxhp = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.mp = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.maxmp = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.str = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.def = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.mag = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.ap = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else e.wait = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else e.max_wait = atoi(p_buffer);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.dice = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.dice_sides = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.bonus_damage = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else e.status_id = atoi(p_buffer);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else e.status_dur = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else e.status_str = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.lv = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",e_buffer) == 0) early_termination("Error reading savefile.");
    else e.xp = strtod(e_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else turn = strtod(p_buffer,NULL);

    if (fscanf(save,"%s",p_buffer) == 0) early_termination("Error reading savefile.");
    else global_wait = atoi(p_buffer);
    
    fclose(save);
}

void save_game() {
    int a,invslot = 0;

    FILE *save;

    save = fopen("./savefile","w");
    if (save == NULL) {
        early_termination("Could not open savefile.");
    }

    sprintf(p_buffer,"%d",SAVE_VERSION);
    fprintf(save,"%s\n",p_buffer);
    
    for (a = 0;a < 21;++a) {
        sprintf(p_buffer,"%d",p.name[a]);
        fprintf(save,"%s\n",p_buffer);
    }

    sprintf(p_buffer,"%.0f",p.hp);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.maxhp);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.mp);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.maxmp);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.str);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.def);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.mag);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.max_wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.dice);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.dice_sides);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.2f",p.bonus_damage);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.equip_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.equip_wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.equip_ap);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.equip_maxcon);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.equip_con);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.head_ap);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.body_ap);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.legs_ap);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.feet_ap);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.hands_ap);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.head_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.body_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.legs_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.feet_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.hands_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.head_wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.body_wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.legs_wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.feet_wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.hands_wait);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.head_maxcon);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.body_maxcon);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.legs_maxcon);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.feet_maxcon);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.hands_maxcon);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.head_con);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.body_con);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.legs_con);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.feet_con);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.hands_con);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.status_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.status_dur);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.status_str);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.lv);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.xp);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.next_xp);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.hp_regen_cur);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.hp_regen_time);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.hp_regen_amount);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.mp_regen_cur);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.mp_regen_time);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",p.mp_regen_amount);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",stat_kills);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",stat_m_casts);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",stat_i_used);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",stat_p_dam_dealt);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",stat_p_dam_taken);
    fprintf(save,"%s\n",p_buffer);

    for (a = 0;a <= 12;++a) {
        sprintf(p_buffer,"%d",skill[a][0]);
        fprintf(save,"%s\n",p_buffer);

        sprintf(p_buffer,"%d",skill[a][1]);
        fprintf(save,"%s\n",p_buffer);

        sprintf(p_buffer,"%d",skill[a][2]);
        fprintf(save,"%s\n",p_buffer);
    }

    sprintf(p_buffer,"%d",p_creation);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.species);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",p.pclass);
    fprintf(save,"%s\n",p_buffer);
    
    while (invslot <= INVEN_MAX) {
        sprintf(p_buffer,"%d",inv[invslot].id);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].amount);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].mod);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].adj);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].dice);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].dicesides);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].ap);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%d",inv[invslot].wait);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].maxcon);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].con);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].str);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].type);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].part);
        fprintf(save,"%s\n",p_buffer);
        
        sprintf(p_buffer,"%.0f",inv[invslot].effect);
        fprintf(save,"%s\n",p_buffer);
        
        ++invslot;
    }
    
    sprintf(e_buffer,"%d",e.name[0]);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.hp);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.maxhp);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.mp);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.maxmp);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.str);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.def);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.mag);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.ap);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%d",e.wait);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%d",e.max_wait);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.dice);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.dice_sides);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.bonus_damage);
    fprintf(save,"%s\n",e_buffer);

    sprintf(p_buffer,"%d",e.status_id);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",e.status_dur);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%.0f",e.status_str);
    fprintf(save,"%s\n",p_buffer);

    sprintf(e_buffer,"%.0f",e.lv);
    fprintf(save,"%s\n",e_buffer);

    sprintf(e_buffer,"%.0f",e.xp);
    fprintf(save,"%s\n",e_buffer);

    sprintf(p_buffer,"%.0f",turn);
    fprintf(save,"%s\n",p_buffer);

    sprintf(p_buffer,"%d",global_wait);
    fprintf(save,"%s\n",p_buffer);

    fprintf(save,"\n\n*** END ***");

    fclose(save);
}

void reset_save() {
    int i,invslot = 3;

    FILE *save;

    save = fopen("./savefile","w");

    fprintf(save,"%d\n",SAVE_VERSION);
    
    /* player */
    for (i = 0;i < 21;++i) {
        fprintf(save,"32\n");
    }

    fprintf(save,"20\n"); /* hp */
    fprintf(save,"20\n"); /* maxhp */
    fprintf(save,"20\n"); /* mp */
    fprintf(save,"20\n"); /* maxmp */
    fprintf(save,"5\n"); /* str */
    fprintf(save,"5\n"); /* def */
    fprintf(save,"5\n"); /* mag */
    fprintf(save,"0\n"); /* wait */
    fprintf(save,"500\n"); /* maxwait */
    fprintf(save,"1\n"); /* dice */
    fprintf(save,"5\n"); /* dice sides */
    fprintf(save,"0.00\n"); /* bonus damage */
    fprintf(save,"0\n"); /* equip ID */
    fprintf(save,"0\n"); /* equip wait */
    fprintf(save,"0\n"); /* equip ap */
    fprintf(save,"0\n"); /* equip maxcon */
    fprintf(save,"0\n"); /* equip con */
    fprintf(save,"0\n"); /* Head AP */
    fprintf(save,"0\n"); /* Body AP */
    fprintf(save,"0\n"); /* Legs AP */
    fprintf(save,"0\n"); /* Feet AP */
    fprintf(save,"0\n"); /* Hands AP */
    fprintf(save,"0\n"); /* Head ID */
    fprintf(save,"0\n"); /* Body ID */
    fprintf(save,"0\n"); /* Legs ID */
    fprintf(save,"0\n"); /* Feet ID */
    fprintf(save,"0\n"); /* Hands ID */
    fprintf(save,"0\n"); /* Head Wait */
    fprintf(save,"0\n"); /* Body Wait */
    fprintf(save,"0\n"); /* Legs Wait */
    fprintf(save,"0\n"); /* Feet Wait */
    fprintf(save,"0\n"); /* Hands Wait */
    fprintf(save,"0\n"); /* Head Maxcon */
    fprintf(save,"0\n"); /* Body Maxcon */
    fprintf(save,"0\n"); /* Legs Maxcon */
    fprintf(save,"0\n"); /* Feet Maxcon */
    fprintf(save,"0\n"); /* Hands Maxcon */
    fprintf(save,"0\n"); /* Head Con */
    fprintf(save,"0\n"); /* Body Con */
    fprintf(save,"0\n"); /* Legs Con */
    fprintf(save,"0\n"); /* Feet Con */
    fprintf(save,"0\n"); /* Hands Con */
    fprintf(save,"0\n"); /* status */
    fprintf(save,"0\n"); /* status dur */
    fprintf(save,"0\n"); /* status str */
    fprintf(save,"1\n"); /* lv */
    fprintf(save,"0\n"); /* xp */
    fprintf(save,"30\n"); /* next xp */
    fprintf(save,"20\n"); /* hp regen time */
    fprintf(save,"20\n"); /* hp regen current */
    fprintf(save,"1\n"); /* hp regen amount */
    fprintf(save,"20\n"); /* mp regen time */
    fprintf(save,"20\n"); /* mp regen current */
    fprintf(save,"1\n"); /* mp regen amount */
    fprintf(save,"0\n"); /* kills */
    fprintf(save,"0\n"); /* magic casts */
    fprintf(save,"0\n"); /* items used */
    fprintf(save,"0\n"); /* damage dealt */
    fprintf(save,"0\n"); /* damage taken */
    for (i = 0;i <= 12;++i) { /* skills */
        fprintf(save,"0\n");
        fprintf(save,"0\n");
        fprintf(save,"100\n");
    }
    fprintf(save,"0\n"); /* name done */
    fprintf(save,"0\n"); /* player species */
    fprintf(save,"0\n"); /* player class */
    /* inventory slots 1, 2, and 3 */
    fprintf(save,"1\n"); /* id */
    fprintf(save,"5\n"); /* amount */
    fprintf(save,"0\n"); /* mod */
    fprintf(save,"0\n"); /* adj */
    fprintf(save,"0\n"); /* dice */
    fprintf(save,"0\n"); /* dicesides */
    fprintf(save,"0\n"); /* ap */
    fprintf(save,"0\n"); /* wait */
    fprintf(save,"0\n"); /* maxcon */
    fprintf(save,"0\n"); /* con */
    fprintf(save,"%.0f\n",item_db[1].str); /* str */
    fprintf(save,"1\n"); /* typ */
    fprintf(save,"0\n"); /* par */
    fprintf(save,"%.0f\n",item_db[1].effect); /* eff */
    fprintf(save,"2\n"); /* id */
    fprintf(save,"5\n"); /* amount */
    fprintf(save,"0\n"); /* mod */
    fprintf(save,"0\n"); /* adj */
    fprintf(save,"0\n"); /* dice */
    fprintf(save,"0\n"); /* dicesides */
    fprintf(save,"0\n"); /* ap */
    fprintf(save,"0\n"); /* wait */
    fprintf(save,"0\n"); /* maxcon */
    fprintf(save,"0\n"); /* con */
    fprintf(save,"%.0f\n",item_db[2].str); /* str */
    fprintf(save,"1\n"); /* typ */
    fprintf(save,"0\n"); /* par */
    fprintf(save,"%.0f\n",item_db[2].effect); /* eff */
    fprintf(save,"1\n"); /* id */
    fprintf(save,"3\n"); /* amount */
    fprintf(save,"20\n"); /* mod */
    fprintf(save,"0\n"); /* adj */
    fprintf(save,"0\n"); /* dice */
    fprintf(save,"0\n"); /* dicesides */
    fprintf(save,"0\n"); /* ap */
    fprintf(save,"0\n"); /* wait */
    fprintf(save,"0\n"); /* maxcon */
    fprintf(save,"0\n"); /* con */
    fprintf(save,"%.0f\n",item_db[1].str); /* str */
    fprintf(save,"1\n"); /* typ */
    fprintf(save,"0\n"); /* par */
    fprintf(save,"%.0f\n",item_db[1].effect); /* eff */
    /* The other slots are empty!*/
    while (invslot <= INVEN_MAX) {
        for (i = 1;i <= 14;++i) fprintf(save,"0\n");
        ++invslot;
    }

    /* enemy */
    fprintf(save,"0\n"); /* enemy name */
    fprintf(save,"1\n"); /* hp */
    fprintf(save,"1\n"); /* maxhp */
    fprintf(save,"0\n"); /* mp */
    fprintf(save,"0\n"); /* maxmp */
    fprintf(save,"10\n"); /* str */
    fprintf(save,"10\n"); /* def */
    fprintf(save,"10\n"); /* mag */
    fprintf(save,"0\n"); /* ap */
    fprintf(save,"500\n"); /* wait */
    fprintf(save,"500\n"); /* maxwait */
    fprintf(save,"1\n"); /* dice */
    fprintf(save,"2\n"); /* dice sides */
    fprintf(save,"0\n"); /* bonus damage */
    fprintf(save,"0\n"); /* status */
    fprintf(save,"0\n"); /* status dur */
    fprintf(save,"0\n"); /* status str */
    fprintf(save,"1\n"); /* lv */
    fprintf(save,"1\n"); /* xp */

    /* general */
    fprintf(save,"1\n"); /* turn */
    fprintf(save,"0\n"); /* global wait */

    fprintf(save,"\n\n*** END ***");

    fclose(save);
}
