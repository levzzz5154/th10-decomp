#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463C04..0x00463C0C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463c04() {
    __asm {
    L_00463c04:
        lea edx,[esp+4]
    L_00463c08:
        call asm_unassigned_00464f45
    }
}
