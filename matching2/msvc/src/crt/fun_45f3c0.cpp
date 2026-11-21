extern "C" unsigned int g_crt_ctype_cp932;

// 0x0045F3C0..0x0045F3CF: Replace a global value and return its old value.
extern "C" unsigned int __cdecl crt_helper_45f3c0(unsigned int value) {
    unsigned int previous = g_crt_ctype_cp932;
    g_crt_ctype_cp932 = value;
    return previous;
}
