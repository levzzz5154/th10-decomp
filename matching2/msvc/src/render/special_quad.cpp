#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BDA0..0x0043BF82: FUN_0043bda0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043bda0_0043bda0() {
    __asm {
    L_0043bda0:
        sub esp,5Ch
    L_0043bda3:
        push esi
    L_0043bda4:
        mov esi,dword ptr [data_00491c10]
    L_0043bdaa:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0043bdaf:
        mov eax,dword ptr [edi]
    L_0043bdb1:
        mov ecx,dword ptr [edi+4]
    L_0043bdb4:
        mov edx,eax
    L_0043bdb6:
        mov dword ptr [esp+4],eax
    L_0043bdba:
        mov eax,ecx
    L_0043bdbc:
        mov dword ptr [esp+8],ecx
    L_0043bdc0:
        mov dword ptr [esp+10h],edx
    L_0043bdc4:
        mov edx,dword ptr [edi+8]
    L_0043bdc7:
        mov dword ptr [esp+4],edx
    L_0043bdcb:
        mov dword ptr [esp+0Ch],0
    L_0043bdd3:
        mov ecx,dword ptr [esp+0Ch]
    L_0043bdd7:
        mov dword ptr [esp+18h],ecx
    L_0043bddb:
        mov ecx,edx
    L_0043bddd:
        mov edx,eax
    L_0043bddf:
        mov dword ptr [esp+14h],eax
    L_0043bde3:
        mov dword ptr [esp+8],eax
    L_0043bde7:
        mov dword ptr [esp+24h],ecx
    L_0043bdeb:
        mov ecx,dword ptr [edi]
    L_0043bded:
        mov dword ptr [esp+28h],edx
    L_0043bdf1:
        mov edx,dword ptr [edi+0Ch]
    L_0043bdf4:
        mov dword ptr [esp+0Ch],0
    L_0043bdfc:
        mov eax,dword ptr [esp+0Ch]
    L_0043be00:
        mov dword ptr [esp+2Ch],eax
    L_0043be04:
        mov eax,ecx
    L_0043be06:
        mov dword ptr [esp+4],ecx
    L_0043be0a:
        mov ecx,edx
    L_0043be0c:
        mov dword ptr [esp+8],edx
    L_0043be10:
        mov dword ptr [esp+38h],eax
    L_0043be14:
        mov eax,dword ptr [edi+8]
    L_0043be17:
        mov dword ptr [esp+0Ch],0
    L_0043be1f:
        mov edx,dword ptr [esp+0Ch]
    L_0043be23:
        mov dword ptr [esp+40h],edx
    L_0043be27:
        mov edx,eax
    L_0043be29:
        push 2
    L_0043be2b:
        mov dword ptr [esp+8],eax
    L_0043be2f:
        mov eax,ecx
    L_0043be31:
        mov dword ptr [esp+40h],ecx
    L_0043be35:
        push 4
    L_0043be37:
        mov dword ptr [esp+10h],ecx
    L_0043be3b:
        mov dword ptr [esp+58h],eax
    L_0043be3f:
        mov eax,dword ptr [data_00491c30]
    L_0043be44:
        mov dword ptr [esp+14h],0
    L_0043be4c:
        mov ecx,dword ptr [esp+14h]
    L_0043be50:
        xor esi,esi
    L_0043be52:
        push esi
    L_0043be53:
        mov dword ptr [esp+58h],edx
    L_0043be57:
        mov dword ptr [esp+60h],ecx
    L_0043be5b:
        mov dword ptr [esp+64h],3F800000h
    L_0043be63:
        mov dword ptr [esp+50h],3F800000h
    L_0043be6b:
        mov dword ptr [esp+3Ch],3F800000h
    L_0043be73:
        mov dword ptr [esp+28h],3F800000h
    L_0043be7b:
        mov dword ptr [esp+68h],ebx
    L_0043be7f:
        mov dword ptr [esp+54h],ebx
    L_0043be83:
        mov dword ptr [esp+40h],ebx
    L_0043be87:
        mov dword ptr [esp+2Ch],ebx
    L_0043be8b:
        mov edx,dword ptr [eax]
    L_0043be8d:
        push eax
    L_0043be8e:
        call dword ptr [edx+10Ch]
    L_0043be94:
        mov eax,dword ptr [data_00491c30]
    L_0043be99:
        mov ecx,dword ptr [eax]
    L_0043be9b:
        push 2
    L_0043be9d:
        push 1
    L_0043be9f:
        push esi
    L_0043bea0:
        push eax
    L_0043bea1:
        call dword ptr [ecx+10Ch]
    L_0043bea7:
        mov eax,dword ptr [data_00491c30]
    L_0043beac:
        mov edx,dword ptr [eax]
    L_0043beae:
        push esi
    L_0043beaf:
        push 5
    L_0043beb1:
        push esi
    L_0043beb2:
        push eax
    L_0043beb3:
        call dword ptr [edx+10Ch]
    L_0043beb9:
        mov eax,dword ptr [data_00491c30]
    L_0043bebe:
        mov ecx,dword ptr [eax]
    L_0043bec0:
        push esi
    L_0043bec1:
        push 2
    L_0043bec3:
        push esi
    L_0043bec4:
        push eax
    L_0043bec5:
        call dword ptr [ecx+10Ch]
    L_0043becb:
        mov eax,dword ptr [data_00491c30]
    L_0043bed0:
        mov edx,dword ptr [eax]
    L_0043bed2:
        push 6
    L_0043bed4:
        push 14h
    L_0043bed6:
        push eax
    L_0043bed7:
        call dword ptr [edx+0E4h]
    L_0043bedd:
        mov eax,dword ptr [data_00491c30]
    L_0043bee2:
        mov ecx,dword ptr [eax]
    L_0043bee4:
        push 44h
    L_0043bee6:
        push eax
    L_0043bee7:
        call dword ptr [ecx+164h]
    L_0043beed:
        mov eax,dword ptr [data_00491c30]
    L_0043bef2:
        mov edx,dword ptr [eax]
    L_0043bef4:
        push 14h
    L_0043bef6:
        lea ecx,[esp+14h]
    L_0043befa:
        push ecx
    L_0043befb:
        push 2
    L_0043befd:
        push 5
    L_0043beff:
        push eax
    L_0043bf00:
        call dword ptr [edx+14Ch]
    L_0043bf06:
        mov eax,dword ptr [data_00491c10]
    L_0043bf0b:
        push 4
    L_0043bf0d:
        mov cl,0FFh
    L_0043bf0f:
        push 4
    L_0043bf11:
        mov byte ptr [eax+3ADA6Ah],cl
    L_0043bf17:
        mov dword ptr [eax+3ADA70h],esi
    L_0043bf1d:
        mov dword ptr [eax+3ADA64h],esi
    L_0043bf23:
        mov byte ptr [eax+3ADA69h],cl
    L_0043bf29:
        mov byte ptr [eax+3ADA68h],3
    L_0043bf30:
        mov byte ptr [eax+3ADA6Bh],cl
    L_0043bf36:
        mov eax,dword ptr [data_00491c30]
    L_0043bf3b:
        mov edx,dword ptr [eax]
    L_0043bf3d:
        push esi
    L_0043bf3e:
        push eax
    L_0043bf3f:
        call dword ptr [edx+10Ch]
    L_0043bf45:
        mov eax,dword ptr [data_00491c30]
    L_0043bf4a:
        mov ecx,dword ptr [eax]
    L_0043bf4c:
        push 4
    L_0043bf4e:
        push 1
    L_0043bf50:
        push esi
    L_0043bf51:
        push eax
    L_0043bf52:
        call dword ptr [ecx+10Ch]
    L_0043bf58:
        mov eax,dword ptr [data_00491c30]
    L_0043bf5d:
        mov edx,dword ptr [eax]
    L_0043bf5f:
        push 2
    L_0043bf61:
        push 5
    L_0043bf63:
        push esi
    L_0043bf64:
        push eax
    L_0043bf65:
        call dword ptr [edx+10Ch]
    L_0043bf6b:
        mov eax,dword ptr [data_00491c30]
    L_0043bf70:
        mov ecx,dword ptr [eax]
    L_0043bf72:
        push 2
    L_0043bf74:
        push 2
    L_0043bf76:
        push esi
    L_0043bf77:
        push eax
    L_0043bf78:
        call dword ptr [ecx+10Ch]
    L_0043bf7e:
        pop esi
    L_0043bf7f:
        add esp,5Ch
    L_0043bf82:
        ret
    }
}

