#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436AA0..0x00436AEB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436aa0() {
    __asm {
    L_00436aa0:
        push ebp
    L_00436aa1:
        mov ebp,dword ptr [esp+8]
    L_00436aa5:
        push ebp
    L_00436aa6:
        push esi
    L_00436aa7:
        push edi
    L_00436aa8:
        mov eax,ebx
    L_00436aaa:
        call asm_FUN_00436af0_00436af0
    L_00436aaf:
        test al,al
    L_00436ab1:
        je short L_00436ab9
    L_00436ab3:
        mov al,1
    L_00436ab5:
        pop ebp
    L_00436ab6:
        ret 4
    L_00436ab9:
        cmp ebp,19h
    L_00436abc:
        je short L_00436add
    L_00436abe:
        cmp ebp,1Ah
    L_00436ac1:
        je short L_00436add
    L_00436ac3:
        cmp ebp,17h
    L_00436ac6:
        jne short L_00436ad7
    L_00436ac8:
        push 16h
    L_00436aca:
        push esi
    L_00436acb:
        mov eax,ebx
    L_00436acd:
        push edi
    L_00436ace:
        call asm_FUN_00436af0_00436af0
    L_00436ad3:
        pop ebp
    L_00436ad4:
        ret 4
    L_00436ad7:
        xor al,al
    L_00436ad9:
        pop ebp
    L_00436ada:
        ret 4
    L_00436add:
        push 15h
    L_00436adf:
        push esi
    L_00436ae0:
        mov eax,ebx
    L_00436ae2:
        push edi
    L_00436ae3:
        call asm_FUN_00436af0_00436af0
    L_00436ae8:
        pop ebp
    L_00436ae9:
        ret 4
    }
}
