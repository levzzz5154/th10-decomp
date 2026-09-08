#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BAB0..0x0042BAB0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042bab0() {
    __asm {
    L_0042bab0:
        ret
    }
}
