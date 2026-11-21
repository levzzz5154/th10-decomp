struct File { unsigned int padding[3]; unsigned char flags[4]; int handle; };
extern "C" int __cdecl crt_flush(File*);
extern "C" int __cdecl crt_commit(int);

extern "C" int __cdecl crt_fflush_lk(File* file) {
    if (crt_flush(file) != 0) return -1;
    if ((file->flags[1] & 0x40) != 0) return crt_commit(file->handle) ? -1 : 0;
    return 0;
}
