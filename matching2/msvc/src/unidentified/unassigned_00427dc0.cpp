#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00427DC0..0x00427DED: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00427dc0() {
    __asm {
    L_00427dc0:
        mov ecx,dword ptr [edx+4]
    L_00427dc3:
        mov edx,dword ptr [edx]
    L_00427dc5:
        add ecx,dword ptr [esi+4]
    L_00427dc8:
        add edx,dword ptr [esi]
    L_00427dca:
        mov dword ptr [eax],edx
    L_00427dcc:
        mov dword ptr [eax+4],ecx
    L_00427dcf:
        ret
    L_00427dd0:
        mov eax,dword ptr [esi]
    L_00427dd2:
        mov edx,dword ptr [data_00491c10]
    L_00427dd8:
        push eax
    L_00427dd9:
        call asm_AnimationManager_Find_004491c0
    L_00427dde:
        test eax,eax
    L_00427de0:
        jne short L_00427de4
    L_00427de2:
        mov dword ptr [esi],eax
    L_00427de4:
        xor ecx,ecx
    L_00427de6:
        test eax,eax
    L_00427de8:
        setne cl
    L_00427deb:
        mov eax,ecx
    L_00427ded:
        ret
    }
}
