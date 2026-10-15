extern "C" void* __cdecl asm_onexit_00452dd2(void*);

extern "C" int __cdecl asm_atexit_00452e0a(void* callback) {
    return (asm_onexit_00452dd2(callback) != 0) - 1;
}
