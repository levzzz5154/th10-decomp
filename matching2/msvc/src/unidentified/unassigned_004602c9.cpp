#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004602C9..0x004602DF: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004602c9() {
    __asm {
    L_004602c9:
        xor eax,eax
    L_004602cb:
        inc eax
    L_004602cc:
        ret
    L_004602cd:
        mov esp,dword ptr [ebp-18h]
    L_004602d0:
        call asm_resetstkoflw_00458d91
    L_004602d5:
        xor edi,edi
    L_004602d7:
        xor ebx,ebx
    L_004602d9:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004602dd:
        mov esi,dword ptr [ebp-3Ch]
    }
}
