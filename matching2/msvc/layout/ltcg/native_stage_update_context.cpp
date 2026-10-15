// Complete direct-global semantic model of the 1544-byte stage update.
// Its still-private external helper boundaries are diagnostic, not recovered.
#include <string.h>
#include <stdlib.h>
#include "th10/game/native_stage_fade_00404530.hpp"
#include "th10/render/screen_effect_controller.hpp"
struct StageContextFade_00418190 {
    unsigned char reserved000[0x14];
    int frame;
    unsigned char reserved018[0x58-0x18];
    unsigned int flags;
};
extern "C" {
extern GameStateFade_00404530* data_004776e4;
extern unsigned char* g_ascii_manager;
extern unsigned char* data_004776e8;
extern unsigned char* g_bomb;
extern unsigned char* data_004776f0;
extern unsigned char* g_card;
extern unsigned char* g_effect;
extern unsigned char* data_00477704;
extern unsigned char* data_0047770c;
extern unsigned char* g_hint;
extern unsigned char* data_00477818;
extern unsigned char* g_laser_manager;
extern unsigned char* g_pause;
extern unsigned char* g_player;
extern unsigned char* data_00477838;
extern unsigned char* data_0047783c;
extern unsigned char* g_smoll_score;
extern unsigned char* data_00477848;
extern unsigned int data_00474ca0,data_00474e30,data_00491ff4,data_00491d78;
extern int data_00491fb8,data_00474c88,data_00474c8c,data_00474c68,data_00474c6c;
extern unsigned char data_00492254[],data_00492590[],data_00491c28[],data_00474c40[];
extern const char data_0046d278[],data_0046df98[];
// These declarations represent genuine logical parameters observed in retail.
// Without the full helper closure, native calls do not claim their private ABI.
void __stdcall StageStopWorker_0044c150(void* worker);
void __stdcall StageActivateBullets_00404450(void* player);
void __stdcall StageStartPlayerMode_004045b0(void* player);
void __stdcall StageStopAnimation_00409e50(void* handle);
void __stdcall StageResetBulletPool_00405ed0(void* pool);
void __stdcall StageResetPause_00424d90(void* pause);
void __stdcall StageResetEnemy_00409f90(void* enemy);
void __stdcall StageReleaseChain_00417770(void* chain);
void __stdcall StageResetGameplay_0042a450(void* gameplay);
void __stdcall StageStartScript_0040cfb0(int* state,void* manager,const char* path);
void __stdcall StageInitializeThread_00413bc0(void* thread);
void __stdcall StageRefreshPanel_00426f70(void* panel);
void __stdcall StagePlayMusic_00420b10(int slot,int selector);
void __stdcall StageRegisterMusic_0043e460(void* queue,const char* name,int value,int parameter);
void __stdcall StageSetTimer_00405410(void* timer,int value);
void __stdcall StageDestroyGameState_00402440(void* state);
void __stdcall StageSetInputMode_0040ac90(void* state,int value);
void __stdcall StageTickThread_00417040(void* thread);
void __stdcall StageDecayScore_00418a00(void* score);
void __stdcall StageTickTimer_00404ed0(void* timer);
}
static __forceinline unsigned int& StageWord(unsigned char* owner,unsigned int offset) {
    return *reinterpret_cast<unsigned int*>(owner+offset);
}
static __forceinline void StageKillTask(unsigned int pointer) {
    if (pointer) StageWord(reinterpret_cast<unsigned char*>(pointer),4)|=2u;
}
static __forceinline void StageKillPair(unsigned char* owner) {
    StageKillTask(StageWord(owner,8));
    StageKillTask(StageWord(owner,12));
}
static __forceinline void StageKillRequiredPair(unsigned char* owner) {
    StageWord(reinterpret_cast<unsigned char*>(StageWord(owner,8)),4)|=2u;
    StageWord(reinterpret_cast<unsigned char*>(StageWord(owner,12)),4)|=2u;
}
static __forceinline void StageReset(StageContextFade_00418190* context,int* local_state,bool delayed) {
    context->flags&=~0x800u;
    StageResetBulletPool_00405ed0(data_004776f0);
    StageResetPause_00424d90(g_player);
    memset(data_00477818+0x14,0,0x873A8*4);
    StageResetEnemy_00409f90(data_00477704);
    StageReleaseChain_00417770(g_laser_manager);
    data_00474c88=0;
    data_00474c8c=0;
    StageResetGameplay_0042a450(data_00477838);
    memset(local_state,0,16*4);
    StageStartScript_0040cfb0(local_state,data_00477704,data_0046d278);
    StageInitializeThread_00413bc0(data_0047770c);
    StageKillPair(g_pause);
    StageKillRequiredPair(g_player);
    StageRefreshPanel_00426f70(g_player);
    StageKillPair(data_004776f0);
    StageKillPair(data_00477704);
    StageKillPair(data_00477818);
    StageKillPair(g_laser_manager);
    StageKillRequiredPair(g_effect);
    StageKillPair(g_bomb);
    StageKillRequiredPair(g_smoll_score);
    StageKillPair(g_card);
    StageWord(reinterpret_cast<unsigned char*>(StageWord(g_card,0x37AC)),4)|=2u;
    StageKillPair(g_hint);
    if (delayed) {
        StageRegisterMusic_0043e460(data_00492590,data_0046df98,(data_00491d78&0x10u)?4:3,0);
        StagePlayMusic_00420b10(0,StageWord(data_00477848,0x24));
        unsigned char* thread=g_ascii_manager;
        StageStopAnimation_00409e50(thread+0x89A4);
        StageWord(thread,0x89A4)=0;
        StageSetTimer_00405410(reinterpret_cast<unsigned char*>(context)+0x10,0);
    } else {
        if (!(data_00474ca0&0x20u))
            StagePlayMusic_00420b10(0,StageWord(data_00477848,0x24));
        unsigned char* thread=g_ascii_manager;
        StageStopAnimation_00409e50(thread+0x89A0);
        StageStopAnimation_00409e50(thread+0x89A4);
        StageWord(thread,0x89A4)=0;
    }
}
#pragma code_seg(".text$90context")
extern "C" int __stdcall StageContextUpdate_00418190(StageContextFade_00418190* context) {
    int local_state[16];
    if (context->frame==0) {
        if (context->flags&8u) {
            StageStopWorker_0044c150(data_00492254);
            data_00491fb8=((~(data_00491ff4>>12))&1u)|2u;
            return 1;
        }
        StageActivateBullets_00404450(data_004776e8);
        GameStateFade_00404530* game=data_004776e4;
        if (game) {
            game->BeginFade();
            StageStartPlayerMode_004045b0(data_004776e8);
            context->flags|=0x800u;
            StageStopAnimation_00409e50(data_0047770c+0x9E14);
        } else {
            StageReset(context,local_state,false);
        }
    } else if (context->frame==30 && (context->flags&0x800u)) {
        StageReset(context,local_state,true);
    }
    GameStateFade_00404530* game=data_004776e4;
    if (game && (game->flags&8u) && game) {
        StageDestroyGameState_00402440(game);
        free(game);
    }
    if (context->flags&4u) {
        context->flags|=0x80u;
        return 1;
    }
    StageStopWorker_0044c150(data_00492254);
    if (data_00474ca0&0x20u) {
        if ((data_00474e30&0x160Bu)||(context->flags&0x70u))
            data_00491fb8=(data_00491ff4&0x1000u)?2:4;
        if (context->frame==0xB7C)
            CreateScreenEffect_0043c8b0(43,5,60,0,0,0);
        else if (context->frame==3000)
            StageSetInputMode_0040ac90(data_00491c28,4);
    }
    StageTickThread_00417040(data_0047770c);
    if ((context->flags&0x10u)||(context->flags&0x20u)||(context->flags&0x40u))
        return 3;
    if (StageWord(data_00477838,0x10)!=1) {
        int index=data_00474c6c+data_00474c68*3;
        int* frames=reinterpret_cast<int*>(data_0047783c+index*0x437C+0x4CC);
        if (*frames<215999999) ++*frames;
    }
    if (StageWord(data_00477704,0x10)==0 && StageWord(data_0047770c,0x9EB8)==0 && context->frame>=90)
        StageDecayScore_00418a00(data_00474c40);
    ++data_00474c88;
    ++data_00474c8c;
    StageTickTimer_00404ed0(reinterpret_cast<unsigned char*>(context)+0x10);
    return 1;
}
#pragma code_seg()
