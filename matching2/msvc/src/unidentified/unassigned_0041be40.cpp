#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041BE40..0x0041BE6D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041be40() {
    __asm {
    L_0041be40:
        mov ecx,dword ptr [data_004776f0]
    L_0041be46:
        push esi
    L_0041be47:
        mov esi,eax
    L_0041be49:
        mov eax,dword ptr [esi+3E0h]
    L_0041be4f:
        mov dword ptr [esi+3DCh],2
    L_0041be59:
        mov edx,dword ptr [ecx+3E0B50h]
    L_0041be5f:
        add eax,176h
    L_0041be64:
        push edx
    L_0041be65:
        call asm_FUN_00404f30_00404f30
    L_0041be6a:
        xor eax,eax
    L_0041be6c:
        pop esi
    L_0041be6d:
        ret
    }
}
