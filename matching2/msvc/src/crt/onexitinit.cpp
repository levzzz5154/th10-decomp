extern "C" void* __cdecl crt_malloc(unsigned int);
extern "C" void** g_crt_onexit_table;
extern "C" void** g_crt_onexit_end;

extern "C" int __cdecl crt_onexitinit() {
    g_crt_onexit_table = static_cast<void**>(crt_malloc(0x80));
    if (!g_crt_onexit_table) return 0x18;
    *g_crt_onexit_table = 0;
    g_crt_onexit_end = g_crt_onexit_table;
    return 0;
}
