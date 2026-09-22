// BLOCKED (D3202): closest_byte_count=683/683; first_diff=none (retail
// assembly baseline only; no readable candidate retained).
// residual_class=private constructor/helper ABIs, ESI/EDI live-ins, SEH-like
// caller state, three timer record layouts, and the 2000-entry 0x7F0-stride
// sweep. Live Ghidra topology: sole caller 0x00415DB0 and callees
// 0x00449950, 0x00449870, 0x004489D0, 0x004491C0, 0x00408030, 0x0040E6A0.
// variants_tested=Ghidra complete decompilation, xrefs/callers/callees,
// disassembly, variable/storage audit, and legacy semantic constructor model;
// no compiler-readable candidate was byte-measured or retained.
// next_lever=schema2 native-LTCG cluster over 0x00410DDB -> 0x00415DB0 ->
// 0x00415B00 with explicit ESI/EDI live-ins, the three timer records, and
// verified AnimationManager/region-sweep layouts.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415B00..0x00415D48: FUN_00415b00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00415b00_00415b00() {
    __asm {
    L_00415b00:
        sub esp,0Ch
    L_00415b03:
        push ebp
    L_00415b04:
        mov ebp,dword ptr [esp+14h]
    L_00415b08:
        push esi
    L_00415b09:
        push edi
    L_00415b0a:
        mov edi,dword ptr [ebp+14h]
    L_00415b0d:
        mov eax,0FFFFFFFEh
    L_00415b12:
        and edi,eax
    L_00415b14:
        mov dword ptr [ebp+14h],edi
    L_00415b17:
        and dword ptr [ebp+28h],eax
    L_00415b1a:
        mov edx,dword ptr [ebp+3Ch]
    L_00415b1d:
        and edx,eax
    L_00415b1f:
        xor eax,eax
    L_00415b21:
        mov dword ptr [ebp+3Ch],edx
    L_00415b24:
        mov ecx,24h
    L_00415b29:
        mov edi,ebp
    L_00415b2b:
        rep stosd
    L_00415b2d:
        mov eax,dword ptr [ebp+14h]
    L_00415b30:
        xor edi,edi
    L_00415b32:
        test al,1
    L_00415b34:
        mov esi,0FFF0BDC1h
    L_00415b39:
        mov edx,476F78h
    L_00415b3e:
        jne short L_00415b52
    L_00415b40:
        or eax,1
    L_00415b43:
        mov dword ptr [ebp+8],edi
    L_00415b46:
        mov dword ptr [ebp+4],esi
    L_00415b49:
        mov dword ptr [ebp+0Ch],edi
    L_00415b4c:
        mov dword ptr [ebp+10h],edx
    L_00415b4f:
        mov dword ptr [ebp+14h],eax
    L_00415b52:
        or ecx,0FFFFFFFFh
    L_00415b55:
        mov dword ptr [ebp+8],edi
    L_00415b58:
        mov dword ptr [ebp+0Ch],edi
    L_00415b5b:
        mov dword ptr [ebp+4],ecx
    L_00415b5e:
        mov eax,dword ptr [ebp+28h]
    L_00415b61:
        test al,1
    L_00415b63:
        jne short L_00415b77
    L_00415b65:
        or eax,1
    L_00415b68:
        mov dword ptr [ebp+1Ch],edi
    L_00415b6b:
        mov dword ptr [ebp+18h],esi
    L_00415b6e:
        mov dword ptr [ebp+20h],edi
    L_00415b71:
        mov dword ptr [ebp+24h],edx
    L_00415b74:
        mov dword ptr [ebp+28h],eax
    L_00415b77:
        mov dword ptr [ebp+1Ch],edi
    L_00415b7a:
        mov dword ptr [ebp+20h],edi
    L_00415b7d:
        mov dword ptr [ebp+18h],ecx
    L_00415b80:
        mov dword ptr [ebp+58h],edi
    L_00415b83:
        mov eax,dword ptr [ebp+3Ch]
    L_00415b86:
        test al,1
    L_00415b88:
        jne short L_00415b9c
    L_00415b8a:
        or eax,1
    L_00415b8d:
        mov dword ptr [ebp+30h],edi
    L_00415b90:
        mov dword ptr [ebp+2Ch],esi
    L_00415b93:
        mov dword ptr [ebp+34h],edi
    L_00415b96:
        mov dword ptr [ebp+38h],edx
    L_00415b99:
        mov dword ptr [ebp+3Ch],eax
    L_00415b9c:
        mov eax,dword ptr [esp+20h]
    L_00415ba0:
        mov esi,dword ptr [data_00491c10]
    L_00415ba6:
        mov dword ptr [ebp+2Ch],ecx
    L_00415ba9:
        mov ecx,dword ptr [data_004776e0]
    L_00415baf:
        mov dword ptr [ebp+30h],edi
    L_00415bb2:
        mov dword ptr [ebp+34h],edi
    L_00415bb5:
        mov dword ptr [ebp+5Ch],eax
    L_00415bb8:
        mov edx,dword ptr [ecx+899Ch]
    L_00415bbe:
        push ebx
    L_00415bbf:
        mov dword ptr [esp+20h],edx
    L_00415bc3:
        call asm_FUN_00449950_00449950
    L_00415bc8:
        mov ecx,dword ptr [esp+20h]
    L_00415bcc:
        mov ebx,eax
    L_00415bce:
        mov eax,dword ptr [ebx+35Ch]
    L_00415bd4:
        push edi
    L_00415bd5:
        or eax,40000000h
    L_00415bda:
        push ebx
    L_00415bdb:
        mov dword ptr [ebx+20h],0Fh
    L_00415be2:
        mov dword ptr [ebx+35Ch],eax
    L_00415be8:
        call asm_FUN_00449870_00449870
    L_00415bed:
        mov esi,dword ptr [data_00491c10]
    L_00415bf3:
        lea eax,[esp+20h]
    L_00415bf7:
        mov edx,esi
    L_00415bf9:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00415bfe:
        mov eax,dword ptr [esp+20h]
    L_00415c02:
        mov ecx,dword ptr [data_004776e0]
    L_00415c08:
        mov dword ptr [ebp+4Ch],eax
    L_00415c0b:
        mov edx,dword ptr [ecx+899Ch]
    L_00415c11:
        mov dword ptr [esp+20h],edx
    L_00415c15:
        call asm_FUN_00449950_00449950
    L_00415c1a:
        mov ebx,eax
    L_00415c1c:
        mov ecx,dword ptr [ebx+35Ch]
    L_00415c22:
        or ecx,40000000h
    L_00415c28:
        push 1
    L_00415c2a:
        mov dword ptr [ebx+35Ch],ecx
    L_00415c30:
        mov ecx,dword ptr [esp+24h]
    L_00415c34:
        push ebx
    L_00415c35:
        mov dword ptr [ebx+20h],0Fh
    L_00415c3c:
        call asm_FUN_00449870_00449870
    L_00415c41:
        mov esi,dword ptr [data_00491c10]
    L_00415c47:
        lea eax,[esp+20h]
    L_00415c4b:
        mov edx,esi
    L_00415c4d:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00415c52:
        mov eax,dword ptr [esp+20h]
    L_00415c56:
        mov dword ptr [ebp+50h],eax
    L_00415c59:
        mov ecx,dword ptr [ebp+4Ch]
    L_00415c5c:
        push ecx
    L_00415c5d:
        mov edx,esi
    L_00415c5f:
        call asm_AnimationManager_Find_004491c0
    L_00415c64:
        cmp eax,edi
    L_00415c66:
        jne short L_00415c6b
    L_00415c68:
        mov dword ptr [ebp+4Ch],edi
    L_00415c6b:
        mov bl,10h
    L_00415c6d:
        mov byte ptr [eax+3A0h],bl
    L_00415c73:
        mov edx,dword ptr [ebp+4Ch]
    L_00415c76:
        push edx
    L_00415c77:
        mov edx,esi
    L_00415c79:
        call asm_AnimationManager_Find_004491c0
    L_00415c7e:
        cmp eax,edi
    L_00415c80:
        jne short L_00415c85
    L_00415c82:
        mov dword ptr [ebp+4Ch],edi
    L_00415c85:
        mov byte ptr [eax+3A1h],bl
    L_00415c8b:
        mov eax,dword ptr [ebp+50h]
    L_00415c8e:
        push eax
    L_00415c8f:
        mov edx,esi
    L_00415c91:
        call asm_AnimationManager_Find_004491c0
    L_00415c96:
        cmp eax,edi
    L_00415c98:
        jne short L_00415c9d
    L_00415c9a:
        mov dword ptr [ebp+50h],edi
    L_00415c9d:
        mov byte ptr [eax+3A0h],bl
    L_00415ca3:
        mov ecx,dword ptr [ebp+50h]
    L_00415ca6:
        push ecx
    L_00415ca7:
        mov edx,esi
    L_00415ca9:
        call asm_AnimationManager_Find_004491c0
    L_00415cae:
        cmp eax,edi
    L_00415cb0:
        jne short L_00415cb5
    L_00415cb2:
        mov dword ptr [ebp+50h],edi
    L_00415cb5:
        mov esi,dword ptr [data_004776f0]
    L_00415cbb:
        mov byte ptr [eax+3A1h],bl
    L_00415cc1:
        mov dword ptr [esp+10h],41000000h
    L_00415cc9:
        mov eax,dword ptr [esp+10h]
    L_00415ccd:
        lea edx,[ebp+60h]
    L_00415cd0:
        mov dword ptr [edx],eax
    L_00415cd2:
        mov dword ptr [esp+14h],0
    L_00415cda:
        mov ecx,dword ptr [esp+14h]
    L_00415cde:
        mov dword ptr [edx+4],ecx
    L_00415ce1:
        mov dword ptr [esp+18h],0
    L_00415ce9:
        mov eax,dword ptr [esp+18h]
    L_00415ced:
        mov dword ptr [edx+8],eax
    L_00415cf0:
        mov dword ptr [esp+10h],41C00000h
    L_00415cf8:
        mov edx,dword ptr [esp+10h]
    L_00415cfc:
        lea ecx,[ebp+6Ch]
    L_00415cff:
        mov dword ptr [ecx],edx
    L_00415d01:
        mov dword ptr [esp+14h],0
    L_00415d09:
        mov eax,dword ptr [esp+14h]
    L_00415d0d:
        mov dword ptr [esp+18h],0
    L_00415d15:
        mov edx,dword ptr [esp+18h]
    L_00415d19:
        mov dword ptr [ecx+4],eax
    L_00415d1c:
        mov dword ptr [ebp+80h],edi
    L_00415d22:
        mov dword ptr [ebp+88h],0F8F08Fh
    L_00415d2c:
        mov dword ptr [ebp+8Ch],8088FFh
    L_00415d36:
        mov dword ptr [ebp+84h],edi
    L_00415d3c:
        mov dword ptr [ecx+8],edx
    L_00415d3f:
        add esi,60h
    L_00415d42:
        mov ebx,7D0h
    L_00415d47:
        TH10_REL8(0xeb, 0x00415d47, VA_asm_FUN_00415b00_part_00415d50)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00415d50:
        mov ax,word ptr [esi+446h]
    L_00415d57:
        cmp ax,di
    L_00415d5a:
        je short L_00415d67
    L_00415d5c:
        cmp ax,3
    L_00415d60:
        je short L_00415d67
    L_00415d62:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_00415d67:
        add esi,7F0h
    L_00415d6d:
        dec ebx
    L_00415d6e:
        jne short L_00415d50
    L_00415d70:
        mov eax,dword ptr [data_0047781c]
    L_00415d75:
        mov ecx,dword ptr [eax+18h]
    L_00415d78:
        cmp ecx,edi
    L_00415d7a:
        pop ebx
    L_00415d7b:
        je short L_00415d95
    L_00415d7d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00415d80:
        cmp dword ptr [ecx+0Ch],1
    L_00415d84:
        mov esi,dword ptr [ecx+8]
    L_00415d87:
        je short L_00415d8f
    L_00415d89:
        mov edx,dword ptr [ecx]
    L_00415d8b:
        push edi
    L_00415d8c:
        call dword ptr [edx+14h]
    L_00415d8f:
        cmp esi,edi
    L_00415d91:
        mov ecx,esi
    L_00415d93:
        jne short L_00415d80
    L_00415d95:
        mov eax,dword ptr [data_00477704]
    L_00415d9a:
        push eax
    L_00415d9b:
        call asm_Enemy_DeathSweepRetail_0040e6a0
    L_00415da0:
        pop edi
    L_00415da1:
        pop esi
    L_00415da2:
        mov eax,ebp
    L_00415da4:
        pop ebp
    L_00415da5:
        add esp,0Ch
    L_00415da8:
        ret 8
    }
}
