#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409E40..0x00409E40: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00409e40() {
    __asm {
    L_00409e40:
        ret
    }
}
