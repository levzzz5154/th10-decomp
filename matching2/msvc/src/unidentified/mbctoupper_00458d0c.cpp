#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458D0C..0x00458D90: __mbctoupper
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mbctoupper_00458d0c() {
    __asm {
    L_00458d0c:
        push ebp
    L_00458d0d:
        mov ebp,esp
    L_00458d0f:
        push ecx
    L_00458d10:
        push ecx
    L_00458d11:
        call asm_getptd_00456357
    L_00458d16:
        mov eax,dword ptr [eax+60h]
    L_00458d19:
        cmp eax,dword ptr [data_00497f94]
    L_00458d1f:
        je short L_00458d26
    L_00458d21:
        call asm_updatetmbcinfo_0045cf49
    L_00458d26:
        push ebx
    L_00458d27:
        mov ebx,dword ptr [ebp+8]
    L_00458d2a:
        cmp ebx,0FFh
    L_00458d30:
        jbe short L_00458d7b
    L_00458d32:
        mov ecx,ebx
    L_00458d34:
        shr ecx,8
    L_00458d37:
        mov byte ptr [ebp-4],cl
    L_00458d3a:
        movzx ecx,cl
    L_00458d3d:
        mov byte ptr [ebp-3],bl
    L_00458d40:
        test byte ptr [ecx+eax+1Dh],4
    L_00458d45:
        je short L_00458d8c
    L_00458d47:
        push 1
    L_00458d49:
        push dword ptr [eax+4]
    L_00458d4c:
        lea ecx,[ebp-8]
    L_00458d4f:
        push 2
    L_00458d51:
        push ecx
    L_00458d52:
        push 2
    L_00458d54:
        lea ecx,[ebp-4]
    L_00458d57:
        push ecx
    L_00458d58:
        push 200h
    L_00458d5d:
        push dword ptr [eax+0Ch]
    L_00458d60:
        call asm_FUN_0045ee1d_0045ee1d
    L_00458d65:
        add esp,20h
    L_00458d68:
        test eax,eax
    L_00458d6a:
        je short L_00458d8c
    L_00458d6c:
        movzx eax,byte ptr [ebp-8]
    L_00458d70:
        movzx ecx,byte ptr [ebp-7]
    L_00458d74:
        shl eax,8
    L_00458d77:
        add eax,ecx
    L_00458d79:
        jmp short L_00458d8e
    L_00458d7b:
        add eax,ebx
    L_00458d7d:
        test byte ptr [eax+1Dh],20h
    L_00458d81:
        je short L_00458d8c
    L_00458d83:
        movsx eax,byte ptr [eax+11Dh]
    L_00458d8a:
        jmp short L_00458d8e
    L_00458d8c:
        mov eax,ebx
    L_00458d8e:
        pop ebx
    L_00458d8f:
        leave
    L_00458d90:
        ret
    }
}
