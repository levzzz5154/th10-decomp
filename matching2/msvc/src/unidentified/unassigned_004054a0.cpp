#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004054A0..0x004054A5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004054a0() {
    __asm {
    L_004054a0:
        add eax,3C0h
    L_004054a5:
        ret
    }
}
