// BLOCKED (H2801): closest_byte_count=102; first_diff=unmeasured (no
// compiler-readable candidate reached the private entry symbol);
// residual_class=private_abi/source_shape: retail receives the owner in EAX,
// the three-component vector in EBX, and two remaining arguments on the
// stack (RET 8), then copies owner/vector fields and walks the linked record
// list through a virtual evaluator. Ghidra has no function at 0041C760;
// live boundaries are FUN_0041C680/FUN_0041C7D0, while the neighboring
// semantic ScoreRecords copy/evaluate at 0041C800 independently confirms
// this EAX/EBX private convention and the required polymorphic record type.
// variants_tested=exact retail naked wrapper; IDA linked-record
// reconstruction; ScoreRecords member shape patterned after the exact
// 0041C800 semantic cluster; and ordinary cdecl/fastcall declarations.
// The latter cannot name EAX/EBX simultaneously, and no readable candidate
// was byte-measured outside an LTCG cluster.
// next_lever=native-LTCG cluster with the real linked-record evaluator and a
// synthetic caller that pins EAX/EBX; this region is still kind=asm in
// regions.json, so retain the exact wrapper in H2801.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C760..0x0041C7C5: FUN_0041c760
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041c760_0041c760() {
    __asm {
    L_0041c760:
        mov ecx,dword ptr [eax+18h]
    L_0041c763:
        push ebp
    L_0041c764:
        push esi
    L_0041c765:
        mov esi,dword ptr [esp+0Ch]
    L_0041c769:
        mov ebp,dword ptr [esi]
    L_0041c76b:
        lea edx,[eax+440h]
    L_0041c771:
        mov dword ptr [edx],ebp
    L_0041c773:
        mov ebp,dword ptr [esi+4]
    L_0041c776:
        mov dword ptr [edx+4],ebp
    L_0041c779:
        mov esi,dword ptr [esi+8]
    L_0041c77c:
        mov dword ptr [edx+8],esi
    L_0041c77f:
        add eax,44Ch
    L_0041c784:
        mov edx,ebx
    L_0041c786:
        mov esi,dword ptr [edx]
    L_0041c788:
        mov dword ptr [eax],esi
    L_0041c78a:
        mov esi,dword ptr [edx+4]
    L_0041c78d:
        mov dword ptr [eax+4],esi
    L_0041c790:
        mov edx,dword ptr [edx+8]
    L_0041c793:
        push edi
    L_0041c794:
        xor edi,edi
    L_0041c796:
        test ecx,ecx
    L_0041c798:
        mov dword ptr [eax+8],edx
    L_0041c79b:
        je short L_0041c7be
    L_0041c79d:
        mov ebp,dword ptr [esp+14h]
    L_0041c7a1:
        cmp dword ptr [ecx+0Ch],1
    L_0041c7a5:
        mov esi,dword ptr [ecx+8]
    L_0041c7a8:
        je short L_0041c7b8
    L_0041c7aa:
        mov edx,dword ptr [esp+10h]
    L_0041c7ae:
        mov eax,dword ptr [ecx]
    L_0041c7b0:
        push ebp
    L_0041c7b1:
        push ebx
    L_0041c7b2:
        push edx
    L_0041c7b3:
        call dword ptr [eax+18h]
    L_0041c7b6:
        add edi,eax
    L_0041c7b8:
        test esi,esi
    L_0041c7ba:
        mov ecx,esi
    L_0041c7bc:
        jne short L_0041c7a1
    L_0041c7be:
        mov eax,edi
    L_0041c7c0:
        pop edi
    L_0041c7c1:
        pop esi
    L_0041c7c2:
        pop ebp
    L_0041c7c3:
        ret 8
    }
}
