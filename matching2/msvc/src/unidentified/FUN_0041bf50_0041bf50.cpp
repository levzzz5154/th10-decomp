#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF50..0x0041BF54: FUN_0041bf50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf50_0041bf50() {
    __asm {
    L_0041bf50:
        xor eax,eax
    L_0041bf52:
        ret 0Ch
    }
}
