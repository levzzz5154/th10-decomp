extern "C" unsigned int __cdecl crt_controlfp(unsigned int new_value, unsigned int mask);

extern "C" void __cdecl crt_setdefaultprecision() {
    crt_controlfp(0x10000, 0x30000);
}
