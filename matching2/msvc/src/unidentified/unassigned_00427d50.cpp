#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427D50..0x00427D67: unassigned code fragment
// BLOCKED (M2702): closest_byte_count=24; first_diff=unmeasured;
// residual_class=abi: retail receives output in EAX and the two source
// vectors in ECX/EDX, with ESI/EDI as callee-preserved temporaries; ordinary
// declarations cannot express this three-register helper entry.
// variants_tested=exact retail overlay only; no readable candidate was measured;
// next_lever=compile a dedicated native-LTCG three-register vector-difference
// context with an EAX output anchor.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427d50() {
    __asm {
    L_00427d50:
        push esi
    L_00427d51:
        push edi
    L_00427d52:
        mov edi,dword ptr [edx+4]
    L_00427d55:
        mov esi,ecx
    L_00427d57:
        mov ecx,dword ptr [esi+4]
    L_00427d5a:
        mov esi,dword ptr [esi]
    L_00427d5c:
        sub ecx,edi
    L_00427d5e:
        sub esi,dword ptr [edx]
    L_00427d60:
        pop edi
    L_00427d61:
        mov dword ptr [eax],esi
    L_00427d63:
        mov dword ptr [eax+4],ecx
    L_00427d66:
        pop esi
    L_00427d67:
        ret
    }
}
