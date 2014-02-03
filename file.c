#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "item.h"
#include "globals.h"

void load_game() {
    int a;
    char *tok;
    FILE *save;

    refresh();
    save = fopen("./savefile","r");
    if (save == NULL) {
        reset_save();
        save = fopen("./savefile","r");
    }
    printw("Loading...\n");
    refresh();

    fscanf(save,"%s",f_buffer);
    tok = strtok(f_buffer,"=");
    tok = strtok(NULL,"=");
    if (atoi(tok) != SAVE_VERSION) {
        reset_save();
        early_termination("Save is no longer compatible; it will be reset.\nPlease restart The_Game.");
    }
    
    while (1) {
        for (a = 0;a <= 39;++a) f_buffer[a] = 32;
        fscanf(save,"%s",f_buffer);
        tok = strtok(f_buffer,"=");
        tok = strtok(NULL,"=");
        if (strcmp(f_buffer,"player:name") == 0) {
            for (a = 0;a <= 20;++a) {
                fscanf(save,"%s",f_buffer);
                tok = strtok(f_buffer,"=");
                tok = strtok(NULL,"=");
                p.name[a] = atoi(tok);
            }
        }
        else if (strcmp(f_buffer,"player:hp") == 0) p.hp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:maxhp") == 0) p.maxhp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:mp") == 0) p.mp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:maxmp") == 0) p.maxmp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:str") == 0) p.str = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:tou") == 0) p.tou = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:mag") == 0) p.mag = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:wait") == 0) p.wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:maxwait") == 0) p.max_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:bonusdamage") == 0) p.bonus_damage = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:equipid") == 0) p.equip_id = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:equipwait") == 0) p.equip_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:equipap") == 0) p.equip_ap = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:equipmaxcon") == 0) p.equip_maxcon = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:equipcon") == 0) p.equip_con = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:equipatk") == 0) p.equip_atk = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:headap") == 0) p.head_ap = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:bodyap") == 0) p.body_ap = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:legsap") == 0) p.legs_ap = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:feetap") == 0) p.feet_ap = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:handsap") == 0) p.hands_ap = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:headid") == 0) p.head_id = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:bodyid") == 0) p.body_id = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:legsid") == 0) p.legs_id = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:feetid") == 0) p.feet_id = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:handsid") == 0) p.hands_id = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:headwait") == 0) p.head_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:bodywait") == 0) p.body_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:legswait") == 0) p.legs_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:feetwait") == 0) p.feet_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:handswait") == 0) p.hands_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:headmaxcon") == 0) p.head_maxcon = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:bodymaxcon") == 0) p.body_maxcon = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:legsmaxcon") == 0) p.legs_maxcon = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:feetmaxcon") == 0) p.feet_maxcon = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:handsmaxcon") == 0) p.hands_maxcon = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:headcon") == 0) p.head_con = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:bodycon") == 0) p.body_con = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:legscon") == 0) p.legs_con = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:feetcon") == 0) p.feet_con = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:handscon") == 0) p.hands_con = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:statusid") == 0) p.status_id = atoi(tok);
        else if (strcmp(f_buffer,"player:statusdur") == 0) p.status_dur = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:statusstr") == 0) p.status_str = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:lv") == 0) p.lv = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:xp") == 0) p.xp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:nextxp") == 0) p.next_xp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:hpregentime") == 0) p.hp_regen_time = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:hpregencur") == 0) p.hp_regen_cur = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:hpregenamount") == 0) p.hp_regen_amount = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:mpregentime") == 0) p.mp_regen_time = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:mpregencur") == 0) p.mp_regen_cur = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:mpregenamount") == 0) p.mp_regen_amount = strtod(tok,NULL);
        else if (strcmp(f_buffer,"skills") == 0) {
            for (a = 0;a <= 12;strcmp(f_buffer,"NEXT") == 0 ? ++a : a) {
                fscanf(save,"%s",f_buffer);
                tok = strtok(f_buffer,"=");
                tok = strtok(NULL,"=");
                if (strcmp(f_buffer,"lv") == 0) skill[a][0] = atoi(tok);
                else if (strcmp(f_buffer,"xp") == 0) skill[a][1] = atoi(tok);
                else if (strcmp(f_buffer,"nextxp") == 0) skill[a][2] = atoi(tok);
            }
        }
        else if (strcmp(f_buffer,"player:species") == 0) p.species = strtod(tok,NULL);
        else if (strcmp(f_buffer,"player:class") == 0) p.pclass = strtod(tok,NULL);
        else if (strcmp(f_buffer,"items") == 0) {
            for (a = 0;a <= INVEN_MAX;strcmp(f_buffer,"NEXT") == 0 ? ++a : a) {
                fscanf(save,"%s",f_buffer);
                tok = strtok(f_buffer,"=");
                tok = strtok(NULL,"=");
                if (strcmp(f_buffer,"id") == 0) inv[a].id = atoi(tok);
                else if (strcmp(f_buffer,"amount") == 0) inv[a].amount = strtod(tok,NULL);
                else if (strcmp(f_buffer,"mod") == 0) inv[a].mod = strtod(tok,NULL);
                else if (strcmp(f_buffer,"adj") == 0) inv[a].adj = strtod(tok,NULL);
                else if (strcmp(f_buffer,"atk") == 0) inv[a].atk = strtod(tok,NULL);
                else if (strcmp(f_buffer,"ap") == 0) inv[a].ap = strtod(tok,NULL);
                else if (strcmp(f_buffer,"wait") == 0) inv[a].wait = atoi(tok);
                else if (strcmp(f_buffer,"maxcon") == 0) inv[a].maxcon = strtod(tok,NULL);
                else if (strcmp(f_buffer,"con") == 0) inv[a].con = strtod(tok,NULL);
                else if (strcmp(f_buffer,"str") == 0) inv[a].str = strtod(tok,NULL);
                else if (strcmp(f_buffer,"type") == 0) inv[a].type = atoi(tok);
                else if (strcmp(f_buffer,"part") == 0) inv[a].part = atoi(tok);
                else if (strcmp(f_buffer,"effect") == 0) inv[a].effect = strtod(tok,NULL);
            }
        }
        else if (strcmp(f_buffer,"enemy:name") == 0) strcpy(e.name,tok);
        else if (strcmp(f_buffer,"enemy:hp") == 0) e.hp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:maxhp") == 0) e.maxhp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:mp") == 0) e.mp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:maxmp") == 0) e.maxmp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:str") == 0) e.str = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:tou") == 0) e.tou = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:mag") == 0) e.mag = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:ap") == 0) e.ap = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:wait") == 0) e.wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:maxwait") == 0) e.max_wait = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:bonusdamage") == 0) e.bonus_damage = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:statusid") == 0) e.status_id = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:statusdur") == 0) e.status_dur = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:statusstr") == 0) e.status_str = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:lv") == 0) e.lv = strtod(tok,NULL);
        else if (strcmp(f_buffer,"enemy:xp") == 0) e.xp = strtod(tok,NULL);
        else if (strcmp(f_buffer,"stat:kills") == 0) stat_kills = strtod(tok,NULL);
        else if (strcmp(f_buffer,"stat:mcasts") == 0) stat_m_casts = strtod(tok,NULL);
        else if (strcmp(f_buffer,"stat:iused") == 0) stat_i_used = strtod(tok,NULL);
        else if (strcmp(f_buffer,"stat:damdealt") == 0) stat_p_dam_dealt = strtod(tok,NULL);
        else if (strcmp(f_buffer,"stat:damtaken") == 0) stat_p_dam_taken = strtod(tok,NULL);
        else if (strcmp(f_buffer,"game:pcreation") == 0) p_creation = atoi(tok);
        else if (strcmp(f_buffer,"game:turn") == 0) turn = strtod(tok,NULL);
        else if (strcmp(f_buffer,"game:wait") == 0) global_wait = atoi(tok);
        else if (strcmp(f_buffer,"END") == 0) break;
        
    }
    
    fclose(save);
}

