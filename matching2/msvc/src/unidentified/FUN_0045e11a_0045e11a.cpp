#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E11A..0x0045E122: FUN_0045e11a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045e11a_0045e11a() {
    __asm {
    L_0045e11a:
        push 7
    L_0045e11c:
        call asm_FUN_00453b3f_00453b3f
    L_0045e121:
        pop ecx
    L_0045e122:
        ret
    }
}
