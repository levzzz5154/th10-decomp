#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00412DA0..0x00412DA3: FUN_00412da0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00412da0_00412da0() {
    __asm {
    L_00412da0:
        mov dword ptr [eax+34h],ecx
    L_00412da3:
        ret
    }
}
