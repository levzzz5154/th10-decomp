extern "C" unsigned int __cdecl crt_strgtold12(
    unsigned char*, int*, const unsigned char*, int, int, int, int);
extern "C" int __cdecl crt_ld12told(const void*, void*);

extern "C" unsigned int __cdecl crt_helper_45db86(void* output, int* parsed, const unsigned char* text, int option) {
    unsigned char converted[12];
    unsigned int result = crt_strgtold12(converted, parsed, text, option, 0, 0, 0);
    if (crt_ld12told(converted, output) == 1) result |= 2;
    return result;
}
