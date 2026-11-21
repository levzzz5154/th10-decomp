struct LegacyString4 {
    unsigned char reserved[0x18];
    unsigned int capacity;
    void SetLength(unsigned int size);
    void Assign(const char* source);
    LegacyString4* Init(const char* source);
};
LegacyString4* LegacyString4::Init(const char* source) {
    capacity = 15;
    SetLength(0);
    Assign(source);
    return this;
}
