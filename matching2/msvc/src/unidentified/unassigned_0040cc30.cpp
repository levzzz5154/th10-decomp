#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CC30..0x0040CC35: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cc30() {
    __asm {
    L_0040cc30:
        add eax,23FCh
    L_0040cc35:
        ret
    }
}
