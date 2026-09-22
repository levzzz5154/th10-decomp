extern "C" int (__stdcall *data_00466184)(const void*);
extern "C" int __cdecl asm_ValidateExecute_00463b02(const void* ptr) {
    int valid = 1;
    if (data_00466184(ptr)) valid = 0;
    return valid;
}
