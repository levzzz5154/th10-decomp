#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424610..0x00424615: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424610() {
    __asm {
    L_00424610:
        add eax,3CCh
    L_00424615:
        ret
    }
}
