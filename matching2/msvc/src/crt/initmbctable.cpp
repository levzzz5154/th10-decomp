extern "C" int g_crt_mbcs_ready;
extern "C" int __cdecl crt_setmbcp(int);

extern "C" int __cdecl crt_initmbctable() {
    if (!g_crt_mbcs_ready) {
        crt_setmbcp(-3);
        g_crt_mbcs_ready = 1;
    }
    return 0;
}
