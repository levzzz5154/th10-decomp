#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004367E0..0x004367EA: FUN_004367e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004367e0_004367e0() {
    __asm {
    L_004367e0:
        mov dword ptr [eax+4],0
    L_004367e7:
        mov dword ptr [eax+8],ecx
    L_004367ea:
        ret
    }
}
