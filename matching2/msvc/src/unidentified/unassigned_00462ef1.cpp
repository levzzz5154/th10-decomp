#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462EF1..0x00462F09: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00462ef1() {
    __asm {
    L_00462ef1:
        mov eax,dword ptr [ebp-14h]
    L_00462ef4:
        call asm_unassigned_00462e60
    L_00462ef9:
        ret
    L_00462efa:
        mov esp,dword ptr [ebp-18h]
    L_00462efd:
        and dword ptr [ebp-4],0
    L_00462f01:
        mov edi,dword ptr [ebp+10h]
    L_00462f04:
        mov ebx,dword ptr [ebp+8]
    L_00462f07:
        mov esi,dword ptr [ebp-20h]
    }
}
