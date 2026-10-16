// 0x004383E0..0x004383ED: the small-string pointer: the heap pointer when the
// recorded capacity at +0x18 has reached 0x10, the inline buffer at +0x4
// otherwise.
struct LegacyText {
    unsigned char pad_000[4];
    char* heap;                      // +0x04
    unsigned char pad_008[0x10];
    unsigned int capacity;           // +0x18

    __declspec(noinline) const char* Text() const;
};

const char* LegacyText::Text() const {
    if (capacity >= 0x10) {
        return heap;
    }
    return (const char*)this + 4;
}
