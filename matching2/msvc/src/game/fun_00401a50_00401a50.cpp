#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401000..0x004010FA: GameThread_ConstructOverlay
// Naked body preserves the retail register/stack ABI.

// 0x00401A50..0x00401C89: FUN_00401a50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401a50_00401a50() {
    __asm {
    L_00401a50:
        sub esp,10h
    L_00401a53:
        mov eax,dword ptr [ebx+370h]
    L_00401a59:
        and eax,0FFD7FFFFh
    L_00401a5e:
        or eax,140001h
    L_00401a63:
        push ebp
    L_00401a64:
        mov dword ptr [ebx+370h],eax
    L_00401a6a:
        mov eax,dword ptr [ebx+8970h]
    L_00401a70:
        test eax,eax
    L_00401a72:
        push esi
    L_00401a73:
        push edi
    L_00401a74:
        mov dword ptr [esp+0Ch],1
    L_00401a7c:
        lea ebp,[ebx+6F6Ch]
    L_00401a82:
        mov dword ptr [esp+18h],0
    L_00401a8a:
        jle asm_target_00401c37
    L_00401a90:
        lea eax,[ebp+40h]
    L_00401a93:
        mov ecx,eax
    L_00401a95:
        mov edx,dword ptr [ecx]
    L_00401a97:
        lea eax,[ebx+348h]
    L_00401a9d:
        mov dword ptr [eax],edx
    L_00401a9f:
        mov edx,dword ptr [ecx+4]
    L_00401aa2:
        mov dword ptr [eax+4],edx
    L_00401aa5:
        mov ecx,dword ptr [ecx+8]
    L_00401aa8:
        mov dword ptr [eax+8],ecx
    L_00401aab:
        fld dword ptr [ebp+54h]
    L_00401aae:
        mov edx,dword ptr [ebp+50h]
    L_00401ab1:
        fstp dword ptr [ebx+54h]
    L_00401ab4:
        mov ecx,dword ptr [esp+0Ch]
    L_00401ab8:
        mov dword ptr [ebx+50h],edx
    L_00401abb:
        mov edx,dword ptr [ebx+370h]
    L_00401ac1:
        or edx,8
    L_00401ac4:
        mov dword ptr [ebx+370h],edx
    L_00401aca:
        fild dword ptr [ebx+898Ch]
    L_00401ad0:
        mov eax,dword ptr [ebp+5Ch]
    L_00401ad3:
        cmp ecx,eax
    L_00401ad5:
        fmul dword ptr [ebp+50h]
    L_00401ad8:
        mov edi,ebp
    L_00401ada:
        mov dword ptr [esp+10h],edi
    L_00401ade:
        fstp dword ptr [esp+14h]
    L_00401ae2:
        je asm_target_00401b6d
    L_00401ae8:
        mov esi,dword ptr [data_00491c10]
    L_00401aee:
        mov edi,eax
    L_00401af0:
        mov dword ptr [esp+0Ch],edi
    L_00401af4:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00401af9:
        test edi,edi
    L_00401afb:
        je short L_00401b34
    L_00401afd:
        mov edi,491D7Ch
    L_00401b02:
        mov dword ptr [data_00491fac],edi
    L_00401b08:
        call asm_FUN_004215a0_004215a0
    L_00401b0d:
        mov edx,dword ptr [data_00491fac]
    L_00401b13:
        mov eax,dword ptr [data_00491c30]
    L_00401b18:
        mov ecx,dword ptr [eax]
    L_00401b1a:
        add edx,0CCh
    L_00401b20:
        push edx
    L_00401b21:
        push eax
    L_00401b22:
        call dword ptr [ecx+0BCh]
    L_00401b28:
        mov dword ptr [data_00491fb0],0
    L_00401b32:
        jmp short L_00401b69
    L_00401b34:
        mov edi,491E94h
    L_00401b39:
        mov dword ptr [data_00491fac],edi
    L_00401b3f:
        call asm_FUN_004215a0_004215a0
    L_00401b44:
        mov edx,dword ptr [data_00491fac]
    L_00401b4a:
        mov eax,dword ptr [data_00491c30]
    L_00401b4f:
        mov ecx,dword ptr [eax]
    L_00401b51:
        add edx,0CCh
    L_00401b57:
        push edx
    L_00401b58:
        push eax
    L_00401b59:
        call dword ptr [ecx+0BCh]
    L_00401b5f:
        mov dword ptr [data_00491fb0],1
    L_00401b69:
        mov edi,dword ptr [esp+10h]
    L_00401b6d:
        cmp byte ptr [ebp],0
    L_00401b71:
        je asm_target_00401c15
    L_00401b77:
        mov al,byte ptr [edi]
    L_00401b79:
        cmp al,0Ah
    L_00401b7b:
        jne short L_00401b9d
    L_00401b7d:
        fld dword ptr [ebp+54h]
    L_00401b80:
        fmul dword ptr [data_00470c88]
    L_00401b86:
        fadd dword ptr [ebx+34Ch]
    L_00401b8c:
        fstp dword ptr [ebx+34Ch]
    L_00401b92:
        mov eax,dword ptr [ebp+40h]
    L_00401b95:
        mov dword ptr [ebx+348h],eax
    L_00401b9b:
        jmp short L_00401c09
    L_00401b9d:
        cmp al,20h
    L_00401b9f:
        je short L_00401bf9
    L_00401ba1:
        mov edx,dword ptr [ebx+8994h]
    L_00401ba7:
        fld dword ptr [data_00470afc]
    L_00401bad:
        fld dword ptr [ebx+50h]
    L_00401bb0:
        movzx ecx,al
    L_00401bb3:
        mov eax,dword ptr [edx+118h]
    L_00401bb9:
        fucompp
    L_00401bbb:
        sub ecx,20h
    L_00401bbe:
        imul ecx,44h
    L_00401bc1:
        add ecx,eax
    L_00401bc3:
        mov dword ptr [ebx+3A8h],ecx
    L_00401bc9:
        mov eax,dword ptr [ebp+4Ch]
    L_00401bcc:
        mov dword ptr [ebx+310h],eax
    L_00401bd2:
        fnstsw ax
    L_00401bd4:
        test ah,44h
    L_00401bd7:
        jnp short L_00401bea
    L_00401bd9:
        mov ecx,dword ptr [data_00491c10]
    L_00401bdf:
        push ecx
    L_00401be0:
        lea eax,[ebx+14h]
    L_00401be3:
        call asm_FUN_00443290_00443290
    L_00401be8:
        jmp short L_00401bf9
    L_00401bea:
        mov edx,dword ptr [data_00491c10]
    L_00401bf0:
        push edx
    L_00401bf1:
        lea esi,[ebx+14h]
    L_00401bf4:
        call asm_FUN_00443080_00443080
    L_00401bf9:
        fld dword ptr [esp+14h]
    L_00401bfd:
        fadd dword ptr [ebx+348h]
    L_00401c03:
        fstp dword ptr [ebx+348h]
    L_00401c09:
        mov al,byte ptr [edi+1]
    L_00401c0c:
        inc edi
    L_00401c0d:
        test al,al
    L_00401c0f:
        jne asm_target_00401b77
    L_00401c15:
        mov eax,dword ptr [esp+18h]
    L_00401c19:
        mov ecx,dword ptr [ebx+8970h]
    L_00401c1f:
        inc eax
    L_00401c20:
        add ebp,68h
    L_00401c23:
        cmp eax,ecx
    L_00401c25:
        mov dword ptr [esp+18h],eax
    L_00401c29:
        jl asm_target_00401a90
    L_00401c2f:
        mov eax,dword ptr [esp+0Ch]
    L_00401c33:
        test eax,eax
    L_00401c35:
        je short L_00401c7e
    L_00401c37:
        mov esi,dword ptr [data_00491c10]
    L_00401c3d:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00401c42:
        mov edi,491E94h
    L_00401c47:
        mov dword ptr [data_00491fac],edi
    L_00401c4d:
        call asm_FUN_004215a0_004215a0
    L_00401c52:
        mov edx,dword ptr [data_00491fac]
    L_00401c58:
        mov eax,dword ptr [data_00491c30]
    L_00401c5d:
        mov ecx,dword ptr [eax]
    L_00401c5f:
        add edx,0CCh
    L_00401c65:
        push edx
    L_00401c66:
        push eax
    L_00401c67:
        call dword ptr [ecx+0BCh]
    L_00401c6d:
        pop edi
    L_00401c6e:
        mov eax,1
    L_00401c73:
        pop esi
    L_00401c74:
        mov dword ptr [data_00491fb0],eax
    L_00401c79:
        pop ebp
    L_00401c7a:
        add esp,10h
    L_00401c7d:
        ret
    L_00401c7e:
        pop edi
    L_00401c7f:
        pop esi
    L_00401c80:
        mov eax,1
    L_00401c85:
        pop ebp
    L_00401c86:
        add esp,10h
    L_00401c89:
        ret
    }
}
