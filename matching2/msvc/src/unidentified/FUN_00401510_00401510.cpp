#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401510..0x00401516: FUN_00401510
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401510_00401510() {
    __asm {
    L_00401510:
        push ecx
    L_00401511:
        call asm_FUN_00401760_00401760
    L_00401516:
        ret
    }
}
