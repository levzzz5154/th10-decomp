extern "C" int g_crt_malloc_used;
extern "C" void* __cdecl asm_nh_malloc_004526da(unsigned int, int);

extern "C" void* __cdecl crt_malloc(unsigned int size) {
    return asm_nh_malloc_004526da(size, g_crt_malloc_used);
}
