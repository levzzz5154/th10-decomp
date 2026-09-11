#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00409280..0x004093C7: FUN_00409280
// Naked body preserves the retail register/stack ABI.

// 0x00409280..0x004093C7: FUN_00409280
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409280_00409280() {
    __asm {
    L_00409280:
        mov ecx,dword ptr [esp+0Ch]
    L_00409284:
        push ebx
    L_00409285:
        push ebp
    L_00409286:
        mov ebp,dword ptr [esp+0Ch]
    L_0040928a:
        mov eax,dword ptr [ebp+3744h]
    L_00409290:
        test al,1
    L_00409292:
        push esi
    L_00409293:
        push edi
    L_00409294:
        mov edi,dword ptr [esp+18h]
    L_00409298:
        jne short L_004092c5
    L_0040929a:
        xor edx,edx
    L_0040929c:
        or eax,1
    L_0040929f:
        mov dword ptr [ebp+3738h],edx
    L_004092a5:
        mov dword ptr [ebp+3734h],0FFF0BDC1h
    L_004092af:
        mov dword ptr [ebp+373Ch],edx
    L_004092b5:
        mov dword ptr [ebp+3740h],476F78h
    L_004092bf:
        mov dword ptr [ebp+3744h],eax
    L_004092c5:
        xor eax,eax
    L_004092c7:
        mov dword ptr [ebp+3738h],eax
    L_004092cd:
        mov dword ptr [ebp+373Ch],eax
    L_004092d3:
        lea esi,[ebp+3748h]
    L_004092d9:
        mov dword ptr [ebp+3734h],0FFFFFFFFh
    L_004092e3:
        mov dword ptr [ebp+3788h],edi
    L_004092e9:
        mov eax,ecx
    L_004092eb:
        sub esi,ecx
    L_004092ed:
        TH10_NOP_LEA_ECX_DISP8()
    L_004092f0:
        mov dl,byte ptr [eax]
    L_004092f2:
        mov byte ptr [esi+eax],dl
    L_004092f5:
        inc eax
    L_004092f6:
        test dl,dl
    L_004092f8:
        jne short L_004092f0
    L_004092fa:
        mov eax,dword ptr [ebp+378Ch]
    L_00409300:
        mov edx,dword ptr [data_00477838]
    L_00409306:
        and eax,0FFFFFFE7h
    L_00409309:
        or eax,3
    L_0040930c:
        mov dword ptr [ebp+378Ch],eax
    L_00409312:
        cmp dword ptr [edx+10h],1
    L_00409316:
        je asm_target_004093be
    L_0040931c:
        mov edx,dword ptr [data_00474c68]
    L_00409322:
        mov ebx,dword ptr [data_0047783c]
    L_00409328:
        lea eax,[edi+edi*8]
    L_0040932b:
        mov edi,dword ptr [data_00474c6c]
    L_00409331:
        lea edi,[edi+edx*2]
    L_00409334:
        add edi,edx
    L_00409336:
        imul edi,437Ch
    L_0040933c:
        shl eax,4
    L_0040933f:
        add edi,eax
    L_00409341:
        mov esi,ecx
    L_00409343:
        lea edi,[edi+ebx+5A4h]
    L_0040934a:
        lea ebx,[ebx+force_disp32_zero]
    L_00409350:
        mov dl,byte ptr [esi]
    L_00409352:
        inc esi
    L_00409353:
        mov byte ptr [edi],dl
    L_00409355:
        inc edi
    L_00409356:
        test dl,dl
    L_00409358:
        jne short L_00409350
    L_0040935a:
        mov edx,dword ptr [data_00474c68]
    L_00409360:
        mov esi,dword ptr [data_00474c6c]
    L_00409366:
        lea esi,[esi+edx*2]
    L_00409369:
        add esi,edx
    L_0040936b:
        imul esi,437Ch
    L_00409371:
        add esi,eax
    L_00409373:
        lea edx,[esi+ebx+5A4h]
    L_0040937a:
        mov esi,dword ptr [edx+84h]
    L_00409380:
        cmp esi,1869Fh
    L_00409386:
        jge short L_0040938f
    L_00409388:
        inc esi
    L_00409389:
        mov dword ptr [edx+84h],esi
    L_0040938f:
        lea esi,[eax+ebx+19A8Ch]
    L_00409396:
        mov edx,esi
    L_00409398:
        sub edx,ecx
    L_0040939a:
        lea ebx,[ebx+force_disp32_zero]
    L_004093a0:
        mov al,byte ptr [ecx]
    L_004093a2:
        mov byte ptr [ecx+edx],al
    L_004093a5:
        inc ecx
    L_004093a6:
        test al,al
    L_004093a8:
        jne short L_004093a0
    L_004093aa:
        mov eax,dword ptr [esi+84h]
    L_004093b0:
        cmp eax,1869Fh
    L_004093b5:
        jge short L_004093be
    L_004093b7:
        inc eax
    L_004093b8:
        mov dword ptr [esi+84h],eax
    L_004093be:
        xor esi,esi
    L_004093c0:
        lea edi,[ebp+778h]
    L_004093c6:
        TH10_REL8(0xeb, 0x004093c6, VA_asm_FUN_00409280_part_004093d0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_004093d0:
        mov ecx,dword ptr [data_0047770c]
    L_004093d6:
        mov ecx,dword ptr [ecx+9EC8h]
    L_004093dc:
        lea ebx,[esi+3Ah]
    L_004093df:
        mov eax,edi
    L_004093e1:
        call asm_AnimationObject_LoadScript_0043e710
    L_004093e6:
        inc esi
    L_004093e7:
        add edi,3ACh
    L_004093ed:
        cmp esi,8
    L_004093f0:
        jl short L_004093d0
    L_004093f2:
        xor esi,esi
    L_004093f4:
        lea edi,[ebp+24D8h]
    L_004093fa:
        lea ebx,[ebx+force_disp32_zero]
    L_00409400:
        mov edx,dword ptr [data_0047770c]
    L_00409406:
        mov ecx,dword ptr [edx+9EC8h]
    L_0040940c:
        lea ebx,[esi+42h]
    L_0040940f:
        mov eax,edi
    L_00409411:
        call asm_AnimationObject_LoadScript_0043e710
    L_00409416:
        inc esi
    L_00409417:
        add edi,3ACh
    L_0040941d:
        cmp esi,5
    L_00409420:
        jl short L_00409400
    L_00409422:
        mov eax,dword ptr [data_004776e0]
    L_00409427:
        mov esi,dword ptr [data_00491c10]
    L_0040942d:
        mov ebx,dword ptr [eax+8994h]
    L_00409433:
        call asm_FUN_00449950_00449950
    L_00409438:
        mov edi,eax
    L_0040943a:
        mov eax,dword ptr [edi+35Ch]
    L_00409440:
        push 1
    L_00409442:
        or eax,40000000h
    L_00409447:
        push edi
    L_00409448:
        mov ecx,ebx
    L_0040944a:
        mov dword ptr [edi+20h],0Fh
    L_00409451:
        mov dword ptr [edi+35Ch],eax
    L_00409457:
        call asm_FUN_00449870_00449870
    L_0040945c:
        mov esi,dword ptr [data_00491c10]
    L_00409462:
        lea eax,[edi+4]
    L_00409465:
        xor ebx,ebx
    L_00409467:
        mov dword ptr [eax],edi
    L_00409469:
        mov dword ptr [eax+4],ebx
    L_0040946c:
        mov dword ptr [eax+8],ebx
    L_0040946f:
        cmp dword ptr [esi+72DAD4h],ebx
    L_00409475:
        jne short L_0040947f
    L_00409477:
        mov dword ptr [esi+72DAD4h],eax
    L_0040947d:
        jmp short L_0040949b
    L_0040947f:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00409485:
        mov edx,dword ptr [ecx+4]
    L_00409488:
        cmp edx,ebx
    L_0040948a:
        je short L_00409495
    L_0040948c:
        mov dword ptr [eax+4],edx
    L_0040948f:
        mov edx,dword ptr [ecx+4]
    L_00409492:
        mov dword ptr [edx+8],eax
    L_00409495:
        mov dword ptr [ecx+4],eax
    L_00409498:
        mov dword ptr [eax+8],ecx
    L_0040949b:
        mov dword ptr [esi+72DAD8h],eax
    L_004094a1:
        mov ecx,dword ptr [esi+732454h]
    L_004094a7:
        inc ecx
    L_004094a8:
        mov eax,ecx
    L_004094aa:
        cmp eax,ebx
    L_004094ac:
        mov dword ptr [esi+732454h],ecx
    L_004094b2:
        jne short L_004094bb
    L_004094b4:
        inc eax
    L_004094b5:
        mov dword ptr [esi+732454h],eax
    L_004094bb:
        mov eax,dword ptr [esi+732454h]
    L_004094c1:
        mov ecx,dword ptr [data_004776e0]
    L_004094c7:
        mov dword ptr [edi],eax
    L_004094c9:
        mov eax,dword ptr [esi+732454h]
    L_004094cf:
        mov dword ptr [ebp+768h],eax
    L_004094d5:
        mov ebx,dword ptr [ecx+899Ch]
    L_004094db:
        call asm_FUN_00449950_00449950
    L_004094e0:
        mov edi,eax
    L_004094e2:
        mov ecx,dword ptr [edi+35Ch]
    L_004094e8:
        or ecx,40000000h
    L_004094ee:
        push 48h
    L_004094f0:
        mov dword ptr [edi+35Ch],ecx
    L_004094f6:
        push edi
    L_004094f7:
        mov ecx,ebx
    L_004094f9:
        mov dword ptr [edi+20h],0Fh
    L_00409500:
        call asm_FUN_00449870_00449870
    L_00409505:
        mov esi,dword ptr [data_00491c10]
    L_0040950b:
        lea eax,[edi+4]
    L_0040950e:
        xor ecx,ecx
    L_00409510:
        mov dword ptr [eax],edi
    L_00409512:
        mov dword ptr [eax+4],ecx
    L_00409515:
        mov dword ptr [eax+8],ecx
    L_00409518:
        cmp dword ptr [esi+72DAD4h],ecx
    L_0040951e:
        jne short L_00409528
    L_00409520:
        mov dword ptr [esi+72DAD4h],eax
    L_00409526:
        jmp short L_00409544
    L_00409528:
        mov ecx,dword ptr [esi+72DAD8h]
    L_0040952e:
        mov edx,dword ptr [ecx+4]
    L_00409531:
        test edx,edx
    L_00409533:
        je short L_0040953e
    L_00409535:
        mov dword ptr [eax+4],edx
    L_00409538:
        mov edx,dword ptr [ecx+4]
    L_0040953b:
        mov dword ptr [edx+8],eax
    L_0040953e:
        mov dword ptr [ecx+4],eax
    L_00409541:
        mov dword ptr [eax+8],ecx
    L_00409544:
        mov dword ptr [esi+72DAD8h],eax
    L_0040954a:
        mov ecx,dword ptr [esi+732454h]
    L_00409550:
        inc ecx
    L_00409551:
        xor ebx,ebx
    L_00409553:
        mov eax,ecx
    L_00409555:
        cmp eax,ebx
    L_00409557:
        mov dword ptr [esi+732454h],ecx
    L_0040955d:
        jne short L_00409566
    L_0040955f:
        inc eax
    L_00409560:
        mov dword ptr [esi+732454h],eax
    L_00409566:
        mov eax,dword ptr [esi+732454h]
    L_0040956c:
        mov ecx,dword ptr [data_004776e0]
    L_00409572:
        mov dword ptr [edi],eax
    L_00409574:
        mov eax,dword ptr [esi+732454h]
    L_0040957a:
        mov dword ptr [ebp+76Ch],eax
    L_00409580:
        mov edi,dword ptr [ecx+8994h]
    L_00409586:
        call asm_FUN_00449950_00449950
    L_0040958b:
        mov esi,eax
    L_0040958d:
        mov edx,dword ptr [esi+35Ch]
    L_00409593:
        push 2
    L_00409595:
        or edx,40000000h
    L_0040959b:
        push esi
    L_0040959c:
        mov ecx,edi
    L_0040959e:
        mov dword ptr [esi+20h],0Fh
    L_004095a5:
        mov dword ptr [esi+35Ch],edx
    L_004095ab:
        call asm_FUN_00449870_00449870
    L_004095b0:
        mov ecx,dword ptr [data_00491c10]
    L_004095b6:
        lea eax,[esi+4]
    L_004095b9:
        mov dword ptr [eax],esi
    L_004095bb:
        mov dword ptr [eax+4],ebx
    L_004095be:
        mov dword ptr [eax+8],ebx
    L_004095c1:
        cmp dword ptr [ecx+72DAD4h],ebx
    L_004095c7:
        jne short L_004095d1
    L_004095c9:
        mov dword ptr [ecx+72DAD4h],eax
    L_004095cf:
        jmp short L_004095ed
    L_004095d1:
        mov edx,dword ptr [ecx+72DAD8h]
    L_004095d7:
        mov edi,dword ptr [edx+4]
    L_004095da:
        cmp edi,ebx
    L_004095dc:
        je short L_004095e7
    L_004095de:
        mov dword ptr [eax+4],edi
    L_004095e1:
        mov edi,dword ptr [edx+4]
    L_004095e4:
        mov dword ptr [edi+8],eax
    L_004095e7:
        mov dword ptr [edx+4],eax
    L_004095ea:
        mov dword ptr [eax+8],edx
    L_004095ed:
        mov dword ptr [ecx+72DAD8h],eax
    L_004095f3:
        mov edx,dword ptr [ecx+732454h]
    L_004095f9:
        inc edx
    L_004095fa:
        mov eax,edx
    L_004095fc:
        cmp eax,ebx
    L_004095fe:
        mov dword ptr [ecx+732454h],edx
    L_00409604:
        jne short L_0040960d
    L_00409606:
        inc eax
    L_00409607:
        mov dword ptr [ecx+732454h],eax
    L_0040960d:
        mov edx,dword ptr [ecx+732454h]
    L_00409613:
        mov dword ptr [esi],edx
    L_00409615:
        mov eax,dword ptr [ecx+732454h]
    L_0040961b:
        mov dword ptr [ebp+770h],eax
    L_00409621:
        mov edx,dword ptr [ebp+76Ch]
    L_00409627:
        cmp edx,ebx
    L_00409629:
        jne short L_0040962f
    L_0040962b:
        xor eax,eax
    L_0040962d:
        jmp short L_0040966e
    L_0040962f:
        mov eax,dword ptr [ecx+72DAD4h]
    L_00409635:
        cmp eax,ebx
    L_00409637:
        je short L_0040964d
    L_00409639:
        lea esp,[esp+force_disp32_zero]
    L_00409640:
        mov esi,dword ptr [eax]
    L_00409642:
        cmp dword ptr [esi],edx
    L_00409644:
        je short L_00409668
    L_00409646:
        mov eax,dword ptr [eax+4]
    L_00409649:
        cmp eax,ebx
    L_0040964b:
        jne short L_00409640
    L_0040964d:
        mov eax,dword ptr [ecx+72DADCh]
    L_00409653:
        cmp eax,ebx
    L_00409655:
        je short L_0040962b
    L_00409657:
        mov esi,dword ptr [eax]
    L_00409659:
        cmp dword ptr [esi],edx
    L_0040965b:
        je short L_00409668
    L_0040965d:
        mov eax,dword ptr [eax+4]
    L_00409660:
        cmp eax,ebx
    L_00409662:
        jne short L_00409657
    L_00409664:
        xor eax,eax
    L_00409666:
        jmp short L_0040966e
    L_00409668:
        mov eax,dword ptr [eax]
    L_0040966a:
        cmp eax,ebx
    L_0040966c:
        jne short L_00409674
    L_0040966e:
        mov dword ptr [ebp+76Ch],ebx
    L_00409674:
        mov edx,dword ptr [esp+1Ch]
    L_00409678:
        push edx
    L_00409679:
        push 0FFFFFFh
    L_0040967e:
        push ecx
    L_0040967f:
        mov esi,eax
    L_00409681:
        call asm_Ascii_FormatShadowedRetail_00447ae0
    L_00409686:
        add esp,0Ch
    L_00409689:
        push ebx
    L_0040968a:
        mov edi,0Eh
    L_0040968f:
        mov ecx,492590h
    L_00409694:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00409699:
        mov eax,dword ptr [data_004776f0]
    L_0040969e:
        mov esi,dword ptr [data_00491c10]
    L_004096a4:
        mov edi,dword ptr [eax+3E0B50h]
    L_004096aa:
        call asm_FUN_00449950_00449950
    L_004096af:
        mov esi,eax
    L_004096b1:
        mov ecx,dword ptr [esi+35Ch]
    L_004096b7:
        or ecx,40000000h
    L_004096bd:
        push 1A1h
    L_004096c2:
        mov dword ptr [esi+35Ch],ecx
    L_004096c8:
        push esi
    L_004096c9:
        mov ecx,edi
    L_004096cb:
        mov dword ptr [esi+20h],0Fh
    L_004096d2:
        call asm_FUN_00449870_00449870
    L_004096d7:
        mov edi,dword ptr [data_00491c10]
    L_004096dd:
        lea eax,[esi+4]
    L_004096e0:
        mov dword ptr [eax],esi
    L_004096e2:
        mov dword ptr [eax+4],ebx
    L_004096e5:
        mov dword ptr [eax+8],ebx
    L_004096e8:
        cmp dword ptr [edi+72DAD4h],ebx
    L_004096ee:
        jne short L_004096f8
    L_004096f0:
        mov dword ptr [edi+72DAD4h],eax
    L_004096f6:
        jmp short L_00409714
    L_004096f8:
        mov ecx,dword ptr [edi+72DAD8h]
    L_004096fe:
        mov edx,dword ptr [ecx+4]
    L_00409701:
        cmp edx,ebx
    L_00409703:
        je short L_0040970e
    L_00409705:
        mov dword ptr [eax+4],edx
    L_00409708:
        mov edx,dword ptr [ecx+4]
    L_0040970b:
        mov dword ptr [edx+8],eax
    L_0040970e:
        mov dword ptr [ecx+4],eax
    L_00409711:
        mov dword ptr [eax+8],ecx
    L_00409714:
        mov dword ptr [edi+72DAD8h],eax
    L_0040971a:
        mov ecx,dword ptr [edi+732454h]
    L_00409720:
        inc ecx
    L_00409721:
        mov eax,ecx
    L_00409723:
        cmp eax,ebx
    L_00409725:
        mov dword ptr [edi+732454h],ecx
    L_0040972b:
        jne short L_00409734
    L_0040972d:
        inc eax
    L_0040972e:
        mov dword ptr [edi+732454h],eax
    L_00409734:
        mov eax,dword ptr [edi+732454h]
    L_0040973a:
        mov ecx,dword ptr [data_00477704]
    L_00409740:
        mov dword ptr [esi],eax
    L_00409742:
        mov eax,dword ptr [edi+732454h]
    L_00409748:
        mov dword ptr [ebp+774h],eax
    L_0040974e:
        mov edx,dword ptr [ecx+10h]
    L_00409751:
        add edx,1068h
    L_00409757:
        mov ebx,dword ptr [edx]
    L_00409759:
        lea esi,[ebp+379Ch]
    L_0040975f:
        mov ecx,esi
    L_00409761:
        mov dword ptr [ecx],ebx
    L_00409763:
        mov ebx,dword ptr [edx+4]
    L_00409766:
        mov dword ptr [ecx+4],ebx
    L_00409769:
        mov edx,dword ptr [edx+8]
    L_0040976c:
        mov dword ptr [ecx+8],edx
    L_0040976f:
        push eax
    L_00409770:
        mov edx,edi
    L_00409772:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_00409777:
        mov ecx,dword ptr [ebp+774h]
    L_0040977d:
        xor esi,esi
    L_0040977f:
        cmp ecx,esi
    L_00409781:
        jne short L_00409787
    L_00409783:
        xor eax,eax
    L_00409785:
        jmp short L_004097bf
    L_00409787:
        mov eax,dword ptr [edi+72DAD4h]
    L_0040978d:
        cmp eax,esi
    L_0040978f:
        je short L_0040979e
    L_00409791:
        mov edx,dword ptr [eax]
    L_00409793:
        cmp dword ptr [edx],ecx
    L_00409795:
        je short L_004097b9
    L_00409797:
        mov eax,dword ptr [eax+4]
    L_0040979a:
        cmp eax,esi
    L_0040979c:
        jne short L_00409791
    L_0040979e:
        mov eax,dword ptr [edi+72DADCh]
    L_004097a4:
        cmp eax,esi
    L_004097a6:
        je short L_00409783
    L_004097a8:
        mov edx,dword ptr [eax]
    L_004097aa:
        cmp dword ptr [edx],ecx
    L_004097ac:
        je short L_004097b9
    L_004097ae:
        mov eax,dword ptr [eax+4]
    L_004097b1:
        cmp eax,esi
    L_004097b3:
        jne short L_004097a8
    L_004097b5:
        xor eax,eax
    L_004097b7:
        jmp short L_004097bf
    L_004097b9:
        mov eax,dword ptr [eax]
    L_004097bb:
        cmp eax,esi
    L_004097bd:
        jne short L_004097c5
    L_004097bf:
        mov dword ptr [ebp+774h],esi
    L_004097c5:
        add eax,10h
    L_004097c8:
        cmp eax,esi
    L_004097ca:
        je short L_004097e3
    L_004097cc:
        mov ecx,19Fh
    L_004097d1:
        mov edx,dword ptr [eax]
    L_004097d3:
        cmp word ptr [edx+38Ah],cx
    L_004097da:
        je short L_004097fd
    L_004097dc:
        mov eax,dword ptr [eax+4]
    L_004097df:
        cmp eax,esi
    L_004097e1:
        jne short L_004097d1
    L_004097e3:
        xor eax,eax
    L_004097e5:
        mov edx,dword ptr [esp+20h]
    L_004097e9:
        mov dword ptr [eax+314h],edx
    L_004097ef:
        mov ecx,dword ptr [ebp+774h]
    L_004097f5:
        cmp ecx,esi
    L_004097f7:
        jne short L_00409801
    L_004097f9:
        xor eax,eax
    L_004097fb:
        TH10_REL8(0xeb, 0x004097fb, VA_asm_target_0040983e)
    L_004097fd:
        mov eax,dword ptr [eax]
    L_004097ff:
        jmp short L_004097e5
    L_00409801:
        mov eax,dword ptr [edi+72DAD4h]
    L_00409807:
        cmp eax,esi
    L_00409809:
        TH10_REL8(0x74, 0x00409809, VA_asm_target_0040981d)
    L_0040980b:
        TH10_REL8(0xeb, 0x0040980b, VA_asm_FUN_00409280_part_00409810)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00409810:
        mov ebx,dword ptr [eax]
    L_00409812:
        cmp dword ptr [ebx],ecx
    L_00409814:
        je short L_00409838
    L_00409816:
        mov eax,dword ptr [eax+4]
    L_00409819:
        cmp eax,esi
    L_0040981b:
        jne short L_00409810
    L_0040981d:
        mov eax,dword ptr [edi+72DADCh]
    L_00409823:
        cmp eax,esi
    L_00409825:
        TH10_REL8(0x74, 0x00409825, VA_asm_target_004097f9)
    L_00409827:
        mov ebx,dword ptr [eax]
    L_00409829:
        cmp dword ptr [ebx],ecx
    L_0040982b:
        je short L_00409838
    L_0040982d:
        mov eax,dword ptr [eax+4]
    L_00409830:
        cmp eax,esi
    L_00409832:
        jne short L_00409827
    L_00409834:
        xor eax,eax
    L_00409836:
        jmp short L_0040983e
    L_00409838:
        mov eax,dword ptr [eax]
    L_0040983a:
        cmp eax,esi
    L_0040983c:
        jne short L_00409844
    L_0040983e:
        mov dword ptr [ebp+774h],esi
    L_00409844:
        add eax,10h
    L_00409847:
        cmp eax,esi
    L_00409849:
        je short L_00409866
    L_0040984b:
        mov ecx,1A0h
    L_00409850:
        mov ebx,dword ptr [eax]
    L_00409852:
        cmp word ptr [ebx+38Ah],cx
    L_00409859:
        je asm_target_00409903
    L_0040985f:
        mov eax,dword ptr [eax+4]
    L_00409862:
        cmp eax,esi
    L_00409864:
        jne short L_00409850
    L_00409866:
        xor eax,eax
    L_00409868:
        mov dword ptr [eax+314h],edx
    L_0040986e:
        mov dword ptr [ebp+3798h],edx
    L_00409874:
        mov eax,dword ptr [data_00474c7c]
    L_00409879:
        lea eax,[eax+eax*2+0Ah]
    L_0040987d:
        imul eax,dword ptr [data_00474c4c]
    L_00409884:
        lea eax,[eax+eax*4]
    L_00409887:
        shl eax,1
    L_00409889:
        cmp eax,5F5E100h
    L_0040988e:
        mov dword ptr [ebp+3790h],eax
    L_00409894:
        mov dword ptr [ebp+3794h],eax
    L_0040989a:
        jl short L_004098a6
    L_0040989c:
        mov dword ptr [ebp+3794h],5F5E0FFh
    L_004098a6:
        mov eax,dword ptr [data_004776f0]
    L_004098ab:
        mov ebx,dword ptr [eax+3E0B50h]
    L_004098b1:
        mov esi,edi
    L_004098b3:
        call asm_FUN_00449950_00449950
    L_004098b8:
        mov esi,eax
    L_004098ba:
        mov ecx,dword ptr [esi+35Ch]
    L_004098c0:
        or ecx,40000000h
    L_004098c6:
        push 1ABh
    L_004098cb:
        mov dword ptr [esi+35Ch],ecx
    L_004098d1:
        push esi
    L_004098d2:
        mov ecx,ebx
    L_004098d4:
        mov dword ptr [esi+20h],0Fh
    L_004098db:
        call asm_FUN_00449870_00449870
    L_004098e0:
        mov ecx,dword ptr [data_00491c10]
    L_004098e6:
        lea eax,[esi+4]
    L_004098e9:
        xor ebx,ebx
    L_004098eb:
        mov dword ptr [eax],esi
    L_004098ed:
        mov dword ptr [eax+4],ebx
    L_004098f0:
        mov dword ptr [eax+8],ebx
    L_004098f3:
        cmp dword ptr [ecx+72DAD4h],ebx
    L_004098f9:
        jne short L_0040990a
    L_004098fb:
        mov dword ptr [ecx+72DAD4h],eax
    L_00409901:
        jmp short L_00409926
    L_00409903:
        mov eax,dword ptr [eax]
    L_00409905:
        jmp asm_target_00409868
    L_0040990a:
        mov edx,dword ptr [ecx+72DAD8h]
    L_00409910:
        mov edi,dword ptr [edx+4]
    L_00409913:
        cmp edi,ebx
    L_00409915:
        je short L_00409920
    L_00409917:
        mov dword ptr [eax+4],edi
    L_0040991a:
        mov edi,dword ptr [edx+4]
    L_0040991d:
        mov dword ptr [edi+8],eax
    L_00409920:
        mov dword ptr [edx+4],eax
    L_00409923:
        mov dword ptr [eax+8],edx
    L_00409926:
        mov dword ptr [ecx+72DAD8h],eax
    L_0040992c:
        mov edx,dword ptr [ecx+732454h]
    L_00409932:
        inc edx
    L_00409933:
        mov eax,edx
    L_00409935:
        cmp eax,ebx
    L_00409937:
        mov dword ptr [ecx+732454h],edx
    L_0040993d:
        jne short L_00409946
    L_0040993f:
        inc eax
    L_00409940:
        mov dword ptr [ecx+732454h],eax
    L_00409946:
        mov ecx,dword ptr [ecx+732454h]
    L_0040994c:
        mov dword ptr [esi],ecx
    L_0040994e:
        mov eax,dword ptr [data_00474c7c]
    L_00409953:
        dec eax
    L_00409954:
        cmp eax,6
    L_00409957:
        ja asm_target_00409bdc
    L_0040995d:
        jmp dword ptr [eax*4+409BE4h]
    L_00409964:
        mov edx,dword ptr [data_00477704]
    L_0040996a:
        mov eax,dword ptr [edx+38h]
    L_0040996d:
        push eax
    L_0040996e:
        lea esi,[ebp+10h]
    L_00409971:
        mov eax,0Ch
    L_00409976:
        call asm_FUN_00404f30_00404f30
    L_0040997b:
        mov ecx,dword ptr [data_00477704]
    L_00409981:
        mov edx,dword ptr [ecx+38h]
    L_00409984:
        lea esi,[ebp+3BCh]
    L_0040998a:
        push edx
    L_0040998b:
        mov eax,0Bh
    L_00409990:
        call asm_FUN_00404f30_00404f30
    L_00409995:
        cmp dword ptr [esp+18h],2
    L_0040999a:
        mov esi,dword ptr [data_00491c10]
    L_004099a0:
        jl short L_004099b6
    L_004099a2:
        mov eax,dword ptr [data_00477704]
    L_004099a7:
        mov edi,dword ptr [eax+38h]
    L_004099aa:
        call asm_FUN_00449950_00449950
    L_004099af:
        push 0Eh
    L_004099b1:
        jmp asm_target_00409bb0
    L_004099b6:
        mov ecx,dword ptr [data_00477704]
    L_004099bc:
        mov edi,dword ptr [ecx+38h]
    L_004099bf:
        call asm_FUN_00449950_00449950
    L_004099c4:
        push 0Fh
    L_004099c6:
        jmp asm_target_00409bb0
    L_004099cb:
        mov edx,dword ptr [data_00477704]
    L_004099d1:
        mov eax,dword ptr [edx+38h]
    L_004099d4:
        push eax
    L_004099d5:
        lea esi,[ebp+10h]
    L_004099d8:
        mov eax,0Eh
    L_004099dd:
        call asm_FUN_00404f30_00404f30
    L_004099e2:
        mov ecx,dword ptr [data_00477704]
    L_004099e8:
        mov edx,dword ptr [ecx+38h]
    L_004099eb:
        lea esi,[ebp+3BCh]
    L_004099f1:
        push edx
    L_004099f2:
        mov eax,0Fh
    L_004099f7:
        call asm_FUN_00404f30_00404f30
    L_004099fc:
        mov eax,dword ptr [data_00477704]
    L_00409a01:
        mov esi,dword ptr [data_00491c10]
    L_00409a07:
        mov edi,dword ptr [eax+38h]
    L_00409a0a:
        call asm_FUN_00449950_00449950
    L_00409a0f:
        push 11h
    L_00409a11:
        jmp asm_target_00409bb0
    L_00409a16:
        mov ecx,dword ptr [data_00477704]
    L_00409a1c:
        mov edx,dword ptr [ecx+38h]
    L_00409a1f:
        lea esi,[ebp+10h]
    L_00409a22:
        push edx
    L_00409a23:
        mov eax,12h
    L_00409a28:
        call asm_FUN_00404f30_00404f30
    L_00409a2d:
        mov eax,dword ptr [data_00477704]
    L_00409a32:
        mov ecx,dword ptr [eax+38h]
    L_00409a35:
        lea esi,[ebp+3BCh]
    L_00409a3b:
        push ecx
    L_00409a3c:
        mov eax,13h
    L_00409a41:
        call asm_FUN_00404f30_00404f30
    L_00409a46:
        mov edx,dword ptr [data_00477704]
    L_00409a4c:
        mov esi,dword ptr [data_00491c10]
    L_00409a52:
        mov edi,dword ptr [edx+38h]
    L_00409a55:
        call asm_FUN_00449950_00449950
    L_00409a5a:
        push 15h
    L_00409a5c:
        jmp asm_target_00409bb0
    L_00409a61:
        mov eax,dword ptr [data_00477704]
    L_00409a66:
        mov ecx,dword ptr [eax+38h]
    L_00409a69:
        lea esi,[ebp+10h]
    L_00409a6c:
        push ecx
    L_00409a6d:
        mov eax,13h
    L_00409a72:
        call asm_FUN_00404f30_00404f30
    L_00409a77:
        mov edx,dword ptr [data_00477704]
    L_00409a7d:
        mov eax,dword ptr [edx+38h]
    L_00409a80:
        push eax
    L_00409a81:
        lea esi,[ebp+3BCh]
    L_00409a87:
        mov eax,14h
    L_00409a8c:
        call asm_FUN_00404f30_00404f30
    L_00409a91:
        mov ecx,dword ptr [data_00477704]
    L_00409a97:
        mov esi,dword ptr [data_00491c10]
    L_00409a9d:
        mov edi,dword ptr [ecx+38h]
    L_00409aa0:
        call asm_FUN_00449950_00449950
    L_00409aa5:
        push 16h
    L_00409aa7:
        jmp asm_target_00409bb0
    L_00409aac:
        mov edx,dword ptr [data_00477704]
    L_00409ab2:
        mov eax,dword ptr [edx+38h]
    L_00409ab5:
        push eax
    L_00409ab6:
        lea esi,[ebp+10h]
    L_00409ab9:
        mov eax,0Ch
    L_00409abe:
        call asm_FUN_00404f30_00404f30
    L_00409ac3:
        mov ecx,dword ptr [data_00477704]
    L_00409ac9:
        mov edx,dword ptr [ecx+38h]
    L_00409acc:
        lea esi,[ebp+3BCh]
    L_00409ad2:
        push edx
    L_00409ad3:
        mov eax,0Dh
    L_00409ad8:
        call asm_FUN_00404f30_00404f30
    L_00409add:
        mov eax,dword ptr [data_00477704]
    L_00409ae2:
        mov esi,dword ptr [data_00491c10]
    L_00409ae8:
        mov edi,dword ptr [eax+38h]
    L_00409aeb:
        call asm_FUN_00449950_00449950
    L_00409af0:
        push 0Fh
    L_00409af2:
        jmp asm_target_00409bb0
    L_00409af7:
        mov ecx,dword ptr [data_00477704]
    L_00409afd:
        mov edx,dword ptr [ecx+38h]
    L_00409b00:
        lea esi,[ebp+10h]
    L_00409b03:
        push edx
    L_00409b04:
        mov eax,21h
    L_00409b09:
        call asm_FUN_00404f30_00404f30
    L_00409b0e:
        mov eax,dword ptr [data_00477704]
    L_00409b13:
        mov ecx,dword ptr [eax+38h]
    L_00409b16:
        lea esi,[ebp+3BCh]
    L_00409b1c:
        push ecx
    L_00409b1d:
        mov eax,22h
    L_00409b22:
        call asm_FUN_00404f30_00404f30
    L_00409b27:
        mov edx,dword ptr [data_00477704]
    L_00409b2d:
        mov esi,dword ptr [data_00491c10]
    L_00409b33:
        mov edi,dword ptr [edx+38h]
    L_00409b36:
        call asm_FUN_00449950_00449950
    L_00409b3b:
        push 24h
    L_00409b3d:
        jmp short L_00409bb0
    L_00409b3f:
        cmp dword ptr [data_00474c84],18h
    L_00409b46:
        mov eax,dword ptr [data_00477704]
    L_00409b4b:
        mov ecx,dword ptr [eax+38h]
    L_00409b4e:
        lea esi,[ebp+10h]
    L_00409b51:
        push ecx
    L_00409b52:
        jge short L_00409b76
    L_00409b54:
        mov eax,26h
    L_00409b59:
        call asm_FUN_00404f30_00404f30
    L_00409b5e:
        mov edx,dword ptr [data_00477704]
    L_00409b64:
        mov esi,dword ptr [data_00491c10]
    L_00409b6a:
        mov edi,dword ptr [edx+38h]
    L_00409b6d:
        call asm_FUN_00449950_00449950
    L_00409b72:
        push 28h
    L_00409b74:
        jmp short L_00409bb0
    L_00409b76:
        mov eax,1Bh
    L_00409b7b:
        call asm_FUN_00404f30_00404f30
    L_00409b80:
        mov edx,dword ptr [data_00477704]
    L_00409b86:
        mov eax,dword ptr [edx+38h]
    L_00409b89:
        push eax
    L_00409b8a:
        lea esi,[ebp+3BCh]
    L_00409b90:
        mov eax,1Ch
    L_00409b95:
        call asm_FUN_00404f30_00404f30
    L_00409b9a:
        mov ecx,dword ptr [data_00477704]
    L_00409ba0:
        mov esi,dword ptr [data_00491c10]
    L_00409ba6:
        mov edi,dword ptr [ecx+38h]
    L_00409ba9:
        call asm_FUN_00449950_00449950
    L_00409bae:
        push 1Eh
    L_00409bb0:
        mov esi,eax
    L_00409bb2:
        or dword ptr [esi+35Ch],40000000h
    L_00409bbc:
        mov ecx,edi
    L_00409bbe:
        push esi
    L_00409bbf:
        mov dword ptr [esi+20h],0Fh
    L_00409bc6:
        call asm_FUN_00449870_00449870
    L_00409bcb:
        mov edx,dword ptr [data_00491c10]
    L_00409bd1:
        lea eax,[esp+1Ch]
    L_00409bd5:
        mov ebx,esi
    L_00409bd7:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00409bdc:
        pop edi
    L_00409bdd:
        pop esi
    L_00409bde:
        pop ebp
    L_00409bdf:
        pop ebx
    L_00409be0:
        ret 10h
        _emit 0x90
        _emit 0x64
        _emit 0x99
        _emit 0x40
        _emit 0x00
        _emit 0xcb
        _emit 0x99
        _emit 0x40
        _emit 0x00
        _emit 0x16
        _emit 0x9a
        _emit 0x40
        _emit 0x00
        _emit 0x61
        _emit 0x9a
        _emit 0x40
        _emit 0x00
        _emit 0xac
        _emit 0x9a
        _emit 0x40
        _emit 0x00
        _emit 0xf7
        _emit 0x9a
        _emit 0x40
        _emit 0x00
        _emit 0x3f
        _emit 0x9b
        _emit 0x40
        _emit 0x00
    }
}
