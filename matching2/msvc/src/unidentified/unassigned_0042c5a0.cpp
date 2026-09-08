#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C5A0..0x0042C5A0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042c5a0() {
    __asm {
    L_0042c5a0:
        ret
    }
}
