#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AD10..0x0040AD15: FUN_0040ad10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ad10_0040ad10() {
    __asm {
    L_0040ad10:
        mov ecx,dword ptr [eax]
    L_0040ad12:
        mov dword ptr [eax+4],ecx
    L_0040ad15:
        ret
    }
}
