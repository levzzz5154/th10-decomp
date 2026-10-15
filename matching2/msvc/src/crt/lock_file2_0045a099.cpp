extern "C" void __cdecl asm_lock_00453c0c(int);
extern "C" void (__stdcall *data_004660b0)(void*);

extern "C" void __cdecl asm_lock_file2_0045a099(int number, void* file) {
    if (number < 20) {
        asm_lock_00453c0c(number + 16);
        return;
    }
    data_004660b0(static_cast<unsigned char*>(file) + 0x20);
}
