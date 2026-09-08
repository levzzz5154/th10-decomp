#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042DEB6..0x0042DEBF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042deb6() {
    __asm {
    L_0042deb6:
        lea esp,[esp+force_disp32_zero]
    L_0042debd:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
