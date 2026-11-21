extern "C" int g_crt_mbcs_ready;
extern "C" unsigned char* g_crt_cmdline;
extern "C" unsigned char g_crt_empty_string;
extern "C" void __cdecl crt_initmbctable();
extern "C" int __cdecl crt_ismbblead(unsigned int);

extern "C" unsigned char* __cdecl crt_wincmdln() {
    int quoted = 0;
    if (g_crt_mbcs_ready == 0) crt_initmbctable();
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
        if (crt_ismbblead(ch)) ++text;
        ++text;
    }
}
