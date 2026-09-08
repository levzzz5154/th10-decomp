#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408AA0..0x00408AA2: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408aa0() {
    __asm {
    L_00408aa0:
        xor eax,eax
    L_00408aa2:
        ret
    }
}
