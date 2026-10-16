extern "C" int g_crt_mbcs_ready;
extern "C" int __cdecl asm_setmbcp_0045d15c(int);

extern "C" int __cdecl asm_initmbctable_0045d2ac() {
    if (!g_crt_mbcs_ready) {
        asm_setmbcp_0045d15c(-3);
        g_crt_mbcs_ready = 1;
    }
    return 0;
}
