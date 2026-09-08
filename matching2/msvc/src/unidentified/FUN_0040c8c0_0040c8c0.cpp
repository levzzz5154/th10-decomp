#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C8C0..0x0040C8C2: FUN_0040c8c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c8c0_0040c8c0() {
    __asm {
    L_0040c8c0:
        mov dword ptr [eax],ecx
    L_0040c8c2:
        ret
    }
}
