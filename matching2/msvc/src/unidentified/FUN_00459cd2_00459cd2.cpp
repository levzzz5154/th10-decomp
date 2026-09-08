#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459CD2..0x00459E8D: FUN_00459cd2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00459cd2_00459cd2() {
    __asm {
    L_00459cd2:
        push ebp
    L_00459cd3:
        lea ebp,[esp-3A4h]
    L_00459cda:
        sub esp,424h
    L_00459ce0:
        mov eax,dword ptr [data_00473660]
    L_00459ce5:
        xor ecx,ecx
    L_00459ce7:
        xor eax,ebp
    L_00459ce9:
        cmp dword ptr [ebp+3B4h],ecx
    L_00459cef:
        push edi
    L_00459cf0:
        mov edi,dword ptr [ebp+3B0h]
    L_00459cf6:
        mov dword ptr [ebp+3A0h],eax
    L_00459cfc:
        mov dword ptr [ebp-7Ch],edi
    L_00459cff:
        mov dword ptr [ebp-74h],ecx
    L_00459d02:
        mov dword ptr [ebp-78h],ecx
    L_00459d05:
        jne short L_00459d0e
    L_00459d07:
        xor eax,eax
    L_00459d09:
        jmp asm_target_00459e78
    L_00459d0e:
        mov eax,dword ptr [ebp+3ACh]
    L_00459d14:
        push ebx
    L_00459d15:
        mov ebx,dword ptr [ebp+3ACh]
    L_00459d1b:
        and eax,1Fh
    L_00459d1e:
        sar ebx,5
    L_00459d21:
        push esi
    L_00459d22:
        lea esi,[eax+eax*8]
    L_00459d25:
        lea ebx,[ebx*4+499200h]
    L_00459d2c:
        mov eax,dword ptr [ebx]
    L_00459d2e:
        shl esi,2
    L_00459d31:
        test byte ptr [eax+esi+4],20h
    L_00459d36:
        je short L_00459d4c
    L_00459d38:
        push 2
    L_00459d3a:
        push ecx
    L_00459d3b:
        push ecx
    L_00459d3c:
        push dword ptr [ebp+3ACh]
    L_00459d42:
        call asm_lseeki64_lk_0045fa1a
    L_00459d47:
        add esp,10h
    L_00459d4a:
        xor ecx,ecx
    L_00459d4c:
        mov eax,dword ptr [ebx]
    L_00459d4e:
        add eax,esi
    L_00459d50:
        test byte ptr [eax+4],80h
    L_00459d54:
        je asm_target_00459de6
    L_00459d5a:
        cmp dword ptr [ebp+3B4h],ecx
    L_00459d60:
        mov dword ptr [ebp-70h],edi
    L_00459d63:
        mov dword ptr [ebp-68h],ecx
    L_00459d66:
        jbe asm_target_00459e49
    L_00459d6c:
        jmp short L_00459d70
    L_00459d6e:
        xor ecx,ecx
    L_00459d70:
        mov dword ptr [ebp-6Ch],ecx
    L_00459d73:
        mov ecx,dword ptr [ebp-70h]
    L_00459d76:
        sub ecx,dword ptr [ebp-7Ch]
    L_00459d79:
        lea eax,[ebp-64h]
    L_00459d7c:
        cmp ecx,dword ptr [ebp+3B4h]
    L_00459d82:
        jae short L_00459dab
    L_00459d84:
        mov edx,dword ptr [ebp-70h]
    L_00459d87:
        inc dword ptr [ebp-70h]
    L_00459d8a:
        mov dl,byte ptr [edx]
    L_00459d8c:
        inc ecx
    L_00459d8d:
        cmp dl,0Ah
    L_00459d90:
        jne short L_00459d9c
    L_00459d92:
        inc dword ptr [ebp-78h]
    L_00459d95:
        mov byte ptr [eax],0Dh
    L_00459d98:
        inc eax
    L_00459d99:
        inc dword ptr [ebp-6Ch]
    L_00459d9c:
        mov byte ptr [eax],dl
    L_00459d9e:
        inc eax
    L_00459d9f:
        inc dword ptr [ebp-6Ch]
    L_00459da2:
        cmp dword ptr [ebp-6Ch],400h
    L_00459da9:
        jl short L_00459d7c
    L_00459dab:
        mov edi,eax
    L_00459dad:
        lea eax,[ebp-64h]
    L_00459db0:
        sub edi,eax
    L_00459db2:
        push 0
    L_00459db4:
        lea eax,[ebp-80h]
    L_00459db7:
        push eax
    L_00459db8:
        push edi
    L_00459db9:
        lea eax,[ebp-64h]
    L_00459dbc:
        push eax
    L_00459dbd:
        mov eax,dword ptr [ebx]
    L_00459dbf:
        push dword ptr [eax+esi]
    L_00459dc2:
        call dword ptr [data_004660d4]
    L_00459dc8:
        test eax,eax
    L_00459dca:
        je short L_00459e0a
    L_00459dcc:
        mov eax,dword ptr [ebp-80h]
    L_00459dcf:
        add dword ptr [ebp-74h],eax
    L_00459dd2:
        cmp eax,edi
    L_00459dd4:
        jl short L_00459e13
    L_00459dd6:
        mov eax,dword ptr [ebp-70h]
    L_00459dd9:
        sub eax,dword ptr [ebp-7Ch]
    L_00459ddc:
        cmp eax,dword ptr [ebp+3B4h]
    L_00459de2:
        jb short L_00459d6e
    L_00459de4:
        jmp short L_00459e13
    L_00459de6:
        push ecx
    L_00459de7:
        lea ecx,[ebp-80h]
    L_00459dea:
        push ecx
    L_00459deb:
        push dword ptr [ebp+3B4h]
    L_00459df1:
        push edi
    L_00459df2:
        push dword ptr [eax]
    L_00459df4:
        call dword ptr [data_004660d4]
    L_00459dfa:
        test eax,eax
    L_00459dfc:
        je short L_00459e0a
    L_00459dfe:
        mov eax,dword ptr [ebp-80h]
    L_00459e01:
        and dword ptr [ebp-68h],0
    L_00459e05:
        mov dword ptr [ebp-74h],eax
    L_00459e08:
        jmp short L_00459e13
    L_00459e0a:
        call dword ptr [data_0046610c]
    L_00459e10:
        mov dword ptr [ebp-68h],eax
    L_00459e13:
        mov eax,dword ptr [ebp-74h]
    L_00459e16:
        test eax,eax
    L_00459e18:
        jne short L_00459e73
    L_00459e1a:
        cmp dword ptr [ebp-68h],eax
    L_00459e1d:
        je short L_00459e46
    L_00459e1f:
        push 5
    L_00459e21:
        pop esi
    L_00459e22:
        cmp dword ptr [ebp-68h],esi
    L_00459e25:
        jne short L_00459e3b
    L_00459e27:
        call asm_FUN_00456af2_00456af2
    L_00459e2c:
        mov dword ptr [eax],9
    L_00459e32:
        call asm_FUN_00456afb_00456afb
    L_00459e37:
        mov dword ptr [eax],esi
    L_00459e39:
        jmp short L_00459e6e
    L_00459e3b:
        push dword ptr [ebp-68h]
    L_00459e3e:
        call asm_dosmaperr_00456b04
    L_00459e43:
        pop ecx
    L_00459e44:
        jmp short L_00459e6e
    L_00459e46:
        mov edi,dword ptr [ebp-7Ch]
    L_00459e49:
        mov eax,dword ptr [ebx]
    L_00459e4b:
        test byte ptr [eax+esi+4],40h
    L_00459e50:
        je short L_00459e5b
    L_00459e52:
        cmp byte ptr [edi],1Ah
    L_00459e55:
        jne short L_00459e5b
    L_00459e57:
        xor eax,eax
    L_00459e59:
        jmp short L_00459e76
    L_00459e5b:
        call asm_FUN_00456af2_00456af2
    L_00459e60:
        mov dword ptr [eax],1Ch
    L_00459e66:
        call asm_FUN_00456afb_00456afb
    L_00459e6b:
        and dword ptr [eax],0
    L_00459e6e:
        or eax,0FFFFFFFFh
    L_00459e71:
        jmp short L_00459e76
    L_00459e73:
        sub eax,dword ptr [ebp-78h]
    L_00459e76:
        pop esi
    L_00459e77:
        pop ebx
    L_00459e78:
        mov ecx,dword ptr [ebp+3A0h]
    L_00459e7e:
        xor ecx,ebp
    L_00459e80:
        pop edi
    L_00459e81:
        call asm_security_check_cookie_00458ea5
    L_00459e86:
        add ebp,3A4h
    L_00459e8c:
        leave
    L_00459e8d:
        ret
    }
}
