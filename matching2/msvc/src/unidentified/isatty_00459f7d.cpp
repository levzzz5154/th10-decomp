extern "C" unsigned int data_004991e4;
extern "C" char* data_00499200[];

// 0x00459F7D..0x00459FA6: Test the CRT character-device flag.
extern "C" int __cdecl asm_isatty_00459f7d(int handle) {
    if (static_cast<unsigned int>(handle) >= data_004991e4)
        return 0;
    char* block = data_00499200[handle >> 5];
    int offset = (handle & 31) * 36;
    return static_cast<signed char>(block[offset + 4]) & 0x40;
}
