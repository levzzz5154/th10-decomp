#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C020..0x0041C020: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c020() {
    __asm {
    L_0041c020:
        ret
    }
}
