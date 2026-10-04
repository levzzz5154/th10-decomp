#pragma once
#include "th10/platform/worker.hpp"

struct AnimationResource_00449870;
struct DispatcherVec3;

// The game UI's embedded worker, synchronization state and position markers.
struct GameUiThreadHost {
    unsigned char reserved_000[0x3c8];
    AnimationResource_00449870* marker_resource;   // +0x3c8
    unsigned char reserved_3cc[0x260];
    PlatformWorker worker;                  // +0x62c
    unsigned char reserved_648[0x94];
    unsigned char critical_section[24];     // +0x6dc, Win32 CRITICAL_SECTION
    unsigned char reserved_6f4[6];
    unsigned char spawning;                 // +0x6fa
    int markers_created;                    // +0x6fc

    __declspec(noinline) int Spawn(PlatformWorkerEntry start, void* context);
    __declspec(noinline) void StopWorker();
    __declspec(noinline) void CreateMarkers(const DispatcherVec3* position);
};

typedef char GameUiThreadHost_resource_offset[(offsetof(GameUiThreadHost, marker_resource) == 0x3c8) ? 1 : -1];
typedef char GameUiThreadHost_worker_offset[(offsetof(GameUiThreadHost, worker) == 0x62c) ? 1 : -1];
typedef char GameUiThreadHost_lock_offset[(offsetof(GameUiThreadHost, critical_section) == 0x6dc) ? 1 : -1];
typedef char GameUiThreadHost_spawning_offset[(offsetof(GameUiThreadHost, spawning) == 0x6fa) ? 1 : -1];
typedef char GameUiThreadHost_markers_offset[(offsetof(GameUiThreadHost, markers_created) == 0x6fc) ? 1 : -1];
