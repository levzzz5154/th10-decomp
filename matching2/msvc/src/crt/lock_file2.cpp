extern "C" void __cdecl crt_lock(int);
extern "C" void (__stdcall *imp_EnterCriticalSection)(void*);

extern "C" void __cdecl crt_lock_file2(int number, void* file) {
    if (number < 20) {
        crt_lock(number + 16);
        return;
    }
    imp_EnterCriticalSection(static_cast<unsigned char*>(file) + 0x20);
}
