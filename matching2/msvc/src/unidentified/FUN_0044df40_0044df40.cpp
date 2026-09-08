#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF40..0x0044DF46: FUN_0044df40
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044df40_0044df40() {
    __asm {
    L_0044df40:
        mov eax,dword ptr [eax+1000h]
    L_0044df46:
        ret
    }
}
