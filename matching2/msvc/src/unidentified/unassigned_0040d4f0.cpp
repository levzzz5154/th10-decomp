#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D4F0..0x0040D4F2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040d4f0() {
    __asm {
    L_0040d4f0:
        xor eax,eax
    L_0040d4f2:
        ret
    }
}
