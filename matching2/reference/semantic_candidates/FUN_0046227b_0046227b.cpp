#include "asm_encoding.hpp"

#pragma comment(linker, "/alternatename:_asm_FUN_0046227b_0046227b=_FindMultibyteCharacter_0046227B")

struct ThreadData;
extern "C" ThreadData* __cdecl asm_getptd_00456357(void);
extern "C" void __cdecl asm_updatetmbcinfo_0045cf49(void);
extern "C" char* __cdecl asm_FUN_00452730_00452730(
    const char* text, int character);
extern "C" unsigned char data_00497f94;

// 0x00452720..0x00452724: FUN_0046227b
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046227b_part_00452720() {
    __asm {
    L_00452720:
        lea eax,[edx-1]
    L_00452723:
        pop ebx
    L_00452724:
        ret
    }
}

// 0x0046227B..0x004622F5: find a single- or double-byte character in a string.
extern "C" unsigned int* __cdecl FindMultibyteCharacter_0046227B(
        unsigned int* text, unsigned int character) {
    unsigned char* threadData =
        reinterpret_cast<unsigned char*>(asm_getptd_00456357());
    unsigned char* locale = *reinterpret_cast<unsigned char**>(threadData + 0x60);
    unsigned char* currentLocale =
        *reinterpret_cast<unsigned char**>(&data_00497f94);

    if (locale != currentLocale) {
        typedef unsigned char* (__cdecl *UpdateMultibyteLocale)(void);
        UpdateMultibyteLocale updateLocale =
            reinterpret_cast<UpdateMultibyteLocale>(asm_updatetmbcinfo_0045cf49);
        locale = updateLocale();
    }

    if (*reinterpret_cast<unsigned int*>(locale + 8) == 0) {
        return reinterpret_cast<unsigned int*>(asm_FUN_00452730_00452730(
            reinterpret_cast<const char*>(text), static_cast<int>(character)));
    }

    unsigned char* cursor = reinterpret_cast<unsigned char*>(text);
    for (;;) {
        unsigned char first = *cursor;
        if (first == 0) {
            return character == 0
                ? reinterpret_cast<unsigned int*>(cursor)
                : 0;
        }

        if ((locale[0x1D + first] & 4) == 0) {
            if (character == first)
                return reinterpret_cast<unsigned int*>(cursor);
            ++cursor;
            continue;
        }

        unsigned char second = cursor[1];
        if (second == 0)
            return 0;

        unsigned int pair = (static_cast<unsigned int>(first) << 8) | second;
        if (character == pair)
            return reinterpret_cast<unsigned int*>(cursor);
        cursor += 2;
    }
}
