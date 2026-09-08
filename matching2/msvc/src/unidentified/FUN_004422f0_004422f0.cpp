#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004422F0..0x004422FE: FUN_004422f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004422f0_004422f0() {
    __asm {
    L_004422f0:
        mov byte ptr [eax],cl
    L_004422f2:
        mov cl,byte ptr [esp+4]
    L_004422f6:
        mov byte ptr [eax+1],dl
    L_004422f9:
        mov byte ptr [eax+2],cl
    L_004422fc:
        ret 4
    }
}
