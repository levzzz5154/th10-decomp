#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00444760..0x00444B00: FUN_00444760
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00444760_00444760() {
    __asm {
    L_00444760:
        sub esp,0C0h
    L_00444766:
        push ebx
    L_00444767:
        mov ebx,eax
    L_00444769:
        mov eax,dword ptr [ebx+35Ch]
    L_0044476f:
        test al,1
    L_00444771:
        je short L_00444777
    L_00444773:
        test al,2
    L_00444775:
        jne short L_00444784
    L_00444777:
        or eax,0FFFFFFFFh
    L_0044477a:
        pop ebx
    L_0044477b:
        add esp,0C0h
    L_00444781:
        ret 4
    L_00444784:
        mov al,byte ptr [ebx+2FFh]
    L_0044478a:
        test al,al
    L_0044478c:
        jne short L_0044479d
    L_0044478e:
        mov eax,0FFFFFFFFh
    L_00444793:
        pop ebx
    L_00444794:
        add esp,0C0h
    L_0044479a:
        ret 4
    L_0044479d:
        push ebp
    L_0044479e:
        mov ebp,dword ptr [esp+0CCh]
    L_004447a5:
        mov eax,dword ptr [ebp+3ADAC8h]
    L_004447ab:
        test eax,eax
    L_004447ad:
        push esi
    L_004447ae:
        je short L_004447b7
    L_004447b0:
        mov esi,ebp
    L_004447b2:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004447b7:
        mov eax,dword ptr [ebx+35Ch]
    L_004447bd:
        test ah,40h
    L_004447c0:
        push edi
    L_004447c1:
        jne asm_target_0044489f
    L_004447c7:
        test al,0Ch
    L_004447c9:
        je asm_target_0044489f
    L_004447cf:
        fld dword ptr [ebx+3Ch]
    L_004447d2:
        lea ebp,[ebx+27Ch]
    L_004447d8:
        lea esi,[ebx+23Ch]
    L_004447de:
        mov ecx,10h
    L_004447e3:
        mov edi,ebp
    L_004447e5:
        rep movsd
    L_004447e7:
        fmul dword ptr [ebp]
    L_004447ea:
        fstp dword ptr [ebp]
    L_004447ed:
        fld dword ptr [ebx+40h]
    L_004447f0:
        fmul dword ptr [ebx+290h]
    L_004447f6:
        fstp dword ptr [ebx+290h]
    L_004447fc:
        fld dword ptr [ebx+24h]
    L_004447ff:
        fld qword ptr [data_00470b70]
    L_00444805:
        and eax,0FFFFFFF7h
    L_00444808:
        fucompp
    L_0044480a:
        mov dword ptr [ebx+35Ch],eax
    L_00444810:
        fnstsw ax
    L_00444812:
        test ah,44h
    L_00444815:
        jnp short L_00444831
    L_00444817:
        mov eax,dword ptr [ebx+24h]
    L_0044481a:
        push eax
    L_0044481b:
        lea ecx,[esp+54h]
    L_0044481f:
        push ecx
    L_00444820:
        call asm_D3DXMatrixRotationX_004521ac
    L_00444825:
        lea edx,[esp+50h]
    L_00444829:
        push edx
    L_0044482a:
        push ebp
    L_0044482b:
        push ebp
    L_0044482c:
        call asm_D3DXMatrixMultiply_004521b2
    L_00444831:
        fld dword ptr [ebx+28h]
    L_00444834:
        fld qword ptr [data_00470b70]
    L_0044483a:
        fucompp
    L_0044483c:
        fnstsw ax
    L_0044483e:
        test ah,44h
    L_00444841:
        jnp short L_0044485d
    L_00444843:
        mov eax,dword ptr [ebx+28h]
    L_00444846:
        push eax
    L_00444847:
        lea ecx,[esp+54h]
    L_0044484b:
        push ecx
    L_0044484c:
        call asm_D3DXMatrixRotationY_004521b8
    L_00444851:
        lea edx,[esp+50h]
    L_00444855:
        push edx
    L_00444856:
        push ebp
    L_00444857:
        push ebp
    L_00444858:
        call asm_D3DXMatrixMultiply_004521b2
    L_0044485d:
        fld dword ptr [ebx+2Ch]
    L_00444860:
        fld qword ptr [data_00470b70]
    L_00444866:
        fucompp
    L_00444868:
        fnstsw ax
    L_0044486a:
        test ah,44h
    L_0044486d:
        jnp short L_00444889
    L_0044486f:
        mov eax,dword ptr [ebx+2Ch]
    L_00444872:
        push eax
    L_00444873:
        lea ecx,[esp+54h]
    L_00444877:
        push ecx
    L_00444878:
        call asm_D3DXMatrixRotationZ_004521be
    L_0044487d:
        lea edx,[esp+50h]
    L_00444881:
        push edx
    L_00444882:
        push ebp
    L_00444883:
        push ebp
    L_00444884:
        call asm_D3DXMatrixMultiply_004521b2
    L_00444889:
        mov eax,dword ptr [ebx+35Ch]
    L_0044488f:
        mov ebp,dword ptr [esp+0D4h]
    L_00444896:
        and eax,0FFFFFFFBh
    L_00444899:
        mov dword ptr [ebx+35Ch],eax
    L_0044489f:
        lea esi,[ebx+27Ch]
    L_004448a5:
        mov ecx,10h
    L_004448aa:
        lea edi,[esp+10h]
    L_004448ae:
        rep movsd
    L_004448b0:
        mov ecx,dword ptr [ebx+35Ch]
    L_004448b6:
        mov eax,ecx
    L_004448b8:
        shr eax,12h
    L_004448bb:
        and eax,3
    L_004448be:
        sub eax,0
    L_004448c1:
        je short L_00444907
    L_004448c3:
        dec eax
    L_004448c4:
        je short L_004448df
    L_004448c6:
        dec eax
    L_004448c7:
        jne short L_0044491d
    L_004448c9:
        fld dword ptr [ebx+4Ch]
    L_004448cc:
        fmul dword ptr [ebx+3Ch]
    L_004448cf:
        fmul dword ptr [data_00470b0c]
    L_004448d5:
        fabs
    L_004448d7:
        fadd dword ptr [ebx+34Ch]
    L_004448dd:
        jmp short L_0044490d
    L_004448df:
        fld dword ptr [ebx+34Ch]
    L_004448e5:
        fadd dword ptr [ebx+340h]
    L_004448eb:
        fadd dword ptr [ebx+334h]
    L_004448f1:
        fld dword ptr [ebx+4Ch]
    L_004448f4:
        fmul dword ptr [ebx+3Ch]
    L_004448f7:
        fmul dword ptr [data_00470b0c]
    L_004448fd:
        fabs
    L_004448ff:
        fxch
    L_00444901:
        fxch
    L_00444903:
        fsubp st(1),st
    L_00444905:
        jmp short L_00444919
    L_00444907:
        fld dword ptr [ebx+34Ch]
    L_0044490d:
        fadd dword ptr [ebx+340h]
    L_00444913:
        fadd dword ptr [ebx+334h]
    L_00444919:
        fstp dword ptr [esp+40h]
    L_0044491d:
        shr ecx,14h
    L_00444920:
        and ecx,3
    L_00444923:
        sub ecx,0
    L_00444926:
        je short L_0044496c
    L_00444928:
        dec ecx
    L_00444929:
        je short L_00444944
    L_0044492b:
        dec ecx
    L_0044492c:
        jne short L_00444982
    L_0044492e:
        fld dword ptr [ebx+50h]
    L_00444931:
        fmul dword ptr [ebx+40h]
    L_00444934:
        fmul dword ptr [data_00470b0c]
    L_0044493a:
        fabs
    L_0044493c:
        fadd dword ptr [ebx+350h]
    L_00444942:
        jmp short L_00444972
    L_00444944:
        fld dword ptr [ebx+350h]
    L_0044494a:
        fadd dword ptr [ebx+344h]
    L_00444950:
        fadd dword ptr [ebx+338h]
    L_00444956:
        fld dword ptr [ebx+50h]
    L_00444959:
        fmul dword ptr [ebx+40h]
    L_0044495c:
        fmul dword ptr [data_00470b0c]
    L_00444962:
        fabs
    L_00444964:
        fxch
    L_00444966:
        fxch
    L_00444968:
        fsubp st(1),st
    L_0044496a:
        jmp short L_0044497e
    L_0044496c:
        fld dword ptr [ebx+350h]
    L_00444972:
        fadd dword ptr [ebx+344h]
    L_00444978:
        fadd dword ptr [ebx+338h]
    L_0044497e:
        fstp dword ptr [esp+44h]
    L_00444982:
        fld dword ptr [ebx+33Ch]
    L_00444988:
        mov eax,ebp
    L_0044498a:
        fadd dword ptr [ebx+348h]
    L_00444990:
        fstp dword ptr [esp+48h]
    L_00444994:
        call asm_FUN_004423e0_004423e0
    L_00444999:
        fld dword ptr [ebx+354h]
    L_0044499f:
        mov eax,dword ptr [data_00491c30]
    L_004449a4:
        fadd dword ptr [ebx+33Ch]
    L_004449aa:
        lea edx,[esp+10h]
    L_004449ae:
        push edx
    L_004449af:
        push 100h
    L_004449b4:
        fadd dword ptr [ebx+348h]
    L_004449ba:
        push eax
    L_004449bb:
        fstp dword ptr [esp+54h]
    L_004449bf:
        mov ecx,dword ptr [eax]
    L_004449c1:
        call dword ptr [ecx+0B0h]
    L_004449c7:
        mov eax,dword ptr [ebx+394h]
    L_004449cd:
        mov eax,dword ptr [eax+4]
    L_004449d0:
        cmp dword ptr [ebp+3ADA64h],eax
    L_004449d6:
        je short L_004449f0
    L_004449d8:
        push eax
    L_004449d9:
        mov dword ptr [ebp+3ADA64h],eax
    L_004449df:
        mov ecx,dword ptr [data_00491c30]
    L_004449e5:
        mov edx,dword ptr [ecx]
    L_004449e7:
        push 0
    L_004449e9:
        push ecx
    L_004449ea:
        call dword ptr [edx+104h]
    L_004449f0:
        mov ecx,dword ptr [ebx+394h]
    L_004449f6:
        cmp dword ptr [ebp+3ADA70h],ecx
    L_004449fc:
        jne short L_00444a22
    L_004449fe:
        fld dword ptr [data_00470b04]
    L_00444a04:
        fld dword ptr [ebx+54h]
    L_00444a07:
        fucompp
    L_00444a09:
        fnstsw ax
    L_00444a0b:
        test ah,44h
    L_00444a0e:
        jp short L_00444a22
    L_00444a10:
        fld dword ptr [data_00470b04]
    L_00444a16:
        fld dword ptr [ebx+54h]
    L_00444a19:
        fucompp
    L_00444a1b:
        fnstsw ax
    L_00444a1d:
        test ah,44h
    L_00444a20:
        jnp short L_00444a74
    L_00444a22:
        mov dword ptr [ebp+3ADA70h],ecx
    L_00444a28:
        mov eax,dword ptr [ebx+394h]
    L_00444a2e:
        lea esi,[ebx+2BCh]
    L_00444a34:
        mov ecx,10h
    L_00444a39:
        lea edi,[esp+90h]
    L_00444a40:
        rep movsd
    L_00444a42:
        fld dword ptr [eax+20h]
    L_00444a45:
        fadd dword ptr [ebx+54h]
    L_00444a48:
        fstp dword ptr [esp+0B0h]
    L_00444a4f:
        fld dword ptr [eax+24h]
    L_00444a52:
        fadd dword ptr [ebx+58h]
    L_00444a55:
        fstp dword ptr [esp+0B4h]
    L_00444a5c:
        mov eax,dword ptr [data_00491c30]
    L_00444a61:
        mov ecx,dword ptr [eax]
    L_00444a63:
        lea edx,[esp+90h]
    L_00444a6a:
        push edx
    L_00444a6b:
        push 10h
    L_00444a6d:
        push eax
    L_00444a6e:
        call dword ptr [ecx+0B0h]
    L_00444a74:
        mov al,byte ptr [ebp+3ADA6Ah]
    L_00444a7a:
        mov ebx,2
    L_00444a7f:
        cmp al,bl
    L_00444a81:
        pop edi
    L_00444a82:
        je short L_00444ae0
    L_00444a84:
        mov edx,dword ptr [ebp+3ADA74h]
    L_00444a8a:
        mov eax,dword ptr [data_00491c30]
    L_00444a8f:
        mov ecx,dword ptr [eax]
    L_00444a91:
        push 14h
    L_00444a93:
        push 0
    L_00444a95:
        push edx
    L_00444a96:
        push 0
    L_00444a98:
        push eax
    L_00444a99:
        call dword ptr [ecx+190h]
    L_00444a9f:
        mov eax,dword ptr [data_00491c30]
    L_00444aa4:
        mov ecx,dword ptr [eax]
    L_00444aa6:
        push 102h
    L_00444aab:
        push eax
    L_00444aac:
        call dword ptr [ecx+164h]
    L_00444ab2:
        mov eax,dword ptr [data_00491c30]
    L_00444ab7:
        mov edx,dword ptr [eax]
    L_00444ab9:
        push 3
    L_00444abb:
        push 6
    L_00444abd:
        push 0
    L_00444abf:
        push eax
    L_00444ac0:
        call dword ptr [edx+10Ch]
    L_00444ac6:
        mov eax,dword ptr [data_00491c30]
    L_00444acb:
        mov ecx,dword ptr [eax]
    L_00444acd:
        push 3
    L_00444acf:
        push 3
    L_00444ad1:
        push 0
    L_00444ad3:
        push eax
    L_00444ad4:
        call dword ptr [ecx+10Ch]
    L_00444ada:
        mov byte ptr [ebp+3ADA6Ah],bl
    L_00444ae0:
        mov eax,dword ptr [data_00491c30]
    L_00444ae5:
        mov edx,dword ptr [eax]
    L_00444ae7:
        push ebx
    L_00444ae8:
        push 0
    L_00444aea:
        push 5
    L_00444aec:
        push eax
    L_00444aed:
        call dword ptr [edx+144h]
    L_00444af3:
        pop esi
    L_00444af4:
        pop ebp
    L_00444af5:
        xor eax,eax
    L_00444af7:
        pop ebx
    L_00444af8:
        add esp,0C0h
    L_00444afe:
        ret 4
    }
}
