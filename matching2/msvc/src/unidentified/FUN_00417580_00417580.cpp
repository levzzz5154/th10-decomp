#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417580..0x00417583: FUN_00417580
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417580_00417580() {
    __asm {
    L_00417580:
        mov dword ptr [eax+5Ch],ecx
    L_00417583:
        ret
    }
}
