struct RuntimeException_004623e9 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException_004623e9* Init(void* message);
};
RuntimeException_004623e9* RuntimeException_004623e9::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46ca00);
    return this;
}
