struct CrtFileEntry_0045f5d9 {
    int os_handle;
    unsigned char flags;
    unsigned char other_fields[31];
};

typedef char CrtFileEntry_0045f5d9_size_check[
    sizeof(CrtFileEntry_0045f5d9) == 0x24 ? 1 : -1];

extern "C" unsigned int data_004991e4;
extern "C" CrtFileEntry_0045f5d9* data_00499200[];
extern "C" int data_00473074;
extern "C" unsigned int (__stdcall *data_004661bc)(
    unsigned int standard_handle, unsigned int os_handle);
extern "C" int* __cdecl asm_FUN_00456af2_00456af2();
extern "C" unsigned int* __cdecl asm_FUN_00456afb_00456afb();

namespace {

__forceinline CrtFileEntry_0045f5d9* FileEntry(unsigned int descriptor) {
    return &data_00499200[descriptor >> 5][descriptor & 31];
}

__forceinline unsigned int StandardHandleKind(unsigned int descriptor) {
    return static_cast<unsigned int>(-10 - static_cast<int>(descriptor));
}

__forceinline int InvalidDescriptor() {
    *asm_FUN_00456af2_00456af2() = 9;
    *asm_FUN_00456afb_00456afb() = 0;
    return -1;
}

} // namespace

// 0x0045F5D9..0x0045F654: install an OS handle in a vacant CRT descriptor.
extern "C" int __cdecl CrtFile_SetOsHandle_0045f5d9(
    unsigned int descriptor, unsigned int os_handle) {
    if (descriptor >= data_004991e4)
        return InvalidDescriptor();

    CrtFileEntry_0045f5d9* entry = FileEntry(descriptor);
    if (entry->os_handle != -1)
        return InvalidDescriptor();

    if (data_00473074 == 1 && descriptor < 3)
        data_004661bc(StandardHandleKind(descriptor), os_handle);
    entry->os_handle = static_cast<int>(os_handle);
    return 0;
}

// 0x0045F655..0x0045F6D3: release the OS handle stored in a CRT descriptor.
extern "C" int __cdecl CrtFile_FreeOsHandle_0045f655(
    unsigned int descriptor) {
    if (descriptor >= data_004991e4)
        return InvalidDescriptor();

    CrtFileEntry_0045f5d9* entry = FileEntry(descriptor);
    if ((entry->flags & 1) == 0 || entry->os_handle == -1)
        return InvalidDescriptor();

    if (data_00473074 == 1 && descriptor < 3)
        data_004661bc(StandardHandleKind(descriptor), 0);
    entry->os_handle = -1;
    return 0;
}
