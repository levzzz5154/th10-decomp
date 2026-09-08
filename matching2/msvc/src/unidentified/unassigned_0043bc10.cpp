#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BC10..0x0043BC13: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043bc10() {
    __asm {
    L_0043bc10:
        add eax,0Ch
    L_0043bc13:
        ret
    }
}
