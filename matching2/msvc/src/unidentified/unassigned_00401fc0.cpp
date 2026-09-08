#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401FC0..0x00401FC0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401fc0() {
    __asm {
    L_00401fc0:
        ret
    }
}
