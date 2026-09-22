extern "C" unsigned int __cdecl asm_FUN_0045d746_0045d746(void*, int*, const unsigned char*, int, int, int, int);
extern "C" int __cdecl asm_ld12told_0045d5fa(const void*, void*);

extern "C" unsigned int __cdecl asm_FUN_0045db86_0045db86(void* output, int* parsed, const unsigned char* text, int option) {
    unsigned char converted[12];
    unsigned int result = asm_FUN_0045d746_0045d746(converted, parsed, text, option, 0, 0, 0);
    if (asm_ld12told_0045d5fa(converted, output) == 1) result |= 2;
    return result;
}
