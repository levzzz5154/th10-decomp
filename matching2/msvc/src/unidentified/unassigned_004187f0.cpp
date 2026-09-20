// BLOCKED (M2703): closest_byte_count=29; first_diff=0x004187F1;
// residual_class=abi: four source shapes, including pooled literals, made
// the native pass place the source in EAX and destination in ECX, while
// retail requires source in ECX and destination in EAX for both x87 stores;
// variants_tested=4 source shapes including pooled-literal forms, plus the
// exact retail naked wrapper;
// next_lever=use a native-LTCG caller/anchor that assigns the private
// ECX-source/EAX-destination tuple, then remeasure this 29-byte leaf.

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
