#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF10..0x0044DF10: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044df10() {
    __asm {
    L_0044df10:
        ret
    }
}
