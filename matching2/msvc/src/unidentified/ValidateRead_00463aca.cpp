#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463ACA..0x00463AE5: _ValidateRead
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ValidateRead_00463aca() {
    __asm {
    L_00463aca:
        push esi
    L_00463acb:
        push dword ptr [esp+0Ch]
    L_00463acf:
        xor esi,esi
    L_00463ad1:
        push dword ptr [esp+0Ch]
    L_00463ad5:
        inc esi
    L_00463ad6:
        call dword ptr [data_004661d8]
    L_00463adc:
        test eax,eax
    L_00463ade:
        je short L_00463ae2
    L_00463ae0:
        xor esi,esi
    L_00463ae2:
        mov eax,esi
    L_00463ae4:
        pop esi
    L_00463ae5:
        ret
    }
}
