#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402700..0x00402711: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402700() {
    __asm {
    L_00402700:
        test esi,esi
    L_00402702:
        je short L_00402711
    L_00402704:
        push esi
    L_00402705:
        call asm_DestroyGameState_00402440
    L_0040270a:
        push esi
    L_0040270b:
        call asm_free_004524a1
    L_00402710:
        pop ecx
    L_00402711:
        ret
    }
}
