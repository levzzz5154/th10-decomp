#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042CA3D..0x0042CA3F: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042ca3d() {
    __asm {
    L_0042ca3d:
        TH10_NOP_LEA_ECX_DISP8()
    }
}
