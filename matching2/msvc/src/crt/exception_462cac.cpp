struct RuntimeException15 {
    void* vtable;
    void* message;
    int owns_message;
    void Destroy();
};
extern "C" void __cdecl asm_free_00452422(void*);
void RuntimeException15::Destroy() {
    bool owned = owns_message != 0;
    vtable = reinterpret_cast<void*>(0x46ca68);
    if (owned)
        asm_free_00452422(message);
}
