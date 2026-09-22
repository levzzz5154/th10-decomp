struct File { unsigned int padding[3]; unsigned int flags; int handle; unsigned int padding2[2]; void* buffer; };
extern "C" int __cdecl asm_flush_0045fbf6(File*);
extern "C" void __cdecl asm_freebuf_00462225(File*);
extern "C" int __cdecl asm_close_0046218a(int);
extern "C" void __cdecl asm_free_00452422(void*);

extern "C" int __cdecl asm_fclose_lk_0046140c(File* file) {
    int result = -1;
    if (file->flags & 0x83) {
        result = asm_flush_0045fbf6(file);
        asm_freebuf_00462225(file);
        if (asm_close_0046218a(file->handle) < 0) result = -1;
        else if (file->buffer) {
            asm_free_00452422(file->buffer);
            file->buffer = 0;
        }
    }
    file->flags = 0;
    return result;
}
