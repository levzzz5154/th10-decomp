#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461CA2..0x00461CBD: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00461ca2() {
    __asm {
    L_00461ca2:
        xor eax,eax
    L_00461ca4:
        inc eax
    L_00461ca5:
        ret
    L_00461ca6:
        mov esp,dword ptr [ebp-18h]
    L_00461ca9:
        call asm_resetstkoflw_00458d91
    L_00461cae:
        and dword ptr [ebp-38h],0
    L_00461cb2:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00461cb6:
        mov ebx,dword ptr [ebp-4Ch]
    L_00461cb9:
        xor edi,edi
    L_00461cbb:
        mov esi,dword ptr [ebp-3Ch]
    }
}
