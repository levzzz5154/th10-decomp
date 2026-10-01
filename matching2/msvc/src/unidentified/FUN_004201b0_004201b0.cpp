#include "th10/platform/worker.hpp"
#include "th10/platform/native_game_input.hpp"
#include "th10/render/clip_worker_native.hpp"
#include "th10/platform/native_font_start.hpp"
struct StatsTaskOwner;
StatsTaskOwner *__cdecl CreateStatsTaskOwner_00413350();
void __cdecl InitializeVersionMarker_00420100();
extern "C" {
void __cdecl RenderCamera_InitializeDefaults_004216f0();
void __cdecl Sound_PreloadWorker_0043d080();
unsigned int __cdecl GameWorker_0043ba90();
__declspec(dllimport) unsigned long __stdcall timeGetTime();
typedef unsigned long (__stdcall *RawThreadEntry)(void*);
__declspec(dllimport) void *__stdcall CreateThread(void*,unsigned long,RawThreadEntry,void*,unsigned long,unsigned long*);
unsigned int __cdecl beginthreadex_00453683(void*,unsigned int,PlatformWorkerEntry,void*,unsigned int,unsigned int*);
extern float data_00476f78;
extern unsigned int data_004923a8,data_00491ff8;
extern unsigned short data_004918a8;
extern unsigned char data_00492590;
extern void *data_004977ac;
extern PlatformWorker data_00474dd4;
}
#pragma code_seg(".text$a00worker")
extern "C" __declspec(noinline) int __cdecl StartGameWorkers_004201b0() {
    InitializeVersionMarker_00420100();
    data_00476f78=1.0f;data_004923a8=0xff000000;
    RenderCamera_InitializeDefaults_004216f0();
    unsigned long now=timeGetTime();data_00491ff8=now;
    data_004918b0.seed=(unsigned short)now;data_004918a8=(unsigned short)now;
    unsigned long thread_id;
    data_004977ac=CreateThread(0,0,reinterpret_cast<RawThreadEntry>(&Sound_PreloadWorker_0043d080),&data_00492590,0,&thread_id);
    CreateStatsTaskOwner_00413350();
    data_00474dd4.Stop();
    data_00474dd4.entry=reinterpret_cast<PlatformWorkerEntry>(&GameWorker_0043ba90);
    data_00474dd4.running=1;data_00474dd4.stop_requested=0;
    data_00474dd4.thread=reinterpret_cast<void*>(beginthreadex_00453683(0,0,reinterpret_cast<PlatformWorkerEntry>(&GameWorker_0043ba90),&data_00491c28,0,&data_00474dd4.thread_id));
    data_00491c10->InitializeClip();
    InitializeFontCache_00437a00();
    return 0;
}
#pragma code_seg()
