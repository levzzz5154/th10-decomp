#include "th10/game/linked_pool_append.hpp"


#include <cstring>

// 0x0042AA50 - Allocate and append one pool payload. Retail carries the
// pool index in ESI (compiler-reserved register, like the release path
// at 0x0042AB20) and takes the manager as the stack argument. After
// zeroing the 0x18A1-word payload the retail body wires the self
// pointer at word 0x1518, points the entry cursor at word 0x1519, and
// initializes the three-word intrusive node; it then follows the
// sentinel chain at manager word offset pool_index*3 + 0xF to the last
// node and appends. The dead "patch a non-null successor" branch after
// the tail walk (its condition is false by construction) is dropped.

LinkedPoolPayload* LinkedPool_AllocateAndAppend(LinkedPoolManager* manager,
                                                uint32_t pool_index,
                                                void* (*allocate)(uint32_t)) {
    LinkedPoolPayload* payload =
        allocate != 0 ? (LinkedPoolPayload*)allocate(0x6284) : 0;
    if (payload == 0) {
        return 0;
    }
    memset(payload, 0, sizeof(*payload));
    payload->self = payload;
    payload->entry_cursor = payload->reserved;
    payload->node.owner = payload;
    payload->node.next = 0;
    payload->node.previous = 0;

    LinkedPoolNode* tail = &manager->lists[pool_index];
    while (tail->next != 0) {
        tail = tail->next;
    }
    tail->next = &payload->node;
    payload->node.previous = tail;
    return payload;
}
