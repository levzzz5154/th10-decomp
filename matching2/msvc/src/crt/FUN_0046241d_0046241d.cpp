struct RuntimeException_0046241d {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall asm_FUN_00462371_00462371(RuntimeException_0046241d*);
void RuntimeException_0046241d::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca00);
    asm_FUN_00462371_00462371(this);
}
