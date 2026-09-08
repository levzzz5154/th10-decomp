#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C5B0..0x0042C5B5: FUN_0042c5b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042c5b0_0042c5b0() {
    __asm {
    L_0042c5b0:
        mov eax,5ACCh
    L_0042c5b5:
        ret
    }
}
