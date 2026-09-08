#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413740..0x00413751: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413740() {
    __asm {
    L_00413740:
        or dword ptr [eax+9EB4h],10h
    L_00413747:
        mov dword ptr [eax+9ECCh],0
    L_00413751:
        ret
    }
}
