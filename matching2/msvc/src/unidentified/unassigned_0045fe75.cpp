#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FE75..0x0045FE7D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045fe75() {
    __asm {
    L_0045fe75:
        call asm_getptd_00456357
    L_0045fe7a:
        add eax,5Ch
    L_0045fe7d:
        ret
    }
}
