#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420F20..0x00421064: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00420f20() {
    __asm {
    L_00420f20:
        push esi
    L_00420f21:
        mov esi,eax
    L_00420f23:
        add esi,62Ch
    L_00420f29:
        call asm_Platform_StopWorker_0044c150
    L_00420f2e:
        pop esi
    L_00420f2f:
        ret
    L_00420f30:
        push ecx
    L_00420f31:
        mov eax,dword ptr [edi+6FCh]
    L_00420f37:
        test eax,eax
    L_00420f39:
        jne asm_target_00421061
    L_00420f3f:
        push ebx
    L_00420f40:
        push ebp
    L_00420f41:
        mov ebp,dword ptr [edi+3C8h]
    L_00420f47:
        push esi
    L_00420f48:
        mov esi,dword ptr [data_00491c10]
    L_00420f4e:
        call asm_FUN_00449950_00449950
    L_00420f53:
        mov ebx,eax
    L_00420f55:
        mov eax,dword ptr [ebx+35Ch]
    L_00420f5b:
        push 0
    L_00420f5d:
        or eax,40000000h
    L_00420f62:
        push ebx
    L_00420f63:
        mov ecx,ebp
    L_00420f65:
        mov dword ptr [ebx+20h],0Fh
    L_00420f6c:
        mov dword ptr [ebx+35Ch],eax
    L_00420f72:
        call asm_FUN_00449870_00449870
    L_00420f77:
        mov esi,dword ptr [data_00491c10]
    L_00420f7d:
        lea eax,[esp+0Ch]
    L_00420f81:
        mov edx,esi
    L_00420f83:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00420f88:
        mov eax,dword ptr [esp+0Ch]
    L_00420f8c:
        mov dword ptr [data_00477824],eax
    L_00420f91:
        mov ebp,dword ptr [edi+3C8h]
    L_00420f97:
        call asm_FUN_00449950_00449950
    L_00420f9c:
        mov ebx,eax
    L_00420f9e:
        mov ecx,dword ptr [ebx+35Ch]
    L_00420fa4:
        or ecx,40000000h
    L_00420faa:
        push 1
    L_00420fac:
        mov dword ptr [ebx+35Ch],ecx
    L_00420fb2:
        push ebx
    L_00420fb3:
        mov ecx,ebp
    L_00420fb5:
        mov dword ptr [ebx+20h],0Fh
    L_00420fbc:
        call asm_FUN_00449870_00449870
    L_00420fc1:
        mov esi,dword ptr [data_00491c10]
    L_00420fc7:
        lea eax,[esp+0Ch]
    L_00420fcb:
        mov edx,esi
    L_00420fcd:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00420fd2:
        mov ecx,dword ptr [esp+0Ch]
    L_00420fd6:
        mov dword ptr [data_00477828],ecx
    L_00420fdc:
        mov ebp,dword ptr [edi+3C8h]
    L_00420fe2:
        call asm_FUN_00449950_00449950
    L_00420fe7:
        mov ebx,eax
    L_00420fe9:
        mov edx,dword ptr [ebx+35Ch]
    L_00420fef:
        push 2
    L_00420ff1:
        or edx,40000000h
    L_00420ff7:
        push ebx
    L_00420ff8:
        mov ecx,ebp
    L_00420ffa:
        mov dword ptr [ebx+20h],0Fh
    L_00421001:
        mov dword ptr [ebx+35Ch],edx
    L_00421007:
        call asm_FUN_00449870_00449870
    L_0042100c:
        mov ebp,dword ptr [data_00491c10]
    L_00421012:
        lea eax,[esp+0Ch]
    L_00421016:
        mov edx,ebp
    L_00421018:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042101d:
        mov edx,dword ptr [esp+0Ch]
    L_00421021:
        mov esi,dword ptr [esp+14h]
    L_00421025:
        mov dword ptr [data_0047782c],edx
    L_0042102b:
        mov dword ptr [edi+6FCh],1
    L_00421035:
        mov eax,dword ptr [data_00477824]
    L_0042103a:
        push eax
    L_0042103b:
        mov edx,ebp
    L_0042103d:
        call asm_AnimationManager_SetPosition_004492f0
    L_00421042:
        mov ecx,dword ptr [data_00477828]
    L_00421048:
        push ecx
    L_00421049:
        mov edx,ebp
    L_0042104b:
        call asm_AnimationManager_SetPosition_004492f0
    L_00421050:
        mov edx,dword ptr [data_0047782c]
    L_00421056:
        push edx
    L_00421057:
        mov edx,ebp
    L_00421059:
        call asm_AnimationManager_SetPosition_004492f0
    L_0042105e:
        pop esi
    L_0042105f:
        pop ebp
    L_00421060:
        pop ebx
    L_00421061:
        pop ecx
    L_00421062:
        ret 4
    }
}
