#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450580..0x004505AA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00450580() {
    __asm {
    L_00450580:
        push eax
    L_00450581:
        mov eax,dword ptr [esp+8]
    L_00450585:
        call asm_FUN_00450470_00450470
    L_0045058a:
        mov ecx,dword ptr [esi+4]
    L_0045058d:
        mov dword ptr [ecx+4],eax
    L_00450590:
        mov edx,dword ptr [esi+4]
    L_00450593:
        mov dword ptr [edx],0
    L_00450599:
        mov eax,dword ptr [esi+4]
    L_0045059c:
        mov edx,dword ptr [eax+4]
    L_0045059f:
        xor ecx,ecx
    L_004505a1:
        test edx,edx
    L_004505a3:
        sete cl
    L_004505a6:
        mov eax,ecx
    L_004505a8:
        ret 4
    }
}
