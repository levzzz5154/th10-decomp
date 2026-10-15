extern "C" int g_crt_mbcs_ready;
extern "C" unsigned char* g_crt_cmdline;
extern "C" unsigned char g_crt_empty_string;
extern "C" void __cdecl asm_initmbctable_0045d2ac();
extern "C" int __cdecl asm_ismbblead_0045f590(unsigned int);

extern "C" unsigned char* __cdecl asm_wincmdln_004590d8() {
    int quoted = 0;
    if (g_crt_mbcs_ready == 0) asm_initmbctable_0045d2ac();
    unsigned char* text = g_crt_cmdline;
    if (!text) text = &g_crt_empty_string;
    for (;;) {
        unsigned char ch = *text;
        if (ch <= ' ') {
            if (ch == 0) return text;
            if (!quoted) {
                while (*text && *text <= ' ') ++text;
                return text;
            }
        }
        if (ch == '"') quoted = !quoted;
        if (asm_ismbblead_0045f590(ch)) ++text;
        ++text;
    }
}
