extern "C" unsigned int __cdecl asm_FUN_0045d746_0045d746(
    unsigned char*, int*, const unsigned char*, int, int, int, int);
extern "C" int __cdecl asm_FID_conflict___ld12tod_0045d5ce(const void*, void*);

extern "C" void __cdecl asm_FUN_0045d676_0045d676(void* output, const unsigned char* text) {
    unsigned char converted[12];
    int status;
    asm_FUN_0045d746_0045d746(converted, &status, text, 0, 0, 0, 0);
    asm_FID_conflict___ld12tod_0045d5ce(converted, output);
}
