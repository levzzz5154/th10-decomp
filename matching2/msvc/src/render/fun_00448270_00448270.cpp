#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421480..0x0042159E: Camera_ApplyRetail
// Naked body preserves the retail register/stack ABI.

// 0x00448270..0x0044835F: FUN_00448270
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448270_00448270() {
    __asm {
    L_00448270:
        sub esp,24h
    L_00448273:
        push ebp
    L_00448274:
        mov ebp,dword ptr [esp+40h]
    L_00448278:
        shl eax,4
    L_0044827b:
        push esi
    L_0044827c:
        mov esi,ecx
    L_0044827e:
        push edi
    L_0044827f:
        mov edi,eax
    L_00448281:
        mov eax,dword ptr [esi+ebx*4+3AD06Ch]
    L_00448288:
        mov ecx,dword ptr [eax+120h]
    L_0044828e:
        cmp dword ptr [edi+ecx],0
    L_00448292:
        je asm_target_00448357
    L_00448298:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0044829d:
        mov eax,dword ptr [data_00491c30]
    L_004482a2:
        mov edx,dword ptr [eax]
    L_004482a4:
        lea ecx,[esp+48h]
    L_004482a8:
        push ecx
    L_004482a9:
        push 0
    L_004482ab:
        push 0
    L_004482ad:
        push 0
    L_004482af:
        push eax
    L_004482b0:
        call dword ptr [edx+48h]
    L_004482b3:
        test eax,eax
    L_004482b5:
        jne asm_target_00448357
    L_004482bb:
        mov edx,dword ptr [esi+ebx*4+3AD06Ch]
    L_004482c2:
        mov eax,dword ptr [edx+120h]
    L_004482c8:
        mov edi,dword ptr [edi+eax]
    L_004482cb:
        mov ecx,dword ptr [edi]
    L_004482cd:
        lea edx,[esp+0Ch]
    L_004482d1:
        push edx
    L_004482d2:
        push 0
    L_004482d4:
        push edi
    L_004482d5:
        call dword ptr [ecx+48h]
    L_004482d8:
        test eax,eax
    L_004482da:
        jne short L_0044834d
    L_004482dc:
        mov ecx,dword ptr [esp+34h]
    L_004482e0:
        mov edx,dword ptr [esp+3Ch]
    L_004482e4:
        mov eax,dword ptr [esp+38h]
    L_004482e8:
        mov dword ptr [esp+10h],ecx
    L_004482ec:
        add ecx,edx
    L_004482ee:
        mov edx,dword ptr [esp+4Ch]
    L_004482f2:
        mov dword ptr [esp+14h],eax
    L_004482f6:
        mov dword ptr [esp+18h],ecx
    L_004482fa:
        mov ecx,dword ptr [esp+40h]
    L_004482fe:
        add eax,ecx
    L_00448300:
        push 0
    L_00448302:
        mov dword ptr [esp+20h],eax
    L_00448306:
        mov eax,dword ptr [esp+48h]
    L_0044830a:
        push 2
    L_0044830c:
        mov dword ptr [esp+28h],eax
    L_00448310:
        add eax,edx
    L_00448312:
        mov edx,dword ptr [esp+50h]
    L_00448316:
        lea ecx,[esp+18h]
    L_0044831a:
        push ecx
    L_0044831b:
        mov ecx,dword ptr [esp+18h]
    L_0044831f:
        mov dword ptr [esp+34h],eax
    L_00448323:
        mov eax,dword ptr [esp+5Ch]
    L_00448327:
        push 0
    L_00448329:
        mov dword ptr [esp+34h],ebp
    L_0044832d:
        add ebp,eax
    L_0044832f:
        push edx
    L_00448330:
        lea eax,[esp+34h]
    L_00448334:
        push eax
    L_00448335:
        push 0
    L_00448337:
        push ecx
    L_00448338:
        mov dword ptr [esp+4Ch],ebp
    L_0044833c:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_00448341:
        test eax,eax
    L_00448343:
        mov eax,dword ptr [esp+0Ch]
    L_00448347:
        mov edx,dword ptr [eax]
    L_00448349:
        push eax
    L_0044834a:
        call dword ptr [edx+8]
    L_0044834d:
        mov eax,dword ptr [esp+48h]
    L_00448351:
        mov ecx,dword ptr [eax]
    L_00448353:
        push eax
    L_00448354:
        call dword ptr [ecx+8]
    L_00448357:
        pop edi
    L_00448358:
        pop esi
    L_00448359:
        pop ebp
    L_0044835a:
        add esp,24h
    L_0044835d:
        ret 20h
    }
}
