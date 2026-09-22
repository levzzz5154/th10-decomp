// BLOCKED (H3201): closest_byte_count=6/17; first_diff=0x0040C961
// (standalone readable State{pad[0x34], first, second} factory, MSVC 13.10
// /O2 /Gz, emitted 21 bytes and compared 6 equal bytes before the ABI shift).
// Live Ghidra reads 8b4c2404 8b542408 894834 895038 c20800 at 0x0040C960,
// with no function or xrefs registered; IDA confirms result in EAX, two stack
// arguments, and stores at +0x34/+0x38.  A native /GL /LTCG constructor
// context instead promoted both values to ECX/EDX and emitted a 7-byte
// EAX-result/plain-RET body, not the retail stack-cleaning ABI.
// residual_class=private EAX result plus stack-argument ABI; readable UDT
// return uses a hidden stack result and cannot name the retail convention.
// variants_tested=exact retail naked wrapper; readable POD/UDT factory;
// readable State constructor; native-LTCG State constructor context.  All
// nonexact source experiments were restored.
// next_lever=promote this region from asm to semantic and add a native-LTCG
// constructor cluster/context with an explicit retail symbol/address; that
// requires a manifest region-kind/symbol change outside this claim.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C960..0x0040C970: FUN_0040c960
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c960_0040c960() {
    __asm {
    L_0040c960:
        mov ecx,dword ptr [esp+4]
    L_0040c964:
        mov edx,dword ptr [esp+8]
    L_0040c968:
        mov dword ptr [eax+34h],ecx
    L_0040c96b:
        mov dword ptr [eax+38h],edx
    L_0040c96e:
        ret 8
    }
}
