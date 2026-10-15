extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(int);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

extern "C" void __cdecl asm_unlock_file2_0045a0eb(int number, void* file) {
    if (number < 20) {
        asm_FUN_00453b3f_00453b3f(number + 16);
        return;
    }
    imp_LeaveCriticalSection(static_cast<unsigned char*>(file) + 0x20);
}
