#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CBE0..0x0043CBE0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043cbe0() {
    __asm {
    L_0043cbe0:
        ret
    }
}
