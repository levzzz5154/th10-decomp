extern "C" int (__stdcall *imp_CreateDirectoryA)(const char*, void*);
extern "C" unsigned long (__stdcall *imp_GetLastError)();
extern "C" void __cdecl asm_dosmaperr_00456b04(unsigned long);

extern "C" int __cdecl asm_FUN_00452abc_00452abc(const char* path) {
    unsigned long error;
    if (!imp_CreateDirectoryA(path, 0)) error = imp_GetLastError();
    else error = 0;
    if (error) {
        asm_dosmaperr_00456b04(error);
        return -1;
    }
    return 0;
}
