#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409DC0..0x00409DC3: FUN_00409dc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409dc0_00409dc0() {
    __asm {
    L_00409dc0:
        mov eax,dword ptr [eax+44h]
    L_00409dc3:
        ret
    }
}
