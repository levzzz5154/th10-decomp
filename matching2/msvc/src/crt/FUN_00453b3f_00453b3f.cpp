extern "C" void* g_crt_lock_table[];
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(int index) {
    imp_LeaveCriticalSection(g_crt_lock_table[index * 2]);
}
