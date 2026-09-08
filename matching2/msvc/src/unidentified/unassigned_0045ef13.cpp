#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EF13..0x0045EF2D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045ef13() {
    __asm {
    L_0045ef13:
        xor eax,eax
    L_0045ef15:
        inc eax
    L_0045ef16:
        ret
    L_0045ef17:
        mov esp,dword ptr [ebp-18h]
    L_0045ef1a:
        call asm_resetstkoflw_00458d91
    L_0045ef1f:
        xor ebx,ebx
    L_0045ef21:
        mov dword ptr [ebp-1Ch],ebx
    L_0045ef24:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045ef28:
        mov edi,dword ptr [ebp-2Ch]
    L_0045ef2b:
        mov esi,dword ptr [ebp-34h]
    }
}
