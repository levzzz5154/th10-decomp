#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402150..0x00402150: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402150() {
    __asm {
    L_00402150:
        ret
    }
}
