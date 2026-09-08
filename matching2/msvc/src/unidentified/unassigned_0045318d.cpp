#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045318D..0x004531BE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045318d() {
    __asm {
    L_0045318d:
        xor eax,eax
    L_0045318f:
        inc eax
    L_00453190:
        ret
    L_00453191:
        mov esp,dword ptr [ebp-18h]
    L_00453194:
        call asm_resetstkoflw_00458d91
    L_00453199:
        mov esi,dword ptr [ebp-134h]
    L_0045319f:
        lea eax,[esi+1]
    L_004531a2:
        push eax
    L_004531a3:
        call asm_malloc_00452706
    L_004531a8:
        pop ecx
    L_004531a9:
        mov edi,eax
    L_004531ab:
        xor ebx,ebx
    L_004531ad:
        cmp edi,ebx
    L_004531af:
        jne short L_004531b5
    L_004531b1:
        xor esi,esi
    L_004531b3:
        TH10_REL8(0xeb, 0x004531b3, VA_asm_FUN_00453111_part_004531bf)
    L_004531b5:
        mov dword ptr [ebp-130h],1
    }
}
