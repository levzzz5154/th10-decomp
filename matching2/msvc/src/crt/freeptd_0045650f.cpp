extern "C" unsigned int g_crt_tls_index;
extern "C" void* (__stdcall *g_crt_ptd_get)(unsigned int);
extern "C" int (__stdcall *g_crt_ptd_set)(unsigned int, void*);
extern "C" void __stdcall asm_freefls_4_004563c8(void*);

extern "C" void __cdecl asm_freeptd_0045650f(void* data) {
    if (g_crt_tls_index != 0xffffffff) {
        if (!data) data = g_crt_ptd_get(g_crt_tls_index);
        asm_freefls_4_004563c8(data);
        g_crt_ptd_set(g_crt_tls_index, 0);
    }
}
