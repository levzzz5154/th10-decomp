#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BFE0..0x0041BFE0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041bfe0() {
    __asm {
    L_0041bfe0:
        ret
    }
}
