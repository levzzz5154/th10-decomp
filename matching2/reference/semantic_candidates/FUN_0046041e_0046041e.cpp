// Ordinary four-argument cdecl CRT locale helper. The existing assembly
// callers push these arguments and consume the EAX status result.
#include "asm_symbols.hpp"

// 0x0046041E..0x0046054D: mode 1 returns an allocated ANSI locale string
// through output; mode 0 parses a short wide locale value into one byte.
extern "C" int __cdecl asm_FUN_0046041e_0046041e(
    int mode,
    unsigned int locale_id,
    unsigned int locale_type,
    void* output) {
    if (mode == 0) {
        unsigned short* const wide_value =
            reinterpret_cast<unsigned short*>(0x004776c4);
        if (asm_crtGetLocaleInfoW_00461565(
                locale_id, locale_type, wide_value, 4, 0) == 0) {
            return -1;
        }

        unsigned char* const value = static_cast<unsigned char*>(output);
        *value = 0;
        for (unsigned int index = 0; index != 4; ++index) {
            const unsigned char digit =
                static_cast<unsigned char>(wide_value[index]);
            if (asm_isdigit_0045685e(digit) == 0) {
                break;
            }
            *value = static_cast<unsigned char>(
                static_cast<unsigned int>(*value) * 10u + digit - '0');
        }
        return 0;
    }

    if (mode != 1) {
        return -1;
    }

    char local_value[0x80];
    char* source = local_value;
    bool owns_source = false;
    int value_length = asm_crtGetLocaleInfoA_00461695(
        locale_id, locale_type, local_value, sizeof(local_value), 0);

    if (value_length == 0) {
        typedef unsigned long (__stdcall *GetLastErrorFunction)(void);
        GetLastErrorFunction const get_last_error =
            *reinterpret_cast<GetLastErrorFunction*>(&data_0046610c);
        if (get_last_error() != 0x7a) {
            return -1;
        }

        value_length = asm_crtGetLocaleInfoA_00461695(
            locale_id, locale_type, 0, 0, 0);
        if (value_length == 0) {
            return -1;
        }

        source = static_cast<char*>(
            asm_malloc_00452706(static_cast<unsigned int>(value_length)));
        if (source == 0) {
            return -1;
        }
        owns_source = true;

        value_length = asm_crtGetLocaleInfoA_00461695(
            locale_id, locale_type, source, value_length, 0);
        if (value_length == 0) {
            asm_free_00452422(source);
            return -1;
        }
    }

    char* const destination = static_cast<char*>(
        asm_malloc_00452706(static_cast<unsigned int>(value_length)));
    *static_cast<char**>(output) = destination;
    if (destination == 0) {
        if (owns_source) {
            asm_free_00452422(source);
        }
        return -1;
    }

    asm_strncpy_00452960(
        destination, source, static_cast<unsigned int>(value_length));
    if (owns_source) {
        asm_free_00452422(source);
    }
    return 0;
}
