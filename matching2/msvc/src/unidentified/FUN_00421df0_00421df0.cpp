#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421DF0..0x00421DFA: FUN_00421df0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421df0_00421df0() {
    __asm {
    L_00421df0:
        mov dword ptr [eax+3ADA70h],0
    L_00421dfa:
        ret
    }
}
