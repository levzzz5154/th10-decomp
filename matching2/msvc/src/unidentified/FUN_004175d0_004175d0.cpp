#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004175D0..0x004175D3: FUN_004175d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004175d0_004175d0() {
    __asm {
    L_004175d0:
        mov dword ptr [eax+54h],ecx
    L_004175d3:
        ret
    }
}
