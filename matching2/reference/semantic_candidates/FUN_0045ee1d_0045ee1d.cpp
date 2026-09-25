#include <malloc.h>

// This is a CRT locale mapping worker. Keep the import-slot and private helper
// declarations local to preserve the source's own API types.
typedef unsigned int LCID_0045EE1D;
typedef unsigned int DWORD_0045EE1D;
typedef unsigned int UINT_0045EE1D;
typedef int BOOL_0045EE1D;
typedef const unsigned short* LPCWSTR_0045EE1D;
typedef unsigned short* LPWSTR_0045EE1D;
typedef int* LPBOOL_0045EE1D;

extern "C" int (__stdcall *data_0046603c)(LCID_0045EE1D, DWORD_0045EE1D,
                                          LPCWSTR_0045EE1D, int,
                                          LPWSTR_0045EE1D, int); // LCMapStringW
extern "C" int (__stdcall *data_00466040)(LCID_0045EE1D, DWORD_0045EE1D,
                                          const char*, int, char*, int); // LCMapStringA
extern "C" int (__stdcall *data_00466104)(UINT_0045EE1D, DWORD_0045EE1D,
                                          const char*, int,
                                          LPWSTR_0045EE1D, int); // MultiByteToWideChar
extern "C" DWORD_0045EE1D (__stdcall *data_0046610c)(void); // GetLastError
extern "C" int (__stdcall *data_00466154)(UINT_0045EE1D, DWORD_0045EE1D,
                                          LPCWSTR_0045EE1D, int, char*, int,
                                          const char*, LPBOOL_0045EE1D);

extern "C" unsigned int data_00477654; // default locale
extern "C" unsigned int data_00477664; // default multibyte code page
extern "C" unsigned int data_00477694; // cached LCMapStringW availability: 0 unknown, 1 yes, 2 unavailable

extern "C" long __cdecl asm_FUN_004601a1_004601a1(unsigned int locale);
extern "C" int* __cdecl asm_FUN_004601e8_004601e8(
    unsigned int source_code_page, unsigned int destination_code_page,
    char* source, unsigned int* source_count, int* destination,
    int destination_count);
extern "C" void* __cdecl asm_FUN_0045794d_0045794d(
    unsigned int element_size, unsigned int element_count);
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
extern "C" void __cdecl asm_free_00452422(void* memory);
extern "C" void* __cdecl asm_memset_0045bed0(
    void* destination, int value, unsigned int size);
extern "C" void __cdecl asm_resetstkoflw_00458d91(void);

