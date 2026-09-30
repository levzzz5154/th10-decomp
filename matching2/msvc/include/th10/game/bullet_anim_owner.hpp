#pragma once
// The object 0x0040B3A0 destroys and 0x0040B920 deletes: it names five
// animations and owns a worker thread at +0xD0.
#include "th10/platform/worker.hpp"

struct BulletAnimOwner {
    unsigned char unknown_000[0x40];
    int animation_ids[5];        // +0x40
    unsigned char unknown_054[0xD0 - 0x54];
    PlatformWorker worker;       // +0xD0

    void Destroy();
};

typedef char BulletAnimOwner_worker_offset_must_be_0xd0[
    offsetof(BulletAnimOwner, worker) == 0xD0 ? 1 : -1];
