#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412DF0..0x00412DF3: FUN_00412df0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412df0_00412df0() {
    __asm {
    L_00412df0:
        mov eax,dword ptr [eax+34h]
    L_00412df3:
        ret
    }
}
