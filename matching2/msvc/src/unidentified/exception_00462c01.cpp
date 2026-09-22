struct RuntimeException_00462c01 {
    void* vtable;
    void* message;
    int owns_message;
    RuntimeException_00462c01* Init();
};
RuntimeException_00462c01* RuntimeException_00462c01::Init() {
    message = 0;
    owns_message = 0;
    vtable = reinterpret_cast<void*>(0x46ca68);
    return this;
}
