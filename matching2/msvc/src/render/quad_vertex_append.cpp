#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442FE0..0x0044307C: AnimationManager_AppendQuadVertices
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_AppendQuadVertices_00442fe0() {
    __asm {
    L_00442fe0:
        push ebx
    L_00442fe1:
        push ebp
    L_00442fe2:
        push esi
    L_00442fe3:
        push edi
    L_00442fe4:
        mov edi,dword ptr [eax+72DACCh]
    L_00442fea:
        mov esi,edx
    L_00442fec:
        lea ebx,[edx+1Ch]
    L_00442fef:
        mov ecx,7
    L_00442ff4:
        rep movsd
    L_00442ff6:
        mov edi,dword ptr [eax+72DACCh]
    L_00442ffc:
        add edi,1Ch
    L_00442fff:
        mov esi,ebx
    L_00443001:
        lea ebp,[edx+38h]
    L_00443004:
        mov ecx,7
    L_00443009:
        rep movsd
    L_0044300b:
        mov edi,dword ptr [eax+72DACCh]
    L_00443011:
        add edi,38h
    L_00443014:
        mov esi,ebp
    L_00443016:
        mov ecx,7
    L_0044301b:
        rep movsd
    L_0044301d:
        mov edi,dword ptr [eax+72DACCh]
    L_00443023:
        add edi,54h
    L_00443026:
        mov esi,ebx
    L_00443028:
        mov ecx,7
    L_0044302d:
        rep movsd
    L_0044302f:
        mov edi,dword ptr [eax+72DACCh]
    L_00443035:
        add edi,70h
    L_00443038:
        mov esi,ebp
    L_0044303a:
        mov ecx,7
    L_0044303f:
        rep movsd
    L_00443041:
        mov edi,dword ptr [eax+72DACCh]
    L_00443047:
        lea esi,[edx+54h]
    L_0044304a:
        add edi,8Ch
    L_00443050:
        mov ecx,7
    L_00443055:
        rep movsd
    L_00443057:
        mov edx,dword ptr [eax+72DACCh]
    L_0044305d:
        mov ecx,dword ptr [eax+3ADAC8h]
    L_00443063:
        pop edi
    L_00443064:
        add edx,0A8h
    L_0044306a:
        pop esi
    L_0044306b:
        inc ecx
    L_0044306c:
        pop ebp
    L_0044306d:
        mov dword ptr [eax+72DACCh],edx
    L_00443073:
        mov dword ptr [eax+3ADAC8h],ecx
    L_00443079:
        xor eax,eax
    L_0044307b:
        pop ebx
    L_0044307c:
        ret
    }
}
