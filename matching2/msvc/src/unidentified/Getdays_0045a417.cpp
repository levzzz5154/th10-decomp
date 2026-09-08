#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A417..0x0045A495: __Getdays
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Getdays_0045a417() {
    __asm {
    L_0045a417:
        push ebx
    L_0045a418:
        push ebp
    L_0045a419:
        push esi
    L_0045a41a:
        push edi
    L_0045a41b:
        mov edi,dword ptr [data_004739e0]
    L_0045a421:
        xor esi,esi
    L_0045a423:
        xor ebx,ebx
    L_0045a425:
        push dword ptr [edi+ebx*4+1Ch]
    L_0045a429:
        call asm_strlen_00456720
    L_0045a42e:
        push dword ptr [edi+ebx*4]
    L_0045a431:
        mov ebp,eax
    L_0045a433:
        call asm_strlen_00456720
    L_0045a438:
        add eax,esi
    L_0045a43a:
        inc ebx
    L_0045a43b:
        cmp ebx,7
    L_0045a43e:
        pop ecx
    L_0045a43f:
        pop ecx
    L_0045a440:
        lea esi,[eax+ebp+2]
    L_0045a444:
        jb short L_0045a425
    L_0045a446:
        inc esi
    L_0045a447:
        push esi
    L_0045a448:
        call asm_malloc_00452706
    L_0045a44d:
        mov ebp,eax
    L_0045a44f:
        test ebp,ebp
    L_0045a451:
        pop ecx
    L_0045a452:
        je short L_0045a48f
    L_0045a454:
        mov esi,ebp
    L_0045a456:
        xor ebx,ebx
    L_0045a458:
        mov byte ptr [esi],3Ah
    L_0045a45b:
        push dword ptr [edi+ebx*4]
    L_0045a45e:
        inc esi
    L_0045a45f:
        push esi
    L_0045a460:
        call asm_FUN_0045bd80_0045bd80
    L_0045a465:
        push eax
    L_0045a466:
        call asm_strlen_00456720
    L_0045a46b:
        add esi,eax
    L_0045a46d:
        mov byte ptr [esi],3Ah
    L_0045a470:
        push dword ptr [edi+ebx*4+1Ch]
    L_0045a474:
        inc esi
    L_0045a475:
        push esi
    L_0045a476:
        call asm_FUN_0045bd80_0045bd80
    L_0045a47b:
        push eax
    L_0045a47c:
        call asm_strlen_00456720
    L_0045a481:
        add esp,18h
    L_0045a484:
        add esi,eax
    L_0045a486:
        inc ebx
    L_0045a487:
        cmp ebx,7
    L_0045a48a:
        jb short L_0045a458
    L_0045a48c:
        mov byte ptr [esi],0
    L_0045a48f:
        pop edi
    L_0045a490:
        pop esi
    L_0045a491:
        mov eax,ebp
    L_0045a493:
        pop ebp
    L_0045a494:
        pop ebx
    L_0045a495:
        ret
    }
}
