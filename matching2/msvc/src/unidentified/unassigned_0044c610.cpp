#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C610..0x0044C610: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044c610() {
    __asm {
    L_0044c610:
        ret
    }
}
