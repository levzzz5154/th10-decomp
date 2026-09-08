#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402140..0x00402140: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402140() {
    __asm {
    L_00402140:
        ret
    }
}
