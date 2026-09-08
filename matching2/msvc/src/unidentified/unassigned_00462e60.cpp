#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462E60..0x00462E7D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462e60() {
    __asm {
    L_00462e60:
        mov eax,dword ptr [eax]
    L_00462e62:
        cmp dword ptr [eax],0E06D7363h
    L_00462e68:
        je short L_00462e6d
    L_00462e6a:
        xor eax,eax
    L_00462e6c:
        ret
    L_00462e6d:
        call asm_getptd_00456357
    L_00462e72:
        and dword ptr [eax+84h],0
    L_00462e79:
        jmp asm_terminate_00455693
    }
}
