#pragma once
#include "message_teardown_dependencies.hpp"
#include "th10/platform/worker.hpp"
#include "th10/game/entity.hpp"
#include "title_score_archive.hpp"

struct Loading_0044C130 {
    virtual ~Loading_0044C130();
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

struct TitleState {
    unsigned int flags;
    unsigned int reserved_004;
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    Loading_0044C130 worker;
    unsigned char reserved_02c[4];
    TitleAnimation_00401FF0 animation;
    unsigned char reserved_3dc[0x14];
    __declspec(noinline) ~TitleState();
};

typedef char LoadingOffset[offsetof(TitleState,worker)==0x10?1:-1];
typedef char TitleAnimationOffset[offsetof(TitleState,animation)==0x30?1:-1];
typedef char TitleResourceOffset[offsetof(TitleState,animation)+offsetof(Entity,resource)==0x388?1:-1];
typedef char TitleSize[sizeof(TitleState)==0x3F0?1:-1];

struct GameThread;
extern "C" void* g_func_ctrl;
extern "C" void* g_loading;
extern "C" void* g_ascii_manager;
extern "C" void* g_score;
extern "C" void* g_game;
extern "C" void* g_title;
extern "C" void* g_replay;
extern "C" void* g_ending;
extern "C" void __cdecl crt_free(void*);
extern "C" void __stdcall DestroyGameThread(GameThread*);
extern "C" __declspec(noinline) int __cdecl ReleasePair2();
