#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449510..0x00449528: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2701): closest_byte_count=25/25; first_diff=unmeasured;
// residual_class=structural/abi: this is a loop tail entered by the jump from
// 0x004494D0 with EAX and EDX live, not an independently callable C++ body.
// variants_tested=member list-walk model and exact retail wrapper; splitting
// the tail from its predecessor loses the incoming register/state contract.
// next_lever=re-carve and recover the coupled 0x004494D0/0x00449510 region
// (or provide a native-LTCG fragment anchor preserving EAX/EDX).
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449510() {
    __asm {
    L_00449510:
        mov ecx,dword ptr [eax]
    L_00449512:
        and dword ptr [ecx+35Ch],0FFFFFFFDh
    L_00449519:
        mov ecx,dword ptr [eax]
    L_0044951b:
        or dword ptr [ecx+35Ch],edx
    L_00449521:
        mov eax,dword ptr [eax+4]
    L_00449524:
        test eax,eax
    L_00449526:
        jne short L_00449510
    L_00449528:
        ret
    }
}
