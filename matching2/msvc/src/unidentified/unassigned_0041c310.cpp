#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C310..0x0041C321: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c310() {
    __asm {
    L_0041c310:
        test esi,esi
    L_0041c312:
        je short L_0041c321
    L_0041c314:
        push esi
    L_0041c315:
        call asm_ScoreExtendedObject_DestroyRetail_0041c1c0
    L_0041c31a:
        push esi
    L_0041c31b:
        call asm_free_004524a1
    L_0041c320:
        pop ecx
    L_0041c321:
        ret
    }
}
