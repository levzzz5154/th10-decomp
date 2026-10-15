extern "C" int (__stdcall *imp_IsBadCodePtr)(const void*);
extern "C" int __cdecl asm_ValidateExecute_00463b02(const void* ptr) {
    int valid = 1;
    if (imp_IsBadCodePtr(ptr)) valid = 0;
    return valid;
}
