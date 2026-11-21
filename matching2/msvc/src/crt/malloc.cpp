extern "C" int _newmode;
extern "C" void* __cdecl crt_nh_malloc(unsigned int, int);

extern "C" void* __cdecl crt_malloc(unsigned int size) {
    return crt_nh_malloc(size, _newmode);
}
