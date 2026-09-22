// BLOCKED (D3806): closest_byte_count=0/825; first_diff=0x00431ba0;
// residual_class=record-array layout and the private GameThread formatting
// receiver/localtime call edges; the Ghidra body is behaviorally clear but
// its logger and time conversion dependencies remain asm-owned.
// variants_tested=retail assembly baseline (825/825 exact), live-Ghidra
// decompilation, and a disposable schema-2 ownership probe; load_cluster
// rejected the proposed semantic classification because this exclusive
// region is still kind asm, before native-LTCG compilation.
// next_lever=caller-inclusive schema-2/native-LTCG cluster over the browser
// entry, AppendFormattedGameThreadRecord, localtime, and the record-layout
// owners, then compare the complete 825-byte contribution.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00431BA0..0x00431ED8: FUN_00431ba0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00431ba0_00431ba0() {
    __asm {
    L_00431ba0:
        sub esp,0Ch
    L_00431ba3:
        push ebx
    L_00431ba4:
        push ebp
    L_00431ba5:
        mov ebp,dword ptr [esp+18h]
    L_00431ba9:
        mov eax,dword ptr [ebp+20h]
    L_00431bac:
        sub eax,2
    L_00431baf:
        push esi
    L_00431bb0:
        push edi
    L_00431bb1:
        je asm_target_00431d9d
    L_00431bb7:
        sub eax,2
    L_00431bba:
        jne asm_target_00431eca
    L_00431bc0:
        mov eax,dword ptr [ebp+59DCh]
    L_00431bc6:
        mov ecx,dword ptr [ebp+eax*4+59E4h]
    L_00431bcd:
        mov edi,dword ptr [ecx+18h]
    L_00431bd0:
        mov ecx,dword ptr [ebp+2B4h]
    L_00431bd6:
        mov esi,0Ah
    L_00431bdb:
        cmp ecx,esi
    L_00431bdd:
        mov dword ptr [esp+10h],42A00000h
    L_00431be5:
        mov dword ptr [esp+14h],42A00000h
    L_00431bed:
        mov dword ptr [esp+18h],0
    L_00431bf5:
        jge short L_00431c1e
    L_00431bf7:
        fld dword ptr [data_00470c1c]
    L_00431bfd:
        imul eax,0Fh
    L_00431c00:
        fsub dword ptr [ebp+2B8h]
    L_00431c06:
        mov dword ptr [esp+20h],eax
    L_00431c0a:
        fimul dword ptr [esp+20h]
    L_00431c0e:
        fmul dword ptr [data_00470c18]
    L_00431c14:
        fadd dword ptr [data_00470c28]
    L_00431c1a:
        fstp dword ptr [esp+14h]
    L_00431c1e:
        mov edx,dword ptr [data_004776e0]
    L_00431c24:
        lea eax,[edi+0Ch]
    L_00431c27:
        push eax
    L_00431c28:
        mov dword ptr [edx+8988h],1
    L_00431c32:
        call asm_localtime_00452baa
    L_00431c37:
        fld dword ptr [edi+48h]
    L_00431c3a:
        push ecx
    L_00431c3b:
        mov ecx,dword ptr [edi+5Ch]
    L_00431c3e:
        fstp qword ptr [esp]
    L_00431c41:
        mov edx,dword ptr [ecx*4+474744h]
    L_00431c48:
        mov ecx,dword ptr [edi+58h]
    L_00431c4b:
        push edx
    L_00431c4c:
        mov edx,dword ptr [ecx*4+4746F4h]
    L_00431c53:
        mov ecx,dword ptr [edi+50h]
    L_00431c56:
        push edx
    L_00431c57:
        mov edx,dword ptr [edi+54h]
    L_00431c5a:
        lea ecx,[ecx+ecx*2]
    L_00431c5d:
        add ecx,edx
    L_00431c5f:
        mov edx,dword ptr [ecx*4+4746DCh]
    L_00431c66:
        mov ecx,dword ptr [eax+4]
    L_00431c69:
        push edx
    L_00431c6a:
        mov edx,dword ptr [eax+8]
    L_00431c6d:
        push ecx
    L_00431c6e:
        mov ecx,dword ptr [eax+0Ch]
    L_00431c71:
        push edx
    L_00431c72:
        mov edx,dword ptr [eax+10h]
    L_00431c75:
        mov eax,dword ptr [eax+14h]
    L_00431c78:
        push ecx
    L_00431c79:
        inc edx
    L_00431c7a:
        push edx
    L_00431c7b:
        cdq
    L_00431c7c:
        mov ecx,64h
    L_00431c81:
        idiv ecx
    L_00431c83:
        mov eax,dword ptr [data_004776e0]
    L_00431c88:
        lea ebx,[esp+34h]
    L_00431c8c:
        push edx
    L_00431c8d:
        mov edx,dword ptr [ebp+59DCh]
    L_00431c93:
        push edi
    L_00431c94:
        inc edx
    L_00431c95:
        push edx
    L_00431c96:
        push 46EFB0h
    L_00431c9b:
        push eax
    L_00431c9c:
        call asm_GameThread_AppendFormatted_00401630
    L_00431ca1:
        mov eax,dword ptr [ebp+2B4h]
    L_00431ca7:
        add esp,38h
    L_00431caa:
        cmp eax,esi
    L_00431cac:
        jl asm_target_00431eb1
    L_00431cb2:
        mov dword ptr [esp+10h],435C0000h
    L_00431cba:
        mov dword ptr [esp+14h],43000000h
    L_00431cc2:
        mov esi,1
    L_00431cc7:
        mov dword ptr [esp+20h],24h
    L_00431ccf:
        nop
    L_00431cd0:
        mov ebx,dword ptr [ebp+24h]
    L_00431cd3:
        xor edx,edx
    L_00431cd5:
        lea ecx,[esi-1]
    L_00431cd8:
        cmp ebx,ecx
    L_00431cda:
        mov ecx,dword ptr [data_004776e0]
    L_00431ce0:
        setne dl
    L_00431ce3:
        dec edx
    L_00431ce4:
        and edx,7F7E80h
    L_00431cea:
        add edx,0FF808080h
    L_00431cf0:
        mov dword ptr [ecx+8974h],edx
    L_00431cf6:
        mov eax,dword ptr [ebp+59DCh]
    L_00431cfc:
        mov edx,dword ptr [ebp+eax*4+59E4h]
    L_00431d03:
        mov eax,dword ptr [esp+20h]
    L_00431d07:
        add eax,edx
    L_00431d09:
        mov edx,dword ptr [eax+0B0h]
    L_00431d0f:
        test edx,edx
    L_00431d11:
        jne short L_00431d2f
    L_00431d13:
        mov edx,dword ptr [esi*4+47471Ch]
    L_00431d1a:
        push edx
    L_00431d1b:
        push 46F008h
    L_00431d20:
        push ecx
    L_00431d21:
        lea ebx,[esp+1Ch]
    L_00431d25:
        call asm_GameThread_AppendFormatted_00401630
    L_00431d2a:
        add esp,0Ch
    L_00431d2d:
        jmp short L_00431d75
    L_00431d2f:
        cmp esi,6
    L_00431d32:
        jge short L_00431d53
    L_00431d34:
        mov eax,dword ptr [eax+0D4h]
    L_00431d3a:
        test eax,eax
    L_00431d3c:
        je short L_00431d53
    L_00431d3e:
        mov edx,dword ptr [eax+1B4h]
    L_00431d44:
        mov eax,dword ptr [eax+0Ch]
    L_00431d47:
        push edx
    L_00431d48:
        mov edx,dword ptr [esi*4+47471Ch]
    L_00431d4f:
        push eax
    L_00431d50:
        push edx
    L_00431d51:
        jmp short L_00431d63
    L_00431d53:
        mov eax,dword ptr [edi+60h]
    L_00431d56:
        mov edx,dword ptr [edi+10h]
    L_00431d59:
        push eax
    L_00431d5a:
        mov eax,dword ptr [esi*4+47471Ch]
    L_00431d61:
        push edx
    L_00431d62:
        push eax
    L_00431d63:
        push 46EF68h
    L_00431d68:
        lea ebx,[esp+20h]
    L_00431d6c:
        push ecx
    L_00431d6d:
        call asm_GameThread_AppendFormatted_00401630
    L_00431d72:
        add esp,14h
    L_00431d75:
        fld dword ptr [esp+14h]
    L_00431d79:
        mov ecx,dword ptr [esp+20h]
    L_00431d7d:
        fadd dword ptr [data_00470c0c]
    L_00431d83:
        inc esi
    L_00431d84:
        add ecx,24h
    L_00431d87:
        cmp esi,8
    L_00431d8a:
        fstp dword ptr [esp+14h]
    L_00431d8e:
        mov dword ptr [esp+20h],ecx
    L_00431d92:
        jl asm_target_00431cd0
    L_00431d98:
        jmp asm_target_00431eb1
    L_00431d9d:
        mov ecx,dword ptr [data_004776e0]
    L_00431da3:
        lea edx,[ebp+59E4h]
    L_00431da9:
        mov dword ptr [esp+10h],42680000h
    L_00431db1:
        mov dword ptr [esp+14h],42A00000h
    L_00431db9:
        mov dword ptr [esp+18h],0
    L_00431dc1:
        mov dword ptr [ecx+8988h],1
    L_00431dcb:
        xor edi,edi
    L_00431dcd:
        mov dword ptr [esp+20h],edx
    L_00431dd1:
        jmp short L_00431de0
    L_00431dd3:
        mov ecx,dword ptr [data_004776e0]
    L_00431dd9:
        lea esp,[esp+force_disp32_zero]
    L_00431de0:
        mov esi,dword ptr [ebp+24h]
    L_00431de3:
        mov edx,dword ptr [esp+20h]
    L_00431de7:
        xor eax,eax
    L_00431de9:
        cmp esi,edi
    L_00431deb:
        setne al
    L_00431dee:
        dec eax
    L_00431def:
        and eax,7F7E80h
    L_00431df4:
        add eax,0FF808080h
    L_00431df9:
        mov dword ptr [ecx+8974h],eax
    L_00431dff:
        mov eax,dword ptr [edx]
    L_00431e01:
        test eax,eax
    L_00431e03:
        je short L_00431e7b
    L_00431e05:
        mov esi,dword ptr [eax+18h]
    L_00431e08:
        lea eax,[esi+0Ch]
    L_00431e0b:
        push eax
    L_00431e0c:
        call asm_localtime_00452baa
    L_00431e11:
        fld dword ptr [esi+48h]
    L_00431e14:
        push ecx
    L_00431e15:
        mov ecx,dword ptr [esi+5Ch]
    L_00431e18:
        fstp qword ptr [esp]
    L_00431e1b:
        mov edx,dword ptr [ecx*4+474744h]
    L_00431e22:
        mov ecx,dword ptr [esi+58h]
    L_00431e25:
        push edx
    L_00431e26:
        mov edx,dword ptr [ecx*4+4746F4h]
    L_00431e2d:
        mov ecx,dword ptr [esi+50h]
    L_00431e30:
        push edx
    L_00431e31:
        mov edx,dword ptr [esi+54h]
    L_00431e34:
        lea ecx,[ecx+ecx*2]
    L_00431e37:
        add ecx,edx
    L_00431e39:
        mov edx,dword ptr [ecx*4+4746DCh]
    L_00431e40:
        mov ecx,dword ptr [eax+4]
    L_00431e43:
        push edx
    L_00431e44:
        mov edx,dword ptr [eax+8]
    L_00431e47:
        push ecx
    L_00431e48:
        mov ecx,dword ptr [eax+0Ch]
    L_00431e4b:
        push edx
    L_00431e4c:
        mov edx,dword ptr [eax+10h]
    L_00431e4f:
        mov eax,dword ptr [eax+14h]
    L_00431e52:
        push ecx
    L_00431e53:
        inc edi
    L_00431e54:
        inc edx
    L_00431e55:
        push edx
    L_00431e56:
        cdq
    L_00431e57:
        mov ecx,64h
    L_00431e5c:
        idiv ecx
    L_00431e5e:
        lea ebx,[esp+34h]
    L_00431e62:
        push edx
    L_00431e63:
        mov edx,dword ptr [data_004776e0]
    L_00431e69:
        push esi
    L_00431e6a:
        push edi
    L_00431e6b:
        push 46EFB0h
    L_00431e70:
        push edx
    L_00431e71:
        call asm_GameThread_AppendFormatted_00401630
    L_00431e76:
        add esp,38h
    L_00431e79:
        jmp short L_00431e8f
    L_00431e7b:
        inc edi
    L_00431e7c:
        push edi
    L_00431e7d:
        push 46EF74h
    L_00431e82:
        push ecx
    L_00431e83:
        lea ebx,[esp+1Ch]
    L_00431e87:
        call asm_GameThread_AppendFormatted_00401630
    L_00431e8c:
        add esp,0Ch
    L_00431e8f:
        fld dword ptr [esp+14h]
    L_00431e93:
        mov ecx,dword ptr [esp+20h]
    L_00431e97:
        fadd dword ptr [data_00470c08]
    L_00431e9d:
        add ecx,4
    L_00431ea0:
        cmp edi,19h
    L_00431ea3:
        mov dword ptr [esp+20h],ecx
    L_00431ea7:
        fstp dword ptr [esp+14h]
    L_00431eab:
        jl asm_target_00431dd3
    L_00431eb1:
        mov eax,dword ptr [data_004776e0]
    L_00431eb6:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_00431ec0:
        mov dword ptr [eax+8988h],0
    L_00431eca:
        pop edi
    L_00431ecb:
        pop esi
    L_00431ecc:
        pop ebp
    L_00431ecd:
        mov eax,1
    L_00431ed2:
        pop ebx
    L_00431ed3:
        add esp,0Ch
    L_00431ed6:
        ret 4
    }
}
