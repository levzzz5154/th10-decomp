#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463B02..0x00463B19: _ValidateExecute
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ValidateExecute_00463b02() {
    __asm {
    L_00463b02:
        push esi
    L_00463b03:
        push dword ptr [esp+8]
    L_00463b07:
        xor esi,esi
    L_00463b09:
        inc esi
    L_00463b0a:
        call dword ptr [data_00466184]
    L_00463b10:
        test eax,eax
    L_00463b12:
        je short L_00463b16
    L_00463b14:
        xor esi,esi
    L_00463b16:
        mov eax,esi
    L_00463b18:
        pop esi
    L_00463b19:
        ret
    }
}
