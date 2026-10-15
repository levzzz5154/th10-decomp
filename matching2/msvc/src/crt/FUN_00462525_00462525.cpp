struct RuntimeException_00462525 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException_00462525* Init(void* message);
};
RuntimeException_00462525* RuntimeException_00462525::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46c9f4);
    return this;
}
