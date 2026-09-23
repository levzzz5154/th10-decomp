#include <cstdint>

// 0x0045C975..0x0045C9FA: _GetLcidFromLangCountry
// Prepares language and country length state, enumerates system locales, and
// retains the match state only when the callback found all required matches.
using EnumLocaleCallback_0045c975 = int (__stdcall *)(char* locale_name);
using EnumSystemLocalesAFunction_0045c975 = int (__stdcall *)(
    EnumLocaleCallback_0045c975 callback, std::uint32_t flags);

extern "C" unsigned char data_00466058;
extern "C" unsigned char data_00477628;
extern "C" unsigned char data_0047762c;
extern "C" unsigned char data_00477634;
extern "C" unsigned char data_00477638;
extern "C" unsigned char data_0047763c;
extern "C" unsigned char data_00477640;
extern "C" unsigned char data_00477644;

extern "C" unsigned int __cdecl asm_strlen_00456720(const char* text);
extern "C" int __fastcall asm_GetPrimaryLen_0045c527(
    int ignored_ecx, const char* text);
extern "C" int __stdcall asm_FUN_0045c651_0045c651(char* locale_name);

extern "C" void __cdecl asm_GetLcidFromLangCountry_0045c975() {
    const char* const language_text =
        *reinterpret_cast<const char* const*>(&data_00477644);
    const unsigned int language_text_length =
        asm_strlen_00456720(language_text);
    const bool language_text_has_three_characters =
        language_text_length == 3;
    *reinterpret_cast<std::uint32_t*>(&data_00477634) =
        language_text_has_three_characters ? 1u : 0u;

    const char* const country_text =
        *reinterpret_cast<const char* const*>(&data_0047763c);
    const unsigned int country_text_length =
        asm_strlen_00456720(country_text);
    const bool country_text_has_three_characters = country_text_length == 3;
    *reinterpret_cast<std::uint32_t*>(&data_0047762c) = 0;
    *reinterpret_cast<std::uint32_t*>(&data_00477638) =
        country_text_has_three_characters ? 1u : 0u;

    *reinterpret_cast<std::uint32_t*>(&data_00477640) =
        language_text_has_three_characters
            ? 2u
            : static_cast<std::uint32_t>(
                  asm_GetPrimaryLen_0045c527(0, language_text));

    const EnumLocaleCallback_0045c975 callback = &asm_FUN_0045c651_0045c651;
    const EnumSystemLocalesAFunction_0045c975 enum_system_locales_a =
        *reinterpret_cast<EnumSystemLocalesAFunction_0045c975 const*>(
            &data_00466058);
    enum_system_locales_a(callback, 1);

    const std::uint32_t locale_match_state =
        *reinterpret_cast<const std::uint32_t*>(&data_00477628);
    if ((locale_match_state & 0x100u) == 0 ||
        (locale_match_state & 0x200u) == 0 ||
        (locale_match_state & 0x7u) == 0) {
        *reinterpret_cast<std::uint32_t*>(&data_00477628) = 0;
    }
}
