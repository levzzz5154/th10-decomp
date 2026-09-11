#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004172E0..0x0041755F: FUN_004172e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004172e0_004172e0() {
    __asm {
    L_004172e0:
        sub esp,28h
    L_004172e3:
        cmp eax,6
    L_004172e6:
        push ebp
    L_004172e7:
        mov ebp,dword ptr [esp+30h]
    L_004172eb:
        ja asm_target_00417559
    L_004172f1:
        push edi
    L_004172f2:
        jmp dword ptr [eax*4+417560h]
    L_004172f9:
        mov eax,dword ptr [ebp+9E14h]
    L_004172ff:
        mov edx,dword ptr [data_00491c10]
    L_00417305:
        push ebx
    L_00417306:
        push esi
    L_00417307:
        push eax
    L_00417308:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041730d:
        xor esi,esi
    L_0041730f:
        push 0Fh
    L_00417311:
        mov dword ptr [ebp+9E14h],esi
    L_00417317:
        mov ecx,dword ptr [ebp+9EC8h]
    L_0041731d:
        push 47h
    L_0041731f:
        push ecx
    L_00417320:
        lea edi,[esp+2Ch]
    L_00417324:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00417329:
        mov edx,dword ptr [eax]
    L_0041732b:
        mov eax,dword ptr [esp+40h]
    L_0041732f:
        mov dword ptr [esp+10h],esi
    L_00417333:
        mov dword ptr [esp+40h],esi
    L_00417337:
        mov esi,dword ptr [data_00491c10]
    L_0041733d:
        mov dword ptr [ebp+9E14h],edx
    L_00417343:
        mov dword ptr [esp+14h],eax
    L_00417347:
        mov dword ptr [esp+3Ch],989680h
    L_0041734f:
        lea edi,[ebp+9DF4h]
    L_00417355:
        mov ecx,dword ptr [edi]
    L_00417357:
        push ecx
    L_00417358:
        mov edx,esi
    L_0041735a:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041735f:
        mov dword ptr [edi],0
    L_00417365:
        mov edx,dword ptr [ebp+9EC8h]
    L_0041736b:
        mov dword ptr [esp+18h],edx
    L_0041736f:
        call asm_FUN_00449950_00449950
    L_00417374:
        mov ecx,dword ptr [esp+18h]
    L_00417378:
        mov ebx,eax
    L_0041737a:
        mov eax,dword ptr [esp+40h]
    L_0041737e:
        mov esi,dword ptr [ebx+35Ch]
    L_00417384:
        add eax,27h
    L_00417387:
        push eax
    L_00417388:
        or esi,40000000h
    L_0041738e:
        push ebx
    L_0041738f:
        mov dword ptr [ebx+20h],0Fh
    L_00417396:
        mov dword ptr [ebx+35Ch],esi
    L_0041739c:
        call asm_FUN_00449870_00449870
    L_004173a1:
        mov esi,dword ptr [data_00491c10]
    L_004173a7:
        lea eax,[esp+1Ch]
    L_004173ab:
        mov edx,esi
    L_004173ad:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004173b2:
        mov eax,dword ptr [esp+14h]
    L_004173b6:
        cdq
    L_004173b7:
        idiv dword ptr [esp+3Ch]
    L_004173bb:
        mov ecx,dword ptr [esp+1Ch]
    L_004173bf:
        mov dword ptr [edi],ecx
    L_004173c1:
        mov ebx,eax
    L_004173c3:
        test ebx,ebx
    L_004173c5:
        mov dword ptr [esp+18h],edx
    L_004173c9:
        je short L_004173d3
    L_004173cb:
        mov dword ptr [esp+10h],1
    L_004173d3:
        push ecx
    L_004173d4:
        mov edx,esi
    L_004173d6:
        call asm_AnimationManager_Find_004491c0
    L_004173db:
        test eax,eax
    L_004173dd:
        je short L_004173ed
    L_004173df:
        mov ecx,dword ptr [eax+308h]
    L_004173e5:
        lea edx,[ebx+8]
    L_004173e8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004173ed:
        mov eax,dword ptr [esp+10h]
    L_004173f1:
        test eax,eax
    L_004173f3:
        mov eax,edi
    L_004173f5:
        jne short L_004173fe
    L_004173f7:
        call asm_AnimationManager_ClearFlag_004495e0
    L_004173fc:
        jmp short L_00417403
    L_004173fe:
        call asm_AnimationManager_SetFlagBit1_00449590
    L_00417403:
        mov ecx,dword ptr [esp+18h]
    L_00417407:
        mov eax,66666667h
    L_0041740c:
        imul dword ptr [esp+3Ch]
    L_00417410:
        sar edx,2
    L_00417413:
        mov eax,edx
    L_00417415:
        shr eax,1Fh
    L_00417418:
        add eax,edx
    L_0041741a:
        mov dword ptr [esp+3Ch],eax
    L_0041741e:
        mov eax,dword ptr [esp+40h]
    L_00417422:
        inc eax
    L_00417423:
        add edi,4
    L_00417426:
        cmp eax,8
    L_00417429:
        mov dword ptr [esp+14h],ecx
    L_0041742d:
        mov dword ptr [esp+40h],eax
    L_00417431:
        jl asm_target_00417355
    L_00417437:
        pop esi
    L_00417438:
        pop ebx
    L_00417439:
        pop edi
    L_0041743a:
        pop ebp
    L_0041743b:
        add esp,28h
    L_0041743e:
        ret 8
    L_00417441:
        mov ecx,dword ptr [ebp+9E14h]
    L_00417447:
        mov edx,dword ptr [data_00491c10]
    L_0041744d:
        push ecx
    L_0041744e:
        call asm_AnimationManager_SetFlag_004492a0
    L_00417453:
        push 0Fh
    L_00417455:
        push 48h
    L_00417457:
        lea edi,[esp+24h]
    L_0041745b:
        jmp asm_target_0041753a
    L_00417460:
        mov ecx,dword ptr [ebp+9E18h]
    L_00417466:
        mov edx,dword ptr [data_00491c10]
    L_0041746c:
        push ecx
    L_0041746d:
        call asm_AnimationManager_SetFlag_004492a0
    L_00417472:
        push 0Fh
    L_00417474:
        mov dword ptr [ebp+9E18h],0
    L_0041747e:
        mov edx,dword ptr [ebp+9EC8h]
    L_00417484:
        push 49h
    L_00417486:
        push edx
    L_00417487:
        lea edi,[esp+2Ch]
    L_0041748b:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00417490:
        mov eax,dword ptr [eax]
    L_00417492:
        pop edi
    L_00417493:
        mov dword ptr [ebp+9E18h],eax
    L_00417499:
        pop ebp
    L_0041749a:
        add esp,28h
    L_0041749d:
        ret 8
    L_004174a0:
        mov ecx,dword ptr [ebp+9E18h]
    L_004174a6:
        mov edx,dword ptr [data_00491c10]
    L_004174ac:
        push ecx
    L_004174ad:
        call asm_AnimationManager_SetFlag_004492a0
    L_004174b2:
        push 0Fh
    L_004174b4:
        mov dword ptr [ebp+9E18h],0
    L_004174be:
        mov edx,dword ptr [ebp+9EC8h]
    L_004174c4:
        push 4Ah
    L_004174c6:
        push edx
    L_004174c7:
        lea edi,[esp+30h]
    L_004174cb:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004174d0:
        mov eax,dword ptr [eax]
    L_004174d2:
        pop edi
    L_004174d3:
        mov dword ptr [ebp+9E18h],eax
    L_004174d9:
        pop ebp
    L_004174da:
        add esp,28h
    L_004174dd:
        ret 8
    L_004174e0:
        mov ecx,dword ptr [ebp+9E18h]
    L_004174e6:
        mov edx,dword ptr [data_00491c10]
    L_004174ec:
        push ecx
    L_004174ed:
        call asm_AnimationManager_SetFlag_004492a0
    L_004174f2:
        push 0Fh
    L_004174f4:
        mov dword ptr [ebp+9E18h],0
    L_004174fe:
        mov edx,dword ptr [ebp+9EC8h]
    L_00417504:
        push 4Bh
    L_00417506:
        push edx
    L_00417507:
        lea edi,[esp+34h]
    L_0041750b:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00417510:
        mov eax,dword ptr [eax]
    L_00417512:
        pop edi
    L_00417513:
        mov dword ptr [ebp+9E18h],eax
    L_00417519:
        pop ebp
    L_0041751a:
        add esp,28h
    L_0041751d:
        ret 8
    L_00417520:
        mov ecx,dword ptr [ebp+9E14h]
    L_00417526:
        mov edx,dword ptr [data_00491c10]
    L_0041752c:
        push ecx
    L_0041752d:
        call asm_AnimationManager_SetFlag_004492a0
    L_00417532:
        push 0Fh
    L_00417534:
        push 4Ch
    L_00417536:
        lea edi,[esp+34h]
    L_0041753a:
        mov dword ptr [ebp+9E14h],0
    L_00417544:
        mov edx,dword ptr [ebp+9EC8h]
    L_0041754a:
        push edx
    L_0041754b:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00417550:
        mov eax,dword ptr [eax]
    L_00417552:
        mov dword ptr [ebp+9E14h],eax
    L_00417558:
        pop edi
    L_00417559:
        pop ebp
    L_0041755a:
        add esp,28h
    L_0041755d:
        ret 8
        _emit 0xf9
        _emit 0x72
        _emit 0x41
        _emit 0x00
        _emit 0x41
        _emit 0x74
        _emit 0x41
        _emit 0x00
        _emit 0x60
        _emit 0x74
        _emit 0x41
        _emit 0x00
        _emit 0xa0
        _emit 0x74
        _emit 0x41
        _emit 0x00
        _emit 0xe0
        _emit 0x74
        _emit 0x41
        _emit 0x00
        _emit 0x58
        _emit 0x75
        _emit 0x41
        _emit 0x00
        _emit 0x20
        _emit 0x75
        _emit 0x41
        _emit 0x00
    }
}
