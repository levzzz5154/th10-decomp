#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412EE0..0x00412EE3: FUN_00412ee0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412ee0_00412ee0() {
    __asm {
    L_00412ee0:
        mov eax,dword ptr [eax+58h]
    L_00412ee3:
        ret
    }
}
