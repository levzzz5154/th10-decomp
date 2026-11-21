extern "C" unsigned int g_crt_tls_index;
extern "C" void* (__stdcall *g_crt_ptd_get)(unsigned int);
extern "C" int (__stdcall *g_crt_ptd_set)(unsigned int, void*);
extern "C" void __stdcall crt_freefls_4(void*);

extern "C" void __cdecl crt_freeptd(void* data) {
    if (g_crt_tls_index != 0xffffffff) {
        if (!data) data = g_crt_ptd_get(g_crt_tls_index);
        crt_freefls_4(data);
        g_crt_ptd_set(g_crt_tls_index, 0);
    }
}
