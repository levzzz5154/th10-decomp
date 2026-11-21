extern "C" int g_crt_tls_index;
extern "C" void (__stdcall *g_crt_ptd_init)(int);
extern "C" void __cdecl crt_mtdeletelocks();

extern "C" void __cdecl crt_mtterm() {
    if (g_crt_tls_index != -1) {
        g_crt_ptd_init(g_crt_tls_index);
        g_crt_tls_index = -1;
    }
    crt_mtdeletelocks();
}
