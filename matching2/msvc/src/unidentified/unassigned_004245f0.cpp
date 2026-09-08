#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004245F0..0x004245F0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004245f0() {
    __asm {
    L_004245f0:
        ret
    }
}
