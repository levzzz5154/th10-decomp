#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004175B0..0x004175B9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004175b0() {
    __asm {
    L_004175b0:
        mov eax,dword ptr [eax+60h]
    L_004175b3:
        shr eax,2
    L_004175b6:
        and eax,1
    L_004175b9:
        ret
    }
}
