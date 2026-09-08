#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00429B30..0x00429B53: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00429b30() {
    __asm {
    L_00429b30:
        mov eax,dword ptr [edi+18h]
    L_00429b33:
        add eax,0Ch
    L_00429b36:
        push eax
    L_00429b37:
        call asm_FID_conflict___time32_00452b71
    L_00429b3c:
        add esp,4
    L_00429b3f:
        test esi,esi
    L_00429b41:
        lea eax,[esi+7]
    L_00429b44:
        jne short L_00429b4b
    L_00429b46:
        mov eax,dword ptr [data_00474c7c]
    L_00429b4b:
        mov ecx,dword ptr [edi+18h]
    L_00429b4e:
        mov dword ptr [ecx+5Ch],eax
    L_00429b51:
        xor eax,eax
    L_00429b53:
        ret
    }
}
