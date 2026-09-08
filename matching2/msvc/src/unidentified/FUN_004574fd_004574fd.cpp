#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004574FD..0x00457505: FUN_004574fd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004574fd_004574fd() {
    __asm {
    L_004574fd:
        push 4
    L_004574ff:
        call asm_FUN_00453b3f_00453b3f
    L_00457504:
        pop ecx
    L_00457505:
        ret
    }
}
