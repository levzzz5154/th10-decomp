struct RuntimeException_004624ab {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException_004624ab* Init(void* message);
};
RuntimeException_004624ab* RuntimeException_004624ab::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46ca00);
    return this;
}
