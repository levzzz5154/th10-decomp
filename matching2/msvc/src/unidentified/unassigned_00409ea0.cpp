#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409EA0..0x00409EA0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00409ea0() {
    __asm {
    L_00409ea0:
        ret
    }
}
