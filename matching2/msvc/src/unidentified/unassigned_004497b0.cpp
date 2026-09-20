#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004497B0..0x004497CE: unassigned code fragment
// BLOCKED (M2702): closest_byte_count=31; first_diff=unmeasured;
// residual_class=abi: retail walks a list with the cursor in EAX and the
// sought script id in ECX; a normal member/free declaration cannot preserve
// that two-register entry while retaining the observed loop register order.
// variants_tested=exact retail overlay only; no readable candidate was measured;
// next_lever=compile a dedicated native-LTCG two-register list-walk context
// anchored to the neighboring AnimationManager child-lookup family.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004497b0() {
    __asm {
    L_004497b0:
        add eax,10h
    L_004497b3:
        je short L_004497c9
    L_004497b5:
        mov edx,dword ptr [eax]
    L_004497b7:
        movsx edx,word ptr [edx+38Ah]
    L_004497be:
        cmp edx,ecx
    L_004497c0:
        je short L_004497cc
    L_004497c2:
        mov eax,dword ptr [eax+4]
    L_004497c5:
        test eax,eax
    L_004497c7:
        jne short L_004497b5
    L_004497c9:
        xor eax,eax
    L_004497cb:
        ret
    L_004497cc:
        mov eax,dword ptr [eax]
    L_004497ce:
        ret
    }
}
