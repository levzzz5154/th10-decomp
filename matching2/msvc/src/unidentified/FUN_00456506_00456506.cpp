#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456506..0x0045650E: FUN_00456506
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456506_00456506() {
    __asm {
    L_00456506:
        push 0Ch
    L_00456508:
        call asm_FUN_00453b3f_00453b3f
    L_0045650d:
        pop ecx
    L_0045650e:
        ret
    }
}
