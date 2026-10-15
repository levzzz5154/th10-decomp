struct LegacyString_00462371 {
    void Reserve(unsigned char reset, unsigned int capacity);
};
struct RuntimeException_00462371 {
    void* vtable;
    unsigned char reserved[8];
    LegacyString_00462371 message;
    void BaseDestroy();
    void Destroy();
};
void RuntimeException_00462371::Destroy() {
    vtable = reinterpret_cast<void*>(0x46c9e8);
    message.Reserve(1, 0);
    BaseDestroy();
}
