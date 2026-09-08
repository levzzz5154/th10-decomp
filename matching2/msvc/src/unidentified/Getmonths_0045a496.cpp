#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A496..0x0045A52A: __Getmonths
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Getmonths_0045a496() {
    __asm {
    L_0045a496:
        push ebp
    L_0045a497:
        mov ebp,esp
    L_0045a499:
        push ecx
    L_0045a49a:
        push ecx
    L_0045a49b:
        and dword ptr [ebp-4],0
    L_0045a49f:
        push ebx
    L_0045a4a0:
        push esi
    L_0045a4a1:
        push edi
    L_0045a4a2:
        mov edi,dword ptr [data_004739e0]
    L_0045a4a8:
        lea esi,[edi+38h]
    L_0045a4ab:
        mov dword ptr [ebp-8],0Ch
    L_0045a4b2:
        push dword ptr [esi+30h]
    L_0045a4b5:
        call asm_strlen_00456720
    L_0045a4ba:
        push dword ptr [esi]
    L_0045a4bc:
        mov ebx,eax
    L_0045a4be:
        call asm_strlen_00456720
    L_0045a4c3:
        add eax,dword ptr [ebp-4]
    L_0045a4c6:
        pop ecx
    L_0045a4c7:
        lea eax,[eax+ebx+2]
    L_0045a4cb:
        add esi,4
    L_0045a4ce:
        dec dword ptr [ebp-8]
    L_0045a4d1:
        pop ecx
    L_0045a4d2:
        mov dword ptr [ebp-4],eax
    L_0045a4d5:
        jne short L_0045a4b2
    L_0045a4d7:
        inc eax
    L_0045a4d8:
        push eax
    L_0045a4d9:
        call asm_malloc_00452706
    L_0045a4de:
        mov esi,eax
    L_0045a4e0:
        test esi,esi
    L_0045a4e2:
        pop ecx
    L_0045a4e3:
        mov dword ptr [ebp-8],esi
    L_0045a4e6:
        je short L_0045a523
    L_0045a4e8:
        push 0Ch
    L_0045a4ea:
        add edi,68h
    L_0045a4ed:
        pop ebx
    L_0045a4ee:
        mov byte ptr [esi],3Ah
    L_0045a4f1:
        push dword ptr [edi-30h]
    L_0045a4f4:
        inc esi
    L_0045a4f5:
        push esi
    L_0045a4f6:
        call asm_FUN_0045bd80_0045bd80
    L_0045a4fb:
        push eax
    L_0045a4fc:
        call asm_strlen_00456720
    L_0045a501:
        add esi,eax
    L_0045a503:
        mov byte ptr [esi],3Ah
    L_0045a506:
        push dword ptr [edi]
    L_0045a508:
        inc esi
    L_0045a509:
        push esi
    L_0045a50a:
        call asm_FUN_0045bd80_0045bd80
    L_0045a50f:
        push eax
    L_0045a510:
        call asm_strlen_00456720
    L_0045a515:
        add esp,18h
    L_0045a518:
        add esi,eax
    L_0045a51a:
        add edi,4
    L_0045a51d:
        dec ebx
    L_0045a51e:
        jne short L_0045a4ee
    L_0045a520:
        mov byte ptr [esi],0
    L_0045a523:
        mov eax,dword ptr [ebp-8]
    L_0045a526:
        pop edi
    L_0045a527:
        pop esi
    L_0045a528:
        pop ebx
    L_0045a529:
        leave
    L_0045a52a:
        ret
    }
}
