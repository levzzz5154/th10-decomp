extern "C" void* data_00473080[];
extern "C" int __cdecl asm_mtinitlocknum_00453b6c(int);
extern "C" void __cdecl asm_amsg_exit_0045373d(int);
extern "C" void (__stdcall *imp_EnterCriticalSection)(void*);

extern "C" void __cdecl asm_lock_00453c0c(int number) {
    void** slot = &data_00473080[number * 2];
    if (!*slot && !asm_mtinitlocknum_00453b6c(number)) {
        asm_amsg_exit_0045373d(0x11);
    }
    imp_EnterCriticalSection(*slot);
}
