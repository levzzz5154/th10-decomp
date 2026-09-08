#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DC17..0x0045DC7B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045dc17() {
    __asm {
    L_0045dc17:
        mov eax,dword ptr [esp+4]
    L_0045dc1b:
        push ebx
    L_0045dc1c:
        mov bl,byte ptr [data_00473af4]
    L_0045dc22:
        jmp short L_0045dc29
    L_0045dc24:
        cmp cl,bl
    L_0045dc26:
        je short L_0045dc2f
    L_0045dc28:
        inc eax
    L_0045dc29:
        mov cl,byte ptr [eax]
    L_0045dc2b:
        test cl,cl
    L_0045dc2d:
        jne short L_0045dc24
    L_0045dc2f:
        mov cl,byte ptr [eax]
    L_0045dc31:
        inc eax
    L_0045dc32:
        test cl,cl
    L_0045dc34:
        je short L_0045dc60
    L_0045dc36:
        jmp short L_0045dc43
    L_0045dc38:
        cmp cl,65h
    L_0045dc3b:
        je short L_0045dc49
    L_0045dc3d:
        cmp cl,45h
    L_0045dc40:
        je short L_0045dc49
    L_0045dc42:
        inc eax
    L_0045dc43:
        mov cl,byte ptr [eax]
    L_0045dc45:
        test cl,cl
    L_0045dc47:
        jne short L_0045dc38
    L_0045dc49:
        mov edx,eax
    L_0045dc4b:
        dec eax
    L_0045dc4c:
        cmp byte ptr [eax],30h
    L_0045dc4f:
        je short L_0045dc4b
    L_0045dc51:
        cmp byte ptr [eax],bl
    L_0045dc53:
        jne short L_0045dc56
    L_0045dc55:
        dec eax
    L_0045dc56:
        mov cl,byte ptr [edx]
    L_0045dc58:
        inc eax
    L_0045dc59:
        inc edx
    L_0045dc5a:
        test cl,cl
    L_0045dc5c:
        mov byte ptr [eax],cl
    L_0045dc5e:
        jne short L_0045dc56
    L_0045dc60:
        pop ebx
    L_0045dc61:
        ret
    L_0045dc62:
        mov eax,dword ptr [esp+4]
    L_0045dc66:
        fld qword ptr [eax]
    L_0045dc68:
        fcomp qword ptr [data_00470b70]
    L_0045dc6e:
        fnstsw ax
    L_0045dc70:
        test ah,1
    L_0045dc73:
        jne short L_0045dc79
    L_0045dc75:
        xor eax,eax
    L_0045dc77:
        inc eax
    L_0045dc78:
        ret
    L_0045dc79:
        xor eax,eax
    L_0045dc7b:
        ret
    }
}
