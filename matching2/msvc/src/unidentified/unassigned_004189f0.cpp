#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004189F0..0x004189F6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004189f0() {
    __asm {
    L_004189f0:
        inc dword ptr [eax+48h]
    L_004189f3:
        inc dword ptr [eax+4Ch]
    L_004189f6:
        ret
    }
}
