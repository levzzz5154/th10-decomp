struct RuntimeException18 {
    void* vtable;
    void BaseInit(void** message);
    RuntimeException18* Init(void* message);
};
RuntimeException18* RuntimeException18::Init(void* message) {
    BaseInit(&message);
    vtable = reinterpret_cast<void*>(0x46ca94);
    return this;
}
