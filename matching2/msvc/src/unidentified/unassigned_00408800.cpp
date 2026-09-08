#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408800..0x00408800: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408800() {
    __asm {
    L_00408800:
        ret
    }
}
