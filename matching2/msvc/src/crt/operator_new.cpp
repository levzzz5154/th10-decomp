extern "C" void* __cdecl crt_nh_malloc(unsigned int, int);

extern "C" void* __cdecl crt_operator_new(unsigned int size) {
    return crt_nh_malloc(size, 1);
}
