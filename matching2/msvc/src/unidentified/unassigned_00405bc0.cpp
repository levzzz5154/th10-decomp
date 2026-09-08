#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405BC0..0x00405BC0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405bc0() {
    __asm {
    L_00405bc0:
        ret
    }
}
