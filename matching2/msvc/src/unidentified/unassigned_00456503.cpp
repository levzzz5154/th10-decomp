#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456503..0x00456505: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00456503() {
    __asm {
    L_00456503:
        mov esi,dword ptr [ebp+8]
    }
}
