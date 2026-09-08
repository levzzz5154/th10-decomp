#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C070..0x0044C07C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c070() {
    __asm {
    L_0044c070:
        xor al,al
    L_0044c072:
        test edx,edx
    L_0044c074:
        je short L_0044c07c
    L_0044c076:
        add al,byte ptr [ecx]
    L_0044c078:
        inc ecx
    L_0044c079:
        dec edx
    L_0044c07a:
        jne short L_0044c076
    L_0044c07c:
        ret
    }
}
