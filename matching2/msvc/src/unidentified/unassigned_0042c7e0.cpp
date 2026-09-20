#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C7E0..0x0042C7F9: unassigned code fragment
// BLOCKED (M2702): closest_byte_count=26; first_diff=unmeasured;
// residual_class=abi: retail receives the table object in EAX and the slot
// index in ECX, then forwards the indexed handle through AnimationManager_Find;
// no ordinary declaration preserves this two-register entry and call setup.
// variants_tested=exact retail overlay only; no readable candidate was measured;
// next_lever=compile a dedicated native-LTCG EAX/ECX accessor context anchored
// to the neighboring 0x0042C7C0 animation-slot helper.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c7e0() {
    __asm {
    L_0042c7e0:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c7e7:
        push edx
    L_0042c7e8:
        mov edx,dword ptr [data_00491c10]
    L_0042c7ee:
        call asm_AnimationManager_Find_004491c0
    L_0042c7f3:
        neg eax
    L_0042c7f5:
        sbb eax,eax
    L_0042c7f7:
        neg eax
    L_0042c7f9:
        ret
    }
}
