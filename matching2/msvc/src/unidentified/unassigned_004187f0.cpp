// BLOCKED (M2704): closest_byte_count=2; first_diff=0x004187F0;
// residual_class=register-allocation/evaluation-order: Ghidra reports no
// retail xrefs or containing function for this unassigned fragment.  The
// return-by-value native-LTCG candidate did produce a 29-byte body, but
// scheduled pooled constants first and selected the wrong x87 source/store
// order; retail requires source ECX and destination EAX for both stores.
// variants_tested=member mutator with synthetic array caller, member
// return-by-value candidate, pooled-literal and external-data forms; exact
// naked wrapper baseline remains 29/29.
// next_lever=use a real retail caller/anchor (currently absent from Ghidra
// xrefs) that forces the private destination-EAX/source-ECX tuple, then retry
// the return-by-value source with the retail constant aliases.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004187F0..0x0041880C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004187f0() {
    __asm {
    L_004187f0:
        fld dword ptr [ecx]
    L_004187f2:
        fadd dword ptr [data_00470b4c]
    L_004187f8:
        fstp dword ptr [eax]
    L_004187fa:
        fld dword ptr [ecx+4]
    L_004187fd:
        fadd dword ptr [data_00470b48]
    L_00418803:
        fstp dword ptr [eax+4]
    L_00418806:
        mov ecx,dword ptr [ecx+8]
    L_00418809:
        mov dword ptr [eax+8],ecx
    L_0041880c:
        ret
    }
}
