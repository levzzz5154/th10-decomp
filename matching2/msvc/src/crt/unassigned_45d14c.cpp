extern "C" unsigned int g_mbc_codepage;
extern "C" unsigned int g_mbc_cp932;

// 0x0045D14C..0x0045D15B: Return the active CRT flag mask.
extern "C" unsigned int __cdecl asm_unassigned_0045d14c() {
    return g_mbc_codepage ? g_mbc_cp932 : 0;
}
