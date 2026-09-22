// BLOCKED (H3201): closest_byte_count=6/16; first_diff=0x0041AC81
// (standalone readable Pair{int,int} factory, MSVC 13.10 /O2 /Gz, emitted
// 20 bytes and compared 6 equal bytes before the hidden-result ABI shift).
// Live Ghidra reads 8b4c2404 8b542408 8908 895004 c20800 at 0x0041AC80,
// with no function or xrefs registered; IDA confirms result in EAX, two stack
// arguments, and stores at result[0..1].  A native /GL /LTCG Pair constructor
// context promoted both values to ECX/EDX and emitted a 7-byte EAX-result
// plain-RET body, so it does not reproduce retail RET 8.
// residual_class=private EAX result plus stack-argument ABI; readable UDT
// return uses a hidden stack result and cannot name the retail convention.
// variants_tested=exact retail naked wrapper; readable POD/UDT factory;
// readable Pair constructor; native-LTCG Pair constructor/member contexts.
// All nonexact source experiments were restored.
// next_lever=promote this region from asm to semantic and add a native-LTCG
// constructor cluster/context with an explicit retail symbol/address; that
// requires a manifest region-kind/symbol change outside this claim.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AC80..0x0041AC8F: FUN_0041ac80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ac80_0041ac80() {
    __asm {
    L_0041ac80:
        mov ecx,dword ptr [esp+4]
    L_0041ac84:
        mov edx,dword ptr [esp+8]
    L_0041ac88:
        mov dword ptr [eax],ecx
    L_0041ac8a:
        mov dword ptr [eax+4],edx
    L_0041ac8d:
        ret 8
    }
}
