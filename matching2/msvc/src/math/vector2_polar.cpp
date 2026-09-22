#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D2701): closest_byte_count=30; first_diff=0x0044C5D0;
// residual_class=toolkit; a readable MSVC 13.10 `/O2 /Gz /MT /Gy /G6 /GF /GS /Zl`
// candidate using direct cos(angle) and sin(angle) expressions emitted 30
// bytes but differed in 28 bytes because it emitted separate FCOS/FSIN
// operations instead of the retail FSINCOS sequence.  The private ABI is
// __thiscall (destination in ECX), two scalar arguments on the stack, RET 8.
// variants_tested=direct readable cos/sin candidate (30 bytes, first diff at
// the entry); exact naked FSINCOS overlay remains the only exact body.
// next_lever=compiler/toolkit mechanism emitting one readable FSINCOS
// operation while retaining this __thiscall/RET-8 ABI; inline assembly is not
// an allowed readable proposal.
// 0x0044C5D0..0x0044C5ED: Recovery_PolarToVectorRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_PolarToVectorRetail_0044c5d0() {
    __asm {
    L_0044c5d0:
        push ecx
    L_0044c5d1:
        mov dword ptr [esp],ecx
    L_0044c5d4:
        mov eax,dword ptr [esp]
    L_0044c5d7:
        fld dword ptr [esp+8]
    L_0044c5db:
        fsincos
    L_0044c5dd:
        fmul dword ptr [esp+0Ch]
    L_0044c5e1:
        fstp dword ptr [eax]
    L_0044c5e3:
        fmul dword ptr [esp+0Ch]
    L_0044c5e7:
        fstp dword ptr [eax+4]
    L_0044c5ea:
        pop ecx
    L_0044c5eb:
        ret 8
    }
}
