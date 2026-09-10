#pragma once

#include "th10/types.hpp"

// A minimal owner used by the allocation helpers around 0x00435220.
struct HeapBuffer {
    void* data;

    HeapBuffer();
};

// Stateless allocator used by the retail basic_string implementation.
struct LegacyAllocator {
    void* Allocate(uint32_t count);
    void Deallocate(void* memory, uint32_t count);
    uint32_t MaxSize() const;
};

// MSVC 7.1 basic_string-compatible storage used by 0x004381F0. Strings of up
// to 15 bytes live inline at +0x04; larger strings store a heap pointer there.
struct LegacyString {
    uint32_t allocator_cookie;
    union {
        char inline_data[16];
        char* heap_data;
    } storage;
    uint32_t length;
    uint32_t capacity;

    LegacyString* Assign(const char* text);
    LegacyString* AssignRange(const char* text, uint32_t length);
    LegacyString* AssignSubstring(
        const LegacyString* source, uint32_t offset, uint32_t length);
    void Grow(uint32_t requested, uint32_t old_length);
    bool EnsureCapacity(uint32_t requested, bool trim = false);
    LegacyString* Erase(uint32_t offset, uint32_t count);
    void SetLength(uint32_t new_length);
    uint32_t Length() const;
    // 0x00438380 resets storage to the inline representation. It does not
    // reserve capacity. new_length must fit in the 15-byte inline buffer.
    // A false release_heap is for initializing an unbuilt string.
    void ResetInlineStorage(bool release_heap, uint32_t new_length);
    bool OwnsPointer(const char* pointer) const;
    char* Data();
    const char* Data() const;

private:
    void ThrowLengthError() const;
};

void __fastcall HeapBuffer_Release(HeapBuffer* buffer);
void Heap_DestroyOwned(void* object, void (*cleanup)(void*),
                       void (*free_memory)(void*));
void Heap_DestroyOwnedSecondary(void* object, void (*cleanup)(void*),
                                void (*free_memory)(void*));
void __fastcall LegacyString_Clear(LegacyString* string);
char* LegacyString_Duplicate(const char* text);
