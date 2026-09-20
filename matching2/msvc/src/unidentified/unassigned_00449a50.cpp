#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A50..0x00449A6F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2701): closest_byte_count=32/32; first_diff=unmeasured;
// residual_class=structural/abi: retail contains a member-style nine-field
// reset at EAX, but the surrounding 0x00449A50 region also contains a second
// complete reset body at 0x00449A70 with a different register allocation.
// variants_tested=field-by-field Reset model and the exact retail wrapper;
// one manifest symbol cannot express both copies as one readable function.
// next_lever=re-carve at 0x00449A70 and bind the two independent receiver
// conventions in separate native-LTCG sections.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449a50() {
    __asm {
    L_00449a50:
        mov edx,dword ptr [eax+4]
    L_00449a53:
        xor ecx,ecx
    L_00449a55:
        mov dword ptr [eax+8],ecx
    L_00449a58:
        mov dword ptr [eax+0Ch],ecx
    L_00449a5b:
        mov dword ptr [eax+10h],ecx
    L_00449a5e:
        mov dword ptr [eax],ecx
    L_00449a60:
        and edx,0FFFFFFFEh
    L_00449a63:
        mov dword ptr [eax+4],edx
    L_00449a66:
        mov dword ptr [eax+14h],eax
    L_00449a69:
        mov dword ptr [eax+18h],ecx
    L_00449a6c:
        mov dword ptr [eax+1Ch],ecx
    L_00449a6f:
        ret
    }
}
