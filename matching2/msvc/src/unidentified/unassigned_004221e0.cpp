#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004221E0..0x004221E2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004221e0() {
    __asm {
    L_004221e0:
        xor eax,eax
    L_004221e2:
        ret
    }
}
