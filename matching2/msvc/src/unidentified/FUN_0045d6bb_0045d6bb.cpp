extern "C" int __cdecl asm_FUN_0045d746_0045d746(void*, int*, const unsigned char*, int, int, int, int);
extern "C" int __cdecl asm_ld12told_0045d5fa(const void*, void*);

extern "C" void __cdecl asm_FUN_0045d6bb_0045d6bb(void* output, const unsigned char* text) {
    unsigned char converted[12];
    int status;
    asm_FUN_0045d746_0045d746(converted, &status, text, 1, 0, 0, 0);
    asm_ld12told_0045d5fa(converted, output);
}
