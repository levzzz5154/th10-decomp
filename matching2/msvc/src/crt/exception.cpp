struct RuntimeException12 {
    void* vtable;
    void* message;
    int owns_message;
    RuntimeException12* Init();
};
RuntimeException12* RuntimeException12::Init() {
    message = 0;
    owns_message = 0;
    vtable = reinterpret_cast<void*>(0x46ca68);
    return this;
}
