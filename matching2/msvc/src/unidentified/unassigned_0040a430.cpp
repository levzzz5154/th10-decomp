#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A430..0x0040A441: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040a430() {
    __asm {
    L_0040a430:
        test esi,esi
    L_0040a432:
        je short L_0040a441
    L_0040a434:
        push esi
    L_0040a435:
        call asm_FUN_0040a1a0_0040a1a0
    L_0040a43a:
        push esi
    L_0040a43b:
        call asm_free_004524a1
    L_0040a440:
        pop ecx
    L_0040a441:
        ret
    }
}
