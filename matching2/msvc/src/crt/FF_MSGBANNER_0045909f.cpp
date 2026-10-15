extern "C" int g_crt_app_errno_flag;
extern "C" int g_crt_banner_flag;
extern "C" void (__cdecl *g_crt_initterm)();
extern "C" void __cdecl asm_FUN_00458efd_00458efd(int);

extern "C" void __cdecl asm_FF_MSGBANNER_0045909f() {
    if (g_crt_app_errno_flag == 1 || (g_crt_app_errno_flag == 0 && g_crt_banner_flag == 1)) {
        asm_FUN_00458efd_00458efd(0xfc);
        if (g_crt_initterm) g_crt_initterm();
        asm_FUN_00458efd_00458efd(0xff);
    }
}
