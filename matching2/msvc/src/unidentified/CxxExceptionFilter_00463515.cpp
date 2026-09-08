#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463515..0x00463639: ___CxxExceptionFilter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CxxExceptionFilter_00463515() {
    __asm {
    L_00463515:
        push ebp
    L_00463516:
        mov ebp,esp
    L_00463518:
        sub esp,14h
    L_0046351b:
        mov eax,dword ptr [ebp+8]
    L_0046351e:
        push edi
    L_0046351f:
        xor edi,edi
    L_00463521:
        cmp eax,edi
    L_00463523:
        jne short L_0046352c
    L_00463525:
        xor eax,eax
    L_00463527:
        jmp asm_target_00463637
    L_0046352c:
        push ebx
    L_0046352d:
        mov ebx,dword ptr [eax]
    L_0046352f:
        push esi
    L_00463530:
        mov esi,dword ptr [ebp+0Ch]
    L_00463533:
        cmp esi,edi
    L_00463535:
        je asm_target_004635f4
    L_0046353b:
        cmp byte ptr [esi+8],0
    L_0046353f:
        je asm_target_004635f4
    L_00463545:
        cmp dword ptr [ebx],0E06D7363h
    L_0046354b:
        jne asm_target_00463622
    L_00463551:
        cmp dword ptr [ebx+10h],3
    L_00463555:
        jne asm_target_00463622
    L_0046355b:
        mov eax,dword ptr [ebx+14h]
    L_0046355e:
        cmp eax,19930520h
    L_00463563:
        je short L_00463570
    L_00463565:
        cmp eax,19930521h
    L_0046356a:
        jne asm_target_00463622
    L_00463570:
        cmp dword ptr [ebx+1Ch],edi
    L_00463573:
        jne short L_0046358b
    L_00463575:
        call asm_getptd_00456357
    L_0046357a:
        cmp dword ptr [eax+7Ch],edi
    L_0046357d:
        je asm_target_00463622
    L_00463583:
        call asm_getptd_00456357
    L_00463588:
        mov ebx,dword ptr [eax+7Ch]
    L_0046358b:
        mov eax,dword ptr [ebp+10h]
    L_0046358e:
        or eax,80000000h
    L_00463593:
        mov dword ptr [ebp-14h],eax
    L_00463596:
        mov eax,dword ptr [ebx+1Ch]
    L_00463599:
        mov eax,dword ptr [eax+0Ch]
    L_0046359c:
        lea ecx,[eax+4]
    L_0046359f:
        mov eax,dword ptr [eax]
    L_004635a1:
        cmp eax,edi
    L_004635a3:
        mov dword ptr [ebp-10h],esi
    L_004635a6:
        mov dword ptr [ebp+8],ecx
    L_004635a9:
        mov dword ptr [ebp-4],eax
    L_004635ac:
        jle short L_00463622
    L_004635ae:
        mov eax,dword ptr [ebp+8]
    L_004635b1:
        push dword ptr [ebx+1Ch]
    L_004635b4:
        mov edi,dword ptr [eax]
    L_004635b6:
        lea esi,[ebp-14h]
    L_004635b9:
        call asm_TypeMatch_00462e11
    L_004635be:
        test eax,eax
    L_004635c0:
        pop ecx
    L_004635c1:
        jne short L_004635d1
    L_004635c3:
        dec dword ptr [ebp-4]
    L_004635c6:
        add dword ptr [ebp+8],4
    L_004635ca:
        cmp dword ptr [ebp-4],eax
    L_004635cd:
        jg short L_004635ae
    L_004635cf:
        jmp short L_00463622
    L_004635d1:
        call asm_getptd_00456357
    L_004635d6:
        mov edx,dword ptr [ebp+14h]
    L_004635d9:
        add eax,84h
    L_004635de:
        inc dword ptr [eax]
    L_004635e0:
        test edx,edx
    L_004635e2:
        je short L_00463632
    L_004635e4:
        lea eax,[ebp-14h]
    L_004635e7:
        push eax
    L_004635e8:
        push ebx
    L_004635e9:
        mov ecx,edi
    L_004635eb:
        call asm_BuildCatchObject_00463399
    L_004635f0:
        pop ecx
    L_004635f1:
        pop ecx
    L_004635f2:
        jmp short L_00463632
    L_004635f4:
        cmp dword ptr [ebx],0E06D7363h
    L_004635fa:
        jne short L_00463626
    L_004635fc:
        cmp dword ptr [ebx+10h],3
    L_00463600:
        jne short L_00463626
    L_00463602:
        mov eax,dword ptr [ebx+14h]
    L_00463605:
        cmp eax,19930520h
    L_0046360a:
        je short L_00463613
    L_0046360c:
        cmp eax,19930521h
    L_00463611:
        jne short L_00463626
    L_00463613:
        cmp dword ptr [ebx+1Ch],edi
    L_00463616:
        jne short L_00463626
    L_00463618:
        call asm_getptd_00456357
    L_0046361d:
        cmp dword ptr [eax+7Ch],edi
    L_00463620:
        jne short L_00463626
    L_00463622:
        xor eax,eax
    L_00463624:
        jmp short L_00463635
    L_00463626:
        call asm_getptd_00456357
    L_0046362b:
        add eax,84h
    L_00463630:
        inc dword ptr [eax]
    L_00463632:
        xor eax,eax
    L_00463634:
        inc eax
    L_00463635:
        pop esi
    L_00463636:
        pop ebx
    L_00463637:
        pop edi
    L_00463638:
        leave
    L_00463639:
        ret
    }
}
