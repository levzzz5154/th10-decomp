#ifndef TH10_GAME_RESOURCE_CLEANUP_HPP
#define TH10_GAME_RESOURCE_CLEANUP_HPP

#include <stddef.h>
#include "th10/game/scheduler_remove_locked.hpp"

struct ChainNode {
    void* block;
    ChainNode* next;
};
struct Bucket2 {
    ChainNode* head;
    unsigned int reserved_004[2];
};
struct Manager3 {
    SchedulerTaskPair tasks;
    unsigned char reserved_010[0x0C];
    Bucket2 primary[8];
    Bucket2 secondary[8];
    int keys[10];
    __declspec(noinline) void ClearBuckets();
};

typedef char CleanupTaskPairExtent[sizeof(SchedulerTaskPair)==0x10 ? 1 : -1];
typedef char CleanupBucketExtent[sizeof(Bucket2)==12 ? 1 : -1];
typedef char CleanupPrimaryOffset[offsetof(Manager3,primary)==0x1C ? 1 : -1];
typedef char CleanupSecondaryOffset[offsetof(Manager3,secondary)==0x7C ? 1 : -1];
typedef char CleanupKeysOffset[offsetof(Manager3,keys)==0xDC ? 1 : -1];

#endif
