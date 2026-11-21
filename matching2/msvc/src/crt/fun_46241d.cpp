struct RuntimeException8 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall asm_FUN_00462371_00462371(RuntimeException8*);
void RuntimeException8::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca00);
    asm_FUN_00462371_00462371(this);
}
