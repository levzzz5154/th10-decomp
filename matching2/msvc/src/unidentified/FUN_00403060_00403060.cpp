#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403060..0x00403066: FUN_00403060
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403060_00403060() {
    __asm {
    L_00403060:
        push ecx
    L_00403061:
        call asm_FUN_00402850_00402850
    L_00403066:
        ret
    }
}
