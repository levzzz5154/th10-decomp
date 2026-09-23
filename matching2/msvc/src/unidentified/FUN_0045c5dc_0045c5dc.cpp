#include <cstdint>

// 0x0045C5DC..0x0045C650: query the neutral locale's default language.
// The optional check also rejects a language-only current locale string
// when that string does not match the queried LCID.
using GetLocaleInfoAFunction_0045c5dc = int (__stdcall *)(
    std::uint32_t locale, std::uint32_t type, char* buffer, int buffer_size);

extern "C" unsigned char data_00477644;
extern "C" unsigned char data_00477648;
extern "C" int __fastcall asm_LcidFromHexString_0045c4f2(
    int ignored_ecx, const char* text);
extern "C" int __fastcall asm_GetPrimaryLen_0045c527(
    int ignored_ecx, const char* text);
extern "C" unsigned int __cdecl asm_strlen_00456720(const char* text);

extern "C" int __cdecl asm_FUN_0045c5dc_0045c5dc(
    unsigned int locale_id, int check_locale_text) {
    char locale_info[120];

    const GetLocaleInfoAFunction_0045c5dc get_locale_info =
        *reinterpret_cast<GetLocaleInfoAFunction_0045c5dc const*>(
            &data_00477648);
    const std::uint32_t neutral_locale_id =
        (locale_id & 0x3ffu) | 0x400u;
    if (get_locale_info(neutral_locale_id, 1, locale_info,
                        static_cast<int>(sizeof(locale_info))) == 0) {
        return 0;
    }

    const unsigned int default_language = static_cast<unsigned int>(
        asm_LcidFromHexString_0045c4f2(0, locale_info));
    if (locale_id == default_language || check_locale_text == 0) {
        return 1;
    }

    const char* current_locale_text =
        *reinterpret_cast<const char* const*>(&data_00477644);
    const unsigned int current_locale_length =
        asm_strlen_00456720(current_locale_text);
    const int primary_language_length =
        asm_GetPrimaryLen_0045c527(0, current_locale_text);

    return static_cast<unsigned int>(primary_language_length) !=
           current_locale_length;
}
