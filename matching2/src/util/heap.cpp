#include "th10/util/heap.hpp"

extern "C" void __cdecl _free(void*);
extern "C" void* __cdecl _memmove(void* destination, const void* source,
                                    uint32_t size);
extern "C" void* operator_new(uint32_t size);
extern "C" void LegacyString_ThrowLengthError(void);
extern "C" void LegacyString_ThrowRangeError(void);

// 0x004352C0 - Initialize an empty allocation owner.
HeapBuffer::HeapBuffer() : data(0) {
}

// 0x00438690 - The element count is part of the allocator ABI but unused.
void LegacyAllocator::Deallocate(void* memory, uint32_t count) {
    (void)count;
    _free(memory);
}

// 0x004386A0 - Maximum byte count accepted by this allocator.
uint32_t LegacyAllocator::MaxSize() const {
    return 0xFFFFFFFE;
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

// 0x00438260 - Assign a bounded substring from another LegacyString.
LegacyString* LegacyString::AssignSubstring(
        const LegacyString* source, uint32_t offset, uint32_t count) {
    if (source->length < offset) {
        LegacyString_ThrowRangeError();
    }

    uint32_t available = source->length - offset;
    if (available < count) {
        count = available;
    }

    if (this == source) {
        Erase(offset + count, 0xFFFFFFFF);
        Erase(0, offset);
        return this;
    }

    if (count == 0xFFFFFFFF) {
        LegacyString_ThrowLengthError();
    }
    if (capacity < count) {
        Grow(count, length);
    } else if (count == 0) {
        SetLength(0);
        return this;
    }

    if (count != 0) {
        const char* source_data = source->Data() + offset;
        char* destination = Data();
        uint32_t words = count >> 2;
        while (words-- != 0) {
            *(uint32_t*)destination = *(const uint32_t*)source_data;
            destination += 4;
            source_data += 4;
        }
        uint32_t bytes = count & 3;
        while (bytes-- != 0) {
            *destination++ = *source_data++;
        }
        SetLength(count);
    }
    return this;
}

// 0x00438510 - Remove a bounded range and close the gap in place.
LegacyString* LegacyString::Erase(uint32_t offset, uint32_t count) {
    if (length < offset) {
        LegacyString_ThrowRangeError();
    }
    uint32_t available = length - offset;
    if (available < count) {
        count = available;
    }
    if (count != 0) {
        char* data = Data();
        _memmove(data + offset, data + offset + count, available - count);
        SetLength(length - count);
    }
    return this;
}

// 0x00438590 - Update the logical length and write its terminator.
void LegacyString::SetLength(uint32_t new_length) {
    length = new_length;
    if (capacity >= 16) {
        ((char*)storage.heap_data)[new_length] = 0;
    } else {
        storage.inline_data[new_length] = 0;
    }
}

// 0x00438680 - Select inline or allocated character storage. The const and
// mutable instantiations fold to the same retail body.
char* LegacyString::Data() {
    if (capacity >= 16) {
        return (char*)storage.heap_data;
    }
    return storage.inline_data;
}

const char* LegacyString::Data() const {
    if (capacity >= 16) {
        return (const char*)storage.heap_data;
    }
    return storage.inline_data;
}

// 0x004386B0 + 0x0043874C - Grow using the retail 1.5x capacity policy while
// preserving the requested prefix and switching cleanly out of inline mode.
void LegacyString::Grow(uint32_t requested, uint32_t old_length) {
    uint32_t new_capacity = requested | 15;
    if (new_capacity > 0xFFFFFFFE) {
        new_capacity = requested;
    } else {
        uint32_t half = capacity >> 1;
        if (new_capacity / 3 < half && capacity <= 0xFFFFFFFE - half) {
            new_capacity = capacity + half;
        }
    }

    char* allocation = (char*)operator_new(new_capacity + 1);
    const char* old_data = Data();
    for (uint32_t index = 0; index < old_length; ++index) {
        allocation[index] = old_data[index];
    }
    if (capacity >= 16) {
        _free(storage.heap_data);
    }
    storage.inline_data[0] = 0;
    storage.heap_data = allocation;
    capacity = new_capacity;
    length = old_length;
    allocation[old_length] = 0;
}
