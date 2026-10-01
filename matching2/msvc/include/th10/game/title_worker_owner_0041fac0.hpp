#pragma once
#include "th10/game/scheduler.hpp"
#include "th10/platform/worker.hpp"

struct TitleWorkerOwner {
    unsigned char reserved_00[8];
    SchedulerTask* primary_task;             // +0x08
    SchedulerTask* secondary_task;           // +0x0c
    PlatformWorker worker;                  // +0x10

    __declspec(noinline) int StartWorker();
};

typedef char TitleWorkerOwner_primary_offset[
    offsetof(TitleWorkerOwner, primary_task) == 8 ? 1 : -1];
typedef char TitleWorkerOwner_secondary_offset[
    offsetof(TitleWorkerOwner, secondary_task) == 12 ? 1 : -1];
typedef char TitleWorkerOwner_worker_offset[
    offsetof(TitleWorkerOwner, worker) == 16 ? 1 : -1];
