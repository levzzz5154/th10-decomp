#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045AB66..0x0045AB7C: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045ab66() {
    __asm {
    L_0045ab66:
        xor eax,eax
    L_0045ab68:
        inc eax
    L_0045ab69:
        ret
    L_0045ab6a:
        mov esp,dword ptr [ebp-18h]
    L_0045ab6d:
        call asm_resetstkoflw_00458d91
    L_0045ab72:
        xor edi,edi
    L_0045ab74:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045ab78:
        mov ebx,dword ptr [ebp+10h]
    L_0045ab7b:
        xor esi,esi
    }
}
