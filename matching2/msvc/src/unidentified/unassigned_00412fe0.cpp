#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412FE0..0x00412FE0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00412fe0() {
    __asm {
    L_00412fe0:
        ret
    }
}
