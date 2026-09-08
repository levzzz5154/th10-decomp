#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BD72..0x0045BD74: FUN_0045bd72
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045bd72_0045bd72() {
    __asm {
    L_0045bd72:
        xor eax,eax
    L_0045bd74:
        ret
    }
}
