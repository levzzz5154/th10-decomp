struct RuntimeException6 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException6* Init(void* message);
};
RuntimeException6* RuntimeException6::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46ca00);
    return this;
}
