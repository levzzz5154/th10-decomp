#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D2A3..0x0045D2AB: FUN_0045d2a3
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045d2a3_0045d2a3() {
    __asm {
    L_0045d2a3:
        push 0Dh
    L_0045d2a5:
        call asm_FUN_00453b3f_00453b3f
    L_0045d2aa:
        pop ecx
    L_0045d2ab:
        ret
    }
}
