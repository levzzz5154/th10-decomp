#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402120..0x00402120: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00402120() {
    __asm {
    L_00402120:
        ret
    }
}
