#include <cstdint>

typedef int (__stdcall *EnumLocaleCallback_0045c93e)(char* locale_name);
typedef int (__stdcall *EnumSystemLocalesAFunction_0045c93e)(
    EnumLocaleCallback_0045c93e callback, std::uint32_t flags);

extern "C" unsigned char imp_EnumSystemLocalesA;
extern "C" unsigned char g_crt_lcid_country;
extern "C" unsigned char g_crt_lcid_country_b;
extern "C" unsigned char g_crt_lcid_country_c;

extern "C" unsigned int __cdecl asm_strlen_00456720(const char* text);
extern "C" int __stdcall asm_FUN_0045c544_0045c544(char* locale_name);

extern "C" void __cdecl asm_GetLcidFromCountry_0045c93e() {
    const char* const country_text =
        *reinterpret_cast<const char* const*>(&g_crt_lcid_country_c);
    *reinterpret_cast<std::uint32_t*>(&g_crt_lcid_country_b) =
        asm_strlen_00456720(country_text) == 3 ? 1u : 0u;

    const EnumSystemLocalesAFunction_0045c93e enum_system_locales_a =
        *reinterpret_cast<EnumSystemLocalesAFunction_0045c93e const*>(
            &imp_EnumSystemLocalesA);
    enum_system_locales_a(&asm_FUN_0045c544_0045c544, 1);

    const std::uint8_t locale_match_state_low_byte =
        *reinterpret_cast<const std::uint8_t*>(&g_crt_lcid_country);
    if ((locale_match_state_low_byte & 4u) == 0) {
        *reinterpret_cast<std::uint32_t*>(&g_crt_lcid_country) = 0;
    }
}
