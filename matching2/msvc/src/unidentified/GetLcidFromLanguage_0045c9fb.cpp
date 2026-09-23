#include <cstdint>

// 0x0045C9FB..0x0045CA4F: _GetLcidFromLanguage
// Prepares the language-text globals, enumerates installed locales through
// the stored EnumSystemLocalesA entry point, and clears the result on failure.
using EnumLocaleCallback_0045c9fb = int (__stdcall *)(char* locale_name);
using EnumSystemLocalesAFunction_0045c9fb = int (__stdcall *)(
    EnumLocaleCallback_0045c9fb callback, std::uint32_t flags);

extern "C" unsigned char data_00466058;
extern "C" unsigned char data_00477628;
extern "C" unsigned char data_00477634;
extern "C" unsigned char data_00477640;
extern "C" unsigned char data_00477644;

extern "C" unsigned int __cdecl asm_strlen_00456720(const char* text);
extern "C" int __fastcall asm_GetPrimaryLen_0045c527(
    int ignored_ecx, const char* text);
extern "C" int __stdcall asm_FUN_0045c86f_0045c86f(char* locale_name);

extern "C" void __cdecl asm_GetLcidFromLanguage_0045c9fb() {
    const char* const locale_text =
        *reinterpret_cast<const char* const*>(&data_00477644);
    const unsigned int locale_text_length = asm_strlen_00456720(locale_text);
    const bool locale_text_has_three_characters = locale_text_length == 3;

    *reinterpret_cast<std::uint32_t*>(&data_00477634) =
        locale_text_has_three_characters ? 1u : 0u;
    *reinterpret_cast<std::uint32_t*>(&data_00477640) =
        locale_text_has_three_characters
            ? 2u
            : static_cast<std::uint32_t>(
                  asm_GetPrimaryLen_0045c527(0, locale_text));

    const EnumLocaleCallback_0045c9fb callback = &asm_FUN_0045c86f_0045c86f;
    const EnumSystemLocalesAFunction_0045c9fb enum_system_locales_a =
        *reinterpret_cast<EnumSystemLocalesAFunction_0045c9fb const*>(
            &data_00466058);
    enum_system_locales_a(callback, 1);

    const std::uint8_t locale_match_state_low_byte =
        *reinterpret_cast<const std::uint8_t*>(&data_00477628);
    if ((locale_match_state_low_byte & 4u) == 0) {
        *reinterpret_cast<std::uint32_t*>(&data_00477628) = 0;
    }
}
