#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00449770..0x0044977E: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00449770() {
    __asm {
    L_00449770:
        add ecx,10h
    L_00449773:
        push esi
    L_00449774:
        TH10_REL8(0x74, 0x00449774, VA_asm_target_00449794)
    L_00449776:
        TH10_REL8(0xeb, 0x00449776, VA_asm_unassigned_00449780)
    L_00449778:
        lea esp,[esp+force_disp32_zero]
    }
}
