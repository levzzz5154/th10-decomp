struct CrtFileEntry_0045fa1a {
    int os_handle;
    unsigned char flags;
    unsigned char other_fields[31];
};

typedef char CrtFileEntry_0045fa1a_size_check[
    sizeof(CrtFileEntry_0045fa1a) == 0x24 ? 1 : -1];

extern "C" CrtFileEntry_0045fa1a* data_00499200[];
extern "C" int __cdecl asm_get_osfhandle_0045f6d4(int descriptor);
extern "C" int* __cdecl asm_FUN_00456af2_00456af2();
extern "C" void __cdecl asm_dosmaperr_00456b04(unsigned int error);
extern "C" unsigned int (__stdcall *data_004660c8)(
    unsigned int handle, int distance_low, int* distance_high,
    unsigned int origin);
extern "C" unsigned int (__stdcall *data_0046610c)();

// 0x0045FA1A..0x0045FA9C: seek a locked CRT descriptor by a 64-bit offset.
extern "C" long long __cdecl CrtFile_Seek64Locked_0045fa1a(
    unsigned int descriptor, long long distance, unsigned int origin) {
    const int os_handle = asm_get_osfhandle_0045f6d4(
        static_cast<int>(descriptor));
    if (os_handle == -1) {
        *asm_FUN_00456af2_00456af2() = 9;
        return -1;
    }

    const int distance_low = static_cast<int>(distance);
    int distance_high = static_cast<int>(distance >> 32);
    const unsigned int new_low = data_004660c8(
        static_cast<unsigned int>(os_handle), distance_low, &distance_high,
        origin);
    if (new_low == 0xFFFFFFFFu) {
        const unsigned int error = data_0046610c();
        if (error != 0) {
            asm_dosmaperr_00456b04(error);
            return -1;
        }
    }

    CrtFileEntry_0045fa1a* const entry =
        &data_00499200[descriptor >> 5][descriptor & 31];
    entry->flags &= static_cast<unsigned char>(~2u);
    const unsigned long long result_bits =
        (static_cast<unsigned long long>(
             static_cast<unsigned int>(distance_high)) << 32) |
        new_low;
    return static_cast<long long>(result_bits);
}
