struct RuntimeException3 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException3* Init(void* message);
};
RuntimeException3* RuntimeException3::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46c9f4);
    return this;
}
