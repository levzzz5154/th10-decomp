#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420540..0x0042066D: one complete function. The seven-byte prologue was
// previously misclassified as embedded .text data.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420540() {
    __asm {
    L_00420540:
        push ecx
    L_00420541:
        push ebp
    L_00420542:
        push 492150h
    L_00420547:
        call asm_File_OpenSharedWrite_0044b620
    L_0042054c:
        mov eax,dword ptr [data_00474c38]
    L_00420551:
        xor ebp,ebp
    L_00420553:
        cmp eax,0FFFFFFFFh
    L_00420556:
        je asm_target_00420635
    L_0042055c:
        push ebx
    L_0042055d:
        mov ebx,dword ptr [data_004660d4]
    L_00420563:
        push esi
    L_00420564:
        push edi
    L_00420565:
        push ebp
    L_00420566:
        lea ecx,[esp+14h]
    L_0042056a:
        push ecx
    L_0042056b:
        push 0Eh
    L_0042056d:
        push 492138h
    L_00420572:
        push eax
    L_00420573:
        call ebx
    L_00420575:
        cmp dword ptr [esp+10h],0Eh
    L_0042057a:
        mov esi,dword ptr [data_004660cc]
    L_00420580:
        mov edi,dword ptr [data_004660b4]
    L_00420586:
        je short L_0042059e
    L_00420588:
        mov edx,dword ptr [data_00474c38]
    L_0042058e:
        push edx
    L_0042058f:
        call esi
    L_00420591:
        push 4922A4h
    L_00420596:
        call edi
    L_00420598:
        dec byte ptr [data_0049231e]
    L_0042059e:
        mov eax,dword ptr [data_00474c38]
    L_004205a3:
        cmp eax,0FFFFFFFFh
    L_004205a6:
        je asm_target_00420632
    L_004205ac:
        mov edx,dword ptr [data_00492148]
    L_004205b2:
        push ebp
    L_004205b3:
        lea ecx,[esp+14h]
    L_004205b7:
        push ecx
    L_004205b8:
        push 28h
    L_004205ba:
        push edx
    L_004205bb:
        push eax
    L_004205bc:
        call ebx
    L_004205be:
        cmp dword ptr [esp+10h],28h
    L_004205c3:
        je short L_004205da
    L_004205c5:
        mov eax,dword ptr [data_00474c38]
    L_004205ca:
        push eax
    L_004205cb:
        call esi
    L_004205cd:
        push 4922A4h
    L_004205d2:
        call edi
    L_004205d4:
        dec byte ptr [data_0049231e]
    L_004205da:
        mov eax,dword ptr [data_00474c38]
    L_004205df:
        cmp eax,0FFFFFFFFh
    L_004205e2:
        je short L_00420632
    L_004205e4:
        mov edx,dword ptr [data_0049214c]
    L_004205ea:
        push ebp
    L_004205eb:
        lea ecx,[esp+14h]
    L_004205ef:
        push ecx
    L_004205f0:
        push 0E1000h
    L_004205f5:
        push edx
    L_004205f6:
        push eax
    L_004205f7:
        call ebx
    L_004205f9:
        cmp dword ptr [esp+10h],0E1000h
    L_00420601:
        je short L_00420618
    L_00420603:
        mov eax,dword ptr [data_00474c38]
    L_00420608:
        push eax
    L_00420609:
        call esi
    L_0042060b:
        push 4922A4h
    L_00420610:
        call edi
    L_00420612:
        dec byte ptr [data_0049231e]
    L_00420618:
        mov eax,dword ptr [data_00474c38]
    L_0042061d:
        cmp eax,0FFFFFFFFh
    L_00420620:
        je short L_00420632
    L_00420622:
        push eax
    L_00420623:
        call esi
    L_00420625:
        push 4922A4h
    L_0042062a:
        call edi
    L_0042062c:
        dec byte ptr [data_0049231e]
    L_00420632:
        pop edi
    L_00420633:
        pop esi
    L_00420634:
        pop ebx
    L_00420635:
        mov eax,dword ptr [data_00492148]
    L_0042063a:
        cmp eax,ebp
    L_0042063c:
        je short L_0042064d
    L_0042063e:
        push eax
    L_0042063f:
        call asm_free_00452422
    L_00420644:
        add esp,4
    L_00420647:
        mov dword ptr [data_00492148],ebp
    L_0042064d:
        mov eax,dword ptr [data_0049214c]
    L_00420652:
        cmp eax,ebp
    L_00420654:
        je short L_00420665
    L_00420656:
        push eax
    L_00420657:
        call asm_free_00452422
    L_0042065c:
        add esp,4
    L_0042065f:
        mov dword ptr [data_0049214c],ebp
    L_00420665:
        mov dword ptr [data_00492134],ebp
    L_0042066b:
        pop ebp
    L_0042066c:
        pop ecx
    L_0042066d:
        ret
    }
}
