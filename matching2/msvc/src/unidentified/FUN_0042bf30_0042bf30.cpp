#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BF30..0x0042BF72: FUN_0042bf30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042bf30_0042bf30() {
    __asm {
    L_0042bf30:
        push ebx
    L_0042bf31:
        push 2E4h
    L_0042bf36:
        call asm_operator_new_00452493
    L_0042bf3b:
        add esp,4
    L_0042bf3e:
        test eax,eax
    L_0042bf40:
        je short L_0042bf4d
    L_0042bf42:
        mov edx,eax
    L_0042bf44:
        call asm_FUN_0042bb30_0042bb30
    L_0042bf49:
        mov ebx,eax
    L_0042bf4b:
        jmp short L_0042bf4f
    L_0042bf4d:
        xor ebx,ebx
    L_0042bf4f:
        call asm_FUN_0042bbd0_0042bbd0
    L_0042bf54:
        test eax,eax
    L_0042bf56:
        je short L_0042bf6f
    L_0042bf58:
        test ebx,ebx
    L_0042bf5a:
        je short L_0042bf6b
    L_0042bf5c:
        push ebx
    L_0042bf5d:
        call asm_FUN_0042bc30_0042bc30
    L_0042bf62:
        push ebx
    L_0042bf63:
        call asm_free_004524a1
    L_0042bf68:
        add esp,4
    L_0042bf6b:
        xor eax,eax
    L_0042bf6d:
        pop ebx
    L_0042bf6e:
        ret
    L_0042bf6f:
        mov eax,ebx
    L_0042bf71:
        pop ebx
    L_0042bf72:
        ret
    }
}
