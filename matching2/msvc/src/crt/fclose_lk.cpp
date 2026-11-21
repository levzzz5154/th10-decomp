struct File { unsigned int padding[3]; unsigned int flags; int handle; unsigned int padding2[2]; void* buffer; };
extern "C" int __cdecl crt_flush(File*);
extern "C" void __cdecl crt_freebuf(File*);
extern "C" int __cdecl crt_Close_0046218A(int);
extern "C" void __cdecl crt_free(void*);

extern "C" int __cdecl crt_fclose_lk(File* file) {
    int result = -1;
    if (file->flags & 0x83) {
        result = crt_flush(file);
        crt_freebuf(file);
        if (crt_Close_0046218A(file->handle) < 0) result = -1;
        else if (file->buffer) {
            crt_free(file->buffer);
            file->buffer = 0;
        }
    }
    file->flags = 0;
    return result;
}
