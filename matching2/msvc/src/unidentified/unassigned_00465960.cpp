#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00465960..0x00465993: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00465960() {
    __asm {
    L_00465960:
        push edi
    L_00465961:
        and dword ptr [data_00492588],0FFFFFFFEh
    L_00465968:
        xor eax,eax
    L_0046596a:
        mov ecx,11h
    L_0046596f:
        mov edi,492548h
    L_00465974:
        rep stosd
    L_00465976:
        mov edx,dword ptr [data_00492548]
    L_0046597c:
        or edx,2
    L_0046597f:
        push 465A50h
    L_00465984:
        mov dword ptr [data_00492548],edx
    L_0046598a:
        call asm_atexit_00452e0a
    L_0046598f:
        add esp,4
    L_00465992:
        pop edi
    L_00465993:
        ret
    }
}
