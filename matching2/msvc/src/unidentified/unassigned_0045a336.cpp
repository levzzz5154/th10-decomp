#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A336..0x0045A34A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045a336() {
    __asm {
    L_0045a336:
        xor eax,eax
    L_0045a338:
        inc eax
    L_0045a339:
        ret
    L_0045a33a:
        mov esp,dword ptr [ebp-18h]
    L_0045a33d:
        call asm_resetstkoflw_00458d91
    L_0045a342:
        xor esi,esi
    L_0045a344:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045a348:
        mov edi,dword ptr [ebp-28h]
    }
}
