#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040AF90..0x0040AFE5: ?BulletManager_Create@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletManager_Create_0040af90() {
    __asm {
    L_0040af90:
        push ebx
    L_0040af91:
        push 18h
    L_0040af93:
        call asm_operator_new_00452493
    L_0040af98:
        add esp,4
    L_0040af9b:
        test eax,eax
    L_0040af9d:
        je short L_0040afc0
    L_0040af9f:
        xor ecx,ecx
    L_0040afa1:
        mov edx,eax
    L_0040afa3:
        mov dword ptr [edx],ecx
    L_0040afa5:
        mov dword ptr [edx+4],ecx
    L_0040afa8:
        mov dword ptr [edx+8],ecx
    L_0040afab:
        mov dword ptr [edx+0Ch],ecx
    L_0040afae:
        mov dword ptr [edx+10h],ecx
    L_0040afb1:
        mov dword ptr [edx+14h],ecx
    L_0040afb4:
        or dword ptr [eax],2
    L_0040afb7:
        mov dword ptr [data_004776fc],eax
    L_0040afbc:
        mov ebx,eax
    L_0040afbe:
        jmp short L_0040afc2
    L_0040afc0:
        xor ebx,ebx
    L_0040afc2:
        call asm_BulletManager_LoadScripts_0040ae70
    L_0040afc7:
        test eax,eax
    L_0040afc9:
        je short L_0040afe2
    L_0040afcb:
        test ebx,ebx
    L_0040afcd:
        je short L_0040afde
    L_0040afcf:
        push ebx
    L_0040afd0:
        call asm_BulletManager_Release_0040af00
    L_0040afd5:
        push ebx
    L_0040afd6:
        call asm_free_004524a1
    L_0040afdb:
        add esp,4
    L_0040afde:
        xor eax,eax
    L_0040afe0:
        pop ebx
    L_0040afe1:
        ret
    L_0040afe2:
        mov eax,ebx
    L_0040afe4:
        pop ebx
    L_0040afe5:
        ret
    }
}
