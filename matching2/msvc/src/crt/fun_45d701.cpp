extern "C" unsigned int __cdecl crt_strgtold12(
    unsigned char*, int*, const unsigned char*, int, int, int, int);
extern "C" int __cdecl crt_ld12tod_45d5e4(const void*, void*);

extern "C" void __cdecl crt_helper_45d701(void* output, const unsigned char* text) {
    unsigned char converted[12];
    int status;
    crt_strgtold12(converted, &status, text, 0, 0, 0, 0);
    crt_ld12tod_45d5e4(converted, output);
}
