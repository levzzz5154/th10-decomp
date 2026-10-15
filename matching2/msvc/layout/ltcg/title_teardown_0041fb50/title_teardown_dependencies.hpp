#pragma once
#include "message_teardown_dependencies.hpp"
#include "th10/platform/worker.hpp"
#include "th10/game/entity.hpp"
#include "title_score_archive.hpp"

struct TitleWorker_0044C130 {
    virtual ~TitleWorker_0044C130();
    void* thread;
    unsigned int thread_id;
    unsigned int stop_requested;
    unsigned int running;
    unsigned int reserved_14;
    PlatformWorkerEntry entry;
    inline void Stop() { reinterpret_cast<PlatformWorker*>(this)->Stop(); }
};

struct TitleAnimation_00401FF0 : Entity {
    ~TitleAnimation_00401FF0();
};

struct TitleState_0041FB50 {
    unsigned int flags;
    unsigned int reserved_004;
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    TitleWorker_0044C130 worker;
    unsigned char reserved_02c[4];
    TitleAnimation_00401FF0 animation;
    unsigned char reserved_3dc[0x14];
    __declspec(noinline) ~TitleState_0041FB50();
};

typedef char TitleWorkerOffset[offsetof(TitleState_0041FB50,worker)==0x10?1:-1];
typedef char TitleAnimationOffset[offsetof(TitleState_0041FB50,animation)==0x30?1:-1];
typedef char TitleResourceOffset[offsetof(TitleState_0041FB50,animation)+offsetof(Entity,resource)==0x388?1:-1];
typedef char TitleSize[sizeof(TitleState_0041FB50)==0x3F0?1:-1];

struct GameThread;
extern "C" void* data_00491be4;
extern "C" void* data_00477820;
extern "C" void* g_ascii_manager;
extern "C" void* data_0047783c;
extern "C" void* data_00477810;
extern "C" void* data_0047784c;
extern "C" void* data_00477838;
extern "C" void* data_00477700;
extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void __stdcall DestroyGameThread_00401260(GameThread*);
extern "C" __declspec(noinline) int __cdecl ReleasePair_0041f930();
