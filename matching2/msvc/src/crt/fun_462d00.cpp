struct RuntimeException17 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall asm_exception_00462cac(RuntimeException17*);
void RuntimeException17::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca88);
    asm_exception_00462cac(this);
}
