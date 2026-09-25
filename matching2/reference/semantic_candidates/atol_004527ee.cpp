// Ghidra shows the locale pointer at ThreadData+0x64, the ctype category
// reference count at LocaleInfo+0x28, and the ctype table at +0x48.
struct AtolLocaleView {
    unsigned char reserved_0000[0x28];
    int ctype_category_reference_count;
    unsigned char reserved_002c[0x1c];
    const unsigned char* ctype_table;
};

struct AtolThreadDataView {
    unsigned char reserved_0000[0x64];
    AtolLocaleView* locale;
};

extern "C" void* __cdecl asm_getptd_00456357();
extern "C" void* __cdecl asm_updatetlocinfo_00455ade();
extern "C" int __cdecl asm_isctype_mt_00455752(void* locale, int character, int mask);
extern "C" AtolLocaleView* data_0047320c;

// 0x004527EE..0x00452875: _atol
// The retail boundary is cdecl(char const*) -> signed 32-bit long.
extern "C" long __cdecl asm_atol_004527ee(const char* text) {
    AtolThreadDataView* thread_data =
        static_cast<AtolThreadDataView*>(asm_getptd_00456357());
    AtolLocaleView* locale = thread_data->locale;
    if (locale != data_0047320c) {
        locale = static_cast<AtolLocaleView*>(asm_updatetlocinfo_00455ade());
    }

    const unsigned char* cursor = reinterpret_cast<const unsigned char*>(text);
    for (;;) {
        const unsigned char character = *cursor;
        const int is_space = locale->ctype_category_reference_count <= 1
            ? (locale->ctype_table[static_cast<unsigned int>(character) * 2] & 8)
            : asm_isctype_mt_00455752(locale, character, 8);
        if (is_space == 0) break;
        ++cursor;
    }

    const unsigned char sign = *cursor;
    unsigned char character = sign;
    if (character == '-' || character == '+') {
        ++cursor;
        character = *cursor;
    }

    // Unsigned arithmetic preserves the retail 32-bit wraparound on overflow.
    unsigned int value = 0;
    while (character >= '0' && character <= '9') {
        value = value * 10u + static_cast<unsigned int>(character - '0');
        ++cursor;
        character = *cursor;
    }
    if (sign == '-') value = 0u - value;
    return static_cast<long>(static_cast<int>(value));
}
