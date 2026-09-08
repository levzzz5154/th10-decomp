#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457285..0x0045728D: FUN_00457285
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00457285_00457285() {
    __asm {
    L_00457285:
        push 6
    L_00457287:
        call asm_FUN_00453b3f_00453b3f
    L_0045728c:
        pop ecx
    L_0045728d:
        ret
    }
}
