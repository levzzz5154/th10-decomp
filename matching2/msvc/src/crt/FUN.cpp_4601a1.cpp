extern "C" int (__stdcall *imp_GetLocaleInfoA)(unsigned int, unsigned int, char*, int);
extern "C" long __cdecl asm_atol_004527ee(const char*);

extern "C" long __cdecl asm_FUN_004601a1_004601a1(unsigned int locale) {
    char buffer[7];
    buffer[6] = 0;
    if (imp_GetLocaleInfoA(locale, 0x1004, buffer, 6) == 0) return -1;
    return asm_atol_004527ee(buffer);
}
