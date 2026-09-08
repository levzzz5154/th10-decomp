#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408AB0..0x00408AB2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408ab0() {
    __asm {
    L_00408ab0:
        xor eax,eax
    L_00408ab2:
        ret
    }
}
