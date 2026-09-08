#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463260..0x0046330E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463260() {
    __asm {
    L_00463260:
        mov eax,dword ptr [ebp-14h]
    L_00463263:
        mov eax,dword ptr [eax]
    L_00463265:
        mov dword ptr [ebp-1Ch],eax
    L_00463268:
        mov eax,dword ptr [ebp-1Ch]
    L_0046326b:
        cmp dword ptr [eax],0E06D7363h
    L_00463271:
        jne short L_004632a4
    L_00463273:
        mov eax,dword ptr [ebp-1Ch]
    L_00463276:
        cmp dword ptr [eax+10h],3
    L_0046327a:
        jne short L_004632a4
    L_0046327c:
        mov eax,dword ptr [ebp-1Ch]
    L_0046327f:
        cmp dword ptr [eax+14h],19930520h
    L_00463286:
        je short L_00463294
    L_00463288:
        mov eax,dword ptr [ebp-1Ch]
    L_0046328b:
        cmp dword ptr [eax+14h],19930521h
    L_00463292:
        jne short L_004632a4
    L_00463294:
        mov eax,dword ptr [ebp-1Ch]
    L_00463297:
        cmp dword ptr [eax+1Ch],0
    L_0046329b:
        mov dword ptr [ebp-24h],1
    L_004632a2:
        je short L_004632ab
    L_004632a4:
        mov dword ptr [ebp-24h],0
    L_004632ab:
        mov eax,dword ptr [ebp-24h]
    L_004632ae:
        ret
    L_004632af:
        mov esp,dword ptr [ebp-18h]
    L_004632b2:
        mov ecx,dword ptr [ebp+14h]
    L_004632b5:
        mov eax,dword ptr [ecx+8]
    L_004632b8:
        mov dword ptr [ebp-30h],eax
    L_004632bb:
        mov edi,dword ptr [ebp+0Ch]
    L_004632be:
        mov eax,dword ptr [edi+8]
    L_004632c1:
        mov dword ptr [ebp-28h],eax
    L_004632c4:
        mov edx,dword ptr [ecx+10h]
    L_004632c7:
        mov dword ptr [ebp-2Ch],edx
    L_004632ca:
        xor edx,edx
    L_004632cc:
        mov dword ptr [ebp-34h],edx
    L_004632cf:
        cmp edx,dword ptr [ecx+0Ch]
    L_004632d2:
        jae short L_004632f8
    L_004632d4:
        lea esi,[edx+edx*4]
    L_004632d7:
        mov ebx,dword ptr [ebp-2Ch]
    L_004632da:
        lea esi,[ebx+esi*4]
    L_004632dd:
        mov ebx,dword ptr [esi+4]
    L_004632e0:
        cmp eax,ebx
    L_004632e2:
        TH10_REL8(0x7e, 0x004632e2, VA_asm_unassigned_00463321)
    L_004632e4:
        cmp eax,dword ptr [esi+8]
    L_004632e7:
        TH10_REL8(0x7f, 0x004632e7, VA_asm_unassigned_00463321)
    L_004632e9:
        lea eax,[ebx+1]
    L_004632ec:
        mov dword ptr [ebp-28h],eax
    L_004632ef:
        mov edx,dword ptr [ebp-30h]
    L_004632f2:
        mov eax,dword ptr [edx+eax*8]
    L_004632f5:
        mov dword ptr [ebp-28h],eax
    L_004632f8:
        push eax
    L_004632f9:
        push ecx
    L_004632fa:
        xor esi,esi
    L_004632fc:
        push esi
    L_004632fd:
        push edi
    L_004632fe:
        call asm_FrameUnwindToState_00462e7e
    L_00463303:
        add esp,10h
    L_00463306:
        mov dword ptr [ebp-20h],esi
    L_00463309:
        mov dword ptr [ebp-4],esi
    L_0046330c:
        mov esi,dword ptr [ebp+8]
    }
}
