struct RuntimeException8 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall crt_helper_462371(RuntimeException8*);
void RuntimeException8::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca00);
    crt_helper_462371(this);
}
