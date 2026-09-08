#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004130D0..0x004130D3: FUN_004130d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004130d0_004130d0() {
    __asm {
    L_004130d0:
        mov dword ptr [eax+10h],ecx
    L_004130d3:
        ret
    }
}
