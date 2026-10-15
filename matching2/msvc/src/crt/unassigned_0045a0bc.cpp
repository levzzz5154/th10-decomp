extern "C" unsigned char data_00473740;
extern "C" unsigned char data_004739a0;
extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(unsigned int lock);
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void* section);

extern "C" void __cdecl asm_unassigned_0045a0bc(void* lock) {
    unsigned char* address = static_cast<unsigned char*>(lock);
    if (address >= &data_00473740 && address <= &data_004739a0) {
        asm_FUN_00453b3f_00453b3f(((address - &data_00473740) >> 5) + 0x10);
    } else {
        imp_LeaveCriticalSection(address + 0x20);
    }
}
