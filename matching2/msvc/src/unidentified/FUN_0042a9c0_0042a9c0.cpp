#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A9C0..0x0042A9C7: FUN_0042a9c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a9c0_0042a9c0() {
    __asm {
    L_0042a9c0:
        mov dword ptr [eax+4],0
    L_0042a9c7:
        ret
    }
}
