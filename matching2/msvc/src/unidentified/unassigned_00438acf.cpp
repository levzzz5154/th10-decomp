#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438ACF..0x00438ACF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00438acf() {
    __asm {
    L_00438acf:
        int 3
    }
}
