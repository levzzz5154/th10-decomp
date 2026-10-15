#include "th10/game/replay_pool_append_0042aa50.hpp"
#include <stdlib.h>
#pragma code_seg(".text$40release")
extern "C" __declspec(noinline) void __stdcall
ReplayPool_Clear_0042ab20(ReplayPoolLists_0042aa50* lists, int stage) {
    ReplayPoolLink_0042aa50* current = lists->stages[stage].next;
    while (current) {
        ReplayPoolLink_0042aa50* next = current->next;
        ReplayPool_0042aa50* pool = current->pool;
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
