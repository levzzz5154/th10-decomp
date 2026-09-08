#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A9B0..0x0042A9B5: FUN_0042a9b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a9b0_0042a9b0() {
    __asm {
    L_0042a9b0:
        mov eax,dword ptr [data_00491fc4]
    L_0042a9b5:
        ret
    }
}
