// BLOCKED (M2704): closest_byte_count=0; first_diff=0x0042A9F0;
// residual_class=private-ABI/control-flow: Ghidra identifies the real callee
// at 0x00418C40 as __fastcall (destination in EDX), while this fragment
// enters with the record in ESI, preserves EDI, clears 25 dwords, and returns
// ESI.  The native-LTCG readable member candidate emitted a 95-byte body,
// retaining a public thiscall shape and a cdecl call, rather than this
// private multi-register schedule.
// variants_tested=readable member with loop clear and native caller context;
// __fastcall callee link binding and cdecl callee binding; exact retail naked
// wrapper retained as baseline.
// next_lever=co-compile a real caller that supplies ESI/EDX and a declared
// private callee edge, then revisit the loop/return source shape.
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
