// BLOCKED (D2701): shared native-LTCG operand/value/pop scope retained the
// exact 41-byte extent and all state/control-flow bytes, but MSVC emits
// `sub ecx,4` (`83 E9 04`) where retail uses `add ecx,-4` (`83 C1 FC`).
// residual_class=instruction-encoding; Ghidra dataflow confirms EAX scratch
// VM, +0x1000 stack pointer, +0x1004 frame base, and the signed branch.
// variants_tested=member models with signed/unsigned fields, x86 pointer
// arithmetic, eleven equivalent decrement spellings, and shared caller
// scheduling with the two float resolvers; all retain the same residual.
// next_lever=use an actual 0044E1A0 caller/toolkit encoding lever; do not
// cosmetically retry equivalent source spellings.

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
