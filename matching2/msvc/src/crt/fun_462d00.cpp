struct RuntimeException17 {
    void* vtable;
    void Destroy();
};
extern "C" void __fastcall crt_exception(RuntimeException17*);
void RuntimeException17::Destroy() {
    vtable = reinterpret_cast<void*>(0x46ca88);
    crt_exception(this);
}
