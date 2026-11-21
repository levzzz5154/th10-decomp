struct RuntimeException9 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException9* Init(void* message);
};
RuntimeException9* RuntimeException9::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46ca00);
    return this;
}
