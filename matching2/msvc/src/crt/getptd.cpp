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
extern "C" char _XcptActTab;
extern "C" ThreadData* __cdecl crt_calloc(unsigned int, unsigned int);
extern "C" void __cdecl crt_amsg_exit(int);

extern "C" ThreadData* __cdecl crt_getptd() {
    unsigned int saved_error = imp_GetLastError();
    ThreadData* data = g_crt_ptd_get(g_crt_tls_index);
    if (!data) {
        data = crt_calloc(1, 0x8c);
        if (data && g_crt_ptd_set(g_crt_tls_index, data)) {
            data->initaddr = &_XcptActTab;
            data->holdrand = 1;
            unsigned int id = imp_GetCurrentThreadId();
            data->thread_handle = 0xffffffff;
            data->thread_id = id;
        } else {
            crt_amsg_exit(0x10);
        }
    }
    imp_SetLastError(saved_error);
    return data;
}
