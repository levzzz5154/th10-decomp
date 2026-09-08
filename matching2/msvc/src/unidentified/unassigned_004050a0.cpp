#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004050A0..0x004050CC: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004050a0() {
    __asm {
    L_004050a0:
        fld dword ptr [esi+8]
    L_004050a3:
        call asm_FUN_00463b2c_00463b2c
    L_004050a8:
        fld dword ptr [esi+0Ch]
    L_004050ab:
        mov byte ptr [esi+18h],al
    L_004050ae:
        call asm_FUN_00463b2c_00463b2c
    L_004050b3:
        fld dword ptr [esi+10h]
    L_004050b6:
        mov byte ptr [esi+19h],al
    L_004050b9:
        call asm_FUN_00463b2c_00463b2c
    L_004050be:
        fld dword ptr [esi+14h]
    L_004050c1:
        mov byte ptr [esi+1Ah],al
    L_004050c4:
        call asm_FUN_00463b2c_00463b2c
    L_004050c9:
        mov byte ptr [esi+1Bh],al
    L_004050cc:
        ret
    }
}
