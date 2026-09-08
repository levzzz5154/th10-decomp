#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455BF3..0x00455D52: FUN_00455bf3
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00455bf3_00455bf3() {
    __asm {
    L_00455bf3:
        push ebp
    L_00455bf4:
        lea ebp,[esp-64h]
    L_00455bf8:
        sub esp,0A0h
    L_00455bfe:
        mov eax,dword ptr [data_00473660]
    L_00455c03:
        mov ecx,dword ptr [ebp+74h]
    L_00455c06:
        mov edx,dword ptr [ebp+78h]
    L_00455c09:
        xor eax,ebp
    L_00455c0b:
        push esi
    L_00455c0c:
        mov esi,dword ptr [ebp+6Ch]
    L_00455c0f:
        push edi
    L_00455c10:
        mov dword ptr [ebp+60h],eax
    L_00455c13:
        mov eax,dword ptr [ebp+70h]
    L_00455c16:
        xor edi,edi
    L_00455c18:
        cmp esi,edi
    L_00455c1a:
        mov dword ptr [ebp-3Ch],eax
    L_00455c1d:
        mov dword ptr [ebp-38h],ecx
    L_00455c20:
        mov dword ptr [ebp-34h],edx
    L_00455c23:
        jne short L_00455c2c
    L_00455c25:
        xor eax,eax
    L_00455c27:
        jmp asm_target_00455d42
    L_00455c2c:
        cmp byte ptr [esi],43h
    L_00455c2f:
        jne short L_00455c5c
    L_00455c31:
        cmp byte ptr [esi+1],0
    L_00455c35:
        jne short L_00455c5c
    L_00455c37:
        cmp ecx,edi
    L_00455c39:
        mov byte ptr [eax],43h
    L_00455c3c:
        mov byte ptr [eax+1],0
    L_00455c40:
        je short L_00455c4d
    L_00455c42:
        mov word ptr [ecx],di
    L_00455c45:
        mov word ptr [ecx+2],di
    L_00455c49:
        mov word ptr [ecx+4],di
    L_00455c4d:
        cmp edx,edi
    L_00455c4f:
        je asm_target_00455d42
    L_00455c55:
        mov dword ptr [edx],edi
    L_00455c57:
        jmp asm_target_00455d42
    L_00455c5c:
        push ebx
    L_00455c5d:
        push esi
    L_00455c5e:
        call asm_strlen_00456720
    L_00455c63:
        mov edi,82h
    L_00455c68:
        cmp eax,edi
    L_00455c6a:
        pop ecx
    L_00455c6b:
        mov ebx,4732C0h
    L_00455c70:
        jae short L_00455c94
    L_00455c72:
        push esi
    L_00455c73:
        push ebx
    L_00455c74:
        call asm_strcmp_0045bf30
    L_00455c79:
        test eax,eax
    L_00455c7b:
        pop ecx
    L_00455c7c:
        pop ecx
    L_00455c7d:
        je asm_target_00455d04
    L_00455c83:
        push esi
    L_00455c84:
        push 473238h
    L_00455c89:
        call asm_strcmp_0045bf30
    L_00455c8e:
        test eax,eax
    L_00455c90:
        pop ecx
    L_00455c91:
        pop ecx
    L_00455c92:
        je short L_00455d04
    L_00455c94:
        lea eax,[ebp-30h]
    L_00455c97:
        push esi
    L_00455c98:
        push eax
    L_00455c99:
        call asm_lc_strtolc_004559b4
    L_00455c9e:
        test eax,eax
    L_00455ca0:
        pop ecx
    L_00455ca1:
        pop ecx
    L_00455ca2:
        je short L_00455cab
    L_00455ca4:
        xor eax,eax
    L_00455ca6:
        jmp asm_target_00455d41
    L_00455cab:
        lea eax,[ebp-30h]
    L_00455cae:
        push eax
    L_00455caf:
        push 477368h
    L_00455cb4:
        push eax
    L_00455cb5:
        call asm_get_qualified_locale_0045ca50
    L_00455cba:
        add esp,0Ch
    L_00455cbd:
        test eax,eax
    L_00455cbf:
        je short L_00455ca4
    L_00455cc1:
        movzx eax,word ptr [data_0047736c]
    L_00455cc8:
        mov dword ptr [data_00477370],eax
    L_00455ccd:
        lea eax,[ebp-30h]
    L_00455cd0:
        push eax
    L_00455cd1:
        push ebx
    L_00455cd2:
        call asm_lc_lctostr_00455a90
    L_00455cd7:
        cmp byte ptr [esi],0
    L_00455cda:
        pop ecx
    L_00455cdb:
        pop ecx
    L_00455cdc:
        je short L_00455ce9
    L_00455cde:
        push esi
    L_00455cdf:
        call asm_strlen_00456720
    L_00455ce4:
        cmp eax,edi
    L_00455ce6:
        pop ecx
    L_00455ce7:
        jb short L_00455cee
    L_00455ce9:
        mov esi,46D275h
    L_00455cee:
        push edi
    L_00455cef:
        push esi
    L_00455cf0:
        push 473238h
    L_00455cf5:
        mov byte ptr [data_004732ba],0
    L_00455cfc:
        call asm_strncpy_00452960
    L_00455d01:
        add esp,0Ch
    L_00455d04:
        cmp dword ptr [ebp-38h],0
    L_00455d08:
        je short L_00455d1c
    L_00455d0a:
        push 6
    L_00455d0c:
        push 477368h
    L_00455d11:
        push dword ptr [ebp-38h]
    L_00455d14:
        call asm_memcpy_0045bfc0
    L_00455d19:
        add esp,0Ch
    L_00455d1c:
        cmp dword ptr [ebp-34h],0
    L_00455d20:
        je short L_00455d34
    L_00455d22:
        push 4
    L_00455d24:
        push 477370h
    L_00455d29:
        push dword ptr [ebp-34h]
    L_00455d2c:
        call asm_memcpy_0045bfc0
    L_00455d31:
        add esp,0Ch
    L_00455d34:
        push ebx
    L_00455d35:
        push dword ptr [ebp-3Ch]
    L_00455d38:
        call asm_FUN_0045bd80_0045bd80
    L_00455d3d:
        pop ecx
    L_00455d3e:
        pop ecx
    L_00455d3f:
        mov eax,ebx
    L_00455d41:
        pop ebx
    L_00455d42:
        mov ecx,dword ptr [ebp+60h]
    L_00455d45:
        pop edi
    L_00455d46:
        xor ecx,ebp
    L_00455d48:
        pop esi
    L_00455d49:
        call asm_security_check_cookie_00458ea5
    L_00455d4e:
        add ebp,64h
    L_00455d51:
        leave
    L_00455d52:
        ret
    }
}
