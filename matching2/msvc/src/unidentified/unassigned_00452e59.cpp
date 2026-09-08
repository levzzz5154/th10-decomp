#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452E59..0x00452E59: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00452e59() {
    __asm {
    L_00452e59:
        pop esi
    }
}
