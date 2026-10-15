struct LocaleInfo { unsigned char padding0[4]; unsigned int codepage; unsigned char padding1[12]; int multibyte; unsigned char padding2[16]; int max_bytes; };
extern "C" int (__stdcall *data_00466154)(unsigned int, unsigned int, const unsigned short*, int, char*, int, const char*, char**);
extern "C" int* __cdecl asm_FUN_00456af2_00456af2();

extern "C" int __cdecl asm_wctomb_mt_0045a10e(LocaleInfo* locale, char* destination, unsigned short wide) {
    char* output = destination;
    if (!destination) return 0;
    if (locale->multibyte == 0) {
        if (wide <= 0xff) {
            *destination = static_cast<char>(wide);
            return 1;
        }
    } else {
        destination = 0;
        int result = data_00466154(locale->codepage, 0, &wide, 1, output, locale->max_bytes, 0, &destination);
        if (result != 0 && destination == 0) return result;
    }
    *asm_FUN_00456af2_00456af2() = 42;
    return -1;
}
