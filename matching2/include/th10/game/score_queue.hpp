#pragma once

#include <cstdint>

// One popup node in the score display queue (retail 32-bit word offsets
// in comments).
struct ScorePopupNode {
    const void* vtable;    // word 0
    ScorePopupNode* prev;  // word 1, previous tail at link time
    ScorePopupNode* next;  // word 2
    uint32_t id;           // word 0x15, queue-assigned identifier
};

// Queue fields inside the score manager (retail offsets in comments).
struct ScorePopupQueue {
    ScorePopupNode* tail;  // +0x434
    int32_t count;         // +0x438, capped at 0x100 entries
    int32_t next_id;       // +0x43C, wraps from 0 to 1
};

// 0x0041C510 - Push one popup onto the score queue. When the queue
// holds more than 0xFF entries the call returns 0. Otherwise the id
// counter advances (skipping 0), and kind 0 allocates a 0xD58-byte
// plain popup (retail constructor 0x0041C5B0) while kind 1 allocates a
// 0xD74-byte score view (retail constructor 0x0041C680); any other kind
// just returns the advanced id. The new node records the id, links
// behind the previous tail, bumps the count, becomes the tail, and its
// second vtable entry runs (injected as on_attached). Retail would
// dereference a failed allocation; the readable form skips the link
// instead. Returns the current id counter.
uint32_t ScoreQueue_Push(ScorePopupQueue* queue, int32_t kind,
                         void* (*allocate)(uint32_t size),
                         ScorePopupNode* (*construct_plain)(void* memory),
                         ScorePopupNode* (*construct_view)(void* memory),
                         void (*on_attached)(ScorePopupNode* node));
