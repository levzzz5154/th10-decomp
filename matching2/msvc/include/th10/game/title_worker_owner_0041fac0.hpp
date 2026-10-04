#pragma once
#include "th10/game/scheduler.hpp"
#include "th10/platform/worker.hpp"

struct TitleWorkerOwner {
    unsigned char reserved_00[8];
    SchedulerTask* primary_task;             // +0x08
    SchedulerTask* secondary_task;           // +0x0c
    PlatformWorker worker;                  // +0x10
    unsigned char reserved_2c[0x3e0 - 0x2c];
    void* logo_animation;                    // +0x3e0, sig.anm
    int logo_loaded;                         // +0x3e4
    int game_thread_created;                 // +0x3e8

    __declspec(noinline) int StartWorker();
    // 0x0041F8D0. The body only uses globals, so the receiver is never read.
    __declspec(noinline) int LoadStartupResources();
};

typedef char TitleWorkerOwner_primary_offset[
    offsetof(TitleWorkerOwner, primary_task) == 8 ? 1 : -1];
typedef char TitleWorkerOwner_secondary_offset[
    offsetof(TitleWorkerOwner, secondary_task) == 12 ? 1 : -1];
typedef char TitleWorkerOwner_worker_offset[
    offsetof(TitleWorkerOwner, worker) == 16 ? 1 : -1];
typedef char TitleWorkerOwner_logo_offset[
    offsetof(TitleWorkerOwner, logo_animation) == 0x3e0 ? 1 : -1];
