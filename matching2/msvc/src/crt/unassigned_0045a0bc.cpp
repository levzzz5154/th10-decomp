extern "C" unsigned char g_crt_lock_range_start;
extern "C" unsigned char g_crt_lock_range_end;
extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(unsigned int lock);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void* section);

extern "C" void __cdecl asm_unassigned_0045a0bc(void* lock) {
    unsigned char* address = static_cast<unsigned char*>(lock);
    if (address >= &g_crt_lock_range_start && address <= &g_crt_lock_range_end) {
        asm_FUN_00453b3f_00453b3f(((address - &g_crt_lock_range_start) >> 5) + 0x10);
    } else {
        imp_LeaveCriticalSection(address + 0x20);
    }
}
