// BLOCKED (M2703): closest_byte_count=33; first_diff=unmeasured;
// residual_class=abi: the fragment enters with its object in ESI, performs
// an indirect import call, and has two retail RET sites; a standalone
// __cdecl/__thiscall declaration cannot preserve that private receiver.
// variants_tested=exact retail naked wrapper; no compiler-readable candidate
// was attempted or byte-measured;

// next_lever=co-compile this body with its real caller in a native-LTCG
// cluster that exposes the ESI receiver and indirect import binding.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DEE0..0x0044DF00: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044dee0() {
    __asm {
    L_0044dee0:
        cmp dword ptr [esi+78h],1
    L_0044dee4:
        jne short L_0044defd
    L_0044dee6:
        mov eax,dword ptr [esi+8Ch]
    L_0044deec:
        push eax
    L_0044deed:
        call dword ptr [data_004660cc]
    L_0044def3:
        mov dword ptr [esi+8Ch],0FFFFFFFFh
    L_0044defd:
        xor eax,eax
    L_0044deff:
        ret
    L_0044df00:
        ret
    }
}
