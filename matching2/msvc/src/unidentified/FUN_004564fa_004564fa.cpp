#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004564FA..0x00456502: FUN_004564fa
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004564fa_004564fa() {
    __asm {
    L_004564fa:
        push 0Dh
    L_004564fc:
        call asm_FUN_00453b3f_00453b3f
    L_00456501:
        pop ecx
    L_00456502:
        ret
    }
}
