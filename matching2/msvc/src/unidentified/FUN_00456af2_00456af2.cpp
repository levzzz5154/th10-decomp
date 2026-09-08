#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456AF2..0x00456AFA: FUN_00456af2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456af2_00456af2() {
    __asm {
    L_00456af2:
        call asm_getptd_00456357
    L_00456af7:
        add eax,8
    L_00456afa:
        ret
    }
}
