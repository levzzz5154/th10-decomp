#include <cstdint>

typedef int (__stdcall *EnumLocaleCallback)(char* locale_name);
typedef int (__stdcall *EnumSystemLocalesAFunction)(
    EnumLocaleCallback callback, std::uint32_t flags);

extern "C" unsigned char imp_EnumSystemLocalesA;
extern "C" unsigned char g_crt_lcid_country;
extern "C" unsigned char g_crt_lcid_country_b;
extern "C" unsigned char g_crt_lcid_country_c;

extern "C" unsigned int __cdecl crt_strlen(const char* text);
extern "C" int __stdcall crt_helper_45c544(char* locale_name);

extern "C" void __cdecl crt_libcmt_getqloc_GetLcidFromCountry() {
    const char* const country_text =
        *reinterpret_cast<const char* const*>(&g_crt_lcid_country_c);
    *reinterpret_cast<std::uint32_t*>(&g_crt_lcid_country_b) =
        crt_strlen(country_text) == 3 ? 1u : 0u;

    const EnumSystemLocalesAFunction enum_system_locales_a =
        *reinterpret_cast<EnumSystemLocalesAFunction const*>(
            &imp_EnumSystemLocalesA);
    enum_system_locales_a(&crt_helper_45c544, 1);

    const std::uint8_t locale_match_state_low_byte =
        *reinterpret_cast<const std::uint8_t*>(&g_crt_lcid_country);
    if ((locale_match_state_low_byte & 4u) == 0) {
        *reinterpret_cast<std::uint32_t*>(&g_crt_lcid_country) = 0;
    }
}
