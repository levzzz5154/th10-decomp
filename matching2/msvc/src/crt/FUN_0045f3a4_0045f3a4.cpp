extern "C" unsigned int g_crt_ctype_cp932;

// 0x0045F3A4..0x0045F3B3: Replace a global value and return its old value.
extern "C" unsigned int __cdecl asm_FUN_0045f3a4_0045f3a4(unsigned int value) {
    unsigned int previous = g_crt_ctype_cp932;
    g_crt_ctype_cp932 = value;
    return previous;
}
