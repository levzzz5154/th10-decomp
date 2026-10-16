struct File { unsigned int padding[3]; unsigned char flags[4]; int handle; };
extern "C" int __cdecl asm_flush_0045fbf6(File*);
extern "C" int __cdecl asm_commit_004614a9(int);

extern "C" int __cdecl asm_fflush_lk_0045fc53(File* file) {
    if (asm_flush_0045fbf6(file) != 0) return -1;
    if ((file->flags[1] & 0x40) != 0) return asm_commit_004614a9(file->handle) ? -1 : 0;
    return 0;
}
