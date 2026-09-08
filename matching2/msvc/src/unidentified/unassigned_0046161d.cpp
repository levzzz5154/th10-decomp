#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046161D..0x00461633: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0046161d() {
    __asm {
    L_0046161d:
        xor eax,eax
    L_0046161f:
        inc eax
    L_00461620:
        ret
    L_00461621:
        mov esp,dword ptr [ebp-18h]
    L_00461624:
        call asm_resetstkoflw_00458d91
    L_00461629:
        xor edi,edi
    L_0046162b:
        xor esi,esi
    L_0046162d:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461631:
        xor ebx,ebx
    L_00461633:
        inc ebx
    }
}
