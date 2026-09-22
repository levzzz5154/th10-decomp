struct RuntimeException_00462d00 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall asm_exception_00462cac(RuntimeException_00462d00*);
void RuntimeException_00462d00::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca88);
    asm_exception_00462cac(this);
}
