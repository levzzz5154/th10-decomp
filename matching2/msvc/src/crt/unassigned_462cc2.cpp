struct RuntimeException16 {
    void* vtable;
    const char* message;
    const char* What();
    void BaseInitAddress(void** message);
    void BaseInitValue(void* message);
    RuntimeException16* InitAddress(void* message);
    RuntimeException16* InitValue(void* message);
};
const char* RuntimeException16::What() {
    return message ? message : reinterpret_cast<const char*>(0x46ca70);
}
RuntimeException16* RuntimeException16::InitAddress(void* message) {
    BaseInitAddress(&message);
    vtable = reinterpret_cast<void*>(0x46ca88);
    return this;
}
RuntimeException16* RuntimeException16::InitValue(void* message) {
    BaseInitValue(message);
    vtable = reinterpret_cast<void*>(0x46ca88);
    return this;
}
