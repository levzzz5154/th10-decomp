#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00426CF0..0x00426D98: FUN_00426cf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426cf0_00426cf0() {
    __asm {
    L_00426cf0:
        sub esp,14h
    L_00426cf3:
        mov ecx,dword ptr [data_004776f0]
    L_00426cf9:
        push ebx
    L_00426cfa:
        push ebp
    L_00426cfb:
        mov ebp,dword ptr [esp+20h]
    L_00426cff:
        mov dword ptr [ebp+458h],4
    L_00426d09:
        fld dword ptr [ebp+3C0h]
    L_00426d0f:
        fadd dword ptr [data_00470b4c]
    L_00426d15:
        mov eax,dword ptr [ebp+3C8h]
    L_00426d1b:
        push esi
    L_00426d1c:
        mov esi,dword ptr [data_00491c10]
    L_00426d22:
        fstp dword ptr [esp+14h]
    L_00426d26:
        push edi
    L_00426d27:
        fld dword ptr [ebp+3C4h]
    L_00426d2d:
        mov edi,dword ptr [ecx+3E0B50h]
    L_00426d33:
        fadd dword ptr [data_00470b48]
    L_00426d39:
        mov dword ptr [esp+20h],eax
    L_00426d3d:
        fstp dword ptr [esp+1Ch]
    L_00426d41:
        call asm_FUN_00449950_00449950
    L_00426d46:
        mov ebx,eax
    L_00426d48:
        mov esi,dword ptr [ebx+35Ch]
    L_00426d4e:
        push 162h
    L_00426d53:
        or esi,40000000h
    L_00426d59:
        push ebx
    L_00426d5a:
        mov ecx,edi
    L_00426d5c:
        mov dword ptr [ebx+20h],0
    L_00426d63:
        mov dword ptr [ebx+35Ch],esi
    L_00426d69:
        call asm_FUN_00449870_00449870
    L_00426d6e:
        mov edi,dword ptr [data_00491c10]
    L_00426d74:
        lea eax,[esp+28h]
    L_00426d78:
        mov edx,edi
    L_00426d7a:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00426d7f:
        mov edx,dword ptr [esp+28h]
    L_00426d83:
        push edx
    L_00426d84:
        lea esi,[esp+1Ch]
    L_00426d88:
        mov edx,edi
    L_00426d8a:
        call asm_AnimationManager_SetPosition_004492f0
    L_00426d8f:
        mov dword ptr [esp+28h],20h
    L_00426d97:
        TH10_REL8(0xeb, 0x00426d97, VA_asm_FUN_00426cf0_part_00426da0)
    }
}

