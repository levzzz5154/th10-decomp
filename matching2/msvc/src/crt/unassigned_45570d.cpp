typedef int (__cdecl *NewHandler)(unsigned int);
extern "C" NewHandler g_crt_ptd_raw;
extern "C" void __cdecl asm_lock_00453c0c(int lock);
extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(int lock);

extern "C" NewHandler __cdecl asm_unassigned_0045570d(NewHandler handler) {
    asm_lock_00453c0c(4);
    NewHandler previous = g_crt_ptd_raw;
    g_crt_ptd_raw = handler;
    asm_FUN_00453b3f_00453b3f(4);
    return previous;
}
