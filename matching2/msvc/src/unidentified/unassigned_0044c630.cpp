#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C630..0x0044C630: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c630() {
    __asm {
    L_0044c630:
        ret
    }
}
