struct RuntimeException21 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException21* Init(void* message);
};
RuntimeException21* RuntimeException21::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46caa0);
    return this;
}

struct RuntimeException22 {
    void* vtable;
    void BaseInit(void* message);
    RuntimeException22* Init(void* message);
};
RuntimeException22* RuntimeException22::Init(void* message) {
    BaseInit(message);
    vtable = reinterpret_cast<void*>(0x46caa0);
    return this;
}
