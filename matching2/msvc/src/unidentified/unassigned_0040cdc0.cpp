#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CDC0..0x0040CDD6: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040cdc0() {
    __asm {
    L_0040cdc0:
        mov cl,byte ptr [eax+3508h]
    L_0040cdc6:
        test cl,cl
    L_0040cdc8:
        jne short L_0040cdd4
    L_0040cdca:
        mov ecx,dword ptr [esp+4]
    L_0040cdce:
        mov dword ptr [eax+3504h],ecx
    L_0040cdd4:
        ret 4
    }
}
