extern "C" void* (__stdcall *imp_HeapCreate)(unsigned int, unsigned int, unsigned int);
extern "C" int (__stdcall *imp_HeapDestroy)(void*);
extern "C" void* g_crt_heap_handle;
extern "C" int g_crt_heap_type;
extern "C" int __cdecl crt_heap_select();
extern "C" int __cdecl crt_sbh_heap_init(unsigned int);

extern "C" int __cdecl crt_heap_init(int flag) {
    g_crt_heap_handle = imp_HeapCreate(flag == 0, 0x1000, 0);
    if (!g_crt_heap_handle) return 0;
    g_crt_heap_type = crt_heap_select();
    if (g_crt_heap_type == 3 && !crt_sbh_heap_init(0x3f8)) {
        imp_HeapDestroy(g_crt_heap_handle);
        return 0;
    }
    return 1;
}
