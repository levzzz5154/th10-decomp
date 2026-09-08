#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427C10..0x00427C30: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427c10() {
    __asm {
    L_00427c10:
        fld dword ptr [esi]
    L_00427c12:
        fmul dword ptr [data_00470b44]
    L_00427c18:
        call asm_FUN_00463b2c_00463b2c
    L_00427c1d:
        mov dword ptr [edi],eax
    L_00427c1f:
        fld dword ptr [esi+4]
    L_00427c22:
        fmul dword ptr [data_00470b44]
    L_00427c28:
        call asm_FUN_00463b2c_00463b2c
    L_00427c2d:
        mov dword ptr [edi+4],eax
    L_00427c30:
        ret
    }
}
