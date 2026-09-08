#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462DD9..0x00462DF4: FUN_00462dd9
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462dd9_00462dd9() {
    __asm {
    L_00462dd9:
        push esi
    L_00462dda:
        mov esi,ecx
    L_00462ddc:
        call asm_FUN_00462d3c_00462d3c
    L_00462de1:
        test byte ptr [esp+8],1
    L_00462de6:
        je short L_00462def
    L_00462de8:
        push esi
    L_00462de9:
        call asm_free_004524a1
    L_00462dee:
        pop ecx
    L_00462def:
        mov eax,esi
    L_00462df1:
        pop esi
    L_00462df2:
        ret 4
    }
}
