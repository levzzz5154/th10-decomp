extern "C" int __cdecl crt_helper_454ed7(unsigned int*, const unsigned char*, void*);

extern "C" void __cdecl crt_helper_452b40(const unsigned char* format, ...) {
    unsigned int state[8];
    state[2] = 0;
    state[0] = 0;
    state[1] = 0x7fffffff;
    state[3] = 0x42;
    crt_helper_454ed7(state, format, &format + 1);
}
