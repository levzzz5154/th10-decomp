// 0x004390A0..0x004390DC: release every table entry, then the record itself
// when the low bit of the flags argument is set.
extern "C" void __cdecl entry_free_00452422(void* memory);
extern "C" void __cdecl entry_free_004524a1(void* memory);

struct Object_004390a0 {
    void* entries[0x2800];           // +0x0000
    unsigned int count;              // +0xA000
    __declspec(noinline) void* Destroy(unsigned int flags);
};

#pragma code_seg(".text$01accessor")
void* Object_004390a0::Destroy(unsigned int flags) {
    if (count) {
        for (int index = 0; index < 0x2800; ++index) {
            if (entries[index]) {
                entry_free_00452422(entries[index]);
            }
        }
    }
    if (flags & 1) {
        entry_free_004524a1(this);
    }
    return this;
}
#pragma code_seg()
