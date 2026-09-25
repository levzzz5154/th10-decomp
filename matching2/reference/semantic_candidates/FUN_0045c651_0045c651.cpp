#include <cstdint>

// 0x0045C651..0x0045C86E: locale-enumeration callback.
typedef int (__stdcall *GetLocaleInfoAFunction_0045c651)(
    std::uint32_t locale, std::uint32_t type, char* buffer, int buffer_size);

extern "C" unsigned char data_00477628;
extern "C" unsigned char data_0047762c;
extern "C" unsigned char data_00477630;
extern "C" unsigned char data_00477634;
extern "C" unsigned char data_00477638;
extern "C" unsigned char data_0047763c;
extern "C" unsigned char data_00477640;
extern "C" unsigned char data_00477644;
extern "C" unsigned char data_00477648;

extern "C" int __fastcall asm_LcidFromHexString_0045c4f2(
    int ignored_ecx, const char* text);
extern "C" int __cdecl asm_FUN_0045c3f1_0045c3f1(short value);
extern "C" int __cdecl asm_FUN_0045c5dc_0045c5dc(
    unsigned int locale_id, int check_locale_text);
extern "C" int __cdecl asm_stricmp_0046054e(
    const unsigned char* left, const unsigned char* right);
extern "C" int __cdecl asm_strnicmp_004605b7(
    const unsigned char* left, const unsigned char* right,
    unsigned int count);
extern "C" unsigned int __cdecl asm_strlen_00456720(const char* text);

extern "C" int __stdcall asm_FUN_0045c651_0045c651(char* locale_name) {
    char locale_info[120];
    std::uint32_t& match_state =
        *reinterpret_cast<std::uint32_t*>(&data_00477628);
    const char* const language_text =
        *reinterpret_cast<const char* const*>(&data_00477644);
    const char* const country_text =
        *reinterpret_cast<const char* const*>(&data_0047763c);
    std::uint32_t& selected_locale =
        *reinterpret_cast<std::uint32_t*>(&data_0047762c);
    std::uint32_t& current_locale =
        *reinterpret_cast<std::uint32_t*>(&data_00477630);
    const std::uint32_t primary_language_length =
        *reinterpret_cast<std::uint32_t*>(&data_00477640);
    const bool language_text_has_three_characters =
        *reinterpret_cast<std::uint32_t*>(&data_00477634) != 0;
    const bool country_text_has_three_characters =
        *reinterpret_cast<std::uint32_t*>(&data_00477638) != 0;

    const std::uint32_t locale_id = static_cast<std::uint32_t>(
        asm_LcidFromHexString_0045c4f2(0, locale_name));
    const GetLocaleInfoAFunction_0045c651 get_locale_info =
        *reinterpret_cast<GetLocaleInfoAFunction_0045c651 const*>(
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
            reinterpret_cast<const unsigned char*>(locale_info)) == 0) {
        const std::uint32_t language_name_type =
            language_text_has_three_characters ? 3u : 0x1001u;
        if (get_locale_info(locale_id, language_name_type, locale_info,
                            static_cast<int>(sizeof(locale_info))) == 0) {
            match_state = 0;
            return 1;
        }

        if (asm_stricmp_0046054e(
                reinterpret_cast<const unsigned char*>(language_text),
                reinterpret_cast<const unsigned char*>(locale_info)) == 0) {
            *reinterpret_cast<std::uint16_t*>(&data_00477628) |= 0x304u;
            selected_locale = locale_id;
            current_locale = locale_id;
        } else if ((match_state & 2u) == 0) {
            const bool primary_language_matches =
                primary_language_length != 0 &&
                asm_strnicmp_004605b7(
                    reinterpret_cast<const unsigned char*>(language_text),
                    reinterpret_cast<const unsigned char*>(locale_info),
                    primary_language_length) == 0;
            if (primary_language_matches) {
                match_state |= 2u;
                current_locale = locale_id;
                if (asm_strlen_00456720(language_text) ==
                    primary_language_length) {
                    selected_locale = locale_id;
                }
            } else if ((match_state & 1u) == 0 &&
                       asm_FUN_0045c3f1_0045c3f1(
                           static_cast<short>(locale_id)) != 0) {
                match_state |= 1u;
                current_locale = locale_id;
            }
        }
    }

    if ((match_state & 0x300u) != 0x300u) {
        const std::uint32_t language_name_type =
            language_text_has_three_characters ? 3u : 0x1001u;
        if (get_locale_info(locale_id, language_name_type, locale_info,
                            static_cast<int>(sizeof(locale_info))) == 0) {
            match_state = 0;
            return 1;
        }

        const bool language_name_matches =
            asm_stricmp_0046054e(
                reinterpret_cast<const unsigned char*>(language_text),
                reinterpret_cast<const unsigned char*>(locale_info)) == 0;
        if (language_name_matches) {
            reinterpret_cast<std::uint8_t*>(&data_00477628)[1] |= 2u;
            if (!language_text_has_three_characters &&
                primary_language_length != 0 &&
                asm_strlen_00456720(language_text) ==
                    primary_language_length &&
                asm_FUN_0045c5dc_0045c5dc(locale_id, 1) == 0) {
                return static_cast<int>((~(match_state >> 2)) & 1u);
            }
        } else {
            if (language_text_has_three_characters ||
                primary_language_length == 0 ||
                asm_strnicmp_004605b7(
                    reinterpret_cast<const unsigned char*>(language_text),
                    reinterpret_cast<const unsigned char*>(locale_info),
                    primary_language_length) != 0) {
                return static_cast<int>((~(match_state >> 2)) & 1u);
            }
            if (asm_FUN_0045c5dc_0045c5dc(locale_id, 0) == 0) {
                return static_cast<int>((~(match_state >> 2)) & 1u);
            }
        }

        reinterpret_cast<std::uint8_t*>(&data_00477628)[1] |= 1u;
        if (selected_locale == 0) {
            selected_locale = locale_id;
        }
    }

    return static_cast<int>((~(match_state >> 2)) & 1u);
}
