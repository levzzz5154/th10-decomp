#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004136A0..0x004136A6: FUN_004136a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004136a0_004136a0() {
    __asm {
    L_004136a0:
        mov eax,dword ptr [eax+390h]
    L_004136a6:
        ret
    }
}
