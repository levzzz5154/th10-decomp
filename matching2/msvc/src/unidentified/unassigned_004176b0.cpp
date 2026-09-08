#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004176B0..0x004176B0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004176b0() {
    __asm {
    L_004176b0:
        ret
    }
}
