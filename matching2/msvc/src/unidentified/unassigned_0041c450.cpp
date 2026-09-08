#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041C450..0x0041C47A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041c450() {
    __asm {
    L_0041c450:
        mov ecx,dword ptr [eax+18h]
    L_0041c453:
        test ecx,ecx
    L_0041c455:
        je short L_0041c475
    L_0041c457:
        push esi
    L_0041c458:
        jmp short L_0041c460
    L_0041c45a:
        lea ebx,[ebx+force_disp32_zero]
    L_0041c460:
        cmp dword ptr [ecx+0Ch],1
    L_0041c464:
        mov esi,dword ptr [ecx+8]
    L_0041c467:
        je short L_0041c46e
    L_0041c469:
        mov edx,dword ptr [ecx]
    L_0041c46b:
        call dword ptr [edx+0Ch]
    L_0041c46e:
        test esi,esi
    L_0041c470:
        mov ecx,esi
    L_0041c472:
        jne short L_0041c460
    L_0041c474:
        pop esi
    L_0041c475:
        mov eax,1
    L_0041c47a:
        ret
    }
}
