struct MbcInfo { unsigned char padding0[4]; unsigned int codepage; unsigned int padding1; unsigned int lcid; };
struct ThreadData { unsigned char padding[0x60]; MbcInfo* mbc; };
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" MbcInfo* __cdecl crt_updatetmbcinfo();
extern "C" MbcInfo* g_mbc_info;
extern "C" int __cdecl crt_helper_461af9(unsigned int, int, const unsigned char*, unsigned int, const unsigned char*, unsigned int, unsigned int);

extern "C" int __cdecl crt_mbsnbicoll(const unsigned char* first, const unsigned char* second, unsigned int count) {
    MbcInfo* info = crt_getptd()->mbc;
    if (info != g_mbc_info) info = crt_updatetmbcinfo();
    if (count == 0) return 0;
    int result = crt_helper_461af9(info->lcid, 1, first, count, second, count, info->codepage);
    if (result == 0) return 0x7fffffff;
    return result - 2;
}
