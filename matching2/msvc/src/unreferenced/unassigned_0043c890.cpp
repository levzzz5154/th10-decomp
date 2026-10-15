// 0x0043C890..0x0043C8A8: release the record and free it when the low bit of
// the flags argument is set.
extern "C" void __stdcall recovery_release_0043cb00(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);

struct Object_0043c890 {
    __declspec(noinline) void* Destroy(unsigned int flags);
};

#pragma code_seg(".text$01accessor")
void* Object_0043c890::Destroy(unsigned int flags) {
    recovery_release_0043cb00(this);
    if (flags & 1) {
        crt_free_startup(this);
    }
    return this;
}
#pragma code_seg()
