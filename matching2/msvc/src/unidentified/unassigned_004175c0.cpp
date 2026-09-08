#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004175C0..0x004175C4: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004175c0() {
    __asm {
    L_004175c0:
        or dword ptr [eax+60h],4
    L_004175c4:
        ret
    }
}
