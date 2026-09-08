#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004053E0..0x004053E0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004053e0() {
    __asm {
    L_004053e0:
        ret
    }
}
