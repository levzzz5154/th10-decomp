#ifndef TH10_GAME_RESOURCE_CLEANUP_HPP
#define TH10_GAME_RESOURCE_CLEANUP_HPP

#include <stddef.h>
#include "th10/game/scheduler_remove_locked.hpp"

struct ChainNode_00419040 {
    void* block;
    ChainNode_00419040* next;
};
struct Bucket_00419040 {
    ChainNode_00419040* head;
    unsigned int reserved_004[2];
};
struct Manager_00419040 {
    SchedulerTaskPair tasks;
    unsigned char reserved_010[0x0C];
    Bucket_00419040 primary[8];
    Bucket_00419040 secondary[8];
    int keys[10];
    __declspec(noinline) void ClearBuckets();
};

typedef char CleanupTaskPairExtent[sizeof(SchedulerTaskPair)==0x10 ? 1 : -1];
typedef char CleanupBucketExtent[sizeof(Bucket_00419040)==12 ? 1 : -1];
typedef char CleanupPrimaryOffset[offsetof(Manager_00419040,primary)==0x1C ? 1 : -1];
typedef char CleanupSecondaryOffset[offsetof(Manager_00419040,secondary)==0x7C ? 1 : -1];
typedef char CleanupKeysOffset[offsetof(Manager_00419040,keys)==0xDC ? 1 : -1];

#endif
