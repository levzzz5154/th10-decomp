// BLOCKED (M2703): closest_byte_count=24; first_diff=unmeasured;
// residual_class=abi/source_shape: the fragment enters with its record in
// ESI, passes an EDX-derived configuration destination, preserves EDI around
// the call, then performs a 25-dword clear and returns the ESI record;
// this private multi-register schedule is not expressible by a standalone
// ordinary declaration;
// variants_tested=exact retail naked wrapper; no compiler-readable candidate
// was attempted or byte-measured;
// next_lever=co-compile the initializer with its 0x0042A9E0 predecessor and
// a native-LTCG caller context that exposes ESI/EDX ownership.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A9F0..0x0042AA07: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042a9f0() {
    __asm {
    L_0042a9f0:
        push edi
    L_0042a9f1:
        lea edx,[esi+14h]
    L_0042a9f4:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_0042a9f9:
        xor eax,eax
    L_0042a9fb:
        mov ecx,19h
    L_0042aa00:
        mov edi,esi
    L_0042aa02:
        rep stosd
    L_0042aa04:
        mov eax,esi
    L_0042aa06:
        pop edi
    L_0042aa07:
        ret
    }
}
