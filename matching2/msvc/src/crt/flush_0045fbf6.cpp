struct File { char* current; int count; char* base; unsigned int flags; int handle; };
extern "C" int __cdecl asm_write_00459e8e(int, const void*, unsigned int);

extern "C" int __cdecl asm_flush_0045fbf6(File* file) {
    int result = 0;
    unsigned int flags = file->flags;
    if ((flags & 3) == 2 && (flags & 0x108) != 0) {
        int length = file->current - file->base;
        if (length > 0) {
            if (asm_write_00459e8e(file->handle, file->base, length) == length) {
                unsigned int current_flags = file->flags;
                if ((current_flags & 0x80) != 0) {
                    current_flags &= ~2u;
                    file->flags = current_flags;
                }
            } else {
                file->flags |= 0x20;
                result = -1;
            }
        }
    }
    file->count = 0;
    file->current = file->base;
    return result;
}
