extern "C" int (__stdcall *imp_IsBadWritePtr)(void*, unsigned int);
extern "C" int __cdecl asm_ValidateWrite_00463ae6(void* ptr, unsigned int size) {
    int valid = 1;
    if (imp_IsBadWritePtr(ptr, size)) valid = 0;
    return valid;
}
