struct ThreadData {
    unsigned int thread_id;
    unsigned int thread_handle;
    unsigned char padding0[0x0c];
    unsigned int holdrand;
    unsigned char padding1[0x3c];
    void* initaddr;
};
extern "C" int __cdecl asm_mtinitlocks_00453aa1();
extern "C" void __cdecl asm_mtterm_00456327();
extern "C" void __stdcall asm_freefls_4_004563c8(void*);
extern "C" unsigned int __stdcall asm_FUN_0045631e_0045631e(void*);
extern "C" ThreadData* __cdecl asm_FUN_0045794d_0045794d(unsigned int, unsigned int);
extern "C" void* (__stdcall *imp_GetModuleHandleA)(const char*);
extern "C" void* (__stdcall *imp_GetProcAddress)(void*, const char*);
extern "C" unsigned int (__stdcall *imp_GetCurrentThreadId)();
extern "C" void* imp_TlsGetValue;
extern "C" void* imp_TlsSetValue;
extern "C" void* imp_TlsFree;
extern "C" void* g_crt_ptd_alloc;
extern "C" void* g_crt_ptd_get;
extern "C" void* g_crt_ptd_set;
extern "C" void* g_crt_ptd_init;
extern "C" unsigned int g_crt_tls_index;
extern "C" char g_crt_ptd_init_marker;

extern "C" int __cdecl asm_mtinit_0045654a() {
    if (!asm_mtinitlocks_00453aa1()) {
        asm_mtterm_00456327();
        return 0;
    }
    void* module = imp_GetModuleHandleA(reinterpret_cast<const char*>(0x46aa5c));
    if (module) {
        void* (__stdcall *get_proc)(void*, const char*) = imp_GetProcAddress;
        g_crt_ptd_alloc = get_proc(module, reinterpret_cast<const char*>(0x46aa50));
        g_crt_ptd_get = get_proc(module, reinterpret_cast<const char*>(0x46aa44));
        g_crt_ptd_set = get_proc(module, reinterpret_cast<const char*>(0x46aa38));
        g_crt_ptd_init = get_proc(module, reinterpret_cast<const char*>(0x46aa30));
        if (!g_crt_ptd_get) {
            g_crt_ptd_get = imp_TlsGetValue;
            g_crt_ptd_set = imp_TlsSetValue;
            g_crt_ptd_alloc = reinterpret_cast<void*>(&asm_FUN_0045631e_0045631e);
            g_crt_ptd_init = imp_TlsFree;
        }
    }
    g_crt_tls_index = reinterpret_cast<unsigned int (__stdcall*)(void*)>(g_crt_ptd_alloc)(reinterpret_cast<void*>(&asm_freefls_4_004563c8));
    if (g_crt_tls_index != 0xffffffff) {
        ThreadData* data = asm_FUN_0045794d_0045794d(1, 0x8c);
        if (data && reinterpret_cast<int (__stdcall*)(unsigned int, ThreadData*)>(g_crt_ptd_set)(g_crt_tls_index, data)) {
            data->initaddr = &g_crt_ptd_init_marker;
            data->holdrand = 1;
            unsigned int id = imp_GetCurrentThreadId();
            data->thread_handle = 0xffffffff;
            data->thread_id = id;
            return 1;
        }
    }
    asm_mtterm_00456327();
    return 0;
}
