#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004425A0..0x00442668: AnmManager_SyncEntityRenderStateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnmManager_SyncEntityRenderStateRetail_004425a0() {
    __asm {
    L_004425a0:
        push esi
    L_004425a1:
        mov esi,eax
    L_004425a3:
        mov eax,dword ptr [edi+35Ch]
    L_004425a9:
        mov cl,byte ptr [esi+3ADA68h]
    L_004425af:
        shr eax,4
    L_004425b2:
        and eax,3
    L_004425b5:
        cmp cl,al
    L_004425b7:
        je short L_00442600
    L_004425b9:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004425be:
        mov eax,dword ptr [edi+35Ch]
    L_004425c4:
        shr eax,4
    L_004425c7:
        and al,3
    L_004425c9:
        mov byte ptr [esi+3ADA68h],al
    L_004425cf:
        movzx eax,al
    L_004425d2:
        sub eax,0
    L_004425d5:
        je short L_004425ee
    L_004425d7:
        dec eax
    L_004425d8:
        jne short L_00442600
    L_004425da:
        mov eax,dword ptr [data_00491c30]
    L_004425df:
        mov ecx,dword ptr [eax]
    L_004425e1:
        push 2
    L_004425e3:
        push 14h
    L_004425e5:
        push eax
    L_004425e6:
        call dword ptr [ecx+0E4h]
    L_004425ec:
        jmp short L_00442600
    L_004425ee:
        mov eax,dword ptr [data_00491c30]
    L_004425f3:
        mov edx,dword ptr [eax]
    L_004425f5:
        push 6
    L_004425f7:
        push 14h
    L_004425f9:
        push eax
    L_004425fa:
        call dword ptr [edx+0E4h]
    L_00442600:
        mov eax,dword ptr [edi+35Ch]
    L_00442606:
        mov cl,byte ptr [esi+3ADA6Eh]
    L_0044260c:
        shr eax,1Fh
    L_0044260f:
        cmp cl,al
    L_00442611:
        je short L_00442664
    L_00442613:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00442618:
        mov eax,dword ptr [edi+35Ch]
    L_0044261e:
        shr eax,1Fh
    L_00442621:
        and al,1
    L_00442623:
        mov byte ptr [esi+3ADA6Eh],al
    L_00442629:
        mov eax,dword ptr [data_00491c30]
    L_0044262e:
        mov ecx,dword ptr [eax]
    L_00442630:
        jne short L_00442643
    L_00442632:
        push 2
    L_00442634:
        push 5
    L_00442636:
        push 0
    L_00442638:
        push eax
    L_00442639:
        call dword ptr [ecx+114h]
    L_0044263f:
        push 2
    L_00442641:
        jmp short L_00442652
    L_00442643:
        push 1
    L_00442645:
        push 5
    L_00442647:
        push 0
    L_00442649:
        push eax
    L_0044264a:
        call dword ptr [ecx+114h]
    L_00442650:
        push 1
    L_00442652:
        mov eax,dword ptr [data_00491c30]
    L_00442657:
        mov edx,dword ptr [eax]
    L_00442659:
        push 6
    L_0044265b:
        push 0
    L_0044265d:
        push eax
    L_0044265e:
        call dword ptr [edx+114h]
    L_00442664:
        inc dword ptr [esi+54h]
    L_00442667:
        pop esi
    L_00442668:
        ret
    }
}
