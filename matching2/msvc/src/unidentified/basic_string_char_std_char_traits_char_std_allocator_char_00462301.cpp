struct LegacyString_00462301 {
    unsigned char reserved[0x18];
    unsigned int capacity;
    void SetLength(unsigned int size);
    void AssignSubstring(const LegacyString_00462301* source, unsigned int offset, unsigned int count);
    LegacyString_00462301* Init(const LegacyString_00462301* source);
};
LegacyString_00462301* LegacyString_00462301::Init(const LegacyString_00462301* source) {
    capacity = 15;
    SetLength(0);
    AssignSubstring(source, 0, 0xffffffff);
    return this;
}
