extern "C" int (__stdcall *data_00466174)(void*, unsigned int);
extern "C" int __cdecl asm_ValidateWrite_00463ae6(void* ptr, unsigned int size) {
    int valid = 1;
    if (data_00466174(ptr, size)) valid = 0;
    return valid;
}