void save_game() {
    int a,invslot = 0;

    FILE *save;

    save = fopen("./savefile","w");
    if (save == NULL) {
        early_termination("Could not open savefile.");
    }

    sprintf(f_buffer,"%d",SAVE_VERSION);
    fprintf(save,"version=%s\n",f_buffer);
    
    fprintf(save,"player:name=21\n");
    for (a = 0;a <= 20;++a) fprintf(save,"let%d=%d\n",a,p.name[a]);

    sprintf(f_buffer,"%.0f",p.hp);
    fprintf(save,"player:hp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.maxhp);
    fprintf(save,"player:maxhp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.mp);
    fprintf(save,"player:mp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.maxmp);
    fprintf(save,"player:maxmp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.str);
    fprintf(save,"player:str=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.tou);
    fprintf(save,"player:tou=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.mag);
    fprintf(save,"player:mag=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.wait);
    fprintf(save,"player:wait=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.max_wait);
    fprintf(save,"player:max_wait=%s\n",f_buffer);

    sprintf(f_buffer,"%.2f",p.bonus_damage);
    fprintf(save,"player:bonusdamage=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.equip_id);
    fprintf(save,"player:equipid=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.equip_wait);
    fprintf(save,"player:equipwait=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.equip_ap);
    fprintf(save,"player:equipap=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.equip_maxcon);
    fprintf(save,"player:equipmaxcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.equip_con);
    fprintf(save,"player:equipcon=%s\n",f_buffer);
    
    sprintf(f_buffer,"%.0f",p.equip_atk);
    fprintf(save,"player:equipatk=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.head_ap);
    fprintf(save,"player:headap=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.body_ap);
    fprintf(save,"player:bodyap=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.legs_ap);
    fprintf(save,"player:legsap=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.feet_ap);
    fprintf(save,"player:feetap=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.hands_ap);
    fprintf(save,"player:handsap=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.head_id);
    fprintf(save,"player:headid=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.body_id);
    fprintf(save,"player:bodyid=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.legs_id);
    fprintf(save,"player:legsid=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.feet_id);
    fprintf(save,"player:feetid=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.hands_id);
    fprintf(save,"player:handsid=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.head_wait);
    fprintf(save,"player:headwait=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.body_wait);
    fprintf(save,"player:bodywait=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.legs_wait);
    fprintf(save,"player:legswait=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.feet_wait);
    fprintf(save,"player:feetwait=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.hands_wait);
    fprintf(save,"player:handswait=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.head_maxcon);
    fprintf(save,"player:headmaxcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.body_maxcon);
    fprintf(save,"player:bodymaxcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.legs_maxcon);
    fprintf(save,"player:legsmaxcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.feet_maxcon);
    fprintf(save,"player:feetmaxcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.hands_maxcon);
    fprintf(save,"player:handsmaxcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.head_con);
    fprintf(save,"player:headcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.body_con);
    fprintf(save,"player:bodycon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.legs_con);
    fprintf(save,"player:legscon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.feet_con);
    fprintf(save,"player:feetcon=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.hands_con);
    fprintf(save,"player:handscon=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.status_id);
    fprintf(save,"player:statusid=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.status_dur);
    fprintf(save,"player:statusdur=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.status_str);
    fprintf(save,"player:statusstr=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.lv);
    fprintf(save,"player:lv=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.xp);
    fprintf(save,"player:xp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.next_xp);
    fprintf(save,"player:nextxp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.hp_regen_cur);
    fprintf(save,"player:hpregencur=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.hp_regen_time);
    fprintf(save,"player:hpregentime=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.hp_regen_amount);
    fprintf(save,"player:hpregenamount=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.mp_regen_cur);
    fprintf(save,"player:mpregencur=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.mp_regen_time);
    fprintf(save,"player:mpregentime=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",p.mp_regen_amount);
    fprintf(save,"player:mpregenamount=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",stat_kills);
    fprintf(save,"stat:kills=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",stat_m_casts);
    fprintf(save,"stat:mcasts=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",stat_i_used);
    fprintf(save,"stat:iused=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",stat_p_dam_dealt);
    fprintf(save,"stat:damdealt=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",stat_p_dam_taken);
    fprintf(save,"stat:damtaken=%s\n",f_buffer);

    fprintf(save,"skills=12\n");
    for (a = 0;a <= 12;++a) {
        sprintf(f_buffer,"%d",skill[a][0]);
        fprintf(save,"lv=%s\n",f_buffer);

        sprintf(f_buffer,"%d",skill[a][1]);
        fprintf(save,"xp=%s\n",f_buffer);

        sprintf(f_buffer,"%d",skill[a][2]);
        fprintf(save,"nextxp=%s\n",f_buffer);
        
        fprintf(save,"NEXT=0\n");
    }

    sprintf(f_buffer,"%d",p_creation);
    fprintf(save,"game:creation=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.species);
    fprintf(save,"player:species=%s\n",f_buffer);

    sprintf(f_buffer,"%d",p.pclass);
    fprintf(save,"player:class=%s\n",f_buffer);
    
    fprintf(save,"items=9\n");
    while (invslot <= INVEN_MAX) {
        sprintf(f_buffer,"%d",inv[invslot].id);
        fprintf(save,"id=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].amount);
        fprintf(save,"amount=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].mod);
        fprintf(save,"mod=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].adj);
        fprintf(save,"adj=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].atk);
        fprintf(save,"atk=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].ap);
        fprintf(save,"ap=%s\n",f_buffer);
        
        sprintf(f_buffer,"%d",inv[invslot].wait);
        fprintf(save,"wait=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].maxcon);
        fprintf(save,"maxcon=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].con);
        fprintf(save,"con=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].str);
        fprintf(save,"str=%s\n",f_buffer);
        
        sprintf(f_buffer,"%d",inv[invslot].type);
        fprintf(save,"type=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].part);
        fprintf(save,"part=%s\n",f_buffer);
        
        sprintf(f_buffer,"%.0f",inv[invslot].effect);
        fprintf(save,"effect=%s\n",f_buffer);
        
        fprintf(save,"NEXT=0\n");
        
        ++invslot;
    }
    
    sprintf(f_buffer,"%d",e.name[0]);
    fprintf(save,"enemy:name=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.hp);
    fprintf(save,"enemy:hp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.maxhp);
    fprintf(save,"enemy:maxhp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.mp);
    fprintf(save,"enemy:mp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.maxmp);
    fprintf(save,"enemy:maxmp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.str);
    fprintf(save,"enemy:str=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.tou);
    fprintf(save,"enemy:tou=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.mag);
    fprintf(save,"enemy:mag=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.ap);
    fprintf(save,"enemy:ap=%s\n",f_buffer);

    sprintf(f_buffer,"%d",e.wait);
    fprintf(save,"enemy:wait=%s\n",f_buffer);

    sprintf(f_buffer,"%d",e.max_wait);
    fprintf(save,"enemy:maxwait=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.bonus_damage);
    fprintf(save,"enemy:bonusdamage=%s\n",f_buffer);

    sprintf(f_buffer,"%d",e.status_id);
    fprintf(save,"enemy:statusid=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.status_dur);
    fprintf(save,"enemy:statusdur=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.status_str);
    fprintf(save,"enemy:statusstr=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.lv);
    fprintf(save,"enemy:lv=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",e.xp);
    fprintf(save,"enemy:xp=%s\n",f_buffer);

    sprintf(f_buffer,"%.0f",turn);
    fprintf(save,"game:turn=%s\n",f_buffer);

    sprintf(f_buffer,"%d",global_wait);
    fprintf(save,"game:wait=%s\n",f_buffer);
    
    fprintf(save,"END=0\n");

    fclose(save);
}

void reset_save() {
    int i;

    FILE *save;

    save = fopen("./savefile","w");

    fprintf(save,"version=%d\n",SAVE_VERSION);
    fprintf(save,"player:name=21\n");
    for (i = 0;i <= 21;++i) fprintf(save,"let%d=32\n",i);
    fprintf(save,"player:hp=20\n");
    fprintf(save,"player:maxhp=20\n");
    fprintf(save,"player:mp=20\n");
    fprintf(save,"player:maxmp=20\n");
    fprintf(save,"player:str=5\n");
    fprintf(save,"player:tou=5\n");
    fprintf(save,"player:mag=5\n");
    fprintf(save,"player:wait=0\n");
    fprintf(save,"player:maxwait=500\n");
    fprintf(save,"player:bonusdamage=0.00\n");
    fprintf(save,"player:equipid=6\n");
    fprintf(save,"player:equipwait=0\n");
    fprintf(save,"player:equipap=0\n");
    fprintf(save,"player:equipmaxcon=5000\n");
    fprintf(save,"player:equipcon=5000\n");
    fprintf(save,"player:equipatk=2\n");
    fprintf(save,"player:headap=1\n");
    fprintf(save,"player:bodyap=3\n");
    fprintf(save,"player:legsap=2\n");
    fprintf(save,"player:feetap=1\n");
    fprintf(save,"player:handsap=1\n");
    fprintf(save,"player:headid=9\n");
    fprintf(save,"player:bodyid=10\n");
    fprintf(save,"player:legsid=12\n");
    fprintf(save,"player:feetid=13\n");
    fprintf(save,"player:handsid=11\n");
    fprintf(save,"player:headwait=0\n");
    fprintf(save,"player:bodywait=0\n");
    fprintf(save,"player:legswait=0\n");
    fprintf(save,"player:feetwait=0\n");
    fprintf(save,"player:handswait=0\n");
    fprintf(save,"player:headmaxcon=300\n");
    fprintf(save,"player:bodymaxcon=425\n");
    fprintf(save,"player:legsmaxcon=200\n");
    fprintf(save,"player:feetmaxcon=110\n");
    fprintf(save,"player:handsmaxcon=120\n");
    fprintf(save,"player:headcon=300\n");
    fprintf(save,"player:bodycon=425\n");
    fprintf(save,"player:legscon=200\n");
    fprintf(save,"player:feetcon=110\n");
    fprintf(save,"player:handscon=120\n");
    fprintf(save,"player:statusid=0\n");
    fprintf(save,"player:statusdur=0\n");
    fprintf(save,"player:statusstr=0\n");
    fprintf(save,"player:lv=1\n");
    fprintf(save,"player:xp=0\n");
    fprintf(save,"player:nextxp=100\n");
    fprintf(save,"player:hpregentime=20\n");
    fprintf(save,"player:hpregencur=20\n");
    fprintf(save,"player:hpregenamount=1\n");
    fprintf(save,"player:mpregentime=20\n");
    fprintf(save,"player:mpregencur=20\n");
    fprintf(save,"player:mpregenamount=1\n");
    fprintf(save,"stat:kills=0\n");
    fprintf(save,"stat:mcasts=0\n");
    fprintf(save,"stat:iused=0\n");
    fprintf(save,"stat:damdealt=0\n");
    fprintf(save,"stat:damtaken=0\n");
    fprintf(save,"skills=12\n");
    for (i = 0;i <= 12;++i) {
        fprintf(save,"lv=0\n");
        fprintf(save,"xp=0\n");
        fprintf(save,"nextxp=100\n");
        fprintf(save,"NEXT=0\n");
    }
    fprintf(save,"game:creation=0\n");
    fprintf(save,"player:species=0\n");
    fprintf(save,"player:class=0\n");
    fprintf(save,"items=9\n");
    fprintf(save,"id=1\n");
    fprintf(save,"amount=5\n");
    fprintf(save,"mod=0\n");
    fprintf(save,"adj=0\n");
    fprintf(save,"atk=0\n");
    fprintf(save,"ap=0\n");
    fprintf(save,"wait=0\n");
    fprintf(save,"maxcon=0\n");
    fprintf(save,"con=0\n");
    fprintf(save,"str=%.0f\n",item_db[1].str);
    fprintf(save,"type=1\n");
    fprintf(save,"part=0\n");
    fprintf(save,"effect=%.0f\n",item_db[1].effect);
    fprintf(save,"NEXT=0\n");
    fprintf(save,"id=2\n");
    fprintf(save,"amount=5\n");
    fprintf(save,"mod=0\n");
    fprintf(save,"adj=0\n");
    fprintf(save,"atk=0\n");
    fprintf(save,"ap=0\n");
    fprintf(save,"wait=0\n");
    fprintf(save,"maxcon=0\n");
    fprintf(save,"con=0\n");
    fprintf(save,"str=%.0f\n",item_db[2].str);
    fprintf(save,"type=1\n");
    fprintf(save,"part=0\n");
    fprintf(save,"effect=%.0f\n",item_db[2].effect);
    fprintf(save,"NEXT=0\n");
    for (i = 0;i <= 8;++i) {
        fprintf(save,"id=0\n");
        fprintf(save,"amount=0\n");
        fprintf(save,"mod=0\n");
        fprintf(save,"adj=0\n");
        fprintf(save,"atk=0\n");
        fprintf(save,"ap=0\n");
        fprintf(save,"wait=0\n");
        fprintf(save,"maxcon=0\n");
        fprintf(save,"con=0\n");
        fprintf(save,"str=0\n");
        fprintf(save,"type=0\n");
        fprintf(save,"part=0\n");
        fprintf(save,"effect=0\n");
        fprintf(save,"NEXT=0\n");
    }
    fprintf(save,"enemy:name=0\n");
    fprintf(save,"enemy:hp=1\n");
    fprintf(save,"enemy:maxhp=1\n");
    fprintf(save,"enemy:mp=0\n");
    fprintf(save,"enemy:maxmp=0\n");
    fprintf(save,"enemy:str=10\n");
    fprintf(save,"enemy:tou=10\n");
    fprintf(save,"enemy:mag=10\n");
    fprintf(save,"enemy:ap=0\n");
    fprintf(save,"enemy:wait=500\n");
    fprintf(save,"enemy:maxwait=500\n");
    fprintf(save,"enemy:bonusdamage=0.00\n");
    fprintf(save,"enemy:statusid=0\n");
    fprintf(save,"enemy:statusdur=0\n");
    fprintf(save,"enemy:statusstr=0\n");
    fprintf(save,"enemy:lv=1\n");
    fprintf(save,"enemy:xp=1\n");
    fprintf(save,"game:turn=1\n");
    fprintf(save,"game:wait=0\n");
    fprintf(save,"END=0");

    fclose(save);
}
