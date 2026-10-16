struct ThreadData {
    unsigned int thread_id;
    unsigned int thread_handle;
    unsigned char padding0[0x0c];
    unsigned int holdrand;
    unsigned char padding1[0x3c];
    void* initaddr;
};
extern "C" unsigned int (__stdcall *imp_GetLastError)();
extern "C" void (__stdcall *imp_SetLastError)(unsigned int);
extern "C" unsigned int (__stdcall *imp_GetCurrentThreadId)();
extern "C" ThreadData* (__stdcall *g_crt_ptd_get)(unsigned int);
extern "C" int (__stdcall *g_crt_ptd_set)(unsigned int, ThreadData*);
extern "C" unsigned int g_crt_tls_index;
extern "C" char g_crt_ptd_init_marker;
extern "C" ThreadData* __cdecl asm_FUN_0045794d_0045794d(unsigned int, unsigned int);
extern "C" void __cdecl asm_amsg_exit_0045373d(int);

extern "C" ThreadData* __cdecl asm_getptd_00456357() {
    unsigned int saved_error = imp_GetLastError();
    ThreadData* data = g_crt_ptd_get(g_crt_tls_index);
    if (!data) {
        data = asm_FUN_0045794d_0045794d(1, 0x8c);
        if (data && g_crt_ptd_set(g_crt_tls_index, data)) {
            data->initaddr = &g_crt_ptd_init_marker;
            data->holdrand = 1;
            unsigned int id = imp_GetCurrentThreadId();
            data->thread_handle = 0xffffffff;
            data->thread_id = id;
        } else {
            asm_amsg_exit_0045373d(0x10);
        }
    }
    imp_SetLastError(saved_error);
    return data;
}
