#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004535ED..0x004535ED: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004535ed() {
    __asm {
    L_004535ed:
        pop esi
    }
}
