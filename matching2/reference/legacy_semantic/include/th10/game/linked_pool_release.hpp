// 0x0042AB20 FUN_0042ab20
// Readable reconstruction of retail helper FUN_0042ab20.
//
// FUN_0042ab20 walks a per-pool linked list (the list head lives at
// ``owner + 0x40 + pool_index * 0xc``) and tears down each entry.  Each
// list node is an 8-byte (payload_ptr, next_node_ptr) pair; the payload
// itself is linked into a separate doubly-linked list stored at
// payload + 0x627c (prev) / + 0x6280 (next).  Before freeing the
// payload, retail unlinks it from the doubly-linked list (patching the
// adjacent prev/next pointers, then zeroing the payload's slots) and
// then calls _free.
//
// The readable signature exposes the pool index explicitly because the
// retail ABI has it carried in EAX across the call (compiler-reserved
// register); the function is otherwise straightforward.

#ifndef TH10_GAME_LINKED_POOL_RELEASE_HPP
#define TH10_GAME_LINKED_POOL_RELEASE_HPP

#include <cstdint>

// Walk the singly-linked list stored at ``owner + 0x40 + pool_index*0xc``
// and tear down each entry: unlink the payload's node from the
// doubly-linked list stored at payload + 0x627c/+0x6280, then free the
// payload.  Safe to call with owner == 0 (no-op).
void LinkedPool_ReleaseByIndex(void* owner, uint32_t pool_index);

#endif  // TH10_GAME_LINKED_POOL_RELEASE_HPP