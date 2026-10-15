#include "types.hpp"
#include <stdlib.h>
// One 0x6284-byte page of input records (th10/game/linked_pool_append.hpp).
struct ReplayPoolPage {
    unsigned char records[0x5460];
    ReplayPoolPage* scratch_page;   // +0x5460
    unsigned char scratch[0xE10];
    unsigned char* scratch_cursor;           // +0x6274
    ReplayPoolLink_0042a6a0 link;            // +0x6278

    ReplayPoolPage() {
        memset(this, 0, sizeof(*this));
        scratch_page = this;
        scratch_cursor = scratch;
        link.page = this;
        link.next = 0;
        link.previous = 0;
    }
};
typedef char ReplayPoolPageSize_0042a6a0[sizeof(ReplayPoolPage) == 0x6284 ? 1 : -1];

// The body of 0x0042AA50.
#pragma code_seg(".text$0042aa50_fn")
ReplayPoolLink_0042a6a0* ReplayManager_0042a6a0::AppendPage(int stage) {
    ReplayPoolLink_0042a6a0* link = &(new ReplayPoolPage)->link;
    ReplayPoolLink_0042a6a0* tail = &pools[stage];
    while (tail->next)
        tail = tail->next;
    if (tail->next) {
        link->next = tail->next;
        tail->next->previous = link;
    }
    tail->next = link;
    link->previous = tail;
    return link;
}

// The body of 0x0042AB20.
#pragma code_seg(".text$0042ab20_fn")
extern "C" __declspec(noinline) void __stdcall
ReplayFinishClearPools(ReplayManager_0042a6a0* manager, int stage) {
    ReplayPoolLink_0042a6a0* current = manager->pools[stage].next;
    while (current) {
        ReplayPoolLink_0042a6a0* next = current->next;
        ReplayPoolPage* pool = current->page;
        if (pool) {
            if (pool->link.next) pool->link.next->previous = pool->link.previous;
            if (pool->link.previous) pool->link.previous->next = pool->link.next;
            pool->link.next = 0;
            pool->link.previous = 0;
            free(pool);
        }
        current = next;
    }
}
#pragma code_seg()
