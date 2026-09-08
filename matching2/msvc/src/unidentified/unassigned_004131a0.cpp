#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004131A0..0x004131A9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004131a0() {
    __asm {
    L_004131a0:
        mov eax,dword ptr [eax+60h]
    L_004131a3:
        shr eax,3
    L_004131a6:
        and eax,1
    L_004131a9:
        ret
    }
}
