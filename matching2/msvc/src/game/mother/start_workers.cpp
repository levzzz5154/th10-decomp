// 0x004201B0: the app's start-up: seed the timers and random state, then start
// the input, sound-preload and stats worker threads.
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
unsigned int __cdecl Input_InitThread();
__declspec(dllimport) unsigned long __stdcall timeGetTime();
typedef unsigned long (__stdcall *RawThreadEntry)(void*);
__declspec(dllimport) void *__stdcall CreateThread(void*,unsigned long,RawThreadEntry,void*,unsigned long,unsigned long*);
unsigned int __cdecl beginthreadex_00453683(void*,unsigned int,PlatformWorkerEntry,void*,unsigned int,unsigned int*);
extern float g_game_speed;
extern unsigned int g_main_clear_color,g_startup_time;
extern unsigned short g_rng_seed_copy;
extern unsigned char g_sound_manager;
extern void *g_sound_preload_thread;
extern PlatformWorker g_input_worker;
}
#pragma code_seg(".text$a00worker")
extern "C" __declspec(noinline) int __cdecl App_StartWorkers() {
    InitializeVersionMarker_00420100();
    g_game_speed=1.0f;g_main_clear_color=0xff000000;
    RenderCamera_InitializeDefaults_004216f0();
    unsigned long now=timeGetTime();g_startup_time=now;
    g_rng.seed=(unsigned short)now;g_rng_seed_copy=(unsigned short)now;
    unsigned long thread_id;
    g_sound_preload_thread=CreateThread(0,0,reinterpret_cast<RawThreadEntry>(&Sound_PreloadWorker_0043d080),&g_sound_manager,0,&thread_id);
    CreateStatsTaskOwner_00413350();
    g_input_worker.Stop();
    g_input_worker.entry=reinterpret_cast<PlatformWorkerEntry>(&Input_InitThread);
    g_input_worker.running=1;g_input_worker.stop_requested=0;
    g_input_worker.thread=reinterpret_cast<void*>(beginthreadex_00453683(0,0,reinterpret_cast<PlatformWorkerEntry>(&Input_InitThread),&g_application,0,&g_input_worker.thread_id));
    g_sprt_ctrl->InitializeClip();
    InitializeFontCache_00437a00();
    return 0;
}
#pragma code_seg()
