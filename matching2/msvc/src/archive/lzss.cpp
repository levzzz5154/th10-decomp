#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00435DC0..0x00435F9A: DecompressDatLzss
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DecompressDatLzss_00435dc0() {
    __asm {
    L_00435dc0:
        sub esp,0Ch
    L_00435dc3:
        mov eax,dword ptr [esp+18h]
    L_00435dc7:
        push ebx
    L_00435dc8:
        push ebp
    L_00435dc9:
        xor ebp,ebp
    L_00435dcb:
        cmp eax,ebp
    L_00435dcd:
        mov bl,80h
    L_00435dcf:
        mov dword ptr [esp+8],ebp
    L_00435dd3:
        jne short L_00435df4
    L_00435dd5:
        mov eax,dword ptr [esp+24h]
    L_00435dd9:
        push eax
    L_00435dda:
        call asm_malloc_00452706
    L_00435ddf:
        add esp,4
    L_00435de2:
        cmp eax,ebp
    L_00435de4:
        mov dword ptr [esp+20h],eax
    L_00435de8:
        jne short L_00435df4
    L_00435dea:
        pop ebp
    L_00435deb:
        xor eax,eax
    L_00435ded:
        pop ebx
    L_00435dee:
        add esp,0Ch
    L_00435df1:
        ret 10h
    L_00435df4:
        mov edx,dword ptr [esp+18h]
    L_00435df8:
        mov ecx,dword ptr [esp+20h]
    L_00435dfc:
        push esi
    L_00435dfd:
        push edi
    L_00435dfe:
        mov edi,edx
    L_00435e00:
        mov dword ptr [esp+2Ch],ecx
    L_00435e04:
        mov dword ptr [esp+14h],1
    L_00435e0c:
        jmp short L_00435e14
    L_00435e0e:
        xor ebp,ebp
    L_00435e10:
        mov edx,dword ptr [esp+20h]
    L_00435e14:
        cmp bl,80h
    L_00435e17:
        jne short L_00435e33
    L_00435e19:
        movzx eax,byte ptr [edi]
    L_00435e1c:
        mov ecx,edi
    L_00435e1e:
        mov dword ptr [esp+10h],eax
    L_00435e22:
        mov eax,dword ptr [esp+24h]
    L_00435e26:
        sub ecx,edx
    L_00435e28:
        cmp ecx,eax
    L_00435e2a:
        jl short L_00435e32
    L_00435e2c:
        mov dword ptr [esp+10h],ebp
    L_00435e30:
        jmp short L_00435e33
    L_00435e32:
        inc edi
    L_00435e33:
        mov eax,dword ptr [esp+10h]
    L_00435e37:
        movzx ecx,bl
    L_00435e3a:
        shr bl,1
    L_00435e3c:
        and ecx,eax
    L_00435e3e:
        test bl,bl
    L_00435e40:
        jne short L_00435e44
    L_00435e42:
        mov bl,80h
    L_00435e44:
        cmp ecx,ebp
    L_00435e46:
        mov ecx,edi
    L_00435e48:
        je short L_00435eaa
    L_00435e4a:
        xor eax,eax
    L_00435e4c:
        mov esi,80h
    L_00435e51:
        sub ecx,edx
    L_00435e53:
        cmp bl,80h
    L_00435e56:
        jne short L_00435e6d
    L_00435e58:
        movzx edx,byte ptr [edi]
    L_00435e5b:
        mov dword ptr [esp+10h],edx
    L_00435e5f:
        cmp ecx,dword ptr [esp+24h]
    L_00435e63:
        jl short L_00435e6b
    L_00435e65:
        mov dword ptr [esp+10h],ebp
    L_00435e69:
        jmp short L_00435e6d
    L_00435e6b:
        inc edi
    L_00435e6c:
        inc ecx
    L_00435e6d:
        mov dl,byte ptr [esp+10h]
    L_00435e71:
        test bl,dl
    L_00435e73:
        je short L_00435e77
    L_00435e75:
        or eax,esi
    L_00435e77:
        shr bl,1
    L_00435e79:
        shr esi,1
    L_00435e7b:
        test bl,bl
    L_00435e7d:
        jne short L_00435e81
    L_00435e7f:
        mov bl,80h
    L_00435e81:
        cmp esi,ebp
    L_00435e83:
        jne short L_00435e53
    L_00435e85:
        mov ecx,dword ptr [esp+2Ch]
    L_00435e89:
        mov byte ptr [ecx],al
    L_00435e8b:
        inc ecx
    L_00435e8c:
        mov dword ptr [esp+2Ch],ecx
    L_00435e90:
        mov ecx,dword ptr [esp+14h]
    L_00435e94:
        mov byte ptr [ecx+48F868h],al
    L_00435e9a:
        inc ecx
    L_00435e9b:
        and ecx,1FFFh
    L_00435ea1:
        mov dword ptr [esp+14h],ecx
    L_00435ea5:
        jmp asm_target_00435e10
    L_00435eaa:
        mov esi,1000h
    L_00435eaf:
        sub ecx,edx
    L_00435eb1:
        cmp bl,80h
    L_00435eb4:
        jne short L_00435ecf
    L_00435eb6:
        movzx eax,byte ptr [edi]
    L_00435eb9:
        mov dword ptr [esp+10h],eax
    L_00435ebd:
        cmp ecx,dword ptr [esp+24h]
    L_00435ec1:
        jl short L_00435ecd
    L_00435ec3:
        mov dword ptr [esp+10h],0
    L_00435ecb:
        jmp short L_00435ecf
    L_00435ecd:
        inc edi
    L_00435ece:
        inc ecx
    L_00435ecf:
        mov al,byte ptr [esp+10h]
    L_00435ed3:
        test bl,al
    L_00435ed5:
        je short L_00435ed9
    L_00435ed7:
        or ebp,esi
    L_00435ed9:
        shr bl,1
    L_00435edb:
        shr esi,1
    L_00435edd:
        test bl,bl
    L_00435edf:
        jne short L_00435ee3
    L_00435ee1:
        mov bl,80h
    L_00435ee3:
        test esi,esi
    L_00435ee5:
        jne short L_00435eb1
    L_00435ee7:
        xor eax,eax
    L_00435ee9:
        cmp ebp,eax
    L_00435eeb:
        mov dword ptr [esp+18h],ebp
    L_00435eef:
        je asm_target_00435f7d
    L_00435ef5:
        mov ecx,edi
    L_00435ef7:
        xor ebp,ebp
    L_00435ef9:
        mov esi,8
    L_00435efe:
        sub ecx,edx
    L_00435f00:
        cmp bl,80h
    L_00435f03:
        jne short L_00435f1a
    L_00435f05:
        movzx edx,byte ptr [edi]
    L_00435f08:
        mov dword ptr [esp+10h],edx
    L_00435f0c:
        cmp ecx,dword ptr [esp+24h]
    L_00435f10:
        jl short L_00435f18
    L_00435f12:
        mov dword ptr [esp+10h],eax
    L_00435f16:
        jmp short L_00435f1a
    L_00435f18:
        inc edi
    L_00435f19:
        inc ecx
    L_00435f1a:
        mov dl,byte ptr [esp+10h]
    L_00435f1e:
        test bl,dl
    L_00435f20:
        je short L_00435f24
    L_00435f22:
        or ebp,esi
    L_00435f24:
        shr bl,1
    L_00435f26:
        shr esi,1
    L_00435f28:
        test bl,bl
    L_00435f2a:
        jne short L_00435f2e
    L_00435f2c:
        mov bl,80h
    L_00435f2e:
        cmp esi,eax
    L_00435f30:
        jne short L_00435f00
    L_00435f32:
        lea esi,[ebp+2]
    L_00435f35:
        xor ecx,ecx
    L_00435f37:
        cmp esi,eax
    L_00435f39:
        jl asm_target_00435e0e
    L_00435f3f:
        nop
    L_00435f40:
        mov eax,dword ptr [esp+18h]
    L_00435f44:
        lea edx,[ecx+eax]
    L_00435f47:
        mov eax,dword ptr [esp+2Ch]
    L_00435f4b:
        and edx,1FFFh
    L_00435f51:
        movzx edx,byte ptr [edx+48F868h]
    L_00435f58:
        mov byte ptr [eax],dl
    L_00435f5a:
        inc eax
    L_00435f5b:
        mov dword ptr [esp+2Ch],eax
    L_00435f5f:
        mov eax,dword ptr [esp+14h]
    L_00435f63:
        mov byte ptr [eax+48F868h],dl
    L_00435f69:
        inc eax
    L_00435f6a:
        and eax,1FFFh
    L_00435f6f:
        inc ecx
    L_00435f70:
        cmp ecx,esi
    L_00435f72:
        mov dword ptr [esp+14h],eax
    L_00435f76:
        jle short L_00435f40
    L_00435f78:
        jmp asm_target_00435e0e
    L_00435f7d:
        cmp bl,80h
    L_00435f80:
        pop edi
    L_00435f81:
        pop esi
    L_00435f82:
        je short L_00435f8f
    L_00435f84:
        shr bl,1
    L_00435f86:
        test bl,bl
    L_00435f88:
        je short L_00435f8f
    L_00435f8a:
        cmp bl,80h
    L_00435f8d:
        jne short L_00435f84
    L_00435f8f:
        mov eax,dword ptr [esp+20h]
    L_00435f93:
        pop ebp
    L_00435f94:
        pop ebx
    L_00435f95:
        add esp,0Ch
    L_00435f98:
        ret 10h
    }
}
