// 0x00462363: the string's own pointer: the pointer member while the string
// is large, the inline buffer otherwise.
//
// std::basic_string keeps a 16-byte buffer and the pointer in one union at
// +0x10; the capacity at +0x24 chooses between them. The image tests the
// capacity against the small-string size and leaves the buffer arm out of
// line, so the large arm is the one written first.

struct StringBase_00462363 {
    unsigned char pad_000[0x10];
    union {
        char buffer[0x10];
        char* pointer;
    } storage;                   // +0x0010
    unsigned int reserved;       // +0x0020
    unsigned int capacity;       // +0x0024
    const char* Myptr() const;
};

const char* StringBase_00462363::Myptr() const {
    if (capacity >= 0x10)
        return storage.pointer;
    return storage.buffer;
}
