#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045375F..0x00453761: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045375f() {
    __asm {
    L_0045375f:
        pop ecx
    L_00453760:
        pop ecx
    L_00453761:
        ret
    }
}
