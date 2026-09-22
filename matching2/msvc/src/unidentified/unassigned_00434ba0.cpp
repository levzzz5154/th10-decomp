#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434BA0..0x00434BB0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2801): closest_byte_count=0/17; first_diff=extent mismatch
// (readable member emitted 23 bytes); residual_class=private ABI/register
// allocation (retail consumes EAX live-in with ECX object); variants_tested=
// unsigned-int member update with temporary old value; next_lever=manifest-
// eligible native-LTCG ABI context or explicit promotion.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00434ba0() {
    __asm {
    L_00434ba0:
        mov edx,dword ptr [ecx+60h]
    L_00434ba3:
        shl eax,4
    L_00434ba6:
        xor eax,edx
    L_00434ba8:
        and eax,10h
    L_00434bab:
        xor edx,eax
    L_00434bad:
        mov dword ptr [ecx+60h],edx
    L_00434bb0:
        ret
    }
}
