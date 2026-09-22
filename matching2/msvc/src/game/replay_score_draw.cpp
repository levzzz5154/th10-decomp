// BLOCKED (D3801): closest_byte_count=0/689; first_diff=none (exact retail
// naked baseline; no readable candidate retained).
// residual_class=private EDI receiver, x87/date-field evaluation order,
// GameThread logger's variadic stack contract, and replay record layout.
// variants_tested=live Ghidra decompilation with caller xref 0x0042D282,
// logger/localtime callees, and typed replay-record candidate; exact MSVC
// 13.10 naked baseline probe=689/689.
// next_lever=native-LTCG cluster joining caller 0x0042D282, this helper,
// GameThread_AppendFormatted, localtime, and the replay record schema.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004329F0..0x00432CA0: FUN_004329f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004329f0_004329f0() {
    __asm {
    L_004329f0:
        push ebp
    L_004329f1:
        mov ebp,esp
    L_004329f3:
        and esp,0FFFFFFF8h
    L_004329f6:
        sub esp,20h
    L_004329f9:
        mov eax,dword ptr [edi+20h]
    L_004329fc:
        push ebx
    L_004329fd:
        sub eax,2
    L_00432a00:
        push esi
    L_00432a01:
        mov eax,1
    L_00432a06:
        jne asm_target_00432c9b
    L_00432a0c:
        mov esi,dword ptr [edi+0FCh]
    L_00432a12:
        mov ecx,dword ptr [data_004776e0]
    L_00432a18:
        mov dword ptr [ecx+8988h],eax
    L_00432a1e:
        mov edx,dword ptr [edi+1D4h]
    L_00432a24:
        test edx,edx
    L_00432a26:
        mov dword ptr [esp+1Ch],42400000h
    L_00432a2e:
        mov dword ptr [esp+20h],43200000h
    L_00432a36:
        mov dword ptr [esp+24h],0
    L_00432a3e:
        mov dword ptr [esp+18h],esi
    L_00432a42:
        jne asm_target_00432b8d
    L_00432a48:
        mov dword ptr [esp+0Ch],eax
    L_00432a4c:
        imul esi,0F0h
    L_00432a52:
        mov eax,0FFh
    L_00432a57:
        mov dword ptr [esp+10h],eax
    L_00432a5b:
        mov dword ptr [esp+14h],0Ah
    L_00432a63:
        jmp short L_00432a70
    L_00432a65:
        mov eax,dword ptr [esp+10h]
    L_00432a69:
        lea esp,[esp+force_disp32_zero]
    L_00432a70:
        mov edx,eax
    L_00432a72:
        shl edx,8
    L_00432a75:
        or edx,eax
    L_00432a77:
        shl edx,8
    L_00432a7a:
        or edx,0FF0000FFh
    L_00432a80:
        mov dword ptr [ecx+8974h],edx
    L_00432a86:
        mov eax,dword ptr [edi+24h]
    L_00432a89:
        mov edx,dword ptr [data_0047783c]
    L_00432a8f:
        imul eax,437Ch
    L_00432a95:
        lea ebx,[esi+eax]
    L_00432a98:
        cmp dword ptr [ebx+edx+28h],0
    L_00432a9d:
        je short L_00432b19
    L_00432a9f:
        lea eax,[eax+edx+8]
    L_00432aa3:
        lea eax,[esi+eax+20h]
    L_00432aa7:
        push eax
    L_00432aa8:
        call asm_localtime_00452baa
    L_00432aad:
        mov ecx,dword ptr [edi+24h]
    L_00432ab0:
        mov edx,dword ptr [data_0047783c]
    L_00432ab6:
        imul ecx,437Ch
    L_00432abc:
        add ecx,esi
    L_00432abe:
        add ecx,edx
    L_00432ac0:
        movsx edx,byte ptr [ecx+1Ch]
    L_00432ac4:
        fld dword ptr [ecx+2Ch]
    L_00432ac7:
        mov edx,dword ptr [edx*4+47471Ch]
    L_00432ace:
        push ecx
    L_00432acf:
        add ecx,1Eh
    L_00432ad2:
        lea ebx,[esp+24h]
    L_00432ad6:
        fstp qword ptr [esp]
    L_00432ad9:
        push edx
    L_00432ada:
        mov edx,dword ptr [eax+4]
    L_00432add:
        push edx
    L_00432ade:
        mov edx,dword ptr [eax+8]
    L_00432ae1:
        push edx
    L_00432ae2:
        mov edx,dword ptr [eax+0Ch]
    L_00432ae5:
        push edx
    L_00432ae6:
        mov edx,dword ptr [eax+10h]
    L_00432ae9:
        mov eax,dword ptr [eax+14h]
    L_00432aec:
        inc edx
    L_00432aed:
        push edx
    L_00432aee:
        movsx edx,byte ptr [ecx-1]
    L_00432af2:
        add eax,76Ch
    L_00432af7:
        push eax
    L_00432af8:
        mov eax,dword ptr [ecx-6]
    L_00432afb:
        push edx
    L_00432afc:
        mov edx,dword ptr [data_004776e0]
    L_00432b02:
        push eax
    L_00432b03:
        push ecx
    L_00432b04:
        mov ecx,dword ptr [esp+38h]
    L_00432b08:
        push ecx
    L_00432b09:
        push 46EE84h
    L_00432b0e:
        push edx
    L_00432b0f:
        call asm_GameThread_AppendFormatted_00401630
    L_00432b14:
        add esp,38h
    L_00432b17:
        jmp short L_00432b53
    L_00432b19:
        mov eax,dword ptr [edi+24h]
    L_00432b1c:
        imul eax,437Ch
    L_00432b22:
        add eax,esi
    L_00432b24:
        add eax,edx
    L_00432b26:
        movsx edx,byte ptr [eax+1Dh]
    L_00432b2a:
        fld dword ptr [eax+2Ch]
    L_00432b2d:
        sub esp,8
    L_00432b30:
        add eax,1Eh
    L_00432b33:
        lea ebx,[esp+24h]
    L_00432b37:
        fstp qword ptr [esp]
    L_00432b3a:
        push edx
    L_00432b3b:
        mov edx,dword ptr [eax-6]
    L_00432b3e:
        push edx
    L_00432b3f:
        push eax
    L_00432b40:
        mov eax,dword ptr [esp+20h]
    L_00432b44:
        push eax
    L_00432b45:
        push 46EE50h
    L_00432b4a:
        push ecx
    L_00432b4b:
        call asm_GameThread_AppendFormatted_00401630
    L_00432b50:
        add esp,20h
    L_00432b53:
        fld dword ptr [esp+20h]
    L_00432b57:
        mov edx,dword ptr [esp+10h]
    L_00432b5b:
        mov ecx,dword ptr [esp+0Ch]
    L_00432b5f:
        fadd dword ptr [data_00470c0c]
    L_00432b65:
        mov eax,dword ptr [esp+14h]
    L_00432b69:
        sub edx,10h
    L_00432b6c:
        add esi,18h
    L_00432b6f:
        fstp dword ptr [esp+20h]
    L_00432b73:
        inc ecx
    L_00432b74:
        dec eax
    L_00432b75:
        mov dword ptr [esp+0Ch],ecx
    L_00432b79:
        mov ecx,dword ptr [data_004776e0]
    L_00432b7f:
        mov dword ptr [esp+10h],edx
    L_00432b83:
        mov dword ptr [esp+14h],eax
    L_00432b87:
        jne asm_target_00432a65
    L_00432b8d:
        mov eax,dword ptr [data_0047783c]
    L_00432b92:
        or esi,0FFFFFFFFh
    L_00432b95:
        mov dword ptr [ecx+8974h],esi
    L_00432b9b:
        mov edx,dword ptr [edi+24h]
    L_00432b9e:
        imul edx,437Ch
    L_00432ba4:
        mov edx,dword ptr [edx+eax+4C8h]
    L_00432bab:
        push edx
    L_00432bac:
        push 46EE48h
    L_00432bb1:
        push ecx
    L_00432bb2:
        lea ebx,[esp+28h]
    L_00432bb6:
        mov dword ptr [esp+28h],43A40000h
    L_00432bbe:
        mov dword ptr [esp+2Ch],43BD0000h
    L_00432bc6:
        call asm_GameThread_AppendFormatted_00401630
    L_00432bcb:
        mov eax,dword ptr [edi+24h]
    L_00432bce:
        mov ecx,dword ptr [data_0047783c]
    L_00432bd4:
        imul eax,437Ch
    L_00432bda:
        mov ecx,dword ptr [eax+ecx+4CCh]
    L_00432be1:
        mov eax,88888889h
    L_00432be6:
        imul ecx
    L_00432be8:
        add edx,ecx
    L_00432bea:
        sar edx,5
    L_00432bed:
        mov eax,edx
    L_00432bef:
        shr eax,1Fh
    L_00432bf2:
        add eax,edx
    L_00432bf4:
        cdq
    L_00432bf5:
        mov ebx,3Ch
    L_00432bfa:
        idiv ebx
    L_00432bfc:
        mov eax,91A2B3C5h
    L_00432c01:
        mov dword ptr [esp+2Ch],43C60000h
    L_00432c09:
        push edx
    L_00432c0a:
        imul ecx
    L_00432c0c:
        add edx,ecx
    L_00432c0e:
        sar edx,0Bh
    L_00432c11:
        mov eax,edx
    L_00432c13:
        shr eax,1Fh
    L_00432c16:
        add eax,edx
    L_00432c18:
        cdq
    L_00432c19:
        idiv ebx
    L_00432c1b:
        mov eax,9B583739h
    L_00432c20:
        lea ebx,[esp+2Ch]
    L_00432c24:
        push edx
    L_00432c25:
        imul ecx
    L_00432c27:
        add edx,ecx
    L_00432c29:
        mov ecx,dword ptr [data_004776e0]
    L_00432c2f:
        sar edx,11h
    L_00432c32:
        mov eax,edx
    L_00432c34:
        shr eax,1Fh
    L_00432c37:
        add eax,edx
    L_00432c39:
        push eax
    L_00432c3a:
        push 46EE38h
    L_00432c3f:
        push ecx
    L_00432c40:
        call asm_GameThread_AppendFormatted_00401630
    L_00432c45:
        mov edx,dword ptr [edi+24h]
    L_00432c48:
        mov ebx,dword ptr [esp+38h]
    L_00432c4c:
        imul edx,10DFh
    L_00432c52:
        mov eax,dword ptr [data_0047783c]
    L_00432c57:
        add edx,ebx
    L_00432c59:
        mov ecx,dword ptr [eax+edx*4+4D0h]
    L_00432c60:
        mov edx,dword ptr [data_004776e0]
    L_00432c66:
        push ecx
    L_00432c67:
        push 46EE48h
    L_00432c6c:
        push edx
    L_00432c6d:
        lea ebx,[esp+48h]
    L_00432c71:
        mov dword ptr [esp+4Ch],43CF0000h
    L_00432c79:
        call asm_GameThread_AppendFormatted_00401630
    L_00432c7e:
        mov eax,dword ptr [data_004776e0]
    L_00432c83:
        mov dword ptr [eax+8974h],esi
    L_00432c89:
        mov dword ptr [eax+8988h],0
    L_00432c93:
        add esp,2Ch
    L_00432c96:
        mov eax,1
    L_00432c9b:
        pop esi
    L_00432c9c:
        pop ebx
    L_00432c9d:
        mov esp,ebp
    L_00432c9f:
        pop ebp
    L_00432ca0:
        ret
    }
}
