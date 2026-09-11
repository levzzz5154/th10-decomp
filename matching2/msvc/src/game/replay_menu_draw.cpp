#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00433B30..0x00433D08: FUN_00433b30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00433b30_00433b30() {
    __asm {
    L_00433b30:
        sub esp,10h
    L_00433b33:
        push ebx
    L_00433b34:
        push ebp
    L_00433b35:
        push esi
    L_00433b36:
        mov esi,dword ptr [esp+20h]
    L_00433b3a:
        mov eax,dword ptr [esi+20h]
    L_00433b3d:
        sub eax,2
    L_00433b40:
        push edi
    L_00433b41:
        je asm_target_00433dbf
    L_00433b47:
        dec eax
    L_00433b48:
        jne asm_target_00433edc
    L_00433b4e:
        mov eax,dword ptr [esi+2B4h]
    L_00433b54:
        mov edi,dword ptr [esi+59DCh]
    L_00433b5a:
        mov ebp,0Ah
    L_00433b5f:
        cmp eax,ebp
    L_00433b61:
        mov dword ptr [esp+14h],42680000h
    L_00433b69:
        mov dword ptr [esp+18h],43700000h
    L_00433b71:
        mov dword ptr [esp+1Ch],0
    L_00433b79:
        jge short L_00433baf
    L_00433b7b:
        fld dword ptr [data_00470c1c]
    L_00433b81:
        mov eax,edi
    L_00433b83:
        fsub dword ptr [esi+2B8h]
    L_00433b89:
        imul eax,0Fh
    L_00433b8c:
        add eax,50h
    L_00433b8f:
        mov dword ptr [esp+10h],eax
    L_00433b93:
        fild dword ptr [esp+10h]
    L_00433b97:
        fsub dword ptr [data_00470bfc]
    L_00433b9d:
        fmulp st(1),st
    L_00433b9f:
        fmul dword ptr [data_00470c18]
    L_00433ba5:
        fadd dword ptr [data_00470bfc]
    L_00433bab:
        fstp dword ptr [esp+18h]
    L_00433baf:
        mov ecx,dword ptr [data_00477838]
    L_00433bb5:
        mov esi,dword ptr [ecx+18h]
    L_00433bb8:
        lea edx,[esi+0Ch]
    L_00433bbb:
        push edx
    L_00433bbc:
        call asm_localtime_00452baa
    L_00433bc1:
        fld dword ptr [esi+48h]
    L_00433bc4:
        mov edx,dword ptr [esi+58h]
    L_00433bc7:
        push ecx
    L_00433bc8:
        mov ecx,dword ptr [data_00474764]
    L_00433bce:
        fstp qword ptr [esp]
    L_00433bd1:
        push ecx
    L_00433bd2:
        mov ecx,dword ptr [edx*4+4746F4h]
    L_00433bd9:
        push ecx
    L_00433bda:
        mov ecx,dword ptr [esi+50h]
    L_00433bdd:
        lea edx,[ecx+ecx*2]
    L_00433be0:
        add edx,dword ptr [esi+54h]
    L_00433be3:
        mov ecx,dword ptr [edx*4+4746DCh]
    L_00433bea:
        mov edx,dword ptr [eax+4]
    L_00433bed:
        push ecx
    L_00433bee:
        mov ecx,dword ptr [eax+8]
    L_00433bf1:
        push edx
    L_00433bf2:
        mov edx,dword ptr [eax+0Ch]
    L_00433bf5:
        push ecx
    L_00433bf6:
        mov ecx,dword ptr [eax+10h]
    L_00433bf9:
        mov eax,dword ptr [eax+14h]
    L_00433bfc:
        push edx
    L_00433bfd:
        inc ecx
    L_00433bfe:
        push ecx
    L_00433bff:
        cdq
    L_00433c00:
        mov ecx,64h
    L_00433c05:
        idiv ecx
    L_00433c07:
        inc edi
    L_00433c08:
        lea ebx,[esp+38h]
    L_00433c0c:
        push edx
    L_00433c0d:
        mov edx,dword ptr [data_004776e0]
    L_00433c13:
        push 46E354h
    L_00433c18:
        push edi
    L_00433c19:
        push 46EFB0h
    L_00433c1e:
        push edx
    L_00433c1f:
        call asm_GameThread_AppendFormatted_00401630
    L_00433c24:
        mov edi,dword ptr [esp+5Ch]
    L_00433c28:
        mov eax,dword ptr [edi+2B4h]
    L_00433c2e:
        add esp,38h
    L_00433c31:
        cmp eax,ebp
    L_00433c33:
        jl asm_target_00433ec3
    L_00433c39:
        mov eax,dword ptr [data_004746d8]
    L_00433c3e:
        lea edx,[eax+1]
    L_00433c41:
        mov cl,byte ptr [eax]
    L_00433c43:
        inc eax
    L_00433c44:
        test cl,cl
    L_00433c46:
        jne short L_00433c41
    L_00433c48:
        sub eax,edx
    L_00433c4a:
        lea ecx,[edi+58DCh]
    L_00433c50:
        push ecx
    L_00433c51:
        mov ebp,eax
    L_00433c53:
        mov eax,dword ptr [data_004776e0]
    L_00433c58:
        push 46E1C8h
    L_00433c5d:
        or esi,0FFFFFFFFh
    L_00433c60:
        push eax
    L_00433c61:
        lea ebx,[esp+20h]
    L_00433c65:
        mov dword ptr [esp+20h],42E00000h
    L_00433c6d:
        mov dword ptr [esp+24h],43700000h
    L_00433c75:
        mov dword ptr [esp+28h],0
    L_00433c7d:
        mov dword ptr [eax+8974h],esi
    L_00433c83:
        call asm_GameThread_AppendFormatted_00401630
    L_00433c88:
        mov eax,dword ptr [edi+58E8h]
    L_00433c8e:
        lea edx,[eax+eax*8]
    L_00433c91:
        mov dword ptr [esp+30h],edx
    L_00433c95:
        fild dword ptr [esp+30h]
    L_00433c99:
        add esp,0Ch
    L_00433c9c:
        cmp eax,8
    L_00433c9f:
        fadd dword ptr [data_00470c14]
    L_00433ca5:
        fstp dword ptr [esp+14h]
    L_00433ca9:
        jne short L_00433cb9
    L_00433cab:
        fld dword ptr [esp+14h]
    L_00433caf:
        fsub dword ptr [data_00470c10]
    L_00433cb5:
        fstp dword ptr [esp+14h]
    L_00433cb9:
        mov eax,dword ptr [data_004776e0]
    L_00433cbe:
        push 46E1C4h
    L_00433cc3:
        push eax
    L_00433cc4:
        lea ebx,[esp+1Ch]
    L_00433cc8:
        mov dword ptr [eax+8974h],0FFFFFF00h
    L_00433cd2:
        call asm_GameThread_AppendFormatted_00401630
    L_00433cd7:
        mov eax,dword ptr [data_004776e0]
    L_00433cdc:
        mov dword ptr [eax+8974h],esi
    L_00433ce2:
        add esp,8
    L_00433ce5:
        xor esi,esi
    L_00433ce7:
        test ebp,ebp
    L_00433ce9:
        mov dword ptr [esp+14h],43540000h
    L_00433cf1:
        mov dword ptr [esp+18h],43B40000h
    L_00433cf9:
        mov dword ptr [esp+1Ch],0
    L_00433d01:
        jle asm_target_00433db0
    L_00433d07:
        TH10_REL8(0xeb, 0x00433d07, VA_asm_FUN_00433b30_part_00433d10)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00433d10:
        mov edx,dword ptr [edi+58F4h]
    L_00433d16:
        xor ecx,ecx
    L_00433d18:
        cmp edx,esi
    L_00433d1a:
        setne cl
    L_00433d1d:
        dec ecx
    L_00433d1e:
        and ecx,7F7E80h
    L_00433d24:
        add ecx,0FF808080h
    L_00433d2a:
        mov dword ptr [eax+8974h],ecx
    L_00433d30:
        lea ecx,[ebp-3]
    L_00433d33:
        cmp esi,ecx
    L_00433d35:
        jge short L_00433d43
    L_00433d37:
        mov edx,dword ptr [data_004746d8]
    L_00433d3d:
        movsx ecx,byte ptr [edx+esi]
    L_00433d41:
        jmp short L_00433d59
    L_00433d43:
        jne short L_00433d4c
    L_00433d45:
        mov ecx,81h
    L_00433d4a:
        jmp short L_00433d59
    L_00433d4c:
        xor ecx,ecx
    L_00433d4e:
        lea edx,[ebp-2]
    L_00433d51:
        cmp esi,edx
    L_00433d53:
        setne cl
    L_00433d56:
        add ecx,7Fh
    L_00433d59:
        push ecx
    L_00433d5a:
        push 46E1C0h
    L_00433d5f:
        lea ebx,[esp+1Ch]
    L_00433d63:
        push eax
    L_00433d64:
        call asm_GameThread_AppendFormatted_00401630
    L_00433d69:
        xor edx,edx
    L_00433d6b:
        mov eax,esi
    L_00433d6d:
        mov ecx,0Dh
    L_00433d72:
        div ecx
    L_00433d74:
        add esp,0Ch
    L_00433d77:
        cmp edx,0Ch
    L_00433d7a:
        jne short L_00433d94
    L_00433d7c:
        fld dword ptr [esp+18h]
    L_00433d80:
        mov dword ptr [esp+14h],43540000h
    L_00433d88:
        fadd dword ptr [data_00470b48]
    L_00433d8e:
        fstp dword ptr [esp+18h]
    L_00433d92:
        jmp short L_00433da2
    L_00433d94:
        fld dword ptr [esp+14h]
    L_00433d98:
        fadd dword ptr [data_00470c0c]
    L_00433d9e:
        fstp dword ptr [esp+14h]
    L_00433da2:
        mov eax,dword ptr [data_004776e0]
    L_00433da7:
        inc esi
    L_00433da8:
        cmp esi,ebp
    L_00433daa:
        jl asm_FUN_00433b30_part_00433d10
    L_00433db0:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_00433dba:
        jmp asm_target_00433ec8
    L_00433dbf:
        mov ecx,dword ptr [data_004776e0]
    L_00433dc5:
        mov dword ptr [esp+14h],42680000h
    L_00433dcd:
        mov dword ptr [esp+18h],42A00000h
    L_00433dd5:
        mov dword ptr [esp+1Ch],0
    L_00433ddd:
        mov dword ptr [ecx+8988h],1
    L_00433de7:
        xor edi,edi
    L_00433de9:
        lea ebp,[esi+59E4h]
    L_00433def:
        jmp short L_00433df7
    L_00433df1:
        mov ecx,dword ptr [data_004776e0]
    L_00433df7:
        mov eax,dword ptr [esi+24h]
    L_00433dfa:
        xor edx,edx
    L_00433dfc:
        cmp eax,edi
    L_00433dfe:
        setne dl
    L_00433e01:
        dec edx
    L_00433e02:
        and edx,7F7E80h
    L_00433e08:
        add edx,0FF808080h
    L_00433e0e:
        mov dword ptr [ecx+8974h],edx
    L_00433e14:
        mov eax,dword ptr [ebp]
    L_00433e17:
        test eax,eax
    L_00433e19:
        je short L_00433e95
    L_00433e1b:
        mov esi,dword ptr [eax+18h]
    L_00433e1e:
        lea eax,[esi+0Ch]
    L_00433e21:
        push eax
    L_00433e22:
        call asm_localtime_00452baa
    L_00433e27:
        fld dword ptr [esi+48h]
    L_00433e2a:
        push ecx
    L_00433e2b:
        mov ecx,dword ptr [esi+5Ch]
    L_00433e2e:
        fstp qword ptr [esp]
    L_00433e31:
        mov edx,dword ptr [ecx*4+474744h]
    L_00433e38:
        mov ecx,dword ptr [esi+58h]
    L_00433e3b:
        push edx
    L_00433e3c:
        mov edx,dword ptr [ecx*4+4746F4h]
    L_00433e43:
        mov ecx,dword ptr [esi+50h]
    L_00433e46:
        push edx
    L_00433e47:
        mov edx,dword ptr [esi+54h]
    L_00433e4a:
        lea ecx,[ecx+ecx*2]
    L_00433e4d:
        add ecx,edx
    L_00433e4f:
        mov edx,dword ptr [ecx*4+4746DCh]
    L_00433e56:
        mov ecx,dword ptr [eax+4]
    L_00433e59:
        push edx
    L_00433e5a:
        mov edx,dword ptr [eax+8]
    L_00433e5d:
        push ecx
    L_00433e5e:
        mov ecx,dword ptr [eax+0Ch]
    L_00433e61:
        push edx
    L_00433e62:
        mov edx,dword ptr [eax+10h]
    L_00433e65:
        mov eax,dword ptr [eax+14h]
    L_00433e68:
        push ecx
    L_00433e69:
        inc edi
    L_00433e6a:
        inc edx
    L_00433e6b:
        push edx
    L_00433e6c:
        cdq
    L_00433e6d:
        mov ecx,64h
    L_00433e72:
        idiv ecx
    L_00433e74:
        lea ebx,[esp+38h]
    L_00433e78:
        push edx
    L_00433e79:
        mov edx,dword ptr [data_004776e0]
    L_00433e7f:
        push esi
    L_00433e80:
        push edi
    L_00433e81:
        push 46EFB0h
    L_00433e86:
        push edx
    L_00433e87:
        call asm_GameThread_AppendFormatted_00401630
    L_00433e8c:
        mov esi,dword ptr [esp+5Ch]
    L_00433e90:
        add esp,38h
    L_00433e93:
        jmp short L_00433ea9
    L_00433e95:
        inc edi
    L_00433e96:
        push edi
    L_00433e97:
        push 46EF74h
    L_00433e9c:
        push ecx
    L_00433e9d:
        lea ebx,[esp+20h]
    L_00433ea1:
        call asm_GameThread_AppendFormatted_00401630
    L_00433ea6:
        add esp,0Ch
    L_00433ea9:
        fld dword ptr [esp+18h]
    L_00433ead:
        add ebp,4
    L_00433eb0:
        cmp edi,19h
    L_00433eb3:
        fadd dword ptr [data_00470c08]
    L_00433eb9:
        fstp dword ptr [esp+18h]
    L_00433ebd:
        jl asm_target_00433df1
    L_00433ec3:
        mov eax,dword ptr [data_004776e0]
    L_00433ec8:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_00433ed2:
        mov dword ptr [eax+8988h],0
    L_00433edc:
        pop edi
    L_00433edd:
        pop esi
    L_00433ede:
        pop ebp
    L_00433edf:
        mov eax,1
    L_00433ee4:
        pop ebx
    L_00433ee5:
        add esp,10h
    L_00433ee8:
        ret 4
    }
}
