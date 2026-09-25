#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422150..0x004221DD: MainMenu_RegisterTasksRetail
// Naked body preserves the retail register/stack ABI.

// 0x00422AB0..0x00422C2D: FUN_00422ab0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00422ab0_00422ab0() {
    __asm {
    L_00422ab0:
        push ebx
    L_00422ab1:
        push ebp
    L_00422ab2:
        mov ebp,dword ptr [esp+0Ch]
    L_00422ab6:
        mov dword ptr [ebp+4],1
    L_00422abd:
        mov eax,dword ptr [ebp+20h]
    L_00422ac0:
        push esi
    L_00422ac1:
        xor ecx,ecx
    L_00422ac3:
        test al,1
    L_00422ac5:
        push edi
    L_00422ac6:
        jne short L_00422ae2
    L_00422ac8:
        or eax,1
    L_00422acb:
        mov dword ptr [ebp+14h],ecx
    L_00422ace:
        mov dword ptr [ebp+10h],0FFF0BDC1h
    L_00422ad5:
        mov dword ptr [ebp+18h],ecx
    L_00422ad8:
        mov dword ptr [ebp+1Ch],476F78h
    L_00422adf:
        mov dword ptr [ebp+20h],eax
    L_00422ae2:
        mov eax,dword ptr [data_00477810]
    L_00422ae7:
        mov dword ptr [ebp+14h],ecx
    L_00422aea:
        mov dword ptr [ebp+18h],ecx
    L_00422aed:
        mov dword ptr [ebp+10h],0FFFFFFFFh
    L_00422af4:
        or dword ptr [eax+58h],10h
    L_00422af8:
        mov eax,dword ptr [data_004776e0]
    L_00422afd:
        mov esi,dword ptr [data_00491c10]
    L_00422b03:
        mov edi,dword ptr [eax+8998h]
    L_00422b09:
        call asm_FUN_00449950_00449950
    L_00422b0e:
        mov ebx,eax
    L_00422b10:
        mov edx,dword ptr [ebx+35Ch]
    L_00422b16:
        push 0
    L_00422b18:
        or edx,40000000h
    L_00422b1e:
        push ebx
    L_00422b1f:
        mov ecx,edi
    L_00422b21:
        mov dword ptr [ebx+20h],0Fh
    L_00422b28:
        mov dword ptr [ebx+35Ch],edx
    L_00422b2e:
        call asm_FUN_00449870_00449870
    L_00422b33:
        mov esi,dword ptr [data_00491c10]
    L_00422b39:
        lea eax,[esp+14h]
    L_00422b3d:
        mov edx,esi
    L_00422b3f:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00422b44:
        mov eax,dword ptr [esp+14h]
    L_00422b48:
        push 1C0h
    L_00422b4d:
        push 180h
    L_00422b52:
        push 10h
    L_00422b54:
        push 20h
    L_00422b56:
        push eax
    L_00422b57:
        mov dword ptr [ebp+1D8h],eax
    L_00422b5d:
        call asm_FUN_00424480_00424480
    L_00422b62:
        mov ecx,dword ptr [data_0047770c]
    L_00422b68:
        mov edi,dword ptr [ecx+9EC8h]
    L_00422b6e:
        mov dword ptr [ebp+2C4h],edi
    L_00422b74:
        call asm_FUN_00449950_00449950
    L_00422b79:
        mov ebx,eax
    L_00422b7b:
        mov edx,dword ptr [ebx+35Ch]
    L_00422b81:
        push 79h
    L_00422b83:
        or edx,40000000h
    L_00422b89:
        push ebx
    L_00422b8a:
        mov ecx,edi
    L_00422b8c:
        mov dword ptr [ebx+20h],0Fh
    L_00422b93:
        mov dword ptr [ebx+35Ch],edx
    L_00422b99:
        call asm_FUN_00449870_00449870
    L_00422b9e:
        mov edx,dword ptr [data_00491c10]
    L_00422ba4:
        lea eax,[esp+14h]
    L_00422ba8:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00422bad:
        mov edx,dword ptr [esp+14h]
    L_00422bb1:
        lea esi,[ebp+1D4h]
    L_00422bb7:
        mov eax,esi
    L_00422bb9:
        mov dword ptr [esi],edx
    L_00422bbb:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00422bc0:
        push 0
    L_00422bc2:
        mov edi,20h
    L_00422bc7:
        mov ecx,492590h
    L_00422bcc:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00422bd1:
        push 0
    L_00422bd3:
        push 6
    L_00422bd5:
        mov edx,46E0C0h
    L_00422bda:
        mov eax,ecx
    L_00422bdc:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00422be1:
        mov eax,dword ptr [data_00477810]
    L_00422be6:
        mov ecx,dword ptr [eax+5Ch]
    L_00422be9:
        test ecx,ecx
    L_00422beb:
        je short L_00422c11
    L_00422bed:
        mov ebx,75h
    L_00422bf2:
        lea edi,[esp+14h]
    L_00422bf6:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00422bfb:
        mov edx,dword ptr [data_00491c10]
    L_00422c01:
        mov esi,eax
    L_00422c03:
        mov ecx,dword ptr [esi]
    L_00422c05:
        push ecx
    L_00422c06:
        call asm_AnimationManager_SetFlag_004492a0
    L_00422c0b:
        mov dword ptr [esi],0
    L_00422c11:
        mov edx,dword ptr [data_00476f78]
    L_00422c17:
        pop edi
    L_00422c18:
        pop esi
    L_00422c19:
        mov dword ptr [ebp+2C0h],edx
    L_00422c1f:
        pop ebp
    L_00422c20:
        mov dword ptr [data_00476f78],3F800000h
    L_00422c2a:
        pop ebx
    L_00422c2b:
        ret 4
    }
}
