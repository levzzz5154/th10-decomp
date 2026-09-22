struct FileEntry { int handle; unsigned char flags; unsigned char padding[31]; };
extern "C" unsigned int data_004991e4;
extern "C" FileEntry* data_00499200[];
extern "C" int* __cdecl asm_FUN_00456af2_00456af2();
extern "C" unsigned int* __cdecl asm_FUN_00456afb_00456afb();

extern "C" int __cdecl asm_get_osfhandle_0045f6d4(int file) {
    if (static_cast<unsigned int>(file) < data_004991e4) {
        FileEntry* entry = &data_00499200[file >> 5][file & 0x1f];
        if (entry->flags & 1) return entry->handle;
    }
    *asm_FUN_00456af2_00456af2() = 9;
    *asm_FUN_00456afb_00456afb() = 0;
    return -1;
}
