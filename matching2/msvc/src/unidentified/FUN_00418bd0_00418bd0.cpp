#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418BD0..0x00418BD3: FUN_00418bd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00418bd0_00418bd0() {
    __asm {
    L_00418bd0:
        mov dword ptr [eax+4],ecx
    L_00418bd3:
        ret
    }
}
