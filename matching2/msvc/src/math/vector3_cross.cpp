#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (H2901): Ghidra disassembles an exact 77-byte leaf span at
// 0x00421B90 with no incoming xrefs/callers and no callees.  Its ABI is the
// private triple-pointer form result=EAX, left=ECX, right=EDX; a standalone
// MSVC 13.10 C++ declaration cannot express that register placement (the
// ordinary __fastcall candidate makes ECX the result and shifts the inputs).
// variants_tested=retail private-ABI overlay only; standalone __fastcall ABI
// feasibility rejected before source mutation because it cannot supply EAX as
// an input result pointer. next_lever=an LTCG cluster with a real caller that
// preserves EAX/ECX/EDX simultaneously; Ghidra reports no such caller in the
// current retail image, so the exact readable replacement is blocked.
// closest_byte_count=77/77 (existing overlay); first_diff=N/A for overlay;
// residual_class=private-ABI register placement.
// 0x00421B90..0x00421BDC: Vector3_Cross
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Vector3_Cross_00421b90() {
    __asm {
    L_00421b90:
        sub esp,0Ch
    L_00421b93:
        fld dword ptr [ecx+8]
    L_00421b96:
        fmul dword ptr [edx+4]
    L_00421b99:
        fld dword ptr [edx+8]
    L_00421b9c:
        fmul dword ptr [ecx+4]
    L_00421b9f:
        fsubp st(1),st
    L_00421ba1:
        fstp dword ptr [esp]
    L_00421ba4:
        fld dword ptr [edx+8]
    L_00421ba7:
        fmul dword ptr [ecx]
    L_00421ba9:
        fld dword ptr [ecx+8]
    L_00421bac:
        fmul dword ptr [edx]
    L_00421bae:
        fsubp st(1),st
    L_00421bb0:
        fstp dword ptr [esp+4]
    L_00421bb4:
        fld dword ptr [edx]
    L_00421bb6:
        fmul dword ptr [ecx+4]
    L_00421bb9:
        fld dword ptr [ecx]
    L_00421bbb:
        mov ecx,eax
    L_00421bbd:
        fmul dword ptr [edx+4]
    L_00421bc0:
        mov edx,dword ptr [esp]
    L_00421bc3:
        mov dword ptr [ecx],edx
    L_00421bc5:
        mov edx,dword ptr [esp+4]
    L_00421bc9:
        fsubp st(1),st
    L_00421bcb:
        mov dword ptr [ecx+4],edx
    L_00421bce:
        fstp dword ptr [esp+8]
    L_00421bd2:
        mov edx,dword ptr [esp+8]
    L_00421bd6:
        mov dword ptr [ecx+8],edx
    L_00421bd9:
        add esp,0Ch
    L_00421bdc:
        ret
    }
}
