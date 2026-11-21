extern "C" unsigned char _iob;
extern "C" unsigned char _iob_end;
extern "C" void __cdecl crt_unlock(unsigned int lock);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void* section);

extern "C" void __cdecl crt_unlock_file(void* lock) {
    unsigned char* address = static_cast<unsigned char*>(lock);
    if (address >= &_iob && address <= &_iob_end) {
        crt_unlock(((address - &_iob) >> 5) + 0x10);
    } else {
        imp_LeaveCriticalSection(address + 0x20);
    }
}
