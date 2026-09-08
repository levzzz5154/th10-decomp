#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427E00..0x00427E00: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427e00() {
    __asm {
    L_00427e00:
        ret
    }
}
