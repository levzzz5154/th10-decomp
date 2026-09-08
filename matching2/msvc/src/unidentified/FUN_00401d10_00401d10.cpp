#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401D10..0x00401D16: FUN_00401d10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401d10_00401d10() {
    __asm {
    L_00401d10:
        mov dword ptr [eax+394h],ecx
    L_00401d16:
        ret
    }
}
