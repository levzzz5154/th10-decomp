#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x004065C0..0x004066B8: FUN_004065c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004065c0_004065c0() {
    __asm {
    L_004065c0:
        push ecx
    L_004065c1:
        push ebx
    L_004065c2:
        push ebp
    L_004065c3:
        xor ebp,ebp
    L_004065c5:
        lea ebx,[esi+60h]
    L_004065c8:
        push edi
    L_004065c9:
        mov dword ptr [esi+5Ch],ebp
    L_004065cc:
        mov dword ptr [esi+28h],ebp
    L_004065cf:
        mov dword ptr [esi+24h],ebp
    L_004065d2:
        mov dword ptr [esi+20h],ebp
    L_004065d5:
        mov dword ptr [esi+1Ch],ebp
    L_004065d8:
        mov dword ptr [esi+18h],ebp
    L_004065db:
        mov dword ptr [esi+14h],ebp
    L_004065de:
        mov dword ptr [esi+40h],ebp
    L_004065e1:
        mov dword ptr [esi+3Ch],ebp
    L_004065e4:
        mov dword ptr [esi+38h],ebp
    L_004065e7:
        mov dword ptr [esi+34h],ebp
    L_004065ea:
        mov dword ptr [esi+30h],ebp
    L_004065ed:
        mov dword ptr [esi+2Ch],ebp
    L_004065f0:
        lea edi,[ebx+400h]
    L_004065f6:
        mov dword ptr [esp+0Ch],7D0h
    L_004065fe:
        mov edi,edi
    L_00406600:
        cmp word ptr [edi+46h],bp
    L_00406604:
        je asm_target_00406694
    L_0040660a:
        mov eax,dword ptr [data_00477810]
    L_0040660f:
        cmp eax,ebp
    L_00406611:
        je short L_0040661f
    L_00406613:
        mov eax,dword ptr [eax+58h]
    L_00406616:
        test al,2
    L_00406618:
        je short L_0040661f
    L_0040661a:
        test ah,4
    L_0040661d:
        jne short L_00406629
    L_0040661f:
        push ebx
    L_00406620:
        call asm_FUN_00406240_00406240
    L_00406625:
        test eax,eax
    L_00406627:
        jne short L_00406694
    L_00406629:
        mov eax,dword ptr [edi+60h]
    L_0040662c:
        cmp dword ptr [esi+eax*4+14h],ebp
    L_00406630:
        je short L_0040663e
    L_00406632:
        mov eax,dword ptr [esi+eax*4+2Ch]
    L_00406636:
        mov dword ptr [eax+44Ch],ebx
    L_0040663c:
        jmp short L_00406642
    L_0040663e:
        mov dword ptr [esi+eax*4+14h],ebx
    L_00406642:
        mov ecx,dword ptr [edi+60h]
    L_00406645:
        mov dword ptr [esi+ecx*4+2Ch],ebx
    L_00406649:
        mov dword ptr [edi+4Ch],ebp
    L_0040664c:
        inc dword ptr [esi+5Ch]
    L_0040664f:
        mov edx,dword ptr [edi-4]
    L_00406652:
        mov ecx,dword ptr [edi+4]
    L_00406655:
        mov dword ptr [edi-8],edx
    L_00406658:
        fld dword ptr [ecx]
    L_0040665a:
        fcomp dword ptr [data_00470b68]
    L_00406660:
        fnstsw ax
    L_00406662:
        test ah,41h
    L_00406665:
        jne short L_00406686
    L_00406667:
        fld dword ptr [ecx]
    L_00406669:
        fcomp dword ptr [data_00470b64]
    L_0040666f:
        fnstsw ax
    L_00406671:
        test ah,5
    L_00406674:
        jp short L_00406686
    L_00406676:
        fld dword ptr [edi]
    L_00406678:
        inc edx
    L_00406679:
        fadd dword ptr [data_00470afc]
    L_0040667f:
        mov dword ptr [edi-4],edx
    L_00406682:
        fstp dword ptr [edi]
    L_00406684:
        jmp short L_00406694
    L_00406686:
        fld dword ptr [edi]
    L_00406688:
        fadd dword ptr [ecx]
    L_0040668a:
        fst dword ptr [edi]
    L_0040668c:
        call asm_FUN_00463b2c_00463b2c
    L_00406691:
        mov dword ptr [edi-4],eax
    L_00406694:
        mov eax,dword ptr [esp+0Ch]
    L_00406698:
        add ebx,7F0h
    L_0040669e:
        add edi,7F0h
    L_004066a4:
        dec eax
    L_004066a5:
        mov dword ptr [esp+0Ch],eax
    L_004066a9:
        jne asm_target_00406600
    L_004066af:
        pop edi
    L_004066b0:
        pop ebp
    L_004066b1:
        mov eax,1
    L_004066b6:
        pop ebx
    L_004066b7:
        pop ecx
    L_004066b8:
        ret
    }
}
