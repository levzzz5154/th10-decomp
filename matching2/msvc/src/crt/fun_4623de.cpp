struct RuntimeException5 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall crt_helper_462371(RuntimeException5*);
void RuntimeException5::Destroy() {
    vtable = reinterpret_cast<void*>(0x46c9f4);
    crt_helper_462371(this);
}
