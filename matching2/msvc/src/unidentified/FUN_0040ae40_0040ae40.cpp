#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE40..0x0040AE43: FUN_0040ae40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ae40_0040ae40() {
    __asm {
    L_0040ae40:
        mov eax,dword ptr [eax+4]
    L_0040ae43:
        ret
    }
}
