#include "th10/game/replay_pool_append.hpp"
#include <stdlib.h>
#pragma code_seg(".text$40release")
extern "C" __declspec(noinline) void __stdcall
ReplayPool_Clear(ReplayPoolLists* lists, int stage) {
    ReplayPoolLink2* current = lists->stages[stage].next;
    while (current) {
        ReplayPoolLink2* next = current->next;
        ReplayPool* pool = current->pool;
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
