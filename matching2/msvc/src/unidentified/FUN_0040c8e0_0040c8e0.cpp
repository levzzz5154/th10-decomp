#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C8E0..0x0040C8E3: FUN_0040c8e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c8e0_0040c8e0() {
    __asm {
    L_0040c8e0:
        mov dword ptr [eax+4],ecx
    L_0040c8e3:
        ret
    }
}
