#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004053A0..0x004053A6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004053a0() {
    __asm {
    L_004053a0:
        mov eax,dword ptr [eax+60h]
    L_004053a3:
        and eax,1
    L_004053a6:
        ret
    }
}
