extern "C" void* (__stdcall *imp_HeapCreate)(unsigned int, unsigned int, unsigned int);
extern "C" int (__stdcall *imp_HeapDestroy)(void*);
extern "C" void* g_crt_heap_handle;
extern "C" int g_crt_heap_type;
extern "C" int __cdecl asm_heap_select_004539b1();
extern "C" int __cdecl asm_sbh_heap_init_00453c52(unsigned int);

extern "C" int __cdecl asm_heap_init_004539cb(int flag) {
    g_crt_heap_handle = imp_HeapCreate(flag == 0, 0x1000, 0);
    if (!g_crt_heap_handle) return 0;
    g_crt_heap_type = asm_heap_select_004539b1();
    if (g_crt_heap_type == 3 && !asm_sbh_heap_init_00453c52(0x3f8)) {
        imp_HeapDestroy(g_crt_heap_handle);
        return 0;
    }
    return 1;
}
