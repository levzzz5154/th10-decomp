#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00426500..0x00426506: FUN_00426500
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426500_00426500() {
    __asm {
    L_00426500:
        push ecx
    L_00426501:
        call asm_FUN_00425730_00425730
    L_00426506:
        ret
    }
}
