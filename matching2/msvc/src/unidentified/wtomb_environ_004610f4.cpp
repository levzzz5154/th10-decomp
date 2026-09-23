#include "asm_symbols.hpp"

typedef int (__stdcall *WideCharToMultiByte_004610F4)(
    unsigned int codePage,
    unsigned int flags,
    const unsigned short* wideText,
    int wideCharacterCount,
    char* output,
    int outputSize,
    const char* defaultCharacter,
    int* usedDefaultCharacter);

extern "C" int __cdecl WtombEnviron_004610F4(void) {
    const WideCharToMultiByte_004610F4 convertWideToMultiByte =
        *reinterpret_cast<WideCharToMultiByte_004610F4*>(&data_00466154);
    const unsigned short* const* wideEnvironment =
        *reinterpret_cast<const unsigned short* const**>(&data_00477498);

    const unsigned short* const* current = wideEnvironment;
    while (*current != 0) {
        const unsigned short* wideString = *current;
        const int outputSize = convertWideToMultiByte(
            0, 0, wideString, -1, 0, 0, 0, 0);
        if (outputSize == 0) {
            return -1;
        }

        char* convertedString = static_cast<char*>(
            asm_malloc_00452706(static_cast<unsigned int>(outputSize)));
        if (convertedString == 0) {
            return -1;
        }

        if (convertWideToMultiByte(
                0, 0, wideString, -1, convertedString, outputSize, 0, 0) == 0) {
            asm_free_00452422(convertedString);
            return -1;
        }

        const int addResult = asm_FUN_00461f31_00461f31(&convertedString, 0);
        if (addResult < 0 && convertedString != 0) {
            asm_free_00452422(convertedString);
            convertedString = 0;
        }

        ++current;
    }

    return 0;
}
