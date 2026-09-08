#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040ABF0..0x0040ABF9: FUN_0040abf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040abf0_0040abf0() {
    __asm {
    L_0040abf0:
        push edi
    L_0040abf1:
        mov edi,ecx
    L_0040abf3:
        call asm_FUN_0040a940_0040a940
    L_0040abf8:
        pop edi
    L_0040abf9:
        ret
    }
}
