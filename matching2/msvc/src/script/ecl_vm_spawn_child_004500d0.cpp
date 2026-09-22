#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D2102): readable semantic source remains nonexact.  The current
// retail wrapper is exact (142/142 bytes in the linked baseline).  Ghidra
// confirms the private ABI: parent EDI, child VM in ESI after allocation,
// 0x1024 VM plus 0xC intrusive node, parent mask at +0x101C, and StartChild
// called at 0x00450154 with EAX child and EDI parent.
// native-LTCG probe: SpawnChild semantic candidate was 147 bytes (retail 142)
// and retained ECX thiscall plus ESI/EDI saves; adding a synthetic caller did
// not select the retail EDI convention.  Retain the exact wrapper; do not
// claim a readable match.
// residual_class=private-register ABI; residual_bytes=142 source bytes;
// variants_tested=direct C++ layout, native-LTCG child/start pair, and a
// caller-root probe; no readable candidate matched.
// next_lever=co-compile the actual 0x0044E1A0 dispatcher (which supplies EDI)
// with this child pair, then remeasure before changing this exact wrapper.
// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x004500D0..0x0045015D: EclVm_SpawnChild
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EclVm_SpawnChild_004500d0() {
    __asm {
    L_004500d0:
        push ebx
    L_004500d1:
        push esi
    L_004500d2:
        push 1024h
    L_004500d7:
        call asm_operator_new_00452493
    L_004500dc:
        xor ebx,ebx
    L_004500de:
        add esp,4
    L_004500e1:
        cmp eax,ebx
    L_004500e3:
        je short L_004500f5
    L_004500e5:
        mov dword ptr [eax+1008h],ebx
    L_004500eb:
        mov dword ptr [eax+100Ch],ebx
    L_004500f1:
        mov esi,eax
    L_004500f3:
        jmp short L_004500f7
    L_004500f5:
        xor esi,esi
    L_004500f7:
        push 0Ch
    L_004500f9:
        call asm_operator_new_00452493
    L_004500fe:
        mov ecx,dword ptr [esp+10h]
    L_00450102:
        mov dword ptr [esi+1010h],ecx
    L_00450108:
        mov dword ptr [esi+1014h],edi
    L_0045010e:
        mov dword ptr [esi],ebx
    L_00450110:
        mov dword ptr [esi+4],ebx
    L_00450113:
        mov edx,dword ptr [edi+4]
    L_00450116:
        mov cl,byte ptr [edx+101Ch]
    L_0045011c:
        mov byte ptr [esi+101Ch],cl
    L_00450122:
        lea ecx,[edi+1030h]
    L_00450128:
        mov dword ptr [eax],esi
    L_0045012a:
        mov dword ptr [eax+4],ebx
    L_0045012d:
        mov dword ptr [eax+8],ebx
    L_00450130:
        mov edx,dword ptr [ecx+4]
    L_00450133:
        add esp,4
    L_00450136:
        cmp edx,ebx
    L_00450138:
        je short L_00450143
    L_0045013a:
        mov dword ptr [eax+4],edx
    L_0045013d:
        mov edx,dword ptr [ecx+4]
    L_00450140:
        mov dword ptr [edx+8],eax
    L_00450143:
        mov dword ptr [ecx+4],eax
    L_00450146:
        mov dword ptr [eax+8],ecx
    L_00450149:
        mov eax,dword ptr [esp+10h]
    L_0045014d:
        mov ecx,dword ptr [edi+4]
    L_00450150:
        push eax
    L_00450151:
        push ecx
    L_00450152:
        mov eax,esi
    L_00450154:
        call asm_EclVm_StartChildRetail_0044df70
    L_00450159:
        pop esi
    L_0045015a:
        pop ebx
    L_0045015b:
        ret 8
    }
}
