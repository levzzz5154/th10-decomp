#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420DC0..0x00420DC0: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420dc0() {
    __asm {
    L_00420dc0:
        ret
    }
}
