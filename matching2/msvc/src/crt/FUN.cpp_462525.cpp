struct RuntimeException10 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException10* Init(void* message);
};
RuntimeException10* RuntimeException10::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46c9f4);
    return this;
}
