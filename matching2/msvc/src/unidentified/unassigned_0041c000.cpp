#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C000..0x0041C000: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c000() {
    __asm {
    L_0041c000:
        ret
    }
}
