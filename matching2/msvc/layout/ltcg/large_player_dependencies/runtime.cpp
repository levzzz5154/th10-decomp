#include "th10/game/large_player_native.hpp"
#include "th10/platform/archive_callers.hpp"
#include "th10/platform/text_log.hpp"
#include "th10/game/scheduler.hpp"
struct CachedResource;
CachedResource* __fastcall Recovery_LoadCachedResource(int,void*,const char*);
extern "C" {
    extern unsigned int data_00474c68,data_00474c6c;
    extern void* data_00491c10;
    extern ParameterFile* data_00491bf0;
    extern Scheduler* data_00491be4;
    extern char data_0046e42c[],data_0046e420[],data_0046e3ec[];
    extern const char* data_00476fc0[];
    extern TextLog_0044b810 data_00474f70;
    extern float data_00470b44,data_00470b0c,data_00476f78;
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
        timer->elapsed=0;timer->speed=&data_00476f78;timer->flags|=1;
    }
}
#pragma code_seg(".text$a07body")
int PlayerResetBlock::Initialize() {
    const char* name=data_00474c68 ? data_0046e420:data_0046e42c;
    CachedResource* resource=Recovery_LoadCachedResource(8,data_00491c10,name);
    Word(0x10)=(unsigned int)resource;
    if (!resource) { data_00474f70.Append(data_0046e3ec); return -1; }
    if (data_00491bf0) {
        Word(0x45c)=(unsigned int)data_00491bf0;data_00491bf0=0;
    } else {
        const char* parameter_name=data_00476fc0[data_00474c6c+3*data_00474c68];
        if (((ParameterLoader*)this)->Load(parameter_name)) {
            data_00474f70.Append(data_0046e3ec);return -1;
        }
    }
    SchedulerTask* task=LargePlayerCallbackCreate(LargePlayerTick);
    task->context=this;*(unsigned int*)((char*)task+4)&=~2u;
    Scheduler_RegisterPrimary(data_00491be4,task,0x10);Word(8)=(unsigned int)task;
    task=LargePlayerCallbackCreate(LargePlayerDraw);
    *(unsigned int*)((char*)task+4)&=~2u;task->context=this;
    Scheduler_RegisterSecondary(data_00491be4,task,0x16);Word(0xc)=(unsigned int)task;
    ConfigureResource_00404f30 script_resource={(void*)Word(0x10)};
    ((ItemConfiguredEntity_00404f30*)&slot)->Configure(0,script_resource);
    Float(0x3c0)=0;Float(0x3c4)=400;
    Word(0x3cc)=0;Word(0x3d0)=40000;
    ParameterFile* parameters=(ParameterFile*)Word(0x45c);
    Word(0x3d4)=(int)(parameters->width*data_00470b44);
    Word(0x3d8)=(int)(parameters->height*data_00470b44);
    Word(0x3dc)=(int)(parameters->projected_width*data_00470b44);
    Word(0x3e0)=(int)(parameters->projected_height*data_00470b44);
    for (int i=0;i<33;++i) {
        Word(0x436c+i*8)=Word(0x3cc);Word(0x4370+i*8)=Word(0x3d0);
    }
    InitializeTimer(&timer_460);timer_460.elapsed=-1;timer_460.previous=-2;timer_460.current=-1;
    // Character tables initialize the three leading parameter words at +4,+C,+8.
    *(float*)((char*)Word(0x45c)+4)=data_00476fb8[data_00474c68];
    *(float*)((char*)Word(0x45c)+12)=data_00476fb0[data_00474c68];
    *(float*)((char*)Word(0x45c)+8)=data_00476fa0[data_00474c68];
    float half=*(float*)((char*)Word(0x45c)+4)*data_00470b0c;
    Float(0x424)=5;Float(0x420)=half;Float(0x41c)=half;
    half=data_00476fb0[data_00474c68]*data_00470b0c;
    Float(0x430)=5;Float(0x42c)=half;Float(0x428)=half;
    half=data_00476fa8[data_00474c68]*data_00470b0c;
    Float(0x43c)=5;Float(0x438)=half;Float(0x434)=half;
#define LARGE_BOUNDS(base,extent) \
    Float(base)=Float(0x3c0)-Float(extent); \
    Float(base+4)=Float(0x3c4)-Float(extent+4); \
    Float(base+8)=Float(0x3c8)-Float(extent+8); \
    Float(base+12)=Float(extent)+Float(0x3c0); \
    Float(base+16)=Float(extent+4)+Float(0x3c4); \
    Float(base+20)=Float(extent+8)+Float(0x3c8)
    LARGE_BOUNDS(0x404,0x41c);LARGE_BOUNDS(0x4324,0x428);
    LARGE_BOUNDS(0x433c,0x434);LARGE_BOUNDS(0x4354,0x434);
#undef LARGE_BOUNDS
    InitializeTimer(&timer_474);timer_474.current=0;timer_474.elapsed=0;timer_474.previous=-1;
    InitializeTimer(&final_timer);final_timer.current=120;final_timer.elapsed=120;final_timer.previous=119;
    Word(0x4308)=30;LargePlayerRefresh(this);return 0;
}
#pragma code_seg()
