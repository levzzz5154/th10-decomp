#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404410..0x0040441A: FUN_00404410
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404410_00404410() {
    __asm {
    L_00404410:
        mov dword ptr [eax+1EE4h],1
    L_0040441a:
        ret
    }
}
