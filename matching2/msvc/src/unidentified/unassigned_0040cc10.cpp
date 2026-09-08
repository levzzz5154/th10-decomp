#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CC10..0x0040CC13: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cc10() {
    __asm {
    L_0040cc10:
        add eax,2Ch
    L_0040cc13:
        ret
    }
}
