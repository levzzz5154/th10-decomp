struct FileEntry { unsigned char padding[0x0c]; unsigned char critical[0x18]; };
extern "C" FileEntry* g_crt_file_table[];
extern "C" void (__stdcall *imp_LeaveCriticalSection)(void*);

extern "C" void __cdecl asm_FUN_0045f7b5_0045f7b5(int file) {
    imp_LeaveCriticalSection(g_crt_file_table[file >> 5][file & 0x1f].critical);
}
