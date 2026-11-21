struct RuntimeException23 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall crt_exception(RuntimeException23*);
void RuntimeException23::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca94);
    crt_exception(this);
}
