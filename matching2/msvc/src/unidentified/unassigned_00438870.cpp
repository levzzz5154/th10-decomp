#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438870..0x00438870: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438870() {
    __asm {
    L_00438870:
        ret
    }
}
