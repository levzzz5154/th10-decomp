extern "C" int (__stdcall *data_004661e0)(const char*, void*);
extern "C" unsigned long (__stdcall *data_0046610c)();
extern "C" void __cdecl asm_dosmaperr_00456b04(unsigned long);

extern "C" int __cdecl asm_FUN_00452abc_00452abc(const char* path) {
    unsigned long error;
    if (!data_004661e0(path, 0)) error = data_0046610c();
    else error = 0;
    if (error) {
        asm_dosmaperr_00456b04(error);
        return -1;
    }
    return 0;
}
