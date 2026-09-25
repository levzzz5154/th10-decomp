// 0x0045287B..0x00452921: CRT-style signed 64-bit decimal conversion.
// Ghidra's live listing shows a one-pointer cdecl entry returning EDX:EAX.
struct Atoi64LocaleView_0045287b {
    unsigned char reserved_0000[0x28];
    int ctype_category_reference_count;
    unsigned char reserved_002c[0x1c];
    const unsigned char* ctype_table;
};

struct Atoi64ThreadDataView_0045287b {
    unsigned char reserved_0000[0x64];
    Atoi64LocaleView_0045287b* locale;
};

extern "C" void* __cdecl asm_getptd_00456357();
extern "C" void* __cdecl asm_updatetlocinfo_00455ade();
extern "C" int __cdecl asm_isctype_mt_00455752(
    void* locale, int character, int mask);
extern "C" Atoi64LocaleView_0045287b* data_0047320c;

extern "C" __int64 __cdecl asm_unassigned_0045287b(const char* text) {
    Atoi64ThreadDataView_0045287b* thread_data =
        static_cast<Atoi64ThreadDataView_0045287b*>(asm_getptd_00456357());
    Atoi64LocaleView_0045287b* locale = thread_data->locale;
    if (locale != data_0047320c) {
        locale = static_cast<Atoi64LocaleView_0045287b*>(
            asm_updatetlocinfo_00455ade());
    }

    const unsigned char* cursor =
        reinterpret_cast<const unsigned char*>(text);
    for (;;) {
        const unsigned char character = *cursor;
        const int is_space = locale->ctype_category_reference_count <= 1
            ? (locale->ctype_table[static_cast<unsigned int>(character) * 2] & 8)
            : asm_isctype_mt_00455752(locale, character, 8);
        if (is_space == 0) break;
        ++cursor;
    }

    const unsigned char sign = *cursor++;
    unsigned char character = sign;
    if (character == '-' || character == '+') {
        character = *cursor++;
    }

    // Unsigned arithmetic models the retail two-word multiply/add wraparound.
    unsigned __int64 value = 0;
    while (character >= '0' && character <= '9') {
        value = value * 10u + static_cast<unsigned int>(character - '0');
        character = *cursor++;
    }

    if (sign == '-') value = 0u - value;
    return static_cast<__int64>(value);
}
