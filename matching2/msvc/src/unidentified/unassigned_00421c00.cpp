#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421C00..0x00421C0A: unassigned code fragment
// Naked body preserves the retail register/stack ABI. The forward branch is a
// tail call into the store ladder at 0x00421C0B, which is a region of its own,
// so it carries a fixed displacement against that region's address.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00421c00() {
    __asm {
    L_00421c00:
        cmp dword ptr [eax],0
    L_00421c03:
        TH10_REL8(0x7c, 0x00421c03, VA_asm_unassigned_00421c0b)
    L_00421c05:
        or eax,0FFFFFFFFh
    L_00421c08:
        ret 20h
    }
}
