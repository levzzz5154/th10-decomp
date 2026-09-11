#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004049A0..0x00404C4F: FUN_004049a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004049a0_004049a0() {
    __asm {
    L_004049a0:
        sub esp,0D4h
    L_004049a6:
        mov eax,dword ptr [ebx+84h]
    L_004049ac:
        push ebp
    L_004049ad:
        mov ebp,dword ptr [esp+0DCh]
    L_004049b4:
        push esi
    L_004049b5:
        xor esi,esi
    L_004049b7:
        cmp eax,esi
    L_004049b9:
        push edi
    L_004049ba:
        mov dword ptr [esp+0Ch],eax
    L_004049be:
        jle asm_target_00404a8f
    L_004049c4:
        mov edx,dword ptr [ebx+74h]
    L_004049c7:
        mov ecx,dword ptr [ebx+7Ch]
    L_004049ca:
        mov dword ptr [ebx+70h],edx
    L_004049cd:
        fld dword ptr [ecx]
    L_004049cf:
        fcomp dword ptr [data_00470b68]
    L_004049d5:
        fnstsw ax
    L_004049d7:
        test ah,41h
    L_004049da:
        jne short L_004049fd
    L_004049dc:
        fld dword ptr [ecx]
    L_004049de:
        fcomp dword ptr [data_00470b64]
    L_004049e4:
        fnstsw ax
    L_004049e6:
        test ah,5
    L_004049e9:
        jp short L_004049fd
    L_004049eb:
        fld dword ptr [ebx+78h]
    L_004049ee:
        inc edx
    L_004049ef:
        fadd dword ptr [data_00470afc]
    L_004049f5:
        mov dword ptr [ebx+74h],edx
    L_004049f8:
        fstp dword ptr [ebx+78h]
    L_004049fb:
        jmp short L_00404a0d
    L_004049fd:
        fld dword ptr [ecx]
    L_004049ff:
        fadd dword ptr [ebx+78h]
    L_00404a02:
        fst dword ptr [ebx+78h]
    L_00404a05:
        call asm_FUN_00463b2c_00463b2c
    L_00404a0a:
        mov dword ptr [ebx+74h],eax
    L_00404a0d:
        mov ecx,dword ptr [ebx+84h]
    L_00404a13:
        cmp dword ptr [ebx+74h],ecx
    L_00404a16:
        mov dword ptr [esp+0Ch],ecx
    L_00404a1a:
        jl short L_00404a8f
    L_00404a1c:
        mov eax,dword ptr [ebx+80h]
    L_00404a22:
        test al,1
    L_00404a24:
        mov dword ptr [esp+0Ch],ecx
    L_00404a28:
        jne short L_00404a47
    L_00404a2a:
        or eax,1
    L_00404a2d:
        mov dword ptr [ebx+74h],esi
    L_00404a30:
        mov dword ptr [ebx+70h],0FFF0BDC1h
    L_00404a37:
        mov dword ptr [ebx+78h],esi
    L_00404a3a:
        mov dword ptr [ebx+7Ch],476F78h
    L_00404a41:
        mov dword ptr [ebx+80h],eax
    L_00404a47:
        fild dword ptr [esp+0Ch]
    L_00404a4b:
        mov dword ptr [ebx+74h],ecx
    L_00404a4e:
        dec ecx
    L_00404a4f:
        mov dword ptr [ebx+70h],ecx
    L_00404a52:
        fstp dword ptr [ebx+78h]
    L_00404a55:
        mov eax,dword ptr [ebx+88h]
    L_00404a5b:
        mov ecx,7
    L_00404a60:
        cmp eax,ecx
    L_00404a62:
        mov dword ptr [ebx+84h],esi
    L_00404a68:
        mov edi,ebp
    L_00404a6a:
        mov eax,ebp
    L_00404a6c:
        je short L_00404a7f
    L_00404a6e:
        lea esi,[ebx+1Ch]
    L_00404a71:
        rep movsd
    L_00404a73:
        pop edi
    L_00404a74:
        pop esi
    L_00404a75:
        pop ebp
    L_00404a76:
        add esp,0D4h
    L_00404a7c:
        ret 4
    L_00404a7f:
        mov esi,ebx
    L_00404a81:
        rep movsd
    L_00404a83:
        pop edi
    L_00404a84:
        pop esi
    L_00404a85:
        pop ebp
    L_00404a86:
        add esp,0D4h
    L_00404a8c:
        ret 4
    L_00404a8f:
        mov eax,dword ptr [ebx+88h]
    L_00404a95:
        cmp eax,7
    L_00404a98:
        jne short L_00404ac6
    L_00404a9a:
        mov ecx,eax
    L_00404a9c:
        mov esi,ebx
    L_00404a9e:
        lea edi,[esp+1Ch]
    L_00404aa2:
        rep movsd
    L_00404aa4:
        lea eax,[ebx+1Ch]
    L_00404aa7:
        lea esi,[esp+38h]
    L_00404aab:
        lea ecx,[esp+1Ch]
    L_00404aaf:
        call asm_ParticleSeed_Combine_00404e10
    L_00404ab4:
        mov ecx,7
    L_00404ab9:
        mov esi,eax
    L_00404abb:
        mov edi,ebx
    L_00404abd:
        rep movsd
    L_00404abf:
        mov esi,ebx
    L_00404ac1:
        jmp asm_target_00404c39
    L_00404ac6:
        cmp eax,11h
    L_00404ac9:
        jne short L_00404b14
    L_00404acb:
        mov ecx,7
    L_00404ad0:
        mov esi,ebx
    L_00404ad2:
        lea edi,[esp+1Ch]
    L_00404ad6:
        rep movsd
    L_00404ad8:
        lea eax,[ebx+54h]
    L_00404adb:
        lea esi,[esp+38h]
    L_00404adf:
        lea ecx,[esp+1Ch]
    L_00404ae3:
        call asm_ParticleSeed_Combine_00404e10
    L_00404ae8:
        mov esi,eax
    L_00404aea:
        mov ecx,7
    L_00404aef:
        mov edi,ebx
    L_00404af1:
        rep movsd
    L_00404af3:
        lea edi,[ebx+54h]
    L_00404af6:
        lea eax,[ebx+1Ch]
    L_00404af9:
        lea esi,[esp+38h]
    L_00404afd:
        mov ecx,edi
    L_00404aff:
        call asm_ParticleSeed_Combine_00404e10
    L_00404b04:
        mov ecx,7
    L_00404b09:
        mov esi,eax
    L_00404b0b:
        rep movsd
    L_00404b0d:
        mov esi,ebx
    L_00404b0f:
        jmp asm_target_00404c39
    L_00404b14:
        cmp eax,8
    L_00404b17:
        fild dword ptr [esp+0Ch]
    L_00404b1b:
        jne asm_target_00404bfa
    L_00404b21:
        fdivr dword ptr [ebx+78h]
    L_00404b24:
        lea esi,[esp+38h]
    L_00404b28:
        fld st(0)
    L_00404b2a:
        fadd st,st(1)
    L_00404b2c:
        fld st(1)
    L_00404b2e:
        fsub dword ptr [data_00470afc]
    L_00404b34:
        fstp dword ptr [esp+0Ch]
    L_00404b38:
        fld dword ptr [data_00470afc]
    L_00404b3e:
        fadd st,st(1)
    L_00404b40:
        fmul dword ptr [esp+0Ch]
    L_00404b44:
        fmul dword ptr [esp+0Ch]
    L_00404b48:
        fstp dword ptr [esp+10h]
    L_00404b4c:
        fld dword ptr [data_00470bd4]
    L_00404b52:
        fsub st,st(1)
    L_00404b54:
        fmul st,st(2)
    L_00404b56:
        fmul st,st(2)
    L_00404b58:
        fstp dword ptr [esp+14h]
    L_00404b5c:
        fstp st(0)
    L_00404b5e:
        fld dword ptr [data_00470afc]
    L_00404b64:
        fsub st,st(1)
    L_00404b66:
        fld st(0)
    L_00404b68:
        fmul st,st(1)
    L_00404b6a:
        fmul st,st(2)
    L_00404b6c:
        fstp dword ptr [esp+18h]
    L_00404b70:
        fstp st(0)
    L_00404b72:
        fld dword ptr [esp+0Ch]
    L_00404b76:
        fmul st,st(1)
    L_00404b78:
        fmul st,st(1)
    L_00404b7a:
        fstp dword ptr [esp+0Ch]
    L_00404b7e:
        mov eax,dword ptr [esp+0Ch]
    L_00404b82:
        push eax
    L_00404b83:
        fstp st(0)
    L_00404b85:
        lea eax,[ebx+54h]
    L_00404b88:
        call asm_Recovery_ScaleColor_00404da0
    L_00404b8d:
        mov ecx,dword ptr [esp+18h]
    L_00404b91:
        mov edi,eax
    L_00404b93:
        push ecx
    L_00404b94:
        lea eax,[ebx+38h]
    L_00404b97:
        lea esi,[esp+20h]
    L_00404b9b:
        call asm_Recovery_ScaleColor_00404da0
    L_00404ba0:
        mov edx,dword ptr [esp+14h]
    L_00404ba4:
        mov dword ptr [esp+14h],eax
    L_00404ba8:
        push edx
    L_00404ba9:
        lea eax,[ebx+1Ch]
    L_00404bac:
        lea esi,[esp+0ACh]
    L_00404bb3:
        call asm_Recovery_ScaleColor_00404da0
    L_00404bb8:
        mov ecx,dword ptr [esp+10h]
    L_00404bbc:
        mov dword ptr [esp+10h],eax
    L_00404bc0:
        push ecx
    L_00404bc1:
        lea esi,[esp+0C8h]
    L_00404bc8:
        mov eax,ebx
    L_00404bca:
        call asm_Recovery_ScaleColor_00404da0
    L_00404bcf:
        mov ecx,eax
    L_00404bd1:
        mov eax,dword ptr [esp+10h]
    L_00404bd5:
        lea esi,[esp+54h]
    L_00404bd9:
        call asm_ParticleSeed_Combine_00404e10
    L_00404bde:
        mov ecx,eax
    L_00404be0:
        mov eax,dword ptr [esp+14h]
    L_00404be4:
        lea esi,[esp+8Ch]
    L_00404beb:
        call asm_ParticleSeed_Combine_00404e10
    L_00404bf0:
        mov ecx,eax
    L_00404bf2:
        mov eax,edi
    L_00404bf4:
        lea esi,[esp+70h]
    L_00404bf8:
        jmp short L_00404c32
    L_00404bfa:
        mov edx,dword ptr [ebx+78h]
    L_00404bfd:
        push ecx
    L_00404bfe:
        fstp dword ptr [esp]
    L_00404c01:
        push edx
    L_00404c02:
        call asm_FUN_0044c350_0044c350
    L_00404c07:
        fstp dword ptr [esp+10h]
    L_00404c0b:
        mov eax,dword ptr [esp+10h]
    L_00404c0f:
        push eax
    L_00404c10:
        lea ecx,[ebx+1Ch]
    L_00404c13:
        mov eax,ebx
    L_00404c15:
        lea esi,[esp+74h]
    L_00404c19:
        call asm_Vec_Subtract_00404d40
    L_00404c1e:
        lea esi,[esp+90h]
    L_00404c25:
        call asm_Recovery_ScaleColor_00404da0
    L_00404c2a:
        mov ecx,eax
    L_00404c2c:
        mov eax,ebx
    L_00404c2e:
        lea esi,[esp+54h]
    L_00404c32:
        call asm_ParticleSeed_Combine_00404e10
    L_00404c37:
        mov esi,eax
    L_00404c39:
        mov edi,ebp
    L_00404c3b:
        mov ecx,7
    L_00404c40:
        rep movsd
    L_00404c42:
        pop edi
    L_00404c43:
        pop esi
    L_00404c44:
        mov eax,ebp
    L_00404c46:
        pop ebp
    L_00404c47:
        add esp,0D4h
    L_00404c4d:
        ret 4
    }
}
