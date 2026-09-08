#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461744..0x0046175A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00461744() {
    __asm {
    L_00461744:
        xor eax,eax
    L_00461746:
        inc eax
    L_00461747:
        ret
    L_00461748:
        mov esp,dword ptr [ebp-18h]
    L_0046174b:
        call asm_resetstkoflw_00458d91
    L_00461750:
        xor esi,esi
    L_00461752:
        xor edi,edi
    L_00461754:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461758:
        mov ebx,dword ptr [ebp-24h]
    }
}
