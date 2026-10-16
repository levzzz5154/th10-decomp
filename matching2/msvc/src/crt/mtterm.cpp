extern "C" int g_crt_tls_index;
extern "C" void (__stdcall *g_crt_ptd_init)(int);
extern "C" void __cdecl asm_mtdeletelocks_00453aea();

extern "C" void __cdecl asm_mtterm_00456327() {
    if (g_crt_tls_index != -1) {
        g_crt_ptd_init(g_crt_tls_index);
        g_crt_tls_index = -1;
    }
    asm_mtdeletelocks_00453aea();
}
