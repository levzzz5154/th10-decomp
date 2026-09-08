#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B420..0x0042B420: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042b420() {
    __asm {
    L_0042b420:
        ret
    }
}
