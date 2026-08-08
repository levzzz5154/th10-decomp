#include "th10/game/ui_final_runtime.hpp"
#include "th10/render/animation_manager.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

// Retail globals read/written by the 0x00414900 reconstruction below:
// the stage-front mode word (dword_491FB8), its mode-2 gate (dword_491FF4),
// the score source (dword_474C4C), the difficulty (dword_474C7C), the
// stage-progress counter (dword_474C84) and the game-state arena
// (dword_4776F4, play flag at +14220).
#ifdef _MSC_VER
extern "C" unsigned long dword_491FB8;
extern "C" unsigned long dword_491FF4;
extern "C" unsigned long dword_474C4C;
extern "C" unsigned long dword_474C7C;
extern "C" unsigned long dword_474C84;
extern "C" unsigned long dword_4776F4;
extern "C" unsigned long dword_474C68;
extern "C" unsigned long dword_474C6C;
extern "C" unsigned long dword_474C70;
extern "C" unsigned long dword_474C74;
extern "C" unsigned long dword_474CA0;
extern "C" unsigned long dword_474E5C;
extern "C" unsigned long dword_474E62;
extern "C" unsigned long dword_47770C;
extern "C" unsigned long dword_47783C;
extern "C" unsigned long dword_477830;
extern "C" unsigned long dword_477848;
extern "C" unsigned long dword_474C40;
extern "C" unsigned short word_474C48;
extern "C" unsigned long dword_491C28;
extern "C" float flt_476F78;
#define FRONT_MODE_WORD dword_491FB8
#define FRONT_MODE_GATE dword_491FF4
#define FRONT_SCORE dword_474C4C
#define FRONT_DIFFICULTY dword_474C7C
#define FRONT_PROGRESS dword_474C84
#define FRONT_GAME_STATE dword_4776F4
#else
extern unsigned int DAT_00491fb8;
extern unsigned int DAT_00491ff4;
extern unsigned int DAT_00474c4c;
extern unsigned int DAT_00474c7c;
extern unsigned int DAT_00474c84;
extern unsigned int DAT_00474c8c;
extern unsigned char* DAT_004776f4;  // host: the game-state arena pointer
extern unsigned int DAT_00474c68;
extern unsigned int DAT_00474c6c;
extern unsigned int DAT_00474c70;
extern unsigned int DAT_00474c74;
extern unsigned int DAT_00474ca0;
extern unsigned int DAT_00474e5c;
extern unsigned int DAT_00474e62;
extern unsigned char* DAT_0047770c;
extern unsigned char* DAT_00477704;
extern unsigned char* DAT_0047783c;
extern unsigned char* DAT_00477830;
extern unsigned char* DAT_00477848;
extern unsigned int DAT_00474c40;
extern unsigned short DAT_00474c48;
extern unsigned int DAT_00491c28;
extern float DAT_00476f78;
#define FRONT_MODE_WORD DAT_00491fb8
#define FRONT_MODE_GATE DAT_00491ff4
#define FRONT_SCORE DAT_00474c4c
#define FRONT_DIFFICULTY DAT_00474c7c
#define FRONT_PROGRESS DAT_00474c84
#define FRONT_GAME_STATE DAT_004776f4
#define FRAME_DELTA DAT_00476f78
#define SEQ_PROGRESS DAT_00474c84
#define SEQ_PLAYER_SLOT DAT_00477704
#define SEQ_DIFFICULTY DAT_00474c7c
#define SEQ_PROGRESS_OTHER DAT_00474c8c
#define SEQ_MODE_SELECT DAT_00474c68
#define SEQ_STAGE DAT_00474c6c
#define SEQ_RANK_BONUS DAT_00474c70
#define SEQ_CLEAR_MODE DAT_00474c74
#define SEQ_CLEAR_FLAGS DAT_00474ca0
#define SEQ_INPUT_FLAGS DAT_00474e5c
#define SEQ_INPUT_FLAGS_2 DAT_00474e62
#define SEQ_MANAGER_70C DAT_0047770c
#define SEQ_NOTICE_TABLE DAT_0047783c
#define SEQ_CLEAR_STATE DAT_00477830
#define SEQ_BGM_STATE DAT_00477848
#define SEQ_SCORE_BANK DAT_00474c40
#define SEQ_SCORE DAT_00474c4c
#define SEQ_GRAZE DAT_00474c48
#endif

