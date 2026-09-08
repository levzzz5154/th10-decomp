#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458D91..0x00458E73: __resetstkoflw
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_resetstkoflw_00458d91() {
    __asm {
    L_00458d91:
        push ebp
    L_00458d92:
        mov ebp,esp
    L_00458d94:
        sub esp,4Ch
    L_00458d97:
        push ebx
    L_00458d98:
        push esi
    L_00458d99:
        push edi
    L_00458d9a:
        push 4
    L_00458d9c:
        pop eax
    L_00458d9d:
        call asm_chkstk_00458ec0
    L_00458da2:
        mov esi,esp
    L_00458da4:
        push 1Ch
    L_00458da6:
        lea eax,[ebp-28h]
    L_00458da9:
        push eax
    L_00458daa:
        push esi
    L_00458dab:
        call dword ptr [data_0046609c]
    L_00458db1:
        test eax,eax
    L_00458db3:
        je short L_00458e2c
    L_00458db5:
        mov ebx,dword ptr [ebp-24h]
    L_00458db8:
        lea eax,[ebp-4Ch]
    L_00458dbb:
        push eax
    L_00458dbc:
        call dword ptr [data_00466134]
    L_00458dc2:
        mov ecx,dword ptr [ebp-48h]
    L_00458dc5:
        mov eax,dword ptr [data_00477470]
    L_00458dca:
        lea edi,[ecx-1]
    L_00458dcd:
        not edi
    L_00458dcf:
        and edi,esi
    L_00458dd1:
        sub edi,ecx
    L_00458dd3:
        mov esi,eax
    L_00458dd5:
        dec esi
    L_00458dd6:
        neg esi
    L_00458dd8:
        sbb esi,esi
    L_00458dda:
        and esi,0FFFFFFF1h
    L_00458ddd:
        add esi,11h
    L_00458de0:
        imul esi,ecx
    L_00458de3:
        add esi,ebx
    L_00458de5:
        cmp edi,esi
    L_00458de7:
        mov dword ptr [ebp-8],ecx
    L_00458dea:
        jb short L_00458e2c
    L_00458dec:
        cmp eax,1
    L_00458def:
        je short L_00458e4d
    L_00458df1:
        mov dword ptr [ebp-4],ebx
    L_00458df4:
        mov ebx,1000h
    L_00458df9:
        push 1Ch
    L_00458dfb:
        lea eax,[ebp-28h]
    L_00458dfe:
        push eax
    L_00458dff:
        push dword ptr [ebp-4]
    L_00458e02:
        call dword ptr [data_0046609c]
    L_00458e08:
        test eax,eax
    L_00458e0a:
        je short L_00458e2c
    L_00458e0c:
        mov eax,dword ptr [ebp-1Ch]
    L_00458e0f:
        add dword ptr [ebp-4],eax
    L_00458e12:
        test dword ptr [ebp-18h],ebx
    L_00458e15:
        je short L_00458df9
    L_00458e17:
        test byte ptr [ebp-13h],1
    L_00458e1b:
        mov eax,dword ptr [ebp-28h]
    L_00458e1e:
        mov dword ptr [ebp-4],eax
    L_00458e21:
        je short L_00458e28
    L_00458e23:
        xor eax,eax
    L_00458e25:
        inc eax
    L_00458e26:
        jmp short L_00458e6c
    L_00458e28:
        cmp edi,eax
    L_00458e2a:
        jae short L_00458e30
    L_00458e2c:
        xor eax,eax
    L_00458e2e:
        jmp short L_00458e6c
    L_00458e30:
        cmp eax,esi
    L_00458e32:
        jae short L_00458e37
    L_00458e34:
        mov dword ptr [ebp-4],esi
    L_00458e37:
        push 4
    L_00458e39:
        push ebx
    L_00458e3a:
        push dword ptr [ebp-8]
    L_00458e3d:
        push dword ptr [ebp-4]
    L_00458e40:
        call dword ptr [data_0046617c]
    L_00458e46:
        mov eax,dword ptr [data_00477470]
    L_00458e4b:
        jmp short L_00458e50
    L_00458e4d:
        mov dword ptr [ebp-4],edi
    L_00458e50:
        dec eax
    L_00458e51:
        neg eax
    L_00458e53:
        sbb eax,eax
    L_00458e55:
        and eax,103h
    L_00458e5a:
        lea ecx,[ebp-0Ch]
    L_00458e5d:
        push ecx
    L_00458e5e:
        inc eax
    L_00458e5f:
        push eax
    L_00458e60:
        push dword ptr [ebp-8]
    L_00458e63:
        push dword ptr [ebp-4]
    L_00458e66:
        call dword ptr [data_00466138]
    L_00458e6c:
        lea esp,[ebp-58h]
    L_00458e6f:
        pop edi
    L_00458e70:
        pop esi
    L_00458e71:
        pop ebx
    L_00458e72:
        leave
    L_00458e73:
        ret
    }
}
