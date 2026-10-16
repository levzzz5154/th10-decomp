struct LegacyString2 {
    unsigned char reserved[0x18];
    unsigned int capacity;
    void SetLength(unsigned int size);
    void AssignSubstring(const LegacyString2* source, unsigned int offset, unsigned int count);
    LegacyString2* Init(const LegacyString2* source);
};
LegacyString2* LegacyString2::Init(const LegacyString2* source) {
    capacity = 15;
    SetLength(0);
    AssignSubstring(source, 0, 0xffffffff);
    return this;
}
