#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042C580..0x0042C584: thunk_FUN_0042bfc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_thunk_FUN_0042bfc0_0042c580() {
    __asm {
    L_0042c580:
        jmp asm_FUN_0042bfc0_0042bfc0
    }
}
