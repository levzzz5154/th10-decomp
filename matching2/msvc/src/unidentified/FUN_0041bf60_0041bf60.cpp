#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BF60..0x0041BF64: FUN_0041bf60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bf60_0041bf60() {
    __asm {
    L_0041bf60:
        xor eax,eax
    L_0041bf62:
        ret 0Ch
    }
}
