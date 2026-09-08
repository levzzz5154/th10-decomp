#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452475..0x0045247D: FUN_00452475
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452475_00452475() {
    __asm {
    L_00452475:
        push 4
    L_00452477:
        call asm_FUN_00453b3f_00453b3f
    L_0045247c:
        pop ecx
    L_0045247d:
        ret
    }
}
