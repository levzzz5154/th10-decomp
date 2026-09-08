#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449C28..0x00449C2E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449c28() {
    __asm {
    L_00449c28:
        lea esp,[esp+force_disp32_zero]
    }
}
