extern "C" unsigned int g_crt_handle_count;
extern "C" char* g_crt_file_table[];

// 0x00459F7D..0x00459FA6: Test the CRT character-device flag.
extern "C" int __cdecl asm_isatty_00459f7d(int handle) {
    if (static_cast<unsigned int>(handle) >= g_crt_handle_count)
        return 0;
    char* block = g_crt_file_table[handle >> 5];
    int offset = (handle & 31) * 36;
    return static_cast<signed char>(block[offset + 4]) & 0x40;
}
