#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454D11..0x00454E29: __flsbuf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_flsbuf_00454d11() {
    __asm {
    L_00454d11:
        push ebp
    L_00454d12:
        mov ebp,esp
    L_00454d14:
        push ebx
    L_00454d15:
        push esi
    L_00454d16:
        mov esi,dword ptr [ebp+0Ch]
    L_00454d19:
        mov eax,dword ptr [esi+0Ch]
    L_00454d1c:
        test al,82h
    L_00454d1e:
        mov ebx,dword ptr [esi+10h]
    L_00454d21:
        je asm_target_00454e1d
    L_00454d27:
        test al,40h
    L_00454d29:
        jne asm_target_00454e1d
    L_00454d2f:
        test al,1
    L_00454d31:
        je short L_00454d4a
    L_00454d33:
        and dword ptr [esi+4],0
    L_00454d37:
        test al,10h
    L_00454d39:
        je asm_target_00454e1d
    L_00454d3f:
        mov ecx,dword ptr [esi+8]
    L_00454d42:
        and eax,0FFFFFFFEh
    L_00454d45:
        mov dword ptr [esi],ecx
    L_00454d47:
        mov dword ptr [esi+0Ch],eax
    L_00454d4a:
        mov eax,dword ptr [esi+0Ch]
    L_00454d4d:
        and dword ptr [esi+4],0
    L_00454d51:
        and dword ptr [ebp+0Ch],0
    L_00454d55:
        and eax,0FFFFFFEFh
    L_00454d58:
        or eax,2
    L_00454d5b:
        test ax,10Ch
    L_00454d5f:
        mov dword ptr [esi+0Ch],eax
    L_00454d62:
        jne short L_00454d86
    L_00454d64:
        cmp esi,473760h
    L_00454d6a:
        je short L_00454d74
    L_00454d6c:
        cmp esi,473780h
    L_00454d72:
        jne short L_00454d7f
    L_00454d74:
        push ebx
    L_00454d75:
        call asm_isatty_00459f7d
    L_00454d7a:
        test eax,eax
    L_00454d7c:
        pop ecx
    L_00454d7d:
        jne short L_00454d86
    L_00454d7f:
        push esi
    L_00454d80:
        call asm_getbuf_00459f39
    L_00454d85:
        pop ecx
    L_00454d86:
        test word ptr [esi+0Ch],108h
    L_00454d8c:
        push edi
    L_00454d8d:
        je short L_00454df3
    L_00454d8f:
        mov eax,dword ptr [esi+8]
    L_00454d92:
        mov edi,dword ptr [esi]
    L_00454d94:
        lea ecx,[eax+1]
    L_00454d97:
        mov dword ptr [esi],ecx
    L_00454d99:
        mov ecx,dword ptr [esi+18h]
    L_00454d9c:
        sub edi,eax
    L_00454d9e:
        dec ecx
    L_00454d9f:
        test edi,edi
    L_00454da1:
        mov dword ptr [esi+4],ecx
    L_00454da4:
        jle short L_00454db3
    L_00454da6:
        push edi
    L_00454da7:
        push eax
    L_00454da8:
        push ebx
    L_00454da9:
        call asm_write_00459e8e
    L_00454dae:
        mov dword ptr [ebp+0Ch],eax
    L_00454db1:
        jmp short L_00454de6
    L_00454db3:
        cmp ebx,0FFFFFFFFh
    L_00454db6:
        je short L_00454dd1
    L_00454db8:
        mov ecx,ebx
    L_00454dba:
        sar ecx,5
    L_00454dbd:
        mov ecx,dword ptr [ecx*4+499200h]
    L_00454dc4:
        mov eax,ebx
    L_00454dc6:
        and eax,1Fh
    L_00454dc9:
        lea eax,[eax+eax*8]
    L_00454dcc:
        lea eax,[ecx+eax*4]
    L_00454dcf:
        jmp short L_00454dd6
    L_00454dd1:
        mov eax,473708h
    L_00454dd6:
        test byte ptr [eax+4],20h
    L_00454dda:
        je short L_00454de9
    L_00454ddc:
        push 2
    L_00454dde:
        push 0
    L_00454de0:
        push ebx
    L_00454de1:
        call asm_lseek_00459c27
    L_00454de6:
        add esp,0Ch
    L_00454de9:
        mov eax,dword ptr [esi+8]
    L_00454dec:
        mov cl,byte ptr [ebp+8]
    L_00454def:
        mov byte ptr [eax],cl
    L_00454df1:
        jmp short L_00454e07
    L_00454df3:
        xor edi,edi
    L_00454df5:
        inc edi
    L_00454df6:
        push edi
    L_00454df7:
        lea eax,[ebp+8]
    L_00454dfa:
        push eax
    L_00454dfb:
        push ebx
    L_00454dfc:
        call asm_write_00459e8e
    L_00454e01:
        add esp,0Ch
    L_00454e04:
        mov dword ptr [ebp+0Ch],eax
    L_00454e07:
        cmp dword ptr [ebp+0Ch],edi
    L_00454e0a:
        pop edi
    L_00454e0b:
        je short L_00454e13
    L_00454e0d:
        or dword ptr [esi+0Ch],20h
    L_00454e11:
        jmp short L_00454e23
    L_00454e13:
        mov eax,dword ptr [ebp+8]
    L_00454e16:
        and eax,0FFh
    L_00454e1b:
        jmp short L_00454e26
    L_00454e1d:
        or eax,20h
    L_00454e20:
        mov dword ptr [esi+0Ch],eax
    L_00454e23:
        or eax,0FFFFFFFFh
    L_00454e26:
        pop esi
    L_00454e27:
        pop ebx
    L_00454e28:
        pop ebp
    L_00454e29:
        ret
    }
}
