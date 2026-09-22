struct RuntimeException_00462d77 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall asm_exception_00462cac(RuntimeException_00462d77*);
void RuntimeException_00462d77::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca94);
    asm_exception_00462cac(this);
}
