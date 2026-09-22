// BLOCKED (M2701): closest_byte_count=1; first_diff=0x00422201;
// residual_class=private ABI: retail receives the owner object in EAX and
// uses EAX as the second-node cursor before the final flag store.
// variants_tested=extern-C cdecl readable owner/node structs (30-byte extent,
// first diff at byte 1); no compiler-readable standalone declaration can
// preserve the EAX receiver while retaining the fixed _asm symbol. MSVC 13.10
// project flags were used.
// next_lever=native-LTCG context that pins the owner in EAX and exposes the
// fixed-address symbol through a migrated semantic manifest entry.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422200..0x0042221B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00422200() {
    __asm {
    L_00422200:
        mov ecx,dword ptr [eax+8]
    L_00422203:
        test ecx,ecx
    L_00422205:
        mov edx,2
    L_0042220a:
        je short L_0042220f
    L_0042220c:
        or dword ptr [ecx+4],edx
    L_0042220f:
        mov ecx,dword ptr [eax+0Ch]
    L_00422212:
        test ecx,ecx
    L_00422214:
        je short L_0042221B
    L_00422216:
        mov eax,ecx
    L_00422218:
        or dword ptr [eax+4],edx
    L_0042221B:
        ret
    }
}
