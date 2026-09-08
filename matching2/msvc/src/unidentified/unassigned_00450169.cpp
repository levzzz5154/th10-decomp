#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450169..0x0045016F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00450169() {
    __asm {
    L_00450169:
        lea esp,[esp+force_disp32_zero]
    }
}
