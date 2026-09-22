struct LegacyString_004624c3 {
    unsigned char reserved[0x18];
    unsigned int capacity;
    void SetLength(unsigned int size);
    void Assign(const char* source);
    LegacyString_004624c3* Init(const char* source);
};
LegacyString_004624c3* LegacyString_004624c3::Init(const char* source) {
    capacity = 15;
    SetLength(0);
    Assign(source);
    return this;
}