// 0x00426DA0..0x00426F62: FUN_00426cf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426cf0_part_00426da0() {
    __asm {
    L_00426da0:
        mov eax,dword ptr [data_004776f0]
    L_00426da5:
        mov ecx,dword ptr [eax+3E0B50h]
    L_00426dab:
        mov esi,edi
    L_00426dad:
        mov dword ptr [esp+10h],ecx
    L_00426db1:
        call asm_FUN_00449950_00449950
    L_00426db6:
        mov ecx,dword ptr [esp+10h]
    L_00426dba:
        mov ebx,eax
    L_00426dbc:
        mov edi,dword ptr [ebx+35Ch]
    L_00426dc2:
        push 163h
    L_00426dc7:
        or edi,40000000h
    L_00426dcd:
        push ebx
    L_00426dce:
        mov dword ptr [ebx+20h],0
    L_00426dd5:
        mov dword ptr [ebx+35Ch],edi
    L_00426ddb:
        call asm_FUN_00449870_00449870
    L_00426de0:
        mov edi,dword ptr [data_00491c10]
    L_00426de6:
        lea eax,[esp+14h]
    L_00426dea:
        mov edx,edi
    L_00426dec:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00426df1:
        mov edx,dword ptr [esp+14h]
    L_00426df5:
        push edx
    L_00426df6:
        lea esi,[esp+1Ch]
    L_00426dfa:
        mov edx,edi
    L_00426dfc:
        call asm_AnimationManager_SetPosition_004492f0
    L_00426e01:
        dec dword ptr [esp+28h]
    L_00426e05:
        jne short L_00426da0
    L_00426e07:
        mov eax,dword ptr [ebp+484h]
    L_00426e0d:
        xor esi,esi
    L_00426e0f:
        test al,1
    L_00426e11:
        mov ebx,476F78h
    L_00426e16:
        jne short L_00426e3d
    L_00426e18:
        or eax,1
    L_00426e1b:
        mov dword ptr [ebp+478h],esi
    L_00426e21:
        mov dword ptr [ebp+474h],0FFF0BDC1h
    L_00426e2b:
        mov dword ptr [ebp+47Ch],esi
    L_00426e31:
        mov dword ptr [ebp+480h],ebx
    L_00426e37:
        mov dword ptr [ebp+484h],eax
    L_00426e3d:
        mov eax,dword ptr [data_00477810]
    L_00426e42:
        cmp eax,esi
    L_00426e44:
        mov dword ptr [ebp+478h],esi
    L_00426e4a:
        mov dword ptr [ebp+47Ch],esi
    L_00426e50:
        mov dword ptr [ebp+474h],0FFFFFFFFh
    L_00426e5a:
        je short L_00426e76
    L_00426e5c:
        mov ecx,dword ptr [eax+58h]
    L_00426e5f:
        test ch,2
    L_00426e62:
        jne short L_00426e76
    L_00426e64:
        push esi
    L_00426e65:
        mov edi,4
    L_00426e6a:
        mov ecx,492590h
    L_00426e6f:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00426e74:
        xor esi,esi
    L_00426e76:
        mov eax,dword ptr [ebp+431Ch]
    L_00426e7c:
        test al,1
    L_00426e7e:
        jne short L_00426ea5
    L_00426e80:
        or eax,1
    L_00426e83:
        mov dword ptr [ebp+4310h],esi
    L_00426e89:
        mov dword ptr [ebp+430Ch],0FFF0BDC1h
    L_00426e93:
        mov dword ptr [ebp+4314h],esi
    L_00426e99:
        mov dword ptr [ebp+4318h],ebx
    L_00426e9f:
        mov dword ptr [ebp+431Ch],eax
    L_00426ea5:
        mov dword ptr [ebp+4310h],6
    L_00426eaf:
        mov dword ptr [ebp+4314h],40C00000h
    L_00426eb9:
        mov dword ptr [ebp+430Ch],5
    L_00426ec3:
        mov ecx,dword ptr [ebp+10h]
    L_00426ec6:
        lea eax,[ebp+14h]
    L_00426ec9:
        xor ebx,ebx
    L_00426ecb:
        call asm_AnimationObject_LoadScript_0043e710
    L_00426ed0:
        mov eax,dword ptr [data_004776f4]
    L_00426ed5:
        cmp dword ptr [eax+3738h],3Ch
    L_00426edc:
        jl short L_00426f59
    L_00426ede:
        mov edi,dword ptr [eax+378Ch]
    L_00426ee4:
        mov dword ptr [eax+3790h],esi
    L_00426eea:
        mov ecx,0FFFFFFFDh
    L_00426eef:
        and edi,ecx
    L_00426ef1:
        mov dword ptr [eax+378Ch],edi
    L_00426ef7:
        mov esi,dword ptr [eax+0AD4h]
    L_00426efd:
        mov edx,dword ptr [eax+0E80h]
    L_00426f03:
        mov ebp,dword ptr [eax+15D8h]
    L_00426f09:
        mov ebx,dword ptr [eax+1984h]
    L_00426f0f:
        mov edi,dword ptr [eax+1D30h]
    L_00426f15:
        and esi,ecx
    L_00426f17:
        and edx,ecx
    L_00426f19:
        mov dword ptr [eax+0AD4h],esi
    L_00426f1f:
        mov esi,dword ptr [eax+20DCh]
    L_00426f25:
        mov dword ptr [eax+0E80h],edx
    L_00426f2b:
        mov edx,dword ptr [eax+2488h]
    L_00426f31:
        and ebp,ecx
    L_00426f33:
        and ebx,ecx
    L_00426f35:
        and edi,ecx
    L_00426f37:
        and esi,ecx
    L_00426f39:
        and edx,ecx
    L_00426f3b:
        mov dword ptr [eax+15D8h],ebp
    L_00426f41:
        mov dword ptr [eax+1984h],ebx
    L_00426f47:
        mov dword ptr [eax+1D30h],edi
    L_00426f4d:
        mov dword ptr [eax+20DCh],esi
    L_00426f53:
        mov dword ptr [eax+2488h],edx
    L_00426f59:
        pop edi
    L_00426f5a:
        pop esi
    L_00426f5b:
        pop ebp
    L_00426f5c:
        pop ebx
    L_00426f5d:
        add esp,14h
    L_00426f60:
        ret 4
    }
}
