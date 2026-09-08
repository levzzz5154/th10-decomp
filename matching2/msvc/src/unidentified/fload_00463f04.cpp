#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463F04..0x00463F3F: __fload
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_fload_00463f04() {
    __asm {
    L_00463f04:
        push ebp
    L_00463f05:
        mov ebp,esp
    L_00463f07:
        add esp,0FFFFFFF4h
    L_00463f0a:
        push ebx
    L_00463f0b:
        mov ax,word ptr [ebp+0Eh]
    L_00463f0f:
        mov bx,ax
    L_00463f12:
        and ax,7FF0h
    L_00463f16:
        cmp ax,7FF0h
    L_00463f1a:
        jne short L_00463f3a
    L_00463f1c:
        or bx,7FFFh
    L_00463f21:
        mov word ptr [ebp-2],bx
    L_00463f25:
        mov eax,dword ptr [ebp+0Ch]
    L_00463f28:
        mov ebx,dword ptr [ebp+8]
    L_00463f2b:
        shld eax,ebx,0Bh
    L_00463f2f:
        mov dword ptr [ebp-6],eax
    L_00463f32:
        mov dword ptr [ebp-0Ah],ebx
    L_00463f35:
        fld tbyte ptr [ebp-0Ah]
    L_00463f38:
        jmp short L_00463f3d
    L_00463f3a:
        fld qword ptr [ebp+8]
    L_00463f3d:
        pop ebx
    L_00463f3e:
        leave
    L_00463f3f:
        ret
    }
}
