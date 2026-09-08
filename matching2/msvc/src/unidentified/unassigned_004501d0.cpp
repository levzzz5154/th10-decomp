#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004501D0..0x004501D0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004501d0() {
    __asm {
    L_004501d0:
        ret
    }
}
