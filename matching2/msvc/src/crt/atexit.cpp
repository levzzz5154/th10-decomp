extern "C" void* __cdecl asm_onexit_00452dd2(void*);

extern "C" int __cdecl crt_atexit(void* callback) {
    return (asm_onexit_00452dd2(callback) != 0) - 1;
}
