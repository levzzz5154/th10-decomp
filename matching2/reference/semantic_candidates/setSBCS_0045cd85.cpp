#include "asm_symbols.hpp"

// 0x0045CD85..0x0045CDAD: setSBCS
extern "C" void __cdecl asm_setSBCS_0045cd85() {
    volatile unsigned int* ctype_words =
        reinterpret_cast<volatile unsigned int*>(&data_00497fa0);
    for (unsigned int i = 0; i != 0x40; ++i) ctype_words[i] = 0;
    reinterpret_cast<volatile unsigned char*>(ctype_words)[0x100] = 0;

    *reinterpret_cast<volatile unsigned int*>(&data_004980a4) = 0;
    *reinterpret_cast<volatile unsigned int*>(&data_00497f98) = 0;
    *reinterpret_cast<volatile unsigned int*>(&data_00497f90) = 0;

    volatile unsigned int* multibyte_state =
        reinterpret_cast<volatile unsigned int*>(&data_004980b0);
    multibyte_state[0] = 0;
    multibyte_state[1] = 0;
    multibyte_state[2] = 0;
}
