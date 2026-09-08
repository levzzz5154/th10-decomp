#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040BA60..0x0040BA65: FUN_0040ba60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ba60_0040ba60() {
    __asm {
    L_0040ba60:
        mov eax,1
    L_0040ba65:
        ret
    }
}
