#pragma once

// LegacyString growth/assign exception-cleanup funclets (retail 0x00438723, 0x004387C2).

// ABI-compatible view of the string block used by the retail funclets:
// a 16-byte inline buffer that becomes a heap pointer once the capacity
// grows past 15 characters.
struct LegacyStringPayload {
    union {
        char inline_text[16];
        char* heap_text;
    } storage;
    unsigned int length;
    unsigned int capacity;
};

void* LegacyString_GrowthCatchAllocate(unsigned int requested_length,
                                       void* (*allocate)(unsigned int size));

void LegacyString_AssignCatchRelease(LegacyStringPayload* text,
                                     void (*free_memory)(void* memory),
                                     void (*rethrow)(void));
