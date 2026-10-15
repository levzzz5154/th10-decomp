struct RuntimeException_00462cc2 {
    void* vtable;
    const char* message;
    const char* What();
    void BaseInitAddress(void** message);
    void BaseInitValue(void* message);
    RuntimeException_00462cc2* InitAddress(void* message);
    RuntimeException_00462cc2* InitValue(void* message);
};
const char* RuntimeException_00462cc2::What() {
    return message ? message : reinterpret_cast<const char*>(0x46ca70);
}
RuntimeException_00462cc2* RuntimeException_00462cc2::InitAddress(void* message) {
    BaseInitAddress(&message);
    vtable = reinterpret_cast<void*>(0x46ca88);
    return this;
}
RuntimeException_00462cc2* RuntimeException_00462cc2::InitValue(void* message) {
    BaseInitValue(message);
    vtable = reinterpret_cast<void*>(0x46ca88);
    return this;
}
