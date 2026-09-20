// BLOCKED (D2701): closest_byte_count=41/41; first_diff=0x004506D7;
// residual_class=instruction-encoding: the native-LTCG EAX-entry model has
// the exact 41-byte extent and all state/control-flow bytes, but MSVC emits
// `sub ecx,4` (`83 E9 04`) where retail uses `add ecx,-4` (`83 C1 FC`).
// variants_tested=exact retail wrapper and the measured EclVm_004506d0
// member model with signed/unsigned fields, x86 pointer arithmetic, `x - 4`,
// `x + -4`, `-4 + x`, explicit 0xFFFFFFFC constants, and signed/unsigned
// non-negative tests; all eleven readable spellings retained the same
// two-byte residual.
// next_lever=use a compiler/toolkit scheduling or encoding lever that emits
// the retail add-immediate-negative form while preserving the EAX-entry
// cluster and 41-byte extent; do not cosmetically retry equivalent source
// spellings.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x004506D0..0x004506F8: ?ECL_PopScratchValue@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_PopScratchValue_004506d0() {
    __asm {
    L_004506d0:
        mov ecx,dword ptr [eax+1000h]
    L_004506d6:
        add ecx,0FFFFFFFCh
    L_004506d9:
        mov edx,dword ptr [eax+1004h]
    L_004506df:
        js short L_004506f0
    L_004506e1:
        mov dword ptr [eax+1000h],ecx
    L_004506e7:
        mov ecx,dword ptr [ecx+eax]
    L_004506ea:
        mov dword ptr [eax+1004h],ecx
    L_004506f0:
        mov dword ptr [eax+1000h],edx
    L_004506f6:
        xor eax,eax
    L_004506f8:
        ret
    }
}
