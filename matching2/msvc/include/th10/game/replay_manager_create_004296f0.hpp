#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"
#include "th10/game/replay_pool_append_0042aa50.hpp"

void* __cdecl operator new(unsigned int size);
void __cdecl operator delete(void* block);

// One 0x24-byte list node of the replay manager; built by 0x0042AC20 and
// unlinked by 0x0042AC60.
struct ReplayManagerNode_004296f0 {
    unsigned char storage[0x24];

    __declspec(noinline) ReplayManagerNode_004296f0();
    __declspec(noinline) ~ReplayManagerNode_004296f0();
};

// The replay file's 0x24-byte header and 0x64-byte summary; plain data.
struct ReplayHeader_004296f0 {
    unsigned char storage[0x24];
};
struct ReplaySummary_004296f0 {
    unsigned char storage[0x64];
};
struct ReplayStageData_004296f0;

// The 0x2D4-byte replay manager.
struct ReplayManager_004296f0 {
    unsigned char reserved_000[8];
    SchedulerTask* update_task;
    SchedulerTask* draw_task;
    int mode;                               // 0 = record, 1 = play back, 2 = file opened directly
    ReplayHeader_004296f0* header;
    ReplaySummary_004296f0* summary;
    ReplayStageData_004296f0* stage_data[8];
    ReplayPoolLink_0042aa50 stages[8];      // +0x3C, the input pools of each stage
    ReplayPoolLink_0042aa50* current_pool;
    ReplayManagerNode_004296f0 nodes[8];
    unsigned char reserved_1c0[0x1CC - 0x1C0];
    SchedulerTask* trailing_task;           // +0x1CC
    unsigned int reserved_1d0;
    char path[0x100];

    // The pool lists are laid out as the pool functions expect them.
    ReplayPoolLists_0042aa50* PoolLists() {
        return reinterpret_cast<ReplayPoolLists_0042aa50*>(this);
    }
    // Free every input pool of one stage.
    void ClearStage(int stage);

    ReplayManager_004296f0() { memset(this, 0, sizeof(*this)); }
    __declspec(noinline) ~ReplayManager_004296f0();    // 0x004294A0
    // 0x0042A200: remember the replay file's path and read it; nonzero on failure.
    __declspec(noinline) int Initialize(const char* replay_path);
    // 0x00428F60: start recording (mode 0) or play back the named replay
    // (mode 1); nonzero on failure.
    __declspec(noinline) int Start(int start_mode, const char* replay_path);
};
typedef char ReplayManagerSize_004296f0[sizeof(ReplayManager_004296f0) == 0x2D4 ? 1 : -1];
typedef char ReplayManagerNodes_004296f0[offsetof(ReplayManager_004296f0, nodes) == 0xA0 ? 1 : -1];
typedef char ReplayManagerPath_004296f0[offsetof(ReplayManager_004296f0, path) == 0x1D4 ? 1 : -1];

// 0x0042AB20: free every input pool of one stage.
extern "C" __declspec(noinline) void __stdcall ReplayPool_Clear_0042ab20(ReplayPoolLists_0042aa50* lists, int stage);
inline void ReplayManager_004296f0::ClearStage(int stage) {
    ReplayPool_Clear_0042ab20(PoolLists(), stage);
}
__declspec(noinline) void __stdcall ManagerTeardownScheduler_Remove_00449F60(Scheduler* scheduler, SchedulerTask* task);
extern "C" void* data_00491be4;
// The replay manager the game is currently using.
extern "C" ReplayManager_004296f0* data_00477838;

__declspec(noinline) ReplayManager_004296f0* __stdcall ReplayManager_Create_004296f0(const char* replay_path);
__declspec(noinline) ReplayManager_004296f0* __stdcall ReplayManager_Create_00429610(int start_mode, const char* replay_path);
