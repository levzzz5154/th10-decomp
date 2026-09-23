// BLOCKED (H3201): closest_byte_count=6/16; first_diff=0x00412F71
// (standalone readable Pair{int,int} factory, MSVC 13.10 /O2 /Gz, emitted
// 20 bytes and compared 6 equal bytes before the hidden-result ABI shift).
// Live Ghidra reads 8b4c2404 8b542408 8908 895004 c20800 at 0x00412F70,
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
// Ghidra ABI/range audit: matching2/reference/recovery_notes/FUN_00412f70_abi.md

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412F70..0x00412F7F: FUN_00412f70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412f70_00412f70() {
    __asm {
    L_00412f70:
        mov ecx,dword ptr [esp+4]
    L_00412f74:
        mov edx,dword ptr [esp+8]
    L_00412f78:
        mov dword ptr [eax],ecx
    L_00412f7a:
        mov dword ptr [eax+4],edx
    L_00412f7d:
        ret 8
    }
}
