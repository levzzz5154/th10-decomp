#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D2702): closest_byte_count=30; first_diff=unmeasured;
// residual_class=toolkit; this __thiscall leaf is the canonical x87 FSINCOS
// sequence: ECX supplies the destination, the angle and magnitude remain in
// the caller's stack slots, and RET 8 owns both scalar arguments.  Readable
// sin/cos expressions do not force MSVC 7.1 to emit one FSINCOS instruction.
// variants_tested=the existing Score_SetPolarVector implementation, direct
// Vector2 SetPolar source spellings, and the exact retail overlay; no
// compiler-readable FSINCOS candidate was byte-measured.
// next_lever=provide a compiler/toolkit intrinsic or inline-code mechanism
// that emits FSINCOS while retaining this __thiscall/RET-8 ABI.
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
