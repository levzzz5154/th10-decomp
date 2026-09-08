#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C950..0x0040C953: FUN_0040c950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c950_0040c950() {
    __asm {
    L_0040c950:
        mov dword ptr [eax+edx*4],ecx
    L_0040c953:
        ret
    }
}
