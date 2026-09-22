// BLOCKED (M2803): closest_byte_count=0/15; first_diff=0x00449770;
// residual_class=private ABI/fragment extent: the retail entry receives its
// linked-list cursor in ECX, preserves ESI, and jumps into the separately
// owned continuation at 0x00449780/0x00449794 without a normal function
// boundary.  Ghidra reports no function, callers, callees, xrefs, or PCode.
// variants_tested=exact retail naked wrapper and a readable linked-list model;
// the ordinary model used stack arguments and emitted 55 bytes rather than
// the claimed 15-byte continuation fragment.
// next_lever=native-LTCG cluster with a proven caller pinning ECX/ESI and
// co-compiled 0x00449780/0x00449794 continuation ownership; retain the exact
// wrapper in M2803.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449770..0x0044977E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449770() {
    __asm {
    L_00449770:
        add ecx,10h
    L_00449773:
        push esi
    L_00449774:
        TH10_REL8(0x74, 0x00449774, VA_asm_target_00449794)
    L_00449776:
        TH10_REL8(0xeb, 0x00449776, VA_asm_unassigned_00449780)
    L_00449778:
        lea esp,[esp+force_disp32_zero]
    }
}
