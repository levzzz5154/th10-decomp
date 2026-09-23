#include <cstdint>

// 0x0045C544..0x0045C5DB: country-only locale-enumeration callback.
using GetLocaleInfoAFunction_0045c544 = int (__stdcall *)(
    std::uint32_t locale, std::uint32_t type, char* buffer, int buffer_size);

extern "C" unsigned char data_00477628;
extern "C" unsigned char data_0047762c;
extern "C" unsigned char data_00477630;
extern "C" unsigned char data_00477638;
extern "C" unsigned char data_0047763c;
extern "C" unsigned char data_00477648;

extern "C" int __fastcall asm_LcidFromHexString_0045c4f2(
    int ignored_ecx, const char* text);
extern "C" int __cdecl asm_FUN_0045c3f1_0045c3f1(short value);
extern "C" int __cdecl asm_stricmp_0046054e(
    const unsigned char* left, const unsigned char* right);

extern "C" int __stdcall asm_FUN_0045c544_0045c544(char* locale_name) {
    char locale_info[120];
    const char* const country_text =
        *reinterpret_cast<const char* const*>(&data_0047763c);
    std::uint32_t& match_state =
        *reinterpret_cast<std::uint32_t*>(&data_00477628);
    const bool country_text_has_three_characters =
        *reinterpret_cast<std::uint32_t*>(&data_00477638) != 0;
    const std::uint32_t locale_id = static_cast<std::uint32_t>(
        asm_LcidFromHexString_0045c4f2(0, locale_name));
    const GetLocaleInfoAFunction_0045c544 get_locale_info =
        *reinterpret_cast<GetLocaleInfoAFunction_0045c544 const*>(
            &data_00477648);
    const std::uint32_t country_name_type =
        country_text_has_three_characters ? 7u : 0x1002u;

    if (get_locale_info(locale_id, country_name_type, locale_info,
                        static_cast<int>(sizeof(locale_info))) == 0) {
        match_state = 0;
        return 1;
    }

    if (asm_stricmp_0046054e(
            reinterpret_cast<const unsigned char*>(country_text),
            reinterpret_cast<const unsigned char*>(locale_info)) == 0 &&
        asm_FUN_0045c3f1_0045c3f1(static_cast<short>(locale_id)) != 0) {
        match_state |= 4u;
        *reinterpret_cast<std::uint32_t*>(&data_00477630) = locale_id;
        *reinterpret_cast<std::uint32_t*>(&data_0047762c) = locale_id;
    }

    return static_cast<int>((~(match_state >> 2)) & 1u);
}