namespace th10::ui_final {
// The sequence object's ramp state (retail seq+4/+8/+12/+16); the 0x00415E90
// reconstruction (UpdateStageSequence) owns the object - this mirror keeps the
// same layout so UpdateFront can advance it after a zero tick return.
struct SequenceState {
    int old_int;    // +0x04
    int frame_int;  // +0x08
    float acc;      // +0x0C
    float rate;     // +0x10
};

// Register an allocated object with the manager and return its handle
// (retail: the manual two-list insert + the manager's id counter).
static int register_handle(void* manager, void* obj) {
    return AnimationManager_RegisterObject(
        manager, (AnimationObject*)obj);
}
// 0x00409280 - QueueNotice: the score-notice queue entry. Retail flow:
// frame-ramp init (the +14132..+14148 fields, gated by bit 0 of +14148),
// the text copy (+14152) and slot store (+14216), the flags word (bits
// 3/4 cleared, then | 3), then - while the game state's +16 flag is not 1 -
// the notice-table text write (dword_47783C + 17276*(3*mode+stage) +
// 144*slot + 1444), the table count (99999-capped) and the per-slot text
// + count (also 99999-capped, +0x19A8C / +0x84). Then the 8+5 slot draws
// (sub_43E710, ids 58..65 / 66..70), three sprite registrations
// (sub_449950 + sub_449870 with ids 1/72/2 into the +1896/+1900/+1904
// handles), the text set (sub_447AE0, color 0xFFFFFF) + sound 14, the 417
// icon with the boss position copy (+4200) and attach (sub_449350), the
// 415/416 rank-child writes (+0x314 = value; retail-laid-out records only,
// same convention as the DrawOptions/DrawMain record walks), the score
// pair (10*score*(3*difficulty+10), cap 99999999), the 427 icon, and the
// difficulty rank-icon switch (sub_404F30 pairs into the +16/+956 slots,
// then sub_449870 + sub_4489D0).
void QueueNotice(Notice&n,const NoticeEnv&env,int slot,
                const std::string& text,int value){
  // 1. frame ramp init (retail: gated by bit 0 of +14148)
  if((n.flags&1)==0){
    n.frame_counter=0;
    n.frame_target_minus1=-999999;
    n.frame_float=0.0f;
    n.frame_delta=&FRAME_DELTA;
    n.flags|=1;
  }
  n.frame_counter=0;
  n.frame_float=0.0f;
  n.frame_target_minus1=-1;
  n.slot=slot;
  n.text=text;
  n.flags=(n.flags&~0x1Bu)|3u;
  // 2. notice-table writes (gated by the game-state +16 flag)
  if(!(env.game_state&&((unsigned char*)env.game_state)[16]==1)){
    if(SEQ_NOTICE_TABLE){
      char* base=(char*)SEQ_NOTICE_TABLE
        + 34552*SEQ_MODE_SELECT + 17276*SEQ_MODE_SELECT + 17276*SEQ_STAGE
        + 144*slot;
      strcpy(base+1444,text.c_str());
      // retail: the count sits at the text offset +0x84 (base+1444+132)
      int* count=(int*)(base+1444+132);
      if(*count<99999)++*count;
      // the per-slot text copy + its 99999-capped count (+132).
      // Retail (asm 0x0040938F): LEA ESI,[EAX + EBX*1 + 0x19A8C] with
      // EAX=slot*144, EBX=DAT_0047783C — relative to the TABLE, with NO
      // mode/stage term (unlike the first text at base+0x5A4).
      char* slot_text=(char*)SEQ_NOTICE_TABLE + 144*slot + 0x19A8C;
      strcpy(slot_text,text.c_str());
      int* slot_count=(int*)(slot_text+132);
      if(*slot_count<99999)++*slot_count;
    }
  }
  // 3. the 8+5 slot draws (ids 58..65, 66..70)
  if(env.tick_slot){
    for(int i=0;i<8;++i)env.tick_slot(i,i+58);
    for(int i=0;i<5;++i)env.tick_slot(8+i,i+66);
  }
  // 4. the three sprite registrations (ids 1/72/2)
  if(env.allocate_object&&env.init_object){
    const int sprites[3]={1,72,2};
    const void* banks[3]={env.bank_a,env.bank_b,env.bank_a};
    for(int i=0;i<3;++i){
      void* obj=env.allocate_object(env.manager);
      if(obj){
        ((unsigned int*)obj)[215]|=0x40000000u;
        ((int*)obj)[8]=15;
        env.init_object(obj,(void*)banks[i],sprites[i]);
        n.handles[i]=register_handle(env.manager,obj);
      }
    }
  }
  // 5. text set on the 72 sprite + sound 14 (retail: find by the +1900
  // handle, zero the slot on failure, then sub_447AE0 + sub_43DC90(14))
  if(env.find_object){
    void* obj=env.find_object(n.handles[1]);
    if(!obj)n.handles[1]=0;
    else if(env.text_set)env.text_set(obj,0xFFFFFF,n.text.c_str());
  }
  if(env.queue_sound)env.queue_sound(14);
  // 6. the 417 rank icon + boss position copy + attach
  if(env.allocate_object&&env.init_object){
    void* obj=env.allocate_object(env.manager);
    if(obj){
      ((unsigned int*)obj)[215]|=0x40000000u;
      ((int*)obj)[8]=15;
      env.init_object(obj,env.bank_b,417);
      n.handles[3]=register_handle(env.manager,obj);
      if(env.player_slot){
        void* boss=((void**)env.player_slot)[4];
        if(boss){
          const float* src=(const float*)((char*)boss+4200);
          n.boss_pos[0]=src[0];n.boss_pos[1]=src[1];n.boss_pos[2]=src[2];
          if(env.attach_position)
            env.attach_position(obj,n.boss_pos.data());
        }
      }
    }
  }
  // 7. the 415/416 rank-child writes (+0x314 = the rank value on the child
  // records) + the +14232 rank store.  Retail re-resolves the 417 object
  // by its +1908 handle (zeroing the slot on failure), walks the child
  // list for tag 415 (0x19F) and writes value to record+0x314, then repeats
  // for tag 416 (0x1A0); the +14232 store is unconditional.  The child
  // walk uses the file's record convention (AnimationManager_FindChildByScriptIndex
  // + AnimationManager_Find on retail-laid-out records, same as the
  // DrawOptions/DrawMain record resolution); with a null manager the write
  // is elided and only the rank mirror remains.
  n.rank=value;  // +14232 (retail: unconditional)
  if(n.handles[3]!=0&&env.manager!=0){
    // retail: the parent find failure zeroes the +1908 slot; a child-walk
    // miss keeps the slot and the write (retail writes to low memory - the
    // host elides it)
    if(AnimationManager_Find(env.manager,n.handles[3])==0){
      n.handles[3]=0;
    }else{
      int child=AnimationManager_FindChildByScriptIndex(
          env.manager,n.handles[3],(short)415);
      if(child!=0)
        if(unsigned char* rec=(unsigned char*)AnimationManager_Find(env.manager,child))
          *(int*)(rec+0x314)=value;  // retail: child record +788 = value
    }
  }
  if(n.handles[3]!=0&&env.manager!=0){
    if(AnimationManager_Find(env.manager,n.handles[3])==0){
      n.handles[3]=0;
    }else{
      int child=AnimationManager_FindChildByScriptIndex(
          env.manager,n.handles[3],(short)416);
      if(child!=0)
        if(unsigned char* rec=(unsigned char*)AnimationManager_Find(env.manager,child))
          *(int*)(rec+0x314)=value;  // retail: child record +788 = value
    }
  }
  // 8. the score pair
  n.score=10*SEQ_SCORE*(3*(int)SEQ_DIFFICULTY+10);
  n.score_capped=n.score>=100000000?99999999:n.score;
  // 9. the 427 icon
  if(env.allocate_object&&env.init_object){
    void* obj=env.allocate_object(env.manager);
    if(obj){
      ((unsigned int*)obj)[215]|=0x40000000u;
      ((int*)obj)[8]=15;
      env.init_object(obj,env.bank_b,427);
      register_handle(env.manager,obj);
    }
  }
  // 10. the difficulty rank-icon switch (sub_404F30 pairs + the final
  //     sub_449870/sub_4489D0 registration)
  if(env.register_icon&&env.allocate_object&&env.init_object){
    void* bank=env.player_slot?((void**)env.player_slot)[14]:nullptr;
    int v84=15;
    const int difficulty=(int)SEQ_DIFFICULTY;
    if(difficulty==1){
      env.register_icon(12,n.handles[3]?n.handles[3]:0,0,bank);
      env.register_icon(11,0,1,bank);
      v84=n.slot<2?15:14;
    }else if(difficulty==2){
      env.register_icon(14,n.handles[3]?n.handles[3]:0,0,bank);
      env.register_icon(15,0,1,bank);
      v84=17;
    }else if(difficulty==3){
      env.register_icon(18,0,0,bank);
      env.register_icon(19,0,1,bank);
      v84=21;
    }else if(difficulty==4){
      env.register_icon(19,0,0,bank);
      env.register_icon(20,0,1,bank);
      v84=22;
    }else if(difficulty==5){
      env.register_icon(12,n.handles[3]?n.handles[3]:0,0,bank);
      env.register_icon(13,0,1,bank);
      v84=15;
    }else if(difficulty==6){
      env.register_icon(33,0,0,bank);
      env.register_icon(34,0,1,bank);
      v84=36;
    }else if(difficulty==7){
      if(SEQ_PROGRESS>=24){
        env.register_icon(27,0,0,bank);
        env.register_icon(28,0,1,bank);
        v84=30;
      }else{
        env.register_icon(38,0,0,bank);
        v84=40;
      }
    }else{
      return;
    }
    void* obj=env.allocate_object(env.manager);
    if(obj){
      ((unsigned int*)obj)[215]|=0x40000000u;
      ((int*)obj)[8]=15;
      env.init_object(obj,bank,v84);
      if(env.register_text)env.register_text(obj);
    }
  }
}
// 0x00414900 - UpdateFront: the stage-front HUD tick. The retail flow, in
// order (a1 offsets from the hpp map):
//   1. Flag-gated transition timer (bit 0x10 of +40628): once it reaches 120
//      the global mode word dword_491FB8 = (dword_491FF4 & 0x1000) ? 2 : 14.
//   2. 15 ANM slot ticks: 9 at +18816, 4 at +27276, 2 at +31036 (stride 940).
//   3. Player-position gates (dword_477834 floats +240/+241): the bit-0 state
//      writes 2 into the +33688[7] words (stride 470) when the player is far,
//      the clear state writes 3 when the player is close, toggling bit 0.
//   4. Score digits: dword_474C4C divided by 10000..1 - each of the five
//      +33856 slots is preloaded with digit+30 then ticked.
//   5. Boss gauge (+40580/+40584/+40588): hp/max ratio from the boss object
//      (player_slot[4], +9212/+9216), display ramp +0.025/frame.
//   6. Boss-name/boss-id ANM objects: bit 8 of +40628 selects the stop frame
//      (2 far / 3 near); the registered ids (+40488[10], count +40592) and the
//      name id (+40484) are stopped, then re-armed: the name sprite is the
//      difficulty switch 133..140, the ids are slot+91 - each allocated via
//      sub_449950, initialized via sub_449870 and registered (the manager's
//      id counter).
//   7. The sequence object (+40632) is ticked via sub_415E90; on its non-zero
//      return the six ANM handles (+16..+21) are flagged 0x04000000 and the
//      object freed.
//   8. Lives/graze HUD (+40640 vs +40644): the +31808/+32748 words become
//      7/8/9 with sounds 27/36, and the two +31036/+31976 digit slots are
//      preloaded with lives/10+8 and lives%10+8.
//   9. Rank word (+40268, 7..10): gated by the boss's flag word (+9344) and
//      the game-state play flag (dword_4776F4 + 14220), thresholds
//      2000/1000/400 (playing) or 700/400/200; then the boss-position sprite
//      (+40328 = boss x + 224.0, +40332 = 480.0) and the proximity alpha
//      (+40263 = 64 - |dx|*2.984375, clamped, 0 when the boss is off-screen).
//   10. Fade ramp (+40544..+40556): the int/float pair advances by the rate
//       unless the rate is inside (0.99, 1.01), in which case it steps +1.
// Slot indices for the env follow the retail visit order (see the hpp).
int UpdateFront(FrontTick&s,const FrontEnv&env){
  // 1. transition timer (retail: +40652 incremented while +40628 bit 0x10)
  if(s.flags&0x10){
    ++s.timer;
    if(s.timer>=120){  // retail 0x77 < v1 fires for v1 >= 120
      const int next=(FRONT_MODE_GATE&0x1000)!=0?2:14;
      FRONT_MODE_WORD=next;
      s.mode=next;
    }
  }
  // 2. ANM slot ticks: 9/4/2 loops (stride 940)
  if(env.tick_slot){
    for(int i=0;i<9;++i)env.tick_slot(i);
    for(int i=9;i<13;++i)env.tick_slot(i);
    for(int i=13;i<15;++i)env.tick_slot(i);
  }
  // 3. player-position word writes (+33688[7], stride 470)
  if(env.player){
    if(s.flags&1){
      if(((float*)env.player)[241]<400.0f||((float*)env.player)[240]>-112.0f){
        for(auto&w:s.position_words)w=2;
        s.flags&=~1u;
      }
    }else if(((float*)env.player)[241]>416.0f&&((float*)env.player)[240]<-128.0f){
      for(auto&w:s.position_words)w=3;
      s.flags|=1u;
    }
  }
  // 4. score digits (dword_474C4C, five slots at +33856, base +30)
  if(env.tick_slot&&env.preload_sprite){
    env.tick_slot(15);
    int value=(int)FRONT_SCORE;
    int divisor=10000;
    for(int i=0;i<5;++i){
      const int digit=value/divisor;
      value%=divisor;
      env.preload_sprite(16+i,digit+30,s.bank);
      env.tick_slot(16+i);
      divisor/=10;
    }
  }
  env.tick_slot&&env.tick_slot(21);
  // 5. boss gauge (+40580/+40584/+40588): retail splits on
  // player_slot==0 || boss==0 || sequence!=0 (the inactive path stops the
  // boss-name object at depth 1, clears its handle and zeroes the gauge)
  {
    void* boss=env.player_slot?((void**)env.player_slot)[4]:nullptr;
    if(boss&&!s.sequence){
      const int hp=((int*)boss)[9212/4];
      const int max_hp=((int*)boss)[9216/4];
      s.boss_hp=hp;
      s.boss_ratio=max_hp!=0?(float)hp/(float)max_hp:0.0f;
      if(s.boss_ratio>s.boss_disp)s.boss_disp+=0.025f;
      if(s.boss_disp>s.boss_ratio)s.boss_disp=s.boss_ratio;
      // 6. boss-name/boss-id object walk (bit 8 state); the retail reads
      // dword_477834 unconditionally - the host env may omit the player
      if(env.player&&env.find_object&&env.stop_object_tree){
        const float px=((float*)env.player)[240];
        const float py=((float*)env.player)[241];
        if(s.flags&8){
          if(!(py<80.0f&&px<=0.0f)){
            for(int i=0;i<s.boss_id_count;++i)
              if(void* obj=env.find_object(s.boss_ids[i]))env.stop_object_tree(obj,2);
            if(void* obj=env.find_object(s.boss_name_id))env.stop_object_tree(obj,2);
            s.flags&=~8u;
          }
        }else if(py<64.0f&&px<-64.0f){
          for(int i=0;i<s.boss_id_count;++i)
            if(void* obj=env.find_object(s.boss_ids[i]))env.stop_object_tree(obj,3);
          if(void* obj=env.find_object(s.boss_name_id))env.stop_object_tree(obj,3);
          s.flags|=8u;
        }
      }
      // re-arm: the name object (difficulty switch 133..140) when absent
      if(!s.boss_name_id&&env.allocate_object&&env.init_object){
        int sprite=133;
        bool do_alloc=true;
        switch((int)FRONT_DIFFICULTY){
          case 1:sprite=FRONT_PROGRESS>=24?134:133;break;
          case 2:if(FRONT_PROGRESS>=24)sprite=135;else do_alloc=false;break;
          case 3:if(FRONT_PROGRESS>=24)sprite=136;else do_alloc=false;break;
          case 4:sprite=FRONT_PROGRESS>=24?138:137;break;
          case 5:sprite=139;break;
          case 6:sprite=140;break;
          case 7:sprite=FRONT_PROGRESS>=24?141:140;break;
          default:break;
        }
        // retail LABEL_114def: difficulties 2/3 with progress < 24 skip the
        // allocation entirely (goto LAB_114f33); the rest allocate 133..141
        if(do_alloc){
          if(void* obj=env.allocate_object(env.manager)){
            ((unsigned int*)obj)[215]|=0x40000000u;
            ((int*)obj)[8]=15;
            env.init_object(obj,s.bank,sprite);
            s.boss_name_id=register_handle(env.manager,obj);
          }
        }
      }
      // re-arm the id slots: fill empty slots with sprite slot+91; stop and
      // clear ids at/after the count (retail LABEL_115 loop)
      if(env.allocate_object&&env.init_object){
        for(int i=0;i<10;++i){
          if(i<s.boss_id_count){
            if(!s.boss_ids[i]){
              if(void* obj=env.allocate_object(env.manager)){
                ((unsigned int*)obj)[215]|=0x40000000u;
                ((int*)obj)[8]=15;
                env.init_object(obj,s.bank,i+91);
                s.boss_ids[i]=register_handle(env.manager,obj);
              }
            }
          }else{
            if(s.boss_ids[i]){
              if(void* obj=env.find_object(s.boss_ids[i]))env.stop_object_tree(obj,1);
              s.boss_ids[i]=0;
            }
          }
        }
      }
    }else{
      // retail inactive path (LAB_150cf..LAB_1510a): stop the boss-name
      // object at depth 1, clear its handle, zero the gauge (+40580; the
      // +40596/+40604/+40612/+40620 zero writes have no host mirror)
      if(s.boss_name_id){
        if(env.find_object&&env.stop_object_tree)
          if(void* obj=env.find_object(s.boss_name_id))env.stop_object_tree(obj,1);
        s.boss_name_id=0;
      }
      s.boss_disp=0;
    }
  }
  // 7. sequence object tick (sub_415E90) + teardown
  if(s.sequence){
    if(!env.tick_sequence||!env.tick_sequence(s.sequence)){
      // retail zero return: the sequence's own ramp (seq+4/+8/+12/+16)
      // advances; +12 is an int field truncated every tick
      SequenceState* seq=(SequenceState*)s.sequence;
      seq->old_int=seq->frame_int;
      if(seq->rate<=0.99000001f||seq->rate>=1.01f){
        const int v=(int)(seq->rate+seq->acc);
        seq->acc=(float)v;  // retail: seq+12 = ftol(rate + acc)
        seq->frame_int=v;
      }else{
        seq->frame_int=seq->old_int+1;
        seq->acc+=1.0f;
      }
    }else{
      // teardown: flag the six ANM handles 0x04000000, clear, free
      if(env.find_object&&env.set_flag_tree){
        int* handles=(int*)((char*)s.sequence+64);
        for(int i=0;i<6;++i){
          if(void* obj=env.find_object(handles[i]))
            env.set_flag_tree(obj,0x04000000u);
          handles[i]=0;
        }
      }
      free(s.sequence);
      s.sequence=nullptr;
    }
  }
  // 8. lives/graze HUD words + sounds + digit preloads
  if(env.player_slot){
    void* boss=((void**)env.player_slot)[4];
    if(s.lives>=0&&boss&&!s.sequence){
      if(s.lives>=s.graze_disp){
        if(s.lives>s.graze_disp){s.lives_words[0]=7;s.lives_words[1]=7;}
      }else if(s.lives>5){
        if(s.lives<=10){
          s.lives_words[0]=8;s.lives_words[1]=8;
          if(env.queue_sound)env.queue_sound(27);
        }
      }else{
        s.lives_words[0]=9;s.lives_words[1]=9;
        if(env.queue_sound)env.queue_sound(36);
      }
      if(s.lives!=s.graze_disp){
        if(env.preload_sprite){
          env.preload_sprite(13,s.lives/10+8,s.bank);
          env.preload_sprite(14,s.lives%10+8,s.bank);
        }
        s.graze_disp=s.lives;
      }
    }
    // 9. rank word + boss-position sprite + proximity alpha (retail: the
    // whole block is gated by the boss's flag word +9344, bits 4/0 clear;
    // the rank writes happen only when the rank crosses the threshold -
    // mode 3 resets (word 10, mode bits cleared) only when rank EXCEEDS
    // the threshold, per the shared LAB_156ba comparison)
    if(boss){
      const unsigned int boss_flags=((unsigned int*)boss)[9344/4];
      if(!((boss_flags>>4)&1u)&&!(boss_flags&1u)){
        const int mode=(s.flags>>1)&3;
        const int rank=((int*)boss)[9220/4];
        const bool playing=FRONT_GAME_STATE!=0&&(FRONT_GAME_STATE[14220]&1)!=0;
        if(mode==0){
          if(rank<(playing?2000:700)){
            s.rank_word=7;
            s.flags=(s.flags&~6u)|2u;
          }
        }else if(mode==1){
          if(rank<(playing?1000:400)){
            s.rank_word=8;
            s.flags=(s.flags&~6u)|4u;
          }
        }else if(mode==2){
          if(rank<(playing?400:200)){
            s.rank_word=9;
            s.flags=(s.flags&~6u)|6u;
          }
        }else{
          if(rank>(playing?400:200)){
            s.rank_word=10;
            s.flags&=~6u;
          }
        }
        // retail LAB_156ce (inside the gate): slot-22 tick, the boss
        // position sprite (+40328 = boss_x+224.0, +40332 = 480.0) and the
        // proximity alpha (+40263).  The alpha is 64 - (char)ftol(|dx| *
        // -2.984375) = 64 + trunc(|dx|*2.984375) for |dx| < 64, else 0xFF.
        if(env.tick_slot)env.tick_slot(22);
        const float boss_x=((float*)boss)[4200/4];
        s.boss_pos[0]=boss_x+224.0f;
        s.boss_pos[1]=480.0f;
        if(env.player){
          const float dx=fabsf(boss_x-((float*)env.player)[240]);
          if(dx<64.0f)s.rank_alpha=(uint8_t)(64+(unsigned long long)(dx*2.984375f));
          else s.rank_alpha=(uint8_t)-1;
        }
        if(boss_x<-192.0f||boss_x>192.0f)s.rank_alpha=0;
      }
    }
  }
  // 10. fade ramp (+40544..+40556)
  s.fade_int=s.fade_old;
  if(s.fade_rate<=0.99000001f||s.fade_rate>=1.01f){
    s.fade_acc+=s.fade_rate;
    s.fade_old=(int)s.fade_acc;
    s.fade_int=s.fade_old;
  }else{
    s.fade_old=s.fade_old+1;
    s.fade_acc+=1.0f;
    s.fade_int=s.fade_old;
  }
  s.transition=(s.flags&0x10)!=0;
  return 1;
}
// Retail 0x00415E90 case 0x14: the stage-clear score write. The
// multiplier ladder (dword_474C40 += 1000*dword_474C4C plus the rank/grazing
// bonuses) and the notice-table byte writes (dword_47783C + the
// mode/stage/difficulty index) are retail-exact; the sub_423370 clear
// transition, the sub_43C8B0 clear sound, the sub_40AC90 setup and the
// sub_4175E0 clear-text reset route through the env hooks.
static void stage_clear_score_block(StageSequence& s, const SequenceEnv& env,
                                    const unsigned char* cmd) {
    (void)s;
    (void)cmd;
    if ((int)SEQ_CLEAR_MODE != 4 && SEQ_NOTICE_TABLE) {
        unsigned char* base = (unsigned char*)SEQ_NOTICE_TABLE
            + 34552 * SEQ_MODE_SELECT + 17276 * SEQ_MODE_SELECT
            + 17276 * SEQ_STAGE + 48 * SEQ_CLEAR_MODE + 8 * (int)SEQ_DIFFICULTY;
        base[1249] = 1;
        base[1248] = 1;
    }
    if ((SEQ_CLEAR_FLAGS & 0x10) != 0) {
        if (env.stage_clear)
            env.stage_clear((void*)(uintptr_t)SEQ_CLEAR_MODE, SEQ_CLEAR_STATE);
        return;
    }
    const int rank_bonus = (int)SEQ_RANK_BONUS;
    const int graze = (int)SEQ_GRAZE;
    const int clear_mode = (int)SEQ_CLEAR_MODE;
    // retail: only the non-clear-done extra/last-stage paths reach the
    // +1232 notice-table counter increment
    bool count_clear = false;
    if ((int)SEQ_DIFFICULTY == 6) {
        // retail: the front flag word +40628 bit 0x20 set before the adds
        if (SEQ_MANAGER_70C)
            *(unsigned int*)(SEQ_MANAGER_70C + 0x9eb4) |= 0x20u;
        if (env.score_add) {
            env.score_add((int*)&SEQ_SCORE_BANK, 1000 * (int)SEQ_SCORE);
            switch (clear_mode) {
                case 0: env.score_add((int*)&SEQ_SCORE_BANK, 20000000 * rank_bonus);
                        env.score_add((int*)&SEQ_SCORE_BANK, 100000 * graze); break;
                case 1: env.score_add((int*)&SEQ_SCORE_BANK, 25000000 * rank_bonus);
                        env.score_add((int*)&SEQ_SCORE_BANK, 100000 * graze); break;
                case 2: env.score_add((int*)&SEQ_SCORE_BANK, 35000000 * rank_bonus);
                        env.score_add((int*)&SEQ_SCORE_BANK, 200000 * graze); break;
                case 3: env.score_add((int*)&SEQ_SCORE_BANK, 40000000 * rank_bonus);
                        env.score_add((int*)&SEQ_SCORE_BANK, 300000 * graze); break;
                case 4: env.score_add((int*)&SEQ_SCORE_BANK, 40000000 * rank_bonus);
                        env.score_add((int*)&SEQ_SCORE_BANK, 400000 * graze); break;
                default: break;
            }
        }
        if (env.clear_done && env.clear_done()) {
            if (env.setup_clear) env.setup_clear(4);
        } else {
            if (env.clear_sound) env.clear_sound();
            if (env.clear_notify) env.clear_notify();  // +40652 = 0, +40628 |= 0x10
            count_clear = true;
        }
    } else if ((int)SEQ_DIFFICULTY != 7) {
        if (env.clear_anim) env.clear_anim();
        if (env.alloc_sprite) {
            void* bank = (SEQ_MANAGER_70C
                ? (void*)((uintptr_t*)SEQ_MANAGER_70C)[10162] : nullptr);
            env.alloc_sprite(bank, 76);
        }
        if (env.setup_clear) env.setup_clear(11);
        if (env.clear_text) env.clear_text();
    } else {
        // retail difficulty 7: +40628 |= 0x20 first, then the adds; the
        // non-clear-done path calls sub_423370 only (no +40628/+40652 writes)
        if (SEQ_MANAGER_70C)
            *(unsigned int*)(SEQ_MANAGER_70C + 0x9eb4) |= 0x20u;
        if (env.score_add) {
            env.score_add((int*)&SEQ_SCORE_BANK, 1000 * (int)SEQ_SCORE);
            env.score_add((int*)&SEQ_SCORE_BANK, 40000000 * rank_bonus);
            env.score_add((int*)&SEQ_SCORE_BANK, 400000 * graze);
        }
        if (env.clear_done && env.clear_done()) {
            if (env.setup_clear) env.setup_clear(4);
        } else {
            if (env.stage_clear)
                env.stage_clear((void*)(uintptr_t)SEQ_CLEAR_MODE, SEQ_CLEAR_STATE);
            count_clear = true;
        }
    }
    // the 99999-capped notice counter (retail: piVar7 = the +1232 table
    // index; reached only on the two non-clear-done paths above)
    if (count_clear && env.notice_counter) {
        int* counter = env.notice_counter();
        if (counter && *counter < 99999) ++*counter;
    }
}

// 0x00415AE0 - Retail forwarder: `return sub_414900(this)` - a 4-byte tail
// jump into the front-HUD update (0x00414900).  The host alias routes to
// the same reconstruction; the front record is the shared `this`/a1.
int UpdateFrontAlias(FrontTick& s, const FrontEnv& env) {
    return UpdateFront(s, env);
}

// 0x00415E90 - UpdateStageSequence: the stage-sequence script opcode
// walker. The sequence object is the retail a1 (see the hpp layout map);
// side effects route through SequenceEnv (the recovered callee twins).
// The opcode stream: each record is {u16 count, u8 opcode, u8 length,
// operands}; the frame counter (+28) gates the loop against the record's
// count word, and every executed record advances the stream by 4 + length.
// Case 0 ends the script (returns -1, clears the stage-progress globals).
int UpdateStageSequence(StageSequence&s,const SequenceEnv&env){
  // prologue: cooldown decrement
  if(s.cooldown>0)--s.cooldown;
  // frame-rate refresh: retail +124 bit 0 AND dword_474E5C bit 8 gate the
  // target assignment (+28 = count, +24 = count-1, +32 = count) EVERY call;
  // only the -999999 / &flt_476F78 setup (+24/+28/+32/+36) is gated by the
  // +40 bit-0 init flag (retail: if ((param_1[10] & 1) == 0) { ... } then
  // the three stores run unconditionally inside the outer gate)
  if((s.flag_byte&1)!=0&&(SEQ_INPUT_FLAGS&0x100)!=0){
    const unsigned int target=s.script?*reinterpret_cast<const unsigned short*>(s.script):0u;
    if((s.flags&1)==0){
      s.flags|=1;
      s.frame_counter=0;
      s.frame_target_minus1=-999999;
      s.frame_float=0.0f;
      s.frame_delta=&FRAME_DELTA;
    }
    s.frame_target_minus1=(int)target-1;
    s.frame_counter=(int)target;
    s.frame_float=(float)target;
  }
  // main loop gate: +28 >= **+92 (the record's count word)
  if(!s.script)return 0;
  if(s.frame_counter>= (int)*reinterpret_cast<const unsigned short*>(s.script)){
    while(true){
      const unsigned char* rec=s.script;
      const int opcode=rec[2];
      const unsigned char* cmd=rec+4;
      switch(opcode){
        case 0:
          if(SEQ_PROGRESS)SEQ_PROGRESS_OTHER=0;
          SEQ_PROGRESS=0;
          return -1;
        case 1:{
          // retail: sub_448D00(player[4], 29) only for mode select 0/1
          if(SEQ_MODE_SELECT==0||SEQ_MODE_SELECT==1){
            void* bank=(SEQ_PLAYER_SLOT?((void**)SEQ_PLAYER_SLOT)[4]:nullptr);
            if(env.alloc_sprite)s.handles[0]=env.alloc_sprite(bank,29);
          }
          break;
        }
        case 2:{
          // retail: difficulty 6 -> sprite 32, difficulty 7 pre-clear ->
          // sprite 37, else sprite 30; every branch gated on mode select 0/1
          if(SEQ_MODE_SELECT==0||SEQ_MODE_SELECT==1){
            if(SEQ_DIFFICULTY==6){
              void* bank=(SEQ_PLAYER_SLOT?((void**)SEQ_PLAYER_SLOT)[14]:nullptr);
              if(env.alloc_sprite)s.handles[1]=env.alloc_sprite(bank,32);
            }else if(SEQ_DIFFICULTY==7&&s.counter<1){
              void* bank=(SEQ_PLAYER_SLOT?((void**)SEQ_PLAYER_SLOT)[14]:nullptr);
              if(env.alloc_sprite)s.handles[1]=env.alloc_sprite(bank,37);
            }else{
              void* bank=(SEQ_PLAYER_SLOT?((void**)SEQ_PLAYER_SLOT)[4]:nullptr);
              if(env.alloc_sprite)s.handles[1]=env.alloc_sprite(bank,30);
            }
          }
          break;
        }
        case 3:{
          void* bank=(SEQ_MANAGER_70C?(void*)((uintptr_t*)SEQ_MANAGER_70C)[10162]:nullptr);
          if(env.alloc_sprite)s.handles[2]=env.alloc_sprite(bank,90);
          break;
        }
        case 4:
          if(env.release_handle)env.release_handle(s.handles[0],opcode);
          s.handles[0]=0;
          break;
        case 5:
          if(env.release_handle){
            env.release_handle(s.handles[1],opcode);
            env.release_handle(s.handles[5],opcode);
          }
          s.handles[1]=0;
          s.handles[5]=0;
          break;
        case 6:
          if(env.release_handle){
            env.release_handle(s.handles[2],opcode);
            env.release_handle(s.handles[3],opcode);
            env.release_handle(s.handles[4],opcode);
          }
          break;
        case 7:
          if(env.release_text)env.release_text(s.handles[1],opcode);
          if(env.release_other)env.release_other(s.handles[0],opcode);
          s.slot_selector=0;
          if(env.anim_register){
            env.anim_register(s.handles[3],s.handles[3],&s.text_slots[0]);
            env.anim_register(s.handles[3],s.handles[4],&s.text_slots[s.slot_selector]);
          }
          s.text_phase=0;
          break;
        case 8:
          if(env.release_text)env.release_text(s.handles[0],opcode);
          if(env.release_other)env.release_other(s.handles[1],opcode);
          s.slot_selector=1;
          if(env.anim_register){
            env.anim_register(s.handles[3],s.handles[3],&s.text_slots[1]);
            env.anim_register(s.handles[3],s.handles[4],&s.text_slots[s.slot_selector]);
          }
          s.text_phase=0;
          break;
        case 9:
          s.flag_byte^=((unsigned char)s.flag_byte^cmd[0])&1u;
          break;
        case 0xA:{
          if(s.timer_count<=0&&env.timer_start)env.timer_start(&s.timer_value,*(const int*)cmd);
          if(env.timer_step)env.timer_step(&s.timer_value,-1.0f);
          if((SEQ_INPUT_FLAGS_2&0x1001)!=0||s.timer_count<=0){
            if(env.sound_id)env.sound_id(0);
            if(env.timer_start)env.timer_start(&s.timer_value,0);
            s.text_phase=0;
          }else{
            if((s.flag_byte&1)==0||(SEQ_INPUT_FLAGS&0x100)==0)return 0;
            if(env.timer_start)env.timer_start(&s.timer_value,0);
            s.text_phase=0;
          }
          break;
        }
        case 0xB:
          s.cooldown=1;
          break;
        case 0xC:{
          if(SEQ_MODE_SELECT==0){
            void* obj=nullptr;
            if(env.text_register){
              obj=env.text_register(0,23,&s.handles[0]);
              const int x=*(const int*)cmd+52;
              if(env.text_place)env.text_place(obj,x);
              obj=env.text_register(*(const int*)(s.script?reinterpret_cast<const unsigned char*>(s.script)+4:nullptr)+60,26,&s.handles[0]);
              if(env.text_place)env.text_place(obj,*(const int*)(s.script?reinterpret_cast<const unsigned char*>(s.script)+4:nullptr)+60);
            }
          }else if(SEQ_MODE_SELECT==1){
            void* obj=nullptr;
            if(env.text_register){
              obj=env.text_register(0,23,&s.handles[0]);
              const int x=*(const int*)cmd+45;
              if(env.text_place)env.text_place(obj,x);
              obj=env.text_register(*(const int*)(s.script?reinterpret_cast<const unsigned char*>(s.script)+4:nullptr)+53,26,&s.handles[0]);
              if(env.text_place)env.text_place(obj,*(const int*)(s.script?reinterpret_cast<const unsigned char*>(s.script)+4:nullptr)+53);
            }
          }
          break;
        }
        case 0xD:{
          // retail: the difficulty ladder runs only for mode select 0/1
          if((SEQ_MODE_SELECT==0||SEQ_MODE_SELECT==1)&&env.text_register&&env.text_place){
            void* bank=(SEQ_PLAYER_SLOT?((void**)SEQ_PLAYER_SLOT)[14]:nullptr);
            int a=0,b=0,f1=24,f2=27;
            switch((int)SEQ_DIFFICULTY){
              case 1:a=15;b=23;break;
              case 2:a=21;b=30;break;
              case 3:a=34;b=43;break;
              case 4:a=37;b=46;break;
              case 5:a=22;b=31;break;
              case 6:a=48;b=57;f1=28;f2=31;break;
              case 7:
                if(s.counter>=1){a=46;b=55;}
                else{a=68;b=77;f1=33;f2=36;}
                break;
              default:break;
            }
            if(a||b){
              void* obj=env.text_register(0,f1,&s.handles[1]);
              if(env.text_place)env.text_place(obj,*(const int*)cmd+a);
              obj=env.text_register(*(const int*)(s.script?reinterpret_cast<const unsigned char*>(s.script)+4:nullptr)+b,f2,&s.handles[1]);
              if(env.text_place)env.text_place(obj,*(const int*)(s.script?reinterpret_cast<const unsigned char*>(s.script)+4:nullptr)+b);
              (void)bank;
            }
          }
          break;
        }
        case 0xE:
        case 0xF:{
          int& slot=s.handles[opcode==0xE?3:4];
          if(env.text_find){
            void* obj=env.text_find(slot);
            if(!obj)slot=0;
            const char* str=env.string_convert?env.string_convert(cmd):"";
            if(env.text_set&&obj)env.text_set(obj,s.text_param,str);
          }
          if(env.release_other)env.release_other(slot,opcode);
          break;
        }
        case 0x10:{
          if(s.text_phase){
            if(env.text_find){
              void* obj=env.text_find(s.handles[4]);
              if(!obj)s.handles[4]=0;
              const char* str=env.string_convert?env.string_convert(cmd):"";
              if(env.text_set&&obj)env.text_set(obj,s.text_param,str);
            }
            if(env.release_other)env.release_other(s.handles[4],opcode);
            s.text_phase=0;
          }else{
            if(env.text_find&&env.text_set){
              void* obj=env.text_find(s.handles[3]);
              if(!obj)s.handles[3]=0;
              if(obj)env.text_set(obj,s.text_param," ");
              obj=env.text_find(s.handles[4]);
              if(!obj)s.handles[4]=0;
              if(obj)env.text_set(obj,s.text_param," ");
              obj=env.text_find(s.handles[3]);
              if(!obj)s.handles[3]=0;
              const char* str=env.string_convert?env.string_convert(cmd):"";
              if(obj)env.text_set(obj,s.text_param,str);
            }
            if(env.release_other)env.release_other(s.handles[3],opcode);
            if(env.release_text)env.release_text(s.handles[4],opcode);
            ++s.text_phase;
          }
          break;
        }
        case 0x11:
          if(env.release_text){
            env.release_text(s.handles[3],opcode);
            env.release_text(s.handles[4],opcode);
          }
          break;
        case 0x12:
          if(env.sound_boss_bgm)env.sound_boss_bgm(1,(int)(SEQ_BGM_STATE?*(uintptr_t*)((char*)SEQ_BGM_STATE+40):0u));
          if(env.alloc_sprite){
            void* bank=(SEQ_MANAGER_70C?(void*)((uintptr_t*)SEQ_MANAGER_70C)[10144]:nullptr);
            env.alloc_sprite(bank,2);
          }
          break;
        case 0x13:{
          if(env.alloc_sprite){
            void* bank=(SEQ_PLAYER_SLOT?((void**)SEQ_PLAYER_SLOT)[14]:nullptr);
            static const int sprites[8]={0,13,16,20,21,14,35,29};
            const int d=(int)SEQ_DIFFICULTY;
            if(d>=1&&d<=7)s.handles[5]=env.alloc_sprite(bank,sprites[d]);
          }
          break;
        }
        case 0x14:
          stage_clear_score_block(s,env,cmd);
          break;
        case 0x15:
          if(env.sound_speed)env.sound_speed(SEQ_DIFFICULTY==6?8.0f:2.0f);
          break;
        case 0x16:
          if(env.anim_propagate)env.anim_propagate(&s.handles[0],opcode,7);
          break;
        case 0x17:
          if(env.anim_propagate)env.anim_propagate(&s.handles[1],opcode,7);
          break;
        default:
          break;
      }
      // record advance: +92 += 4 + length byte
      s.script=rec+4+rec[3];
      if(s.frame_counter<(int)*reinterpret_cast<const unsigned short*>(s.script))
        break;
    }
  }
  // LABEL_136: the frame-delta advance (+24 ramp)
  if(env.frame_advance)env.frame_advance(&s.frame_target_minus1);
  return 0;
}
// Partial host-side model of retail 0x004236F0 (replay-save flow).
// Phases 6/7/8 are retail-exact in shape: timer>=10 gates (+20), selection +-1 on
// 0x10/0x20 (retail sub_44BEA0, 25 slots), sound ids 10/11/12 (retail sub_43DC90),
// confirm 0x1001 -> phase 13 (slot 1 -> phase 10 replay-list load), cancel 0xA ->
// back to the default selection. Phases 10..13 map to retail 0xA..0xD: 10 name
// entry (retail copies the stored name from dword_47783C+120952 into +692; not
// modeled), 11/12 letter-row selection (+-13 on 0x10/0x20, +-1 on 0x40/0x80) with
// character entry -- the char source off_4746D8[0] is NOT modeled, so only the
// cursor (+480) advances; backspace (cursor-1, byte 32) is retail-exact. Phase 13
// close: retail writes dword_491FB8 = (+484) ? 10 : 13 (saved stands in for +484).
// The 'A'+sel%26 name writes, phase 9 and the 0x800/saved flag of the earlier
// model have NO retail counterpart; removed. Full reconstruction pending.
int UpdateReplaySave(ReplaySaveFlow&s,std::uint32_t in){
  ++s.timer;
  switch(s.phase){
  case 6:
    if(s.timer>=10&&(in&0x1001)){s.phase=7;s.timer=0;s.events.push_back(10);} // retail sound 10
    break;
  case 7:
    if(s.timer>=10){s.phase=s.saved?8:12;s.timer=0;} // retail: !(+488) -> phase 12
    break;
  case 8:{
    int prev=s.selection;
    if(in&0x10)s.selection=(s.selection+24)%25;  // retail sub_44BEA0(+36,-1)
    if(in&0x20)s.selection=(s.selection+1)%25;   // retail sub_44BEA0(+36,+1)
    if(prev!=s.selection)s.events.push_back(12); // retail sound 12
    if(in&0x1001){
      s.events.push_back(10);                    // retail sound 10
      s.phase=(s.selection==1)?10:13;            // slot 1 -> replay list, else confirm
      s.timer=0;
    }
    if(in&0xa){
      s.events.push_back(11);                    // retail sound 11
      if(s.selection!=2){s.selection=2;s.timer=0;} // back to default selection
    }
    break;
  }
  case 10:
    if(s.timer>=10){
      int prev=s.selection;
      if(in&0x10)s.selection=(s.selection+24)%25;
      if(in&0x20)s.selection=(s.selection+1)%25;
      if(prev!=s.selection)s.events.push_back(12);
      if(in&0x1001){s.phase=11;s.timer=0;s.cursor=0;s.events.push_back(10);} // name copy not modeled
      if(in&0xa){s.phase=8;s.timer=0;s.events.push_back(11);} // back to slot menu
    }
    break;
  case 11:
  case 12:
    if(s.timer>=10){
      int prev=s.selection;
      if(in&0x10)s.selection-=13;                          // retail sub_44BEA0(+252,-13)
      if(in&0x20)s.selection+=13;                          // retail sub_44BEA0(+252,+13)
      if(in&0x40)s.selection+=(s.selection%13)?-1:12;      // retail sub_44BEA0(+252,-1/+12)
      if(in&0x80)s.selection+=(s.selection%13==12)?-12:1;  // retail sub_44BEA0(+252,-12/+1)
      if(prev!=s.selection)s.events.push_back(12);         // retail sound 12
      if(in&0x1001){
        if(s.saved&&s.phase==12){s.phase=8;s.timer=0;s.selection=0;} // retail +488 arm
        else{
          if(s.cursor<9)++s.cursor; // retail cursor (+480) advance; char source off_4746D8[0] not modeled
          s.events.push_back(10);   // retail sound 10
          s.timer=0;
        }
      }
      if(in&0xa){
        if(s.cursor){s.events.push_back(11);s.name[--s.cursor]=' ';} // retail backspace, byte 32
        else if(s.phase==11){s.events.push_back(11);s.phase=10;s.timer=0;} // retail 0xB -> 0xA
        else if(s.selection<0){s.events.push_back(10);s.phase=8;s.timer=0;} // retail 0xC -> 8
      }
    }
    break;
  case 13:
    if(s.timer>=12){
      s.events.push_back(s.saved?10:13); // retail dword_491FB8 = (+484)?10:13 (sub_423510 not modeled)
      s.timer=0;
    }
    break;
  }
  return 1;
}
namespace {
// Retail offsets on the ANM records consumed by 0x0042E5A0 (raw byte
// offsets; retail-laid-out objects only -- see AnmDrawVm in
// anm_vm_draw_dispatch.hpp for the typed view).
constexpr int kObjChildren=0x10;  // RETAIL child-list head offset. RESOLVED:
// the host registration self-node (object+4, 24 bytes) overlaps +0x10, so
// the record-resolution walk is routed through the find_child env hook
// (see the ResolveTaggedRecord bodies) instead of a raw offset walk.
constexpr int kObjBank=0x308;     // dword: effect-resource bank pointer
constexpr int kObjFlags=0x35C;    // dword: flags; bit 1 = display toggle
constexpr int kObjTypeTag=0x38A;  // word: animation script index (37..51)

// Retail record resolution for one draw/toggle: sub_4491C0(manager,
// parent_handle) finds the parent record by its handle, the child list at
// parent+0x10 (a {record*, next} cell chain, head cell at +0x10 itself) is
// walked for the tag word at +0x38A, and the child is re-resolved by its own
// handle (record[0]).  The parent-handle slot mirrors retail's
// *(panel+0x2C8) = 0 on resolve failure.  Retail starts the walk at
// parent+0x10 even when the parent resolve failed (dereferencing low memory);
// the host form guards the parent instead.  The next-cell stride is
// sizeof(void*) -- dword cells on the 32-bit retail layout (+4), 8-byte
// cells on the host.
unsigned char* ResolveTaggedRecord(OptionsView& view,int tag){
  if(view.manager==0)
    return 0; // not resident: the retail chain is not reachable
  // The retail child-list tag walk (sub_4491C0 find-by-handle + child-list
  // walk matching the +0x38A tag word) maps onto the recovered host
  // machinery: AnimationManager_FindChildByScriptIndex walks the object's
  // membership chain comparing Entity::ScriptIndex() (the host twin of the
  // retail tag word).  The child handle re-resolves to the record.
  int child=AnimationManager_FindChildByScriptIndex(
      view.manager,view.parent_handle,(short)tag);
  if(child==0){
    view.parent_handle=0; // retail: resolve failure zeroes the +0x2C8 slot
    return 0;
  }
  return (unsigned char*)AnimationManager_Find(view.manager,child);
}
// Retail record resolution for one draw of 0x0042F8B0: same find-by-handle +
// child-list tag walk as the DrawOptions path above (the host twin is
// AnimationManager_FindChildByScriptIndex).  The parent-handle slot mirrors
// retail's *(a1+716) = 0 on resolve failure.
unsigned char* ResolveTaggedRecord(MainView& view,int tag){
  if(view.manager==0)
    return 0; // not resident: the retail chain is not reachable
  int child=AnimationManager_FindChildByScriptIndex(
      view.manager,view.parent_handle,(short)tag);
  if(child==0){
    view.parent_handle=0;
    return 0;
  }
  return (unsigned char*)AnimationManager_Find(view.manager,child);
}
}  // namespace

// 0x0042E5A0 - DrawOptions: the options music/sound draw.
//
// Retail order of operations (all byte-grounded from the 0x0042E5A0 body):
//   1. dword_497854 = byte_491D68                  (music volume publish)
//   2. sub_43E460(Parameter, "SetVol", 8, 0)       (queue the "SetVol" record
//                                                   on the sound context
//                                                   dword_492590; host twin
//                                                   AnimationManager_RegisterResource)
//   3. dword_497858 = byte_491D69                  (SE volume publish)
//   4. dword_49785C = byte_491D69
//          ? -5000 - ftol((1 - (1 - music*0.01)^4) * -5000.0) : -10000
//   5. Twelve digit draws, one per ANM record tag: 37/38/39 (music, sprite
//      base +51), 45/46/47 (sound, +51), 41/42/43 (music, +61), 49/50/51
//      (sound, +61).  Each draw resolves the record retail-style:
//        parent = sub_4491C0(manager, *(panel+0x2C8))  (find by handle;
//                                                        failure zeroes the slot)
//        walk the child list at parent+0x10 for the tag word at +0x38A
//        record = sub_4491C0(manager, child[0])        (re-resolve by handle)
//        sub_43E5A0(record, digit, record[+0x308])     (recovered as
//                                                        EffectRuntime_Preload;
//                                                        rendering then proceeds
//                                                        via the render leaves /
//                                                        AnmVm_DrawDispatch)
//   6. Leading-digit visibility: the record flag word at +0x35C, bit 1.
//      Hundreds tags 37/41/45/49 are shown at >= 100, tens tags 38/42/46/50
//      at >= 10 (retail |= 2 / &= ~2 per magnitude branch).
//
// Host routing: byte_491D68/491D69 stand in as OptionsView::music/sound;
// dword_491C10 as OptionsView::manager; dword_492590 ("Parameter") as
// OptionsView::sound_context; the panel parent handle *(panel+0x2C8) as
// OptionsView::parent_handle. The preload leaf is OptionsView::preload
// (wire EffectRuntime_Preload from pool_constructors.cpp -- not in the host
// test link set, so the field stays 0 there). With the pointers null the
// side effects are elided and the view mirrors them: sprites (the 12 digit
// draws), flags (bit-1 state per toggle tag) and the three volume dwords.
void DrawOptions(OptionsView& s){
  // 1. Volume publish + SetVol queue, in retail order.  Retail passes the
  //    stale register value as sub_4491C0's ignored first argument; the
  //    host twin takes (manager, handle) only.
  s.volume_music=s.music;                          // dword_497854 = byte_491D68
  if(s.sound_context!=0)
    AnimationManager_RegisterResource(s.sound_context,0,"SetVol",8,0); // sub_43E460
  s.volume_sound=s.sound;                          // dword_497858 = byte_491D69
  if(s.sound!=0){
    const double v2=(1.0-(double)s.music*0.01);    // retail flt_470B00 = 0.0099999998f
    const double v4=v2*v2;                         // (1 - music*0.01)^4
    s.volume_pan=-5000-(int)((1.0-v4)*-5000.0);    // dword_49785C, __ftol2 truncation
  }else{
    s.volume_pan=-10000;                           // dword_49785C = -10000
  }
  // 2. The twelve digit draws (record tag, sprite base, digit): retail calls
  //    sub_43E5A0(record, digit+base, record[+0x308]) per tag.  sprites[]
  //    mirrors the draws; the live records get the preload when a manager
  //    and a preload leaf are present.
  struct DigitDraw{int tag;int base;int digit;};
  const DigitDraw draws[12]={
    {37,0x33,s.music/100},{38,0x33,(s.music/10)%10},{39,0x33,s.music%10},
    {41,0x3D,s.music/100},{42,0x3D,(s.music/10)%10},{43,0x3D,s.music%10},
    {45,0x33,s.sound/100},{46,0x33,(s.sound/10)%10},{47,0x33,s.sound%10},
    {49,0x3D,s.sound/100},{50,0x3D,(s.sound/10)%10},{51,0x3D,s.sound%10},
  };
  s.sprites.fill(-1);
  for(int i=0;i<12;++i){
    s.sprites[i]=draws[i].digit+draws[i].base;
    unsigned char* record=ResolveTaggedRecord(s,draws[i].tag);
    if(record!=0&&s.preload!=0)
      s.preload(record,s.sprites[i],*(void**)(record+kObjBank)); // sub_43E5A0
  }
  // 3. Leading-digit visibility toggles (retail runs these after the draws).
  //    flags[] mirrors bit 1 of the record flag word per tag; the live
  //    records get the |= 2 / &= ~2 write when a manager is present.
  static const int kToggleTags[8]={37,38,41,42,45,46,49,50};
  for(int i=0;i<8;++i){
    const bool is_music=i<4;
    const bool is_hundreds=(i&1)==0;
    const bool visible=(is_music?s.music:s.sound)>=(is_hundreds?100:10);
    s.flags[i]=visible?2:0; // bit 1 of record[+0x35C]
    if(s.manager!=0){
      unsigned char* record=ResolveTaggedRecord(s,kToggleTags[i]);
      if(record!=0){
        unsigned int* flags=(unsigned int*)(record+kObjFlags);
        if(visible)*flags|=2u; else *flags&=~2u;
      }
    }
  }
}
// 0x0042F8B0 - DrawMain: the main-menu score/rank draw.
// Retail flow (all byte-grounded from the 0x0042F8B0 body): 20 sub_43E5A0
// digit draws, 4 per metric -- tens /10+51 and ones %10+51 on a base record
// pair, then both digits again on the base+10 pair -- over the five __int16
// metrics at a1+22988..+22996. Record tags in retail visit order: 67/68,
// 77/78, 69/70, 79/80, 71/72, 81/82, 73/74, 83/84, 75/76, 85/86.  Each draw
// resolves the record retail-style:
//   parent = sub_4491C0(manager, *(a1+716))   (find by handle; failure zeroes
//                                               the +716 slot)
//   walk the child list at parent+0x10 for the tag word at +0x38A
//   record = sub_4491C0(manager, child[0])    (re-resolve by handle)
//   sub_43E5A0(record, digit, record[+0x308]) (EffectRuntime_Preload)
// The last draw is a tail call: the function returns its preload result
// (0 when the last record did not resolve).  The digits come from a signed
// 16-bit read (movsx + idiv), mirrored with (short) casts.
// Host routing: dword_491C10 as MainView::manager, *(a1+716) as
// MainView::parent_handle, the preload leaf as MainView::preload (wire
// EffectRuntime_Preload from pool_constructors.cpp -- not in the host test
// link set, so the field stays 0 there).  With the pointers null the side
// effects are elided and the view mirrors them: sprites (the 20 draws) and
// parent_handle (the resolve-failure zeroing).
int DrawMain(MainView& s){
  struct DigitDraw{int tag;int digit;};
  const short metric0=(short)s.value; // +22988 (retail movsx read)
  const DigitDraw draws[20]={
    {67,metric0/10},{68,metric0%10},
    {77,metric0/10},{78,metric0%10},
    {69,s.metric[0]/10},{70,s.metric[0]%10},
    {79,s.metric[0]/10},{80,s.metric[0]%10},
    {71,s.metric[1]/10},{72,s.metric[1]%10},
    {81,s.metric[1]/10},{82,s.metric[1]%10},
    {73,s.metric[2]/10},{74,s.metric[2]%10},
    {83,s.metric[2]/10},{84,s.metric[2]%10},
    {75,s.metric[3]/10},{76,s.metric[3]%10},
    {85,s.metric[3]/10},{86,s.metric[3]%10},
  };
  s.sprites.fill(-1);
  int result=0;
  for(int i=0;i<20;++i){
    s.sprites[i]=draws[i].digit+0x33; // retail: digit + 51
    unsigned char* record=ResolveTaggedRecord(s,draws[i].tag);
    if(record!=0&&s.preload!=0)
      result=s.preload(record,s.sprites[i],*(void**)(record+kObjBank)); // sub_43E5A0
    else
      result=0; // retail: the last draw's resolve failure returns 0
  }
  return result; // retail: return sub_43E5A0(...) tail call of the last draw
}
// Host model of retail 0x00433EF0 (music-room handler), based on the IDA
// listing and the raw Ghidra export. IDA shows the handler switching on +32,
// reading the shared +692 timer/ramp field, and returning without advancing
// it; the common dispatcher advances +0x2B4 after this call. All retail-owned
// animation-manager, text, sound, and phase-transition operations route
// through MusicRoomEnv. The three-argument overload below is a separate
// compatibility model for the old host fixture and is never used by this path.
namespace {
constexpr unsigned kMusicTextColor = 0x00FFFFFFu;
constexpr unsigned kMusicPreviewColor = 0x008080FFu;
constexpr int kMusicFrameFirst = 39;
constexpr int kMusicRowFirst = 173;
constexpr int kMusicFrameCount = 8;
constexpr int kMusicPreviewDummy = 3;
constexpr int kMusicPreviewDummyAlt = 4;
constexpr int kMusicPlayDummy = 2;
constexpr float kMusicRowX = 64.0f;
constexpr float kMusicRowY = 96.0f;
constexpr float kMusicRowStep = 20.0f;
constexpr float kMusicSelectedOffset = 4.0f;

void MusicResetRamp(MusicRoom&state,const MusicRoomEnv&env){
  if((state.ramp_flags&1u)==0){
    state.ramp_counter=0;
    state.ramp_target_minus1=-999999;
    state.ramp_value=0.0f;
    state.ramp_delta=env.frame_delta;
    state.ramp_flags|=1u;
  }
  state.ramp_counter=0;
  state.ramp_value=0.0f;
  state.ramp_target_minus1=-1;
}

bool MusicAnmLive(const MusicRoomEnv&env,int handle){
  if(handle==0)return false;
  return env.resolve_anm==nullptr||env.resolve_anm(env.manager,handle)!=0;
}

int MusicRegister(const MusicRoom&state,const MusicRoomEnv&env,
                  void* bank,int sprite){
  (void)state;
  if(env.register_anm==nullptr)return 0;
  return env.register_anm(env.manager,bank,sprite);
}

void MusicSound(MusicRoom&state,const MusicRoomEnv&env,int id){
  if(env.play_sound!=nullptr)env.play_sound(id);
  else state.events.push_back(id);
}

void MusicDepthLive(const MusicRoomEnv&env,int handle,int depth){
  if(handle!=0&&env.set_depth!=nullptr)env.set_depth(env.manager,handle,depth);
}

void MusicDepth(const MusicRoomEnv&env,int handle,int depth){
  if(handle!=0&&MusicAnmLive(env,handle))MusicDepthLive(env,handle,depth);
}

void MusicVisibleLive(const MusicRoomEnv&env,int handle,bool visible){
  if(handle!=0&&env.set_visible!=nullptr)
    env.set_visible(env.manager,handle,visible);
}

void MusicPositionLive(const MusicRoomEnv&env,int handle,float x,float y){
  if(handle!=0&&env.set_position!=nullptr)
    env.set_position(env.manager,handle,x,y,0.0f);
}

// sub_434A80 writes a four-frame ramp into the resolved ANM object. The
// immediate callback remains the compatibility fallback for hosts that do
// not expose the object's ramp fields.
void MusicPositionRamp(const MusicRoomEnv&env,int handle,float x,float y){
  if(handle==0)return;
  if(env.set_position_ramp!=nullptr)
    env.set_position_ramp(env.manager,handle,x,y,0.0f);
  else if(env.set_position!=nullptr)
    env.set_position(env.manager,handle,x,y,0.0f);
}

void MusicPositionInitial(const MusicRoomEnv&env,int handle,float x,float y){
  // The initial row setup always calls sub_434A80; its object starts with no
  // useful position, so there is no 40-unit comparison at this call site.
  MusicPositionRamp(env,handle,x,y);
}

void MusicPositionChanged(const MusicRoomEnv&env,int handle,float x,float y){
  if(handle==0)return;
  float current_y=0.0f;
  if(env.get_position_y!=nullptr&&
     env.get_position_y(env.manager,handle,&current_y)&&
     std::fabs(current_y-y)<40.0f){
    MusicPositionRamp(env,handle,x,y);
  }else{
    // Retail writes x/y/z immediately when the existing Y is at least 40
    // units from the target. Without a resolved Y, an immediate write is the
    // only honest host behavior available.
    MusicPositionLive(env,handle,x,y);
  }
}

bool MusicTrackPlayedLocal(const MusicRoom&state,int track){
  if(track<0)return false;
  if(track<(int)state.played_tracks.size())return state.played_tracks[track]!=0;
  return track==state.selection&&state.played;
}

bool MusicTrackPlayed(const MusicRoom&state,const MusicRoomEnv&env,int track){
  if(track<0)return false;
  if(env.is_track_played!=nullptr)return env.is_track_played(track);
  return MusicTrackPlayedLocal(state,track);
}

void MusicMarkTrackPlayed(MusicRoom&state,const MusicRoomEnv&env,int track){
  if(track<0)return;
  if(env.mark_track_played!=nullptr)env.mark_track_played(track);
  if(track>=(int)state.played_tracks.size())
    state.played_tracks.resize((std::size_t)track+1,0);
  state.played_tracks[track]=1;
  state.played=true;
}

const std::string&MusicRowText(const MusicRoom&state,int track){
  static const std::string empty;
  if(track<0||track>=(int)state.comments.size())return empty;
  return state.comments[track];
}

const std::string&MusicTitle(const MusicRoom&state,int track){
  static const std::string empty;
  if(track<0||track>=(int)state.titles.size())return empty;
  return state.titles[track];
}

void MusicDrawRowText(const MusicRoom&state,const MusicRoomEnv&env,
                     int handle,int track){
  if(handle==0||env.draw_text==nullptr)return;
  if(MusicTrackPlayed(state,env,track)){
    env.draw_text(env.manager,handle,kMusicTextColor,
                  MusicRowText(state,track).c_str());
    return;
  }
  char no_text[32];
  std::snprintf(no_text,sizeof(no_text),"No.%d  ",track+1);
  env.draw_text(env.manager,handle,kMusicTextColor,no_text);
}


void MusicDrawFrameRow(MusicRoom&state,const MusicRoomEnv&env,int frame){
  if(frame<0||frame>=kMusicFrameCount)return;
  int handle=state.frame_handles[frame];
  if(handle==0||!MusicAnmLive(env,handle)){
    if(env.resolve_anm!=nullptr)state.frame_handles[frame]=0;
    return;
  }
  const int displayed=state.displayed;
  const bool preview=!MusicTrackPlayed(state,env,displayed)&&state.armed;
  if(env.draw_text!=nullptr){
    if(preview){
      const char*text=env.preview_text==nullptr?nullptr:env.preview_text(frame);
      // off_476FD8 is an encoded retail string table. Without a callback
      // carrying those bytes there is no honest host-side replacement.
      if(text!=nullptr)
        env.draw_text(env.manager,handle,kMusicPreviewColor,text);
    }else{
      const std::size_t row=(std::size_t)displayed*8u+(std::size_t)frame;
      const char*text=row<state.row_texts.size()?state.row_texts[row].c_str():"";
      env.draw_text(env.manager,handle,kMusicTextColor,text);
    }
  }
  MusicDepthLive(env,handle,2);
}

void MusicHideFrameRows(const MusicRoom&state,const MusicRoomEnv&env){
  for(int handle:state.frame_handles)MusicDepth(env,handle,1);
}

void MusicAdvanceSelection(MusicRoom&state,int delta){
  const int count=state.track_count;
  if(count<=0)return;
  int next=state.selection+delta;
  while(next>=count)next-=count;
  while(next<0)next+=count;
  state.selection=next;
}

void MusicLayoutRows(MusicRoom&state,const MusicRoomEnv&env){
  for(int track=0;track<state.track_count&&track<(int)state.row_handles.size();++track){
    int&handle=state.row_handles[track];
    if(handle!=0&&!MusicAnmLive(env,handle))handle=0;
    if(handle==0)continue;
    const float y=kMusicRowY-(float)state.scroll*kMusicRowStep+
                 (float)track*kMusicRowStep;
    MusicVisibleLive(env,handle,track>=state.scroll&&track<state.scroll+10);
    MusicDepthLive(env,handle,2+(track==state.selection?0:1));
    MusicPositionChanged(env,handle,
                         kMusicRowX-(track==state.selection?kMusicSelectedOffset:0.0f),y);
  }
}

void MusicPopHistory(MusicRoom&state,const MusicRoomEnv&env){
  // The retail callback owns the +0x24 history operation. Do not apply a
  // second host-side pop after it, since that would overwrite callback state.
  if(env.history_pop!=nullptr){
    env.history_pop(state);
    return;
  }
  if(!state.history.empty()){
    if(state.history_cursor<0)
      state.history_cursor=(int)state.history.size();
    if(state.history_cursor>0)--state.history_cursor;
    if(state.history_cursor>=(int)state.history.size())
      state.history_cursor=(int)state.history.size()-1;
    const std::pair<int,int>&entry=state.history[(std::size_t)state.history_cursor];
    state.selection=entry.first;
    state.track_count=entry.second;
  }else{
    // A zeroed host state is the retail object's zero-depth history entry.
    state.selection=0;
    state.track_count=0;
  }
}

void MusicExitToPhase3(MusicRoom&state,const MusicRoomEnv&env){
  if(state.file_buffer!=nullptr){
    std::free(state.file_buffer);
    state.file_buffer=nullptr;
  }
  state.loaded=false;
  MusicPopHistory(state,env);
  // sub_409E50 is a depth-1 stop-and-propagate operation, not release/free.
  // Keep the handles: retail leaves these slots populated after stopping.
  for(int handle:state.row_handles)
    if(handle!=0&&env.stop_anm!=nullptr)env.stop_anm(env.manager,handle);
  MusicHideFrameRows(state,env);
  MusicSound(state,env,11);
  state.phase=3;
  state.timer=0;
  MusicResetRamp(state,env);
}

bool MusicReadLine(const std::string&resource,std::size_t&cursor,
                   std::string&line){
  if(cursor>=resource.size())return false;
  const std::size_t start=cursor;
  while(cursor<resource.size()&&resource[cursor]!='\n'&&resource[cursor]!='\r')++cursor;
  line=resource.substr(start,cursor-start);
  while(cursor<resource.size()&&(resource[cursor]=='\n'||resource[cursor]=='\r'))++cursor;
  return true;
}

std::string MusicField(const std::string&line,std::size_t capacity){
  // Retail copies into fixed 64-byte title and 66-byte comment/row slots.
  // Clamp at the destination capacity minus its terminating byte rather than
  // allowing a host string to claim data retail would overwrite.
  return line.substr(0,capacity>0?capacity-1:0);
}

void MusicParseResource(MusicRoom&state,const std::string&resource){
  state.titles.clear();
  state.comments.clear();
  state.row_texts.clear();
  std::size_t cursor=0;
  std::string line;
  while(MusicReadLine(resource,cursor,line)){
    // FUN_004349E0 skips every non-'@' line, including '#'-comments.
    if(line.empty()||line[0]!='@')continue;
    state.titles.push_back(MusicField(line.substr(1),64));
    if(!MusicReadLine(resource,cursor,line))line.clear();
    state.comments.push_back(MusicField(line,66));
    for(int row=0;row<8;++row){
      if(!MusicReadLine(resource,cursor,line))line.clear();
      state.row_texts.push_back(MusicField(line,66));
    }
  }
  state.track_count=(int)state.titles.size();
  state.played_tracks.resize((std::size_t)state.track_count,0);
  state.scroll=0;
  state.draw_cursor=0;
  state.displayed=0;
  state.armed=false;
}

// The old three-argument host adapter used one '@' line per record. It is
// intentionally separate from the retail parser so a partially initialized
// retail environment cannot select this trace through a public flag.
void MusicParseCompatibilityResource(MusicRoom&state,
                                      const std::string&resource){
  state.titles.clear();
  state.comments.clear();
  state.row_texts.clear();
  std::size_t cursor=0;
  std::string line;
  while(MusicReadLine(resource,cursor,line)){
    if(line.empty()||line[0]!='@')continue;
    state.titles.push_back(line.substr(1));
    state.comments.emplace_back();
    for(int row=0;row<8;++row)state.row_texts.emplace_back();
  }
  state.track_count=(int)state.titles.size();
  state.played_tracks.resize((std::size_t)state.track_count,0);
  state.scroll=0;
  state.draw_cursor=0;
  state.displayed=0;
  state.armed=false;
}

void MusicRegisterInitialAnm(MusicRoom&state,const MusicRoomEnv&env){
  if(state.animation_bank==nullptr)state.animation_bank=env.animation_bank;
  if(!MusicAnmLive(env,state.parent_handle)){
    state.parent_handle=MusicRegister(state,env,state.animation_bank,95);
    state.anm_handles[95]=state.parent_handle;
    state.fallback_handle=MusicRegister(state,env,env.fallback_bank,8);
  }
  state.auxiliary_handle=MusicRegister(state,env,state.animation_bank,103);
  state.anm_handles[103]=state.auxiliary_handle;
  for(int frame=0;frame<kMusicFrameCount;++frame){
    state.frame_handles[frame]=MusicRegister(state,env,env.frame_bank,
                                               kMusicFrameFirst+frame);
    if(env.register_anm==nullptr)state.events.push_back(kMusicFrameFirst+frame);
  }
}

void MusicRegisterRows(MusicRoom&state,const MusicRoomEnv&env){
  if((int)state.row_handles.size()<state.track_count)
    state.row_handles.resize((std::size_t)state.track_count,0);
  if((int)state.rows.size()<state.track_count)
    state.rows.resize((std::size_t)state.track_count,0);
  const int first=std::max(0,2*state.timer-2);
  const int last=std::max(0,2*state.timer);
  const bool no_env=env.register_anm==nullptr;
  for(int track=first;track<last&&track<state.track_count;++track){
    const int sprite=kMusicRowFirst+track;
    state.rows[track]=sprite;
    state.row_handles[track]=MusicRegister(state,env,state.animation_bank,sprite);
    if(no_env)state.row_handles[track]=0;
    if(state.row_handles[track]==0&&env.resolve_anm!=nullptr)continue;
    if(state.row_handles[track]!=0){
      if(!MusicAnmLive(env,state.row_handles[track])){
        state.row_handles[track]=0;
        continue;
      }
      MusicDrawRowText(state,env,state.row_handles[track],track);
      const bool selected=track==state.selection;
      const bool visible=track>=state.scroll&&track<state.scroll+10;
      MusicVisibleLive(env,state.row_handles[track],visible);
      MusicDepthLive(env,state.row_handles[track],2+(selected?0:1));
      const float y=kMusicRowY-(float)state.scroll*kMusicRowStep+
                   (float)state.timer*kMusicRowStep*2.0f-kMusicRowStep*2.0f;
      MusicPositionInitial(env,state.row_handles[track],
                           kMusicRowX-(selected?kMusicSelectedOffset:0.0f),y);
    }
  }
}
}

void AdvanceMusicRoomTimer(MusicRoom&state, const float* frame_delta) {
  if(state.timer==0)
    state.timer_fraction=0.0f;
  const float speed=frame_delta==nullptr?1.0f:*frame_delta;
  if(speed<=0.0f)
    return;
  if(0.99f<speed&&speed<1.01f)
    state.timer_fraction+=1.0f;
  else
    state.timer_fraction+=speed;
  state.timer=static_cast<int>(state.timer_fraction);
}

int UpdateMusicRoom(MusicRoom&state,const MusicRoomEnv&env,
                    std::uint32_t input,const std::string&resource){
  switch(state.phase){
  case 0:
    // +0x2B4 is advanced by the shared dispatcher after return. The retail
    // handler only consumes its current boundary value.
    if(state.timer==1){
      // Retail seeds +44 to six before the resource count is known; the
      // final parsed count is then used by sub_44BEA0 for wrapped navigation.
      state.track_count=6;
      state.selection=0;
      // An empty byte stream is a valid loaded file. Retail only enters the
      // failure cleanup when sub_44B360 returns null; resource_available keeps
      // that result distinct from an empty host string.
      if(!env.resource_available){
        MusicExitToPhase3(state,env);
        return 0;
      }
      state.file_buffer=std::malloc(resource.size()+1);
      if(state.file_buffer==nullptr){
        MusicExitToPhase3(state,env);
        return 0;
      }
      std::memcpy(state.file_buffer,resource.data(),resource.size());
      static_cast<char*>(state.file_buffer)[resource.size()]='\0';
      MusicParseResource(state,resource);
      state.loaded=true;
      MusicRegisterInitialAnm(state,env);
    }
    if(state.timer<10)MusicRegisterRows(state,env);
    if(state.timer>=10){
      state.phase=1;
      state.timer=0;
      MusicResetRamp(state,env);
    }
    break;
  case 1:
    if((state.timer&1)==0&&state.draw_cursor<kMusicFrameCount){
      MusicDrawFrameRow(state,env,state.draw_cursor);
      ++state.draw_cursor;
    }
    if(state.timer>4){
      state.phase=2;
      state.timer=0;
      MusicResetRamp(state,env);
    }
    break;
  case 2:
    if((state.timer&1)==0&&state.draw_cursor<kMusicFrameCount){
      MusicDrawFrameRow(state,env,state.draw_cursor);
      ++state.draw_cursor;
    }
    {
      state.previous_selection=state.selection;
      const int previous=state.previous_selection;
      if((input&0x10u)!=0)MusicAdvanceSelection(state,-1);
      if((input&0x20u)!=0)MusicAdvanceSelection(state,1);
      if(previous!=state.selection){
        MusicSound(state,env,12);
        if(state.selection<state.scroll)state.scroll=state.selection;
        else if(state.selection>=state.scroll+10)state.scroll=state.selection-9;
        MusicLayoutRows(state,env);
        state.armed=false;
      }
    }
    if((input&0x1001u)==0){
      if((input&0xAu)!=0){
        MusicExitToPhase3(state,env);
        return 0;
      }
      return 0;
    }
    for(int handle:state.frame_handles)MusicDepth(env,handle,3);
    state.displayed=state.selection;
    state.draw_cursor=0;
    state.timer=0;
    MusicResetRamp(state,env);
    if(MusicTrackPlayed(state,env,state.selection)||state.armed){
      const std::string&title=MusicTitle(state,state.selection);
      if(env.play_music!=nullptr)
        env.play_music(0,title.c_str());
      if(env.dummy_state!=nullptr&&env.dummy_mode4)env.dummy_state(kMusicPreviewDummyAlt);
      if(env.dummy_state!=nullptr)env.dummy_state(kMusicPlayDummy);
      // Retail writes the played-table base byte here (the disassembly has
      // no selection-index add); row/preview queries still use displayed.
      MusicMarkTrackPlayed(state,env,0);
      state.armed=false;
    }else{
      if(env.dummy_state!=nullptr)
        env.dummy_state(env.dummy_mode4?kMusicPreviewDummyAlt:kMusicPreviewDummy);
      state.armed=true;
    }
    break;
  case 3:
    if(state.timer>=10){
      MusicDepth(env,state.auxiliary_handle,1);
      state.auxiliary_handle=0;
      state.anm_handles[103]=0;
      MusicDepth(env,state.anm_handles[90],8);
      MusicDepth(env,state.anm_handles[91],8);
      MusicDepth(env,state.parent_handle,1);
      state.parent_handle=0;
      state.anm_handles[95]=0;
      if(state.fallback_handle!=0&&env.stop_anm!=nullptr)
        env.stop_anm(env.manager,state.fallback_handle);
      state.substate=2;
      state.phase=0;
      state.timer=0;
      MusicResetRamp(state,env);
      if(env.restore_bgm!=nullptr)env.restore_bgm("bgm/th10_02.wav");
      if(env.set_bgm_state!=nullptr)env.set_bgm_state(0,0);
      MusicPopHistory(state,env);
    }
    break;
  default:
    break;
  }
  return 0;
}

int UpdateMusicRoom(MusicRoom&state,std::uint32_t input,
                    const std::string&resource){
  // Compatibility-only state machine retained for the original host fixture.
  // It owns the legacy one-line parser and caller-side timer tick; the retail
  // env overload above never enters this path.
  MusicRoomEnv env{};
  ++state.timer;
  switch(state.phase){
  case 0:
    if(state.timer==1){
      MusicParseCompatibilityResource(state,resource);
      state.loaded=true;
      state.events.clear();
      for(int i=0;i<kMusicFrameCount;++i)
        state.events.push_back(kMusicFrameFirst+i);
    }
    if(state.timer>=10){
      state.phase=1;
      state.timer=0;
      MusicResetRamp(state,env);
    }
    break;
  case 1:
    if(state.timer>4){
      state.phase=2;
      state.timer=0;
      MusicResetRamp(state,env);
    }
    break;
  case 2:
    if((input&0x10u)!=0)MusicAdvanceSelection(state,-1);
    if((input&0x20u)!=0)MusicAdvanceSelection(state,1);
    if((input&0xAu)!=0){
      state.phase=3;
      state.timer=0;
    }
    break;
  default:
    break;
  }
  return 0;
}
}
