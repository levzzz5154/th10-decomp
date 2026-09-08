#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454BF7..0x00454C07: __SEH_epilog
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SEH_epilog_00454bf7() {
    __asm {
    L_00454bf7:
        mov ecx,dword ptr [ebp-10h]
    L_00454bfa:
        mov dword ptr fs:[0],ecx
    L_00454c01:
        pop ecx
    L_00454c02:
        pop edi
    L_00454c03:
        pop esi
    L_00454c04:
        pop ebx
    L_00454c05:
        leave
    L_00454c06:
        push ecx
    L_00454c07:
        ret
    }
}
