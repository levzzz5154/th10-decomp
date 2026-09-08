#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462A13..0x00462A33: IsExceptionObjectToBeDestroyed
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_IsExceptionObjectToBeDestroyed_00462a13() {
    __asm {
    L_00462a13:
        call asm_getptd_00456357
    L_00462a18:
        mov eax,dword ptr [eax+88h]
    L_00462a1e:
        jmp short L_00462a2b
    L_00462a20:
        mov ecx,dword ptr [eax]
    L_00462a22:
        cmp ecx,dword ptr [esp+4]
    L_00462a26:
        je short L_00462a31
    L_00462a28:
        mov eax,dword ptr [eax+4]
    L_00462a2b:
        test eax,eax
    L_00462a2d:
        jne short L_00462a20
    L_00462a2f:
        inc eax
    L_00462a30:
        ret
    L_00462a31:
        xor eax,eax
    L_00462a33:
        ret
    }
}
