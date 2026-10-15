struct FileEntry { unsigned char padding[0x0c]; unsigned char critical[0x18]; };
extern "C" FileEntry* data_00499200[];
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

extern "C" void __cdecl asm_FUN_0045f7b5_0045f7b5(int file) {
    imp_LeaveCriticalSection(data_00499200[file >> 5][file & 0x1f].critical);
}
