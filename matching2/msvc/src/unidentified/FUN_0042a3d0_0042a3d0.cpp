#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A3D0..0x0042A3D9: FUN_0042a3d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a3d0_0042a3d0() {
    __asm {
    L_0042a3d0:
        push edi
    L_0042a3d1:
        mov edi,ecx
    L_0042a3d3:
        call asm_FUN_004297d0_004297d0
    L_0042a3d8:
        pop edi
    L_0042a3d9:
        ret
    }
}
