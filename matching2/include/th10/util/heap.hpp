#pragma once

#include "th10/game/entity.hpp"

// A minimal owner used by the allocation helpers around 0x00435220.
struct HeapBuffer {
    void* data;

    HeapBuffer();
};

// MSVC 7.1 basic_string-compatible storage used by 0x004381F0. Strings of up
// to 15 bytes live inline at +0x04; larger strings store a heap pointer there.
struct LegacyString {
    uint32_t field_000;
    union {
        char inline_data[16];
        void* heap_data;
    } storage;
    uint32_t length;
    uint32_t capacity;
};

void __fastcall HeapBuffer_Release(HeapBuffer* buffer);
void __fastcall LegacyString_Clear(LegacyString* string);
