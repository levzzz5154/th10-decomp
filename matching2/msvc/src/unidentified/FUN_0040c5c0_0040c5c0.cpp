#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C5C0..0x0040C5C3: FUN_0040c5c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c5c0_0040c5c0() {
    __asm {
    L_0040c5c0:
        mov eax,dword ptr [eax+34h]
    L_0040c5c3:
        ret
    }
}
