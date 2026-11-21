extern "C" void* g_crt_lock_table[];
extern "C" int __cdecl crt_mtinitlocknum(int);
extern "C" void __cdecl crt_amsg_exit(int);
extern "C" void (__stdcall *imp_EnterCriticalSection)(void*);

extern "C" void __cdecl crt_lock(int number) {
    void** slot = &g_crt_lock_table[number * 2];
    if (!*slot && !crt_mtinitlocknum(number)) {
        crt_amsg_exit(0x11);
    }
    imp_EnterCriticalSection(*slot);
}
