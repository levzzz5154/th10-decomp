// 0x0045FA9D..0x0045FB5A: seek a CRT descriptor by a signed 64-bit offset.
// The descriptor is checked again after taking its lock because another
// thread can close it between the first check and the lock acquisition.
struct CrtFileEntry_0045fa9d {
    int os_handle;
    unsigned char flags;
    unsigned char other_fields[31];
};

typedef char CrtFileEntry_0045fa9d_size_check[
    sizeof(CrtFileEntry_0045fa9d) == 0x24 ? 1 : -1];

extern "C" CrtFileEntry_0045fa9d* data_00499200[];
extern "C" unsigned int data_004991e4;
extern "C" void __cdecl asm_lock_fhandle_0045f715(int descriptor);
extern "C" void __cdecl asm_FUN_0045f7b5_0045f7b5(int descriptor);
extern "C" int* __cdecl asm_FUN_00456af2_00456af2(void);
extern "C" unsigned int* __cdecl asm_FUN_00456afb_00456afb(void);
extern "C" long long __cdecl CrtFile_Seek64Locked_0045fa1a(
    unsigned int descriptor, long long distance, unsigned int origin);

static long long invalid_descriptor_0045fa9d(void) {
    *asm_FUN_00456af2_00456af2() = 9;
    *asm_FUN_00456afb_00456afb() = 0;
    return -1;
}

extern "C" long long __cdecl asm_unassigned_0045fa9d(
    unsigned int descriptor, long long distance, unsigned int origin) {
    if (descriptor >= data_004991e4)
        return invalid_descriptor_0045fa9d();

    CrtFileEntry_0045fa9d* entry =
        &data_00499200[descriptor >> 5][descriptor & 31];
    if ((entry->flags & 1) == 0)
        return invalid_descriptor_0045fa9d();

    asm_lock_fhandle_0045f715(static_cast<int>(descriptor));
    long long result;
    __try {
        // Reload the table pointer: the lock protects the current slot.
        entry = &data_00499200[descriptor >> 5][descriptor & 31];
        if ((entry->flags & 1) == 0)
            result = invalid_descriptor_0045fa9d();
        else
            result = CrtFile_Seek64Locked_0045fa1a(
                descriptor, distance, origin);
    } __finally {
        asm_FUN_0045f7b5_0045f7b5(static_cast<int>(descriptor));
    }
    return result;
}
