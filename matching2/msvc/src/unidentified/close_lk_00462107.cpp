struct CloseLkFileEntry {
    int os_handle;
    unsigned char flags;
    unsigned char padding[31];
};

extern "C" unsigned int data_004991e4;
extern "C" CloseLkFileEntry* data_00499200[];

extern "C" int __cdecl asm_get_osfhandle_0045f6d4(int file);
extern "C" int __cdecl asm_free_osfhnd_0045f655(int file);
extern "C" void __cdecl asm_dosmaperr_00456b04(unsigned int dos_error);

extern "C" __declspec(dllimport) int __stdcall CloseHandle(void* handle);
extern "C" __declspec(dllimport) unsigned int __stdcall GetLastError(void);

// 0x00462107..0x00462189: __close_lk
// EAX return; one cdecl file-descriptor argument on the stack.
extern "C" int __cdecl asm_close_lk_00462107(unsigned int file) {
    unsigned int os_error = 0;
    const int initial_handle = asm_get_osfhandle_0045f6d4(static_cast<int>(file));

    if (initial_handle != -1) {
        bool shared_standard_handle = false;
        if (file == 1 || file == 2) {
            const int stderr_handle = asm_get_osfhandle_0045f6d4(2);
            const int stdout_handle = asm_get_osfhandle_0045f6d4(1);
            shared_standard_handle = stdout_handle == stderr_handle;
        }

        if (!shared_standard_handle) {
            const int os_handle = asm_get_osfhandle_0045f6d4(static_cast<int>(file));
            void* handle = reinterpret_cast<void*>(
                static_cast<unsigned int>(os_handle));
            if (CloseHandle(handle) == 0) {
                os_error = GetLastError();
            }
        }
    }

    asm_free_osfhnd_0045f655(static_cast<int>(file));

    // The retail body clears the per-descriptor flag byte after freeing its
    // OS handle. The table is grouped in blocks of 32 records, each 0x24 bytes.
    const int block_index = static_cast<int>(file) >> 5;
    const unsigned int slot_index = file & 0x1f;
    data_00499200[block_index][slot_index].flags = 0;

    if (os_error != 0) {
        asm_dosmaperr_00456b04(os_error);
        return -1;
    }
    return 0;
}
