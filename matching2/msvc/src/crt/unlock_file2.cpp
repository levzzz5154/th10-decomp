extern "C" void __cdecl crt_unlock(int);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

extern "C" void __cdecl crt_unlock_file2(int number, void* file) {
    if (number < 20) {
        crt_unlock(number + 16);
        return;
    }
    imp_LeaveCriticalSection(static_cast<unsigned char*>(file) + 0x20);
}
