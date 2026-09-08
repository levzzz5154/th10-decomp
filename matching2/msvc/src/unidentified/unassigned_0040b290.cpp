#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B290..0x0040B290: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040b290() {
    __asm {
    L_0040b290:
        ret
    }
}
