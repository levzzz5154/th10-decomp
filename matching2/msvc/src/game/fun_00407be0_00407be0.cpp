#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00407560..0x00407690: FUN_00407560
// Naked body preserves the retail register/stack ABI.

// 0x00407BE0..0x00407D9D: FUN_00407be0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00407be0_00407be0() {
    __asm {
    L_00407be0:
        fld dword ptr [esi+3B4h]
    L_00407be6:
        fcomp dword ptr [data_00470b40]
    L_00407bec:
        fnstsw ax
    L_00407bee:
        test ah,41h
    L_00407bf1:
        jnp short L_00407c30
    L_00407bf3:
        fld dword ptr [esi+3B4h]
    L_00407bf9:
        fcomp dword ptr [data_00470b3c]
    L_00407bff:
        fnstsw ax
    L_00407c01:
        test ah,1
    L_00407c04:
        je short L_00407c30
    L_00407c06:
        fld dword ptr [esi+3B8h]
    L_00407c0c:
        fcomp dword ptr [data_00470b04]
    L_00407c12:
        fnstsw ax
    L_00407c14:
        test ah,41h
    L_00407c17:
        jnp short L_00407c30
    L_00407c19:
        fld dword ptr [esi+3B8h]
    L_00407c1f:
        fcomp dword ptr [data_00470b38]
    L_00407c25:
        fnstsw ax
    L_00407c27:
        test ah,1
    L_00407c2a:
        jne asm_target_00407d9d
    L_00407c30:
        push ebx
    L_00407c31:
        push edi
    L_00407c32:
        mov edi,dword ptr [esi+458h]
    L_00407c38:
        xor ebx,ebx
    L_00407c3a:
        test edi,edi
    L_00407c3c:
        jl short L_00407c49
    L_00407c3e:
        push ebx
    L_00407c3f:
        mov ecx,492590h
    L_00407c44:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00407c49:
        fld dword ptr [esi+3B4h]
    L_00407c4f:
        fcomp dword ptr [data_00470b40]
    L_00407c55:
        fnstsw ax
    L_00407c57:
        test ah,5
    L_00407c5a:
        jnp short L_00407c6f
    L_00407c5c:
        fld dword ptr [esi+3B4h]
    L_00407c62:
        fcomp dword ptr [data_00470b3c]
    L_00407c68:
        fnstsw ax
    L_00407c6a:
        test ah,1
    L_00407c6d:
        jne short L_00407cc0
    L_00407c6f:
        fld dword ptr [esi+3E4h]
    L_00407c75:
        push 0
    L_00407c77:
        fchs
    L_00407c79:
        push ecx
    L_00407c7a:
        fsub dword ptr [data_00470b18]
    L_00407c80:
        fstp dword ptr [esp]
    L_00407c83:
        call asm_Angle_NormalizeSum_0044bc10
    L_00407c88:
        fstp dword ptr [esi+3E4h]
    L_00407c8e:
        mov ebx,1
    L_00407c93:
        fld dword ptr [esi+3B4h]
    L_00407c99:
        fcomp dword ptr [data_00470b40]
    L_00407c9f:
        fnstsw ax
    L_00407ca1:
        test ah,5
    L_00407ca4:
        jp short L_00407cae
    L_00407ca6:
        fld dword ptr [data_00470b58]
    L_00407cac:
        jmp short L_00407cb4
    L_00407cae:
        fld dword ptr [data_00470b54]
    L_00407cb4:
        fsub dword ptr [esi+3B4h]
    L_00407cba:
        fstp dword ptr [esi+3B4h]
    L_00407cc0:
        mov ecx,dword ptr [esi+43Ch]
    L_00407cc6:
        test ecx,8000000h
    L_00407ccc:
        jne short L_00407d41
    L_00407cce:
        fld dword ptr [esi+3B8h]
    L_00407cd4:
        fcomp dword ptr [data_00470b04]
    L_00407cda:
        fnstsw ax
    L_00407cdc:
        test ah,5
    L_00407cdf:
        jnp short L_00407cf9
    L_00407ce1:
        fld dword ptr [esi+3B8h]
    L_00407ce7:
        fcomp dword ptr [data_00470b38]
    L_00407ced:
        fnstsw ax
    L_00407cef:
        test ah,1
    L_00407cf2:
        jne short L_00407d41
    L_00407cf4:
        test ch,4
    L_00407cf7:
        je short L_00407d41
    L_00407cf9:
        fld dword ptr [esi+3E4h]
    L_00407cff:
        mov ebx,1
    L_00407d04:
        fchs
    L_00407d06:
        fstp dword ptr [esi+3E4h]
    L_00407d0c:
        fld dword ptr [esi+3B8h]
    L_00407d12:
        fcomp dword ptr [data_00470b04]
    L_00407d18:
        fnstsw ax
    L_00407d1a:
        test ah,5
    L_00407d1d:
        jp short L_00407d29
    L_00407d1f:
        fld dword ptr [esi+3B8h]
    L_00407d25:
        fchs
    L_00407d27:
        jmp short L_00407d3b
    L_00407d29:
        fld dword ptr [data_00470b38]
    L_00407d2f:
        fsub dword ptr [esi+3B8h]
    L_00407d35:
        fadd dword ptr [data_00470b38]
    L_00407d3b:
        fstp dword ptr [esi+3B8h]
    L_00407d41:
        fld dword ptr [esi+6F8h]
    L_00407d47:
        fcomp dword ptr [data_00470b50]
    L_00407d4d:
        fnstsw ax
    L_00407d4f:
        test ah,41h
    L_00407d52:
        jne short L_00407d60
    L_00407d54:
        mov eax,dword ptr [esi+6F8h]
    L_00407d5a:
        mov dword ptr [esi+3D8h],eax
    L_00407d60:
        mov ecx,dword ptr [esi+3D8h]
    L_00407d66:
        mov edx,dword ptr [esi+3E4h]
    L_00407d6c:
        push ecx
    L_00407d6d:
        push edx
    L_00407d6e:
        lea ecx,[esi+3C0h]
    L_00407d74:
        call asm_Score_SetPolarVector_00408750
    L_00407d79:
        pop edi
    L_00407d7a:
        test ebx,ebx
    L_00407d7c:
        pop ebx
    L_00407d7d:
        je short L_00407d85
    L_00407d7f:
        inc dword ptr [esi+70Ch]
    L_00407d85:
        mov eax,dword ptr [esi+70Ch]
    L_00407d8b:
        cmp eax,dword ptr [esi+710h]
    L_00407d91:
        jl short L_00407d9d
    L_00407d93:
        and dword ptr [esi+43Ch],0F7FFF3FFh
    L_00407d9d:
        ret
    }
}
