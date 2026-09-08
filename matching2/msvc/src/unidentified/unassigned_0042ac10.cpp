#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AC10..0x0042AC10: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ac10() {
    __asm {
    L_0042ac10:
        ret
    }
}
