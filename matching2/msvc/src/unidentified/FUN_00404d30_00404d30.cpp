#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404D30..0x00404D3A: FUN_00404d30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404d30_00404d30() {
    __asm {
    L_00404d30:
        mov dword ptr [eax+84h],0
    L_00404d3a:
        ret
    }
}
