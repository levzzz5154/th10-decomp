#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004501E0..0x004501E6: FUN_004501e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004501e0_004501e0() {
    __asm {
    L_004501e0:
        mov dword ptr [eax+102Ch],ecx
    L_004501e6:
        ret
    }
}
