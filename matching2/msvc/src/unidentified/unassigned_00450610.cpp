#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450610..0x00450689: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00450610() {
    __asm {
    L_00450610:
        mov edx,dword ptr [eax+1000h]
    L_00450616:
        sub edx,ecx
    L_00450618:
        push ebp
    L_00450619:
        mov ebp,dword ptr [esp+8]
    L_0045061d:
        jns short L_00450626
    L_0045061f:
        or eax,0FFFFFFFFh
    L_00450622:
        pop ebp
    L_00450623:
        ret 4
    L_00450626:
        push esi
    L_00450627:
        push edi
    L_00450628:
        mov dword ptr [eax+1000h],edx
    L_0045062e:
        lea esi,[edx+eax]
    L_00450631:
        mov edx,ecx
    L_00450633:
        shr ecx,2
    L_00450636:
        mov edi,ebp
    L_00450638:
        rep movsd
    L_0045063a:
        mov ecx,edx
    L_0045063c:
        and ecx,3
    L_0045063f:
        test bl,bl
    L_00450641:
        rep movsb
    L_00450643:
        pop edi
    L_00450644:
        pop esi
    L_00450645:
        je short L_00450684
    L_00450647:
        mov edx,dword ptr [eax+1000h]
    L_0045064d:
        add edx,0FFFFFFFCh
    L_00450650:
        mov ecx,edx
    L_00450652:
        mov dword ptr [eax+1000h],edx
    L_00450658:
        mov al,byte ptr [ecx+eax]
    L_0045065b:
        cmp al,66h
    L_0045065d:
        je short L_00450674
    L_0045065f:
        cmp al,69h
    L_00450661:
        jne short L_00450684
    L_00450663:
        cmp bl,66h
    L_00450666:
        jne short L_00450684
    L_00450668:
        fild dword ptr [ebp]
    L_0045066b:
        xor eax,eax
    L_0045066d:
        fstp dword ptr [ebp]
    L_00450670:
        pop ebp
    L_00450671:
        ret 4
    L_00450674:
        cmp bl,69h
    L_00450677:
        jne short L_00450684
    L_00450679:
        fld dword ptr [ebp]
    L_0045067c:
        call asm_FUN_00463b2c_00463b2c
    L_00450681:
        mov dword ptr [ebp],eax
    L_00450684:
        xor eax,eax
    L_00450686:
        pop ebp
    L_00450687:
        ret 4
    }
}
