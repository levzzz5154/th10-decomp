extern "C" int data_00477364;
extern "C" void* __cdecl asm_nh_malloc_004526da(unsigned int, int);

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size) {
    return asm_nh_malloc_004526da(size, data_00477364);
}
