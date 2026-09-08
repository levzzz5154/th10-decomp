#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441FD0..0x00441FD3: FUN_00441fd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441fd0_00441fd0() {
    __asm {
    L_00441fd0:
        mov dword ptr [eax+24h],ecx
    L_00441fd3:
        ret
    }
}
