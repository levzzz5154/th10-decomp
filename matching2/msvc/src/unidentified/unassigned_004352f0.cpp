#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004352F0..0x004352F0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004352f0() {
    __asm {
    L_004352f0:
        ret
    }
}
