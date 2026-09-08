#include "th10/util/heap.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void __cdecl entry_free_004524a1(void*);
#ifdef _MSC_VER
void* __cdecl operator new(uint32_t size);
#else
void* operator new(decltype(sizeof(0)) size);
#endif

HeapBuffer::HeapBuffer() : data(0) {
}

void* LegacyAllocator::Allocate(uint32_t count) {
    return ::operator new(count);
}

void LegacyAllocator::Deallocate(void* memory, uint32_t count) {
    (void)count;
    entry_free_004524a1(memory);
}

uint32_t LegacyAllocator::MaxSize() const {
    return 0xFFFFFFFE;
}

void __fastcall HeapBuffer_Release(HeapBuffer* buffer) {
    void* data = buffer->data;
    if (data != 0) {
        entry_free_00452422(data);
        buffer->data = 0;
    }
}

void __fastcall LegacyString_Clear(LegacyString* string) {
    if (string->capacity >= 16)
        entry_free_004524a1(string->storage.heap_data);
    string->capacity = 15;
    string->length = 0;
    string->storage.inline_data[0] = 0;
}

uint32_t LegacyString::Length() const {
    return length;
}

bool LegacyString::OwnsPointer(const char* pointer) const {
    if (pointer >= Data() && Data() + length > pointer)
        return true;
    return false;
}

char* LegacyString::Data() {
    if (capacity >= 16)
        return (char*)storage.heap_data;
    return storage.inline_data;
}

const char* LegacyString::Data() const {
    if (capacity >= 16)
        return (const char*)storage.heap_data;
    return storage.inline_data;
}

// 0x00438590: update the logical length and terminate the active inline or
// heap-backed character buffer.
void LegacyString::SetLength(uint32_t new_length) {
    length = new_length;

    char* data;
    if (capacity >= 16)
        data = storage.heap_data;
    else
        data = storage.inline_data;
    data[new_length] = 0;
}
