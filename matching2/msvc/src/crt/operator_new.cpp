extern "C" void* __cdecl asm_nh_malloc_004526da(unsigned int, int);

extern "C" void* __cdecl crt_operator_new(unsigned int size) {
    return asm_nh_malloc_004526da(size, 1);
}
