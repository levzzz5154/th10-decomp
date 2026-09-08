#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452BAA..0x00452D29: _localtime
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_localtime_00452baa() {
    __asm {
    L_00452baa:
        push ebp
    L_00452bab:
        mov ebp,esp
    L_00452bad:
        push esi
    L_00452bae:
        mov esi,dword ptr [ebp+8]
    L_00452bb1:
        cmp dword ptr [esi],0
    L_00452bb4:
        jge short L_00452bbd
    L_00452bb6:
        xor eax,eax
    L_00452bb8:
        jmp asm_target_00452cef
    L_00452bbd:
        call asm_tzset_004571cf
    L_00452bc2:
        mov eax,dword ptr [esi]
    L_00452bc4:
        cmp eax,3F480h
    L_00452bc9:
        jle short L_00452c23
    L_00452bcb:
        cmp eax,7FFC0B7Fh
    L_00452bd0:
        jge short L_00452c23
    L_00452bd2:
        sub eax,dword ptr [data_00473520]
    L_00452bd8:
        mov dword ptr [ebp+8],eax
    L_00452bdb:
        lea eax,[ebp+8]
    L_00452bde:
        push eax
    L_00452bdf:
        call asm_gmtime_0045728e
    L_00452be4:
        cmp dword ptr [data_00473524],0
    L_00452beb:
        pop ecx
    L_00452bec:
        mov esi,eax
    L_00452bee:
        je asm_target_00452ced
    L_00452bf4:
        push esi
    L_00452bf5:
        call asm_isindst_00457250
    L_00452bfa:
        test eax,eax
    L_00452bfc:
        pop ecx
    L_00452bfd:
        je asm_target_00452ced
    L_00452c03:
        mov eax,dword ptr [data_00473528]
    L_00452c08:
        sub dword ptr [ebp+8],eax
    L_00452c0b:
        lea eax,[ebp+8]
    L_00452c0e:
        push eax
    L_00452c0f:
        call asm_gmtime_0045728e
    L_00452c14:
        mov esi,eax
    L_00452c16:
        pop ecx
    L_00452c17:
        mov dword ptr [esi+20h],1
    L_00452c1e:
        jmp asm_target_00452ced
    L_00452c23:
        push esi
    L_00452c24:
        call asm_gmtime_0045728e
    L_00452c29:
        cmp dword ptr [data_00473524],0
    L_00452c30:
        pop ecx
    L_00452c31:
        mov esi,eax
    L_00452c33:
        je short L_00452c5d
    L_00452c35:
        push esi
    L_00452c36:
        call asm_isindst_00457250
    L_00452c3b:
        test eax,eax
    L_00452c3d:
        pop ecx
    L_00452c3e:
        je short L_00452c5d
    L_00452c40:
        mov eax,dword ptr [esi]
    L_00452c42:
        sub eax,dword ptr [data_00473528]
    L_00452c48:
        sub eax,dword ptr [data_00473520]
    L_00452c4e:
        mov dword ptr [ebp+8],eax
    L_00452c51:
        mov dword ptr [esi+20h],1
    L_00452c58:
        mov eax,dword ptr [ebp+8]
    L_00452c5b:
        jmp short L_00452c68
    L_00452c5d:
        mov eax,dword ptr [esi]
    L_00452c5f:
        sub eax,dword ptr [data_00473520]
    L_00452c65:
        mov dword ptr [ebp+8],eax
    L_00452c68:
        push ebx
    L_00452c69:
        push 3Ch
    L_00452c6b:
        pop ecx
    L_00452c6c:
        cdq
    L_00452c6d:
        mov ebx,ecx
    L_00452c6f:
        idiv ebx
    L_00452c71:
        test edx,edx
    L_00452c73:
        mov dword ptr [esi],edx
    L_00452c75:
        jge short L_00452c7e
    L_00452c77:
        add edx,ecx
    L_00452c79:
        mov dword ptr [esi],edx
    L_00452c7b:
        sub dword ptr [ebp+8],ecx
    L_00452c7e:
        mov eax,dword ptr [ebp+8]
    L_00452c81:
        cdq
    L_00452c82:
        mov ebx,ecx
    L_00452c84:
        idiv ebx
    L_00452c86:
        add eax,dword ptr [esi+4]
    L_00452c89:
        mov dword ptr [ebp+8],eax
    L_00452c8c:
        cdq
    L_00452c8d:
        idiv ebx
    L_00452c8f:
        pop ebx
    L_00452c90:
        test edx,edx
    L_00452c92:
        mov dword ptr [esi+4],edx
    L_00452c95:
        jge short L_00452ca0
    L_00452c97:
        add edx,3Ch
    L_00452c9a:
        mov dword ptr [esi+4],edx
    L_00452c9d:
        sub dword ptr [ebp+8],ecx
    L_00452ca0:
        mov eax,dword ptr [ebp+8]
    L_00452ca3:
        cdq
    L_00452ca4:
        idiv ecx
    L_00452ca6:
        push 18h
    L_00452ca8:
        pop ecx
    L_00452ca9:
        add eax,dword ptr [esi+8]
    L_00452cac:
        mov dword ptr [ebp+8],eax
    L_00452caf:
        cdq
    L_00452cb0:
        idiv ecx
    L_00452cb2:
        test edx,edx
    L_00452cb4:
        mov dword ptr [esi+8],edx
    L_00452cb7:
        jge short L_00452cc1
    L_00452cb9:
        add edx,ecx
    L_00452cbb:
        mov dword ptr [esi+8],edx
    L_00452cbe:
        sub dword ptr [ebp+8],ecx
    L_00452cc1:
        mov eax,dword ptr [ebp+8]
    L_00452cc4:
        push 18h
    L_00452cc6:
        cdq
    L_00452cc7:
        pop ecx
    L_00452cc8:
        idiv ecx
    L_00452cca:
        mov ecx,eax
    L_00452ccc:
        test ecx,ecx
    L_00452cce:
        mov dword ptr [ebp+8],ecx
    L_00452cd1:
        jle short L_00452cf2
    L_00452cd3:
        mov eax,dword ptr [esi+18h]
    L_00452cd6:
        add eax,ecx
    L_00452cd8:
        cdq
    L_00452cd9:
        push 7
    L_00452cdb:
        pop ecx
    L_00452cdc:
        idiv ecx
    L_00452cde:
        mov dword ptr [esi+18h],edx
    L_00452ce1:
        mov eax,dword ptr [ebp+8]
    L_00452ce4:
        add dword ptr [esi+0Ch],eax
    L_00452ce7:
        mov eax,dword ptr [ebp+8]
    L_00452cea:
        add dword ptr [esi+1Ch],eax
    L_00452ced:
        mov eax,esi
    L_00452cef:
        pop esi
    L_00452cf0:
        pop ebp
    L_00452cf1:
        ret
    L_00452cf2:
        jge short L_00452ced
    L_00452cf4:
        mov eax,dword ptr [esi+18h]
    L_00452cf7:
        lea eax,[eax+ecx+7]
    L_00452cfb:
        cdq
    L_00452cfc:
        push 7
    L_00452cfe:
        pop ecx
    L_00452cff:
        idiv ecx
    L_00452d01:
        mov dword ptr [esi+18h],edx
    L_00452d04:
        mov eax,dword ptr [ebp+8]
    L_00452d07:
        add dword ptr [esi+0Ch],eax
    L_00452d0a:
        mov eax,dword ptr [esi+0Ch]
    L_00452d0d:
        test eax,eax
    L_00452d0f:
        jg short L_00452ce7
    L_00452d11:
        add eax,1Fh
    L_00452d14:
        dec dword ptr [esi+14h]
    L_00452d17:
        mov dword ptr [esi+0Ch],eax
    L_00452d1a:
        mov dword ptr [esi+1Ch],16Ch
    L_00452d21:
        mov dword ptr [esi+10h],0Bh
    L_00452d28:
        jmp short L_00452ced
    }
}
