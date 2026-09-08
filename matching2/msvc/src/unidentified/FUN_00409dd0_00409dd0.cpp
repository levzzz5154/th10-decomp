#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409DD0..0x00409DD3: FUN_00409dd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409dd0_00409dd0() {
    __asm {
    L_00409dd0:
        mov eax,dword ptr [eax+0Ch]
    L_00409dd3:
        ret
    }
}
