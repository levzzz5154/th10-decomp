#pragma once

#include "th10/game/entity.hpp"

// A minimal owner used by the allocation helpers around 0x00435220.
struct HeapBuffer {
    void* data;

    HeapBuffer();
};

// Stateless allocator used by the retail basic_string implementation.
struct LegacyAllocator {
    void Deallocate(void* memory, uint32_t count);
    uint32_t MaxSize() const;
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

    void Assign(const char* text);
    LegacyString* AssignRange(const char* text, uint32_t length);
    LegacyString* AssignSubstring(
        const LegacyString* source, uint32_t offset, uint32_t length);
    void Grow(uint32_t requested, uint32_t old_length);
    LegacyString* Erase(uint32_t offset, uint32_t count);
    void SetLength(uint32_t new_length);
    char* Data();
    const char* Data() const;
};

void __fastcall HeapBuffer_Release(HeapBuffer* buffer);
void __fastcall LegacyString_Clear(LegacyString* string);
