#include "th10/util/heap.hpp"

extern "C" void __cdecl _free(void*);
extern "C" void LegacyString_ThrowLengthError(void);

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

// 0x00438350 - Assign a null-terminated byte string.
void LegacyString::Assign(const char* text) {
    const char* end = text;
    char current;
    do {
        current = *end;
        ++end;
    } while (current != 0);
    AssignRange(text, end - (text + 1));
}

// 0x00438420 - Assign an explicit byte range, preserving small-string storage
// and handling ranges which point back into this string.
LegacyString* LegacyString::AssignRange(const char* text, uint32_t count) {
    char* current = capacity < 16
        ? storage.inline_data
        : (char*)storage.heap_data;

    if (text >= current && text < current + length) {
        return AssignSubstring(this, text - current, count);
    }

    if (count == 0xFFFFFFFF) {
        LegacyString_ThrowLengthError();
    }

    if (capacity < count) {
        Grow(count, length);
    } else if (count == 0) {
        length = 0;
        current = capacity < 16
            ? storage.inline_data
            : (char*)storage.heap_data;
        current[0] = 0;
        return this;
    }

    if (count != 0) {
        current = capacity < 16
            ? storage.inline_data
            : (char*)storage.heap_data;
        uint32_t words = count >> 2;
        uint32_t* destination_word = (uint32_t*)current;
        const uint32_t* source_word = (const uint32_t*)text;
        while (words-- != 0) {
            *destination_word++ = *source_word++;
        }
        uint32_t bytes = count & 3;
        char* destination_byte = (char*)destination_word;
        const char* source_byte = (const char*)source_word;
        while (bytes-- != 0) {
            *destination_byte++ = *source_byte++;
        }
        length = count;
        current[count] = 0;
    }
    return this;
}
