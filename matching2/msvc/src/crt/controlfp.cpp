extern "C" unsigned int __cdecl crt_control87(unsigned int, unsigned int);

extern "C" unsigned int __cdecl crt_controlfp(unsigned int new_value, unsigned int mask) {
    return crt_control87(new_value, mask & 0xfff7ffff);
}
