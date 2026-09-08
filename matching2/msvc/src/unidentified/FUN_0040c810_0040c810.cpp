#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C810..0x0040C814: FUN_0040c810
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c810_0040c810() {
    __asm {
    L_0040c810:
        xor eax,eax
    L_0040c812:
        ret 4
    }
}
