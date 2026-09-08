#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427E10..0x00427E12: FUN_00427e10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427e10_00427e10() {
    __asm {
    L_00427e10:
        mov eax,ecx
    L_00427e12:
        ret
    }
}
