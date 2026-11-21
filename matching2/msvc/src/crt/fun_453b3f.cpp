extern "C" void* g_crt_lock_table[];
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

extern "C" void __cdecl crt_unlock(int index) {
    imp_LeaveCriticalSection(g_crt_lock_table[index * 2]);
}
