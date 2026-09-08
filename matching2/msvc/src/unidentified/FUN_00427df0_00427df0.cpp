#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427DF0..0x00427DF3: FUN_00427df0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427df0_00427df0() {
    __asm {
    L_00427df0:
        mov eax,dword ptr [eax+2Ch]
    L_00427df3:
        ret
    }
}
