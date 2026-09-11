#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.

// 0x0040E6A0..0x0040E755: Enemy_DeathSweepRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Enemy_DeathSweepRetail_0040e6a0() {
    __asm {
    L_0040e6a0:
        push ebp
    L_0040e6a1:
        mov ebp,dword ptr [esp+8]
    L_0040e6a5:
        mov eax,dword ptr [ebp+58h]
    L_0040e6a8:
        test eax,eax
    L_0040e6aa:
        je short L_0040e707
    L_0040e6ac:
        push ebx
    L_0040e6ad:
        push esi
    L_0040e6ae:
        push edi
    L_0040e6af:
        nop
    L_0040e6b0:
        mov esi,dword ptr [eax]
    L_0040e6b2:
        mov ebx,dword ptr [eax+4]
    L_0040e6b5:
        mov eax,dword ptr [esi+2480h]
    L_0040e6bb:
        test al,50h
    L_0040e6bd:
        jne short L_0040e6c4
    L_0040e6bf:
        test ah,0C0h
    L_0040e6c2:
        je short L_0040e6c8
    L_0040e6c4:
        test al,al
    L_0040e6c6:
        jns short L_0040e6fe
    L_0040e6c8:
        mov eax,dword ptr [esi+2448h]
    L_0040e6ce:
        test eax,eax
    L_0040e6d0:
        jl short L_0040e6f4
    L_0040e6d2:
        mov ecx,dword ptr [esi+244Ch]
    L_0040e6d8:
        mov edx,dword ptr [data_00477704]
    L_0040e6de:
        push eax
    L_0040e6df:
        lea eax,[esp+18h]
    L_0040e6e3:
        push eax
    L_0040e6e4:
        mov eax,dword ptr [edx+ecx*4+30h]
    L_0040e6e8:
        lea edi,[esi+1068h]
    L_0040e6ee:
        push eax
    L_0040e6ef:
        call asm_PlayerAnimation_Create_00448db0
    L_0040e6f4:
        or dword ptr [esi+2480h],20000h
    L_0040e6fe:
        test ebx,ebx
    L_0040e700:
        mov eax,ebx
    L_0040e702:
        jne short L_0040e6b0
    L_0040e704:
        pop edi
    L_0040e705:
        pop esi
    L_0040e706:
        pop ebx
    L_0040e707:
        mov edx,dword ptr [ebp+44h]
    L_0040e70a:
        mov ecx,dword ptr [ebp+4Ch]
    L_0040e70d:
        mov dword ptr [ebp+40h],edx
    L_0040e710:
        fld dword ptr [ecx]
    L_0040e712:
        fcomp dword ptr [data_00470b68]
    L_0040e718:
        fnstsw ax
    L_0040e71a:
        test ah,41h
    L_0040e71d:
        jne short L_0040e742
    L_0040e71f:
        fld dword ptr [ecx]
    L_0040e721:
        fcomp dword ptr [data_00470b64]
    L_0040e727:
        fnstsw ax
    L_0040e729:
        test ah,5
    L_0040e72c:
        jp short L_0040e742
    L_0040e72e:
        fld dword ptr [ebp+48h]
    L_0040e731:
        inc edx
    L_0040e732:
        fadd dword ptr [data_00470afc]
    L_0040e738:
        mov dword ptr [ebp+44h],edx
    L_0040e73b:
        fstp dword ptr [ebp+48h]
    L_0040e73e:
        pop ebp
    L_0040e73f:
        ret 4
    L_0040e742:
        fld dword ptr [ecx]
    L_0040e744:
        fadd dword ptr [ebp+48h]
    L_0040e747:
        fst dword ptr [ebp+48h]
    L_0040e74a:
        call asm_FUN_00463b2c_00463b2c
    L_0040e74f:
        mov dword ptr [ebp+44h],eax
    L_0040e752:
        pop ebp
    L_0040e753:
        ret 4
    }
}
