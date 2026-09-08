#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C990..0x0040C992: FUN_0040c990
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c990_0040c990() {
    __asm {
    L_0040c990:
        mov eax,dword ptr [eax]
    L_0040c992:
        ret
    }
}
