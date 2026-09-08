#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CD80..0x0040CD84: FUN_0040cd80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cd80_0040cd80() {
    __asm {
    L_0040cd80:
        mov dword ptr [ecx+edx*4+30h],eax
    L_0040cd84:
        ret
    }
}
