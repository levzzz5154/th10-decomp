#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424530..0x0042453C: unassigned code fragment
// Naked body preserves the retail register/stack ABI. The forward branch is a
// tail call into the store ladder at 0x0042453D, which is a region of its own,
// so it carries a fixed displacement against that region's address.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00424530() {
    __asm {
    L_00424530:
        mov ecx,dword ptr [eax+4]
    L_00424533:
        test ecx,ecx
    L_00424535:
        TH10_REL8(0x7c, 0x00424535, VA_asm_unassigned_0042453d)
    L_00424537:
        or eax,0FFFFFFFFh
    L_0042453a:
        ret 24h
    }
}
