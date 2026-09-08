#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C8B0..0x0040C8B2: FUN_0040c8b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c8b0_0040c8b0() {
    __asm {
    L_0040c8b0:
        mov eax,dword ptr [eax]
    L_0040c8b2:
        ret
    }
}
