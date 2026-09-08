#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453B60..0x00453B69: FUN_00453b60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00453b60_00453b60() {
    __asm {
    L_00453b60:
        push 0FFh
    L_00453b65:
        call asm_crtExitProcess_00457547
    }
}
