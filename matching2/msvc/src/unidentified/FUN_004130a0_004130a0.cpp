#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004130A0..0x004130A6: FUN_004130a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004130a0_004130a0() {
    __asm {
    L_004130a0:
        mov dword ptr [eax+300h],ecx
    L_004130a6:
        ret
    }
}
