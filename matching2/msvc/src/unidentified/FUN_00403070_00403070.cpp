#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00403070..0x00403076: FUN_00403070
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00403070_00403070() {
    __asm {
    L_00403070:
        push ecx
    L_00403071:
        call asm_FUN_00402ca0_00402ca0
    L_00403076:
        ret
    }
}
