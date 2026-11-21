extern "C" unsigned int g_crt_cfltcvt_tab_0;
extern "C" unsigned int g_crt_cfltcvt_tab_1;
extern "C" unsigned int g_crt_cfltcvt_tab_2;
extern "C" unsigned int g_crt_cfltcvt_tab_3;
extern "C" unsigned int g_crt_cfltcvt_tab_4;
extern "C" unsigned int g_crt_cfltcvt_tab_5;

// 0x00456A8C..0x00456AC3: Install the CRT floating-point conversion hooks.
extern "C" void __cdecl crt_cfltcvt_init() {
    g_crt_cfltcvt_tab_0 = 0x0045df97;
    g_crt_cfltcvt_tab_1 = 0x0045dc17;
    g_crt_cfltcvt_tab_2 = 0x0045dc7c;
    g_crt_cfltcvt_tab_3 = 0x0045dbdb;
    g_crt_cfltcvt_tab_4 = 0x0045dc62;
    g_crt_cfltcvt_tab_5 = 0x0045df97;
}
