#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045570D..0x00455730: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045570d() {
    __asm {
    L_0045570d:
        push esi
    L_0045570e:
        push 4
    L_00455710:
        call asm_lock_00453c0c
    L_00455715:
        mov eax,dword ptr [esp+0Ch]
    L_00455719:
        mov esi,dword ptr [data_00477360]
    L_0045571f:
        push 4
    L_00455721:
        mov dword ptr [data_00477360],eax
    L_00455726:
        call asm_FUN_00453b3f_00453b3f
    L_0045572b:
        pop ecx
    L_0045572c:
        pop ecx
    L_0045572d:
        mov eax,esi
    L_0045572f:
        pop esi
    L_00455730:
        ret
    }
}
