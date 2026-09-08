#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462B72..0x00462B7A: FUN_00462b72
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00462b72_00462b72() {
    __asm {
    L_00462b72:
        push 0Eh
    L_00462b74:
        call asm_FUN_00453b3f_00453b3f
    L_00462b79:
        pop ecx
    L_00462b7a:
        ret
    }
}
