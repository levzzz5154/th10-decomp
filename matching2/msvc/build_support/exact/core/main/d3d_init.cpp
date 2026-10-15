// BLOCKED (D3504): closest_byte_count=0/1159; first_diff=0x00439890;
// residual_class=caller-inclusive D3D retry/register topology and variadic
// logger call scheduling: retail keeps EBX/EBP/ESI/EDI live across COM,
// D3DX, and TextLog calls while interleaving stack-parameter stores.
// variants_tested=exact retail wrapper, live-Ghidra decompilation plus
// caller/callee graph, and the legacy readable D3D candidate (1199 bytes);
// the prior native-LTCG logger cluster reached 1191 bytes with first residual
// at 0x004398F0 (+0x60), so no readable body was retained.
// next_lever=native-LTCG cluster over real caller 0x00438C2C, this body,
// TextLog_0044B810, D3DX stubs, and device-default/viewport helpers; retain
// the logger's caller-pop convention and reproduce all 1159 bytes.
#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

// 0x00439890..0x00439D16: FUN_00439890
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439890_00439890() {
    __asm {
    L_00439890:
        sub esp,70h
    L_00439893:
        push ebx
    L_00439894:
        push ebp
    L_00439895:
        push esi
    L_00439896:
        push edi
    L_00439897:
        xor eax,eax
    L_00439899:
        lea edx,[esp+38h]
    L_0043989d:
        push edx
    L_0043989e:
        mov ecx,0Eh
    L_004398a3:
        lea edi,[esp+4Ch]
    L_004398a7:
        rep stosd
    L_004398a9:
        mov eax,dword ptr [data_00491c2c]
    L_004398ae:
        mov ecx,dword ptr [eax]
    L_004398b0:
        xor ebx,ebx
    L_004398b2:
        push ebx
    L_004398b3:
        push eax
    L_004398b4:
        mov byte ptr [esp+1Fh],1
    L_004398b9:
        call dword ptr [ecx+20h]
    L_004398bc:
        cmp byte ptr [data_00491d65],bl
    L_004398c2:
        mov edi,80000000h
    L_004398c7:
        jne asm_target_00439991
    L_004398cd:
        test byte ptr [data_00491d78],1
    L_004398d4:
        je short L_004398e7
    L_004398d6:
        mov dword ptr [esp+50h],17h
    L_004398de:
        mov byte ptr [data_00491d62],1
    L_004398e5:
        jmp short L_00439920
    L_004398e7:
        mov al,byte ptr [data_00491d62]
    L_004398ec:
        cmp al,0FFh
    L_004398ee:
        jne short L_00439912
    L_004398f0:
        push 46F640h
    L_004398f5:
        mov ecx,474F70h
    L_004398fa:
        mov dword ptr [esp+54h],16h
    L_00439902:
        mov byte ptr [data_00491d62],bl
    L_00439908:
        call asm_TextLog_Append_0044b810
    L_0043990d:
        add esp,4
    L_00439910:
        jmp short L_00439920
    L_00439912:
        xor ecx,ecx
    L_00439914:
        cmp al,bl
    L_00439916:
        setne cl
    L_00439919:
        add ecx,16h
    L_0043991c:
        mov dword ptr [esp+50h],ecx
    L_00439920:
        cmp byte ptr [data_00492518],bl
    L_00439926:
        je short L_00439935
    L_00439928:
        mov ebp,1
    L_0043992d:
        mov dword ptr [data_00491fdc],ebp
    L_00439933:
        jmp short L_0043996e
    L_00439935:
        cmp dword ptr [data_00491fdc],ebx
    L_0043993b:
        jne short L_00439969
    L_0043993d:
        mov esi,1
    L_00439942:
        push 46F614h
    L_00439947:
        mov ecx,474F70h
    L_0043994c:
        mov dword ptr [esp+7Ch],3Ch
    L_00439954:
        mov dword ptr [esp+80h],esi
    L_0043995b:
        call asm_TextLog_Append_0044b810
    L_00439960:
        add esp,4
    L_00439963:
        mov dword ptr [esp+60h],esi
    L_00439967:
        jmp short L_004399a6
    L_00439969:
        mov ebp,1
    L_0043996e:
        push 46F5F0h
    L_00439973:
        mov ecx,474F70h
    L_00439978:
        mov dword ptr [esp+7Ch],ebx
    L_0043997c:
        mov dword ptr [esp+64h],ebp
    L_00439980:
        mov dword ptr [esp+80h],edi
    L_00439987:
        call asm_TextLog_Append_0044b810
    L_0043998c:
        add esp,4
    L_0043998f:
        jmp short L_004399ab
    L_00439991:
        mov edx,dword ptr [esp+44h]
    L_00439995:
        mov eax,1
    L_0043999a:
        mov dword ptr [esp+50h],edx
    L_0043999e:
        mov dword ptr [esp+60h],eax
    L_004399a2:
        mov dword ptr [esp+68h],eax
    L_004399a6:
        mov ebp,1
    L_004399ab:
        mov eax,dword ptr [data_00491ff4]
    L_004399b0:
        or eax,2
    L_004399b3:
        mov dword ptr [esp+48h],280h
    L_004399bb:
        mov dword ptr [esp+4Ch],1E0h
    L_004399c3:
        mov dword ptr [esp+6Ch],ebp
    L_004399c7:
        mov dword ptr [esp+70h],50h
    L_004399cf:
        mov dword ptr [esp+74h],ebp
    L_004399d3:
        mov dword ptr [data_00491ff4],eax
    L_004399d8:
        mov dword ptr [data_00491fe0],ebp
    L_004399de:
        xor esi,esi
    L_004399e0:
        test byte ptr [data_00491d78],2
    L_004399e7:
        jne short L_00439a65
    L_004399e9:
        mov eax,dword ptr [data_00491c2c]
    L_004399ee:
        mov ecx,dword ptr [eax]
    L_004399f0:
        push 491C30h
    L_004399f5:
        lea edx,[esp+4Ch]
    L_004399f9:
        push edx
    L_004399fa:
        mov edx,dword ptr [data_004924f0]
    L_00439a00:
        push 40h
    L_00439a02:
        push edx
    L_00439a03:
        push ebp
    L_00439a04:
        push ebx
    L_00439a05:
        push eax
    L_00439a06:
        call dword ptr [ecx+40h]
    L_00439a09:
        test eax,eax
    L_00439a0b:
        jge asm_target_00439b4f
    L_00439a11:
        cmp esi,ebx
    L_00439a13:
        je short L_00439a27
    L_00439a15:
        push 46F5CCh
    L_00439a1a:
        mov ecx,474F70h
    L_00439a1f:
        call asm_TextLog_Append_0044b810
    L_00439a24:
        add esp,4
    L_00439a27:
        mov eax,dword ptr [data_00491c2c]
    L_00439a2c:
        mov ecx,dword ptr [eax]
    L_00439a2e:
        push 491C30h
    L_00439a33:
        lea edx,[esp+4Ch]
    L_00439a37:
        push edx
    L_00439a38:
        mov edx,dword ptr [data_004924f0]
    L_00439a3e:
        push 20h
    L_00439a40:
        push edx
    L_00439a41:
        push ebp
    L_00439a42:
        push ebx
    L_00439a43:
        push eax
    L_00439a44:
        call dword ptr [ecx+40h]
    L_00439a47:
        test eax,eax
    L_00439a49:
        jge asm_target_00439b33
    L_00439a4f:
        cmp esi,ebx
    L_00439a51:
        je short L_00439a65
    L_00439a53:
        push 46F5ACh
    L_00439a58:
        mov ecx,474F70h
    L_00439a5d:
        call asm_TextLog_Append_0044b810
    L_00439a62:
        add esp,4
    L_00439a65:
        mov eax,dword ptr [data_00491c2c]
    L_00439a6a:
        mov ecx,dword ptr [eax]
    L_00439a6c:
        push 491C30h
    L_00439a71:
        lea edx,[esp+4Ch]
    L_00439a75:
        push edx
    L_00439a76:
        mov edx,dword ptr [data_004924f0]
    L_00439a7c:
        push 20h
    L_00439a7e:
        push edx
    L_00439a7f:
        push 2
    L_00439a81:
        push ebx
    L_00439a82:
        push eax
    L_00439a83:
        call dword ptr [ecx+40h]
    L_00439a86:
        test eax,eax
    L_00439a88:
        jge asm_target_00439b13
    L_00439a8e:
        cmp dword ptr [data_00491fdc],ebx
    L_00439a94:
        jne short L_00439ab9
    L_00439a96:
        push 46F584h
    L_00439a9b:
        mov ecx,474F70h
    L_00439aa0:
        call asm_TextLog_Append_0044b810
    L_00439aa5:
        add esp,4
    L_00439aa8:
        mov dword ptr [esp+78h],ebx
    L_00439aac:
        mov dword ptr [data_00491fe0],ebx
    L_00439ab2:
        mov esi,ebp
    L_00439ab4:
        jmp asm_target_004399e0
    L_00439ab9:
        cmp dword ptr [esp+7Ch],edi
    L_00439abd:
        jne short L_00439ae2
    L_00439abf:
        push 46F54Ch
    L_00439ac4:
        mov ecx,474F70h
    L_00439ac9:
        call asm_TextLog_Append_0044b810
    L_00439ace:
        add esp,4
    L_00439ad1:
        mov dword ptr [esp+7Ch],ebp
    L_00439ad5:
        mov dword ptr [esp+60h],3
    L_00439add:
        jmp asm_target_004399e0
    L_00439ae2:
        push 46F514h
    L_00439ae7:
        mov edi,474F70h
    L_00439aec:
        call asm_TextLog_AppendLine_0044b8e0
    L_00439af1:
        mov eax,dword ptr [data_00491c2c]
    L_00439af6:
        add esp,4
    L_00439af9:
        cmp eax,ebx
    L_00439afb:
        je short L_00439b09
    L_00439afd:
        mov ecx,dword ptr [eax]
    L_00439aff:
        push eax
    L_00439b00:
        call dword ptr [ecx+8]
    L_00439b03:
        mov dword ptr [data_00491c2c],ebx
    L_00439b09:
        pop edi
    L_00439b0a:
        pop esi
    L_00439b0b:
        mov eax,ebp
    L_00439b0d:
        pop ebp
    L_00439b0e:
        pop ebx
    L_00439b0f:
        add esp,70h
    L_00439b12:
        ret
    L_00439b13:
        push 46F4D8h
    L_00439b18:
        mov ecx,474F70h
    L_00439b1d:
        call asm_TextLog_Append_0044b810
    L_00439b22:
        mov eax,dword ptr [data_00491ff4]
    L_00439b27:
        add esp,4
    L_00439b2a:
        and eax,0FFFFFFFEh
    L_00439b2d:
        mov byte ptr [esp+13h],bl
    L_00439b31:
        jmp short L_00439b68
    L_00439b33:
        push 46F4C4h
    L_00439b38:
        mov ecx,474F70h
    L_00439b3d:
        call asm_TextLog_Append_0044b810
    L_00439b42:
        mov eax,dword ptr [data_00491ff4]
    L_00439b47:
        add esp,4
    L_00439b4a:
        and eax,0FFFFFFFEh
    L_00439b4d:
        jmp short L_00439b68
    L_00439b4f:
        push 46F4A8h
    L_00439b54:
        mov ecx,474F70h
    L_00439b59:
        call asm_TextLog_Append_0044b810
    L_00439b5e:
        mov eax,dword ptr [data_00491ff4]
    L_00439b63:
        add esp,4
    L_00439b66:
        or eax,ebp
    L_00439b68:
        fld qword ptr [data_00470c00]
    L_00439b6e:
        mov dword ptr [data_00491ff4],eax
    L_00439b73:
        fptan
    L_00439b75:
        lea edx,[esp+14h]
    L_00439b79:
        push edx
    L_00439b7a:
        mov ecx,0Eh
    L_00439b7f:
        lea esi,[esp+4Ch]
    L_00439b83:
        mov edi,491D0Ch
    L_00439b88:
        lea eax,[esp+24h]
    L_00439b8c:
        rep movsd
    L_00439b8e:
        push eax
    L_00439b8f:
        lea ecx,[esp+34h]
    L_00439b93:
        push ecx
    L_00439b94:
        push 491C74h
    L_00439b99:
        mov dword ptr [esp+3Ch],43A00000h
    L_00439ba1:
        mov dword ptr [esp+40h],0C3700000h
    L_00439ba9:
        mov dword ptr [esp+30h],43A00000h
    L_00439bb1:
        mov dword ptr [esp+34h],0C3700000h
    L_00439bb9:
        mov dword ptr [esp+38h],0
    L_00439bc1:
        mov dword ptr [esp+24h],0
    L_00439bc9:
        mov dword ptr [esp+28h],3F800000h
    L_00439bd1:
        mov dword ptr [esp+2Ch],0
    L_00439bd9:
        fstp st(0)
    L_00439bdb:
        fdivr dword ptr [data_00470bfc]
    L_00439be1:
        fchs
    L_00439be3:
        fstp dword ptr [esp+44h]
    L_00439be7:
        call asm_D3DXMatrixLookAtLH_00452194
    L_00439bec:
        push 461C4000h
    L_00439bf1:
        push 42C80000h
    L_00439bf6:
        push 3FAAAAABh
    L_00439bfb:
        push 3F060A92h
    L_00439c00:
        push 491CB4h
    L_00439c05:
        call asm_D3DXMatrixPerspectiveFovLH_0045219a
    L_00439c0a:
        mov eax,dword ptr [g_d3d_device]
    L_00439c0f:
        mov edx,dword ptr [eax]
    L_00439c11:
        push 491C74h
    L_00439c16:
        push 2
    L_00439c18:
        push eax
    L_00439c19:
        call dword ptr [edx+0B0h]
    L_00439c1f:
        mov eax,dword ptr [g_d3d_device]
    L_00439c24:
        mov ecx,dword ptr [eax]
    L_00439c26:
        push 491CB4h
    L_00439c2b:
        push 3
    L_00439c2d:
        push eax
    L_00439c2e:
        call dword ptr [ecx+0B0h]
    L_00439c34:
        mov eax,dword ptr [g_d3d_device]
    L_00439c39:
        mov edx,dword ptr [eax]
    L_00439c3b:
        push 491CF4h
    L_00439c40:
        push eax
    L_00439c41:
        call dword ptr [edx+0C0h]
    L_00439c47:
        mov eax,dword ptr [g_d3d_device]
    L_00439c4c:
        mov ecx,dword ptr [eax]
    L_00439c4e:
        push 492000h
    L_00439c53:
        push eax
    L_00439c54:
        call dword ptr [ecx+1Ch]
    L_00439c57:
        test byte ptr [data_00492090],40h
    L_00439c5e:
        jne short L_00439c72
    L_00439c60:
        push 46F458h
    L_00439c65:
        mov ecx,474F70h
    L_00439c6a:
        call asm_TextLog_Append_0044b810
    L_00439c6f:
        add esp,4
    L_00439c72:
        cmp dword ptr [data_00492058],100h
    L_00439c7c:
        ja short L_00439c90
    L_00439c7e:
        push 46F408h
    L_00439c83:
        mov ecx,474F70h
    L_00439c88:
        call asm_TextLog_Append_0044b810
    L_00439c8d:
        add esp,4
    L_00439c90:
        test byte ptr [data_00491d78],1
    L_00439c97:
        jne short L_00439cf2
    L_00439c99:
        cmp byte ptr [esp+13h],bl
    L_00439c9d:
        je short L_00439cf2
    L_00439c9f:
        mov ecx,dword ptr [esp+50h]
    L_00439ca3:
        mov eax,dword ptr [data_00491c2c]
    L_00439ca8:
        mov edx,dword ptr [eax]
    L_00439caa:
        push 15h
    L_00439cac:
        push 3
    L_00439cae:
        push ebx
    L_00439caf:
        push ecx
    L_00439cb0:
        push ebp
    L_00439cb1:
        push ebx
    L_00439cb2:
        push eax
    L_00439cb3:
        call dword ptr [edx+28h]
    L_00439cb6:
        test eax,eax
    L_00439cb8:
        jne short L_00439cc3
    L_00439cba:
        or dword ptr [data_00491ff4],4
    L_00439cc1:
        jmp short L_00439cf2
    L_00439cc3:
        mov esi,dword ptr [data_00491ff4]
    L_00439cc9:
        mov edx,dword ptr [data_00491d78]
    L_00439ccf:
        or edx,ebp
    L_00439cd1:
        and esi,0FFFFFFFBh
    L_00439cd4:
        push 46F3C0h
    L_00439cd9:
        mov ecx,474F70h
    L_00439cde:
        mov dword ptr [data_00491ff4],esi
    L_00439ce4:
        mov dword ptr [data_00491d78],edx
    L_00439cea:
        call asm_TextLog_Append_0044b810
    L_00439cef:
        add esp,4
    L_00439cf2:
        call asm_FUN_00439d20_00439d20
    L_00439cf7:
        push 0FF000000h
    L_00439cfc:
        call asm_Viewport_ApplyDefaultRetail_0043bcd0
    L_00439d01:
        pop edi
    L_00439d02:
        pop esi
    L_00439d03:
        pop ebp
    L_00439d04:
        mov dword ptr [data_004924f4],ebx
    L_00439d0a:
        mov dword ptr [data_00491fe4],ebx
    L_00439d10:
        xor eax,eax
    L_00439d12:
        pop ebx
    L_00439d13:
        add esp,70h
    L_00439d16:
        ret
    }
}
