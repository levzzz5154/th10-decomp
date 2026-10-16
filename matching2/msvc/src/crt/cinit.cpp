typedef int (__cdecl *InitFn)();
typedef void (__cdecl *VoidInitFn)();
extern "C" void (__cdecl *g_crt_init_callback)(int);
extern "C" InitFn g_crt_cinit_starts[];
extern "C" InitFn g_crt_cinit_end;
extern "C" VoidInitFn g_crt_preterm_starts[];
extern "C" VoidInitFn g_crt_preterm_end;
extern "C" void __cdecl asm_FUN_004597ba_004597ba();
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)());

extern "C" int __cdecl asm_cinit_004575bf(int argument) {
    if (g_crt_init_callback) g_crt_init_callback(argument);
    int result = 0;
    InitFn* p = g_crt_cinit_starts;
    while (p < &g_crt_cinit_end) {
        if (result) return result;
        if (*p) result = (*p)();
        ++p;
    }
    if (!result) {
        asm_atexit_00452e0a(&asm_FUN_004597ba_004597ba);
        VoidInitFn* q = g_crt_preterm_starts;
        while (q < &g_crt_preterm_end) {
            if (*q) (*q)();
            ++q;
        }
        return 0;
    }
    return result;
}
