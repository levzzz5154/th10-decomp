#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004458A0..0x004458A6: FUN_004458a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004458a0_004458a0() {
    __asm {
    L_004458a0:
        mov eax,dword ptr [eax+2FCh]
    L_004458a6:
        ret
    }
}