// 0x0045EE1D..0x0045F1F2: locale-sensitive ANSI string mapping.
// The observed ABI is cdecl with eight stack arguments and an integer result.
extern "C" int __cdecl asm_FUN_0045ee1d_0045ee1d(
    LCID_0045EE1D locale, DWORD_0045EE1D map_flags, const char* source,
    int source_count, char* destination, int destination_count,
    UINT_0045EE1D code_page, BOOL_0045EE1D reject_invalid_multibyte) {
    unsigned int wide_api_state = data_00477694;
    unsigned short* volatile wide_source = 0;
    unsigned short* volatile wide_mapped = 0;
    int volatile free_wide_source = 0;
    int volatile free_wide_mapped = 0;
    char* volatile legacy_source = 0;
    char* volatile legacy_mapped = 0;
    char* volatile legacy_result = 0;
    int volatile free_legacy_mapped = 0;
    int result = 0;

    __try {
        if (wide_api_state == 0) {
            const unsigned short empty_string[1] = { 0 };
            if (data_0046603c(0, 0x100, empty_string, 1, 0, 0) != 0) {
                wide_api_state = 1;
                data_00477694 = 1;
            } else if (data_0046610c() == 0x78) {
                wide_api_state = 2;
                data_00477694 = 2;
            }
        }

        // The CRT treats a positive count as a bounded string and trims at
        // the first NUL. A count of -1 is passed through to the Win32 APIs.
        if (source_count > 0) {
            for (int index = 0; index < source_count; ++index) {
                if (source[index] == '\0') {
                    source_count = index;
                    break;
                }
            }
        }

        if (wide_api_state == 1) {
            if (code_page == 0)
                code_page = data_00477664;

            const DWORD_0045EE1D conversion_flags =
                1 | (reject_invalid_multibyte != 0 ? 8 : 0);
            int wide_count = data_00466104(code_page, conversion_flags,
                                           source, source_count, 0, 0);
            if (wide_count == 0)
                return 0;

            const unsigned int wide_bytes =
                (static_cast<unsigned int>(wide_count) * 2u + 3u) & ~3u;
            unsigned short* volatile stack_wide_source = 0;
            __try {
                stack_wide_source =
                    static_cast<unsigned short*>(_alloca(wide_bytes));
            } __except (1) {
                asm_resetstkoflw_00458d91();
            }
            wide_source = stack_wide_source;
            if (wide_source == 0) {
                wide_source = static_cast<unsigned short*>(
                    asm_malloc_00452706(
                        static_cast<unsigned int>(wide_count) * 2u));
                if (wide_source == 0)
                    return 0;
                free_wide_source = 1;
            }

            if (data_00466104(code_page, conversion_flags, source,
                              source_count, wide_source, wide_count) == 0)
                return 0;

            int mapped_count = data_0046603c(
                locale, map_flags, wide_source, wide_count, 0, 0);
            if (mapped_count == 0)
                return 0;

            if ((map_flags & 0x400) != 0) {
                if (destination_count != 0 &&
                    mapped_count <= destination_count) {
                    result = data_0046603c(
                        locale, map_flags, wide_source, wide_count,
                        reinterpret_cast<unsigned short*>(destination),
                        destination_count);
                }
                return result;
            }

            const unsigned int mapped_bytes =
                (static_cast<unsigned int>(mapped_count) * 2u + 3u) & ~3u;
            unsigned short* volatile stack_wide_mapped = 0;
            __try {
                stack_wide_mapped =
                    static_cast<unsigned short*>(_alloca(mapped_bytes));
            } __except (1) {
                asm_resetstkoflw_00458d91();
            }
            wide_mapped = stack_wide_mapped;
            if (wide_mapped == 0) {
                wide_mapped = static_cast<unsigned short*>(
                    asm_malloc_00452706(
                        static_cast<unsigned int>(mapped_count) * 2u));
                if (wide_mapped == 0)
                    return 0;
                free_wide_mapped = 1;
            }

            if (data_0046603c(locale, map_flags, wide_source, wide_count,
                              wide_mapped, mapped_count) == 0)
                return 0;

            char* output = destination_count == 0 ? 0 : destination;
            int output_capacity = destination_count == 0 ? 0 : destination_count;
            result = data_00466154(code_page, 0, wide_mapped,
                                   mapped_count, output, output_capacity,
                                   0, 0);
            return result;
        }

        if (wide_api_state != 0 && wide_api_state != 2)
            return 0;

        if (locale == 0)
            locale = data_00477654;
        if (code_page == 0)
            code_page = data_00477664;

        const long locale_code_page = asm_FUN_004601a1_004601a1(locale);
        if (locale_code_page == -1)
            return 0;

        if (static_cast<unsigned int>(locale_code_page) == code_page) {
            result = data_00466040(locale, map_flags, source, source_count,
                                   destination, destination_count);
            return result;
        }

        unsigned int converted_source_count =
            static_cast<unsigned int>(source_count);
        legacy_source = reinterpret_cast<char*>(
            asm_FUN_004601e8_004601e8(
                code_page, static_cast<unsigned int>(locale_code_page),
                const_cast<char*>(source), &converted_source_count, 0, 0));
        if (legacy_source == 0)
            return 0;

        int mapped_capacity = data_00466040(
            locale, map_flags, legacy_source,
            static_cast<int>(converted_source_count), 0, 0);
        if (mapped_capacity == 0)
            return 0;

        const unsigned int mapped_bytes =
            (static_cast<unsigned int>(mapped_capacity) + 3u) & ~3u;
        char* volatile stack_legacy_mapped = 0;
        __try {
            stack_legacy_mapped = static_cast<char*>(_alloca(mapped_bytes));
        } __except (1) {
            asm_resetstkoflw_00458d91();
        }
        legacy_mapped = stack_legacy_mapped;
        if (legacy_mapped == 0) {
            legacy_mapped = static_cast<char*>(
                asm_FUN_0045794d_0045794d(
                    1, static_cast<unsigned int>(mapped_capacity)));
            if (legacy_mapped == 0)
                return 0;
            free_legacy_mapped = 1;
        }
        asm_memset_0045bed0(legacy_mapped, 0,
                            static_cast<unsigned int>(mapped_capacity));

        const int mapped_count = data_00466040(
            locale, map_flags, legacy_source,
            static_cast<int>(converted_source_count), legacy_mapped,
            mapped_capacity);
        if (mapped_count == 0)
            return 0;

        unsigned int converted_mapped_count =
            static_cast<unsigned int>(mapped_count);
        legacy_result = reinterpret_cast<char*>(
            asm_FUN_004601e8_004601e8(
                static_cast<unsigned int>(locale_code_page), code_page,
                legacy_mapped, &converted_mapped_count,
                reinterpret_cast<int*>(destination), destination_count));
        if (legacy_result != 0)
            result = static_cast<int>(converted_mapped_count);
    } __finally {
        if (free_legacy_mapped)
            asm_free_00452422(legacy_mapped);
        if (legacy_source != 0)
            asm_free_00452422(legacy_source);
        if (legacy_result != 0 && legacy_result != destination)
            asm_free_00452422(legacy_result);
        if (free_wide_mapped)
            asm_free_00452422(wide_mapped);
        if (free_wide_source)
            asm_free_00452422(wide_source);
    }

    return result;
}
