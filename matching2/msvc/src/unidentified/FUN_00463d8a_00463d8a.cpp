#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463D8A..0x00463ED0: FUN_00463d8a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00463d8a_00463d8a() {
    __asm {
    L_00463d8a:
        cmp dword ptr [data_00477384],0
    L_00463d91:
        jne short L_00463de2
    L_00463d93:
        fst qword ptr [ebp-2D0h]
    L_00463d99:
        mov al,byte ptr [ebp-90h]
    L_00463d9f:
        or al,al
    L_00463da1:
        je short L_00463dbd
    L_00463da3:
        cmp al,0FFh
    L_00463da5:
        je short L_00463e02
    L_00463da7:
        cmp al,0FEh
    L_00463da9:
        je short L_00463dea
    L_00463dab:
        or al,al
    L_00463dad:
        je short L_00463de2
    L_00463daf:
        movsx eax,al
    L_00463db2:
        mov dword ptr [ebp-8Eh],eax
    L_00463db8:
        jmp asm_target_00463e6f
    L_00463dbd:
        mov ax,word ptr [ebp-0A4h]
    L_00463dc4:
        TH10_OPERAND16()
        and eax,20h
    L_00463dc8:
        jne short L_00463de2
    L_00463dca:
        wait
        fnstsw ax
    L_00463dcd:
        TH10_OPERAND16()
        and eax,20h
    L_00463dd1:
        je short L_00463de2
    L_00463dd3:
        mov dword ptr [ebp-8Eh],8
    L_00463ddd:
        jmp asm_target_00463e6f
    L_00463de2:
        fldcw word ptr [ebp-0A4h]
    L_00463de8:
        wait
    L_00463de9:
        ret
    L_00463dea:
        mov ax,word ptr [ebp-2CAh]
    L_00463df1:
        and ax,7FF0h
    L_00463df5:
        or ax,ax
    L_00463df8:
        je short L_00463e15
    L_00463dfa:
        cmp ax,7FF0h
    L_00463dfe:
        je short L_00463e43
    L_00463e00:
        jmp short L_00463dbd
    L_00463e02:
        mov ax,word ptr [ebp-2CAh]
    L_00463e09:
        and ax,7FF0h
    L_00463e0d:
        cmp ax,7FF0h
    L_00463e11:
        je short L_00463e43
    L_00463e13:
        jmp short L_00463dbd
    L_00463e15:
        mov dword ptr [ebp-8Eh],4
    L_00463e1f:
        fld qword ptr [data_00470d78]
    L_00463e25:
        fxch
    L_00463e27:
        fscale
    L_00463e29:
        fstp st(1)
    L_00463e2b:
        fld st(0)
    L_00463e2d:
        fabs
    L_00463e2f:
        fcomp qword ptr [data_00470d68]
    L_00463e35:
        wait
        fnstsw ax
    L_00463e38:
        sahf
    L_00463e39:
        jae short L_00463e6f
    L_00463e3b:
        fmul qword ptr [data_00470d88]
    L_00463e41:
        jmp short L_00463e6f
    L_00463e43:
        mov dword ptr [ebp-8Eh],3
    L_00463e4d:
        fld qword ptr [data_00470d70]
    L_00463e53:
        fxch
    L_00463e55:
        fscale
    L_00463e57:
        fstp st(1)
    L_00463e59:
        fld st(0)
    L_00463e5b:
        fabs
    L_00463e5d:
        fcomp qword ptr [data_00470d60]
    L_00463e63:
        wait
        fnstsw ax
    L_00463e66:
        sahf
    L_00463e67:
        jbe short L_00463e6f
    L_00463e69:
        fmul qword ptr [data_00470d80]
    L_00463e6f:
        push esi
    L_00463e70:
        push edi
    L_00463e71:
        mov ebx,dword ptr [ebp-94h]
    L_00463e77:
        inc ebx
    L_00463e78:
        mov dword ptr [ebp-8Ah],ebx
    L_00463e7e:
        test byte ptr [ebp-2C8h],1
    L_00463e85:
        jne short L_00463ea1
    L_00463e87:
        cld
    L_00463e88:
        lea esi,[ebp+8]
    L_00463e8b:
        lea edi,[ebp-86h]
    L_00463e91:
        movsd
    L_00463e92:
        movsd
    L_00463e93:
        cmp byte ptr [ebx+0Ch],1
    L_00463e97:
        je short L_00463ea1
    L_00463e99:
        lea esi,[ebp+10h]
    L_00463e9c:
        lea edi,[ebp-7Eh]
    L_00463e9f:
        movsd
    L_00463ea0:
        movsd
    L_00463ea1:
        fstp qword ptr [ebp-76h]
    L_00463ea4:
        lea eax,[ebp-8Eh]
    L_00463eaa:
        lea ebx,[ebp-0A4h]
    L_00463eb0:
        push ebx
    L_00463eb1:
        push eax
    L_00463eb2:
        mov ebx,dword ptr [ebp-94h]
    L_00463eb8:
        mov al,byte ptr [ebx+0Eh]
    L_00463ebb:
        movsx eax,al
    L_00463ebe:
        push eax
    L_00463ebf:
        call asm_FUN_0046508c_0046508c
    L_00463ec4:
        add esp,0Ch
    L_00463ec7:
        pop edi
    L_00463ec8:
        pop esi
    L_00463ec9:
        fld qword ptr [ebp-76h]
    L_00463ecc:
        jmp asm_target_00463de2
    }
}
