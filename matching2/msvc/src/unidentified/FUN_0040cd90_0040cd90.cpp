#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CD90..0x0040CD94: FUN_0040cd90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cd90_0040cd90() {
    __asm {
    L_0040cd90:
        mov dword ptr [eax+edx*4+10h],ecx
    L_0040cd94:
        ret
    }
}
