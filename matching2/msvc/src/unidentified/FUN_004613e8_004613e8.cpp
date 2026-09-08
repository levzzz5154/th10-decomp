#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004613E8..0x004613EF: FUN_004613e8
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004613e8_004613e8() {
    __asm {
    L_004613e8:
        push ebx
    L_004613e9:
        call asm_FUN_0045f7b5_0045f7b5
    L_004613ee:
        pop ecx
    L_004613ef:
        ret
    }
}
