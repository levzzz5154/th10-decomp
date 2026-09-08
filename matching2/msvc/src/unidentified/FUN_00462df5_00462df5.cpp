#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462DF5..0x00462E10: FUN_00462df5
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462df5_00462df5() {
    __asm {
    L_00462df5:
        push esi
    L_00462df6:
        mov esi,ecx
    L_00462df8:
        call asm_FUN_00462d77_00462d77
    L_00462dfd:
        test byte ptr [esp+8],1
    L_00462e02:
        je short L_00462e0b
    L_00462e04:
        push esi
    L_00462e05:
        call asm_free_004524a1
    L_00462e0a:
        pop ecx
    L_00462e0b:
        mov eax,esi
    L_00462e0d:
        pop esi
    L_00462e0e:
        ret 4
    }
}
