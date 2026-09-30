#pragma once
#include "th10/platform/worker.hpp"

// The game UI's embedded worker and synchronization state.
struct GameUiThreadHost {
    unsigned char reserved_000[0x62c];
    PlatformWorker worker;                  // +0x62c
    unsigned char reserved_648[0x94];
    unsigned char critical_section[24];     // +0x6dc, Win32 CRITICAL_SECTION
    unsigned char reserved_6f4[6];
    unsigned char spawning;                 // +0x6fa

    __declspec(noinline) int Spawn(PlatformWorkerEntry start, void* context);
};

typedef char GameUiThreadHost_worker_offset[(offsetof(GameUiThreadHost, worker) == 0x62c) ? 1 : -1];
typedef char GameUiThreadHost_lock_offset[(offsetof(GameUiThreadHost, critical_section) == 0x6dc) ? 1 : -1];
typedef char GameUiThreadHost_spawning_offset[(offsetof(GameUiThreadHost, spawning) == 0x6fa) ? 1 : -1];
