#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BFA0..0x0043C194: FUN_0043bfa0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043bfa0_0043bfa0() {
    __asm {
    L_0043bfa0:
        sub esp,5Ch
    L_0043bfa3:
        push esi
    L_0043bfa4:
        mov esi,dword ptr [data_00491c10]
    L_0043bfaa:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0043bfaf:
        mov eax,dword ptr [edi]
    L_0043bfb1:
        mov ecx,dword ptr [edi+4]
    L_0043bfb4:
        mov edx,eax
    L_0043bfb6:
        mov dword ptr [esp+4],eax
    L_0043bfba:
        mov eax,ecx
    L_0043bfbc:
        mov dword ptr [esp+8],ecx
    L_0043bfc0:
        mov dword ptr [esp+10h],edx
    L_0043bfc4:
        mov edx,dword ptr [edi+8]
    L_0043bfc7:
        mov dword ptr [esp+4],edx
    L_0043bfcb:
        mov dword ptr [esp+14h],eax
    L_0043bfcf:
        mov dword ptr [esp+8],eax
    L_0043bfd3:
        mov dword ptr [esp+0Ch],0
    L_0043bfdb:
        mov ecx,dword ptr [esp+0Ch]
    L_0043bfdf:
        mov dword ptr [esp+18h],ecx
    L_0043bfe3:
        mov ecx,edx
    L_0043bfe5:
        mov edx,eax
    L_0043bfe7:
        mov dword ptr [esp+24h],ecx
    L_0043bfeb:
        mov ecx,dword ptr [edi]
    L_0043bfed:
        mov dword ptr [esp+28h],edx
    L_0043bff1:
        mov edx,dword ptr [edi+0Ch]
    L_0043bff4:
        mov dword ptr [esp+0Ch],0
    L_0043bffc:
        mov eax,dword ptr [esp+0Ch]
    L_0043c000:
        mov dword ptr [esp+2Ch],eax
    L_0043c004:
        mov eax,ecx
    L_0043c006:
        mov dword ptr [esp+4],ecx
    L_0043c00a:
        mov ecx,edx
    L_0043c00c:
        mov dword ptr [esp+8],edx
    L_0043c010:
        mov dword ptr [esp+38h],eax
    L_0043c014:
        mov eax,dword ptr [edi+8]
    L_0043c017:
        mov dword ptr [esp+0Ch],0
    L_0043c01f:
        mov edx,dword ptr [esp+0Ch]
    L_0043c023:
        mov dword ptr [esp+40h],edx
    L_0043c027:
        mov edx,eax
    L_0043c029:
        mov dword ptr [esp+4],eax
    L_0043c02d:
        mov eax,ecx
    L_0043c02f:
        mov dword ptr [esp+3Ch],ecx
    L_0043c033:
        mov dword ptr [esp+8],ecx
    L_0043c037:
        mov dword ptr [esp+4Ch],edx
    L_0043c03b:
        mov edx,dword ptr [esp+64h]
    L_0043c03f:
        mov dword ptr [esp+50h],eax
    L_0043c043:
        mov eax,dword ptr [esp+68h]
    L_0043c047:
        push 2
    L_0043c049:
        mov dword ptr [esp+10h],0
    L_0043c051:
        mov ecx,dword ptr [esp+10h]
    L_0043c055:
        mov dword ptr [esp+58h],ecx
    L_0043c059:
        mov ecx,dword ptr [esp+70h]
    L_0043c05d:
        mov dword ptr [esp+24h],edx
    L_0043c061:
        mov edx,dword ptr [esp+74h]
    L_0043c065:
        push 4
    L_0043c067:
        mov dword ptr [esp+3Ch],eax
    L_0043c06b:
        mov eax,dword ptr [data_00491c30]
    L_0043c070:
        xor esi,esi
    L_0043c072:
        push esi
    L_0043c073:
        mov dword ptr [esp+64h],3F800000h
    L_0043c07b:
        mov dword ptr [esp+50h],3F800000h
    L_0043c083:
        mov dword ptr [esp+3Ch],3F800000h
    L_0043c08b:
        mov dword ptr [esp+28h],3F800000h
    L_0043c093:
        mov dword ptr [esp+54h],ecx
    L_0043c097:
        mov dword ptr [esp+68h],edx
    L_0043c09b:
        mov ecx,dword ptr [eax]
    L_0043c09d:
        push eax
    L_0043c09e:
        call dword ptr [ecx+10Ch]
    L_0043c0a4:
        mov eax,dword ptr [data_00491c30]
    L_0043c0a9:
        mov edx,dword ptr [eax]
    L_0043c0ab:
        push 2
    L_0043c0ad:
        push 1
    L_0043c0af:
        push esi
    L_0043c0b0:
        push eax
    L_0043c0b1:
        call dword ptr [edx+10Ch]
    L_0043c0b7:
        mov eax,dword ptr [data_00491c30]
    L_0043c0bc:
        mov ecx,dword ptr [eax]
    L_0043c0be:
        push esi
    L_0043c0bf:
        push 5
    L_0043c0c1:
        push esi
    L_0043c0c2:
        push eax
    L_0043c0c3:
        call dword ptr [ecx+10Ch]
    L_0043c0c9:
        mov eax,dword ptr [data_00491c30]
    L_0043c0ce:
        mov edx,dword ptr [eax]
    L_0043c0d0:
        push esi
    L_0043c0d1:
        push 2
    L_0043c0d3:
        push esi
    L_0043c0d4:
        push eax
    L_0043c0d5:
        call dword ptr [edx+10Ch]
    L_0043c0db:
        mov eax,dword ptr [data_00491c30]
    L_0043c0e0:
        mov ecx,dword ptr [eax]
    L_0043c0e2:
        push 6
    L_0043c0e4:
        push 14h
    L_0043c0e6:
        push eax
    L_0043c0e7:
        call dword ptr [ecx+0E4h]
    L_0043c0ed:
        mov eax,dword ptr [data_00491c30]
    L_0043c0f2:
        mov edx,dword ptr [eax]
    L_0043c0f4:
        push 44h
    L_0043c0f6:
        push eax
    L_0043c0f7:
        call dword ptr [edx+164h]
    L_0043c0fd:
        mov eax,dword ptr [data_00491c30]
    L_0043c102:
        mov ecx,dword ptr [eax]
    L_0043c104:
        push 14h
    L_0043c106:
        lea edx,[esp+14h]
    L_0043c10a:
        push edx
    L_0043c10b:
        push 2
    L_0043c10d:
        push 5
    L_0043c10f:
        push eax
    L_0043c110:
        call dword ptr [ecx+14Ch]
    L_0043c116:
        mov eax,dword ptr [data_00491c10]
    L_0043c11b:
        push 4
    L_0043c11d:
        mov cl,0FFh
    L_0043c11f:
        push 4
    L_0043c121:
        mov byte ptr [eax+3ADA6Ah],cl
    L_0043c127:
        mov dword ptr [eax+3ADA70h],esi
    L_0043c12d:
        mov dword ptr [eax+3ADA64h],esi
    L_0043c133:
        mov byte ptr [eax+3ADA69h],cl
    L_0043c139:
        mov byte ptr [eax+3ADA68h],3
    L_0043c140:
        mov byte ptr [eax+3ADA6Bh],cl
    L_0043c146:
        mov eax,dword ptr [data_00491c30]
    L_0043c14b:
        mov ecx,dword ptr [eax]
    L_0043c14d:
        push esi
    L_0043c14e:
        push eax
    L_0043c14f:
        call dword ptr [ecx+10Ch]
    L_0043c155:
        mov eax,dword ptr [data_00491c30]
    L_0043c15a:
        mov edx,dword ptr [eax]
    L_0043c15c:
        push 4
    L_0043c15e:
        push 1
    L_0043c160:
        push esi
    L_0043c161:
        push eax
    L_0043c162:
        call dword ptr [edx+10Ch]
    L_0043c168:
        mov eax,dword ptr [data_00491c30]
    L_0043c16d:
        mov ecx,dword ptr [eax]
    L_0043c16f:
        push 2
    L_0043c171:
        push 5
    L_0043c173:
        push esi
    L_0043c174:
        push eax
    L_0043c175:
        call dword ptr [ecx+10Ch]
    L_0043c17b:
        mov eax,dword ptr [data_00491c30]
    L_0043c180:
        mov edx,dword ptr [eax]
    L_0043c182:
        push 2
    L_0043c184:
        push 2
    L_0043c186:
        push esi
    L_0043c187:
        push eax
    L_0043c188:
        call dword ptr [edx+10Ch]
    L_0043c18e:
        pop esi
    L_0043c18f:
        add esp,5Ch
    L_0043c192:
        ret 10h
    }
}
