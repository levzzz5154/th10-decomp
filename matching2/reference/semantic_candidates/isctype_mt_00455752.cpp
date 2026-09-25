#include "asm_symbols.hpp"

struct IsctypeLocaleView {
    unsigned char reserved_0000[0x4];
    unsigned int code_page;
    unsigned char reserved_0008[0xc];
    unsigned int locale_id;
    unsigned char reserved_0018[0x30];
    const unsigned short* ctype_table;
};

// 0x00455752..0x004557C8: ___isctype_mt
extern "C" int __cdecl asm_isctype_mt_00455752(void* locale_pointer, int character, int mask) {
    const IsctypeLocaleView* locale =
        static_cast<const IsctypeLocaleView*>(locale_pointer);
    unsigned short character_type;

    if (static_cast<unsigned int>(character) + 1u < 0x101u) {
        // The table pointer is biased to include the CRT's EOF entry at -1.
        character_type = locale->ctype_table[character];
    } else {
        const unsigned int code = static_cast<unsigned int>(character);
        const unsigned char low_byte = static_cast<unsigned char>(code);
        const unsigned char high_byte = static_cast<unsigned char>(code >> 8);
        const unsigned char* ctype_bytes =
            reinterpret_cast<const unsigned char*>(locale->ctype_table);
        const bool is_lead_byte =
            (ctype_bytes[static_cast<unsigned int>(high_byte) * 2u + 1u] & 0x80u) != 0;

        char source[3];
        int source_length = 1;
        if (is_lead_byte) {
            source[0] = static_cast<char>(high_byte);
            source[1] = static_cast<char>(low_byte);
            source[2] = 0;
            source_length = 2;
        } else {
            source[0] = static_cast<char>(low_byte);
            source[1] = 0;
            source[2] = 0;
        }

        character_type = 0;
        const int succeeded = asm_crtGetStringTypeA_0045a25d(
            1, source, source_length, &character_type,
            locale->code_page, locale->locale_id, 1);
        if (succeeded == 0) return 0;
    }

    return static_cast<int>(character_type & static_cast<unsigned int>(mask));
}
