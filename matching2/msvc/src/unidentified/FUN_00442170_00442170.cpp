#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442170..0x00442173: FUN_00442170
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442170_00442170() {
    __asm {
    L_00442170:
        mov dword ptr [ecx+48h],eax
    L_00442173:
        ret
    }
}
