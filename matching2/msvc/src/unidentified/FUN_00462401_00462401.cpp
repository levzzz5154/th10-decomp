#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462401..0x0046241C: FUN_00462401
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462401_00462401() {
    __asm {
    L_00462401:
        push esi
    L_00462402:
        mov esi,ecx
    L_00462404:
        call asm_FUN_0046241d_0046241d
    L_00462409:
        test byte ptr [esp+8],1
    L_0046240e:
        je short L_00462417
    L_00462410:
        push esi
    L_00462411:
        call asm_free_004524a1
    L_00462416:
        pop ecx
    L_00462417:
        mov eax,esi
    L_00462419:
        pop esi
    L_0046241a:
        ret 4
    }
}
