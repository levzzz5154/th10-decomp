#include "th10/game/large_player_native.hpp"
#include "th10/platform/archive_callers.hpp"
#include "th10/platform/text_log.hpp"
#include "th10/core/func_ctrl.hpp"
struct CachedResource;
CachedResource* __fastcall Recovery_LoadCachedResource(int,void*,const char*);
extern "C" {
    // The selection words are fields of one game-state struct other code
    // reaches through its address, so field loads are never folded.
    struct GameSelectionView { int shot_type, character, unknown_08, difficulty; };
    extern GameSelectionView g_globals_character;
    extern void* g_sprt_ctrl;
    extern ParameterFile* data_00491bf0;
    extern FuncCtrl* g_func_ctrl;
    extern char data_0046e42c[],data_0046e420[],data_0046e3ec[];
    extern const char* data_00476fc0[];
    extern TextLog_0044b810 g_log;
    extern float data_00470b44,data_00470b0c,g_game_speed;
    extern float data_00476fb8[],data_00476fb0[],data_00476fa0[],data_00476fa8[];
    int __fastcall LargePlayerTick(void*);
    int __fastcall LargePlayerDraw(void*);
    SchedulerTask* __stdcall LargePlayerCallbackCreate(TaskRoutine);
    void __stdcall LargePlayerRefresh(PlayerResetBlock*);
}
// Actual timer lazy initialization shared by the three affected records.
static __forceinline void InitializeTimer(PlayerTimerRecord14* timer) {
    if (!(timer->flags&1)) {
        timer->current=0;timer->previous=(int)0xfff0bdc1u;
        timer->elapsed=0;timer->speed=&g_game_speed;timer->flags|=1;
    }
}
#pragma code_seg(".text$a07body")
// Three float lanes staged through one local, the way the retail build moves
// every computed bound through its reserved frame window before the copy.
struct PlayerBounds3 { float x, y, z; };

