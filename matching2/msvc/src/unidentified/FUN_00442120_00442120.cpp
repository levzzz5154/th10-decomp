#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442120..0x00442123: FUN_00442120
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442120_00442120() {
    __asm {
    L_00442120:
        mov dword ptr [eax+44h],ecx
    L_00442123:
        ret
    }
}
