extern "C" int g_crt_app_errno_flag;
extern "C" int g_crt_banner_flag;
extern "C" void (__cdecl *g_crt_initterm)();
extern "C" void __cdecl crt_NMSG_WRITE(int);

extern "C" void __cdecl crt_FF_MSGBANNER() {
    if (g_crt_app_errno_flag == 1 || (g_crt_app_errno_flag == 0 && g_crt_banner_flag == 1)) {
        crt_NMSG_WRITE(0xfc);
        if (g_crt_initterm) g_crt_initterm();
        crt_NMSG_WRITE(0xff);
    }
}
