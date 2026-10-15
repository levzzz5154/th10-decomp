#pragma once
#include "th10/game/ecl_view_draw.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/platform/worker.hpp"

extern "C" void __cdecl free(void* block);
void __cdecl operator delete(void* block);

// The game managers the screen created in its startup step; it owns them and
// deletes each one here. Only their destructors matter to this screen.
struct EclViewItems : EclViewTaskPair {
    __declspec(noinline) ~EclViewItems();      // 0x004145F0
    __declspec(noinline) void Reset();                       // 0x00413BC0
};
struct EclViewPlayer : EclViewTaskPair {
    __declspec(noinline) ~EclViewPlayer();     // 0x00424ED0
    __declspec(noinline) void SuspendAndStop();              // 0x0040A010
    __declspec(noinline) void Reset();                       // 0x00424D90
};
struct EclViewBullets : EclViewTaskPair {
    __declspec(noinline) ~EclViewBullets();    // 0x00405F70
    __declspec(noinline) void Reset();                       // 0x00405ED0
};
struct EclViewLasers {
    __declspec(noinline) ~EclViewLasers();     // 0x00405620
};
struct EclViewEffects : EclViewTaskPair {
    unsigned char reserved_010[4];
    unsigned int slots[0x873A8];

    __declspec(noinline) ~EclViewEffects();    // 0x0041ADF0
};
struct EclViewPopups {
    __declspec(noinline) ~EclViewPopups();     // 0x0042B570
};

extern "C" {
extern EclViewItems* g_front;
extern EclViewPlayer* g_player;
extern EclViewBullets* g_bullet_manager;
extern EclViewLasers* g_bomb;
extern EclViewEffects* g_item_manager;
extern EclViewPopups* g_smoll_score;
extern EclView* g_ecl_view;
extern void* g_func_ctrl;          // the scheduler
}
// 0x00449F60: unlink one task; the caller holds the scheduler lock.
__declspec(noinline) void __stdcall ManagerTeardownFuncCtrl_Remove(FuncCtrl*, SchedulerTask*);
