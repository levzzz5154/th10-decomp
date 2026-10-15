extern "C" void* __cdecl asm_malloc_00452706(unsigned int);
extern "C" void** g_crt_onexit_table;
extern "C" void** g_crt_onexit_end;

extern "C" int __cdecl asm_onexitinit_00452daa() {
    g_crt_onexit_table = static_cast<void**>(asm_malloc_00452706(0x80));
    if (!g_crt_onexit_table) return 0x18;
    *g_crt_onexit_table = 0;
    g_crt_onexit_end = g_crt_onexit_table;
    return 0;
}
