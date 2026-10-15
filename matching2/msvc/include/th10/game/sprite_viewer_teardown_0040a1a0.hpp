#pragma once
#include "th10/game/sprite_viewer_draw_0040a940.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/platform/worker.hpp"

extern "C" void __cdecl free(void* block);
void __cdecl operator delete(void* block);

// The game managers the screen created in its startup step; it owns them and
// deletes each one here. Only their destructors matter to this screen.
struct SpriteViewerItems_0040a1a0 : SpriteViewerTaskPair_0040a940 {
    __declspec(noinline) ~SpriteViewerItems_0040a1a0();      // 0x004145F0
    __declspec(noinline) void Reset();                       // 0x00413BC0
};
struct SpriteViewerPlayer_0040a1a0 : SpriteViewerTaskPair_0040a940 {
    __declspec(noinline) ~SpriteViewerPlayer_0040a1a0();     // 0x00424ED0
    __declspec(noinline) void SuspendAndStop();              // 0x0040A010
    __declspec(noinline) void Reset();                       // 0x00424D90
};
struct SpriteViewerBullets_0040a1a0 : SpriteViewerTaskPair_0040a940 {
    __declspec(noinline) ~SpriteViewerBullets_0040a1a0();    // 0x00405F70
    __declspec(noinline) void Reset();                       // 0x00405ED0
};
struct SpriteViewerLasers_0040a1a0 {
    __declspec(noinline) ~SpriteViewerLasers_0040a1a0();     // 0x00405620
};
struct SpriteViewerEffects_0040a1a0 : SpriteViewerTaskPair_0040a940 {
    unsigned char reserved_010[4];
    unsigned int slots[0x873A8];

    __declspec(noinline) ~SpriteViewerEffects_0040a1a0();    // 0x0041ADF0
};
struct SpriteViewerPopups_0040a1a0 {
    __declspec(noinline) ~SpriteViewerPopups_0040a1a0();     // 0x0042B570
};

extern "C" {
extern SpriteViewerItems_0040a1a0* data_0047770c;
extern SpriteViewerPlayer_0040a1a0* g_player;
extern SpriteViewerBullets_0040a1a0* data_004776f0;
extern SpriteViewerLasers_0040a1a0* g_bomb;
extern SpriteViewerEffects_0040a1a0* data_00477818;
extern SpriteViewerPopups_0040a1a0* data_00477840;
extern SpriteViewer_0040a940* data_004776f8;
extern void* data_00491be4;          // the scheduler
}
// 0x00449F60: unlink one task; the caller holds the scheduler lock.
__declspec(noinline) void __stdcall ManagerTeardownScheduler_Remove_00449F60(Scheduler*, SchedulerTask*);
