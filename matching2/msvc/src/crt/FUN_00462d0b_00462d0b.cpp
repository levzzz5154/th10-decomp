struct RuntimeException_00462d0b {
    void* vtable;
    void BaseInit(void** message);
    RuntimeException_00462d0b* Init(void* message);
};
RuntimeException_00462d0b* RuntimeException_00462d0b::Init(void* message) {
    BaseInit(&message);
    vtable = reinterpret_cast<void*>(0x46ca94);
    return this;
}
