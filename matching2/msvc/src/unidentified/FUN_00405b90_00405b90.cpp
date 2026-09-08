#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405B90..0x00405B94: FUN_00405b90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00405b90_00405b90() {
    __asm {
    L_00405b90:
        mov ax,word ptr [eax+8]
    L_00405b94:
        ret
    }
}
