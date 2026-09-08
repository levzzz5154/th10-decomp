#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041AB60..0x0041AB63: FUN_0041ab60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ab60_0041ab60() {
    __asm {
    L_0041ab60:
        mov eax,dword ptr [eax+24h]
    L_0041ab63:
        ret
    }
}
