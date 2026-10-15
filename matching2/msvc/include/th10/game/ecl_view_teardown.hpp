#pragma once
#include "th10/game/ecl_view_draw.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/platform/worker.hpp"

extern "C" void __cdecl free(void* block);
void __cdecl operator delete(void* block);

// The game managers the screen created in its startup step; it owns them and
// deletes each one here. Only their destructors matter to this screen.
struct EclViewItems_0040a1a0 : EclViewTaskPair_0040a940 {
    __declspec(noinline) ~EclViewItems_0040a1a0();      // 0x004145F0
    __declspec(noinline) void Reset();                       // 0x00413BC0
};
struct EclViewPlayer_0040a1a0 : EclViewTaskPair_0040a940 {
    __declspec(noinline) ~EclViewPlayer_0040a1a0();     // 0x00424ED0
    __declspec(noinline) void SuspendAndStop();              // 0x0040A010
    __declspec(noinline) void Reset();                       // 0x00424D90
};
struct EclViewBullets_0040a1a0 : EclViewTaskPair_0040a940 {
    __declspec(noinline) ~EclViewBullets_0040a1a0();    // 0x00405F70
    __declspec(noinline) void Reset();                       // 0x00405ED0
};
struct EclViewLasers_0040a1a0 {
    __declspec(noinline) ~EclViewLasers_0040a1a0();     // 0x00405620
};
struct EclViewEffects_0040a1a0 : EclViewTaskPair_0040a940 {
    unsigned char reserved_010[4];
    unsigned int slots[0x873A8];

    __declspec(noinline) ~EclViewEffects_0040a1a0();    // 0x0041ADF0
};
struct EclViewPopups_0040a1a0 {
    __declspec(noinline) ~EclViewPopups_0040a1a0();     // 0x0042B570
};

extern "C" {
extern EclViewItems_0040a1a0* g_front;
extern EclViewPlayer_0040a1a0* g_player;
extern EclViewBullets_0040a1a0* g_bullet_manager;
extern EclViewLasers_0040a1a0* g_bomb;
extern EclViewEffects_0040a1a0* g_item_manager;
extern EclViewPopups_0040a1a0* g_smoll_score;
extern EclView_0040a940* g_ecl_view;
extern void* g_func_ctrl;          // the scheduler
}
// 0x00449F60: unlink one task; the caller holds the scheduler lock.
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove_00449F60(FuncCtrl*, SchedulerTask*);
