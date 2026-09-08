#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045258F..0x004525A0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045258f() {
    __asm {
    L_0045258f:
        mov eax,dword ptr [eax]
    L_00452591:
        cmp dword ptr [eax],0E06D7363h
    L_00452597:
        je short L_0045259c
    L_00452599:
        xor eax,eax
    L_0045259b:
        ret
    L_0045259c:
        jmp asm_terminate_00455693
    }
}
