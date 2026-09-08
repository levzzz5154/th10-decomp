#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401C90..0x00401C95: FUN_00401c90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401c90_00401c90() {
    __asm {
    L_00401c90:
        mov eax,89ACh
    L_00401c95:
        ret
    }
}
