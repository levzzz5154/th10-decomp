struct RuntimeException19 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException19* Init(void* message);
};
RuntimeException19* RuntimeException19::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46ca94);
    return this;
}
