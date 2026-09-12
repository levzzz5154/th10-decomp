// 0x0042AB20 FUN_0042ab20
// Readable reconstruction of retail helper FUN_0042ab20.
//
// See the header for the linked-list layout.  The readable body matches
// the retail control flow exactly: walk next-pointers, capture the
// payload at each node, unlink the payload from its doubly-linked list
// (patching prev->next and next->prev when those neighbours exist) and
// then free it.

#include "th10/game/linked_pool_release.hpp"

#include <cstdint>


extern "C" void _free(void* memory);


void LinkedPool_ReleaseByIndex(void* owner, uint32_t pool_index) {
    if (owner == 0) return;
    uint8_t* base = static_cast<uint8_t*>(owner);
    // The pool head lives at owner + 0x40 + i*0xc as a value: a pointer
    // to the first list node.  Each list node is an 8-byte
    // (payload*, next_node*) pair.  The retail payload's doubly-linked
    // list lives at payload + 0x627c (prev) / +0x6280 (next) as 32-bit
    // pointers — on a 64-bit host the upper 4 bytes would overlap, so
    // the readable helper mirrors the retail 4-byte layout by truncating
    // each slot to uint32_t.
    void** head_slot = reinterpret_cast<void**>(
        base + 0x40 + pool_index * 0xc);
    void** node = static_cast<void**>(*head_slot);
    while (node != 0) {
        void* payload = node[0];
        void** next = static_cast<void**>(node[1]);
        if (payload != 0) {
            uint8_t* payload_bytes = static_cast<uint8_t*>(payload);
            uint32_t* payload_prev =
                reinterpret_cast<uint32_t*>(payload_bytes + 0x627c);
            uint32_t* payload_next =
                reinterpret_cast<uint32_t*>(payload_bytes + 0x6280);
            uint32_t prev_addr = *payload_prev;
            uint32_t next_addr = *payload_next;
            if (prev_addr != 0) {
                // prev->next = payload->next   (stored at +0x8 of the prev)
                *reinterpret_cast<uint32_t*>(
                    static_cast<uintptr_t>(prev_addr) + 8) = next_addr;
            }
            if (next_addr != 0) {
                // next->prev = payload->prev   (stored at +0x4 of the next)
                *reinterpret_cast<uint32_t*>(
                    static_cast<uintptr_t>(next_addr) + 4) = prev_addr;
            }
            *payload_prev = 0;
            *payload_next = 0;
            _free(payload);
        }
        node = next;
    }
    *head_slot = 0;
}