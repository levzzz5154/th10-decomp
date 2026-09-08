#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046054E..0x004605B6: __stricmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_stricmp_0046054e() {
    __asm {
    L_0046054e:
        push ebp
    L_0046054f:
        mov ebp,esp
    L_00460551:
        push ecx
    L_00460552:
        push ebx
    L_00460553:
        call asm_getptd_00456357
    L_00460558:
        mov ebx,dword ptr [eax+64h]
    L_0046055b:
        cmp ebx,dword ptr [data_0047320c]
    L_00460561:
        je short L_0046056a
    L_00460563:
        call asm_updatetlocinfo_00455ade
    L_00460568:
        mov ebx,eax
    L_0046056a:
        cmp dword ptr [ebx+14h],0
    L_0046056e:
        jne short L_0046057f
    L_00460570:
        push dword ptr [ebp+0Ch]
    L_00460573:
        push dword ptr [ebp+8]
    L_00460576:
        call asm_ascii_stricmp_004603d0
    L_0046057b:
        pop ecx
    L_0046057c:
        pop ecx
    L_0046057d:
        jmp short L_004605b4
    L_0046057f:
        push esi
    L_00460580:
        mov esi,dword ptr [ebp+8]
    L_00460583:
        push edi
    L_00460584:
        mov edi,dword ptr [ebp+0Ch]
    L_00460587:
        movzx eax,byte ptr [esi]
    L_0046058a:
        push eax
    L_0046058b:
        push ebx
    L_0046058c:
        call asm_tolower_mt_00460c26
    L_00460591:
        mov dword ptr [ebp-4],eax
    L_00460594:
        movzx eax,byte ptr [edi]
    L_00460597:
        push eax
    L_00460598:
        push ebx
    L_00460599:
        inc esi
    L_0046059a:
        call asm_tolower_mt_00460c26
    L_0046059f:
        add esp,10h
    L_004605a2:
        mov ecx,eax
    L_004605a4:
        mov eax,dword ptr [ebp-4]
    L_004605a7:
        inc edi
    L_004605a8:
        test eax,eax
    L_004605aa:
        je short L_004605b0
    L_004605ac:
        cmp eax,ecx
    L_004605ae:
        je short L_00460587
    L_004605b0:
        pop edi
    L_004605b1:
        sub eax,ecx
    L_004605b3:
        pop esi
    L_004605b4:
        pop ebx
    L_004605b5:
        leave
    L_004605b6:
        ret
    }
}
