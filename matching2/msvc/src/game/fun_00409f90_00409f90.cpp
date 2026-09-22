#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// BLOCKED (D3301): closest_byte_count=1/118; first_diff=0x00409F91;
// residual_class=schema2 private-EAX manager receiver, virtual-release ABI,
// and register/stack local scheduling; variants_tested=live-Ghidra decompile
// plus callers (0x0040D530, 0x00417C80, 0x00418190) and callee
// (0x004493E0), MSVC 13.10 readable candidate (114-byte extent, 1 matching
// byte), and native-LTCG synthetic accessor context at 0x00409F90 (0/37
// matching bytes); next_lever=compile a real 0x0040D530/0x00417C80 caller
// cluster that preserves the hidden manager EAX receiver.

// 0x00409F90..0x0040A005: FUN_00409f90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409f90_00409f90() {
    __asm {
    L_00409f90:
        push ebx
    L_00409f91:
        mov ebx,dword ptr [data_00491c10]
    L_00409f97:
        push ebp
    L_00409f98:
        mov ebp,dword ptr [esp+0Ch]
    L_00409f9c:
        push esi
    L_00409f9d:
        push edi
    L_00409f9e:
        lea esi,[ebx+3AD090h]
    L_00409fa4:
        mov edi,4
    L_00409fa9:
        lea esp,[esp+force_disp32_zero]
    L_00409fb0:
        mov edx,dword ptr [esi]
    L_00409fb2:
        mov eax,ebx
    L_00409fb4:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_00409fb9:
        add esi,4
    L_00409fbc:
        dec edi
    L_00409fbd:
        jne short L_00409fb0
    L_00409fbf:
        mov eax,dword ptr [ebp+58h]
    L_00409fc2:
        xor edi,edi
    L_00409fc4:
        cmp eax,edi
    L_00409fc6:
        je short L_00409fe0
    L_00409fc8:
        mov esi,dword ptr [eax+4]
    L_00409fcb:
        mov eax,dword ptr [eax]
    L_00409fcd:
        cmp eax,edi
    L_00409fcf:
        je short L_00409fda
    L_00409fd1:
        mov edx,dword ptr [eax]
    L_00409fd3:
        push 1
    L_00409fd5:
        mov ecx,eax
    L_00409fd7:
        call dword ptr [edx+14h]
    L_00409fda:
        cmp esi,edi
    L_00409fdc:
        mov eax,esi
    L_00409fde:
        jne short L_00409fc8
    L_00409fe0:
        mov eax,dword ptr [ebp+8]
    L_00409fe3:
        cmp eax,edi
    L_00409fe5:
        mov dword ptr [ebp+64h],edi
    L_00409fe8:
        mov dword ptr [ebp+10h],edi
    L_00409feb:
        mov ecx,0FFFFFFFDh
    L_00409ff0:
        je short L_00409ff5
    L_00409ff2:
        and dword ptr [eax+4],ecx
    L_00409ff5:
        mov eax,dword ptr [ebp+0Ch]
    L_00409ff8:
        cmp eax,edi
    L_00409ffa:
        pop edi
    L_00409ffb:
        pop esi
    L_00409ffc:
        pop ebp
    L_00409ffd:
        pop ebx
    L_00409ffe:
        je short L_0040a003
    L_0040a000:
        and dword ptr [eax+4],ecx
    L_0040a003:
        ret 4
    }
}
