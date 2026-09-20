#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A70..0x00449A8F: unassigned code fragment
// BLOCKED (M2702): closest_byte_count=32; first_diff=unmeasured;
// residual_class=abi/source_shape: the retail fragment receives its list
// object in EAX and its child pointer in ECX, then resets flagged fields;
// ordinary declarations cannot express both live-ins at this split, and the
// paired 0x00449A50/0x00449A70 fragments need separate retail symbols.
// variants_tested=exact retail overlay only; no readable candidate was measured;
// next_lever=compile the paired list-reset methods in one native-LTCG cluster
// with separate A50 and A70 entry contexts.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449a70() {
    __asm {
    L_00449a70:
        mov edx,dword ptr [eax+4]
    L_00449a73:
        mov dword ptr [eax+8],ecx
    L_00449a76:
        xor ecx,ecx
    L_00449a78:
        mov dword ptr [eax+0Ch],ecx
    L_00449a7b:
        mov dword ptr [eax+10h],ecx
    L_00449a7e:
        mov dword ptr [eax],ecx
    L_00449a80:
        and edx,0FFFFFFFEh
    L_00449a83:
        mov dword ptr [eax+4],edx
    L_00449a86:
        mov dword ptr [eax+14h],eax
    L_00449a89:
        mov dword ptr [eax+18h],ecx
    L_00449a8c:
        mov dword ptr [eax+1Ch],ecx
    L_00449a8f:
        ret
    }
}
