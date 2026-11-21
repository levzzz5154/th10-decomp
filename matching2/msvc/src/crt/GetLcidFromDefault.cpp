extern "C" unsigned short g_crt_lcid_country;
extern "C" unsigned int g_crt_lcid_default_sub;
extern "C" unsigned int g_crt_lcid_default_lang;
extern "C" unsigned int (__stdcall *imp_GetUserDefaultLCID)();

extern "C" void __cdecl crt_libcmt_getqloc_GetLcidFromDefault() {
    g_crt_lcid_country |= 0x104;
    g_crt_lcid_default_sub = imp_GetUserDefaultLCID();
    g_crt_lcid_default_lang = g_crt_lcid_default_sub;
}
