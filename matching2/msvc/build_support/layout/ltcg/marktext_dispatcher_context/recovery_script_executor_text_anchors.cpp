// Genuine, complete helper models for the 0040BD80 caller cluster.
// The native MSVC LTCG build determines the helpers' private register inputs.

#include <stdarg.h>
#include "th10/game/ending_text_dispatcher.hpp"

extern "C" unsigned char recovery_decoded_path_00497d40[];

#pragma code_seg(".text$00417010_fn")
char* __stdcall EndingScript_DecodePath(const unsigned char* encoded) {
    unsigned char* output = recovery_decoded_path_00497d40;
    unsigned char key = 0x77;
    unsigned char increment = 7;
    unsigned char decoded;
    do {
        decoded = *encoded ^ key;
        *output = decoded;
        ++output;
        key += increment;
        ++encoded;
        increment += 0x10;
    } while (decoded != 0);
    return reinterpret_cast<char*>(recovery_decoded_path_00497d40);
}
#pragma code_seg()

