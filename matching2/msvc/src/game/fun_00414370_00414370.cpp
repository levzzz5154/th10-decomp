// BLOCKED (D3402): closest_byte_count=12/476; first_diff=0x00414370
// residual_class=abi/cluster; a native manager-teardown cluster candidate
// emitted 484 bytes and differed in 464 bytes of the 476-byte live extent.
// Retail carries the transition object through EBP/stack homes, selects the
// manager in ESI/EDX, and shares private AnimationManager/vector callees.
// variants_tested=archived manager-teardown semantic body plus four-source
// native MSVC 13.10 LTCG bridge; measured candidate extent 484, 464 diffs.
// next_lever=derive the shared AnimationManager SetFlag/MarkResource and
// vector-destructor ABIs, then rebuild the complete manager caller cluster.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x00414370..0x0041451C: FUN_00414370
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414370_00414370() {
    __asm {
    L_00414370:
        mov al,byte ptr [data_00474ca0]
    L_00414375:
        push ebx
    L_00414376:
        push ebp
    L_00414377:
        mov ebp,dword ptr [esp+0Ch]
    L_0041437b:
        push esi
    L_0041437c:
        xor ebx,ebx
    L_0041437e:
        test al,9
    L_00414380:
        push edi
    L_00414381:
        jne short L_004143ad
    L_00414383:
        mov esi,dword ptr [data_00491c10]
    L_00414389:
        mov edi,dword ptr [esi+3AD0DCh]
    L_0041438f:
        add esi,3AD0DCh
    L_00414395:
        cmp edi,ebx
    L_00414397:
        je short L_004143bd
    L_00414399:
        call asm_FUN_00447810_00447810
    L_0041439e:
        mov eax,dword ptr [esi]
    L_004143a0:
        push eax
    L_004143a1:
        call asm_free_004524a1
    L_004143a6:
        add esp,4
    L_004143a9:
        mov dword ptr [esi],ebx
    L_004143ab:
        jmp short L_004143bd
    L_004143ad:
        mov edx,dword ptr [ebp+9E80h]
    L_004143b3:
        mov eax,dword ptr [data_00491c10]
    L_004143b8:
        call asm_AnimationManager_MarkResourceForRemoval_004493e0
    L_004143bd:
        mov esi,dword ptr [ebp+9EB8h]
    L_004143c3:
        cmp esi,ebx
    L_004143c5:
        mov dword ptr [ebp+9E80h],ebx
    L_004143cb:
        je short L_004143e1
    L_004143cd:
        call asm_AnimationSlot_ReleaseRetail_004136c0
    L_004143d2:
        push esi
    L_004143d3:
        call asm_free_004524a1
    L_004143d8:
        add esp,4
    L_004143db:
        mov dword ptr [ebp+9EB8h],ebx
    L_004143e1:
        test byte ptr [data_00474ca0],9
    L_004143e8:
        jne short L_00414411
    L_004143ea:
        mov eax,dword ptr [ebp+9EBCh]
    L_004143f0:
        cmp eax,ebx
    L_004143f2:
        je short L_00414403
    L_004143f4:
        push eax
    L_004143f5:
        call asm_free_00452422
    L_004143fa:
        add esp,4
    L_004143fd:
        mov dword ptr [ebp+9EBCh],ebx
    L_00414403:
        mov dword ptr [ebp+9EBCh],ebx
    L_00414409:
        mov dword ptr [data_00491be8],ebx
    L_0041440f:
        jmp short L_0041441d
    L_00414411:
        mov ecx,dword ptr [ebp+9EBCh]
    L_00414417:
        mov dword ptr [data_00491be8],ecx
    L_0041441d:
        mov eax,dword ptr [ebp+8]
    L_00414420:
        cmp eax,ebx
    L_00414422:
        je short L_00414428
    L_00414424:
        and dword ptr [eax+4],0FFFFFFFDh
    L_00414428:
        mov edx,dword ptr [ebp+9E14h]
    L_0041442e:
        push edx
    L_0041442f:
        mov edx,dword ptr [data_00491c10]
    L_00414435:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041443a:
        mov esi,dword ptr [data_00491c10]
    L_00414440:
        mov dword ptr [ebp+9E14h],ebx
    L_00414446:
        mov eax,dword ptr [ebp+9E18h]
    L_0041444c:
        push eax
    L_0041444d:
        mov edx,esi
    L_0041444f:
        call asm_AnimationManager_SetFlag_004492a0
    L_00414454:
        mov dword ptr [ebp+9E18h],ebx
    L_0041445a:
        mov ecx,dword ptr [ebp+9E24h]
    L_00414460:
        push ecx
    L_00414461:
        mov edx,esi
    L_00414463:
        call asm_AnimationManager_SetFlag_004492a0
    L_00414468:
        xor edx,edx
    L_0041446a:
        mov dword ptr [ebp+9E24h],ebx
    L_00414470:
        mov dword ptr [ebp+9E28h],edx
    L_00414476:
        mov dword ptr [ebp+9E2Ch],edx
    L_0041447c:
        mov dword ptr [ebp+9E30h],edx
    L_00414482:
        mov dword ptr [ebp+9E34h],edx
    L_00414488:
        mov dword ptr [ebp+9E38h],edx
    L_0041448e:
        mov dword ptr [ebp+9E3Ch],edx
    L_00414494:
        mov dword ptr [ebp+9E40h],edx
    L_0041449a:
        mov dword ptr [ebp+9E44h],edx
    L_004144a0:
        mov dword ptr [ebp+9E48h],edx
    L_004144a6:
        mov dword ptr [ebp+9E4Ch],edx
    L_004144ac:
        lea edx,[ebp+9DF4h]
    L_004144b2:
        mov dword ptr [esp+14h],8
    L_004144ba:
        lea ebx,[ebx+force_disp32_zero]
    L_004144c0:
        mov ecx,dword ptr [edx]
    L_004144c2:
        cmp ecx,ebx
    L_004144c4:
        TH10_REL8(0x74, 0x004144c4, VA_asm_target_0041452f)
    L_004144c6:
        mov eax,dword ptr [esi+72DAD4h]
    L_004144cc:
        cmp eax,ebx
    L_004144ce:
        je short L_004144dd
    L_004144d0:
        mov edi,dword ptr [eax]
    L_004144d2:
        cmp dword ptr [edi],ecx
    L_004144d4:
        je short L_004144f6
    L_004144d6:
        mov eax,dword ptr [eax+4]
    L_004144d9:
        cmp eax,ebx
    L_004144db:
        jne short L_004144d0
    L_004144dd:
        mov eax,dword ptr [esi+72DADCh]
    L_004144e3:
        cmp eax,ebx
    L_004144e5:
        TH10_REL8(0x74, 0x004144e5, VA_asm_target_0041452f)
    L_004144e7:
        mov edi,dword ptr [eax]
    L_004144e9:
        cmp dword ptr [edi],ecx
    L_004144eb:
        je short L_004144f6
    L_004144ed:
        mov eax,dword ptr [eax+4]
    L_004144f0:
        cmp eax,ebx
    L_004144f2:
        jne short L_004144e7
    L_004144f4:
        TH10_REL8(0xeb, 0x004144f4, VA_asm_target_0041452f)
    L_004144f6:
        mov eax,dword ptr [eax]
    L_004144f8:
        cmp eax,ebx
    L_004144fa:
        TH10_REL8(0x74, 0x004144fa, VA_asm_target_0041452f)
    L_004144fc:
        mov ecx,dword ptr [eax+35Ch]
    L_00414502:
        mov edi,4000000h
    L_00414507:
        or ecx,edi
    L_00414509:
        mov dword ptr [eax+35Ch],ecx
    L_0041450f:
        cmp dword ptr [eax+18h],ebx
    L_00414512:
        TH10_REL8(0x75, 0x00414512, VA_asm_target_0041452f)
    L_00414514:
        mov eax,dword ptr [eax+14h]
    L_00414517:
        cmp eax,ebx
    L_00414519:
        TH10_REL8(0x74, 0x00414519, VA_asm_target_0041452f)
    L_0041451b:
        TH10_REL8(0xeb, 0x0041451b, VA_asm_FUN_00414370_part_00414520)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00414520:
        mov ecx,dword ptr [eax]
    L_00414522:
        or dword ptr [ecx+35Ch],edi
    L_00414528:
        mov eax,dword ptr [eax+4]
    L_0041452b:
        cmp eax,ebx
    L_0041452d:
        jne short L_00414520
    L_0041452f:
        mov eax,dword ptr [esp+14h]
    L_00414533:
        mov dword ptr [edx],ebx
    L_00414535:
        add edx,4
    L_00414538:
        dec eax
    L_00414539:
        mov dword ptr [esp+14h],eax
    L_0041453d:
        TH10_REL8(0x75, 0x0041453d, VA_asm_target_004144c0)
    L_0041453f:
        pop edi
    L_00414540:
        pop esi
    L_00414541:
        mov dword ptr [ebp+9E90h],ebx
    L_00414547:
        pop ebp
    L_00414548:
        pop ebx
    L_00414549:
        ret 4
    }
}
