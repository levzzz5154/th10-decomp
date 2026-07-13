#include "th10/util/heap.hpp"

extern "C" void __cdecl _free(void*);

// 0x004352C0 - Initialize an empty allocation owner.
HeapBuffer::HeapBuffer() : data(0) {
}

// 0x00435250 - Release a nullable heap buffer.
void __fastcall HeapBuffer_Release(HeapBuffer* buffer) {
    void* data = buffer->data;
    if (data) {
        _free(data);
        buffer->data = 0;
    }
}

// 0x004381F0 - Reset an MSVC 7.1 small-string object to its empty state.
void __fastcall LegacyString_Clear(LegacyString* string) {
    if (string->capacity >= 16) {
        _free(string->storage.heap_data);
    }
    string->capacity = 15;
    string->length = 0;
    string->storage.inline_data[0] = 0;
}
