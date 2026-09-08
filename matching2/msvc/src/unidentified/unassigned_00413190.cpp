#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413190..0x0041319D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413190() {
    __asm {
    L_00413190:
        push edi
    L_00413191:
        mov ecx,0Bh
    L_00413196:
        xor eax,eax
    L_00413198:
        mov edi,edx
    L_0041319a:
        rep stosd
    L_0041319c:
        pop edi
    L_0041319d:
        ret
    }
}
