#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BEE0..0x0041BEE6: FUN_0041bee0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041bee0_0041bee0() {
    __asm {
    L_0041bee0:
        mov dword ptr [ecx+4],eax
    L_0041bee3:
        mov dword ptr [eax+8],ecx
    L_0041bee6:
        ret
    }
}
