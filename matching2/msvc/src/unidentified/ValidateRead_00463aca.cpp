extern "C" int (__stdcall *data_004661d8)(const void*, unsigned int);
extern "C" int __cdecl asm_ValidateRead_00463aca(const void* ptr, unsigned int size) {
    int valid = 1;
    if (data_004661d8(ptr, size)) valid = 0;
    return valid;
}
