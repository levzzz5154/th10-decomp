#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421410..0x00421410: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421410() {
    __asm {
    L_00421410:
        ret
    }
}
