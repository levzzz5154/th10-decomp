#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004054FF..0x004054FF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004054ff() {
    __asm {
    L_004054ff:
        int 3
    }
}
