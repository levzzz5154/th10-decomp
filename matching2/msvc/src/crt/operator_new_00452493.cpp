extern "C" void* __cdecl asm_nh_malloc_004526da(unsigned int, int);

extern "C" void* __cdecl asm_operator_new_00452493(unsigned int size) {
    return asm_nh_malloc_004526da(size, 1);
}
