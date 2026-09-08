#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF50..0x0044DF56: FUN_0044df50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044df50_0044df50() {
    __asm {
    L_0044df50:
        mov dword ptr [eax+1000h],ecx
    L_0044df56:
        ret
    }
}
