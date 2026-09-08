#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045DC7C..0x0045DCB9: __fassign
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_fassign_0045dc7c() {
    __asm {
    L_0045dc7c:
        push ebp
    L_0045dc7d:
        mov ebp,esp
    L_0045dc7f:
        push ecx
    L_0045dc80:
        push ecx
    L_0045dc81:
        cmp dword ptr [ebp+8],0
    L_0045dc85:
        push dword ptr [ebp+10h]
    L_0045dc88:
        je short L_0045dca5
    L_0045dc8a:
        lea eax,[ebp-8]
    L_0045dc8d:
        push eax
    L_0045dc8e:
        call asm_FUN_0045d676_0045d676
    L_0045dc93:
        mov eax,dword ptr [ebp+0Ch]
    L_0045dc96:
        pop ecx
    L_0045dc97:
        pop ecx
    L_0045dc98:
        mov ecx,dword ptr [ebp-8]
    L_0045dc9b:
        mov dword ptr [eax],ecx
    L_0045dc9d:
        mov ecx,dword ptr [ebp-4]
    L_0045dca0:
        mov dword ptr [eax+4],ecx
    L_0045dca3:
        leave
    L_0045dca4:
        ret
    L_0045dca5:
        lea eax,[ebp+8]
    L_0045dca8:
        push eax
    L_0045dca9:
        call asm_FUN_0045d701_0045d701
    L_0045dcae:
        mov eax,dword ptr [ebp+0Ch]
    L_0045dcb1:
        pop ecx
    L_0045dcb2:
        pop ecx
    L_0045dcb3:
        mov ecx,dword ptr [ebp+8]
    L_0045dcb6:
        mov dword ptr [eax],ecx
    L_0045dcb8:
        leave
    L_0045dcb9:
        ret
    }
}
