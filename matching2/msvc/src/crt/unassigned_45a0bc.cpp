extern "C" unsigned char g_crt_lock_range_start;
extern "C" unsigned char g_crt_lock_range_end;
extern "C" void __cdecl crt_unlock(unsigned int lock);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void* section);

extern "C" void __cdecl crt_unlock_file(void* lock) {
    unsigned char* address = static_cast<unsigned char*>(lock);
    if (address >= &g_crt_lock_range_start && address <= &g_crt_lock_range_end) {
        crt_unlock(((address - &g_crt_lock_range_start) >> 5) + 0x10);
    } else {
        imp_LeaveCriticalSection(address + 0x20);
    }
}
