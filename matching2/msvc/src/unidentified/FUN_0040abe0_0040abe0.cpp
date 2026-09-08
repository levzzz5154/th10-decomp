#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040ABE0..0x0040ABE6: FUN_0040abe0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040abe0_0040abe0() {
    __asm {
    L_0040abe0:
        push ecx
    L_0040abe1:
        call asm_FUN_0040a450_0040a450
    L_0040abe6:
        ret
    }
}
