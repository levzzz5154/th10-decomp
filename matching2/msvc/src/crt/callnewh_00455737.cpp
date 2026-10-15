extern "C" int (__cdecl *g_crt_ptd_raw)(unsigned int);

extern "C" int __cdecl asm_callnewh_00455737(unsigned int size) {
    int (__cdecl *handler)(unsigned int) = g_crt_ptd_raw;
    if (handler && handler(size)) return 1;
    return 0;
}
