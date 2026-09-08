#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043DBD9..0x0043DBDF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043dbd9() {
    __asm {
    L_0043dbd9:
        lea esp,[esp+force_disp32_zero]
    }
}
