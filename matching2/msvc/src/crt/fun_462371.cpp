struct LegacyString3 {
    void Reserve(unsigned char reset, unsigned int capacity);
};
struct RuntimeException {
    void* vtable;
    unsigned char reserved[8];
    LegacyString3 message;
    void BaseDestroy();
    void Destroy();
};
void RuntimeException::Destroy() {
    vtable = reinterpret_cast<void*>(0x46c9e8);
    message.Reserve(1, 0);
    BaseDestroy();
}
