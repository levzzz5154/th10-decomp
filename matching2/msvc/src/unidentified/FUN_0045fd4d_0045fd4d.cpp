#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FD4D..0x0045FD55: FUN_0045fd4d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045fd4d_0045fd4d() {
    __asm {
    L_0045fd4d:
        push 1
    L_0045fd4f:
        call asm_FUN_00453b3f_00453b3f
    L_0045fd54:
        pop ecx
    L_0045fd55:
        ret
    }
}
