#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A1B0..0x0043A1B7: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a1b0() {
    __asm {
    L_0043a1b0:
        push eax
    L_0043a1b1:
        call dword ptr [data_004661f0]
    L_0043a1b7:
        ret
    }
}
