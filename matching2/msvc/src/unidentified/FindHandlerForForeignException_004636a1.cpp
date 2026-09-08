#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004636A1..0x0046375E: FindHandlerForForeignException
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FindHandlerForForeignException_004636a1() {
    __asm {
    L_004636a1:
        push ebp
    L_004636a2:
        mov ebp,esp
    L_004636a4:
        push ecx
    L_004636a5:
        push ecx
    L_004636a6:
        push esi
    L_004636a7:
        mov esi,dword ptr [ebp+8]
    L_004636aa:
        cmp dword ptr [esi],80000003h
    L_004636b0:
        je asm_target_0046375c
    L_004636b6:
        call asm_getptd_00456357
    L_004636bb:
        cmp dword ptr [eax+74h],0
    L_004636bf:
        je short L_004636e0
    L_004636c1:
        push dword ptr [ebp+24h]
    L_004636c4:
        push dword ptr [ebp+20h]
    L_004636c7:
        push dword ptr [ebp+18h]
    L_004636ca:
        push dword ptr [ebp+14h]
    L_004636cd:
        push dword ptr [ebp+10h]
    L_004636d0:
        push dword ptr [ebp+0Ch]
    L_004636d3:
        push esi
    L_004636d4:
        call asm_CallSETranslator_004627f8
    L_004636d9:
        add esp,1Ch
    L_004636dc:
        test eax,eax
    L_004636de:
        jne short L_0046375c
    L_004636e0:
        mov esi,dword ptr [ebp+1Ch]
    L_004636e3:
        push edi
    L_004636e4:
        lea eax,[ebp-8]
    L_004636e7:
        push eax
    L_004636e8:
        lea eax,[ebp-4]
    L_004636eb:
        push eax
    L_004636ec:
        push esi
    L_004636ed:
        push dword ptr [ebp+20h]
    L_004636f0:
        push dword ptr [ebp+18h]
    L_004636f3:
        call asm_GetRangeOfTrysToCheck_00462971
    L_004636f8:
        mov edi,eax
    L_004636fa:
        mov eax,dword ptr [ebp-4]
    L_004636fd:
        add esp,14h
    L_00463700:
        cmp eax,dword ptr [ebp-8]
    L_00463703:
        jae short L_0046375b
    L_00463705:
        push ebx
    L_00463706:
        cmp esi,dword ptr [edi]
    L_00463708:
        jl short L_0046374c
    L_0046370a:
        cmp esi,dword ptr [edi+4]
    L_0046370d:
        jg short L_0046374c
    L_0046370f:
        mov eax,dword ptr [edi+0Ch]
    L_00463712:
        mov ecx,dword ptr [edi+10h]
    L_00463715:
        shl eax,4
    L_00463718:
        add eax,ecx
    L_0046371a:
        mov ecx,dword ptr [eax-0Ch]
    L_0046371d:
        test ecx,ecx
    L_0046371f:
        je short L_00463727
    L_00463721:
        cmp byte ptr [ecx+8],0
    L_00463725:
        jne short L_0046374c
    L_00463727:
        push dword ptr [ebp+24h]
    L_0046372a:
        mov esi,dword ptr [ebp+0Ch]
    L_0046372d:
        push dword ptr [ebp+20h]
    L_00463730:
        lea ebx,[eax-10h]
    L_00463733:
        push dword ptr [ebp+18h]
    L_00463736:
        xor ecx,ecx
    L_00463738:
        push dword ptr [ebp+14h]
    L_0046373b:
        push dword ptr [ebp+10h]
    L_0046373e:
        push dword ptr [ebp+8]
    L_00463741:
        call asm_CatchIt_0046363a
    L_00463746:
        mov esi,dword ptr [ebp+1Ch]
    L_00463749:
        add esp,18h
    L_0046374c:
        inc dword ptr [ebp-4]
    L_0046374f:
        mov eax,dword ptr [ebp-4]
    L_00463752:
        add edi,14h
    L_00463755:
        cmp eax,dword ptr [ebp-8]
    L_00463758:
        jb short L_00463706
    L_0046375a:
        pop ebx
    L_0046375b:
        pop edi
    L_0046375c:
        pop esi
    L_0046375d:
        leave
    L_0046375e:
        ret
    }
}
