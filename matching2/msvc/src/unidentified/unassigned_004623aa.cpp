struct RuntimeException_004623aa {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException_004623aa* Init(void* message);
};
RuntimeException_004623aa* RuntimeException_004623aa::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46c9f4);
    return this;
}
