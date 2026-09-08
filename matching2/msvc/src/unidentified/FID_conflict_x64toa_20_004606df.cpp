#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004606DF..0x0046074B: FID_conflict:@x64toa@20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict_x64toa_20_004606df() {
    __asm {
    L_004606df:
        push ebp
    L_004606e0:
        mov ebp,esp
    L_004606e2:
        push ecx
    L_004606e3:
        push ecx
    L_004606e4:
        push ebx
    L_004606e5:
        mov ebx,dword ptr [ebp+8]
    L_004606e8:
        push esi
    L_004606e9:
        xor ecx,ecx
    L_004606eb:
        cmp dword ptr [ebp+14h],ecx
    L_004606ee:
        mov esi,eax
    L_004606f0:
        mov eax,dword ptr [ebp+0Ch]
    L_004606f3:
        push edi
    L_004606f4:
        je short L_00460700
    L_004606f6:
        mov byte ptr [esi],2Dh
    L_004606f9:
        inc esi
    L_004606fa:
        neg ebx
    L_004606fc:
        adc eax,ecx
    L_004606fe:
        neg eax
    L_00460700:
        mov edi,esi
    L_00460702:
        mov dword ptr [ebp+0Ch],ecx
    L_00460705:
        push dword ptr [ebp+0Ch]
    L_00460708:
        push dword ptr [ebp+10h]
    L_0046070b:
        push eax
    L_0046070c:
        push ebx
    L_0046070d:
        call asm_aulldvrm_0045a1b0
    L_00460712:
        cmp ecx,9
    L_00460715:
        mov dword ptr [ebp-4],ebx
    L_00460718:
        mov ebx,eax
    L_0046071a:
        mov eax,edx
    L_0046071c:
        jbe short L_00460723
    L_0046071e:
        add cl,57h
    L_00460721:
        jmp short L_00460726
    L_00460723:
        add cl,30h
    L_00460726:
        mov byte ptr [esi],cl
    L_00460728:
        inc esi
    L_00460729:
        test eax,eax
    L_0046072b:
        ja short L_00460705
    L_0046072d:
        jb short L_00460733
    L_0046072f:
        test ebx,ebx
    L_00460731:
        ja short L_00460705
    L_00460733:
        mov byte ptr [esi],0
    L_00460736:
        dec esi
    L_00460737:
        mov cl,byte ptr [edi]
    L_00460739:
        mov al,byte ptr [esi]
    L_0046073b:
        mov byte ptr [esi],cl
    L_0046073d:
        dec esi
    L_0046073e:
        mov byte ptr [edi],al
    L_00460740:
        inc edi
    L_00460741:
        cmp edi,esi
    L_00460743:
        jb short L_00460737
    L_00460745:
        pop edi
    L_00460746:
        pop esi
    L_00460747:
        pop ebx
    L_00460748:
        leave
    L_00460749:
        ret 10h
    }
}
