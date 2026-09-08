#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C8D0..0x0040C8D3: FUN_0040c8d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c8d0_0040c8d0() {
    __asm {
    L_0040c8d0:
        mov eax,dword ptr [eax+4]
    L_0040c8d3:
        ret
    }
}
