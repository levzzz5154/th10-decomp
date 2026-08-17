#pragma once

#include <cstdint>

struct LinkedPoolPayload;

// Three-word intrusive list node embedded at the tail of every pool
// payload (retail payload offsets +0x6278 owner / +0x627C next /
// +0x6280 prev; the same links LinkedPool_ReleaseByIndex tears down).
struct LinkedPoolNode {
    LinkedPoolPayload* owner;    // +0x6278, the containing payload
    LinkedPoolNode* next;        // +0x627C
    LinkedPoolNode* previous;    // +0x6280
};

// One 0x6284-byte pool payload. The body is a 0x5460-byte entry area
// followed by a self pointer, a cursor into the entry area, and the
// intrusive list node.
struct LinkedPoolPayload {
    uint32_t entries[0x1518];    // +0x0000..+0x5460 zeroed entry area
    LinkedPoolPayload* self;     // +0x5460 (retail word 0x1518)
    uint32_t reserved[0x189D - 0x1519];  // +0x5464..+0x6274
    uint32_t* entry_cursor;      // +0x6274, points at +0x5464
    LinkedPoolNode node;         // +0x6278..+0x6280
};

// Pool manager fragment: the per-pool list sentinels are three-word
// records starting at retail +0x3C (word index 0xF), so pool index i
// resolves to sentinel word offset i*3 + 0xF.
struct LinkedPoolManager {
    uint32_t reserved_00[0xF];   // +0x00..+0x3C
    LinkedPoolNode lists[8];     // +0x3C.. (retail 12-byte stride)
};

// 0x0042AA50 - Allocate one 0x6284-byte pool payload, zero it, wire its
// self pointer / entry cursor / list node, walk the pool sentinel's
// chain to the tail, and append the payload there. The allocation is
// injected; retail calls the statically linked operator new with size
// 0x6284 (host callers must return at least sizeof(LinkedPoolPayload)).
// Returns the appended payload, or null when the allocator fails (the
// retail body would link a garbage node in that case; the readable form
// returns early instead).
LinkedPoolPayload* LinkedPool_AllocateAndAppend(LinkedPoolManager* manager,
                                                uint32_t pool_index,
                                                void* (*allocate)(uint32_t));
