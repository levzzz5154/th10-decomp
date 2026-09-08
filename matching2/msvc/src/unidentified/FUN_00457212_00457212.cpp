#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457212..0x0045721A: FUN_00457212
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457212_00457212() {
    __asm {
    L_00457212:
        push 6
    L_00457214:
        call asm_FUN_00453b3f_00453b3f
    L_00457219:
        pop ecx
    L_0045721a:
        ret
    }
}
