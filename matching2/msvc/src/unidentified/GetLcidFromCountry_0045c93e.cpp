#include <cstdint>

using EnumLocaleCallback_0045c93e = int (__stdcall *)(char* locale_name);
using EnumSystemLocalesAFunction_0045c93e = int (__stdcall *)(
    EnumLocaleCallback_0045c93e callback, std::uint32_t flags);

extern "C" unsigned char data_00466058;
extern "C" unsigned char data_00477628;
extern "C" unsigned char data_00477638;
extern "C" unsigned char data_0047763c;

extern "C" unsigned int __cdecl asm_strlen_00456720(const char* text);
extern "C" int __stdcall asm_FUN_0045c544_0045c544(char* locale_name);

extern "C" void __cdecl asm_GetLcidFromCountry_0045c93e() {
    const char* const country_text =
        *reinterpret_cast<const char* const*>(&data_0047763c);
    *reinterpret_cast<std::uint32_t*>(&data_00477638) =
        asm_strlen_00456720(country_text) == 3 ? 1u : 0u;

    const EnumSystemLocalesAFunction_0045c93e enum_system_locales_a =
        *reinterpret_cast<EnumSystemLocalesAFunction_0045c93e const*>(
            &data_00466058);
    enum_system_locales_a(&asm_FUN_0045c544_0045c544, 1);

    const std::uint8_t locale_match_state_low_byte =
        *reinterpret_cast<const std::uint8_t*>(&data_00477628);
    if ((locale_match_state_low_byte & 4u) == 0) {
        *reinterpret_cast<std::uint32_t*>(&data_00477628) = 0;
    }
}
