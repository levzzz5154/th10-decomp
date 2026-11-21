struct RuntimeException5 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall asm_FUN_00462371_00462371(RuntimeException5*);
void RuntimeException5::Destroy() {
    vtable = reinterpret_cast<void*>(0x46c9f4);
    asm_FUN_00462371_00462371(this);
}
