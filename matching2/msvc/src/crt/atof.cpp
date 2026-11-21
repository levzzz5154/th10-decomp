extern "C" int __cdecl crt_isspace(int);
extern "C" unsigned int __cdecl crt_strlen(const char*);
extern "C" unsigned int* __cdecl crt_helper_456674(unsigned int*, const char*, unsigned int, int, int);

extern "C" double __cdecl crt_atof(const char* input) {
    while (crt_isspace(static_cast<unsigned char>(*input))) ++input;
    unsigned int parsed[6];
    unsigned int* result = crt_helper_456674(parsed, input, crt_strlen(input), 0, 0);
    return *reinterpret_cast<double*>(result + 4);
}
