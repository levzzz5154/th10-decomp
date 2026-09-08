#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409DE0..0x00409DE6: FUN_00409de0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409de0_00409de0() {
    __asm {
    L_00409de0:
        mov eax,dword ptr [eax+899Ch]
    L_00409de6:
        ret
    }
}
