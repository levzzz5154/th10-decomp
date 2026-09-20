#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AC90..0x0042ACAD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
// BLOCKED (M2701): closest_byte_count=30/30; first_diff=unmeasured;
// residual_class=abi/source_shape: the loop is a four-register fragment with
// EAX accumulator, ECX index, EDI byte scratch, and ESI base; it also contains
// retail's explicit eight-byte stack-alignment LEA/NOP.
// variants_tested=direct byte-sum loop and exact retail wrapper; no readable
// declaration can name all four live-ins or force the alignment filler.
// next_lever=native-LTCG context pinning EAX/ECX/EDI/ESI plus an exact
// supported padding mechanism; retain this exact wrapper meanwhile.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ac90() {
    __asm {
    L_0042ac90:
        add edx,0FFFFFFF8h
    L_0042ac93:
        xor eax,eax
    L_0042ac95:
        xor ecx,ecx
    L_0042ac97:
        test edx,edx
    L_0042ac99:
        jle short L_0042acad
    L_0042ac9b:
        push edi
    L_0042ac9c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0042aca0:
        movzx edi,byte ptr [ecx+esi+8]
    L_0042aca5:
        add eax,edi
    L_0042aca7:
        inc ecx
    L_0042aca8:
        cmp ecx,edx
    L_0042acaa:
        jl short L_0042aca0
    L_0042acac:
        pop edi
    L_0042acad:
        ret
    }
}
