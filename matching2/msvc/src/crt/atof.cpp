extern "C" int __cdecl asm_isspace_004568d7(int);
extern "C" unsigned int __cdecl asm_strlen_00456720(const char*);
extern "C" unsigned int* __cdecl asm_FUN_00456674_00456674(unsigned int*, const char*, unsigned int, int, int);

extern "C" double __cdecl asm_atof_00452a84(const char* input) {
    while (asm_isspace_004568d7(static_cast<unsigned char>(*input))) ++input;
    unsigned int parsed[6];
    unsigned int* result = asm_FUN_00456674_00456674(parsed, input, asm_strlen_00456720(input), 0, 0);
    return *reinterpret_cast<double*>(result + 4);
}
