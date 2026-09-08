#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404C90..0x00404C96: FUN_00404c90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404c90_00404c90() {
    __asm {
    L_00404c90:
        mov dword ptr [eax+84h],ecx
    L_00404c96:
        ret
    }
}
