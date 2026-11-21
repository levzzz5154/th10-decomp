struct RuntimeException20 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall crt_exception(RuntimeException20*);
void RuntimeException20::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca94);
    crt_exception(this);
}
