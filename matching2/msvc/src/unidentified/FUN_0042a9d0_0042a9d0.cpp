#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A9D0..0x0042A9D3: FUN_0042a9d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a9d0_0042a9d0() {
    __asm {
    L_0042a9d0:
        mov ax,word ptr [eax]
    L_0042a9d3:
        ret
    }
}
