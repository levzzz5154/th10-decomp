#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463AE6..0x00463B01: _ValidateWrite
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ValidateWrite_00463ae6() {
    __asm {
    L_00463ae6:
        push esi
    L_00463ae7:
        push dword ptr [esp+0Ch]
    L_00463aeb:
        xor esi,esi
    L_00463aed:
        push dword ptr [esp+0Ch]
    L_00463af1:
        inc esi
    L_00463af2:
        call dword ptr [data_00466174]
    L_00463af8:
        test eax,eax
    L_00463afa:
        je short L_00463afe
    L_00463afc:
        xor esi,esi
    L_00463afe:
        mov eax,esi
    L_00463b00:
        pop esi
    L_00463b01:
        ret
    }
}
