typedef int (__cdecl *InitFn)();
typedef void (__cdecl *VoidInitFn)();
extern "C" void (__cdecl *data_004733a8)(int);
extern "C" InitFn data_00473034[];
extern "C" InitFn data_0047304c;
extern "C" VoidInitFn data_00473000[];
extern "C" VoidInitFn data_00473030;
extern "C" void __cdecl asm_FUN_004597ba_004597ba();
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)());

extern "C" int __cdecl asm_cinit_004575bf(int argument) {
    if (data_004733a8) data_004733a8(argument);
    int result = 0;
    InitFn* p = data_00473034;
    while (p < &data_0047304c) {
        if (result) return result;
        if (*p) result = (*p)();
        ++p;
    }
    if (!result) {
        asm_atexit_00452e0a(&asm_FUN_004597ba_004597ba);
        VoidInitFn* q = data_00473000;
        while (q < &data_00473030) {
            if (*q) (*q)();
            ++q;
        }
        return 0;
    }
    return result;
}
