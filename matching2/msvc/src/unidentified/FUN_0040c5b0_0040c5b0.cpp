#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C5B0..0x0040C5B3: FUN_0040c5b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c5b0_0040c5b0() {
    __asm {
    L_0040c5b0:
        mov eax,dword ptr [eax+50h]
    L_0040c5b3:
        ret
    }
}
