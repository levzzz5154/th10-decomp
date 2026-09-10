#include "th10/util/heap.hpp"
#include <string.h>
#include <new>

extern "C" void __cdecl LegacyString_ThrowOutOfRange();
extern "C" void __cdecl entry_free_004524a1(void*);

char* LegacyString::Data() {
    if (capacity >= 16)
        return storage.heap_data;
    return storage.inline_data;
}

const char* LegacyString::Data() const {
    if (capacity >= 16)
        return storage.heap_data;
    return storage.inline_data;
}

void LegacyString::SetLength(uint32_t new_length) {
    length = new_length;

    char* data;
    if (capacity >= 16)
        data = storage.heap_data;
    else
        data = storage.inline_data;
    data[new_length] = 0;
}

// 0x00438510 - Clamp the erase count and move the remaining suffix in place.
LegacyString* LegacyString::Erase(uint32_t offset, uint32_t count) {
    if (length < offset)
        LegacyString_ThrowOutOfRange();
    uint32_t remaining = length - offset;
    if (remaining < count)
        count = remaining;
    if (count > 0) {
        memmove(Data() + offset, Data() + offset + count, remaining - count);
        SetLength(length - count);
    }
    return this;
}

bool LegacyString::OwnsPointer(const char* pointer) const {
    if (pointer >= Data() && Data() + length > pointer)
        return true;
    return false;
}

// 0x00438420 - A source inside this string uses substring assignment so
// overlapping input is preserved before the string is shortened.
LegacyString* LegacyString::AssignRange(const char* text, uint32_t count) {
    if (OwnsPointer(text))
        return AssignSubstring(this, text - Data(), count);
    if (count > 0xFFFFFFFEu)
        ThrowLengthError();
    if (capacity < count)
        Grow(count, length);
    else if (count == 0) {
        SetLength(0);
        return this;
    }
    if (count > 0) {
        memcpy(Data(), text, count);
        SetLength(count);
    }
    return this;
}

// 0x00438260 - Bound the source range; self-assignment erases suffix then prefix.
LegacyString* LegacyString::AssignSubstring(
    const LegacyString* source, uint32_t offset, uint32_t count) {
    if (source->length < offset)
        LegacyString_ThrowOutOfRange();
    uint32_t remaining = source->length - offset;
    if (count < remaining)
        remaining = count;
    if (this == source) {
        Erase(offset + remaining, 0xFFFFFFFFu);
        Erase(0, offset);
        return this;
    }
    if (remaining > 0xFFFFFFFEu)
        ThrowLengthError();
    if (capacity < remaining)
        Grow(remaining, length);
    else if (remaining == 0) {
        SetLength(0);
        return this;
    }
    if (remaining > 0) {
        memcpy(Data(), source->Data() + offset, remaining);
        SetLength(remaining);
    }
    return this;
}

// 0x00438380 - Copy back to inline storage before releasing the old buffer.
void LegacyString::ResetInlineStorage(bool release_heap, uint32_t new_length) {
    if (release_heap && capacity >= 16) {
        char* old_storage = storage.heap_data;
        if (new_length > 0)
            memcpy(storage.inline_data, old_storage, new_length);
        entry_free_004524a1(old_storage);
    }
    capacity = 15;
    SetLength(new_length);
}

// 0x004385B0 - Grow when needed, or move a trimmed small string back inline.
bool LegacyString::EnsureCapacity(uint32_t requested, bool trim) {
    if (requested > 0xFFFFFFFEu)
        ThrowLengthError();
    if (capacity < requested)
        Grow(requested, length);
    else if (trim && requested < 16)
        ResetInlineStorage(true, requested < length ? requested : length);
    else if (requested == 0)
        SetLength(0);
    return requested > 0;
}

// 0x004386B0 - Round up or grow geometrically, then retry without spare
// capacity if allocation fails. A second failure clears storage and rethrows.
void LegacyString::Grow(uint32_t requested, uint32_t old_length) {
    uint32_t new_capacity = requested | 15;
    if (new_capacity > 0xFFFFFFFEu)
        new_capacity = requested;
    else if (new_capacity / 3 < capacity / 2 &&
             capacity <= 0xFFFFFFFEu - capacity / 2)
        new_capacity = capacity + capacity / 2;

    char* new_storage;
    try {
        new_storage = static_cast<char*>(::operator new(new_capacity + 1));
    } catch (...) {
        new_capacity = requested;
        try {
            new_storage = static_cast<char*>(::operator new(new_capacity + 1));
        } catch (...) {
            ResetInlineStorage(true, 0);
            throw;
        }
    }

    if (old_length > 0)
        memcpy(new_storage, Data(), old_length);
    ResetInlineStorage(true, 0);
    storage.heap_data = new_storage;
    capacity = new_capacity;
    SetLength(old_length);
}

// 0x00438350 - The compiler supplies the aligned strlen loop, including the
// three bytes of internal alignment at 0x0043835D.
LegacyString* LegacyString::Assign(const char* text) {
    return AssignRange(text, strlen(text));
}

// 0x004381F0 - Release owned heap storage and restore an empty inline string.
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
