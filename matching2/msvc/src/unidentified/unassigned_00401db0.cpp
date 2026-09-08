#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401DB0..0x00401DB0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00401db0() {
    __asm {
    L_00401db0:
        ret
    }
}
