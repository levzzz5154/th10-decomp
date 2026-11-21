extern "C" void* __cdecl crt_onexit(void*);

extern "C" int __cdecl crt_atexit(void* callback) {
    return (crt_onexit(callback) != 0) - 1;
}
