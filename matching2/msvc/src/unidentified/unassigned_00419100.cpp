#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00419100..0x00419111: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00419100() {
    __asm {
    L_00419100:
        test esi,esi
    L_00419102:
        je short L_00419111
    L_00419104:
        push esi
    L_00419105:
        call asm_FUN_00418ee0_00418ee0
    L_0041910a:
        push esi
    L_0041910b:
        call asm_free_004524a1
    L_00419110:
        pop ecx
    L_00419111:
        ret
    }
}
