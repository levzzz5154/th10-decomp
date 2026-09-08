#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461565..0x0046161C: ___crtGetLocaleInfoW
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtGetLocaleInfoW_00461565() {
    __asm {
    L_00461565:
        push 18h
    L_00461567:
        push 46C980h
    L_0046156c:
        call asm_SEH_prolog_00454bbc
    L_00461571:
        xor edi,edi
    L_00461573:
        xor ebx,ebx
    L_00461575:
        inc ebx
    L_00461576:
        cmp dword ptr [data_004776cc],edi
    L_0046157c:
        jne short L_004615a9
    L_0046157e:
        push edi
    L_0046157f:
        push edi
    L_00461580:
        push ebx
    L_00461581:
        push edi
    L_00461582:
        call dword ptr [data_004661c8]
    L_00461588:
        test eax,eax
    L_0046158a:
        je short L_00461594
    L_0046158c:
        mov dword ptr [data_004776cc],ebx
    L_00461592:
        jmp short L_004615a9
    L_00461594:
        call dword ptr [data_0046610c]
    L_0046159a:
        cmp eax,78h
    L_0046159d:
        jne short L_004615a9
    L_0046159f:
        mov dword ptr [data_004776cc],2
    L_004615a9:
        mov eax,dword ptr [data_004776cc]
    L_004615ae:
        cmp eax,ebx
    L_004615b0:
        jne short L_004615c9
    L_004615b2:
        push dword ptr [ebp+14h]
    L_004615b5:
        push dword ptr [ebp+10h]
    L_004615b8:
        push dword ptr [ebp+0Ch]
    L_004615bb:
        push dword ptr [ebp+8]
    L_004615be:
        call dword ptr [data_004661c8]
    L_004615c4:
        jmp asm_target_0046168c
    L_004615c9:
        cmp eax,2
    L_004615cc:
        je short L_004615d2
    L_004615ce:
        cmp eax,edi
    L_004615d0:
        jne short L_004615fa
    L_004615d2:
        mov dword ptr [ebp-1Ch],edi
    L_004615d5:
        mov dword ptr [ebp-24h],edi
    L_004615d8:
        cmp dword ptr [ebp+18h],edi
    L_004615db:
        jne short L_004615e5
    L_004615dd:
        mov eax,dword ptr [data_00477664]
    L_004615e2:
        mov dword ptr [ebp+18h],eax
    L_004615e5:
        push edi
    L_004615e6:
        push edi
    L_004615e7:
        push dword ptr [ebp+0Ch]
    L_004615ea:
        push dword ptr [ebp+8]
    L_004615ed:
        call dword ptr [data_0046605c]
    L_004615f3:
        mov dword ptr [ebp-20h],eax
    L_004615f6:
        cmp eax,edi
    L_004615f8:
        jne short L_00461601
    L_004615fa:
        xor eax,eax
    L_004615fc:
        jmp asm_target_0046168c
    L_00461601:
        mov dword ptr [ebp-4],edi
    L_00461604:
        add eax,3
    L_00461607:
        and eax,0FFFFFFFCh
    L_0046160a:
        call asm_chkstk_00458ec0
    L_0046160f:
        mov dword ptr [ebp-18h],esp
    L_00461612:
        mov esi,esp
    L_00461614:
        mov dword ptr [ebp-28h],esi
    L_00461617:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0046161b:
        TH10_REL8(0xeb, 0x0046161b, VA_asm_crtGetLocaleInfoW_part_00461634)
    }
}

// 0x00461634..0x00461694: ___crtGetLocaleInfoW
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtGetLocaleInfoW_part_00461634() {
    __asm {
    L_00461634:
        cmp esi,edi
    L_00461636:
        jne short L_0046164a
    L_00461638:
        push dword ptr [ebp-20h]
    L_0046163b:
        call asm_malloc_00452706
    L_00461640:
        pop ecx
    L_00461641:
        mov esi,eax
    L_00461643:
        cmp esi,edi
    L_00461645:
        TH10_REL8(0x74, 0x00461645, VA_asm_target_004615fa)
    L_00461647:
        mov dword ptr [ebp-24h],ebx
    L_0046164a:
        push dword ptr [ebp-20h]
    L_0046164d:
        push esi
    L_0046164e:
        push dword ptr [ebp+0Ch]
    L_00461651:
        push dword ptr [ebp+8]
    L_00461654:
        call dword ptr [data_0046605c]
    L_0046165a:
        test eax,eax
    L_0046165c:
        je short L_0046167d
    L_0046165e:
        cmp dword ptr [ebp+14h],edi
    L_00461661:
        jne short L_00461667
    L_00461663:
        push edi
    L_00461664:
        push edi
    L_00461665:
        jmp short L_0046166d
    L_00461667:
        push dword ptr [ebp+14h]
    L_0046166a:
        push dword ptr [ebp+10h]
    L_0046166d:
        push 0FFFFFFFFh
    L_0046166f:
        push esi
    L_00461670:
        push ebx
    L_00461671:
        push dword ptr [ebp+18h]
    L_00461674:
        call dword ptr [data_00466104]
    L_0046167a:
        mov dword ptr [ebp-1Ch],eax
    L_0046167d:
        cmp dword ptr [ebp-24h],edi
    L_00461680:
        je short L_00461689
    L_00461682:
        push esi
    L_00461683:
        call asm_free_00452422
    L_00461688:
        pop ecx
    L_00461689:
        mov eax,dword ptr [ebp-1Ch]
    L_0046168c:
        lea esp,[ebp-34h]
    L_0046168f:
        call asm_SEH_epilog_00454bf7
    L_00461694:
        ret
    }
}
