struct MbcInfo { unsigned char padding0[4]; unsigned int codepage; unsigned int padding1; unsigned int lcid; };
struct ThreadData { unsigned char padding[0x60]; MbcInfo* mbc; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" MbcInfo* __cdecl asm_updatetmbcinfo_0045cf49();
extern "C" MbcInfo* data_00497f94;
extern "C" int __cdecl asm_FUN_00461af9_00461af9(unsigned int, int, const unsigned char*, unsigned int, const unsigned char*, unsigned int, unsigned int);

extern "C" int __cdecl asm_mbsnbicoll_004610a6(const unsigned char* first, const unsigned char* second, unsigned int count) {
    MbcInfo* info = asm_getptd_00456357()->mbc;
    if (info != data_00497f94) info = asm_updatetmbcinfo_0045cf49();
    if (count == 0) return 0;
    int result = asm_FUN_00461af9_00461af9(info->lcid, 1, first, count, second, count, info->codepage);
    if (result == 0) return 0x7fffffff;
    return result - 2;
}
