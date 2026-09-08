#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461695..0x00461743: ___crtGetLocaleInfoA
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtGetLocaleInfoA_00461695() {
    __asm {
    L_00461695:
        push 18h
    L_00461697:
        push 46C990h
    L_0046169c:
        call asm_SEH_prolog_00454bbc
    L_004616a1:
        xor esi,esi
    L_004616a3:
        cmp dword ptr [data_004776d0],esi
    L_004616a9:
        jne short L_004616d9
    L_004616ab:
        push esi
    L_004616ac:
        push esi
    L_004616ad:
        xor edi,edi
    L_004616af:
        inc edi
    L_004616b0:
        push edi
    L_004616b1:
        push esi
    L_004616b2:
        call dword ptr [data_004661c8]
    L_004616b8:
        test eax,eax
    L_004616ba:
        je short L_004616c4
    L_004616bc:
        mov dword ptr [data_004776d0],edi
    L_004616c2:
        jmp short L_004616d9
    L_004616c4:
        call dword ptr [data_0046610c]
    L_004616ca:
        cmp eax,78h
    L_004616cd:
        jne short L_004616d9
    L_004616cf:
        mov dword ptr [data_004776d0],2
    L_004616d9:
        mov eax,dword ptr [data_004776d0]
    L_004616de:
        cmp eax,2
    L_004616e1:
        je asm_target_004617ba
    L_004616e7:
        cmp eax,esi
    L_004616e9:
        je asm_target_004617ba
    L_004616ef:
        cmp eax,1
    L_004616f2:
        jne short L_0046171e
    L_004616f4:
        mov dword ptr [ebp-1Ch],esi
    L_004616f7:
        mov dword ptr [ebp-20h],esi
    L_004616fa:
        cmp dword ptr [ebp+18h],esi
    L_004616fd:
        jne short L_00461707
    L_004616ff:
        mov eax,dword ptr [data_00477664]
    L_00461704:
        mov dword ptr [ebp+18h],eax
    L_00461707:
        push esi
    L_00461708:
        push esi
    L_00461709:
        push dword ptr [ebp+0Ch]
    L_0046170c:
        push dword ptr [ebp+8]
    L_0046170f:
        call dword ptr [data_004661c8]
    L_00461715:
        mov ebx,eax
    L_00461717:
        mov dword ptr [ebp-24h],ebx
    L_0046171a:
        cmp ebx,esi
    L_0046171c:
        jne short L_00461725
    L_0046171e:
        xor eax,eax
    L_00461720:
        jmp asm_target_004617cc
    L_00461725:
        mov dword ptr [ebp-4],esi
    L_00461728:
        lea eax,[ebx+ebx]
    L_0046172b:
        add eax,3
    L_0046172e:
        and eax,0FFFFFFFCh
    L_00461731:
        call asm_chkstk_00458ec0
    L_00461736:
        mov dword ptr [ebp-18h],esp
    L_00461739:
        mov edi,esp
    L_0046173b:
        mov dword ptr [ebp-28h],edi
    L_0046173e:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461742:
        TH10_REL8(0xeb, 0x00461742, VA_asm_crtGetLocaleInfoA_part_0046175b)
    }
}

// 0x0046175B..0x004617D4: ___crtGetLocaleInfoA
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_crtGetLocaleInfoA_part_0046175b() {
    __asm {
    L_0046175b:
        cmp edi,esi
    L_0046175d:
        jne short L_00461776
    L_0046175f:
        lea eax,[ebx+ebx]
    L_00461762:
        push eax
    L_00461763:
        call asm_malloc_00452706
    L_00461768:
        pop ecx
    L_00461769:
        mov edi,eax
    L_0046176b:
        cmp edi,esi
    L_0046176d:
        TH10_REL8(0x74, 0x0046176d, VA_asm_target_0046171e)
    L_0046176f:
        mov dword ptr [ebp-20h],1
    L_00461776:
        push ebx
    L_00461777:
        push edi
    L_00461778:
        push dword ptr [ebp+0Ch]
    L_0046177b:
        push dword ptr [ebp+8]
    L_0046177e:
        call dword ptr [data_004661c8]
    L_00461784:
        test eax,eax
    L_00461786:
        je short L_004617a9
    L_00461788:
        push esi
    L_00461789:
        push esi
    L_0046178a:
        cmp dword ptr [ebp+14h],esi
    L_0046178d:
        jne short L_00461793
    L_0046178f:
        push esi
    L_00461790:
        push esi
    L_00461791:
        jmp short L_00461799
    L_00461793:
        push dword ptr [ebp+14h]
    L_00461796:
        push dword ptr [ebp+10h]
    L_00461799:
        push 0FFFFFFFFh
    L_0046179b:
        push edi
    L_0046179c:
        push esi
    L_0046179d:
        push dword ptr [ebp+18h]
    L_004617a0:
        call dword ptr [data_00466154]
    L_004617a6:
        mov dword ptr [ebp-1Ch],eax
    L_004617a9:
        cmp dword ptr [ebp-20h],esi
    L_004617ac:
        je short L_004617b5
    L_004617ae:
        push edi
    L_004617af:
        call asm_free_00452422
    L_004617b4:
        pop ecx
    L_004617b5:
        mov eax,dword ptr [ebp-1Ch]
    L_004617b8:
        jmp short L_004617cc
    L_004617ba:
        push dword ptr [ebp+14h]
    L_004617bd:
        push dword ptr [ebp+10h]
    L_004617c0:
        push dword ptr [ebp+0Ch]
    L_004617c3:
        push dword ptr [ebp+8]
    L_004617c6:
        call dword ptr [data_0046605c]
    L_004617cc:
        lea esp,[ebp-34h]
    L_004617cf:
        call asm_SEH_epilog_00454bf7
    L_004617d4:
        ret
    }
}
