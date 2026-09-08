#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AD90..0x0040AD92: FUN_0040ad90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040ad90_0040ad90() {
    __asm {
    L_0040ad90:
        mov eax,dword ptr [eax]
    L_0040ad92:
        ret
    }
}
