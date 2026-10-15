#pragma once
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/worker.hpp"

struct LoadingView {
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

typedef char LoadingOwner_primary_offset[
    offsetof(LoadingView, primary_task) == 8 ? 1 : -1];
typedef char LoadingOwner_secondary_offset[
    offsetof(LoadingView, secondary_task) == 12 ? 1 : -1];
typedef char LoadingOwner_worker_offset[
    offsetof(LoadingView, worker) == 16 ? 1 : -1];
typedef char LoadingOwner_logo_offset[
    offsetof(LoadingView, logo_animation) == 0x3e0 ? 1 : -1];
