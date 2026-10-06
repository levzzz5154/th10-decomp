#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// Unrecovered: complete ordinary C++ emits 874/876 bytes with three diagnostic
// instruction differences (two ID arguments and the primary position Z copy).
// Its shared 20-function genuine effect/pickup graph and 2508 passing bounded
// comparisons are maintained in reference/semantic_candidates/
// player_effect_pickup_00428280. The former 876/876 count described this naked
// baseline. No complete raw fixed-address C++ proof or selection exists.
// 0x00428280..0x004285EB: FUN_00428280
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428280_00428280() {
    __asm {
    L_00428280:
        sub esp,8
    L_00428283:
        push ebx
    L_00428284:
        push ebp
    L_00428285:
        mov ebp,dword ptr [esp+14h]
    L_00428289:
        push esi
    L_0042828a:
        push edi
    L_0042828b:
        lea edi,[ebp+49Ch]
    L_00428291:
        mov dword ptr [esp+10h],edi
    L_00428295:
        add edi,20h
    L_00428298:
        mov dword ptr [esp+14h],80h
    L_004282a0:
        xor ebx,ebx
    L_004282a2:
        TH10_REL8(0xeb, 0x004282a2, VA_asm_FUN_00428280_part_004282b0)
    L_004282a4:
        mov ebp,dword ptr [esp+1Ch]
    L_004282a8:
        TH10_REL8(0xeb, 0x004282a8, VA_asm_FUN_00428280_part_004282b0)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_004282b0:
        mov eax,dword ptr [edi+20h]
    L_004282b3:
        cmp eax,ebx
    L_004282b5:
        je asm_target_004285c3
    L_004282bb:
        mov ecx,dword ptr [edi+38h]
    L_004282be:
        cmp byte ptr [ecx+1Dh],3
    L_004282c2:
        mov esi,1
    L_004282c7:
        jne short L_00428309
    L_004282c9:
        cmp eax,esi
    L_004282cb:
        jne short L_00428309
    L_004282cd:
        cmp dword ptr [ebp+464h],ebx
    L_004282d3:
        jl short L_004282e4
    L_004282d5:
        movsx eax,byte ptr [ecx+1Ch]
    L_004282d9:
        mov ecx,dword ptr [ebp+3500h]
    L_004282df:
        dec eax
    L_004282e0:
        cmp eax,ecx
    L_004282e2:
        jl short L_00428309
    L_004282e4:
        lea eax,[edi+24h]
    L_004282e7:
        call asm_FUN_00409e50_00409e50
    L_004282ec:
        lea eax,[edi+28h]
    L_004282ef:
        call asm_FUN_00409e50_00409e50
    L_004282f4:
        mov ecx,dword ptr [edi+38h]
    L_004282f7:
        mov dword ptr [edi+20h],2
    L_004282fe:
        movsx edx,byte ptr [ecx+1Ch]
    L_00428302:
        mov dword ptr [ebp+edx*4+42F4h],ebx
    L_00428309:
        mov eax,dword ptr [edi+38h]
    L_0042830c:
        cmp byte ptr [eax+1Dh],3
    L_00428310:
        jne short L_00428355
    L_00428312:
        cmp dword ptr [edi+20h],esi
    L_00428315:
        jne short L_00428355
    L_00428317:
        mov eax,dword ptr [data_0047770c]
    L_0042831c:
        cmp eax,ebx
    L_0042831e:
        je short L_00428328
    L_00428320:
        cmp dword ptr [eax+9EB8h],ebx
    L_00428326:
        jne short L_00428330
    L_00428328:
        cmp dword ptr [data_00477704],ebx
    L_0042832e:
        jne short L_00428355
    L_00428330:
        lea eax,[edi+24h]
    L_00428333:
        mov dword ptr [edi+20h],2
    L_0042833a:
        call asm_FUN_00409e50_00409e50
    L_0042833f:
        lea eax,[edi+28h]
    L_00428342:
        call asm_FUN_00409e50_00409e50
    L_00428347:
        mov ecx,dword ptr [edi+38h]
    L_0042834a:
        movsx edx,byte ptr [ecx+1Ch]
    L_0042834e:
        mov dword ptr [ebp+edx*4+42F4h],ebx
    L_00428355:
        mov eax,dword ptr [edi+38h]
    L_00428358:
        cmp byte ptr [eax+1Dh],3
    L_0042835c:
        jne short L_00428378
    L_0042835e:
        cmp dword ptr [edi+30h],ebx
    L_00428361:
        jne short L_00428378
    L_00428363:
        cmp dword ptr [edi+20h],esi
    L_00428366:
        jne short L_00428378
    L_00428368:
        cmp dword ptr [edi+34h],esi
    L_0042836b:
        jne short L_00428378
    L_0042836d:
        lea eax,[edi+24h]
    L_00428370:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00428375:
        mov dword ptr [edi+34h],ebx
    L_00428378:
        mov ecx,dword ptr [edi+38h]
    L_0042837b:
        mov dword ptr [edi+30h],ebx
    L_0042837e:
        mov eax,dword ptr [ecx+28h]
    L_00428381:
        cmp eax,ebx
    L_00428383:
        je short L_0042838d
    L_00428385:
        mov edx,dword ptr [esp+10h]
    L_00428389:
        mov ecx,ebp
    L_0042838b:
        call eax
    L_0042838d:
        test byte ptr [edi+1Ch],1
    L_00428391:
        jne short L_004283a7
    L_00428393:
        mov edx,dword ptr [edi+0Ch]
    L_00428396:
        mov eax,dword ptr [edi+10h]
    L_00428399:
        push edx
    L_0042839a:
        push eax
    L_0042839b:
        mov ecx,edi
    L_0042839d:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_004283a2:
        mov dword ptr [edi+8],ebx
    L_004283a5:
        jmp short L_004283c2
    L_004283a7:
        fld dword ptr [edi+18h]
    L_004283aa:
        push ecx
    L_004283ab:
        fadd dword ptr [edi+14h]
    L_004283ae:
        fstp dword ptr [edi+14h]
    L_004283b1:
        fld dword ptr [edi+0Ch]
    L_004283b4:
        fadd dword ptr [edi+10h]
    L_004283b7:
        fstp dword ptr [esp]
    L_004283ba:
        call asm_Angle_Normalize_0044bc70
    L_004283bf:
        fstp dword ptr [edi+10h]
    L_004283c2:
        lea esi,[edi-0Ch]
    L_004283c5:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_004283ca:
        mov ecx,dword ptr [edi+24h]
    L_004283cd:
        cmp ecx,ebx
    L_004283cf:
        mov edx,dword ptr [data_00491c10]
    L_004283d5:
        je short L_0042841a
    L_004283d7:
        mov eax,dword ptr [edx+72DAD4h]
    L_004283dd:
        cmp eax,ebx
    L_004283df:
        je short L_004283ef
    L_004283e1:
        mov ebp,dword ptr [eax]
    L_004283e3:
        cmp dword ptr [ebp],ecx
    L_004283e6:
        je short L_00428410
    L_004283e8:
        mov eax,dword ptr [eax+4]
    L_004283eb:
        cmp eax,ebx
    L_004283ed:
        jne short L_004283e1
    L_004283ef:
        mov eax,dword ptr [edx+72DADCh]
    L_004283f5:
        cmp eax,ebx
    L_004283f7:
        je short L_0042841a
    L_004283f9:
        lea esp,[esp+force_disp32_zero]
    L_00428400:
        mov ebp,dword ptr [eax]
    L_00428402:
        cmp dword ptr [ebp],ecx
    L_00428405:
        je short L_00428410
    L_00428407:
        mov eax,dword ptr [eax+4]
    L_0042840a:
        cmp eax,ebx
    L_0042840c:
        jne short L_00428400
    L_0042840e:
        jmp short L_0042841a
    L_00428410:
        mov ebp,dword ptr [eax]
    L_00428412:
        cmp ebp,ebx
    L_00428414:
        jne asm_target_004284ad
    L_0042841a:
        mov dword ptr [edi+20h],ebx
    L_0042841d:
        mov ecx,dword ptr [edi+28h]
    L_00428420:
        cmp ecx,ebx
    L_00428422:
        je short L_0042849f
    L_00428424:
        mov eax,dword ptr [edx+72DAD4h]
    L_0042842a:
        cmp eax,ebx
    L_0042842c:
        je short L_0042843d
    L_0042842e:
        mov edi,edi
    L_00428430:
        mov esi,dword ptr [eax]
    L_00428432:
        cmp dword ptr [esi],ecx
    L_00428434:
        je short L_00428462
    L_00428436:
        mov eax,dword ptr [eax+4]
    L_00428439:
        cmp eax,ebx
    L_0042843b:
        jne short L_00428430
    L_0042843d:
        mov eax,dword ptr [edx+72DADCh]
    L_00428443:
        cmp eax,ebx
    L_00428445:
        je short L_0042849f
    L_00428447:
        mov edx,dword ptr [eax]
    L_00428449:
        cmp dword ptr [edx],ecx
    L_0042844b:
        je short L_00428462
    L_0042844d:
        mov eax,dword ptr [eax+4]
    L_00428450:
        cmp eax,ebx
    L_00428452:
        jne short L_00428447
    L_00428454:
        mov dword ptr [edi+28h],ebx
    L_00428457:
        mov dword ptr [edi+24h],ebx
    L_0042845a:
        mov dword ptr [edi+28h],ebx
    L_0042845d:
        jmp asm_target_004285c3
    L_00428462:
        mov eax,dword ptr [eax]
    L_00428464:
        cmp eax,ebx
    L_00428466:
        je short L_0042849f
    L_00428468:
        mov esi,dword ptr [eax+35Ch]
    L_0042846e:
        mov ecx,dword ptr [eax+18h]
    L_00428471:
        mov edx,4000000h
    L_00428476:
        or esi,edx
    L_00428478:
        cmp ecx,ebx
    L_0042847a:
        mov dword ptr [eax+35Ch],esi
    L_00428480:
        jne short L_0042849f
    L_00428482:
        mov eax,dword ptr [eax+14h]
    L_00428485:
        cmp eax,ebx
    L_00428487:
        je short L_0042849f
    L_00428489:
        lea esp,[esp+force_disp32_zero]
    L_00428490:
        mov ecx,dword ptr [eax]
    L_00428492:
        or dword ptr [ecx+35Ch],edx
    L_00428498:
        mov eax,dword ptr [eax+4]
    L_0042849b:
        cmp eax,ebx
    L_0042849d:
        jne short L_00428490
    L_0042849f:
        mov dword ptr [edi+28h],ebx
    L_004284a2:
        mov dword ptr [edi+24h],ebx
    L_004284a5:
        mov dword ptr [edi+28h],ebx
    L_004284a8:
        jmp asm_target_004285c3
    L_004284ad:
        mov eax,dword ptr [edi+38h]
    L_004284b0:
        cmp byte ptr [eax+1Dh],3
    L_004284b4:
        je short L_004284f7
    L_004284b6:
        cmp dword ptr [edi-1Ch],0Ah
    L_004284ba:
        jl short L_004284f7
    L_004284bc:
        mov eax,dword ptr [ebp+394h]
    L_004284c2:
        fld dword ptr [eax+30h]
    L_004284c5:
        sub esp,8
    L_004284c8:
        fmul dword ptr [ebp+40h]
    L_004284cb:
        mov ecx,esi
    L_004284cd:
        fstp dword ptr [esp+4]
    L_004284d1:
        fld dword ptr [eax+34h]
    L_004284d4:
        fmul dword ptr [ebp+3Ch]
    L_004284d7:
        fstp dword ptr [esp]
    L_004284da:
        call asm_EffectPool_OutsideViewport_00428d70
    L_004284df:
        test eax,eax
    L_004284e1:
        je short L_004284f7
    L_004284e3:
        mov ecx,dword ptr [edi+24h]
    L_004284e6:
        push ecx
    L_004284e7:
        call asm_AnimationManager_SetFlag_004492a0
    L_004284ec:
        mov dword ptr [edi+24h],ebx
    L_004284ef:
        mov dword ptr [edi+20h],ebx
    L_004284f2:
        jmp asm_target_004285c3
    L_004284f7:
        fld dword ptr [esi]
    L_004284f9:
        fadd dword ptr [data_00470b4c]
    L_004284ff:
        fstp dword ptr [ebp+340h]
    L_00428505:
        fld dword ptr [edi-8]
    L_00428508:
        fadd dword ptr [data_00470b48]
    L_0042850e:
        fstp dword ptr [ebp+344h]
    L_00428514:
        mov eax,dword ptr [edi-4]
    L_00428517:
        mov dword ptr [ebp+348h],eax
    L_0042851d:
        mov eax,dword ptr [edi+28h]
    L_00428520:
        cmp eax,ebx
    L_00428522:
        je short L_0042855b
    L_00428524:
        mov ecx,eax
    L_00428526:
        push ecx
    L_00428527:
        call asm_AnimationManager_Find_004491c0
    L_0042852c:
        cmp eax,ebx
    L_0042852e:
        jne short L_00428535
    L_00428530:
        mov dword ptr [edi+28h],ebx
    L_00428533:
        jmp short L_0042855b
    L_00428535:
        fld dword ptr [esi]
    L_00428537:
        fadd dword ptr [data_00470b4c]
    L_0042853d:
        fstp dword ptr [eax+340h]
    L_00428543:
        fld dword ptr [edi-8]
    L_00428546:
        fadd dword ptr [data_00470b48]
    L_0042854c:
        fstp dword ptr [eax+344h]
    L_00428552:
        mov edx,dword ptr [edi-4]
    L_00428555:
        mov dword ptr [eax+348h],edx
    L_0042855b:
        mov eax,dword ptr [ebp+35Ch]
    L_00428561:
        test eax,8000000h
    L_00428566:
        je short L_00428577
    L_00428568:
        mov ecx,dword ptr [edi+10h]
    L_0042856b:
        or eax,4
    L_0042856e:
        mov dword ptr [ebp+2Ch],ecx
    L_00428571:
        mov dword ptr [ebp+35Ch],eax
    L_00428577:
        mov eax,dword ptr [esp+10h]
    L_0042857b:
        mov edx,dword ptr [edi-1Ch]
    L_0042857e:
        mov ecx,dword ptr [edi-14h]
    L_00428581:
        mov dword ptr [eax],edx
    L_00428583:
        fld dword ptr [ecx]
    L_00428585:
        fcomp dword ptr [data_00470b68]
    L_0042858b:
        fnstsw ax
    L_0042858d:
        test ah,41h
    L_00428590:
        jne short L_004285b3
    L_00428592:
        fld dword ptr [ecx]
    L_00428594:
        fcomp dword ptr [data_00470b64]
    L_0042859a:
        fnstsw ax
    L_0042859c:
        test ah,5
    L_0042859f:
        jp short L_004285b3
    L_004285a1:
        fld dword ptr [edi-18h]
    L_004285a4:
        inc edx
    L_004285a5:
        fadd dword ptr [data_00470afc]
    L_004285ab:
        mov dword ptr [edi-1Ch],edx
    L_004285ae:
        fstp dword ptr [edi-18h]
    L_004285b1:
        jmp short L_004285c3
    L_004285b3:
        fld dword ptr [edi-18h]
    L_004285b6:
        fadd dword ptr [ecx]
    L_004285b8:
        fst dword ptr [edi-18h]
    L_004285bb:
        call asm_FUN_00463b2c_00463b2c
    L_004285c0:
        mov dword ptr [edi-1Ch],eax
    L_004285c3:
        mov edx,dword ptr [esp+10h]
    L_004285c7:
        mov eax,dword ptr [esp+14h]
    L_004285cb:
        add edx,5Ch
    L_004285ce:
        add edi,5Ch
    L_004285d1:
        dec eax
    L_004285d2:
        mov dword ptr [esp+10h],edx
    L_004285d6:
        mov dword ptr [esp+14h],eax
    L_004285da:
        jne asm_target_004282a4
    L_004285e0:
        pop edi
    L_004285e1:
        pop esi
    L_004285e2:
        pop ebp
    L_004285e3:
        xor eax,eax
    L_004285e5:
        pop ebx
    L_004285e6:
        add esp,8
    L_004285e9:
        ret 4
    }
}