int PlayerResetBlock::Initialize() {
    const char* name;
    if (!g_globals_character.shot_type) name=data_0046e42c; else name=data_0046e420;
    CachedResource* resource=Recovery_LoadCachedResource(8,g_sprt_ctrl,name);
    Word(0x10)=(unsigned int)resource;
    if (!resource) { g_log.Append(data_0046e3ec); return -1; }
    if (data_00491bf0) {
        Word(0x45c)=(unsigned int)data_00491bf0;data_00491bf0=0;
    } else {
        const char* parameter_name=data_00476fc0[g_globals_character.character+3*g_globals_character.shot_type];
        if (((ParameterLoader*)this)->Load(parameter_name)) {
            g_log.Append(data_0046e3ec);return -1;
        }
    }
    SchedulerTask* task=LargePlayerCallbackCreate(LargePlayerTick);
    task->context=this;*(unsigned int*)((char*)task+4)&=~2u;
    FuncCtrl_RegisterPrimary(g_func_ctrl,task,0x10);Word(8)=(unsigned int)task;
    task=LargePlayerCallbackCreate(LargePlayerDraw);
    *(unsigned int*)((char*)task+4)&=~2u;task->context=this;
    FuncCtrl_RegisterSecondary(g_func_ctrl,task,0x16);Word(0xc)=(unsigned int)task;
    ConfigureResource_00404f30 script_resource={(void*)Word(0x10)};
    ((ItemConfiguredEntity_00404f30*)&slot)->Configure(0,script_resource);
    Float(0x3c0)=0;Float(0x3c4)=400;
    Word(0x3cc)=0;Word(0x3d0)=40000;
    ParameterFile* parameters=(ParameterFile*)Word(0x45c);
    Word(0x3d4)=(int)(parameters->width*data_00470b44);
    Word(0x3d8)=(int)(parameters->height*data_00470b44);
    Word(0x3dc)=(int)(parameters->projected_width*data_00470b44);
    Word(0x3e0)=(int)(parameters->projected_height*data_00470b44);
    unsigned int* indicator=(unsigned int*)((char*)this+0x436c);
    for (int i=0;i<33;++i) {
        indicator[0]=Word(0x3cc);indicator[1]=Word(0x3d0);indicator+=2;
    }
    InitializeTimer(&timer_460);timer_460.elapsed=-1;timer_460.previous=-2;timer_460.current=-1;
    // Character tables initialize the three leading parameter words at +4,+C,+8.
    // The parameter words are dword slots; the tables hold float bit patterns.
    *(unsigned int*)((char*)Word(0x45c)+4)=reinterpret_cast<const unsigned int&>(data_00476fb8[g_globals_character.shot_type]);
    *(unsigned int*)((char*)Word(0x45c)+12)=reinterpret_cast<const unsigned int&>(data_00476fb0[g_globals_character.shot_type]);
    *(unsigned int*)((char*)Word(0x45c)+8)=reinterpret_cast<const unsigned int&>(data_00476fa0[g_globals_character.shot_type]);
    float half=*(float*)((char*)Word(0x45c)+4)*data_00470b0c;
    Float(0x424)=5;Float(0x420)=half;Float(0x41c)=half;
    half=data_00476fb0[g_globals_character.shot_type]*data_00470b0c;
    Float(0x430)=5;Float(0x42c)=half;Float(0x428)=half;
    half=data_00476fa8[g_globals_character.shot_type]*data_00470b0c;
    Float(0x43c)=5;Float(0x438)=half;Float(0x434)=half;
    PlayerBounds3 bounds;
    bounds.x=Float(0x3c0)-Float(0x41c);
    bounds.y=Float(0x3c4)-Float(0x420);
    bounds.z=Float(0x3c8)-Float(0x424);
    *(PlayerBounds3*)((char*)this+0x404)=bounds;
    bounds.x=Float(0x41c)+Float(0x3c0);
    bounds.y=Float(0x420)+Float(0x3c4);
    bounds.z=Float(0x424)+Float(0x3c8);
    *(PlayerBounds3*)((char*)this+0x410)=bounds;
    bounds.x=Float(0x3c0)-Float(0x428);
    bounds.y=Float(0x3c4)-Float(0x42c);
    bounds.z=Float(0x3c8)-Float(0x430);
    *(PlayerBounds3*)((char*)this+0x4324)=bounds;
    bounds.x=Float(0x428)+Float(0x3c0);
    bounds.y=Float(0x42c)+Float(0x3c4);
    bounds.z=Float(0x430)+Float(0x3c8);
    *(PlayerBounds3*)((char*)this+0x4330)=bounds;
    bounds.x=Float(0x3c0)-Float(0x434);
    bounds.y=Float(0x3c4)-Float(0x438);
    bounds.z=Float(0x3c8)-Float(0x43c);
    *(PlayerBounds3*)((char*)this+0x433c)=bounds;
    bounds.x=Float(0x434)+Float(0x3c0);
    bounds.y=Float(0x438)+Float(0x3c4);
    bounds.z=Float(0x43c)+Float(0x3c8);
    *(PlayerBounds3*)((char*)this+0x4348)=bounds;
    bounds.x=Float(0x3c0)-Float(0x434);
    bounds.y=Float(0x3c4)-Float(0x438);
    bounds.z=Float(0x3c8)-Float(0x43c);
    *(PlayerBounds3*)((char*)this+0x4354)=bounds;
    bounds.x=Float(0x434)+Float(0x3c0);
    bounds.y=Float(0x438)+Float(0x3c4);
    bounds.z=Float(0x43c)+Float(0x3c8);
    *(PlayerBounds3*)((char*)this+0x4360)=bounds;
    InitializeTimer(&timer_474);timer_474.current=0;timer_474.elapsed=0;timer_474.previous=-1;
    InitializeTimer(&final_timer);final_timer.current=120;final_timer.elapsed=120;final_timer.previous=119;
    Word(0x4308)=30;LargePlayerRefresh(this);return 0;
}
#pragma code_seg()
