#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AD50..0x0040AD56: FUN_0040ad50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ad50_0040ad50() {
    __asm {
    L_0040ad50:
        mov dword ptr [eax+0D0h],ecx
    L_0040ad56:
        ret
    }
}
