struct RuntimeException20 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall asm_exception_00462cac(RuntimeException20*);
void RuntimeException20::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca94);
    asm_exception_00462cac(this);
}
