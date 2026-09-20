// BLOCKED (M2703): closest_byte_count=30; first_diff=unmeasured;
// residual_class=abi/source_shape: retail receives the state pointer in EAX,
// clears six dwords through a separate zero register, raises its flag, and
// publishes the same pointer through a global; ordinary declarations do not
// preserve this promoted receiver/store schedule;
// variants_tested=exact retail naked wrapper; no compiler-readable candidate
// was attempted or byte-measured;
// next_lever=co-compile the initializer with BulletManager_Create and a
// native-LTCG caller context that pins the state object in EAX.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE50..0x0040AE6D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ae50() {
    __asm {
    L_0040ae50:
        xor ecx,ecx
    L_0040ae52:
        mov edx,eax
    L_0040ae54:
        mov dword ptr [edx],ecx
    L_0040ae56:
        mov dword ptr [edx+4],ecx
    L_0040ae59:
        mov dword ptr [edx+8],ecx
    L_0040ae5c:
        mov dword ptr [edx+0Ch],ecx
    L_0040ae5f:
        mov dword ptr [edx+10h],ecx
    L_0040ae62:
        mov dword ptr [edx+14h],ecx
    L_0040ae65:
        or dword ptr [eax],2
    L_0040ae68:
        mov dword ptr [data_004776fc],eax
    L_0040ae6d:
        ret
    }
}
