#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417680..0x00417683: FUN_00417680
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417680_00417680() {
    __asm {
    L_00417680:
        mov eax,dword ptr [eax+5Ch]
    L_00417683:
        ret
    }
}
