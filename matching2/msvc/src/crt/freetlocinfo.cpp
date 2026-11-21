// Semantic model for 0x004557FC..0x004558CB (___freetlocinfo).
extern "C" void __cdecl crt_free(void* memory);
extern "C" void __cdecl asm_free_lc_time_0045b39a(void* time_info);
extern "C" void __cdecl asm_free_lconv_mon_0045b81b(void* locale_info);
extern "C" void __cdecl asm_free_lconv_num_0045b5bc(void* locale_info);

extern "C" unsigned char g_crt_loc_unk_a;
extern "C" unsigned char g_crt_loc_unk_b;
extern "C" unsigned char g_locale_multibyte;
extern "C" unsigned char g_locale_monetary;
extern "C" unsigned char g_locale_numeric;

extern "C" void __cdecl asm_freetlocinfo_004557fc(void* locale_info) {
    unsigned char* info = (unsigned char*)locale_info;
    void* locale_data = *(void**)(info + 0x3c);

    if (locale_data != *(void**)&g_crt_loc_unk_b && locale_data != 0 &&
        **(int**)(info + 0x2c) == 0) {
        void* monetary_locale = *(void**)(info + 0x34);
        if (monetary_locale != 0 && *(int*)monetary_locale == 0 &&
            monetary_locale != *(void**)&g_locale_monetary) {
            crt_free(monetary_locale);
            asm_free_lconv_mon_0045b81b(*(void**)(info + 0x3c));
        }

        void* numeric_locale = *(void**)(info + 0x30);
        if (numeric_locale != 0 && *(int*)numeric_locale == 0 &&
            numeric_locale != *(void**)&g_locale_numeric) {
            crt_free(numeric_locale);
            asm_free_lconv_num_0045b5bc(*(void**)(info + 0x3c));
        }

        crt_free(*(void**)(info + 0x2c));
        crt_free(*(void**)(info + 0x3c));
    }

    void* multibyte_locale = *(void**)(info + 0x40);
    if (multibyte_locale != *(void**)&g_locale_multibyte &&
        multibyte_locale != 0 && *(int*)multibyte_locale == 0) {
        crt_free(multibyte_locale);
        char* allocation_base = *(char**)(info + 0x44);
        crt_free(allocation_base - 0xfe);
    }

    void* time_locale = *(void**)(info + 0x50);
    if (time_locale != *(void**)&g_crt_loc_unk_a && time_locale != 0 &&
        *(unsigned int*)((char*)time_locale + 0xb4) == 0) {
        asm_free_lc_time_0045b39a(time_locale);
        crt_free(*(void**)(info + 0x50));
    }

    crt_free(locale_info);
}
