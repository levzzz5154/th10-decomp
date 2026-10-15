struct RuntimeException_00462d24 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException_00462d24* Init(void* message);
};
RuntimeException_00462d24* RuntimeException_00462d24::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46ca94);
    return this;
}
