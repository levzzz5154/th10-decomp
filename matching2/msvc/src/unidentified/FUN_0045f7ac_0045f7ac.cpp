#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F7AC..0x0045F7B4: FUN_0045f7ac
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045f7ac_0045f7ac() {
    __asm {
    L_0045f7ac:
        push 0Ah
    L_0045f7ae:
        call asm_FUN_00453b3f_00453b3f
    L_0045f7b3:
        pop ecx
    L_0045f7b4:
        ret
    }
}
