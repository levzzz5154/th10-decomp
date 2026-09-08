#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449A30..0x00449A40: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449a30() {
    __asm {
    L_00449a30:
        push edi
    L_00449a31:
        xor eax,eax
    L_00449a33:
        mov ecx,4Ch
    L_00449a38:
        mov edi,edx
    L_00449a3a:
        rep stosd
    L_00449a3c:
        mov eax,edx
    L_00449a3e:
        pop edi
    L_00449a3f:
        ret
    L_00449a40:
        ret
    }
}
