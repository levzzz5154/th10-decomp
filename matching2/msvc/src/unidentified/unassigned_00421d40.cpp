#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421D40..0x00421D40: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421d40() {
    __asm {
    L_00421d40:
        ret
    }
}
