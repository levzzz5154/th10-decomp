#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EFE1..0x0045EFFB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045efe1() {
    __asm {
    L_0045efe1:
        xor eax,eax
    L_0045efe3:
        inc eax
    L_0045efe4:
        ret
    L_0045efe5:
        mov esp,dword ptr [ebp-18h]
    L_0045efe8:
        call asm_resetstkoflw_00458d91
    L_0045efed:
        xor ebx,ebx
    L_0045efef:
        mov dword ptr [ebp-20h],ebx
    L_0045eff2:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045eff6:
        mov edi,dword ptr [ebp-2Ch]
    L_0045eff9:
        mov esi,dword ptr [ebp-34h]
    }
}
