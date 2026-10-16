// 0x004390A0..0x004390DC: release every table entry, then the record itself
// when the low bit of the flags argument is set.
extern "C" void __cdecl crt_free(void* memory);
extern "C" void __cdecl crt_free_startup(void* memory);

struct Object22 {
    void* entries[0x2800];           // +0x0000
    unsigned int count;              // +0xA000
    __declspec(noinline) void* Destroy(unsigned int flags);
};

#pragma code_seg(".text$01accessor")
void* Object22::Destroy(unsigned int flags) {
    if (count) {
        for (int index = 0; index < 0x2800; ++index) {
            if (entries[index]) {
                crt_free(entries[index]);
            }
        }
    }
    if (flags & 1) {
        crt_free_startup(this);
    }
    return this;
}
#pragma code_seg()
