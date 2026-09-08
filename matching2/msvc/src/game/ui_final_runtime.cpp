#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

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
    }
}

// 0x004093D0..0x0040980C: FUN_00409280
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409280_part_004093d0() {
    __asm {
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
    }
}

// 0x00409810..0x00409BE2: FUN_00409280
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00409280_part_00409810() {
    __asm {
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
    }
}

// 0x00414900..0x004149EC: FUN_00414900
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414900_00414900() {
    __asm {
    L_00414900:
        push ecx
    L_00414901:
        push edi
    L_00414902:
        mov edi,dword ptr [esp+0Ch]
    L_00414906:
        test byte ptr [edi+9EB4h],10h
    L_0041490d:
        je short L_0041493c
    L_0041490f:
        mov ecx,dword ptr [edi+9ECCh]
    L_00414915:
        inc ecx
    L_00414916:
        mov eax,ecx
    L_00414918:
        cmp eax,78h
    L_0041491b:
        mov dword ptr [edi+9ECCh],ecx
    L_00414921:
        jl short L_0041493c
    L_00414923:
        mov eax,dword ptr [data_00491ff4]
    L_00414928:
        and eax,1000h
    L_0041492d:
        neg eax
    L_0041492f:
        sbb eax,eax
    L_00414931:
        and eax,0FFFFFFF4h
    L_00414934:
        add eax,0Eh
    L_00414937:
        mov dword ptr [data_00491fb8],eax
    L_0041493c:
        push ebx
    L_0041493d:
        push ebp
    L_0041493e:
        push esi
    L_0041493f:
        lea esi,[edi+4980h]
    L_00414945:
        mov ebx,9
    L_0041494a:
        lea ebx,[ebx+force_disp32_zero]
    L_00414950:
        push esi
    L_00414951:
        call asm_FUN_0043ee30_0043ee30
    L_00414956:
        add esi,3ACh
    L_0041495c:
        dec ebx
    L_0041495d:
        jne short L_00414950
    L_0041495f:
        lea esi,[edi+6A8Ch]
    L_00414965:
        mov ebx,4
    L_0041496a:
        lea ebx,[ebx+force_disp32_zero]
    L_00414970:
        push esi
    L_00414971:
        call asm_FUN_0043ee30_0043ee30
    L_00414976:
        add esi,3ACh
    L_0041497c:
        dec ebx
    L_0041497d:
        jne short L_00414970
    L_0041497f:
        lea esi,[edi+793Ch]
    L_00414985:
        mov ebx,2
    L_0041498a:
        lea ebx,[ebx+force_disp32_zero]
    L_00414990:
        push esi
    L_00414991:
        call asm_FUN_0043ee30_0043ee30
    L_00414996:
        add esi,3ACh
    L_0041499c:
        dec ebx
    L_0041499d:
        jne short L_00414990
    L_0041499f:
        test byte ptr [edi+9EB4h],1
    L_004149a6:
        mov ecx,dword ptr [data_00477834]
    L_004149ac:
        TH10_REL8(0x75, 0x004149ac, VA_asm_target_00414a08)
    L_004149ae:
        test ecx,ecx
    L_004149b0:
        je asm_target_00414a5c
    L_004149b6:
        fld dword ptr [ecx+3C4h]
    L_004149bc:
        fcomp dword ptr [data_00470bdc]
    L_004149c2:
        fnstsw ax
    L_004149c4:
        test ah,41h
    L_004149c7:
        jne asm_target_00414a5c
    L_004149cd:
        fld dword ptr [ecx+3C0h]
    L_004149d3:
        fcomp qword ptr [data_00470d10]
    L_004149d9:
        fnstsw ax
    L_004149db:
        test ah,5
    L_004149de:
        TH10_REL8(0x7a, 0x004149de, VA_asm_target_00414a5c)
    L_004149e0:
        lea eax,[edi+8398h]
    L_004149e6:
        mov ecx,7
    L_004149eb:
        TH10_REL8(0xeb, 0x004149eb, VA_asm_FUN_00414900_part_004149f0)
    }
}

// 0x004149F0..0x00414C8C: FUN_00414900
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414900_part_004149f0() {
    __asm {
    L_004149f0:
        mov word ptr [eax],3
    L_004149f5:
        add eax,3ACh
    L_004149fa:
        dec ecx
    L_004149fb:
        jne short L_004149f0
    L_004149fd:
        mov eax,dword ptr [edi+9EB4h]
    L_00414a03:
        or eax,1
    L_00414a06:
        jmp short L_00414a56
    L_00414a08:
        test ecx,ecx
    L_00414a0a:
        je short L_00414a5c
    L_00414a0c:
        fld dword ptr [ecx+3C4h]
    L_00414a12:
        fcomp dword ptr [data_00470d08]
    L_00414a18:
        fnstsw ax
    L_00414a1a:
        test ah,5
    L_00414a1d:
        jnp short L_00414a32
    L_00414a1f:
        fld dword ptr [ecx+3C0h]
    L_00414a25:
        fcomp qword ptr [data_00470d00]
    L_00414a2b:
        fnstsw ax
    L_00414a2d:
        test ah,41h
    L_00414a30:
        jne short L_00414a5c
    L_00414a32:
        lea eax,[edi+8398h]
    L_00414a38:
        mov ecx,7
    L_00414a3d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00414a40:
        mov word ptr [eax],2
    L_00414a45:
        add eax,3ACh
    L_00414a4a:
        dec ecx
    L_00414a4b:
        jne short L_00414a40
    L_00414a4d:
        mov eax,dword ptr [edi+9EB4h]
    L_00414a53:
        and eax,0FFFFFFFEh
    L_00414a56:
        mov dword ptr [edi+9EB4h],eax
    L_00414a5c:
        mov edi,dword ptr [esp+18h]
    L_00414a60:
        mov ebp,dword ptr [data_00474c4c]
    L_00414a66:
        lea ecx,[edi+8094h]
    L_00414a6c:
        push ecx
    L_00414a6d:
        mov esi,2710h
    L_00414a72:
        call asm_FUN_0043ee30_0043ee30
    L_00414a77:
        add edi,8440h
    L_00414a7d:
        mov ebx,5
    L_00414a82:
        mov eax,ebp
    L_00414a84:
        cdq
    L_00414a85:
        idiv esi
    L_00414a87:
        mov ecx,dword ptr [esp+18h]
    L_00414a8b:
        mov ecx,dword ptr [ecx+9EC8h]
    L_00414a91:
        mov ebp,edx
    L_00414a93:
        lea edx,[eax+1Eh]
    L_00414a96:
        mov eax,edi
    L_00414a98:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00414a9d:
        mov eax,66666667h
    L_00414aa2:
        imul esi
    L_00414aa4:
        sar edx,2
    L_00414aa7:
        mov eax,edx
    L_00414aa9:
        shr eax,1Fh
    L_00414aac:
        add eax,edx
    L_00414aae:
        push edi
    L_00414aaf:
        mov esi,eax
    L_00414ab1:
        call asm_FUN_0043ee30_0043ee30
    L_00414ab6:
        add edi,3ACh
    L_00414abc:
        dec ebx
    L_00414abd:
        jne short L_00414a82
    L_00414abf:
        mov edi,dword ptr [esp+18h]
    L_00414ac3:
        lea ecx,[edi+969Ch]
    L_00414ac9:
        push ecx
    L_00414aca:
        call asm_FUN_0043ee30_0043ee30
    L_00414acf:
        mov eax,dword ptr [data_00477704]
    L_00414ad4:
        test eax,eax
    L_00414ad6:
        je asm_target_0041508c
    L_00414adc:
        mov eax,dword ptr [eax+10h]
    L_00414adf:
        test eax,eax
    L_00414ae1:
        je asm_target_0041508c
    L_00414ae7:
        mov ecx,dword ptr [edi+9EB8h]
    L_00414aed:
        test ecx,ecx
    L_00414aef:
        jne asm_target_0041508c
    L_00414af5:
        mov ecx,dword ptr [eax+23FCh]
    L_00414afb:
        mov dword ptr [esp+10h],ecx
    L_00414aff:
        fild dword ptr [esp+10h]
    L_00414b03:
        mov dword ptr [edi+9E8Ch],ecx
    L_00414b09:
        fidiv dword ptr [eax+2400h]
    L_00414b0f:
        fst dword ptr [edi+9E88h]
    L_00414b15:
        fcomp dword ptr [edi+9E84h]
    L_00414b1b:
        fnstsw ax
    L_00414b1d:
        test ah,41h
    L_00414b20:
        jne short L_00414b34
    L_00414b22:
        fld dword ptr [edi+9E84h]
    L_00414b28:
        fadd dword ptr [data_00470cf8]
    L_00414b2e:
        fstp dword ptr [edi+9E84h]
    L_00414b34:
        fld dword ptr [edi+9E84h]
    L_00414b3a:
        fcomp dword ptr [edi+9E88h]
    L_00414b40:
        fnstsw ax
    L_00414b42:
        test ah,41h
    L_00414b45:
        jne short L_00414b53
    L_00414b47:
        mov edx,dword ptr [edi+9E88h]
    L_00414b4d:
        mov dword ptr [edi+9E84h],edx
    L_00414b53:
        test byte ptr [edi+9EB4h],8
    L_00414b5a:
        mov ecx,dword ptr [data_00477834]
    L_00414b60:
        mov esi,dword ptr [data_00491c10]
    L_00414b66:
        fld dword ptr [ecx+3C4h]
    L_00414b6c:
        je asm_target_00414cae
    L_00414b72:
        fcomp dword ptr [data_00470c28]
    L_00414b78:
        fnstsw ax
    L_00414b7a:
        test ah,1
    L_00414b7d:
        je short L_00414b96
    L_00414b7f:
        fld dword ptr [ecx+3C0h]
    L_00414b85:
        fcomp dword ptr [data_00470b04]
    L_00414b8b:
        fnstsw ax
    L_00414b8d:
        test ah,41h
    L_00414b90:
        jne asm_target_00414def
    L_00414b96:
        mov eax,dword ptr [edi+9E90h]
    L_00414b9c:
        xor ebx,ebx
    L_00414b9e:
        test eax,eax
    L_00414ba0:
        jle short L_00414c1e
    L_00414ba2:
        lea edx,[edi+9E28h]
    L_00414ba8:
        mov ecx,dword ptr [edx]
    L_00414baa:
        test ecx,ecx
    L_00414bac:
        je short L_00414c10
    L_00414bae:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414bb4:
        test eax,eax
    L_00414bb6:
        je short L_00414bc6
    L_00414bb8:
        mov ebp,dword ptr [eax]
    L_00414bba:
        cmp dword ptr [ebp],ecx
    L_00414bbd:
        je short L_00414be0
    L_00414bbf:
        mov eax,dword ptr [eax+4]
    L_00414bc2:
        test eax,eax
    L_00414bc4:
        jne short L_00414bb8
    L_00414bc6:
        mov eax,dword ptr [esi+72DADCh]
    L_00414bcc:
        test eax,eax
    L_00414bce:
        je short L_00414c10
    L_00414bd0:
        mov ebp,dword ptr [eax]
    L_00414bd2:
        cmp dword ptr [ebp],ecx
    L_00414bd5:
        je short L_00414be0
    L_00414bd7:
        mov eax,dword ptr [eax+4]
    L_00414bda:
        test eax,eax
    L_00414bdc:
        jne short L_00414bd0
    L_00414bde:
        jmp short L_00414c10
    L_00414be0:
        mov eax,dword ptr [eax]
    L_00414be2:
        test eax,eax
    L_00414be4:
        je short L_00414c10
    L_00414be6:
        mov ebp,dword ptr [eax+18h]
    L_00414be9:
        test ebp,ebp
    L_00414beb:
        mov ecx,2
    L_00414bf0:
        mov word ptr [eax+304h],cx
    L_00414bf7:
        jne short L_00414c10
    L_00414bf9:
        mov eax,dword ptr [eax+14h]
    L_00414bfc:
        test eax,eax
    L_00414bfe:
        je short L_00414c10
    L_00414c00:
        mov ebp,dword ptr [eax]
    L_00414c02:
        mov word ptr [ebp+304h],cx
    L_00414c09:
        mov eax,dword ptr [eax+4]
    L_00414c0c:
        test eax,eax
    L_00414c0e:
        jne short L_00414c00
    L_00414c10:
        mov eax,dword ptr [edi+9E90h]
    L_00414c16:
        inc ebx
    L_00414c17:
        add edx,4
    L_00414c1a:
        cmp ebx,eax
    L_00414c1c:
        jl short L_00414ba8
    L_00414c1e:
        mov ecx,dword ptr [edi+9E24h]
    L_00414c24:
        test ecx,ecx
    L_00414c26:
        TH10_REL8(0x74, 0x00414c26, VA_asm_target_00414ca0)
    L_00414c28:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414c2e:
        test eax,eax
    L_00414c30:
        je short L_00414c3f
    L_00414c32:
        mov edx,dword ptr [eax]
    L_00414c34:
        cmp dword ptr [edx],ecx
    L_00414c36:
        je short L_00414c6b
    L_00414c38:
        mov eax,dword ptr [eax+4]
    L_00414c3b:
        test eax,eax
    L_00414c3d:
        jne short L_00414c32
    L_00414c3f:
        mov eax,dword ptr [esi+72DADCh]
    L_00414c45:
        test eax,eax
    L_00414c47:
        TH10_REL8(0x74, 0x00414c47, VA_asm_target_00414ca0)
    L_00414c49:
        lea esp,[esp+force_disp32_zero]
    L_00414c50:
        mov edx,dword ptr [eax]
    L_00414c52:
        cmp dword ptr [edx],ecx
    L_00414c54:
        je short L_00414c6b
    L_00414c56:
        mov eax,dword ptr [eax+4]
    L_00414c59:
        test eax,eax
    L_00414c5b:
        jne short L_00414c50
    L_00414c5d:
        mov eax,dword ptr [edi+9EB4h]
    L_00414c63:
        and eax,0FFFFFFF7h
    L_00414c66:
        jmp asm_target_00414de9
    L_00414c6b:
        mov eax,dword ptr [eax]
    L_00414c6d:
        test eax,eax
    L_00414c6f:
        TH10_REL8(0x74, 0x00414c6f, VA_asm_target_00414ca0)
    L_00414c71:
        mov edx,dword ptr [eax+18h]
    L_00414c74:
        test edx,edx
    L_00414c76:
        mov ecx,2
    L_00414c7b:
        mov word ptr [eax+304h],cx
    L_00414c82:
        TH10_REL8(0x75, 0x00414c82, VA_asm_target_00414ca0)
    L_00414c84:
        mov eax,dword ptr [eax+14h]
    L_00414c87:
        test eax,eax
    L_00414c89:
        TH10_REL8(0x74, 0x00414c89, VA_asm_target_00414ca0)
    L_00414c8b:
        TH10_REL8(0xeb, 0x00414c8b, VA_asm_FUN_00414900_part_00414c90)
    }
}

// 0x00414C90..0x00414D49: FUN_00414900
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414900_part_00414c90() {
    __asm {
    L_00414c90:
        mov edx,dword ptr [eax]
    L_00414c92:
        mov word ptr [edx+304h],cx
    L_00414c99:
        mov eax,dword ptr [eax+4]
    L_00414c9c:
        test eax,eax
    L_00414c9e:
        jne short L_00414c90
    L_00414ca0:
        mov eax,dword ptr [edi+9EB4h]
    L_00414ca6:
        and eax,0FFFFFFF7h
    L_00414ca9:
        jmp asm_target_00414de9
    L_00414cae:
        fcomp dword ptr [data_00470bc8]
    L_00414cb4:
        fnstsw ax
    L_00414cb6:
        test ah,41h
    L_00414cb9:
        jp asm_target_00414def
    L_00414cbf:
        fld dword ptr [ecx+3C0h]
    L_00414cc5:
        fcomp dword ptr [data_00470b5c]
    L_00414ccb:
        fnstsw ax
    L_00414ccd:
        test ah,5
    L_00414cd0:
        jp asm_target_00414def
    L_00414cd6:
        mov eax,dword ptr [edi+9E90h]
    L_00414cdc:
        xor ebx,ebx
    L_00414cde:
        test eax,eax
    L_00414ce0:
        jle asm_target_00414d6e
    L_00414ce6:
        lea edx,[edi+9E28h]
    L_00414cec:
        TH10_NOP_LEA_ESP_DISP8()
    L_00414cf0:
        mov ecx,dword ptr [edx]
    L_00414cf2:
        test ecx,ecx
    L_00414cf4:
        TH10_REL8(0x74, 0x00414cf4, VA_asm_target_00414d60)
    L_00414cf6:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414cfc:
        test eax,eax
    L_00414cfe:
        je short L_00414d0e
    L_00414d00:
        mov ebp,dword ptr [eax]
    L_00414d02:
        cmp dword ptr [ebp],ecx
    L_00414d05:
        je short L_00414d28
    L_00414d07:
        mov eax,dword ptr [eax+4]
    L_00414d0a:
        test eax,eax
    L_00414d0c:
        jne short L_00414d00
    L_00414d0e:
        mov eax,dword ptr [esi+72DADCh]
    L_00414d14:
        test eax,eax
    L_00414d16:
        TH10_REL8(0x74, 0x00414d16, VA_asm_target_00414d60)
    L_00414d18:
        mov ebp,dword ptr [eax]
    L_00414d1a:
        cmp dword ptr [ebp],ecx
    L_00414d1d:
        je short L_00414d28
    L_00414d1f:
        mov eax,dword ptr [eax+4]
    L_00414d22:
        test eax,eax
    L_00414d24:
        jne short L_00414d18
    L_00414d26:
        TH10_REL8(0xeb, 0x00414d26, VA_asm_target_00414d60)
    L_00414d28:
        mov eax,dword ptr [eax]
    L_00414d2a:
        test eax,eax
    L_00414d2c:
        TH10_REL8(0x74, 0x00414d2c, VA_asm_target_00414d60)
    L_00414d2e:
        mov ebp,dword ptr [eax+18h]
    L_00414d31:
        test ebp,ebp
    L_00414d33:
        mov ecx,3
    L_00414d38:
        mov word ptr [eax+304h],cx
    L_00414d3f:
        TH10_REL8(0x75, 0x00414d3f, VA_asm_target_00414d60)
    L_00414d41:
        mov eax,dword ptr [eax+14h]
    L_00414d44:
        test eax,eax
    L_00414d46:
        TH10_REL8(0x74, 0x00414d46, VA_asm_target_00414d60)
    L_00414d48:
        TH10_REL8(0xeb, 0x00414d48, VA_asm_FUN_00414900_part_00414d50)
    }
}

// 0x00414D50..0x00415059: FUN_00414900
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414900_part_00414d50() {
    __asm {
    L_00414d50:
        mov ebp,dword ptr [eax]
    L_00414d52:
        mov word ptr [ebp+304h],cx
    L_00414d59:
        mov eax,dword ptr [eax+4]
    L_00414d5c:
        test eax,eax
    L_00414d5e:
        jne short L_00414d50
    L_00414d60:
        mov eax,dword ptr [edi+9E90h]
    L_00414d66:
        inc ebx
    L_00414d67:
        add edx,4
    L_00414d6a:
        cmp ebx,eax
    L_00414d6c:
        TH10_REL8(0x7c, 0x00414d6c, VA_asm_target_00414cf0)
    L_00414d6e:
        mov ecx,dword ptr [edi+9E24h]
    L_00414d74:
        test ecx,ecx
    L_00414d76:
        je short L_00414de0
    L_00414d78:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414d7e:
        test eax,eax
    L_00414d80:
        je short L_00414d8f
    L_00414d82:
        mov edx,dword ptr [eax]
    L_00414d84:
        cmp dword ptr [edx],ecx
    L_00414d86:
        je short L_00414daf
    L_00414d88:
        mov eax,dword ptr [eax+4]
    L_00414d8b:
        test eax,eax
    L_00414d8d:
        jne short L_00414d82
    L_00414d8f:
        mov eax,dword ptr [esi+72DADCh]
    L_00414d95:
        test eax,eax
    L_00414d97:
        je short L_00414de0
    L_00414d99:
        lea esp,[esp+force_disp32_zero]
    L_00414da0:
        mov edx,dword ptr [eax]
    L_00414da2:
        cmp dword ptr [edx],ecx
    L_00414da4:
        je short L_00414daf
    L_00414da6:
        mov eax,dword ptr [eax+4]
    L_00414da9:
        test eax,eax
    L_00414dab:
        jne short L_00414da0
    L_00414dad:
        jmp short L_00414de0
    L_00414daf:
        mov eax,dword ptr [eax]
    L_00414db1:
        test eax,eax
    L_00414db3:
        je short L_00414de0
    L_00414db5:
        mov edx,dword ptr [eax+18h]
    L_00414db8:
        test edx,edx
    L_00414dba:
        mov ecx,3
    L_00414dbf:
        mov word ptr [eax+304h],cx
    L_00414dc6:
        jne short L_00414de0
    L_00414dc8:
        mov eax,dword ptr [eax+14h]
    L_00414dcb:
        test eax,eax
    L_00414dcd:
        je short L_00414de0
    L_00414dcf:
        nop
    L_00414dd0:
        mov edx,dword ptr [eax]
    L_00414dd2:
        mov word ptr [edx+304h],cx
    L_00414dd9:
        mov eax,dword ptr [eax+4]
    L_00414ddc:
        test eax,eax
    L_00414dde:
        jne short L_00414dd0
    L_00414de0:
        mov eax,dword ptr [edi+9EB4h]
    L_00414de6:
        or eax,8
    L_00414de9:
        mov dword ptr [edi+9EB4h],eax
    L_00414def:
        mov eax,dword ptr [edi+9E24h]
    L_00414df5:
        test eax,eax
    L_00414df7:
        jne asm_target_00414f33
    L_00414dfd:
        mov eax,dword ptr [data_00474c7c]
    L_00414e02:
        dec eax
    L_00414e03:
        cmp eax,6
    L_00414e06:
        mov ebp,85h
    L_00414e0b:
        ja short L_00414e87
    L_00414e0d:
        jmp dword ptr [eax*4+4157E0h]
    L_00414e14:
        cmp dword ptr [data_00474c84],18h
    L_00414e1b:
        jl short L_00414e87
    L_00414e1d:
        mov ebp,86h
    L_00414e22:
        jmp short L_00414e87
    L_00414e24:
        cmp dword ptr [data_00474c84],18h
    L_00414e2b:
        jl asm_target_00414f33
    L_00414e31:
        mov ebp,87h
    L_00414e36:
        jmp short L_00414e87
    L_00414e38:
        cmp dword ptr [data_00474c84],18h
    L_00414e3f:
        jl asm_target_00414f33
    L_00414e45:
        mov ebp,88h
    L_00414e4a:
        jmp short L_00414e87
    L_00414e4c:
        mov edx,dword ptr [data_00474c84]
    L_00414e52:
        xor eax,eax
    L_00414e54:
        cmp edx,18h
    L_00414e57:
        setge al
    L_00414e5a:
        add eax,89h
    L_00414e5f:
        mov ebp,eax
    L_00414e61:
        jmp short L_00414e87
    L_00414e63:
        mov ebp,8Bh
    L_00414e68:
        jmp short L_00414e87
    L_00414e6a:
        mov ebp,8Ch
    L_00414e6f:
        jmp short L_00414e87
    L_00414e71:
        mov edx,dword ptr [data_00474c84]
    L_00414e77:
        xor ecx,ecx
    L_00414e79:
        cmp edx,18h
    L_00414e7c:
        setge cl
    L_00414e7f:
        add ecx,8Ch
    L_00414e85:
        mov ebp,ecx
    L_00414e87:
        mov edx,dword ptr [esp+18h]
    L_00414e8b:
        mov ebx,dword ptr [edx+9EC8h]
    L_00414e91:
        call asm_FUN_00449950_00449950
    L_00414e96:
        mov edi,eax
    L_00414e98:
        mov ecx,dword ptr [edi+35Ch]
    L_00414e9e:
        or ecx,40000000h
    L_00414ea4:
        push ebp
    L_00414ea5:
        mov dword ptr [edi+35Ch],ecx
    L_00414eab:
        push edi
    L_00414eac:
        mov ecx,ebx
    L_00414eae:
        mov dword ptr [edi+20h],0Fh
    L_00414eb5:
        call asm_FUN_00449870_00449870
    L_00414eba:
        mov esi,dword ptr [data_00491c10]
    L_00414ec0:
        lea eax,[edi+4]
    L_00414ec3:
        xor ecx,ecx
    L_00414ec5:
        mov dword ptr [eax],edi
    L_00414ec7:
        mov dword ptr [eax+4],ecx
    L_00414eca:
        mov dword ptr [eax+8],ecx
    L_00414ecd:
        cmp dword ptr [esi+72DAD4h],ecx
    L_00414ed3:
        jne short L_00414edd
    L_00414ed5:
        mov dword ptr [esi+72DAD4h],eax
    L_00414edb:
        jmp short L_00414ef9
    L_00414edd:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00414ee3:
        mov edx,dword ptr [ecx+4]
    L_00414ee6:
        test edx,edx
    L_00414ee8:
        je short L_00414ef3
    L_00414eea:
        mov dword ptr [eax+4],edx
    L_00414eed:
        mov edx,dword ptr [ecx+4]
    L_00414ef0:
        mov dword ptr [edx+8],eax
    L_00414ef3:
        mov dword ptr [ecx+4],eax
    L_00414ef6:
        mov dword ptr [eax+8],ecx
    L_00414ef9:
        mov dword ptr [esi+72DAD8h],eax
    L_00414eff:
        mov ecx,dword ptr [esi+732454h]
    L_00414f05:
        inc ecx
    L_00414f06:
        mov eax,ecx
    L_00414f08:
        test eax,eax
    L_00414f0a:
        mov dword ptr [esi+732454h],ecx
    L_00414f10:
        jne short L_00414f19
    L_00414f12:
        inc eax
    L_00414f13:
        mov dword ptr [esi+732454h],eax
    L_00414f19:
        mov eax,dword ptr [esi+732454h]
    L_00414f1f:
        mov edx,dword ptr [esp+18h]
    L_00414f23:
        mov dword ptr [edi],eax
    L_00414f25:
        mov ecx,dword ptr [esi+732454h]
    L_00414f2b:
        mov dword ptr [edx+9E24h],ecx
    L_00414f31:
        mov edi,edx
    L_00414f33:
        lea edx,[edi+9E28h]
    L_00414f39:
        xor ebx,ebx
    L_00414f3b:
        mov dword ptr [esp+10h],edx
    L_00414f3f:
        nop
    L_00414f40:
        cmp ebx,dword ptr [edi+9E90h]
    L_00414f46:
        jge asm_target_00414ffc
    L_00414f4c:
        cmp dword ptr [edx],0
    L_00414f4f:
        jne asm_target_00415076
    L_00414f55:
        mov eax,dword ptr [esp+18h]
    L_00414f59:
        mov ebp,dword ptr [eax+9EC8h]
    L_00414f5f:
        call asm_FUN_00449950_00449950
    L_00414f64:
        mov edi,eax
    L_00414f66:
        or dword ptr [edi+35Ch],40000000h
    L_00414f70:
        lea ecx,[ebx+5Bh]
    L_00414f73:
        push ecx
    L_00414f74:
        push edi
    L_00414f75:
        mov ecx,ebp
    L_00414f77:
        mov dword ptr [edi+20h],0Fh
    L_00414f7e:
        call asm_FUN_00449870_00449870
    L_00414f83:
        mov esi,dword ptr [data_00491c10]
    L_00414f89:
        lea eax,[edi+4]
    L_00414f8c:
        xor ecx,ecx
    L_00414f8e:
        mov dword ptr [eax],edi
    L_00414f90:
        mov dword ptr [eax+4],ecx
    L_00414f93:
        mov dword ptr [eax+8],ecx
    L_00414f96:
        cmp dword ptr [esi+72DAD4h],ecx
    L_00414f9c:
        jne short L_00414fa6
    L_00414f9e:
        mov dword ptr [esi+72DAD4h],eax
    L_00414fa4:
        jmp short L_00414fc2
    L_00414fa6:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00414fac:
        mov edx,dword ptr [ecx+4]
    L_00414faf:
        test edx,edx
    L_00414fb1:
        je short L_00414fbc
    L_00414fb3:
        mov dword ptr [eax+4],edx
    L_00414fb6:
        mov edx,dword ptr [ecx+4]
    L_00414fb9:
        mov dword ptr [edx+8],eax
    L_00414fbc:
        mov dword ptr [ecx+4],eax
    L_00414fbf:
        mov dword ptr [eax+8],ecx
    L_00414fc2:
        mov dword ptr [esi+72DAD8h],eax
    L_00414fc8:
        mov ecx,dword ptr [esi+732454h]
    L_00414fce:
        inc ecx
    L_00414fcf:
        mov eax,ecx
    L_00414fd1:
        test eax,eax
    L_00414fd3:
        mov dword ptr [esi+732454h],ecx
    L_00414fd9:
        jne short L_00414fe2
    L_00414fdb:
        inc eax
    L_00414fdc:
        mov dword ptr [esi+732454h],eax
    L_00414fe2:
        mov eax,dword ptr [esi+732454h]
    L_00414fe8:
        mov edx,dword ptr [esp+10h]
    L_00414fec:
        mov dword ptr [edi],eax
    L_00414fee:
        mov ecx,dword ptr [esi+732454h]
    L_00414ff4:
        mov edi,dword ptr [esp+18h]
    L_00414ff8:
        mov dword ptr [edx],ecx
    L_00414ffa:
        TH10_REL8(0xeb, 0x00414ffa, VA_asm_target_00415076)
    L_00414ffc:
        mov ecx,dword ptr [edx]
    L_00414ffe:
        test ecx,ecx
    L_00415000:
        TH10_REL8(0x74, 0x00415000, VA_asm_target_00415076)
    L_00415002:
        mov eax,dword ptr [esi+72DAD4h]
    L_00415008:
        test eax,eax
    L_0041500a:
        je short L_0041501e
    L_0041500c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00415010:
        mov ebp,dword ptr [eax]
    L_00415012:
        cmp dword ptr [ebp],ecx
    L_00415015:
        je short L_00415038
    L_00415017:
        mov eax,dword ptr [eax+4]
    L_0041501a:
        test eax,eax
    L_0041501c:
        jne short L_00415010
    L_0041501e:
        mov eax,dword ptr [esi+72DADCh]
    L_00415024:
        test eax,eax
    L_00415026:
        TH10_REL8(0x74, 0x00415026, VA_asm_target_00415070)
    L_00415028:
        mov ebp,dword ptr [eax]
    L_0041502a:
        cmp dword ptr [ebp],ecx
    L_0041502d:
        je short L_00415038
    L_0041502f:
        mov eax,dword ptr [eax+4]
    L_00415032:
        test eax,eax
    L_00415034:
        jne short L_00415028
    L_00415036:
        TH10_REL8(0xeb, 0x00415036, VA_asm_target_00415070)
    L_00415038:
        mov eax,dword ptr [eax]
    L_0041503a:
        test eax,eax
    L_0041503c:
        TH10_REL8(0x74, 0x0041503c, VA_asm_target_00415070)
    L_0041503e:
        mov ebp,dword ptr [eax+18h]
    L_00415041:
        test ebp,ebp
    L_00415043:
        mov ecx,1
    L_00415048:
        mov word ptr [eax+304h],cx
    L_0041504f:
        TH10_REL8(0x75, 0x0041504f, VA_asm_target_00415070)
    L_00415051:
        mov eax,dword ptr [eax+14h]
    L_00415054:
        test eax,eax
    L_00415056:
        TH10_REL8(0x74, 0x00415056, VA_asm_target_00415070)
    L_00415058:
        TH10_REL8(0xeb, 0x00415058, VA_asm_FUN_00414900_part_00415060)
    }
}

// 0x00415060..0x004157DC: FUN_00414900
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414900_part_00415060() {
    __asm {
    L_00415060:
        mov ebp,dword ptr [eax]
    L_00415062:
        mov word ptr [ebp+304h],cx
    L_00415069:
        mov eax,dword ptr [eax+4]
    L_0041506c:
        test eax,eax
    L_0041506e:
        jne short L_00415060
    L_00415070:
        mov dword ptr [edx],0
    L_00415076:
        inc ebx
    L_00415077:
        add edx,4
    L_0041507a:
        cmp ebx,0Ah
    L_0041507d:
        mov dword ptr [esp+10h],edx
    L_00415081:
        jb asm_target_00414f40
    L_00415087:
        jmp asm_target_0041513c
    L_0041508c:
        mov ecx,dword ptr [edi+9E24h]
    L_00415092:
        test ecx,ecx
    L_00415094:
        je short L_0041510a
    L_00415096:
        mov edx,dword ptr [data_00491c10]
    L_0041509c:
        mov eax,dword ptr [edx+72DAD4h]
    L_004150a2:
        test eax,eax
    L_004150a4:
        je short L_004150b3
    L_004150a6:
        mov esi,dword ptr [eax]
    L_004150a8:
        cmp dword ptr [esi],ecx
    L_004150aa:
        je short L_004150cf
    L_004150ac:
        mov eax,dword ptr [eax+4]
    L_004150af:
        test eax,eax
    L_004150b1:
        jne short L_004150a6
    L_004150b3:
        mov eax,dword ptr [edx+72DADCh]
    L_004150b9:
        test eax,eax
    L_004150bb:
        je short L_00415100
    L_004150bd:
        TH10_NOP_LEA_ECX_DISP8()
    L_004150c0:
        mov edx,dword ptr [eax]
    L_004150c2:
        cmp dword ptr [edx],ecx
    L_004150c4:
        je short L_004150cf
    L_004150c6:
        mov eax,dword ptr [eax+4]
    L_004150c9:
        test eax,eax
    L_004150cb:
        jne short L_004150c0
    L_004150cd:
        jmp short L_00415100
    L_004150cf:
        mov eax,dword ptr [eax]
    L_004150d1:
        test eax,eax
    L_004150d3:
        je short L_00415100
    L_004150d5:
        mov edx,dword ptr [eax+18h]
    L_004150d8:
        test edx,edx
    L_004150da:
        mov ecx,1
    L_004150df:
        mov word ptr [eax+304h],cx
    L_004150e6:
        jne short L_00415100
    L_004150e8:
        mov eax,dword ptr [eax+14h]
    L_004150eb:
        test eax,eax
    L_004150ed:
        je short L_00415100
    L_004150ef:
        nop
    L_004150f0:
        mov edx,dword ptr [eax]
    L_004150f2:
        mov word ptr [edx+304h],cx
    L_004150f9:
        mov eax,dword ptr [eax+4]
    L_004150fc:
        test eax,eax
    L_004150fe:
        jne short L_004150f0
    L_00415100:
        mov dword ptr [edi+9E24h],0
    L_0041510a:
        mov dword ptr [edi+9E84h],0
    L_00415114:
        mov dword ptr [edi+9E94h],0
    L_0041511e:
        mov dword ptr [edi+9E9Ch],0
    L_00415128:
        mov dword ptr [edi+9EA4h],0
    L_00415132:
        mov dword ptr [edi+9EACh],0
    L_0041513c:
        mov esi,dword ptr [edi+9EB8h]
    L_00415142:
        test esi,esi
    L_00415144:
        je asm_target_0041549a
    L_0041514a:
        push esi
    L_0041514b:
        call asm_FUN_00415e90_00415e90
    L_00415150:
        test eax,eax
    L_00415152:
        jne short L_004151a5
    L_00415154:
        mov edx,dword ptr [esi+8]
    L_00415157:
        mov ecx,dword ptr [esi+10h]
    L_0041515a:
        mov dword ptr [esi+4],edx
    L_0041515d:
        fld dword ptr [ecx]
    L_0041515f:
        fcomp dword ptr [data_00470b68]
    L_00415165:
        fnstsw ax
    L_00415167:
        test ah,41h
    L_0041516a:
        jne short L_00415190
    L_0041516c:
        fld dword ptr [ecx]
    L_0041516e:
        fcomp dword ptr [data_00470b64]
    L_00415174:
        fnstsw ax
    L_00415176:
        test ah,5
    L_00415179:
        jp short L_00415190
    L_0041517b:
        fld dword ptr [esi+0Ch]
    L_0041517e:
        inc edx
    L_0041517f:
        fadd dword ptr [data_00470afc]
    L_00415185:
        mov dword ptr [esi+8],edx
    L_00415188:
        fstp dword ptr [esi+0Ch]
    L_0041518b:
        jmp asm_target_0041549a
    L_00415190:
        fld dword ptr [ecx]
    L_00415192:
        fadd dword ptr [esi+0Ch]
    L_00415195:
        fst dword ptr [esi+0Ch]
    L_00415198:
        call asm_FUN_00463b2c_00463b2c
    L_0041519d:
        mov dword ptr [esi+8],eax
    L_004151a0:
        jmp asm_target_0041549a
    L_004151a5:
        mov ebx,dword ptr [edi+9EB8h]
    L_004151ab:
        test ebx,ebx
    L_004151ad:
        je asm_target_00415490
    L_004151b3:
        mov ecx,dword ptr [ebx+40h]
    L_004151b6:
        test ecx,ecx
    L_004151b8:
        mov edx,dword ptr [data_00491c10]
    L_004151be:
        mov esi,4000000h
    L_004151c3:
        je short L_0041522f
    L_004151c5:
        mov eax,dword ptr [edx+72DAD4h]
    L_004151cb:
        test eax,eax
    L_004151cd:
        je short L_004151de
    L_004151cf:
        nop
    L_004151d0:
        mov ebp,dword ptr [eax]
    L_004151d2:
        cmp dword ptr [ebp],ecx
    L_004151d5:
        je short L_004151f8
    L_004151d7:
        mov eax,dword ptr [eax+4]
    L_004151da:
        test eax,eax
    L_004151dc:
        jne short L_004151d0
    L_004151de:
        mov eax,dword ptr [edx+72DADCh]
    L_004151e4:
        test eax,eax
    L_004151e6:
        je short L_0041522f
    L_004151e8:
        mov ebp,dword ptr [eax]
    L_004151ea:
        cmp dword ptr [ebp],ecx
    L_004151ed:
        je short L_004151f8
    L_004151ef:
        mov eax,dword ptr [eax+4]
    L_004151f2:
        test eax,eax
    L_004151f4:
        jne short L_004151e8
    L_004151f6:
        jmp short L_0041522f
    L_004151f8:
        mov eax,dword ptr [eax]
    L_004151fa:
        test eax,eax
    L_004151fc:
        je short L_0041522f
    L_004151fe:
        mov ebp,dword ptr [eax+35Ch]
    L_00415204:
        mov ecx,dword ptr [eax+18h]
    L_00415207:
        or ebp,esi
    L_00415209:
        test ecx,ecx
    L_0041520b:
        mov dword ptr [eax+35Ch],ebp
    L_00415211:
        jne short L_0041522f
    L_00415213:
        mov eax,dword ptr [eax+14h]
    L_00415216:
        test eax,eax
    L_00415218:
        je short L_0041522f
    L_0041521a:
        lea ebx,[ebx+force_disp32_zero]
    L_00415220:
        mov ecx,dword ptr [eax]
    L_00415222:
        or dword ptr [ecx+35Ch],esi
    L_00415228:
        mov eax,dword ptr [eax+4]
    L_0041522b:
        test eax,eax
    L_0041522d:
        jne short L_00415220
    L_0041522f:
        mov dword ptr [ebx+40h],0
    L_00415236:
        mov ecx,dword ptr [ebx+44h]
    L_00415239:
        test ecx,ecx
    L_0041523b:
        je short L_004152a1
    L_0041523d:
        mov eax,dword ptr [edx+72DAD4h]
    L_00415243:
        test eax,eax
    L_00415245:
        je short L_00415255
    L_00415247:
        mov ebp,dword ptr [eax]
    L_00415249:
        cmp dword ptr [ebp],ecx
    L_0041524c:
        je short L_00415270
    L_0041524e:
        mov eax,dword ptr [eax+4]
    L_00415251:
        test eax,eax
    L_00415253:
        jne short L_00415247
    L_00415255:
        mov eax,dword ptr [edx+72DADCh]
    L_0041525b:
        test eax,eax
    L_0041525d:
        je short L_004152a1
    L_0041525f:
        nop
    L_00415260:
        mov ebp,dword ptr [eax]
    L_00415262:
        cmp dword ptr [ebp],ecx
    L_00415265:
        je short L_00415270
    L_00415267:
        mov eax,dword ptr [eax+4]
    L_0041526a:
        test eax,eax
    L_0041526c:
        jne short L_00415260
    L_0041526e:
        jmp short L_004152a1
    L_00415270:
        mov eax,dword ptr [eax]
    L_00415272:
        test eax,eax
    L_00415274:
        je short L_004152a1
    L_00415276:
        mov ebp,dword ptr [eax+35Ch]
    L_0041527c:
        mov ecx,dword ptr [eax+18h]
    L_0041527f:
        or ebp,esi
    L_00415281:
        test ecx,ecx
    L_00415283:
        mov dword ptr [eax+35Ch],ebp
    L_00415289:
        jne short L_004152a1
    L_0041528b:
        mov eax,dword ptr [eax+14h]
    L_0041528e:
        test eax,eax
    L_00415290:
        je short L_004152a1
    L_00415292:
        mov ecx,dword ptr [eax]
    L_00415294:
        or dword ptr [ecx+35Ch],esi
    L_0041529a:
        mov eax,dword ptr [eax+4]
    L_0041529d:
        test eax,eax
    L_0041529f:
        jne short L_00415292
    L_004152a1:
        mov dword ptr [ebx+44h],0
    L_004152a8:
        mov ecx,dword ptr [ebx+48h]
    L_004152ab:
        test ecx,ecx
    L_004152ad:
        je short L_0041531f
    L_004152af:
        mov eax,dword ptr [edx+72DAD4h]
    L_004152b5:
        test eax,eax
    L_004152b7:
        je short L_004152ce
    L_004152b9:
        lea esp,[esp+force_disp32_zero]
    L_004152c0:
        mov ebp,dword ptr [eax]
    L_004152c2:
        cmp dword ptr [ebp],ecx
    L_004152c5:
        je short L_004152e8
    L_004152c7:
        mov eax,dword ptr [eax+4]
    L_004152ca:
        test eax,eax
    L_004152cc:
        jne short L_004152c0
    L_004152ce:
        mov eax,dword ptr [edx+72DADCh]
    L_004152d4:
        test eax,eax
    L_004152d6:
        je short L_0041531f
    L_004152d8:
        mov ebp,dword ptr [eax]
    L_004152da:
        cmp dword ptr [ebp],ecx
    L_004152dd:
        je short L_004152e8
    L_004152df:
        mov eax,dword ptr [eax+4]
    L_004152e2:
        test eax,eax
    L_004152e4:
        jne short L_004152d8
    L_004152e6:
        jmp short L_0041531f
    L_004152e8:
        mov eax,dword ptr [eax]
    L_004152ea:
        test eax,eax
    L_004152ec:
        je short L_0041531f
    L_004152ee:
        mov ebp,dword ptr [eax+35Ch]
    L_004152f4:
        mov ecx,dword ptr [eax+18h]
    L_004152f7:
        or ebp,esi
    L_004152f9:
        test ecx,ecx
    L_004152fb:
        mov dword ptr [eax+35Ch],ebp
    L_00415301:
        jne short L_0041531f
    L_00415303:
        mov eax,dword ptr [eax+14h]
    L_00415306:
        test eax,eax
    L_00415308:
        je short L_0041531f
    L_0041530a:
        lea ebx,[ebx+force_disp32_zero]
    L_00415310:
        mov ecx,dword ptr [eax]
    L_00415312:
        or dword ptr [ecx+35Ch],esi
    L_00415318:
        mov eax,dword ptr [eax+4]
    L_0041531b:
        test eax,eax
    L_0041531d:
        jne short L_00415310
    L_0041531f:
        mov dword ptr [ebx+48h],0
    L_00415326:
        mov ecx,dword ptr [ebx+4Ch]
    L_00415329:
        test ecx,ecx
    L_0041532b:
        je short L_00415391
    L_0041532d:
        mov eax,dword ptr [edx+72DAD4h]
    L_00415333:
        test eax,eax
    L_00415335:
        je short L_00415345
    L_00415337:
        mov ebp,dword ptr [eax]
    L_00415339:
        cmp dword ptr [ebp],ecx
    L_0041533c:
        je short L_00415360
    L_0041533e:
        mov eax,dword ptr [eax+4]
    L_00415341:
        test eax,eax
    L_00415343:
        jne short L_00415337
    L_00415345:
        mov eax,dword ptr [edx+72DADCh]
    L_0041534b:
        test eax,eax
    L_0041534d:
        je short L_00415391
    L_0041534f:
        nop
    L_00415350:
        mov ebp,dword ptr [eax]
    L_00415352:
        cmp dword ptr [ebp],ecx
    L_00415355:
        je short L_00415360
    L_00415357:
        mov eax,dword ptr [eax+4]
    L_0041535a:
        test eax,eax
    L_0041535c:
        jne short L_00415350
    L_0041535e:
        jmp short L_00415391
    L_00415360:
        mov eax,dword ptr [eax]
    L_00415362:
        test eax,eax
    L_00415364:
        je short L_00415391
    L_00415366:
        mov ebp,dword ptr [eax+35Ch]
    L_0041536c:
        mov ecx,dword ptr [eax+18h]
    L_0041536f:
        or ebp,esi
    L_00415371:
        test ecx,ecx
    L_00415373:
        mov dword ptr [eax+35Ch],ebp
    L_00415379:
        jne short L_00415391
    L_0041537b:
        mov eax,dword ptr [eax+14h]
    L_0041537e:
        test eax,eax
    L_00415380:
        je short L_00415391
    L_00415382:
        mov ecx,dword ptr [eax]
    L_00415384:
        or dword ptr [ecx+35Ch],esi
    L_0041538a:
        mov eax,dword ptr [eax+4]
    L_0041538d:
        test eax,eax
    L_0041538f:
        jne short L_00415382
    L_00415391:
        mov dword ptr [ebx+4Ch],0
    L_00415398:
        mov ecx,dword ptr [ebx+50h]
    L_0041539b:
        test ecx,ecx
    L_0041539d:
        je short L_0041540f
    L_0041539f:
        mov eax,dword ptr [edx+72DAD4h]
    L_004153a5:
        test eax,eax
    L_004153a7:
        je short L_004153be
    L_004153a9:
        lea esp,[esp+force_disp32_zero]
    L_004153b0:
        mov ebp,dword ptr [eax]
    L_004153b2:
        cmp dword ptr [ebp],ecx
    L_004153b5:
        je short L_004153d8
    L_004153b7:
        mov eax,dword ptr [eax+4]
    L_004153ba:
        test eax,eax
    L_004153bc:
        jne short L_004153b0
    L_004153be:
        mov eax,dword ptr [edx+72DADCh]
    L_004153c4:
        test eax,eax
    L_004153c6:
        je short L_0041540f
    L_004153c8:
        mov ebp,dword ptr [eax]
    L_004153ca:
        cmp dword ptr [ebp],ecx
    L_004153cd:
        je short L_004153d8
    L_004153cf:
        mov eax,dword ptr [eax+4]
    L_004153d2:
        test eax,eax
    L_004153d4:
        jne short L_004153c8
    L_004153d6:
        jmp short L_0041540f
    L_004153d8:
        mov eax,dword ptr [eax]
    L_004153da:
        test eax,eax
    L_004153dc:
        je short L_0041540f
    L_004153de:
        mov ebp,dword ptr [eax+35Ch]
    L_004153e4:
        mov ecx,dword ptr [eax+18h]
    L_004153e7:
        or ebp,esi
    L_004153e9:
        test ecx,ecx
    L_004153eb:
        mov dword ptr [eax+35Ch],ebp
    L_004153f1:
        jne short L_0041540f
    L_004153f3:
        mov eax,dword ptr [eax+14h]
    L_004153f6:
        test eax,eax
    L_004153f8:
        je short L_0041540f
    L_004153fa:
        lea ebx,[ebx+force_disp32_zero]
    L_00415400:
        mov ecx,dword ptr [eax]
    L_00415402:
        or dword ptr [ecx+35Ch],esi
    L_00415408:
        mov eax,dword ptr [eax+4]
    L_0041540b:
        test eax,eax
    L_0041540d:
        jne short L_00415400
    L_0041540f:
        mov dword ptr [ebx+50h],0
    L_00415416:
        mov ecx,dword ptr [ebx+54h]
    L_00415419:
        test ecx,ecx
    L_0041541b:
        je short L_00415480
    L_0041541d:
        mov eax,dword ptr [edx+72DAD4h]
    L_00415423:
        test eax,eax
    L_00415425:
        je short L_00415435
    L_00415427:
        mov ebp,dword ptr [eax]
    L_00415429:
        cmp dword ptr [ebp],ecx
    L_0041542c:
        je short L_0041544f
    L_0041542e:
        mov eax,dword ptr [eax+4]
    L_00415431:
        test eax,eax
    L_00415433:
        jne short L_00415427
    L_00415435:
        mov eax,dword ptr [edx+72DADCh]
    L_0041543b:
        test eax,eax
    L_0041543d:
        je short L_00415480
    L_0041543f:
        nop
    L_00415440:
        mov edx,dword ptr [eax]
    L_00415442:
        cmp dword ptr [edx],ecx
    L_00415444:
        je short L_0041544f
    L_00415446:
        mov eax,dword ptr [eax+4]
    L_00415449:
        test eax,eax
    L_0041544b:
        jne short L_00415440
    L_0041544d:
        jmp short L_00415480
    L_0041544f:
        mov eax,dword ptr [eax]
    L_00415451:
        test eax,eax
    L_00415453:
        je short L_00415480
    L_00415455:
        mov edx,dword ptr [eax+35Ch]
    L_0041545b:
        mov ecx,dword ptr [eax+18h]
    L_0041545e:
        or edx,esi
    L_00415460:
        test ecx,ecx
    L_00415462:
        mov dword ptr [eax+35Ch],edx
    L_00415468:
        jne short L_00415480
    L_0041546a:
        mov eax,dword ptr [eax+14h]
    L_0041546d:
        test eax,eax
    L_0041546f:
        je short L_00415480
    L_00415471:
        mov ecx,dword ptr [eax]
    L_00415473:
        or dword ptr [ecx+35Ch],esi
    L_00415479:
        mov eax,dword ptr [eax+4]
    L_0041547c:
        test eax,eax
    L_0041547e:
        jne short L_00415471
    L_00415480:
        push ebx
    L_00415481:
        mov dword ptr [ebx+54h],0
    L_00415488:
        call asm_free_004524a1
    L_0041548d:
        add esp,4
    L_00415490:
        mov dword ptr [edi+9EB8h],0
    L_0041549a:
        mov ecx,dword ptr [data_00477704]
    L_004154a0:
        test ecx,ecx
    L_004154a2:
        je asm_target_00415764
    L_004154a8:
        mov eax,dword ptr [edi+9EC0h]
    L_004154ae:
        test eax,eax
    L_004154b0:
        jl asm_target_004155ba
    L_004154b6:
        mov edx,dword ptr [ecx+10h]
    L_004154b9:
        test edx,edx
    L_004154bb:
        je asm_target_004155ba
    L_004154c1:
        mov edx,dword ptr [edi+9EB8h]
    L_004154c7:
        test edx,edx
    L_004154c9:
        jne asm_target_004155ba
    L_004154cf:
        mov ecx,dword ptr [edi+9EC4h]
    L_004154d5:
        cmp eax,ecx
    L_004154d7:
        jge short L_0041553f
    L_004154d9:
        cmp eax,5
    L_004154dc:
        jg short L_0041550c
    L_004154de:
        mov eax,dword ptr [esp+18h]
    L_004154e2:
        mov ecx,9
    L_004154e7:
        mov word ptr [eax+7C40h],cx
    L_004154ee:
        mov word ptr [eax+7FECh],cx
    L_004154f5:
        push 0
    L_004154f7:
        mov edi,24h
    L_004154fc:
        mov ecx,492590h
    L_00415501:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00415506:
        mov edi,dword ptr [esp+18h]
    L_0041550a:
        jmp short L_00415554
    L_0041550c:
        cmp eax,0Ah
    L_0041550f:
        jg short L_00415554
    L_00415511:
        mov eax,dword ptr [esp+18h]
    L_00415515:
        mov ecx,8
    L_0041551a:
        mov word ptr [eax+7C40h],cx
    L_00415521:
        mov word ptr [eax+7FECh],cx
    L_00415528:
        push 0
    L_0041552a:
        mov edi,1Bh
    L_0041552f:
        mov ecx,492590h
    L_00415534:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00415539:
        mov edi,dword ptr [esp+18h]
    L_0041553d:
        jmp short L_00415554
    L_0041553f:
        jle short L_00415554
    L_00415541:
        mov eax,7
    L_00415546:
        mov word ptr [edi+7C40h],ax
    L_0041554d:
        mov word ptr [edi+7FECh],ax
    L_00415554:
        mov ecx,dword ptr [edi+9EC0h]
    L_0041555a:
        cmp ecx,dword ptr [edi+9EC4h]
    L_00415560:
        je short L_004155a8
    L_00415562:
        mov eax,66666667h
    L_00415567:
        imul ecx
    L_00415569:
        mov ecx,dword ptr [edi+9EC8h]
    L_0041556f:
        sar edx,2
    L_00415572:
        mov eax,edx
    L_00415574:
        shr eax,1Fh
    L_00415577:
        lea edx,[edx+eax+8]
    L_0041557b:
        lea eax,[edi+793Ch]
    L_00415581:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00415586:
        mov eax,dword ptr [edi+9EC0h]
    L_0041558c:
        cdq
    L_0041558d:
        mov ecx,0Ah
    L_00415592:
        idiv ecx
    L_00415594:
        mov ecx,dword ptr [edi+9EC8h]
    L_0041559a:
        lea eax,[edi+7CE8h]
    L_004155a0:
        add edx,8
    L_004155a3:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004155a8:
        mov edx,dword ptr [edi+9EC0h]
    L_004155ae:
        mov ecx,dword ptr [data_00477704]
    L_004155b4:
        mov dword ptr [edi+9EC4h],edx
    L_004155ba:
        mov esi,dword ptr [ecx+10h]
    L_004155bd:
        test esi,esi
    L_004155bf:
        je asm_target_00415764
    L_004155c5:
        mov eax,dword ptr [esi+2480h]
    L_004155cb:
        mov ecx,eax
    L_004155cd:
        shr ecx,4
    L_004155d0:
        not ecx
    L_004155d2:
        test cl,1
    L_004155d5:
        je asm_target_00415764
    L_004155db:
        not eax
    L_004155dd:
        test al,1
    L_004155df:
        je asm_target_00415764
    L_004155e5:
        mov edx,dword ptr [data_004776f4]
    L_004155eb:
        test byte ptr [edx+378Ch],1
    L_004155f2:
        mov eax,dword ptr [edi+9EB4h]
    L_004155f8:
        mov ecx,eax
    L_004155fa:
        je short L_00415646
    L_004155fc:
        shr ecx,1
    L_004155fe:
        and ecx,3
    L_00415601:
        jne short L_0041560f
    L_00415603:
        cmp dword ptr [esi+2404h],7D0h
    L_0041560d:
        jmp short L_00415657
    L_0041560f:
        cmp ecx,1
    L_00415612:
        jne short L_00415620
    L_00415614:
        cmp dword ptr [esi+2404h],3E8h
    L_0041561e:
        jmp short L_00415679
    L_00415620:
        cmp ecx,2
    L_00415623:
        jne short L_00415631
    L_00415625:
        cmp dword ptr [esi+2404h],190h
    L_0041562f:
        jmp short L_0041569b
    L_00415631:
        cmp ecx,3
    L_00415634:
        jne asm_target_004156ce
    L_0041563a:
        cmp dword ptr [esi+2404h],190h
    L_00415644:
        jmp short L_004156ba
    L_00415646:
        shr ecx,1
    L_00415648:
        and ecx,3
    L_0041564b:
        jne short L_0041566a
    L_0041564d:
        cmp dword ptr [esi+2404h],2BCh
    L_00415657:
        jge short L_004156ce
    L_00415659:
        and eax,0FFFFFFFBh
    L_0041565c:
        mov word ptr [edi+9D4Ch],7
    L_00415665:
        or eax,2
    L_00415668:
        jmp short L_004156c8
    L_0041566a:
        cmp ecx,1
    L_0041566d:
        jne short L_0041568c
    L_0041566f:
        cmp dword ptr [esi+2404h],190h
    L_00415679:
        jge short L_004156ce
    L_0041567b:
        and eax,0FFFFFFFDh
    L_0041567e:
        mov word ptr [edi+9D4Ch],8
    L_00415687:
        or eax,4
    L_0041568a:
        jmp short L_004156c8
    L_0041568c:
        cmp ecx,2
    L_0041568f:
        jne short L_004156ab
    L_00415691:
        cmp dword ptr [esi+2404h],0C8h
    L_0041569b:
        jge short L_004156ce
    L_0041569d:
        mov word ptr [edi+9D4Ch],9
    L_004156a6:
        or eax,6
    L_004156a9:
        jmp short L_004156c8
    L_004156ab:
        cmp ecx,3
    L_004156ae:
        jne short L_004156ce
    L_004156b0:
        cmp dword ptr [esi+2404h],0C8h
    L_004156ba:
        jle short L_004156ce
    L_004156bc:
        mov word ptr [edi+9D4Ch],0Ah
    L_004156c5:
        and eax,0FFFFFFF9h
    L_004156c8:
        mov dword ptr [edi+9EB4h],eax
    L_004156ce:
        lea eax,[edi+9A48h]
    L_004156d4:
        push eax
    L_004156d5:
        call asm_FUN_0043ee30_0043ee30
    L_004156da:
        fld dword ptr [esi+1068h]
    L_004156e0:
        fadd dword ptr [data_00470b4c]
    L_004156e6:
        mov ecx,dword ptr [data_00477834]
    L_004156ec:
        mov dword ptr [edi+9D8Ch],43F00000h
    L_004156f6:
        fstp dword ptr [edi+9D88h]
    L_004156fc:
        fld dword ptr [esi+1068h]
    L_00415702:
        fsub dword ptr [ecx+3C0h]
    L_00415708:
        fabs
    L_0041570a:
        fcom qword ptr [data_00470cf0]
    L_00415710:
        fnstsw ax
    L_00415712:
        test ah,1
    L_00415715:
        jne short L_00415722
    L_00415717:
        fstp st(0)
    L_00415719:
        mov byte ptr [edi+9D47h],0FFh
    L_00415720:
        jmp short L_00415737
    L_00415722:
        fmul dword ptr [data_00470ce8]
    L_00415728:
        call asm_FUN_00463b2c_00463b2c
    L_0041572d:
        mov dl,40h
    L_0041572f:
        sub dl,al
    L_00415731:
        mov byte ptr [edi+9D47h],dl
    L_00415737:
        fld dword ptr [esi+1068h]
    L_0041573d:
        fcomp dword ptr [data_00470b40]
    L_00415743:
        fnstsw ax
    L_00415745:
        test ah,5
    L_00415748:
        jnp short L_0041575d
    L_0041574a:
        fld dword ptr [esi+1068h]
    L_00415750:
        fcomp dword ptr [data_00470b3c]
    L_00415756:
        fnstsw ax
    L_00415758:
        test ah,41h
    L_0041575b:
        jne short L_00415764
    L_0041575d:
        mov byte ptr [edi+9D47h],0
    L_00415764:
        mov edx,dword ptr [edi+9E64h]
    L_0041576a:
        mov ecx,dword ptr [edi+9E6Ch]
    L_00415770:
        mov dword ptr [edi+9E60h],edx
    L_00415776:
        fld dword ptr [ecx]
    L_00415778:
        fcomp dword ptr [data_00470b68]
    L_0041577e:
        pop esi
    L_0041577f:
        pop ebp
    L_00415780:
        pop ebx
    L_00415781:
        fnstsw ax
    L_00415783:
        test ah,41h
    L_00415786:
        jne short L_004157ba
    L_00415788:
        fld dword ptr [ecx]
    L_0041578a:
        fcomp dword ptr [data_00470b64]
    L_00415790:
        fnstsw ax
    L_00415792:
        test ah,5
    L_00415795:
        jp short L_004157ba
    L_00415797:
        fld dword ptr [edi+9E68h]
    L_0041579d:
        inc edx
    L_0041579e:
        fadd dword ptr [data_00470afc]
    L_004157a4:
        mov dword ptr [edi+9E64h],edx
    L_004157aa:
        mov eax,1
    L_004157af:
        fstp dword ptr [edi+9E68h]
    L_004157b5:
        pop edi
    L_004157b6:
        pop ecx
    L_004157b7:
        ret 4
    L_004157ba:
        fld dword ptr [ecx]
    L_004157bc:
        fadd dword ptr [edi+9E68h]
    L_004157c2:
        fst dword ptr [edi+9E68h]
    L_004157c8:
        call asm_FUN_00463b2c_00463b2c
    L_004157cd:
        mov dword ptr [edi+9E64h],eax
    L_004157d3:
        mov eax,1
    L_004157d8:
        pop edi
    L_004157d9:
        pop ecx
    L_004157da:
        ret 4
    }
}

// 0x00415E90..0x00416F61: FUN_00415e90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00415e90_00415e90() {
    __asm {
    L_00415e90:
        sub esp,0D8h
    L_00415e96:
        push ebx
    L_00415e97:
        push ebp
    L_00415e98:
        mov ebp,dword ptr [esp+0E4h]
    L_00415e9f:
        mov eax,dword ptr [ebp+78h]
    L_00415ea2:
        xor edx,edx
    L_00415ea4:
        cmp eax,edx
    L_00415ea6:
        push esi
    L_00415ea7:
        push edi
    L_00415ea8:
        jle short L_00415eae
    L_00415eaa:
        dec eax
    L_00415eab:
        mov dword ptr [ebp+78h],eax
    L_00415eae:
        test byte ptr [ebp+7Ch],1
    L_00415eb2:
        je short L_00415ef7
    L_00415eb4:
        mov eax,dword ptr [data_00474e5c]
    L_00415eb9:
        test ah,1
    L_00415ebc:
        je short L_00415ef7
    L_00415ebe:
        mov eax,dword ptr [ebp+5Ch]
    L_00415ec1:
        movzx ecx,word ptr [eax]
    L_00415ec4:
        mov eax,dword ptr [ebp+28h]
    L_00415ec7:
        test al,1
    L_00415ec9:
        mov dword ptr [esp+10h],ecx
    L_00415ecd:
        jne short L_00415ee9
    L_00415ecf:
        or eax,1
    L_00415ed2:
        mov dword ptr [ebp+1Ch],edx
    L_00415ed5:
        mov dword ptr [ebp+18h],0FFF0BDC1h
    L_00415edc:
        mov dword ptr [ebp+20h],edx
    L_00415edf:
        mov dword ptr [ebp+24h],476F78h
    L_00415ee6:
        mov dword ptr [ebp+28h],eax
    L_00415ee9:
        fild dword ptr [esp+10h]
    L_00415eed:
        mov dword ptr [ebp+1Ch],ecx
    L_00415ef0:
        dec ecx
    L_00415ef1:
        mov dword ptr [ebp+18h],ecx
    L_00415ef4:
        fstp dword ptr [ebp+20h]
    L_00415ef7:
        mov ecx,dword ptr [ebp+5Ch]
    L_00415efa:
        movzx edx,word ptr [ecx]
    L_00415efd:
        cmp dword ptr [ebp+1Ch],edx
    L_00415f00:
        jl asm_target_00416f25
    L_00415f06:
        mov eax,dword ptr [ebp+5Ch]
    L_00415f09:
        movzx ecx,byte ptr [eax+2]
    L_00415f0d:
        cmp ecx,17h
    L_00415f10:
        ja asm_target_00416f09
    L_00415f16:
        jmp dword ptr [ecx*4+416F64h]
    L_00415f1d:
        lea edi,[ebp+4Ch]
    L_00415f20:
        jmp short L_00415f25
    L_00415f22:
        lea edi,[ebp+50h]
    L_00415f25:
        mov eax,dword ptr [edi]
    L_00415f27:
        mov ebx,dword ptr [data_00491c10]
    L_00415f2d:
        mov edx,ebx
    L_00415f2f:
        push eax
    L_00415f30:
        call asm_AnimationManager_Find_004491c0
    L_00415f35:
        mov esi,eax
    L_00415f37:
        test esi,esi
    L_00415f39:
        jne short L_00415f3d
    L_00415f3b:
        mov dword ptr [edi],eax
    L_00415f3d:
        mov eax,dword ptr [ebp+5Ch]
    L_00415f40:
        add eax,4
    L_00415f43:
        call asm_Path_DecodeXor_00417010
    L_00415f48:
        mov ecx,dword ptr [ebp+84h]
    L_00415f4e:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00415f55:
        push eax
    L_00415f56:
        push edx
    L_00415f57:
        push ebx
    L_00415f58:
        call asm_Recovery_MarkLogState_00447a50
    L_00415f5d:
        add esp,0Ch
    L_00415f60:
        mov eax,edi
    L_00415f62:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_00415f67:
        jmp asm_target_00416f09
    L_00415f6c:
        mov eax,dword ptr [ebp+80h]
    L_00415f72:
        test eax,eax
    L_00415f74:
        jne asm_target_00416041
    L_00415f7a:
        mov eax,dword ptr [ebp+4Ch]
    L_00415f7d:
        mov esi,dword ptr [data_00491c10]
    L_00415f83:
        lea edi,[ebp+4Ch]
    L_00415f86:
        push eax
    L_00415f87:
        mov edx,esi
    L_00415f89:
        call asm_AnimationManager_Find_004491c0
    L_00415f8e:
        test eax,eax
    L_00415f90:
        jne short L_00415f94
    L_00415f92:
        mov dword ptr [edi],eax
    L_00415f94:
        mov ecx,dword ptr [ebp+84h]
    L_00415f9a:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00415fa1:
        push 46CFD4h
    L_00415fa6:
        push edx
    L_00415fa7:
        push esi
    L_00415fa8:
        mov esi,eax
    L_00415faa:
        call asm_Recovery_MarkLogState_00447a50
    L_00415faf:
        mov eax,dword ptr [ebp+50h]
    L_00415fb2:
        mov esi,dword ptr [data_00491c10]
    L_00415fb8:
        lea ebx,[ebp+50h]
    L_00415fbb:
        add esp,0Ch
    L_00415fbe:
        push eax
    L_00415fbf:
        mov edx,esi
    L_00415fc1:
        call asm_AnimationManager_Find_004491c0
    L_00415fc6:
        test eax,eax
    L_00415fc8:
        jne short L_00415fcc
    L_00415fca:
        mov dword ptr [ebx],eax
    L_00415fcc:
        mov ecx,dword ptr [ebp+84h]
    L_00415fd2:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00415fd9:
        push 46CFD4h
    L_00415fde:
        push edx
    L_00415fdf:
        push esi
    L_00415fe0:
        mov esi,eax
    L_00415fe2:
        call asm_Recovery_MarkLogState_00447a50
    L_00415fe7:
        mov eax,dword ptr [edi]
    L_00415fe9:
        mov edx,dword ptr [data_00491c10]
    L_00415fef:
        add esp,0Ch
    L_00415ff2:
        push eax
    L_00415ff3:
        call asm_AnimationManager_Find_004491c0
    L_00415ff8:
        mov esi,eax
    L_00415ffa:
        test esi,esi
    L_00415ffc:
        jne short L_00416000
    L_00415ffe:
        mov dword ptr [edi],eax
    L_00416000:
        mov eax,dword ptr [ebp+5Ch]
    L_00416003:
        add eax,4
    L_00416006:
        call asm_Path_DecodeXor_00417010
    L_0041600b:
        mov ecx,dword ptr [ebp+84h]
    L_00416011:
        mov edx,dword ptr [ebp+ecx*4+88h]
    L_00416018:
        push eax
    L_00416019:
        mov eax,dword ptr [data_00491c10]
    L_0041601e:
        push edx
    L_0041601f:
        push eax
    L_00416020:
        call asm_Recovery_MarkLogState_00447a50
    L_00416025:
        add esp,0Ch
    L_00416028:
        mov eax,edi
    L_0041602a:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_0041602f:
        mov eax,ebx
    L_00416031:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00416036:
        inc dword ptr [ebp+80h]
    L_0041603c:
        jmp asm_target_00416f09
    L_00416041:
        mov ecx,dword ptr [ebp+50h]
    L_00416044:
        mov ebx,dword ptr [data_00491c10]
    L_0041604a:
        lea edi,[ebp+50h]
    L_0041604d:
        push ecx
    L_0041604e:
        mov edx,ebx
    L_00416050:
        call asm_AnimationManager_Find_004491c0
    L_00416055:
        mov esi,eax
    L_00416057:
        test esi,esi
    L_00416059:
        jne short L_0041605d
    L_0041605b:
        mov dword ptr [edi],eax
    L_0041605d:
        mov eax,dword ptr [ebp+5Ch]
    L_00416060:
        add eax,4
    L_00416063:
        call asm_Path_DecodeXor_00417010
    L_00416068:
        mov edx,dword ptr [ebp+84h]
    L_0041606e:
        push eax
    L_0041606f:
        mov eax,dword ptr [ebp+edx*4+88h]
    L_00416076:
        push eax
    L_00416077:
        push ebx
    L_00416078:
        call asm_Recovery_MarkLogState_00447a50
    L_0041607d:
        add esp,0Ch
    L_00416080:
        mov eax,edi
    L_00416082:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_00416087:
        mov dword ptr [ebp+80h],0
    L_00416091:
        jmp asm_target_00416f09
    L_00416096:
        lea eax,[ebp+4Ch]
    L_00416099:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_0041609e:
        lea eax,[ebp+50h]
    L_004160a1:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_004160a6:
        jmp asm_target_00416f09
    L_004160ab:
        mov ecx,dword ptr [data_0047770c]
    L_004160b1:
        mov eax,dword ptr [ecx+9EC8h]
    L_004160b7:
        push 0Fh
    L_004160b9:
        push 5Ah
    L_004160bb:
        push eax
    L_004160bc:
        lea edi,[esp+1Ch]
    L_004160c0:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004160c5:
        mov edx,dword ptr [eax]
    L_004160c7:
        mov dword ptr [ebp+48h],edx
    L_004160ca:
        jmp asm_target_00416f09
    L_004160cf:
        mov eax,dword ptr [data_00474c68]
    L_004160d4:
        sub eax,0
    L_004160d7:
        je short L_00416103
    L_004160d9:
        dec eax
    L_004160da:
        jne asm_target_00416f09
    L_004160e0:
        mov eax,dword ptr [data_00477834]
    L_004160e5:
        mov eax,dword ptr [eax+10h]
    L_004160e8:
        push 0Fh
    L_004160ea:
        push 1Dh
    L_004160ec:
        push eax
    L_004160ed:
        lea edi,[esp+0BCh]
    L_004160f4:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004160f9:
        mov ecx,dword ptr [eax]
    L_004160fb:
        mov dword ptr [ebp+40h],ecx
    L_004160fe:
        jmp asm_target_00416f09
    L_00416103:
        mov edx,dword ptr [data_00477834]
    L_00416109:
        mov eax,dword ptr [edx+10h]
    L_0041610c:
        push 0Fh
    L_0041610e:
        push 1Dh
    L_00416110:
        push eax
    L_00416111:
        lea edi,[esp+8Ch]
    L_00416118:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0041611d:
        mov eax,dword ptr [eax]
    L_0041611f:
        mov dword ptr [ebp+40h],eax
    L_00416122:
        jmp asm_target_00416f09
    L_00416127:
        mov eax,dword ptr [data_00474c7c]
    L_0041612c:
        cmp eax,6
    L_0041612f:
        jne short L_00416186
    L_00416131:
        mov eax,dword ptr [data_00474c68]
    L_00416136:
        sub eax,0
    L_00416139:
        je short L_00416163
    L_0041613b:
        dec eax
    L_0041613c:
        jne asm_target_00416f09
    L_00416142:
        mov ecx,dword ptr [data_00477704]
    L_00416148:
        mov eax,dword ptr [ecx+38h]
    L_0041614b:
        push 0Fh
    L_0041614d:
        push 20h
    L_0041614f:
        push eax
    L_00416150:
        lea edi,[esp+2Ch]
    L_00416154:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416159:
        mov edx,dword ptr [eax]
    L_0041615b:
        mov dword ptr [ebp+44h],edx
    L_0041615e:
        jmp asm_target_00416f09
    L_00416163:
        mov eax,dword ptr [data_00477704]
    L_00416168:
        mov eax,dword ptr [eax+38h]
    L_0041616b:
        push 0Fh
    L_0041616d:
        push 20h
    L_0041616f:
        push eax
    L_00416170:
        lea edi,[esp+0E4h]
    L_00416177:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0041617c:
        mov ecx,dword ptr [eax]
    L_0041617e:
        mov dword ptr [ebp+44h],ecx
    L_00416181:
        jmp asm_target_00416f09
    L_00416186:
        cmp eax,7
    L_00416189:
        jne short L_004161e7
    L_0041618b:
        cmp dword ptr [ebp],1
    L_0041618f:
        jge short L_004161e7
    L_00416191:
        mov eax,dword ptr [data_00474c68]
    L_00416196:
        sub eax,0
    L_00416199:
        je short L_004161c3
    L_0041619b:
        dec eax
    L_0041619c:
        jne asm_target_00416f09
    L_004161a2:
        mov edx,dword ptr [data_00477704]
    L_004161a8:
        mov eax,dword ptr [edx+38h]
    L_004161ab:
        push 0Fh
    L_004161ad:
        push 25h
    L_004161af:
        push eax
    L_004161b0:
        lea edi,[esp+34h]
    L_004161b4:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004161b9:
        mov eax,dword ptr [eax]
    L_004161bb:
        mov dword ptr [ebp+44h],eax
    L_004161be:
        jmp asm_target_00416f09
    L_004161c3:
        mov ecx,dword ptr [data_00477704]
    L_004161c9:
        mov eax,dword ptr [ecx+38h]
    L_004161cc:
        push 0Fh
    L_004161ce:
        push 25h
    L_004161d0:
        push eax
    L_004161d1:
        lea edi,[esp+94h]
    L_004161d8:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004161dd:
        mov edx,dword ptr [eax]
    L_004161df:
        mov dword ptr [ebp+44h],edx
    L_004161e2:
        jmp asm_target_00416f09
    L_004161e7:
        mov eax,dword ptr [data_00474c68]
    L_004161ec:
        sub eax,0
    L_004161ef:
        je short L_00416218
    L_004161f1:
        dec eax
    L_004161f2:
        jne asm_target_00416f09
    L_004161f8:
        mov eax,dword ptr [data_00477834]
    L_004161fd:
        mov eax,dword ptr [eax+10h]
    L_00416200:
        push 0Fh
    L_00416202:
        push 1Eh
    L_00416204:
        push eax
    L_00416205:
        lea edi,[esp+3Ch]
    L_00416209:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_0041620e:
        mov ecx,dword ptr [eax]
    L_00416210:
        mov dword ptr [ebp+44h],ecx
    L_00416213:
        jmp asm_target_00416f09
    L_00416218:
        mov edx,dword ptr [data_00477834]
    L_0041621e:
        mov eax,dword ptr [edx+10h]
    L_00416221:
        push 0Fh
    L_00416223:
        push 1Eh
    L_00416225:
        push eax
    L_00416226:
        lea edi,[esp+0C4h]
    L_0041622d:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416232:
        mov eax,dword ptr [eax]
    L_00416234:
        mov dword ptr [ebp+44h],eax
    L_00416237:
        jmp asm_target_00416f09
    L_0041623c:
        lea eax,[ebp+40h]
    L_0041623f:
        mov esi,7
    L_00416244:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00416249:
        jmp asm_target_00416f09
    L_0041624e:
        lea eax,[ebp+44h]
    L_00416251:
        mov esi,7
    L_00416256:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_0041625b:
        jmp asm_target_00416f09
    L_00416260:
        lea esi,[ebp+40h]
    L_00416263:
        mov eax,esi
    L_00416265:
        call asm_FUN_00409e50_00409e50
    L_0041626a:
        mov dword ptr [esi],0
    L_00416270:
        jmp asm_target_00416f09
    L_00416275:
        lea esi,[ebp+44h]
    L_00416278:
        mov eax,esi
    L_0041627a:
        call asm_FUN_00409e50_00409e50
    L_0041627f:
        lea eax,[ebp+54h]
    L_00416282:
        mov dword ptr [esi],0
    L_00416288:
        call asm_FUN_00409e50_00409e50
    L_0041628d:
        jmp asm_target_00416f09
    L_00416292:
        lea eax,[ebp+48h]
    L_00416295:
        call asm_FUN_00409e50_00409e50
    L_0041629a:
        lea eax,[ebp+4Ch]
    L_0041629d:
        call asm_FUN_00409e50_00409e50
    L_004162a2:
        lea eax,[ebp+50h]
    L_004162a5:
        call asm_FUN_00409e50_00409e50
    L_004162aa:
        jmp asm_target_00416f09
    L_004162af:
        lea eax,[ebp+44h]
    L_004162b2:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_004162b7:
        lea eax,[ebp+40h]
    L_004162ba:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_004162bf:
        mov ecx,dword ptr [ebp+4Ch]
    L_004162c2:
        mov edi,dword ptr [data_00491c10]
    L_004162c8:
        xor ebx,ebx
    L_004162ca:
        lea esi,[ebp+60h]
    L_004162cd:
        push ecx
    L_004162ce:
        mov edx,edi
    L_004162d0:
        mov dword ptr [ebp+84h],ebx
    L_004162d6:
        call asm_AnimationManager_SetPosition_004492f0
    L_004162db:
        mov eax,dword ptr [ebp+84h]
    L_004162e1:
        add eax,8
    L_004162e4:
        lea edx,[eax+eax*2]
    L_004162e7:
        mov eax,dword ptr [ebp+50h]
    L_004162ea:
        lea esi,[ebp+edx*4]
    L_004162ee:
        push eax
    L_004162ef:
        mov edx,edi
    L_004162f1:
        call asm_AnimationManager_SetPosition_004492f0
    L_004162f6:
        mov dword ptr [ebp+80h],ebx
    L_004162fc:
        jmp asm_target_00416f09
    L_00416301:
        lea eax,[ebp+40h]
    L_00416304:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00416309:
        lea eax,[ebp+44h]
    L_0041630c:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_00416311:
        mov ecx,dword ptr [ebp+4Ch]
    L_00416314:
        mov edi,dword ptr [data_00491c10]
    L_0041631a:
        lea esi,[ebp+6Ch]
    L_0041631d:
        push ecx
    L_0041631e:
        mov edx,edi
    L_00416320:
        mov dword ptr [ebp+84h],1
    L_0041632a:
        call asm_AnimationManager_SetPosition_004492f0
    L_0041632f:
        mov eax,dword ptr [ebp+84h]
    L_00416335:
        add eax,8
    L_00416338:
        lea edx,[eax+eax*2]
    L_0041633b:
        mov eax,dword ptr [ebp+50h]
    L_0041633e:
        lea esi,[ebp+edx*4]
    L_00416342:
        push eax
    L_00416343:
        mov edx,edi
    L_00416345:
        call asm_AnimationManager_SetPosition_004492f0
    L_0041634a:
        mov dword ptr [ebp+80h],0
    L_00416354:
        jmp asm_target_00416f09
    L_00416359:
        mov esi,dword ptr [ebp+7Ch]
    L_0041635c:
        xor ecx,ecx
    L_0041635e:
        mov cl,byte ptr [eax+4]
    L_00416361:
        mov eax,esi
    L_00416363:
        xor ecx,esi
    L_00416365:
        and ecx,1
    L_00416368:
        xor eax,ecx
    L_0041636a:
        mov dword ptr [ebp+7Ch],eax
    L_0041636d:
        jmp asm_target_00416f09
    L_00416372:
        mov ecx,dword ptr [data_00474c68]
    L_00416378:
        sub ecx,0
    L_0041637b:
        je short L_004163c6
    L_0041637d:
        dec ecx
    L_0041637e:
        jne asm_target_00416f09
    L_00416384:
        mov edx,dword ptr [eax+4]
    L_00416387:
        add edx,2Dh
    L_0041638a:
        lea esi,[ebp+40h]
    L_0041638d:
        push edx
    L_0041638e:
        mov ebx,17h
    L_00416393:
        lea edi,[esp+3Ch]
    L_00416397:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041639c:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_004163a1:
        mov eax,dword ptr [ebp+5Ch]
    L_004163a4:
        mov ecx,dword ptr [eax+4]
    L_004163a7:
        add ecx,35h
    L_004163aa:
        push ecx
    L_004163ab:
        mov ebx,1Ah
    L_004163b0:
        lea edi,[esp+94h]
    L_004163b7:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004163bc:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_004163c1:
        jmp asm_target_00416f09
    L_004163c6:
        mov edx,dword ptr [eax+4]
    L_004163c9:
        add edx,34h
    L_004163cc:
        lea esi,[ebp+40h]
    L_004163cf:
        push edx
    L_004163d0:
        mov ebx,17h
    L_004163d5:
        lea edi,[esp+44h]
    L_004163d9:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004163de:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_004163e3:
        mov eax,dword ptr [ebp+5Ch]
    L_004163e6:
        mov ecx,dword ptr [eax+4]
    L_004163e9:
        add ecx,3Ch
    L_004163ec:
        push ecx
    L_004163ed:
        mov ebx,1Ah
    L_004163f2:
        lea edi,[esp+0D4h]
    L_004163f9:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004163fe:
        call asm_AnimationManager_SelectSpriteFromCurrentResource_00449670
    L_00416403:
        jmp asm_target_00416f09
    L_00416408:
        mov ecx,dword ptr [data_00474c7c]
    L_0041640e:
        dec ecx
    L_0041640f:
        cmp ecx,6
    L_00416412:
        ja asm_target_00416f09
    L_00416418:
        jmp dword ptr [ecx*4+416FC4h]
    L_0041641f:
        mov ecx,dword ptr [data_00474c68]
    L_00416425:
        sub ecx,0
    L_00416428:
        je short L_00416487
    L_0041642a:
        dec ecx
    L_0041642b:
        jne asm_target_00416f09
    L_00416431:
        mov eax,dword ptr [eax+4]
    L_00416434:
        mov edx,dword ptr [data_00477704]
    L_0041643a:
        mov ecx,dword ptr [edx+38h]
    L_0041643d:
        add eax,0Fh
    L_00416440:
        push eax
    L_00416441:
        lea esi,[ebp+44h]
    L_00416444:
        push ecx
    L_00416445:
        mov ebx,18h
    L_0041644a:
        lea edi,[esp+50h]
    L_0041644e:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416453:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416458:
        mov ecx,dword ptr [data_00477704]
    L_0041645e:
        mov eax,dword ptr [ecx+38h]
    L_00416461:
        mov edx,dword ptr [ebp+5Ch]
    L_00416464:
        mov ecx,dword ptr [edx+4]
    L_00416467:
        add ecx,17h
    L_0041646a:
        push ecx
    L_0041646b:
        push eax
    L_0041646c:
        mov ebx,1Bh
    L_00416471:
        lea edi,[esp+0A0h]
    L_00416478:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041647d:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416482:
        jmp asm_target_00416f09
    L_00416487:
        mov eax,dword ptr [eax+4]
    L_0041648a:
        mov edx,dword ptr [data_00477704]
    L_00416490:
        mov ecx,dword ptr [edx+38h]
    L_00416493:
        add eax,0Fh
    L_00416496:
        push eax
    L_00416497:
        lea esi,[ebp+44h]
    L_0041649a:
        push ecx
    L_0041649b:
        mov ebx,18h
    L_004164a0:
        lea edi,[esp+58h]
    L_004164a4:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004164a9:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004164ae:
        mov ecx,dword ptr [data_00477704]
    L_004164b4:
        mov eax,dword ptr [ecx+38h]
    L_004164b7:
        mov edx,dword ptr [ebp+5Ch]
    L_004164ba:
        mov ecx,dword ptr [edx+4]
    L_004164bd:
        add ecx,17h
    L_004164c0:
        push ecx
    L_004164c1:
        push eax
    L_004164c2:
        mov ebx,1Bh
    L_004164c7:
        lea edi,[esp+0C8h]
    L_004164ce:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004164d3:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004164d8:
        jmp asm_target_00416f09
    L_004164dd:
        mov ecx,dword ptr [data_00474c68]
    L_004164e3:
        sub ecx,0
    L_004164e6:
        je short L_00416545
    L_004164e8:
        dec ecx
    L_004164e9:
        jne asm_target_00416f09
    L_004164ef:
        mov eax,dword ptr [eax+4]
    L_004164f2:
        mov edx,dword ptr [data_00477704]
    L_004164f8:
        mov ecx,dword ptr [edx+38h]
    L_004164fb:
        add eax,15h
    L_004164fe:
        push eax
    L_004164ff:
        lea esi,[ebp+44h]
    L_00416502:
        push ecx
    L_00416503:
        mov ebx,18h
    L_00416508:
        lea edi,[esp+60h]
    L_0041650c:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416511:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416516:
        mov ecx,dword ptr [data_00477704]
    L_0041651c:
        mov eax,dword ptr [ecx+38h]
    L_0041651f:
        mov edx,dword ptr [ebp+5Ch]
    L_00416522:
        mov ecx,dword ptr [edx+4]
    L_00416525:
        add ecx,1Eh
    L_00416528:
        push ecx
    L_00416529:
        push eax
    L_0041652a:
        mov ebx,1Bh
    L_0041652f:
        lea edi,[esp+0A8h]
    L_00416536:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041653b:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416540:
        jmp asm_target_00416f09
    L_00416545:
        mov eax,dword ptr [eax+4]
    L_00416548:
        mov edx,dword ptr [data_00477704]
    L_0041654e:
        mov ecx,dword ptr [edx+38h]
    L_00416551:
        add eax,15h
    L_00416554:
        push eax
    L_00416555:
        lea esi,[ebp+44h]
    L_00416558:
        push ecx
    L_00416559:
        mov ebx,18h
    L_0041655e:
        lea edi,[esp+68h]
    L_00416562:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416567:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041656c:
        mov ecx,dword ptr [data_00477704]
    L_00416572:
        mov eax,dword ptr [ecx+38h]
    L_00416575:
        mov edx,dword ptr [ebp+5Ch]
    L_00416578:
        mov ecx,dword ptr [edx+4]
    L_0041657b:
        add ecx,1Eh
    L_0041657e:
        push ecx
    L_0041657f:
        push eax
    L_00416580:
        mov ebx,1Bh
    L_00416585:
        lea edi,[esp+0E8h]
    L_0041658c:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416591:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416596:
        jmp asm_target_00416f09
    L_0041659b:
        mov ecx,dword ptr [data_00474c68]
    L_004165a1:
        sub ecx,0
    L_004165a4:
        je short L_00416603
    L_004165a6:
        dec ecx
    L_004165a7:
        jne asm_target_00416f09
    L_004165ad:
        mov eax,dword ptr [eax+4]
    L_004165b0:
        mov edx,dword ptr [data_00477704]
    L_004165b6:
        mov ecx,dword ptr [edx+38h]
    L_004165b9:
        add eax,22h
    L_004165bc:
        push eax
    L_004165bd:
        lea esi,[ebp+44h]
    L_004165c0:
        push ecx
    L_004165c1:
        mov ebx,18h
    L_004165c6:
        lea edi,[esp+70h]
    L_004165ca:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004165cf:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004165d4:
        mov ecx,dword ptr [data_00477704]
    L_004165da:
        mov eax,dword ptr [ecx+38h]
    L_004165dd:
        mov edx,dword ptr [ebp+5Ch]
    L_004165e0:
        mov ecx,dword ptr [edx+4]
    L_004165e3:
        add ecx,2Bh
    L_004165e6:
        push ecx
    L_004165e7:
        push eax
    L_004165e8:
        mov ebx,1Bh
    L_004165ed:
        lea edi,[esp+0B0h]
    L_004165f4:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004165f9:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004165fe:
        jmp asm_target_00416f09
    L_00416603:
        mov eax,dword ptr [eax+4]
    L_00416606:
        mov edx,dword ptr [data_00477704]
    L_0041660c:
        mov ecx,dword ptr [edx+38h]
    L_0041660f:
        add eax,22h
    L_00416612:
        push eax
    L_00416613:
        lea esi,[ebp+44h]
    L_00416616:
        push ecx
    L_00416617:
        mov ebx,18h
    L_0041661c:
        lea edi,[esp+78h]
    L_00416620:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416625:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041662a:
        mov ecx,dword ptr [data_00477704]
    L_00416630:
        mov eax,dword ptr [ecx+38h]
    L_00416633:
        mov edx,dword ptr [ebp+5Ch]
    L_00416636:
        mov ecx,dword ptr [edx+4]
    L_00416639:
        add ecx,2Bh
    L_0041663c:
        push ecx
    L_0041663d:
        push eax
    L_0041663e:
        mov ebx,1Bh
    L_00416643:
        lea edi,[esp+0D0h]
    L_0041664a:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041664f:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416654:
        jmp asm_target_00416f09
    L_00416659:
        mov ecx,dword ptr [data_00474c68]
    L_0041665f:
        sub ecx,0
    L_00416662:
        je short L_004166c1
    L_00416664:
        dec ecx
    L_00416665:
        jne asm_target_00416f09
    L_0041666b:
        mov eax,dword ptr [eax+4]
    L_0041666e:
        mov edx,dword ptr [data_00477704]
    L_00416674:
        mov ecx,dword ptr [edx+38h]
    L_00416677:
        add eax,25h
    L_0041667a:
        push eax
    L_0041667b:
        lea esi,[ebp+44h]
    L_0041667e:
        push ecx
    L_0041667f:
        mov ebx,18h
    L_00416684:
        lea edi,[esp+80h]
    L_0041668b:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416690:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416695:
        mov ecx,dword ptr [data_00477704]
    L_0041669b:
        mov eax,dword ptr [ecx+38h]
    L_0041669e:
        mov edx,dword ptr [ebp+5Ch]
    L_004166a1:
        mov ecx,dword ptr [edx+4]
    L_004166a4:
        add ecx,2Eh
    L_004166a7:
        push ecx
    L_004166a8:
        push eax
    L_004166a9:
        mov ebx,1Bh
    L_004166ae:
        lea edi,[esp+1Ch]
    L_004166b2:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004166b7:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004166bc:
        jmp asm_target_00416f09
    L_004166c1:
        mov eax,dword ptr [eax+4]
    L_004166c4:
        mov edx,dword ptr [data_00477704]
    L_004166ca:
        mov ecx,dword ptr [edx+38h]
    L_004166cd:
        add eax,25h
    L_004166d0:
        push eax
    L_004166d1:
        lea esi,[ebp+44h]
    L_004166d4:
        push ecx
    L_004166d5:
        mov ebx,18h
    L_004166da:
        lea edi,[esp+20h]
    L_004166de:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004166e3:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004166e8:
        mov ecx,dword ptr [data_00477704]
    L_004166ee:
        mov eax,dword ptr [ecx+38h]
    L_004166f1:
        mov edx,dword ptr [ebp+5Ch]
    L_004166f4:
        mov ecx,dword ptr [edx+4]
    L_004166f7:
        add ecx,2Eh
    L_004166fa:
        push ecx
    L_004166fb:
        push eax
    L_004166fc:
        mov ebx,1Bh
    L_00416701:
        lea edi,[esp+24h]
    L_00416705:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041670a:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041670f:
        jmp asm_target_00416f09
    L_00416714:
        mov ecx,dword ptr [data_00474c68]
    L_0041671a:
        sub ecx,0
    L_0041671d:
        je short L_00416779
    L_0041671f:
        dec ecx
    L_00416720:
        jne asm_target_00416f09
    L_00416726:
        mov eax,dword ptr [eax+4]
    L_00416729:
        mov edx,dword ptr [data_00477704]
    L_0041672f:
        mov ecx,dword ptr [edx+38h]
    L_00416732:
        add eax,16h
    L_00416735:
        push eax
    L_00416736:
        lea esi,[ebp+44h]
    L_00416739:
        push ecx
    L_0041673a:
        mov ebx,18h
    L_0041673f:
        lea edi,[esp+2Ch]
    L_00416743:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416748:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041674d:
        mov ecx,dword ptr [data_00477704]
    L_00416753:
        mov eax,dword ptr [ecx+38h]
    L_00416756:
        mov edx,dword ptr [ebp+5Ch]
    L_00416759:
        mov ecx,dword ptr [edx+4]
    L_0041675c:
        add ecx,1Fh
    L_0041675f:
        push ecx
    L_00416760:
        push eax
    L_00416761:
        mov ebx,1Bh
    L_00416766:
        lea edi,[esp+34h]
    L_0041676a:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041676f:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416774:
        jmp asm_target_00416f09
    L_00416779:
        mov eax,dword ptr [eax+4]
    L_0041677c:
        mov edx,dword ptr [data_00477704]
    L_00416782:
        mov ecx,dword ptr [edx+38h]
    L_00416785:
        add eax,16h
    L_00416788:
        push eax
    L_00416789:
        lea esi,[ebp+44h]
    L_0041678c:
        push ecx
    L_0041678d:
        mov ebx,18h
    L_00416792:
        lea edi,[esp+3Ch]
    L_00416796:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041679b:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004167a0:
        mov ecx,dword ptr [data_00477704]
    L_004167a6:
        mov eax,dword ptr [ecx+38h]
    L_004167a9:
        mov edx,dword ptr [ebp+5Ch]
    L_004167ac:
        mov ecx,dword ptr [edx+4]
    L_004167af:
        add ecx,1Fh
    L_004167b2:
        push ecx
    L_004167b3:
        push eax
    L_004167b4:
        mov ebx,1Bh
    L_004167b9:
        lea edi,[esp+44h]
    L_004167bd:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004167c2:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004167c7:
        jmp asm_target_00416f09
    L_004167cc:
        mov ecx,dword ptr [data_00474c68]
    L_004167d2:
        sub ecx,0
    L_004167d5:
        je short L_00416831
    L_004167d7:
        dec ecx
    L_004167d8:
        jne asm_target_00416f09
    L_004167de:
        mov eax,dword ptr [eax+4]
    L_004167e1:
        mov edx,dword ptr [data_00477704]
    L_004167e7:
        mov ecx,dword ptr [edx+38h]
    L_004167ea:
        add eax,30h
    L_004167ed:
        push eax
    L_004167ee:
        lea esi,[ebp+44h]
    L_004167f1:
        push ecx
    L_004167f2:
        mov ebx,1Ch
    L_004167f7:
        lea edi,[esp+4Ch]
    L_004167fb:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416800:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416805:
        mov ecx,dword ptr [data_00477704]
    L_0041680b:
        mov eax,dword ptr [ecx+38h]
    L_0041680e:
        mov edx,dword ptr [ebp+5Ch]
    L_00416811:
        mov ecx,dword ptr [edx+4]
    L_00416814:
        add ecx,39h
    L_00416817:
        push ecx
    L_00416818:
        push eax
    L_00416819:
        mov ebx,1Fh
    L_0041681e:
        lea edi,[esp+54h]
    L_00416822:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416827:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041682c:
        jmp asm_target_00416f09
    L_00416831:
        mov eax,dword ptr [eax+4]
    L_00416834:
        mov edx,dword ptr [data_00477704]
    L_0041683a:
        mov ecx,dword ptr [edx+38h]
    L_0041683d:
        add eax,30h
    L_00416840:
        push eax
    L_00416841:
        lea esi,[ebp+44h]
    L_00416844:
        push ecx
    L_00416845:
        mov ebx,1Ch
    L_0041684a:
        lea edi,[esp+5Ch]
    L_0041684e:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416853:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416858:
        mov ecx,dword ptr [data_00477704]
    L_0041685e:
        mov eax,dword ptr [ecx+38h]
    L_00416861:
        mov edx,dword ptr [ebp+5Ch]
    L_00416864:
        mov ecx,dword ptr [edx+4]
    L_00416867:
        add ecx,39h
    L_0041686a:
        push ecx
    L_0041686b:
        push eax
    L_0041686c:
        mov ebx,1Fh
    L_00416871:
        lea edi,[esp+64h]
    L_00416875:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041687a:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041687f:
        jmp asm_target_00416f09
    L_00416884:
        cmp dword ptr [ebp],1
    L_00416888:
        mov ecx,dword ptr [data_00474c68]
    L_0041688e:
        jge asm_target_00416949
    L_00416894:
        sub ecx,0
    L_00416897:
        je short L_004168f3
    L_00416899:
        dec ecx
    L_0041689a:
        jne asm_target_00416f09
    L_004168a0:
        mov eax,dword ptr [eax+4]
    L_004168a3:
        mov edx,dword ptr [data_00477704]
    L_004168a9:
        mov ecx,dword ptr [edx+38h]
    L_004168ac:
        add eax,44h
    L_004168af:
        push eax
    L_004168b0:
        lea esi,[ebp+44h]
    L_004168b3:
        push ecx
    L_004168b4:
        mov ebx,21h
    L_004168b9:
        lea edi,[esp+6Ch]
    L_004168bd:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004168c2:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004168c7:
        mov ecx,dword ptr [data_00477704]
    L_004168cd:
        mov eax,dword ptr [ecx+38h]
    L_004168d0:
        mov edx,dword ptr [ebp+5Ch]
    L_004168d3:
        mov ecx,dword ptr [edx+4]
    L_004168d6:
        add ecx,4Dh
    L_004168d9:
        push ecx
    L_004168da:
        push eax
    L_004168db:
        mov ebx,24h
    L_004168e0:
        lea edi,[esp+74h]
    L_004168e4:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004168e9:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004168ee:
        jmp asm_target_00416f09
    L_004168f3:
        mov eax,dword ptr [eax+4]
    L_004168f6:
        mov edx,dword ptr [data_00477704]
    L_004168fc:
        mov ecx,dword ptr [edx+38h]
    L_004168ff:
        add eax,44h
    L_00416902:
        push eax
    L_00416903:
        lea esi,[ebp+44h]
    L_00416906:
        push ecx
    L_00416907:
        mov ebx,21h
    L_0041690c:
        lea edi,[esp+7Ch]
    L_00416910:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00416915:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041691a:
        mov ecx,dword ptr [data_00477704]
    L_00416920:
        mov eax,dword ptr [ecx+38h]
    L_00416923:
        mov edx,dword ptr [ebp+5Ch]
    L_00416926:
        mov ecx,dword ptr [edx+4]
    L_00416929:
        add ecx,4Dh
    L_0041692c:
        push ecx
    L_0041692d:
        push eax
    L_0041692e:
        mov ebx,24h
    L_00416933:
        lea edi,[esp+84h]
    L_0041693a:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041693f:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416944:
        jmp asm_target_00416f09
    L_00416949:
        sub ecx,0
    L_0041694c:
        je short L_004169ae
    L_0041694e:
        dec ecx
    L_0041694f:
        jne asm_target_00416f09
    L_00416955:
        mov eax,dword ptr [eax+4]
    L_00416958:
        mov edx,dword ptr [data_00477704]
    L_0041695e:
        mov ecx,dword ptr [edx+38h]
    L_00416961:
        add eax,2Eh
    L_00416964:
        push eax
    L_00416965:
        lea esi,[ebp+44h]
    L_00416968:
        push ecx
    L_00416969:
        mov ebx,18h
    L_0041696e:
        lea edi,[esp+8Ch]
    L_00416975:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0041697a:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_0041697f:
        mov ecx,dword ptr [data_00477704]
    L_00416985:
        mov eax,dword ptr [ecx+38h]
    L_00416988:
        mov edx,dword ptr [ebp+5Ch]
    L_0041698b:
        mov ecx,dword ptr [edx+4]
    L_0041698e:
        add ecx,37h
    L_00416991:
        push ecx
    L_00416992:
        push eax
    L_00416993:
        mov ebx,1Bh
    L_00416998:
        lea edi,[esp+94h]
    L_0041699f:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004169a4:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004169a9:
        jmp asm_target_00416f09
    L_004169ae:
        mov eax,dword ptr [eax+4]
    L_004169b1:
        mov edx,dword ptr [data_00477704]
    L_004169b7:
        mov ecx,dword ptr [edx+38h]
    L_004169ba:
        add eax,2Eh
    L_004169bd:
        push eax
    L_004169be:
        lea esi,[ebp+44h]
    L_004169c1:
        push ecx
    L_004169c2:
        mov ebx,18h
    L_004169c7:
        lea edi,[esp+9Ch]
    L_004169ce:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004169d3:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_004169d8:
        mov ecx,dword ptr [data_00477704]
    L_004169de:
        mov eax,dword ptr [ecx+38h]
    L_004169e1:
        mov edx,dword ptr [ebp+5Ch]
    L_004169e4:
        mov ecx,dword ptr [edx+4]
    L_004169e7:
        add ecx,37h
    L_004169ea:
        push ecx
    L_004169eb:
        push eax
    L_004169ec:
        mov ebx,1Bh
    L_004169f1:
        lea edi,[esp+0A4h]
    L_004169f8:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_004169fd:
        call asm_AnimationManager_SelectSpriteFromResource_004496a0
    L_00416a02:
        jmp asm_target_00416f09
    L_00416a07:
        mov ecx,dword ptr [ebp+30h]
    L_00416a0a:
        xor ebx,ebx
    L_00416a0c:
        cmp ecx,ebx
    L_00416a0e:
        jg short L_00416a1c
    L_00416a10:
        mov edx,dword ptr [eax+4]
    L_00416a13:
        push edx
    L_00416a14:
        lea eax,[ebp+2Ch]
    L_00416a17:
        call asm_Player_SetSchedulerValue_00405410
    L_00416a1c:
        lea esi,[ebp+2Ch]
    L_00416a1f:
        push 0BF800000h
    L_00416a24:
        call asm_FrameTimer_Advance_0044bf40
    L_00416a29:
        test dword ptr [data_00474e62],1001h
    L_00416a33:
        jne short L_00416a65
    L_00416a35:
        cmp dword ptr [ebp+30h],ebx
    L_00416a38:
        jle short L_00416a65
    L_00416a3a:
        test byte ptr [ebp+7Ch],1
    L_00416a3e:
        je asm_target_00416f2d
    L_00416a44:
        mov eax,dword ptr [data_00474e5c]
    L_00416a49:
        test ah,1
    L_00416a4c:
        je asm_target_00416f2d
    L_00416a52:
        push ebx
    L_00416a53:
        mov eax,esi
    L_00416a55:
        call asm_Player_SetSchedulerValue_00405410
    L_00416a5a:
        mov dword ptr [ebp+80h],ebx
    L_00416a60:
        jmp asm_target_00416f09
    L_00416a65:
        push ebx
    L_00416a66:
        xor edi,edi
    L_00416a68:
        mov ecx,492590h
    L_00416a6d:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00416a72:
        push ebx
    L_00416a73:
        mov eax,esi
    L_00416a75:
        call asm_Player_SetSchedulerValue_00405410
    L_00416a7a:
        mov dword ptr [ebp+80h],ebx
    L_00416a80:
        jmp asm_target_00416f09
    L_00416a85:
        mov dword ptr [ebp+78h],1
    L_00416a8c:
        jmp asm_target_00416f09
    L_00416a91:
        mov eax,dword ptr [data_00477848]
    L_00416a96:
        mov ecx,dword ptr [eax+28h]
    L_00416a99:
        push ecx
    L_00416a9a:
        push 1
    L_00416a9c:
        call asm_Sound_PlayDummyRetail_00420b10
    L_00416aa1:
        mov edx,dword ptr [data_0047770c]
    L_00416aa7:
        mov eax,dword ptr [edx+9E80h]
    L_00416aad:
        push 0Fh
    L_00416aaf:
        push 2
    L_00416ab1:
        push eax
    L_00416ab2:
        lea edi,[esp+0B0h]
    L_00416ab9:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416abe:
        jmp asm_target_00416f09
    L_00416ac3:
        mov eax,dword ptr [data_00474c7c]
    L_00416ac8:
        dec eax
    L_00416ac9:
        cmp eax,6
    L_00416acc:
        ja asm_target_00416f09
    L_00416ad2:
        jmp dword ptr [eax*4+416FE0h]
    L_00416ad9:
        mov ecx,dword ptr [data_00477704]
    L_00416adf:
        mov eax,dword ptr [ecx+38h]
    L_00416ae2:
        push 0Fh
    L_00416ae4:
        push 0Dh
    L_00416ae6:
        push eax
    L_00416ae7:
        lea edi,[esp+0B8h]
    L_00416aee:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416af3:
        mov edx,dword ptr [eax]
    L_00416af5:
        mov dword ptr [ebp+54h],edx
    L_00416af8:
        jmp asm_target_00416f09
    L_00416afd:
        mov eax,dword ptr [data_00477704]
    L_00416b02:
        mov eax,dword ptr [eax+38h]
    L_00416b05:
        push 0Fh
    L_00416b07:
        push 10h
    L_00416b09:
        push eax
    L_00416b0a:
        lea edi,[esp+0C0h]
    L_00416b11:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b16:
        mov ecx,dword ptr [eax]
    L_00416b18:
        mov dword ptr [ebp+54h],ecx
    L_00416b1b:
        jmp asm_target_00416f09
    L_00416b20:
        mov edx,dword ptr [data_00477704]
    L_00416b26:
        mov eax,dword ptr [edx+38h]
    L_00416b29:
        push 0Fh
    L_00416b2b:
        push 14h
    L_00416b2d:
        push eax
    L_00416b2e:
        lea edi,[esp+0C8h]
    L_00416b35:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b3a:
        mov eax,dword ptr [eax]
    L_00416b3c:
        mov dword ptr [ebp+54h],eax
    L_00416b3f:
        jmp asm_target_00416f09
    L_00416b44:
        mov ecx,dword ptr [data_00477704]
    L_00416b4a:
        mov eax,dword ptr [ecx+38h]
    L_00416b4d:
        push 0Fh
    L_00416b4f:
        push 15h
    L_00416b51:
        push eax
    L_00416b52:
        lea edi,[esp+0D0h]
    L_00416b59:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b5e:
        mov edx,dword ptr [eax]
    L_00416b60:
        mov dword ptr [ebp+54h],edx
    L_00416b63:
        jmp asm_target_00416f09
    L_00416b68:
        mov eax,dword ptr [data_00477704]
    L_00416b6d:
        mov eax,dword ptr [eax+38h]
    L_00416b70:
        push 0Fh
    L_00416b72:
        push 0Eh
    L_00416b74:
        push eax
    L_00416b75:
        lea edi,[esp+0D8h]
    L_00416b7c:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416b81:
        mov ecx,dword ptr [eax]
    L_00416b83:
        mov dword ptr [ebp+54h],ecx
    L_00416b86:
        jmp asm_target_00416f09
    L_00416b8b:
        mov edx,dword ptr [data_00477704]
    L_00416b91:
        mov eax,dword ptr [edx+38h]
    L_00416b94:
        push 0Fh
    L_00416b96:
        push 23h
    L_00416b98:
        push eax
    L_00416b99:
        lea edi,[esp+0E0h]
    L_00416ba0:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416ba5:
        mov eax,dword ptr [eax]
    L_00416ba7:
        mov dword ptr [ebp+54h],eax
    L_00416baa:
        jmp asm_target_00416f09
    L_00416baf:
        mov ecx,dword ptr [data_00477704]
    L_00416bb5:
        mov eax,dword ptr [ecx+38h]
    L_00416bb8:
        push 0Fh
    L_00416bba:
        push 1Dh
    L_00416bbc:
        push eax
    L_00416bbd:
        lea edi,[esp+0E8h]
    L_00416bc4:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416bc9:
        mov edx,dword ptr [eax]
    L_00416bcb:
        mov dword ptr [ebp+54h],edx
    L_00416bce:
        jmp asm_target_00416f09
    L_00416bd3:
        mov ecx,dword ptr [data_00474c74]
    L_00416bd9:
        cmp ecx,4
    L_00416bdc:
        je short L_00416c3d
    L_00416bde:
        mov eax,dword ptr [data_00474c68]
    L_00416be3:
        mov edx,dword ptr [data_00474c6c]
    L_00416be9:
        lea edx,[edx+eax*2]
    L_00416bec:
        add edx,eax
    L_00416bee:
        imul edx,437Ch
    L_00416bf4:
        lea eax,[ecx+ecx*2]
    L_00416bf7:
        mov ecx,dword ptr [data_00474c7c]
    L_00416bfd:
        lea eax,[ecx+eax*2]
    L_00416c00:
        mov ecx,dword ptr [data_0047783c]
    L_00416c06:
        add edx,ecx
    L_00416c08:
        mov byte ptr [edx+eax*8+4E1h],1
    L_00416c10:
        mov eax,dword ptr [data_00474c74]
    L_00416c15:
        mov esi,dword ptr [data_00474c6c]
    L_00416c1b:
        lea edx,[eax+eax*2+4Eh]
    L_00416c1f:
        mov eax,dword ptr [data_00474c7c]
    L_00416c24:
        lea edx,[eax+edx*2]
    L_00416c27:
        mov eax,dword ptr [data_00474c68]
    L_00416c2c:
        lea esi,[esi+eax*2]
    L_00416c2f:
        add esi,eax
    L_00416c31:
        imul esi,437Ch
    L_00416c37:
        add esi,ecx
    L_00416c39:
        mov byte ptr [esi+edx*8],1
    L_00416c3d:
        test byte ptr [data_00474ca0],10h
    L_00416c44:
        je short L_00416c56
    L_00416c46:
        mov edi,dword ptr [data_00477830]
    L_00416c4c:
        call asm_FUN_00423370_00423370
    L_00416c51:
        jmp asm_target_00416f09
    L_00416c56:
        mov eax,dword ptr [data_00474c7c]
    L_00416c5b:
        cmp eax,6
    L_00416c5e:
        jne asm_target_00416de8
    L_00416c64:
        mov eax,dword ptr [data_0047770c]
    L_00416c69:
        or dword ptr [eax+9EB4h],20h
    L_00416c70:
        mov eax,dword ptr [data_00474c4c]
    L_00416c75:
        imul eax,3E8h
    L_00416c7b:
        push eax
    L_00416c7c:
        mov ecx,474C40h
    L_00416c81:
        call asm_AddScaled_GameScore_00409d90
    L_00416c86:
        mov eax,dword ptr [data_00474c74]
    L_00416c8b:
        cmp eax,4
    L_00416c8e:
        ja asm_target_00416d66
    L_00416c94:
        jmp dword ptr [eax*4+416FFCh]
    L_00416c9b:
        mov ecx,dword ptr [data_00474c70]
    L_00416ca1:
        imul ecx,1312D00h
    L_00416ca7:
        push ecx
    L_00416ca8:
        mov ecx,474C40h
    L_00416cad:
        call asm_AddScaled_GameScore_00409d90
    L_00416cb2:
        movsx edx,word ptr [data_00474c48]
    L_00416cb9:
        imul edx,186A0h
    L_00416cbf:
        push edx
    L_00416cc0:
        jmp asm_target_00416d5c
    L_00416cc5:
        mov eax,dword ptr [data_00474c70]
    L_00416cca:
        imul eax,17D7840h
    L_00416cd0:
        push eax
    L_00416cd1:
        mov ecx,474C40h
    L_00416cd6:
        call asm_AddScaled_GameScore_00409d90
    L_00416cdb:
        movsx ecx,word ptr [data_00474c48]
    L_00416ce2:
        imul ecx,186A0h
    L_00416ce8:
        jmp short L_00416d5b
    L_00416cea:
        mov edx,dword ptr [data_00474c70]
    L_00416cf0:
        imul edx,2160EC0h
    L_00416cf6:
        push edx
    L_00416cf7:
        mov ecx,474C40h
    L_00416cfc:
        call asm_AddScaled_GameScore_00409d90
    L_00416d01:
        movsx eax,word ptr [data_00474c48]
    L_00416d08:
        imul eax,30D40h
    L_00416d0e:
        push eax
    L_00416d0f:
        jmp short L_00416d5c
    L_00416d11:
        mov ecx,dword ptr [data_00474c70]
    L_00416d17:
        imul ecx,2625A00h
    L_00416d1d:
        push ecx
    L_00416d1e:
        mov ecx,474C40h
    L_00416d23:
        call asm_AddScaled_GameScore_00409d90
    L_00416d28:
        movsx edx,word ptr [data_00474c48]
    L_00416d2f:
        imul edx,493E0h
    L_00416d35:
        push edx
    L_00416d36:
        jmp short L_00416d5c
    L_00416d38:
        mov eax,dword ptr [data_00474c70]
    L_00416d3d:
        imul eax,2625A00h
    L_00416d43:
        push eax
    L_00416d44:
        mov ecx,474C40h
    L_00416d49:
        call asm_AddScaled_GameScore_00409d90
    L_00416d4e:
        movsx ecx,word ptr [data_00474c48]
    L_00416d55:
        imul ecx,61A80h
    L_00416d5b:
        push ecx
    L_00416d5c:
        mov ecx,474C40h
    L_00416d61:
        call asm_AddScaled_GameScore_00409d90
    L_00416d66:
        mov edx,dword ptr [data_00477838]
    L_00416d6c:
        cmp dword ptr [edx+10h],1
    L_00416d70:
        je asm_target_00416e8a
    L_00416d76:
        push 0
    L_00416d78:
        push 0
    L_00416d7a:
        push 0
    L_00416d7c:
        push 78h
    L_00416d7e:
        push 5
    L_00416d80:
        mov ebx,31h
    L_00416d85:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00416d8a:
        mov eax,dword ptr [data_0047770c]
    L_00416d8f:
        mov ebx,dword ptr [eax+9EB4h]
    L_00416d95:
        mov dword ptr [eax+9ECCh],0
    L_00416d9f:
        or ebx,10h
    L_00416da2:
        mov dword ptr [eax+9EB4h],ebx
    L_00416da8:
        mov eax,dword ptr [data_00474c68]
    L_00416dad:
        mov ecx,dword ptr [data_00474c6c]
    L_00416db3:
        mov esi,dword ptr [data_00474c74]
    L_00416db9:
        lea edx,[ecx+eax*2]
    L_00416dbc:
        add edx,eax
    L_00416dbe:
        mov eax,dword ptr [data_0047783c]
    L_00416dc3:
        imul edx,10DFh
    L_00416dc9:
        add edx,esi
    L_00416dcb:
        lea eax,[eax+edx*4+4D0h]
    L_00416dd2:
        mov ecx,dword ptr [eax]
    L_00416dd4:
        cmp ecx,1869Fh
    L_00416dda:
        jge asm_target_00416f09
    L_00416de0:
        inc ecx
    L_00416de1:
        mov dword ptr [eax],ecx
    L_00416de3:
        jmp asm_target_00416f09
    L_00416de8:
        cmp eax,7
    L_00416deb:
        jne asm_target_00416e98
    L_00416df1:
        mov eax,dword ptr [data_0047770c]
    L_00416df6:
        or dword ptr [eax+9EB4h],20h
    L_00416dfd:
        mov ecx,dword ptr [data_00474c4c]
    L_00416e03:
        imul ecx,3E8h
    L_00416e09:
        push ecx
    L_00416e0a:
        mov ecx,474C40h
    L_00416e0f:
        call asm_AddScaled_GameScore_00409d90
    L_00416e14:
        mov edx,dword ptr [data_00474c70]
    L_00416e1a:
        imul edx,2625A00h
    L_00416e20:
        push edx
    L_00416e21:
        mov ecx,474C40h
    L_00416e26:
        call asm_AddScaled_GameScore_00409d90
    L_00416e2b:
        movsx eax,word ptr [data_00474c48]
    L_00416e32:
        imul eax,61A80h
    L_00416e38:
        push eax
    L_00416e39:
        mov ecx,474C40h
    L_00416e3e:
        call asm_AddScaled_GameScore_00409d90
    L_00416e43:
        mov ecx,dword ptr [data_00477838]
    L_00416e49:
        cmp dword ptr [ecx+10h],1
    L_00416e4d:
        je short L_00416e8a
    L_00416e4f:
        mov edi,dword ptr [data_00477830]
    L_00416e55:
        call asm_FUN_00423370_00423370
    L_00416e5a:
        mov eax,dword ptr [data_00474c68]
    L_00416e5f:
        mov edx,dword ptr [data_00474c6c]
    L_00416e65:
        lea ecx,[edx+eax*2]
    L_00416e68:
        mov edx,dword ptr [data_00474c74]
    L_00416e6e:
        add ecx,eax
    L_00416e70:
        imul ecx,10DFh
    L_00416e76:
        add ecx,edx
    L_00416e78:
        mov edx,dword ptr [data_0047783c]
    L_00416e7e:
        lea eax,[edx+ecx*4+4D0h]
    L_00416e85:
        jmp asm_target_00416dd2
    L_00416e8a:
        push 4
    L_00416e8c:
        mov eax,491C28h
    L_00416e91:
        call asm_SetInputMode_0040ac90
    L_00416e96:
        jmp short L_00416f09
    L_00416e98:
        mov edi,dword ptr [data_0047770c]
    L_00416e9e:
        mov eax,dword ptr [edi+9E14h]
    L_00416ea4:
        mov edx,dword ptr [data_00491c10]
    L_00416eaa:
        lea esi,[edi+9E14h]
    L_00416eb0:
        push eax
    L_00416eb1:
        call asm_AnimationManager_SetFlag_004492a0
    L_00416eb6:
        push 0Fh
    L_00416eb8:
        mov dword ptr [esi],0
    L_00416ebe:
        mov ecx,dword ptr [edi+9EC8h]
    L_00416ec4:
        push 4Ch
    L_00416ec6:
        push ecx
    L_00416ec7:
        lea edi,[esp+0F0h]
    L_00416ece:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00416ed3:
        mov edx,dword ptr [eax]
    L_00416ed5:
        push 0Bh
    L_00416ed7:
        mov eax,491C28h
    L_00416edc:
        mov dword ptr [esi],edx
    L_00416ede:
        call asm_SetInputMode_0040ac90
    L_00416ee3:
        mov eax,474C40h
    L_00416ee8:
        call asm_FUN_004175e0_004175e0
    L_00416eed:
        jmp short L_00416f09
    L_00416eef:
        cmp dword ptr [data_00474c7c],6
    L_00416ef6:
        je short L_00416eff
    L_00416ef8:
        push 40000000h
    L_00416efd:
        jmp short L_00416f04
    L_00416eff:
        push 41000000h
    L_00416f04:
        call asm_Sound_PlayRandomVoiceRetail_00420c30
    L_00416f09:
        mov eax,dword ptr [ebp+5Ch]
    L_00416f0c:
        movzx ecx,byte ptr [eax+3]
    L_00416f10:
        lea edx,[ecx+eax+4]
    L_00416f14:
        mov eax,edx
    L_00416f16:
        mov dword ptr [ebp+5Ch],edx
    L_00416f19:
        movzx ecx,word ptr [eax]
    L_00416f1c:
        cmp dword ptr [ebp+1Ch],ecx
    L_00416f1f:
        jge asm_target_00415f06
    L_00416f25:
        lea esi,[ebp+18h]
    L_00416f28:
        call asm_FrameTimer_Tick_00404ed0
    L_00416f2d:
        pop edi
    L_00416f2e:
        pop esi
    L_00416f2f:
        pop ebp
    L_00416f30:
        xor eax,eax
    L_00416f32:
        pop ebx
    L_00416f33:
        add esp,0D8h
    L_00416f39:
        ret 4
    L_00416f3c:
        mov ecx,dword ptr [data_00474c84]
    L_00416f42:
        xor eax,eax
    L_00416f44:
        cmp ecx,eax
    L_00416f46:
        je short L_00416f4d
    L_00416f48:
        mov dword ptr [data_00474c8c],eax
    L_00416f4d:
        pop edi
    L_00416f4e:
        pop esi
    L_00416f4f:
        pop ebp
    L_00416f50:
        mov dword ptr [data_00474c84],eax
    L_00416f55:
        or eax,0FFFFFFFFh
    L_00416f58:
        pop ebx
    L_00416f59:
        add esp,0D8h
    L_00416f5f:
        ret 4
    }
}

// 0x0042E5A0..0x0042E644: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_0042e5a0() {
    __asm {
    L_0042e5a0:
        movsx eax,byte ptr [data_00491d68]
    L_0042e5a7:
        push ebx
    L_0042e5a8:
        push ebp
    L_0042e5a9:
        push esi
    L_0042e5aa:
        xor ebx,ebx
    L_0042e5ac:
        push ebx
    L_0042e5ad:
        mov dword ptr [data_00497854],eax
    L_0042e5b2:
        push 8
    L_0042e5b4:
        mov edx,46ECE8h
    L_0042e5b9:
        mov eax,492590h
    L_0042e5be:
        call asm_AnimationManager_RegisterResource_0043e460
    L_0042e5c3:
        movsx eax,byte ptr [data_00491d69]
    L_0042e5ca:
        cmp eax,ebx
    L_0042e5cc:
        mov dword ptr [data_00497858],eax
    L_0042e5d1:
        je short L_0042e60f
    L_0042e5d3:
        fild dword ptr [data_00497854]
    L_0042e5d9:
        fmul dword ptr [data_00470b00]
    L_0042e5df:
        fsubr dword ptr [data_00470afc]
    L_0042e5e5:
        fld st(0)
    L_0042e5e7:
        fmulp st(1),st
    L_0042e5e9:
        fld st(0)
    L_0042e5eb:
        fmul st,st(1)
    L_0042e5ed:
        fsubr dword ptr [data_00470afc]
    L_0042e5f3:
        fmul dword ptr [data_00470b80]
    L_0042e5f9:
        call asm_FUN_00463b2c_00463b2c
    L_0042e5fe:
        fstp st(0)
    L_0042e600:
        mov ecx,0FFFFEC78h
    L_0042e605:
        sub ecx,eax
    L_0042e607:
        mov dword ptr [data_0049785c],ecx
    L_0042e60d:
        jmp short L_0042e619
    L_0042e60f:
        mov dword ptr [data_0049785c],0FFFFD8F0h
    L_0042e619:
        mov edx,dword ptr [edi+2C8h]
    L_0042e61f:
        mov esi,dword ptr [data_00491c10]
    L_0042e625:
        push edx
    L_0042e626:
        mov edx,esi
    L_0042e628:
        call asm_AnimationManager_Find_004491c0
    L_0042e62d:
        cmp eax,ebx
    L_0042e62f:
        jne short L_0042e637
    L_0042e631:
        mov dword ptr [edi+2C8h],ebx
    L_0042e637:
        add eax,10h
    L_0042e63a:
        cmp eax,ebx
    L_0042e63c:
        mov ecx,25h
    L_0042e641:
        TH10_REL8(0x74, 0x0042e641, VA_asm_target_0042e666)
    L_0042e643:
        TH10_REL8(0xeb, 0x0042e643, VA_asm_FUN_0042e5a0_part_0042e650)
    }
}

// 0x0042E650..0x0042E73C: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042e650() {
    __asm {
    L_0042e650:
        mov edx,dword ptr [eax]
    L_0042e652:
        cmp word ptr [edx+38Ah],cx
    L_0042e659:
        je asm_target_0042ed23
    L_0042e65f:
        mov eax,dword ptr [eax+4]
    L_0042e662:
        cmp eax,ebx
    L_0042e664:
        jne short L_0042e650
    L_0042e666:
        xor eax,eax
    L_0042e668:
        push eax
    L_0042e669:
        mov edx,esi
    L_0042e66b:
        call asm_AnimationManager_Find_004491c0
    L_0042e670:
        mov ecx,eax
    L_0042e672:
        cmp ecx,ebx
    L_0042e674:
        je short L_0042e69d
    L_0042e676:
        movsx edx,byte ptr [data_00491d68]
    L_0042e67d:
        mov eax,51EB851Fh
    L_0042e682:
        imul edx
    L_0042e684:
        sar edx,5
    L_0042e687:
        mov eax,edx
    L_0042e689:
        shr eax,1Fh
    L_0042e68c:
        lea edx,[edx+eax+33h]
    L_0042e690:
        mov eax,ecx
    L_0042e692:
        mov ecx,dword ptr [ecx+308h]
    L_0042e698:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e69d:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e6a3:
        push ecx
    L_0042e6a4:
        mov edx,esi
    L_0042e6a6:
        call asm_AnimationManager_Find_004491c0
    L_0042e6ab:
        cmp eax,ebx
    L_0042e6ad:
        jne short L_0042e6b5
    L_0042e6af:
        mov dword ptr [edi+2C8h],ebx
    L_0042e6b5:
        add eax,10h
    L_0042e6b8:
        cmp eax,ebx
    L_0042e6ba:
        mov ecx,26h
    L_0042e6bf:
        je short L_0042e6d7
    L_0042e6c1:
        mov edx,dword ptr [eax]
    L_0042e6c3:
        cmp word ptr [edx+38Ah],cx
    L_0042e6ca:
        je asm_target_0042ed2c
    L_0042e6d0:
        mov eax,dword ptr [eax+4]
    L_0042e6d3:
        cmp eax,ebx
    L_0042e6d5:
        jne short L_0042e6c1
    L_0042e6d7:
        xor eax,eax
    L_0042e6d9:
        push eax
    L_0042e6da:
        mov edx,esi
    L_0042e6dc:
        call asm_AnimationManager_Find_004491c0
    L_0042e6e1:
        mov ecx,eax
    L_0042e6e3:
        cmp ecx,ebx
    L_0042e6e5:
        je short L_0042e717
    L_0042e6e7:
        movsx edx,byte ptr [data_00491d68]
    L_0042e6ee:
        mov eax,66666667h
    L_0042e6f3:
        imul edx
    L_0042e6f5:
        sar edx,2
    L_0042e6f8:
        mov eax,edx
    L_0042e6fa:
        shr eax,1Fh
    L_0042e6fd:
        add eax,edx
    L_0042e6ff:
        cdq
    L_0042e700:
        mov ebp,0Ah
    L_0042e705:
        idiv ebp
    L_0042e707:
        mov eax,ecx
    L_0042e709:
        mov ecx,dword ptr [ecx+308h]
    L_0042e70f:
        add edx,33h
    L_0042e712:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e717:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e71d:
        push ecx
    L_0042e71e:
        mov edx,esi
    L_0042e720:
        call asm_AnimationManager_Find_004491c0
    L_0042e725:
        cmp eax,ebx
    L_0042e727:
        jne short L_0042e72f
    L_0042e729:
        mov dword ptr [edi+2C8h],ebx
    L_0042e72f:
        add eax,10h
    L_0042e732:
        cmp eax,ebx
    L_0042e734:
        TH10_REL8(0x74, 0x0042e734, VA_asm_target_0042e756)
    L_0042e736:
        mov ecx,27h
    L_0042e73b:
        TH10_REL8(0xeb, 0x0042e73b, VA_asm_FUN_0042e5a0_part_0042e740)
    }
}

// 0x0042E740..0x0042EBDC: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042e740() {
    __asm {
    L_0042e740:
        mov edx,dword ptr [eax]
    L_0042e742:
        cmp word ptr [edx+38Ah],cx
    L_0042e749:
        je asm_target_0042ed35
    L_0042e74f:
        mov eax,dword ptr [eax+4]
    L_0042e752:
        cmp eax,ebx
    L_0042e754:
        jne short L_0042e740
    L_0042e756:
        xor eax,eax
    L_0042e758:
        push eax
    L_0042e759:
        mov edx,esi
    L_0042e75b:
        call asm_AnimationManager_Find_004491c0
    L_0042e760:
        mov ecx,eax
    L_0042e762:
        cmp ecx,ebx
    L_0042e764:
        je short L_0042e785
    L_0042e766:
        movsx eax,byte ptr [data_00491d68]
    L_0042e76d:
        cdq
    L_0042e76e:
        mov ebp,0Ah
    L_0042e773:
        idiv ebp
    L_0042e775:
        mov eax,ecx
    L_0042e777:
        mov ecx,dword ptr [ecx+308h]
    L_0042e77d:
        add edx,33h
    L_0042e780:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e785:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e78b:
        push ecx
    L_0042e78c:
        mov edx,esi
    L_0042e78e:
        call asm_AnimationManager_Find_004491c0
    L_0042e793:
        cmp eax,ebx
    L_0042e795:
        jne short L_0042e79d
    L_0042e797:
        mov dword ptr [edi+2C8h],ebx
    L_0042e79d:
        add eax,10h
    L_0042e7a0:
        cmp eax,ebx
    L_0042e7a2:
        mov ebp,29h
    L_0042e7a7:
        je short L_0042e7c6
    L_0042e7a9:
        lea esp,[esp+force_disp32_zero]
    L_0042e7b0:
        mov edx,dword ptr [eax]
    L_0042e7b2:
        cmp word ptr [edx+38Ah],bp
    L_0042e7b9:
        je asm_target_0042ed3e
    L_0042e7bf:
        mov eax,dword ptr [eax+4]
    L_0042e7c2:
        cmp eax,ebx
    L_0042e7c4:
        jne short L_0042e7b0
    L_0042e7c6:
        xor eax,eax
    L_0042e7c8:
        push eax
    L_0042e7c9:
        mov edx,esi
    L_0042e7cb:
        call asm_AnimationManager_Find_004491c0
    L_0042e7d0:
        mov ecx,eax
    L_0042e7d2:
        cmp ecx,ebx
    L_0042e7d4:
        je short L_0042e7fd
    L_0042e7d6:
        movsx edx,byte ptr [data_00491d68]
    L_0042e7dd:
        mov eax,51EB851Fh
    L_0042e7e2:
        imul edx
    L_0042e7e4:
        sar edx,5
    L_0042e7e7:
        mov eax,edx
    L_0042e7e9:
        shr eax,1Fh
    L_0042e7ec:
        lea edx,[edx+eax+3Dh]
    L_0042e7f0:
        mov eax,ecx
    L_0042e7f2:
        mov ecx,dword ptr [ecx+308h]
    L_0042e7f8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e7fd:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e803:
        push ecx
    L_0042e804:
        mov edx,esi
    L_0042e806:
        call asm_AnimationManager_Find_004491c0
    L_0042e80b:
        cmp eax,ebx
    L_0042e80d:
        jne short L_0042e815
    L_0042e80f:
        mov dword ptr [edi+2C8h],ebx
    L_0042e815:
        add eax,10h
    L_0042e818:
        cmp eax,ebx
    L_0042e81a:
        mov ecx,2Ah
    L_0042e81f:
        je short L_0042e837
    L_0042e821:
        mov edx,dword ptr [eax]
    L_0042e823:
        cmp word ptr [edx+38Ah],cx
    L_0042e82a:
        je asm_target_0042ed47
    L_0042e830:
        mov eax,dword ptr [eax+4]
    L_0042e833:
        cmp eax,ebx
    L_0042e835:
        jne short L_0042e821
    L_0042e837:
        xor eax,eax
    L_0042e839:
        push eax
    L_0042e83a:
        mov edx,esi
    L_0042e83c:
        call asm_AnimationManager_Find_004491c0
    L_0042e841:
        mov ecx,eax
    L_0042e843:
        cmp ecx,ebx
    L_0042e845:
        je short L_0042e87c
    L_0042e847:
        movsx edx,byte ptr [data_00491d68]
    L_0042e84e:
        mov eax,66666667h
    L_0042e853:
        imul edx
    L_0042e855:
        sar edx,2
    L_0042e858:
        mov eax,edx
    L_0042e85a:
        shr eax,1Fh
    L_0042e85d:
        add eax,edx
    L_0042e85f:
        cdq
    L_0042e860:
        mov ebp,0Ah
    L_0042e865:
        idiv ebp
    L_0042e867:
        mov eax,ecx
    L_0042e869:
        mov ecx,dword ptr [ecx+308h]
    L_0042e86f:
        add edx,3Dh
    L_0042e872:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e877:
        mov ebp,29h
    L_0042e87c:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e882:
        push ecx
    L_0042e883:
        mov edx,esi
    L_0042e885:
        call asm_AnimationManager_Find_004491c0
    L_0042e88a:
        cmp eax,ebx
    L_0042e88c:
        jne short L_0042e894
    L_0042e88e:
        mov dword ptr [edi+2C8h],ebx
    L_0042e894:
        add eax,10h
    L_0042e897:
        cmp eax,ebx
    L_0042e899:
        je short L_0042e8b6
    L_0042e89b:
        mov ecx,2Bh
    L_0042e8a0:
        mov edx,dword ptr [eax]
    L_0042e8a2:
        cmp word ptr [edx+38Ah],cx
    L_0042e8a9:
        je asm_target_0042ed50
    L_0042e8af:
        mov eax,dword ptr [eax+4]
    L_0042e8b2:
        cmp eax,ebx
    L_0042e8b4:
        jne short L_0042e8a0
    L_0042e8b6:
        xor eax,eax
    L_0042e8b8:
        push eax
    L_0042e8b9:
        mov edx,esi
    L_0042e8bb:
        call asm_AnimationManager_Find_004491c0
    L_0042e8c0:
        mov ecx,eax
    L_0042e8c2:
        cmp ecx,ebx
    L_0042e8c4:
        je short L_0042e8ea
    L_0042e8c6:
        movsx eax,byte ptr [data_00491d68]
    L_0042e8cd:
        cdq
    L_0042e8ce:
        mov ebp,0Ah
    L_0042e8d3:
        idiv ebp
    L_0042e8d5:
        mov eax,ecx
    L_0042e8d7:
        mov ecx,dword ptr [ecx+308h]
    L_0042e8dd:
        add edx,3Dh
    L_0042e8e0:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e8e5:
        mov ebp,29h
    L_0042e8ea:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e8f0:
        push ecx
    L_0042e8f1:
        mov edx,esi
    L_0042e8f3:
        call asm_AnimationManager_Find_004491c0
    L_0042e8f8:
        cmp eax,ebx
    L_0042e8fa:
        jne short L_0042e902
    L_0042e8fc:
        mov dword ptr [edi+2C8h],ebx
    L_0042e902:
        add eax,10h
    L_0042e905:
        cmp eax,ebx
    L_0042e907:
        mov ecx,2Dh
    L_0042e90c:
        je short L_0042e926
    L_0042e90e:
        mov edi,edi
    L_0042e910:
        mov edx,dword ptr [eax]
    L_0042e912:
        cmp word ptr [edx+38Ah],cx
    L_0042e919:
        je asm_target_0042ed59
    L_0042e91f:
        mov eax,dword ptr [eax+4]
    L_0042e922:
        cmp eax,ebx
    L_0042e924:
        jne short L_0042e910
    L_0042e926:
        xor eax,eax
    L_0042e928:
        push eax
    L_0042e929:
        mov edx,esi
    L_0042e92b:
        call asm_AnimationManager_Find_004491c0
    L_0042e930:
        mov ecx,eax
    L_0042e932:
        cmp ecx,ebx
    L_0042e934:
        je short L_0042e95d
    L_0042e936:
        movsx edx,byte ptr [data_00491d69]
    L_0042e93d:
        mov eax,51EB851Fh
    L_0042e942:
        imul edx
    L_0042e944:
        sar edx,5
    L_0042e947:
        mov eax,edx
    L_0042e949:
        shr eax,1Fh
    L_0042e94c:
        lea edx,[edx+eax+33h]
    L_0042e950:
        mov eax,ecx
    L_0042e952:
        mov ecx,dword ptr [ecx+308h]
    L_0042e958:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e95d:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e963:
        push ecx
    L_0042e964:
        mov edx,esi
    L_0042e966:
        call asm_AnimationManager_Find_004491c0
    L_0042e96b:
        cmp eax,ebx
    L_0042e96d:
        jne short L_0042e975
    L_0042e96f:
        mov dword ptr [edi+2C8h],ebx
    L_0042e975:
        add eax,10h
    L_0042e978:
        cmp eax,ebx
    L_0042e97a:
        mov ecx,2Eh
    L_0042e97f:
        je short L_0042e997
    L_0042e981:
        mov edx,dword ptr [eax]
    L_0042e983:
        cmp word ptr [edx+38Ah],cx
    L_0042e98a:
        je asm_target_0042ed62
    L_0042e990:
        mov eax,dword ptr [eax+4]
    L_0042e993:
        cmp eax,ebx
    L_0042e995:
        jne short L_0042e981
    L_0042e997:
        xor eax,eax
    L_0042e999:
        push eax
    L_0042e99a:
        mov edx,esi
    L_0042e99c:
        call asm_AnimationManager_Find_004491c0
    L_0042e9a1:
        mov ecx,eax
    L_0042e9a3:
        cmp ecx,ebx
    L_0042e9a5:
        je short L_0042e9dc
    L_0042e9a7:
        movsx edx,byte ptr [data_00491d69]
    L_0042e9ae:
        mov eax,66666667h
    L_0042e9b3:
        imul edx
    L_0042e9b5:
        sar edx,2
    L_0042e9b8:
        mov eax,edx
    L_0042e9ba:
        shr eax,1Fh
    L_0042e9bd:
        add eax,edx
    L_0042e9bf:
        cdq
    L_0042e9c0:
        mov ebp,0Ah
    L_0042e9c5:
        idiv ebp
    L_0042e9c7:
        mov eax,ecx
    L_0042e9c9:
        mov ecx,dword ptr [ecx+308h]
    L_0042e9cf:
        add edx,33h
    L_0042e9d2:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e9d7:
        mov ebp,29h
    L_0042e9dc:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e9e2:
        push ecx
    L_0042e9e3:
        mov edx,esi
    L_0042e9e5:
        call asm_AnimationManager_Find_004491c0
    L_0042e9ea:
        cmp eax,ebx
    L_0042e9ec:
        jne short L_0042e9f4
    L_0042e9ee:
        mov dword ptr [edi+2C8h],ebx
    L_0042e9f4:
        add eax,10h
    L_0042e9f7:
        cmp eax,ebx
    L_0042e9f9:
        je short L_0042ea16
    L_0042e9fb:
        mov ecx,2Fh
    L_0042ea00:
        mov edx,dword ptr [eax]
    L_0042ea02:
        cmp word ptr [edx+38Ah],cx
    L_0042ea09:
        je asm_target_0042ed6b
    L_0042ea0f:
        mov eax,dword ptr [eax+4]
    L_0042ea12:
        cmp eax,ebx
    L_0042ea14:
        jne short L_0042ea00
    L_0042ea16:
        xor eax,eax
    L_0042ea18:
        push eax
    L_0042ea19:
        mov edx,esi
    L_0042ea1b:
        call asm_AnimationManager_Find_004491c0
    L_0042ea20:
        mov ecx,eax
    L_0042ea22:
        cmp ecx,ebx
    L_0042ea24:
        je short L_0042ea4a
    L_0042ea26:
        movsx eax,byte ptr [data_00491d69]
    L_0042ea2d:
        cdq
    L_0042ea2e:
        mov ebp,0Ah
    L_0042ea33:
        idiv ebp
    L_0042ea35:
        mov eax,ecx
    L_0042ea37:
        mov ecx,dword ptr [ecx+308h]
    L_0042ea3d:
        add edx,33h
    L_0042ea40:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042ea45:
        mov ebp,29h
    L_0042ea4a:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ea50:
        push ecx
    L_0042ea51:
        mov edx,esi
    L_0042ea53:
        call asm_AnimationManager_Find_004491c0
    L_0042ea58:
        cmp eax,ebx
    L_0042ea5a:
        jne short L_0042ea62
    L_0042ea5c:
        mov dword ptr [edi+2C8h],ebx
    L_0042ea62:
        add eax,10h
    L_0042ea65:
        cmp eax,ebx
    L_0042ea67:
        mov ecx,31h
    L_0042ea6c:
        je short L_0042ea86
    L_0042ea6e:
        mov edi,edi
    L_0042ea70:
        mov edx,dword ptr [eax]
    L_0042ea72:
        cmp word ptr [edx+38Ah],cx
    L_0042ea79:
        je asm_target_0042ed74
    L_0042ea7f:
        mov eax,dword ptr [eax+4]
    L_0042ea82:
        cmp eax,ebx
    L_0042ea84:
        jne short L_0042ea70
    L_0042ea86:
        xor eax,eax
    L_0042ea88:
        push eax
    L_0042ea89:
        mov edx,esi
    L_0042ea8b:
        call asm_AnimationManager_Find_004491c0
    L_0042ea90:
        mov ecx,eax
    L_0042ea92:
        cmp ecx,ebx
    L_0042ea94:
        je short L_0042eabd
    L_0042ea96:
        movsx edx,byte ptr [data_00491d69]
    L_0042ea9d:
        mov eax,51EB851Fh
    L_0042eaa2:
        imul edx
    L_0042eaa4:
        sar edx,5
    L_0042eaa7:
        mov eax,edx
    L_0042eaa9:
        shr eax,1Fh
    L_0042eaac:
        lea edx,[edx+eax+3Dh]
    L_0042eab0:
        mov eax,ecx
    L_0042eab2:
        mov ecx,dword ptr [ecx+308h]
    L_0042eab8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042eabd:
        mov ecx,dword ptr [edi+2C8h]
    L_0042eac3:
        push ecx
    L_0042eac4:
        mov edx,esi
    L_0042eac6:
        call asm_AnimationManager_Find_004491c0
    L_0042eacb:
        cmp eax,ebx
    L_0042eacd:
        jne short L_0042ead5
    L_0042eacf:
        mov dword ptr [edi+2C8h],ebx
    L_0042ead5:
        add eax,10h
    L_0042ead8:
        cmp eax,ebx
    L_0042eada:
        mov ecx,32h
    L_0042eadf:
        je short L_0042eaf7
    L_0042eae1:
        mov edx,dword ptr [eax]
    L_0042eae3:
        cmp word ptr [edx+38Ah],cx
    L_0042eaea:
        je asm_target_0042ed7d
    L_0042eaf0:
        mov eax,dword ptr [eax+4]
    L_0042eaf3:
        cmp eax,ebx
    L_0042eaf5:
        jne short L_0042eae1
    L_0042eaf7:
        xor eax,eax
    L_0042eaf9:
        push eax
    L_0042eafa:
        mov edx,esi
    L_0042eafc:
        call asm_AnimationManager_Find_004491c0
    L_0042eb01:
        mov ecx,eax
    L_0042eb03:
        cmp ecx,ebx
    L_0042eb05:
        je short L_0042eb3c
    L_0042eb07:
        movsx edx,byte ptr [data_00491d69]
    L_0042eb0e:
        mov eax,66666667h
    L_0042eb13:
        imul edx
    L_0042eb15:
        sar edx,2
    L_0042eb18:
        mov eax,edx
    L_0042eb1a:
        shr eax,1Fh
    L_0042eb1d:
        add eax,edx
    L_0042eb1f:
        cdq
    L_0042eb20:
        mov ebp,0Ah
    L_0042eb25:
        idiv ebp
    L_0042eb27:
        mov eax,ecx
    L_0042eb29:
        mov ecx,dword ptr [ecx+308h]
    L_0042eb2f:
        add edx,3Dh
    L_0042eb32:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042eb37:
        mov ebp,29h
    L_0042eb3c:
        mov ecx,dword ptr [edi+2C8h]
    L_0042eb42:
        push ecx
    L_0042eb43:
        mov edx,esi
    L_0042eb45:
        call asm_AnimationManager_Find_004491c0
    L_0042eb4a:
        cmp eax,ebx
    L_0042eb4c:
        jne short L_0042eb54
    L_0042eb4e:
        mov dword ptr [edi+2C8h],ebx
    L_0042eb54:
        add eax,10h
    L_0042eb57:
        cmp eax,ebx
    L_0042eb59:
        je short L_0042eb76
    L_0042eb5b:
        mov ecx,33h
    L_0042eb60:
        mov edx,dword ptr [eax]
    L_0042eb62:
        cmp word ptr [edx+38Ah],cx
    L_0042eb69:
        je asm_target_0042ed86
    L_0042eb6f:
        mov eax,dword ptr [eax+4]
    L_0042eb72:
        cmp eax,ebx
    L_0042eb74:
        jne short L_0042eb60
    L_0042eb76:
        xor eax,eax
    L_0042eb78:
        push eax
    L_0042eb79:
        mov edx,esi
    L_0042eb7b:
        call asm_AnimationManager_Find_004491c0
    L_0042eb80:
        mov ecx,eax
    L_0042eb82:
        cmp ecx,ebx
    L_0042eb84:
        je short L_0042ebaa
    L_0042eb86:
        movsx eax,byte ptr [data_00491d69]
    L_0042eb8d:
        cdq
    L_0042eb8e:
        mov ebp,0Ah
    L_0042eb93:
        idiv ebp
    L_0042eb95:
        mov eax,ecx
    L_0042eb97:
        mov ecx,dword ptr [ecx+308h]
    L_0042eb9d:
        add edx,3Dh
    L_0042eba0:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042eba5:
        mov ebp,29h
    L_0042ebaa:
        mov al,byte ptr [data_00491d68]
    L_0042ebaf:
        cmp al,0Ah
    L_0042ebb1:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ebb7:
        mov edx,esi
    L_0042ebb9:
        push ecx
    L_0042ebba:
        jge asm_target_0042edb3
    L_0042ebc0:
        call asm_AnimationManager_Find_004491c0
    L_0042ebc5:
        cmp eax,ebx
    L_0042ebc7:
        jne short L_0042ebcf
    L_0042ebc9:
        mov dword ptr [edi+2C8h],ebx
    L_0042ebcf:
        add eax,10h
    L_0042ebd2:
        cmp eax,ebx
    L_0042ebd4:
        TH10_REL8(0x74, 0x0042ebd4, VA_asm_target_0042ebf6)
    L_0042ebd6:
        mov ecx,25h
    L_0042ebdb:
        TH10_REL8(0xeb, 0x0042ebdb, VA_asm_FUN_0042e5a0_part_0042ebe0)
    }
}

// 0x0042EBE0..0x0042EC35: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042ebe0() {
    __asm {
    L_0042ebe0:
        mov edx,dword ptr [eax]
    L_0042ebe2:
        cmp word ptr [edx+38Ah],cx
    L_0042ebe9:
        je asm_target_0042ed8f
    L_0042ebef:
        mov eax,dword ptr [eax+4]
    L_0042ebf2:
        cmp eax,ebx
    L_0042ebf4:
        jne short L_0042ebe0
    L_0042ebf6:
        xor eax,eax
    L_0042ebf8:
        push eax
    L_0042ebf9:
        mov edx,esi
    L_0042ebfb:
        call asm_AnimationManager_Find_004491c0
    L_0042ec00:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ec06:
        add eax,35Ch
    L_0042ec0b:
        and ecx,0FFFFFFFDh
    L_0042ec0e:
        mov dword ptr [eax],ecx
    L_0042ec10:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ec16:
        push ecx
    L_0042ec17:
        mov edx,esi
    L_0042ec19:
        call asm_AnimationManager_Find_004491c0
    L_0042ec1e:
        cmp eax,ebx
    L_0042ec20:
        jne short L_0042ec28
    L_0042ec22:
        mov dword ptr [edi+2C8h],ebx
    L_0042ec28:
        add eax,10h
    L_0042ec2b:
        cmp eax,ebx
    L_0042ec2d:
        TH10_REL8(0x74, 0x0042ec2d, VA_asm_target_0042ec56)
    L_0042ec2f:
        mov ecx,26h
    L_0042ec34:
        TH10_REL8(0xeb, 0x0042ec34, VA_asm_FUN_0042e5a0_part_0042ec40)
    }
}

// 0x0042EC40..0x0042ECE5: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042ec40() {
    __asm {
    L_0042ec40:
        mov edx,dword ptr [eax]
    L_0042ec42:
        cmp word ptr [edx+38Ah],cx
    L_0042ec49:
        je asm_target_0042ed98
    L_0042ec4f:
        mov eax,dword ptr [eax+4]
    L_0042ec52:
        cmp eax,ebx
    L_0042ec54:
        jne short L_0042ec40
    L_0042ec56:
        xor eax,eax
    L_0042ec58:
        push eax
    L_0042ec59:
        mov edx,esi
    L_0042ec5b:
        call asm_AnimationManager_Find_004491c0
    L_0042ec60:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ec66:
        add eax,35Ch
    L_0042ec6b:
        and ecx,0FFFFFFFDh
    L_0042ec6e:
        mov dword ptr [eax],ecx
    L_0042ec70:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ec76:
        push ecx
    L_0042ec77:
        mov edx,esi
    L_0042ec79:
        call asm_AnimationManager_Find_004491c0
    L_0042ec7e:
        cmp eax,ebx
    L_0042ec80:
        jne short L_0042ec88
    L_0042ec82:
        mov dword ptr [edi+2C8h],ebx
    L_0042ec88:
        add eax,10h
    L_0042ec8b:
        cmp eax,ebx
    L_0042ec8d:
        je short L_0042eca6
    L_0042ec8f:
        nop
    L_0042ec90:
        mov edx,dword ptr [eax]
    L_0042ec92:
        cmp word ptr [edx+38Ah],bp
    L_0042ec99:
        je asm_target_0042eda1
    L_0042ec9f:
        mov eax,dword ptr [eax+4]
    L_0042eca2:
        cmp eax,ebx
    L_0042eca4:
        jne short L_0042ec90
    L_0042eca6:
        xor eax,eax
    L_0042eca8:
        push eax
    L_0042eca9:
        mov edx,esi
    L_0042ecab:
        call asm_AnimationManager_Find_004491c0
    L_0042ecb0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042ecb6:
        add eax,35Ch
    L_0042ecbb:
        and ebp,0FFFFFFFDh
    L_0042ecbe:
        mov dword ptr [eax],ebp
    L_0042ecc0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ecc6:
        push ecx
    L_0042ecc7:
        mov edx,esi
    L_0042ecc9:
        call asm_AnimationManager_Find_004491c0
    L_0042ecce:
        cmp eax,ebx
    L_0042ecd0:
        jne short L_0042ecd8
    L_0042ecd2:
        mov dword ptr [edi+2C8h],ebx
    L_0042ecd8:
        add eax,10h
    L_0042ecdb:
        cmp eax,ebx
    L_0042ecdd:
        TH10_REL8(0x74, 0x0042ecdd, VA_asm_target_0042ed06)
    L_0042ecdf:
        mov ecx,2Ah
    L_0042ece4:
        TH10_REL8(0xeb, 0x0042ece4, VA_asm_FUN_0042e5a0_part_0042ecf0)
    }
}

// 0x0042ECF0..0x0042EDD7: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042ecf0() {
    __asm {
    L_0042ecf0:
        mov edx,dword ptr [eax]
    L_0042ecf2:
        cmp word ptr [edx+38Ah],cx
    L_0042ecf9:
        je asm_target_0042edaa
    L_0042ecff:
        mov eax,dword ptr [eax+4]
    L_0042ed02:
        cmp eax,ebx
    L_0042ed04:
        jne short L_0042ecf0
    L_0042ed06:
        xor eax,eax
    L_0042ed08:
        push eax
    L_0042ed09:
        mov edx,esi
    L_0042ed0b:
        call asm_AnimationManager_Find_004491c0
    L_0042ed10:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ed16:
        add eax,35Ch
    L_0042ed1b:
        and ecx,0FFFFFFFDh
    L_0042ed1e:
        jmp asm_target_0042f07e
    L_0042ed23:
        mov eax,dword ptr [eax]
    L_0042ed25:
        mov eax,dword ptr [eax]
    L_0042ed27:
        jmp asm_target_0042e668
    L_0042ed2c:
        mov eax,dword ptr [eax]
    L_0042ed2e:
        mov eax,dword ptr [eax]
    L_0042ed30:
        jmp asm_target_0042e6d9
    L_0042ed35:
        mov eax,dword ptr [eax]
    L_0042ed37:
        mov eax,dword ptr [eax]
    L_0042ed39:
        jmp asm_target_0042e758
    L_0042ed3e:
        mov eax,dword ptr [eax]
    L_0042ed40:
        mov eax,dword ptr [eax]
    L_0042ed42:
        jmp asm_target_0042e7c8
    L_0042ed47:
        mov eax,dword ptr [eax]
    L_0042ed49:
        mov eax,dword ptr [eax]
    L_0042ed4b:
        jmp asm_target_0042e839
    L_0042ed50:
        mov eax,dword ptr [eax]
    L_0042ed52:
        mov eax,dword ptr [eax]
    L_0042ed54:
        jmp asm_target_0042e8b8
    L_0042ed59:
        mov eax,dword ptr [eax]
    L_0042ed5b:
        mov eax,dword ptr [eax]
    L_0042ed5d:
        jmp asm_target_0042e928
    L_0042ed62:
        mov eax,dword ptr [eax]
    L_0042ed64:
        mov eax,dword ptr [eax]
    L_0042ed66:
        jmp asm_target_0042e999
    L_0042ed6b:
        mov eax,dword ptr [eax]
    L_0042ed6d:
        mov eax,dword ptr [eax]
    L_0042ed6f:
        jmp asm_target_0042ea18
    L_0042ed74:
        mov eax,dword ptr [eax]
    L_0042ed76:
        mov eax,dword ptr [eax]
    L_0042ed78:
        jmp asm_target_0042ea88
    L_0042ed7d:
        mov eax,dword ptr [eax]
    L_0042ed7f:
        mov eax,dword ptr [eax]
    L_0042ed81:
        jmp asm_target_0042eaf9
    L_0042ed86:
        mov eax,dword ptr [eax]
    L_0042ed88:
        mov eax,dword ptr [eax]
    L_0042ed8a:
        jmp asm_target_0042eb78
    L_0042ed8f:
        mov eax,dword ptr [eax]
    L_0042ed91:
        mov eax,dword ptr [eax]
    L_0042ed93:
        jmp asm_target_0042ebf8
    L_0042ed98:
        mov eax,dword ptr [eax]
    L_0042ed9a:
        mov eax,dword ptr [eax]
    L_0042ed9c:
        jmp asm_target_0042ec58
    L_0042eda1:
        mov eax,dword ptr [eax]
    L_0042eda3:
        mov eax,dword ptr [eax]
    L_0042eda5:
        jmp asm_target_0042eca8
    L_0042edaa:
        mov eax,dword ptr [eax]
    L_0042edac:
        mov eax,dword ptr [eax]
    L_0042edae:
        jmp asm_target_0042ed08
    L_0042edb3:
        cmp al,64h
    L_0042edb5:
        jge asm_target_0042ef1c
    L_0042edbb:
        call asm_AnimationManager_Find_004491c0
    L_0042edc0:
        cmp eax,ebx
    L_0042edc2:
        jne short L_0042edca
    L_0042edc4:
        mov dword ptr [edi+2C8h],ebx
    L_0042edca:
        add eax,10h
    L_0042edcd:
        cmp eax,ebx
    L_0042edcf:
        TH10_REL8(0x74, 0x0042edcf, VA_asm_target_0042edf6)
    L_0042edd1:
        mov ecx,25h
    L_0042edd6:
        TH10_REL8(0xeb, 0x0042edd6, VA_asm_FUN_0042e5a0_part_0042ede0)
    }
}

// 0x0042EDE0..0x0042EE35: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042ede0() {
    __asm {
    L_0042ede0:
        mov edx,dword ptr [eax]
    L_0042ede2:
        cmp word ptr [edx+38Ah],cx
    L_0042ede9:
        je asm_target_0042eefb
    L_0042edef:
        mov eax,dword ptr [eax+4]
    L_0042edf2:
        cmp eax,ebx
    L_0042edf4:
        jne short L_0042ede0
    L_0042edf6:
        xor eax,eax
    L_0042edf8:
        push eax
    L_0042edf9:
        mov edx,esi
    L_0042edfb:
        call asm_AnimationManager_Find_004491c0
    L_0042ee00:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ee06:
        add eax,35Ch
    L_0042ee0b:
        and ecx,0FFFFFFFDh
    L_0042ee0e:
        mov dword ptr [eax],ecx
    L_0042ee10:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ee16:
        push ecx
    L_0042ee17:
        mov edx,esi
    L_0042ee19:
        call asm_AnimationManager_Find_004491c0
    L_0042ee1e:
        cmp eax,ebx
    L_0042ee20:
        jne short L_0042ee28
    L_0042ee22:
        mov dword ptr [edi+2C8h],ebx
    L_0042ee28:
        add eax,10h
    L_0042ee2b:
        cmp eax,ebx
    L_0042ee2d:
        TH10_REL8(0x74, 0x0042ee2d, VA_asm_target_0042ee56)
    L_0042ee2f:
        mov ecx,26h
    L_0042ee34:
        TH10_REL8(0xeb, 0x0042ee34, VA_asm_FUN_0042e5a0_part_0042ee40)
    }
}

// 0x0042EE40..0x0042EF38: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042ee40() {
    __asm {
    L_0042ee40:
        mov edx,dword ptr [eax]
    L_0042ee42:
        cmp word ptr [edx+38Ah],cx
    L_0042ee49:
        je asm_target_0042ef04
    L_0042ee4f:
        mov eax,dword ptr [eax+4]
    L_0042ee52:
        cmp eax,ebx
    L_0042ee54:
        jne short L_0042ee40
    L_0042ee56:
        xor eax,eax
    L_0042ee58:
        push eax
    L_0042ee59:
        mov edx,esi
    L_0042ee5b:
        call asm_AnimationManager_Find_004491c0
    L_0042ee60:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ee66:
        add eax,35Ch
    L_0042ee6b:
        or ecx,2
    L_0042ee6e:
        mov dword ptr [eax],ecx
    L_0042ee70:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ee76:
        push ecx
    L_0042ee77:
        mov edx,esi
    L_0042ee79:
        call asm_AnimationManager_Find_004491c0
    L_0042ee7e:
        cmp eax,ebx
    L_0042ee80:
        jne short L_0042ee88
    L_0042ee82:
        mov dword ptr [edi+2C8h],ebx
    L_0042ee88:
        add eax,10h
    L_0042ee8b:
        cmp eax,ebx
    L_0042ee8d:
        je short L_0042eea2
    L_0042ee8f:
        nop
    L_0042ee90:
        mov edx,dword ptr [eax]
    L_0042ee92:
        cmp word ptr [edx+38Ah],bp
    L_0042ee99:
        je short L_0042ef0d
    L_0042ee9b:
        mov eax,dword ptr [eax+4]
    L_0042ee9e:
        cmp eax,ebx
    L_0042eea0:
        jne short L_0042ee90
    L_0042eea2:
        xor eax,eax
    L_0042eea4:
        push eax
    L_0042eea5:
        mov edx,esi
    L_0042eea7:
        call asm_AnimationManager_Find_004491c0
    L_0042eeac:
        mov ebp,dword ptr [eax+35Ch]
    L_0042eeb2:
        add eax,35Ch
    L_0042eeb7:
        and ebp,0FFFFFFFDh
    L_0042eeba:
        mov dword ptr [eax],ebp
    L_0042eebc:
        mov ecx,dword ptr [edi+2C8h]
    L_0042eec2:
        push ecx
    L_0042eec3:
        mov edx,esi
    L_0042eec5:
        call asm_AnimationManager_Find_004491c0
    L_0042eeca:
        cmp eax,ebx
    L_0042eecc:
        jne short L_0042eed4
    L_0042eece:
        mov dword ptr [edi+2C8h],ebx
    L_0042eed4:
        add eax,10h
    L_0042eed7:
        cmp eax,ebx
    L_0042eed9:
        je asm_target_0042f066
    L_0042eedf:
        mov ecx,2Ah
    L_0042eee4:
        mov edx,dword ptr [eax]
    L_0042eee6:
        cmp word ptr [edx+38Ah],cx
    L_0042eeed:
        je short L_0042ef13
    L_0042eeef:
        mov eax,dword ptr [eax+4]
    L_0042eef2:
        cmp eax,ebx
    L_0042eef4:
        jne short L_0042eee4
    L_0042eef6:
        jmp asm_target_0042f066
    L_0042eefb:
        mov eax,dword ptr [eax]
    L_0042eefd:
        mov eax,dword ptr [eax]
    L_0042eeff:
        jmp asm_target_0042edf8
    L_0042ef04:
        mov eax,dword ptr [eax]
    L_0042ef06:
        mov eax,dword ptr [eax]
    L_0042ef08:
        jmp asm_target_0042ee58
    L_0042ef0d:
        mov eax,dword ptr [eax]
    L_0042ef0f:
        mov eax,dword ptr [eax]
    L_0042ef11:
        jmp short L_0042eea4
    L_0042ef13:
        mov eax,dword ptr [eax]
    L_0042ef15:
        mov eax,dword ptr [eax]
    L_0042ef17:
        jmp asm_target_0042f068
    L_0042ef1c:
        call asm_AnimationManager_Find_004491c0
    L_0042ef21:
        cmp eax,ebx
    L_0042ef23:
        jne short L_0042ef2b
    L_0042ef25:
        mov dword ptr [edi+2C8h],ebx
    L_0042ef2b:
        add eax,10h
    L_0042ef2e:
        cmp eax,ebx
    L_0042ef30:
        TH10_REL8(0x74, 0x0042ef30, VA_asm_target_0042ef56)
    L_0042ef32:
        mov ecx,25h
    L_0042ef37:
        TH10_REL8(0xeb, 0x0042ef37, VA_asm_FUN_0042e5a0_part_0042ef40)
    }
}

// 0x0042EF40..0x0042EF95: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042ef40() {
    __asm {
    L_0042ef40:
        mov edx,dword ptr [eax]
    L_0042ef42:
        cmp word ptr [edx+38Ah],cx
    L_0042ef49:
        je asm_target_0042f1f4
    L_0042ef4f:
        mov eax,dword ptr [eax+4]
    L_0042ef52:
        cmp eax,ebx
    L_0042ef54:
        jne short L_0042ef40
    L_0042ef56:
        xor eax,eax
    L_0042ef58:
        push eax
    L_0042ef59:
        mov edx,esi
    L_0042ef5b:
        call asm_AnimationManager_Find_004491c0
    L_0042ef60:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ef66:
        add eax,35Ch
    L_0042ef6b:
        or ecx,2
    L_0042ef6e:
        mov dword ptr [eax],ecx
    L_0042ef70:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ef76:
        push ecx
    L_0042ef77:
        mov edx,esi
    L_0042ef79:
        call asm_AnimationManager_Find_004491c0
    L_0042ef7e:
        cmp eax,ebx
    L_0042ef80:
        jne short L_0042ef88
    L_0042ef82:
        mov dword ptr [edi+2C8h],ebx
    L_0042ef88:
        add eax,10h
    L_0042ef8b:
        cmp eax,ebx
    L_0042ef8d:
        TH10_REL8(0x74, 0x0042ef8d, VA_asm_target_0042efb6)
    L_0042ef8f:
        mov ecx,26h
    L_0042ef94:
        TH10_REL8(0xeb, 0x0042ef94, VA_asm_FUN_0042e5a0_part_0042efa0)
    }
}

// 0x0042EFA0..0x0042F045: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042efa0() {
    __asm {
    L_0042efa0:
        mov edx,dword ptr [eax]
    L_0042efa2:
        cmp word ptr [edx+38Ah],cx
    L_0042efa9:
        je asm_target_0042f1fd
    L_0042efaf:
        mov eax,dword ptr [eax+4]
    L_0042efb2:
        cmp eax,ebx
    L_0042efb4:
        jne short L_0042efa0
    L_0042efb6:
        xor eax,eax
    L_0042efb8:
        push eax
    L_0042efb9:
        mov edx,esi
    L_0042efbb:
        call asm_AnimationManager_Find_004491c0
    L_0042efc0:
        mov ecx,dword ptr [eax+35Ch]
    L_0042efc6:
        add eax,35Ch
    L_0042efcb:
        or ecx,2
    L_0042efce:
        mov dword ptr [eax],ecx
    L_0042efd0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042efd6:
        push ecx
    L_0042efd7:
        mov edx,esi
    L_0042efd9:
        call asm_AnimationManager_Find_004491c0
    L_0042efde:
        cmp eax,ebx
    L_0042efe0:
        jne short L_0042efe8
    L_0042efe2:
        mov dword ptr [edi+2C8h],ebx
    L_0042efe8:
        add eax,10h
    L_0042efeb:
        cmp eax,ebx
    L_0042efed:
        je short L_0042f006
    L_0042efef:
        nop
    L_0042eff0:
        mov edx,dword ptr [eax]
    L_0042eff2:
        cmp word ptr [edx+38Ah],bp
    L_0042eff9:
        je asm_target_0042f206
    L_0042efff:
        mov eax,dword ptr [eax+4]
    L_0042f002:
        cmp eax,ebx
    L_0042f004:
        jne short L_0042eff0
    L_0042f006:
        xor eax,eax
    L_0042f008:
        push eax
    L_0042f009:
        mov edx,esi
    L_0042f00b:
        call asm_AnimationManager_Find_004491c0
    L_0042f010:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f016:
        add eax,35Ch
    L_0042f01b:
        or ebp,2
    L_0042f01e:
        mov dword ptr [eax],ebp
    L_0042f020:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f026:
        push ecx
    L_0042f027:
        mov edx,esi
    L_0042f029:
        call asm_AnimationManager_Find_004491c0
    L_0042f02e:
        cmp eax,ebx
    L_0042f030:
        jne short L_0042f038
    L_0042f032:
        mov dword ptr [edi+2C8h],ebx
    L_0042f038:
        add eax,10h
    L_0042f03b:
        cmp eax,ebx
    L_0042f03d:
        TH10_REL8(0x74, 0x0042f03d, VA_asm_target_0042f066)
    L_0042f03f:
        mov ecx,2Ah
    L_0042f044:
        TH10_REL8(0xeb, 0x0042f044, VA_asm_FUN_0042e5a0_part_0042f050)
    }
}

// 0x0042F050..0x0042F106: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f050() {
    __asm {
    L_0042f050:
        mov edx,dword ptr [eax]
    L_0042f052:
        cmp word ptr [edx+38Ah],cx
    L_0042f059:
        je asm_target_0042ef13
    L_0042f05f:
        mov eax,dword ptr [eax+4]
    L_0042f062:
        cmp eax,ebx
    L_0042f064:
        jne short L_0042f050
    L_0042f066:
        xor eax,eax
    L_0042f068:
        mov edx,esi
    L_0042f06a:
        push eax
    L_0042f06b:
        call asm_AnimationManager_Find_004491c0
    L_0042f070:
        mov ecx,dword ptr [eax+35Ch]
    L_0042f076:
        add eax,35Ch
    L_0042f07b:
        or ecx,2
    L_0042f07e:
        mov dword ptr [eax],ecx
    L_0042f080:
        mov al,byte ptr [data_00491d69]
    L_0042f085:
        cmp al,0Ah
    L_0042f087:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f08d:
        mov edx,esi
    L_0042f08f:
        push ecx
    L_0042f090:
        jge asm_target_0042f230
    L_0042f096:
        call asm_AnimationManager_Find_004491c0
    L_0042f09b:
        cmp eax,ebx
    L_0042f09d:
        jne short L_0042f0a5
    L_0042f09f:
        mov dword ptr [edi+2C8h],ebx
    L_0042f0a5:
        add eax,10h
    L_0042f0a8:
        cmp eax,ebx
    L_0042f0aa:
        je short L_0042f0c7
    L_0042f0ac:
        mov ecx,2Dh
    L_0042f0b1:
        mov edx,dword ptr [eax]
    L_0042f0b3:
        cmp word ptr [edx+38Ah],cx
    L_0042f0ba:
        je asm_target_0042f20f
    L_0042f0c0:
        mov eax,dword ptr [eax+4]
    L_0042f0c3:
        cmp eax,ebx
    L_0042f0c5:
        jne short L_0042f0b1
    L_0042f0c7:
        xor eax,eax
    L_0042f0c9:
        push eax
    L_0042f0ca:
        mov edx,esi
    L_0042f0cc:
        call asm_AnimationManager_Find_004491c0
    L_0042f0d1:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f0d7:
        add eax,35Ch
    L_0042f0dc:
        and ebp,0FFFFFFFDh
    L_0042f0df:
        mov dword ptr [eax],ebp
    L_0042f0e1:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f0e7:
        push ecx
    L_0042f0e8:
        mov edx,esi
    L_0042f0ea:
        call asm_AnimationManager_Find_004491c0
    L_0042f0ef:
        cmp eax,ebx
    L_0042f0f1:
        jne short L_0042f0f9
    L_0042f0f3:
        mov dword ptr [edi+2C8h],ebx
    L_0042f0f9:
        add eax,10h
    L_0042f0fc:
        cmp eax,ebx
    L_0042f0fe:
        TH10_REL8(0x74, 0x0042f0fe, VA_asm_target_0042f126)
    L_0042f100:
        mov ecx,2Eh
    L_0042f105:
        TH10_REL8(0xeb, 0x0042f105, VA_asm_FUN_0042e5a0_part_0042f110)
    }
}

// 0x0042F110..0x0042F165: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f110() {
    __asm {
    L_0042f110:
        mov edx,dword ptr [eax]
    L_0042f112:
        cmp word ptr [edx+38Ah],cx
    L_0042f119:
        je asm_target_0042f218
    L_0042f11f:
        mov eax,dword ptr [eax+4]
    L_0042f122:
        cmp eax,ebx
    L_0042f124:
        jne short L_0042f110
    L_0042f126:
        xor eax,eax
    L_0042f128:
        push eax
    L_0042f129:
        mov edx,esi
    L_0042f12b:
        call asm_AnimationManager_Find_004491c0
    L_0042f130:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f136:
        add eax,35Ch
    L_0042f13b:
        and ebp,0FFFFFFFDh
    L_0042f13e:
        mov dword ptr [eax],ebp
    L_0042f140:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f146:
        push ecx
    L_0042f147:
        mov edx,esi
    L_0042f149:
        call asm_AnimationManager_Find_004491c0
    L_0042f14e:
        cmp eax,ebx
    L_0042f150:
        jne short L_0042f158
    L_0042f152:
        mov dword ptr [edi+2C8h],ebx
    L_0042f158:
        add eax,10h
    L_0042f15b:
        cmp eax,ebx
    L_0042f15d:
        TH10_REL8(0x74, 0x0042f15d, VA_asm_target_0042f186)
    L_0042f15f:
        mov ecx,31h
    L_0042f164:
        TH10_REL8(0xeb, 0x0042f164, VA_asm_FUN_0042e5a0_part_0042f170)
    }
}

// 0x0042F170..0x0042F254: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f170() {
    __asm {
    L_0042f170:
        mov edx,dword ptr [eax]
    L_0042f172:
        cmp word ptr [edx+38Ah],cx
    L_0042f179:
        je asm_target_0042f221
    L_0042f17f:
        mov eax,dword ptr [eax+4]
    L_0042f182:
        cmp eax,ebx
    L_0042f184:
        jne short L_0042f170
    L_0042f186:
        xor eax,eax
    L_0042f188:
        push eax
    L_0042f189:
        mov edx,esi
    L_0042f18b:
        call asm_AnimationManager_Find_004491c0
    L_0042f190:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f196:
        add eax,35Ch
    L_0042f19b:
        and ebp,0FFFFFFFDh
    L_0042f19e:
        mov dword ptr [eax],ebp
    L_0042f1a0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f1a6:
        push ecx
    L_0042f1a7:
        mov edx,esi
    L_0042f1a9:
        call asm_AnimationManager_Find_004491c0
    L_0042f1ae:
        cmp eax,ebx
    L_0042f1b0:
        jne short L_0042f1b8
    L_0042f1b2:
        mov dword ptr [edi+2C8h],ebx
    L_0042f1b8:
        add eax,10h
    L_0042f1bb:
        cmp eax,ebx
    L_0042f1bd:
        je short L_0042f1d6
    L_0042f1bf:
        mov ecx,32h
    L_0042f1c4:
        mov edx,dword ptr [eax]
    L_0042f1c6:
        cmp word ptr [edx+38Ah],cx
    L_0042f1cd:
        je short L_0042f22a
    L_0042f1cf:
        mov eax,dword ptr [eax+4]
    L_0042f1d2:
        cmp eax,ebx
    L_0042f1d4:
        jne short L_0042f1c4
    L_0042f1d6:
        xor eax,eax
    L_0042f1d8:
        push eax
    L_0042f1d9:
        mov edx,esi
    L_0042f1db:
        call asm_AnimationManager_Find_004491c0
    L_0042f1e0:
        mov ecx,dword ptr [eax+35Ch]
    L_0042f1e6:
        add eax,35Ch
    L_0042f1eb:
        pop esi
    L_0042f1ec:
        and ecx,0FFFFFFFDh
    L_0042f1ef:
        pop ebp
    L_0042f1f0:
        mov dword ptr [eax],ecx
    L_0042f1f2:
        pop ebx
    L_0042f1f3:
        ret
    L_0042f1f4:
        mov eax,dword ptr [eax]
    L_0042f1f6:
        mov eax,dword ptr [eax]
    L_0042f1f8:
        jmp asm_target_0042ef58
    L_0042f1fd:
        mov eax,dword ptr [eax]
    L_0042f1ff:
        mov eax,dword ptr [eax]
    L_0042f201:
        jmp asm_target_0042efb8
    L_0042f206:
        mov eax,dword ptr [eax]
    L_0042f208:
        mov eax,dword ptr [eax]
    L_0042f20a:
        jmp asm_target_0042f008
    L_0042f20f:
        mov eax,dword ptr [eax]
    L_0042f211:
        mov eax,dword ptr [eax]
    L_0042f213:
        jmp asm_target_0042f0c9
    L_0042f218:
        mov eax,dword ptr [eax]
    L_0042f21a:
        mov eax,dword ptr [eax]
    L_0042f21c:
        jmp asm_target_0042f128
    L_0042f221:
        mov eax,dword ptr [eax]
    L_0042f223:
        mov eax,dword ptr [eax]
    L_0042f225:
        jmp asm_target_0042f188
    L_0042f22a:
        mov eax,dword ptr [eax]
    L_0042f22c:
        mov eax,dword ptr [eax]
    L_0042f22e:
        jmp short L_0042f1d8
    L_0042f230:
        cmp al,64h
    L_0042f232:
        jge asm_target_0042f3a8
    L_0042f238:
        call asm_AnimationManager_Find_004491c0
    L_0042f23d:
        cmp eax,ebx
    L_0042f23f:
        jne short L_0042f247
    L_0042f241:
        mov dword ptr [edi+2C8h],ebx
    L_0042f247:
        add eax,10h
    L_0042f24a:
        cmp eax,ebx
    L_0042f24c:
        TH10_REL8(0x74, 0x0042f24c, VA_asm_target_0042f276)
    L_0042f24e:
        mov ecx,2Dh
    L_0042f253:
        TH10_REL8(0xeb, 0x0042f253, VA_asm_FUN_0042e5a0_part_0042f260)
    }
}

// 0x0042F260..0x0042F2B5: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f260() {
    __asm {
    L_0042f260:
        mov edx,dword ptr [eax]
    L_0042f262:
        cmp word ptr [edx+38Ah],cx
    L_0042f269:
        je asm_target_0042f387
    L_0042f26f:
        mov eax,dword ptr [eax+4]
    L_0042f272:
        cmp eax,ebx
    L_0042f274:
        jne short L_0042f260
    L_0042f276:
        xor eax,eax
    L_0042f278:
        push eax
    L_0042f279:
        mov edx,esi
    L_0042f27b:
        call asm_AnimationManager_Find_004491c0
    L_0042f280:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f286:
        add eax,35Ch
    L_0042f28b:
        and ebp,0FFFFFFFDh
    L_0042f28e:
        mov dword ptr [eax],ebp
    L_0042f290:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f296:
        push ecx
    L_0042f297:
        mov edx,esi
    L_0042f299:
        call asm_AnimationManager_Find_004491c0
    L_0042f29e:
        cmp eax,ebx
    L_0042f2a0:
        jne short L_0042f2a8
    L_0042f2a2:
        mov dword ptr [edi+2C8h],ebx
    L_0042f2a8:
        add eax,10h
    L_0042f2ab:
        cmp eax,ebx
    L_0042f2ad:
        TH10_REL8(0x74, 0x0042f2ad, VA_asm_target_0042f2d6)
    L_0042f2af:
        mov ecx,2Eh
    L_0042f2b4:
        TH10_REL8(0xeb, 0x0042f2b4, VA_asm_FUN_0042e5a0_part_0042f2c0)
    }
}

// 0x0042F2C0..0x0042F369: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f2c0() {
    __asm {
    L_0042f2c0:
        mov edx,dword ptr [eax]
    L_0042f2c2:
        cmp word ptr [edx+38Ah],cx
    L_0042f2c9:
        je asm_target_0042f390
    L_0042f2cf:
        mov eax,dword ptr [eax+4]
    L_0042f2d2:
        cmp eax,ebx
    L_0042f2d4:
        jne short L_0042f2c0
    L_0042f2d6:
        xor eax,eax
    L_0042f2d8:
        push eax
    L_0042f2d9:
        mov edx,esi
    L_0042f2db:
        call asm_AnimationManager_Find_004491c0
    L_0042f2e0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f2e6:
        add eax,35Ch
    L_0042f2eb:
        or ebp,2
    L_0042f2ee:
        mov dword ptr [eax],ebp
    L_0042f2f0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f2f6:
        push ecx
    L_0042f2f7:
        mov edx,esi
    L_0042f2f9:
        call asm_AnimationManager_Find_004491c0
    L_0042f2fe:
        cmp eax,ebx
    L_0042f300:
        jne short L_0042f308
    L_0042f302:
        mov dword ptr [edi+2C8h],ebx
    L_0042f308:
        add eax,10h
    L_0042f30b:
        cmp eax,ebx
    L_0042f30d:
        je short L_0042f326
    L_0042f30f:
        mov ecx,31h
    L_0042f314:
        mov edx,dword ptr [eax]
    L_0042f316:
        cmp word ptr [edx+38Ah],cx
    L_0042f31d:
        TH10_REL8(0x74, 0x0042f31d, VA_asm_target_0042f399)
    L_0042f31f:
        mov eax,dword ptr [eax+4]
    L_0042f322:
        cmp eax,ebx
    L_0042f324:
        jne short L_0042f314
    L_0042f326:
        xor eax,eax
    L_0042f328:
        push eax
    L_0042f329:
        mov edx,esi
    L_0042f32b:
        call asm_AnimationManager_Find_004491c0
    L_0042f330:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f336:
        add eax,35Ch
    L_0042f33b:
        and ebp,0FFFFFFFDh
    L_0042f33e:
        mov dword ptr [eax],ebp
    L_0042f340:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f346:
        push ecx
    L_0042f347:
        mov edx,esi
    L_0042f349:
        call asm_AnimationManager_Find_004491c0
    L_0042f34e:
        cmp eax,ebx
    L_0042f350:
        jne short L_0042f358
    L_0042f352:
        mov dword ptr [edi+2C8h],ebx
    L_0042f358:
        add eax,10h
    L_0042f35b:
        cmp eax,ebx
    L_0042f35d:
        je asm_target_0042f506
    L_0042f363:
        mov ecx,32h
    L_0042f368:
        TH10_REL8(0xeb, 0x0042f368, VA_asm_FUN_0042e5a0_part_0042f370)
    }
}

// 0x0042F370..0x0042F3C4: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f370() {
    __asm {
    L_0042f370:
        mov edx,dword ptr [eax]
    L_0042f372:
        cmp word ptr [edx+38Ah],cx
    L_0042f379:
        je short L_0042f39f
    L_0042f37b:
        mov eax,dword ptr [eax+4]
    L_0042f37e:
        cmp eax,ebx
    L_0042f380:
        jne short L_0042f370
    L_0042f382:
        jmp asm_target_0042f506
    L_0042f387:
        mov eax,dword ptr [eax]
    L_0042f389:
        mov eax,dword ptr [eax]
    L_0042f38b:
        jmp asm_target_0042f278
    L_0042f390:
        mov eax,dword ptr [eax]
    L_0042f392:
        mov eax,dword ptr [eax]
    L_0042f394:
        jmp asm_target_0042f2d8
    L_0042f399:
        mov eax,dword ptr [eax]
    L_0042f39b:
        mov eax,dword ptr [eax]
    L_0042f39d:
        TH10_REL8(0xeb, 0x0042f39d, VA_asm_target_0042f328)
    L_0042f39f:
        mov eax,dword ptr [eax]
    L_0042f3a1:
        mov eax,dword ptr [eax]
    L_0042f3a3:
        jmp asm_target_0042f508
    L_0042f3a8:
        call asm_AnimationManager_Find_004491c0
    L_0042f3ad:
        cmp eax,ebx
    L_0042f3af:
        jne short L_0042f3b7
    L_0042f3b1:
        mov dword ptr [edi+2C8h],ebx
    L_0042f3b7:
        add eax,10h
    L_0042f3ba:
        cmp eax,ebx
    L_0042f3bc:
        TH10_REL8(0x74, 0x0042f3bc, VA_asm_target_0042f3e6)
    L_0042f3be:
        mov ecx,2Dh
    L_0042f3c3:
        TH10_REL8(0xeb, 0x0042f3c3, VA_asm_FUN_0042e5a0_part_0042f3d0)
    }
}

// 0x0042F3D0..0x0042F425: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f3d0() {
    __asm {
    L_0042f3d0:
        mov edx,dword ptr [eax]
    L_0042f3d2:
        cmp word ptr [edx+38Ah],cx
    L_0042f3d9:
        je asm_target_0042f524
    L_0042f3df:
        mov eax,dword ptr [eax+4]
    L_0042f3e2:
        cmp eax,ebx
    L_0042f3e4:
        jne short L_0042f3d0
    L_0042f3e6:
        xor eax,eax
    L_0042f3e8:
        push eax
    L_0042f3e9:
        mov edx,esi
    L_0042f3eb:
        call asm_AnimationManager_Find_004491c0
    L_0042f3f0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f3f6:
        add eax,35Ch
    L_0042f3fb:
        or ebp,2
    L_0042f3fe:
        mov dword ptr [eax],ebp
    L_0042f400:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f406:
        push ecx
    L_0042f407:
        mov edx,esi
    L_0042f409:
        call asm_AnimationManager_Find_004491c0
    L_0042f40e:
        cmp eax,ebx
    L_0042f410:
        jne short L_0042f418
    L_0042f412:
        mov dword ptr [edi+2C8h],ebx
    L_0042f418:
        add eax,10h
    L_0042f41b:
        cmp eax,ebx
    L_0042f41d:
        TH10_REL8(0x74, 0x0042f41d, VA_asm_target_0042f446)
    L_0042f41f:
        mov ecx,2Eh
    L_0042f424:
        TH10_REL8(0xeb, 0x0042f424, VA_asm_FUN_0042e5a0_part_0042f430)
    }
}

// 0x0042F430..0x0042F485: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f430() {
    __asm {
    L_0042f430:
        mov edx,dword ptr [eax]
    L_0042f432:
        cmp word ptr [edx+38Ah],cx
    L_0042f439:
        je asm_target_0042f52d
    L_0042f43f:
        mov eax,dword ptr [eax+4]
    L_0042f442:
        cmp eax,ebx
    L_0042f444:
        jne short L_0042f430
    L_0042f446:
        xor eax,eax
    L_0042f448:
        push eax
    L_0042f449:
        mov edx,esi
    L_0042f44b:
        call asm_AnimationManager_Find_004491c0
    L_0042f450:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f456:
        add eax,35Ch
    L_0042f45b:
        or ebp,2
    L_0042f45e:
        mov dword ptr [eax],ebp
    L_0042f460:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f466:
        push ecx
    L_0042f467:
        mov edx,esi
    L_0042f469:
        call asm_AnimationManager_Find_004491c0
    L_0042f46e:
        cmp eax,ebx
    L_0042f470:
        jne short L_0042f478
    L_0042f472:
        mov dword ptr [edi+2C8h],ebx
    L_0042f478:
        add eax,10h
    L_0042f47b:
        cmp eax,ebx
    L_0042f47d:
        TH10_REL8(0x74, 0x0042f47d, VA_asm_target_0042f4a6)
    L_0042f47f:
        mov ecx,31h
    L_0042f484:
        TH10_REL8(0xeb, 0x0042f484, VA_asm_FUN_0042e5a0_part_0042f490)
    }
}

// 0x0042F490..0x0042F4E5: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f490() {
    __asm {
    L_0042f490:
        mov edx,dword ptr [eax]
    L_0042f492:
        cmp word ptr [edx+38Ah],cx
    L_0042f499:
        je asm_target_0042f536
    L_0042f49f:
        mov eax,dword ptr [eax+4]
    L_0042f4a2:
        cmp eax,ebx
    L_0042f4a4:
        jne short L_0042f490
    L_0042f4a6:
        xor eax,eax
    L_0042f4a8:
        push eax
    L_0042f4a9:
        mov edx,esi
    L_0042f4ab:
        call asm_AnimationManager_Find_004491c0
    L_0042f4b0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f4b6:
        add eax,35Ch
    L_0042f4bb:
        or ebp,2
    L_0042f4be:
        mov dword ptr [eax],ebp
    L_0042f4c0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f4c6:
        push ecx
    L_0042f4c7:
        mov edx,esi
    L_0042f4c9:
        call asm_AnimationManager_Find_004491c0
    L_0042f4ce:
        cmp eax,ebx
    L_0042f4d0:
        jne short L_0042f4d8
    L_0042f4d2:
        mov dword ptr [edi+2C8h],ebx
    L_0042f4d8:
        add eax,10h
    L_0042f4db:
        cmp eax,ebx
    L_0042f4dd:
        TH10_REL8(0x74, 0x0042f4dd, VA_asm_target_0042f506)
    L_0042f4df:
        mov ecx,32h
    L_0042f4e4:
        TH10_REL8(0xeb, 0x0042f4e4, VA_asm_FUN_0042e5a0_part_0042f4f0)
    }
}

// 0x0042F4F0..0x0042F53E: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_part_0042f4f0() {
    __asm {
    L_0042f4f0:
        mov edx,dword ptr [eax]
    L_0042f4f2:
        cmp word ptr [edx+38Ah],cx
    L_0042f4f9:
        je asm_target_0042f39f
    L_0042f4ff:
        mov eax,dword ptr [eax+4]
    L_0042f502:
        cmp eax,ebx
    L_0042f504:
        jne short L_0042f4f0
    L_0042f506:
        xor eax,eax
    L_0042f508:
        mov edx,esi
    L_0042f50a:
        push eax
    L_0042f50b:
        call asm_AnimationManager_Find_004491c0
    L_0042f510:
        mov ecx,dword ptr [eax+35Ch]
    L_0042f516:
        add eax,35Ch
    L_0042f51b:
        pop esi
    L_0042f51c:
        or ecx,2
    L_0042f51f:
        pop ebp
    L_0042f520:
        mov dword ptr [eax],ecx
    L_0042f522:
        pop ebx
    L_0042f523:
        ret
    L_0042f524:
        mov eax,dword ptr [eax]
    L_0042f526:
        mov eax,dword ptr [eax]
    L_0042f528:
        jmp asm_target_0042f3e8
    L_0042f52d:
        mov eax,dword ptr [eax]
    L_0042f52f:
        mov eax,dword ptr [eax]
    L_0042f531:
        jmp asm_target_0042f448
    L_0042f536:
        mov eax,dword ptr [eax]
    L_0042f538:
        mov eax,dword ptr [eax]
    L_0042f53a:
        jmp asm_target_0042f4a8
    }
}

// 0x0042F8B0..0x0042F953: FUN_0042f8b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042f8b0_0042f8b0() {
    __asm {
    L_0042f8b0:
        push ebx
    L_0042f8b1:
        push esi
    L_0042f8b2:
        push edi
    L_0042f8b3:
        mov edi,dword ptr [data_00491c10]
    L_0042f8b9:
        mov esi,eax
    L_0042f8bb:
        mov eax,dword ptr [esi+2CCh]
    L_0042f8c1:
        push eax
    L_0042f8c2:
        mov edx,edi
    L_0042f8c4:
        call asm_AnimationManager_Find_004491c0
    L_0042f8c9:
        xor ebx,ebx
    L_0042f8cb:
        cmp eax,ebx
    L_0042f8cd:
        jne short L_0042f8d5
    L_0042f8cf:
        mov dword ptr [esi+2CCh],ebx
    L_0042f8d5:
        add eax,10h
    L_0042f8d8:
        cmp eax,ebx
    L_0042f8da:
        je short L_0042f8f7
    L_0042f8dc:
        mov ecx,43h
    L_0042f8e1:
        mov edx,dword ptr [eax]
    L_0042f8e3:
        cmp word ptr [edx+38Ah],cx
    L_0042f8ea:
        je asm_target_0043018d
    L_0042f8f0:
        mov eax,dword ptr [eax+4]
    L_0042f8f3:
        cmp eax,ebx
    L_0042f8f5:
        jne short L_0042f8e1
    L_0042f8f7:
        xor eax,eax
    L_0042f8f9:
        push eax
    L_0042f8fa:
        mov edx,edi
    L_0042f8fc:
        call asm_AnimationManager_Find_004491c0
    L_0042f901:
        mov ecx,eax
    L_0042f903:
        cmp ecx,ebx
    L_0042f905:
        je short L_0042f92e
    L_0042f907:
        movsx edx,word ptr [esi+59CCh]
    L_0042f90e:
        mov eax,66666667h
    L_0042f913:
        imul edx
    L_0042f915:
        sar edx,2
    L_0042f918:
        mov eax,edx
    L_0042f91a:
        shr eax,1Fh
    L_0042f91d:
        lea edx,[edx+eax+33h]
    L_0042f921:
        mov eax,ecx
    L_0042f923:
        mov ecx,dword ptr [ecx+308h]
    L_0042f929:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042f92e:
        mov ecx,dword ptr [esi+2CCh]
    L_0042f934:
        push ecx
    L_0042f935:
        mov edx,edi
    L_0042f937:
        call asm_AnimationManager_Find_004491c0
    L_0042f93c:
        cmp eax,ebx
    L_0042f93e:
        jne short L_0042f946
    L_0042f940:
        mov dword ptr [esi+2CCh],ebx
    L_0042f946:
        add eax,10h
    L_0042f949:
        cmp eax,ebx
    L_0042f94b:
        TH10_REL8(0x74, 0x0042f94b, VA_asm_target_0042f976)
    L_0042f94d:
        mov ecx,44h
    L_0042f952:
        TH10_REL8(0xeb, 0x0042f952, VA_asm_FUN_0042f8b0_part_0042f960)
    }
}

// 0x0042F960..0x004300CC: FUN_0042f8b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042f8b0_part_0042f960() {
    __asm {
    L_0042f960:
        mov edx,dword ptr [eax]
    L_0042f962:
        cmp word ptr [edx+38Ah],cx
    L_0042f969:
        je asm_target_00430196
    L_0042f96f:
        mov eax,dword ptr [eax+4]
    L_0042f972:
        cmp eax,ebx
    L_0042f974:
        jne short L_0042f960
    L_0042f976:
        xor eax,eax
    L_0042f978:
        push ebp
    L_0042f979:
        push eax
    L_0042f97a:
        mov edx,edi
    L_0042f97c:
        call asm_AnimationManager_Find_004491c0
    L_0042f981:
        mov ecx,eax
    L_0042f983:
        cmp ecx,ebx
    L_0042f985:
        je short L_0042f9a6
    L_0042f987:
        movsx eax,word ptr [esi+59CCh]
    L_0042f98e:
        cdq
    L_0042f98f:
        mov ebp,0Ah
    L_0042f994:
        idiv ebp
    L_0042f996:
        mov eax,ecx
    L_0042f998:
        mov ecx,dword ptr [ecx+308h]
    L_0042f99e:
        add edx,33h
    L_0042f9a1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042f9a6:
        mov ecx,dword ptr [esi+2CCh]
    L_0042f9ac:
        push ecx
    L_0042f9ad:
        mov edx,edi
    L_0042f9af:
        call asm_AnimationManager_Find_004491c0
    L_0042f9b4:
        cmp eax,ebx
    L_0042f9b6:
        jne short L_0042f9be
    L_0042f9b8:
        mov dword ptr [esi+2CCh],ebx
    L_0042f9be:
        add eax,10h
    L_0042f9c1:
        cmp eax,ebx
    L_0042f9c3:
        je short L_0042f9e6
    L_0042f9c5:
        mov ecx,4Dh
    L_0042f9ca:
        lea ebx,[ebx+force_disp32_zero]
    L_0042f9d0:
        mov edx,dword ptr [eax]
    L_0042f9d2:
        cmp word ptr [edx+38Ah],cx
    L_0042f9d9:
        je asm_target_0043019f
    L_0042f9df:
        mov eax,dword ptr [eax+4]
    L_0042f9e2:
        cmp eax,ebx
    L_0042f9e4:
        jne short L_0042f9d0
    L_0042f9e6:
        xor eax,eax
    L_0042f9e8:
        push eax
    L_0042f9e9:
        mov edx,edi
    L_0042f9eb:
        call asm_AnimationManager_Find_004491c0
    L_0042f9f0:
        mov ecx,eax
    L_0042f9f2:
        cmp ecx,ebx
    L_0042f9f4:
        je short L_0042fa1d
    L_0042f9f6:
        movsx edx,word ptr [esi+59CCh]
    L_0042f9fd:
        mov eax,66666667h
    L_0042fa02:
        imul edx
    L_0042fa04:
        sar edx,2
    L_0042fa07:
        mov eax,edx
    L_0042fa09:
        shr eax,1Fh
    L_0042fa0c:
        lea edx,[edx+eax+33h]
    L_0042fa10:
        mov eax,ecx
    L_0042fa12:
        mov ecx,dword ptr [ecx+308h]
    L_0042fa18:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fa1d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fa23:
        push ecx
    L_0042fa24:
        mov edx,edi
    L_0042fa26:
        call asm_AnimationManager_Find_004491c0
    L_0042fa2b:
        cmp eax,ebx
    L_0042fa2d:
        jne short L_0042fa35
    L_0042fa2f:
        mov dword ptr [esi+2CCh],ebx
    L_0042fa35:
        add eax,10h
    L_0042fa38:
        cmp eax,ebx
    L_0042fa3a:
        je short L_0042fa57
    L_0042fa3c:
        mov ecx,4Eh
    L_0042fa41:
        mov edx,dword ptr [eax]
    L_0042fa43:
        cmp word ptr [edx+38Ah],cx
    L_0042fa4a:
        je asm_target_004301a8
    L_0042fa50:
        mov eax,dword ptr [eax+4]
    L_0042fa53:
        cmp eax,ebx
    L_0042fa55:
        jne short L_0042fa41
    L_0042fa57:
        xor eax,eax
    L_0042fa59:
        push eax
    L_0042fa5a:
        mov edx,edi
    L_0042fa5c:
        call asm_AnimationManager_Find_004491c0
    L_0042fa61:
        mov ecx,eax
    L_0042fa63:
        cmp ecx,ebx
    L_0042fa65:
        je short L_0042fa86
    L_0042fa67:
        movsx eax,word ptr [esi+59CCh]
    L_0042fa6e:
        cdq
    L_0042fa6f:
        mov ebp,0Ah
    L_0042fa74:
        idiv ebp
    L_0042fa76:
        mov eax,ecx
    L_0042fa78:
        mov ecx,dword ptr [ecx+308h]
    L_0042fa7e:
        add edx,33h
    L_0042fa81:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fa86:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fa8c:
        push ecx
    L_0042fa8d:
        mov edx,edi
    L_0042fa8f:
        call asm_AnimationManager_Find_004491c0
    L_0042fa94:
        cmp eax,ebx
    L_0042fa96:
        jne short L_0042fa9e
    L_0042fa98:
        mov dword ptr [esi+2CCh],ebx
    L_0042fa9e:
        add eax,10h
    L_0042faa1:
        cmp eax,ebx
    L_0042faa3:
        je short L_0042fac6
    L_0042faa5:
        mov ecx,45h
    L_0042faaa:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fab0:
        mov edx,dword ptr [eax]
    L_0042fab2:
        cmp word ptr [edx+38Ah],cx
    L_0042fab9:
        je asm_target_004301b1
    L_0042fabf:
        mov eax,dword ptr [eax+4]
    L_0042fac2:
        cmp eax,ebx
    L_0042fac4:
        jne short L_0042fab0
    L_0042fac6:
        xor eax,eax
    L_0042fac8:
        push eax
    L_0042fac9:
        mov edx,edi
    L_0042facb:
        call asm_AnimationManager_Find_004491c0
    L_0042fad0:
        mov ecx,eax
    L_0042fad2:
        cmp ecx,ebx
    L_0042fad4:
        je short L_0042fafd
    L_0042fad6:
        movsx edx,word ptr [esi+59CEh]
    L_0042fadd:
        mov eax,66666667h
    L_0042fae2:
        imul edx
    L_0042fae4:
        sar edx,2
    L_0042fae7:
        mov eax,edx
    L_0042fae9:
        shr eax,1Fh
    L_0042faec:
        lea edx,[edx+eax+33h]
    L_0042faf0:
        mov eax,ecx
    L_0042faf2:
        mov ecx,dword ptr [ecx+308h]
    L_0042faf8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fafd:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fb03:
        push ecx
    L_0042fb04:
        mov edx,edi
    L_0042fb06:
        call asm_AnimationManager_Find_004491c0
    L_0042fb0b:
        cmp eax,ebx
    L_0042fb0d:
        jne short L_0042fb15
    L_0042fb0f:
        mov dword ptr [esi+2CCh],ebx
    L_0042fb15:
        add eax,10h
    L_0042fb18:
        cmp eax,ebx
    L_0042fb1a:
        je short L_0042fb37
    L_0042fb1c:
        mov ecx,46h
    L_0042fb21:
        mov edx,dword ptr [eax]
    L_0042fb23:
        cmp word ptr [edx+38Ah],cx
    L_0042fb2a:
        je asm_target_004301ba
    L_0042fb30:
        mov eax,dword ptr [eax+4]
    L_0042fb33:
        cmp eax,ebx
    L_0042fb35:
        jne short L_0042fb21
    L_0042fb37:
        xor eax,eax
    L_0042fb39:
        push eax
    L_0042fb3a:
        mov edx,edi
    L_0042fb3c:
        call asm_AnimationManager_Find_004491c0
    L_0042fb41:
        mov ecx,eax
    L_0042fb43:
        cmp ecx,ebx
    L_0042fb45:
        je short L_0042fb66
    L_0042fb47:
        movsx eax,word ptr [esi+59CEh]
    L_0042fb4e:
        cdq
    L_0042fb4f:
        mov ebp,0Ah
    L_0042fb54:
        idiv ebp
    L_0042fb56:
        mov eax,ecx
    L_0042fb58:
        mov ecx,dword ptr [ecx+308h]
    L_0042fb5e:
        add edx,33h
    L_0042fb61:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fb66:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fb6c:
        push ecx
    L_0042fb6d:
        mov edx,edi
    L_0042fb6f:
        call asm_AnimationManager_Find_004491c0
    L_0042fb74:
        cmp eax,ebx
    L_0042fb76:
        jne short L_0042fb7e
    L_0042fb78:
        mov dword ptr [esi+2CCh],ebx
    L_0042fb7e:
        add eax,10h
    L_0042fb81:
        cmp eax,ebx
    L_0042fb83:
        je short L_0042fba6
    L_0042fb85:
        mov ecx,4Fh
    L_0042fb8a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fb90:
        mov edx,dword ptr [eax]
    L_0042fb92:
        cmp word ptr [edx+38Ah],cx
    L_0042fb99:
        je asm_target_004301c3
    L_0042fb9f:
        mov eax,dword ptr [eax+4]
    L_0042fba2:
        cmp eax,ebx
    L_0042fba4:
        jne short L_0042fb90
    L_0042fba6:
        xor eax,eax
    L_0042fba8:
        push eax
    L_0042fba9:
        mov edx,edi
    L_0042fbab:
        call asm_AnimationManager_Find_004491c0
    L_0042fbb0:
        mov ecx,eax
    L_0042fbb2:
        cmp ecx,ebx
    L_0042fbb4:
        je short L_0042fbdd
    L_0042fbb6:
        movsx edx,word ptr [esi+59CEh]
    L_0042fbbd:
        mov eax,66666667h
    L_0042fbc2:
        imul edx
    L_0042fbc4:
        sar edx,2
    L_0042fbc7:
        mov eax,edx
    L_0042fbc9:
        shr eax,1Fh
    L_0042fbcc:
        lea edx,[edx+eax+33h]
    L_0042fbd0:
        mov eax,ecx
    L_0042fbd2:
        mov ecx,dword ptr [ecx+308h]
    L_0042fbd8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fbdd:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fbe3:
        push ecx
    L_0042fbe4:
        mov edx,edi
    L_0042fbe6:
        call asm_AnimationManager_Find_004491c0
    L_0042fbeb:
        cmp eax,ebx
    L_0042fbed:
        jne short L_0042fbf5
    L_0042fbef:
        mov dword ptr [esi+2CCh],ebx
    L_0042fbf5:
        add eax,10h
    L_0042fbf8:
        cmp eax,ebx
    L_0042fbfa:
        je short L_0042fc17
    L_0042fbfc:
        mov ecx,50h
    L_0042fc01:
        mov edx,dword ptr [eax]
    L_0042fc03:
        cmp word ptr [edx+38Ah],cx
    L_0042fc0a:
        je asm_target_004301cc
    L_0042fc10:
        mov eax,dword ptr [eax+4]
    L_0042fc13:
        cmp eax,ebx
    L_0042fc15:
        jne short L_0042fc01
    L_0042fc17:
        xor eax,eax
    L_0042fc19:
        push eax
    L_0042fc1a:
        mov edx,edi
    L_0042fc1c:
        call asm_AnimationManager_Find_004491c0
    L_0042fc21:
        mov ecx,eax
    L_0042fc23:
        cmp ecx,ebx
    L_0042fc25:
        je short L_0042fc46
    L_0042fc27:
        movsx eax,word ptr [esi+59CEh]
    L_0042fc2e:
        cdq
    L_0042fc2f:
        mov ebp,0Ah
    L_0042fc34:
        idiv ebp
    L_0042fc36:
        mov eax,ecx
    L_0042fc38:
        mov ecx,dword ptr [ecx+308h]
    L_0042fc3e:
        add edx,33h
    L_0042fc41:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fc46:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fc4c:
        push ecx
    L_0042fc4d:
        mov edx,edi
    L_0042fc4f:
        call asm_AnimationManager_Find_004491c0
    L_0042fc54:
        cmp eax,ebx
    L_0042fc56:
        jne short L_0042fc5e
    L_0042fc58:
        mov dword ptr [esi+2CCh],ebx
    L_0042fc5e:
        add eax,10h
    L_0042fc61:
        cmp eax,ebx
    L_0042fc63:
        je short L_0042fc86
    L_0042fc65:
        mov ecx,47h
    L_0042fc6a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fc70:
        mov edx,dword ptr [eax]
    L_0042fc72:
        cmp word ptr [edx+38Ah],cx
    L_0042fc79:
        je asm_target_004301d5
    L_0042fc7f:
        mov eax,dword ptr [eax+4]
    L_0042fc82:
        cmp eax,ebx
    L_0042fc84:
        jne short L_0042fc70
    L_0042fc86:
        xor eax,eax
    L_0042fc88:
        push eax
    L_0042fc89:
        mov edx,edi
    L_0042fc8b:
        call asm_AnimationManager_Find_004491c0
    L_0042fc90:
        mov ecx,eax
    L_0042fc92:
        cmp ecx,ebx
    L_0042fc94:
        je short L_0042fcbd
    L_0042fc96:
        movsx edx,word ptr [esi+59D0h]
    L_0042fc9d:
        mov eax,66666667h
    L_0042fca2:
        imul edx
    L_0042fca4:
        sar edx,2
    L_0042fca7:
        mov eax,edx
    L_0042fca9:
        shr eax,1Fh
    L_0042fcac:
        lea edx,[edx+eax+33h]
    L_0042fcb0:
        mov eax,ecx
    L_0042fcb2:
        mov ecx,dword ptr [ecx+308h]
    L_0042fcb8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fcbd:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fcc3:
        push ecx
    L_0042fcc4:
        mov edx,edi
    L_0042fcc6:
        call asm_AnimationManager_Find_004491c0
    L_0042fccb:
        cmp eax,ebx
    L_0042fccd:
        jne short L_0042fcd5
    L_0042fccf:
        mov dword ptr [esi+2CCh],ebx
    L_0042fcd5:
        add eax,10h
    L_0042fcd8:
        cmp eax,ebx
    L_0042fcda:
        je short L_0042fcf7
    L_0042fcdc:
        mov ecx,48h
    L_0042fce1:
        mov edx,dword ptr [eax]
    L_0042fce3:
        cmp word ptr [edx+38Ah],cx
    L_0042fcea:
        je asm_target_004301de
    L_0042fcf0:
        mov eax,dword ptr [eax+4]
    L_0042fcf3:
        cmp eax,ebx
    L_0042fcf5:
        jne short L_0042fce1
    L_0042fcf7:
        xor eax,eax
    L_0042fcf9:
        push eax
    L_0042fcfa:
        mov edx,edi
    L_0042fcfc:
        call asm_AnimationManager_Find_004491c0
    L_0042fd01:
        mov ecx,eax
    L_0042fd03:
        cmp ecx,ebx
    L_0042fd05:
        je short L_0042fd26
    L_0042fd07:
        movsx eax,word ptr [esi+59D0h]
    L_0042fd0e:
        cdq
    L_0042fd0f:
        mov ebp,0Ah
    L_0042fd14:
        idiv ebp
    L_0042fd16:
        mov eax,ecx
    L_0042fd18:
        mov ecx,dword ptr [ecx+308h]
    L_0042fd1e:
        add edx,33h
    L_0042fd21:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fd26:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fd2c:
        push ecx
    L_0042fd2d:
        mov edx,edi
    L_0042fd2f:
        call asm_AnimationManager_Find_004491c0
    L_0042fd34:
        cmp eax,ebx
    L_0042fd36:
        jne short L_0042fd3e
    L_0042fd38:
        mov dword ptr [esi+2CCh],ebx
    L_0042fd3e:
        add eax,10h
    L_0042fd41:
        cmp eax,ebx
    L_0042fd43:
        je short L_0042fd66
    L_0042fd45:
        mov ecx,51h
    L_0042fd4a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fd50:
        mov edx,dword ptr [eax]
    L_0042fd52:
        cmp word ptr [edx+38Ah],cx
    L_0042fd59:
        je asm_target_004301e7
    L_0042fd5f:
        mov eax,dword ptr [eax+4]
    L_0042fd62:
        cmp eax,ebx
    L_0042fd64:
        jne short L_0042fd50
    L_0042fd66:
        xor eax,eax
    L_0042fd68:
        push eax
    L_0042fd69:
        mov edx,edi
    L_0042fd6b:
        call asm_AnimationManager_Find_004491c0
    L_0042fd70:
        mov ecx,eax
    L_0042fd72:
        cmp ecx,ebx
    L_0042fd74:
        je short L_0042fd9d
    L_0042fd76:
        movsx edx,word ptr [esi+59D0h]
    L_0042fd7d:
        mov eax,66666667h
    L_0042fd82:
        imul edx
    L_0042fd84:
        sar edx,2
    L_0042fd87:
        mov eax,edx
    L_0042fd89:
        shr eax,1Fh
    L_0042fd8c:
        lea edx,[edx+eax+33h]
    L_0042fd90:
        mov eax,ecx
    L_0042fd92:
        mov ecx,dword ptr [ecx+308h]
    L_0042fd98:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fd9d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fda3:
        push ecx
    L_0042fda4:
        mov edx,edi
    L_0042fda6:
        call asm_AnimationManager_Find_004491c0
    L_0042fdab:
        cmp eax,ebx
    L_0042fdad:
        jne short L_0042fdb5
    L_0042fdaf:
        mov dword ptr [esi+2CCh],ebx
    L_0042fdb5:
        add eax,10h
    L_0042fdb8:
        cmp eax,ebx
    L_0042fdba:
        je short L_0042fdd7
    L_0042fdbc:
        mov ecx,52h
    L_0042fdc1:
        mov edx,dword ptr [eax]
    L_0042fdc3:
        cmp word ptr [edx+38Ah],cx
    L_0042fdca:
        je asm_target_004301f0
    L_0042fdd0:
        mov eax,dword ptr [eax+4]
    L_0042fdd3:
        cmp eax,ebx
    L_0042fdd5:
        jne short L_0042fdc1
    L_0042fdd7:
        xor eax,eax
    L_0042fdd9:
        push eax
    L_0042fdda:
        mov edx,edi
    L_0042fddc:
        call asm_AnimationManager_Find_004491c0
    L_0042fde1:
        mov ecx,eax
    L_0042fde3:
        cmp ecx,ebx
    L_0042fde5:
        je short L_0042fe06
    L_0042fde7:
        movsx eax,word ptr [esi+59D0h]
    L_0042fdee:
        cdq
    L_0042fdef:
        mov ebp,0Ah
    L_0042fdf4:
        idiv ebp
    L_0042fdf6:
        mov eax,ecx
    L_0042fdf8:
        mov ecx,dword ptr [ecx+308h]
    L_0042fdfe:
        add edx,33h
    L_0042fe01:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fe06:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fe0c:
        push ecx
    L_0042fe0d:
        mov edx,edi
    L_0042fe0f:
        call asm_AnimationManager_Find_004491c0
    L_0042fe14:
        cmp eax,ebx
    L_0042fe16:
        jne short L_0042fe1e
    L_0042fe18:
        mov dword ptr [esi+2CCh],ebx
    L_0042fe1e:
        add eax,10h
    L_0042fe21:
        cmp eax,ebx
    L_0042fe23:
        je short L_0042fe46
    L_0042fe25:
        mov ecx,49h
    L_0042fe2a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fe30:
        mov edx,dword ptr [eax]
    L_0042fe32:
        cmp word ptr [edx+38Ah],cx
    L_0042fe39:
        je asm_target_004301f9
    L_0042fe3f:
        mov eax,dword ptr [eax+4]
    L_0042fe42:
        cmp eax,ebx
    L_0042fe44:
        jne short L_0042fe30
    L_0042fe46:
        xor eax,eax
    L_0042fe48:
        push eax
    L_0042fe49:
        mov edx,edi
    L_0042fe4b:
        call asm_AnimationManager_Find_004491c0
    L_0042fe50:
        mov ecx,eax
    L_0042fe52:
        cmp ecx,ebx
    L_0042fe54:
        je short L_0042fe7d
    L_0042fe56:
        movsx edx,word ptr [esi+59D2h]
    L_0042fe5d:
        mov eax,66666667h
    L_0042fe62:
        imul edx
    L_0042fe64:
        sar edx,2
    L_0042fe67:
        mov eax,edx
    L_0042fe69:
        shr eax,1Fh
    L_0042fe6c:
        lea edx,[edx+eax+33h]
    L_0042fe70:
        mov eax,ecx
    L_0042fe72:
        mov ecx,dword ptr [ecx+308h]
    L_0042fe78:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fe7d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fe83:
        push ecx
    L_0042fe84:
        mov edx,edi
    L_0042fe86:
        call asm_AnimationManager_Find_004491c0
    L_0042fe8b:
        cmp eax,ebx
    L_0042fe8d:
        jne short L_0042fe95
    L_0042fe8f:
        mov dword ptr [esi+2CCh],ebx
    L_0042fe95:
        add eax,10h
    L_0042fe98:
        cmp eax,ebx
    L_0042fe9a:
        je short L_0042feb7
    L_0042fe9c:
        mov ecx,4Ah
    L_0042fea1:
        mov edx,dword ptr [eax]
    L_0042fea3:
        cmp word ptr [edx+38Ah],cx
    L_0042feaa:
        je asm_target_00430202
    L_0042feb0:
        mov eax,dword ptr [eax+4]
    L_0042feb3:
        cmp eax,ebx
    L_0042feb5:
        jne short L_0042fea1
    L_0042feb7:
        xor eax,eax
    L_0042feb9:
        push eax
    L_0042feba:
        mov edx,edi
    L_0042febc:
        call asm_AnimationManager_Find_004491c0
    L_0042fec1:
        mov ecx,eax
    L_0042fec3:
        cmp ecx,ebx
    L_0042fec5:
        je short L_0042fee6
    L_0042fec7:
        movsx eax,word ptr [esi+59D2h]
    L_0042fece:
        cdq
    L_0042fecf:
        mov ebp,0Ah
    L_0042fed4:
        idiv ebp
    L_0042fed6:
        mov eax,ecx
    L_0042fed8:
        mov ecx,dword ptr [ecx+308h]
    L_0042fede:
        add edx,33h
    L_0042fee1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fee6:
        mov ecx,dword ptr [esi+2CCh]
    L_0042feec:
        push ecx
    L_0042feed:
        mov edx,edi
    L_0042feef:
        call asm_AnimationManager_Find_004491c0
    L_0042fef4:
        cmp eax,ebx
    L_0042fef6:
        jne short L_0042fefe
    L_0042fef8:
        mov dword ptr [esi+2CCh],ebx
    L_0042fefe:
        add eax,10h
    L_0042ff01:
        cmp eax,ebx
    L_0042ff03:
        je short L_0042ff26
    L_0042ff05:
        mov ecx,53h
    L_0042ff0a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042ff10:
        mov edx,dword ptr [eax]
    L_0042ff12:
        cmp word ptr [edx+38Ah],cx
    L_0042ff19:
        je asm_target_0043020b
    L_0042ff1f:
        mov eax,dword ptr [eax+4]
    L_0042ff22:
        cmp eax,ebx
    L_0042ff24:
        jne short L_0042ff10
    L_0042ff26:
        xor eax,eax
    L_0042ff28:
        push eax
    L_0042ff29:
        mov edx,edi
    L_0042ff2b:
        call asm_AnimationManager_Find_004491c0
    L_0042ff30:
        mov ecx,eax
    L_0042ff32:
        cmp ecx,ebx
    L_0042ff34:
        je short L_0042ff5d
    L_0042ff36:
        movsx edx,word ptr [esi+59D2h]
    L_0042ff3d:
        mov eax,66666667h
    L_0042ff42:
        imul edx
    L_0042ff44:
        sar edx,2
    L_0042ff47:
        mov eax,edx
    L_0042ff49:
        shr eax,1Fh
    L_0042ff4c:
        lea edx,[edx+eax+33h]
    L_0042ff50:
        mov eax,ecx
    L_0042ff52:
        mov ecx,dword ptr [ecx+308h]
    L_0042ff58:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042ff5d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042ff63:
        push ecx
    L_0042ff64:
        mov edx,edi
    L_0042ff66:
        call asm_AnimationManager_Find_004491c0
    L_0042ff6b:
        cmp eax,ebx
    L_0042ff6d:
        jne short L_0042ff75
    L_0042ff6f:
        mov dword ptr [esi+2CCh],ebx
    L_0042ff75:
        add eax,10h
    L_0042ff78:
        cmp eax,ebx
    L_0042ff7a:
        je short L_0042ff97
    L_0042ff7c:
        mov ecx,54h
    L_0042ff81:
        mov edx,dword ptr [eax]
    L_0042ff83:
        cmp word ptr [edx+38Ah],cx
    L_0042ff8a:
        je asm_target_00430214
    L_0042ff90:
        mov eax,dword ptr [eax+4]
    L_0042ff93:
        cmp eax,ebx
    L_0042ff95:
        jne short L_0042ff81
    L_0042ff97:
        xor eax,eax
    L_0042ff99:
        push eax
    L_0042ff9a:
        mov edx,edi
    L_0042ff9c:
        call asm_AnimationManager_Find_004491c0
    L_0042ffa1:
        mov ecx,eax
    L_0042ffa3:
        cmp ecx,ebx
    L_0042ffa5:
        je short L_0042ffc6
    L_0042ffa7:
        movsx eax,word ptr [esi+59D2h]
    L_0042ffae:
        cdq
    L_0042ffaf:
        mov ebp,0Ah
    L_0042ffb4:
        idiv ebp
    L_0042ffb6:
        mov eax,ecx
    L_0042ffb8:
        mov ecx,dword ptr [ecx+308h]
    L_0042ffbe:
        add edx,33h
    L_0042ffc1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042ffc6:
        mov ecx,dword ptr [esi+2CCh]
    L_0042ffcc:
        push ecx
    L_0042ffcd:
        mov edx,edi
    L_0042ffcf:
        call asm_AnimationManager_Find_004491c0
    L_0042ffd4:
        cmp eax,ebx
    L_0042ffd6:
        jne short L_0042ffde
    L_0042ffd8:
        mov dword ptr [esi+2CCh],ebx
    L_0042ffde:
        add eax,10h
    L_0042ffe1:
        cmp eax,ebx
    L_0042ffe3:
        je short L_00430006
    L_0042ffe5:
        mov ecx,4Bh
    L_0042ffea:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fff0:
        mov edx,dword ptr [eax]
    L_0042fff2:
        cmp word ptr [edx+38Ah],cx
    L_0042fff9:
        je asm_target_0043021d
    L_0042ffff:
        mov eax,dword ptr [eax+4]
    L_00430002:
        cmp eax,ebx
    L_00430004:
        jne short L_0042fff0
    L_00430006:
        xor eax,eax
    L_00430008:
        push eax
    L_00430009:
        mov edx,edi
    L_0043000b:
        call asm_AnimationManager_Find_004491c0
    L_00430010:
        mov ecx,eax
    L_00430012:
        cmp ecx,ebx
    L_00430014:
        je short L_0043003d
    L_00430016:
        movsx edx,word ptr [esi+59D4h]
    L_0043001d:
        mov eax,66666667h
    L_00430022:
        imul edx
    L_00430024:
        sar edx,2
    L_00430027:
        mov eax,edx
    L_00430029:
        shr eax,1Fh
    L_0043002c:
        lea edx,[edx+eax+33h]
    L_00430030:
        mov eax,ecx
    L_00430032:
        mov ecx,dword ptr [ecx+308h]
    L_00430038:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0043003d:
        mov ecx,dword ptr [esi+2CCh]
    L_00430043:
        push ecx
    L_00430044:
        mov edx,edi
    L_00430046:
        call asm_AnimationManager_Find_004491c0
    L_0043004b:
        cmp eax,ebx
    L_0043004d:
        jne short L_00430055
    L_0043004f:
        mov dword ptr [esi+2CCh],ebx
    L_00430055:
        add eax,10h
    L_00430058:
        cmp eax,ebx
    L_0043005a:
        je short L_00430077
    L_0043005c:
        mov ecx,4Ch
    L_00430061:
        mov edx,dword ptr [eax]
    L_00430063:
        cmp word ptr [edx+38Ah],cx
    L_0043006a:
        je asm_target_00430226
    L_00430070:
        mov eax,dword ptr [eax+4]
    L_00430073:
        cmp eax,ebx
    L_00430075:
        jne short L_00430061
    L_00430077:
        xor eax,eax
    L_00430079:
        push eax
    L_0043007a:
        mov edx,edi
    L_0043007c:
        call asm_AnimationManager_Find_004491c0
    L_00430081:
        mov ecx,eax
    L_00430083:
        cmp ecx,ebx
    L_00430085:
        je short L_004300a6
    L_00430087:
        movsx eax,word ptr [esi+59D4h]
    L_0043008e:
        cdq
    L_0043008f:
        mov ebp,0Ah
    L_00430094:
        idiv ebp
    L_00430096:
        mov eax,ecx
    L_00430098:
        mov ecx,dword ptr [ecx+308h]
    L_0043009e:
        add edx,33h
    L_004300a1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004300a6:
        mov ecx,dword ptr [esi+2CCh]
    L_004300ac:
        push ecx
    L_004300ad:
        mov edx,edi
    L_004300af:
        call asm_AnimationManager_Find_004491c0
    L_004300b4:
        cmp eax,ebx
    L_004300b6:
        pop ebp
    L_004300b7:
        jne short L_004300bf
    L_004300b9:
        mov dword ptr [esi+2CCh],ebx
    L_004300bf:
        add eax,10h
    L_004300c2:
        cmp eax,ebx
    L_004300c4:
        TH10_REL8(0x74, 0x004300c4, VA_asm_target_004300e6)
    L_004300c6:
        mov ecx,55h
    L_004300cb:
        TH10_REL8(0xeb, 0x004300cb, VA_asm_FUN_0042f8b0_part_004300d0)
    }
}

// 0x004300D0..0x00430243: FUN_0042f8b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042f8b0_part_004300d0() {
    __asm {
    L_004300d0:
        mov edx,dword ptr [eax]
    L_004300d2:
        cmp word ptr [edx+38Ah],cx
    L_004300d9:
        je asm_target_0043022f
    L_004300df:
        mov eax,dword ptr [eax+4]
    L_004300e2:
        cmp eax,ebx
    L_004300e4:
        jne short L_004300d0
    L_004300e6:
        xor eax,eax
    L_004300e8:
        push eax
    L_004300e9:
        mov edx,edi
    L_004300eb:
        call asm_AnimationManager_Find_004491c0
    L_004300f0:
        mov ecx,eax
    L_004300f2:
        cmp ecx,ebx
    L_004300f4:
        je short L_0043011d
    L_004300f6:
        movsx edx,word ptr [esi+59D4h]
    L_004300fd:
        mov eax,66666667h
    L_00430102:
        imul edx
    L_00430104:
        sar edx,2
    L_00430107:
        mov eax,edx
    L_00430109:
        shr eax,1Fh
    L_0043010c:
        lea edx,[edx+eax+33h]
    L_00430110:
        mov eax,ecx
    L_00430112:
        mov ecx,dword ptr [ecx+308h]
    L_00430118:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0043011d:
        mov ecx,dword ptr [esi+2CCh]
    L_00430123:
        push ecx
    L_00430124:
        mov edx,edi
    L_00430126:
        call asm_AnimationManager_Find_004491c0
    L_0043012b:
        cmp eax,ebx
    L_0043012d:
        jne short L_00430135
    L_0043012f:
        mov dword ptr [esi+2CCh],ebx
    L_00430135:
        add eax,10h
    L_00430138:
        cmp eax,ebx
    L_0043013a:
        je short L_00430157
    L_0043013c:
        mov ecx,56h
    L_00430141:
        mov edx,dword ptr [eax]
    L_00430143:
        cmp word ptr [edx+38Ah],cx
    L_0043014a:
        je asm_target_00430238
    L_00430150:
        mov eax,dword ptr [eax+4]
    L_00430153:
        cmp eax,ebx
    L_00430155:
        jne short L_00430141
    L_00430157:
        xor eax,eax
    L_00430159:
        push eax
    L_0043015a:
        mov edx,edi
    L_0043015c:
        call asm_AnimationManager_Find_004491c0
    L_00430161:
        mov ecx,eax
    L_00430163:
        cmp ecx,ebx
    L_00430165:
        pop edi
    L_00430166:
        je asm_target_00430241
    L_0043016c:
        movsx eax,word ptr [esi+59D4h]
    L_00430173:
        cdq
    L_00430174:
        mov esi,0Ah
    L_00430179:
        idiv esi
    L_0043017b:
        pop esi
    L_0043017c:
        mov eax,ecx
    L_0043017e:
        mov ecx,dword ptr [ecx+308h]
    L_00430184:
        pop ebx
    L_00430185:
        add edx,33h
    L_00430188:
        jmp asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0043018d:
        mov eax,dword ptr [eax]
    L_0043018f:
        mov eax,dword ptr [eax]
    L_00430191:
        jmp asm_target_0042f8f9
    L_00430196:
        mov eax,dword ptr [eax]
    L_00430198:
        mov eax,dword ptr [eax]
    L_0043019a:
        jmp asm_target_0042f978
    L_0043019f:
        mov eax,dword ptr [eax]
    L_004301a1:
        mov eax,dword ptr [eax]
    L_004301a3:
        jmp asm_target_0042f9e8
    L_004301a8:
        mov eax,dword ptr [eax]
    L_004301aa:
        mov eax,dword ptr [eax]
    L_004301ac:
        jmp asm_target_0042fa59
    L_004301b1:
        mov eax,dword ptr [eax]
    L_004301b3:
        mov eax,dword ptr [eax]
    L_004301b5:
        jmp asm_target_0042fac8
    L_004301ba:
        mov eax,dword ptr [eax]
    L_004301bc:
        mov eax,dword ptr [eax]
    L_004301be:
        jmp asm_target_0042fb39
    L_004301c3:
        mov eax,dword ptr [eax]
    L_004301c5:
        mov eax,dword ptr [eax]
    L_004301c7:
        jmp asm_target_0042fba8
    L_004301cc:
        mov eax,dword ptr [eax]
    L_004301ce:
        mov eax,dword ptr [eax]
    L_004301d0:
        jmp asm_target_0042fc19
    L_004301d5:
        mov eax,dword ptr [eax]
    L_004301d7:
        mov eax,dword ptr [eax]
    L_004301d9:
        jmp asm_target_0042fc88
    L_004301de:
        mov eax,dword ptr [eax]
    L_004301e0:
        mov eax,dword ptr [eax]
    L_004301e2:
        jmp asm_target_0042fcf9
    L_004301e7:
        mov eax,dword ptr [eax]
    L_004301e9:
        mov eax,dword ptr [eax]
    L_004301eb:
        jmp asm_target_0042fd68
    L_004301f0:
        mov eax,dword ptr [eax]
    L_004301f2:
        mov eax,dword ptr [eax]
    L_004301f4:
        jmp asm_target_0042fdd9
    L_004301f9:
        mov eax,dword ptr [eax]
    L_004301fb:
        mov eax,dword ptr [eax]
    L_004301fd:
        jmp asm_target_0042fe48
    L_00430202:
        mov eax,dword ptr [eax]
    L_00430204:
        mov eax,dword ptr [eax]
    L_00430206:
        jmp asm_target_0042feb9
    L_0043020b:
        mov eax,dword ptr [eax]
    L_0043020d:
        mov eax,dword ptr [eax]
    L_0043020f:
        jmp asm_target_0042ff28
    L_00430214:
        mov eax,dword ptr [eax]
    L_00430216:
        mov eax,dword ptr [eax]
    L_00430218:
        jmp asm_target_0042ff99
    L_0043021d:
        mov eax,dword ptr [eax]
    L_0043021f:
        mov eax,dword ptr [eax]
    L_00430221:
        jmp asm_target_00430008
    L_00430226:
        mov eax,dword ptr [eax]
    L_00430228:
        mov eax,dword ptr [eax]
    L_0043022a:
        jmp asm_target_00430079
    L_0043022f:
        mov eax,dword ptr [eax]
    L_00430231:
        mov eax,dword ptr [eax]
    L_00430233:
        jmp asm_target_004300e8
    L_00430238:
        mov eax,dword ptr [eax]
    L_0043023a:
        mov eax,dword ptr [eax]
    L_0043023c:
        jmp asm_target_00430159
    L_00430241:
        pop esi
    L_00430242:
        pop ebx
    L_00430243:
        ret
    }
}

// 0x00433EF0..0x0043408C: FUN_00433ef0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00433ef0_00433ef0() {
    __asm {
    L_00433ef0:
        sub esp,1Ch
    L_00433ef3:
        push ebp
    L_00433ef4:
        mov ebp,dword ptr [esp+24h]
    L_00433ef8:
        mov eax,dword ptr [ebp+20h]
    L_00433efb:
        cmp eax,3
    L_00433efe:
        ja asm_target_004349c1
    L_00433f04:
        push ebx
    L_00433f05:
        push esi
    L_00433f06:
        push edi
    L_00433f07:
        jmp dword ptr [eax*4+4349CCh]
    L_00433f0e:
        cmp dword ptr [ebp+2B4h],1
    L_00433f15:
        jne asm_target_00434101
    L_00433f1b:
        mov dword ptr [ebp+2Ch],6
    L_00433f22:
        mov eax,dword ptr [ebp+2Ch]
    L_00433f25:
        test eax,eax
    L_00433f27:
        je short L_00433f38
    L_00433f29:
        jg short L_00433f31
    L_00433f2b:
        dec eax
    L_00433f2c:
        mov dword ptr [ebp+24h],eax
    L_00433f2f:
        jmp short L_00433f3f
    L_00433f31:
        xor eax,eax
    L_00433f33:
        mov dword ptr [ebp+24h],eax
    L_00433f36:
        jmp short L_00433f3f
    L_00433f38:
        mov dword ptr [ebp+24h],0
    L_00433f3f:
        mov eax,dword ptr [ebp+440h]
    L_00433f45:
        mov edx,dword ptr [data_00491c10]
    L_00433f4b:
        push eax
    L_00433f4c:
        call asm_AnimationManager_Find_004491c0
    L_00433f51:
        test eax,eax
    L_00433f53:
        jne short L_00433f82
    L_00433f55:
        push ebp
    L_00433f56:
        mov edi,5Fh
    L_00433f5b:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00433f60:
        mov ecx,dword ptr [data_004776e0]
    L_00433f66:
        mov eax,dword ptr [ecx+8994h]
    L_00433f6c:
        push 0Fh
    L_00433f6e:
        push 8
    L_00433f70:
        push eax
    L_00433f71:
        lea edi,[esp+28h]
    L_00433f75:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00433f7a:
        mov edx,dword ptr [eax]
    L_00433f7c:
        mov dword ptr [ebp+5D0h],edx
    L_00433f82:
        push ebp
    L_00433f83:
        mov edi,67h
    L_00433f88:
        call asm_Recovery_InstallAnimationSlot_0042c670
    L_00433f8d:
        push 0
    L_00433f8f:
        lea eax,[esp+34h]
    L_00433f93:
        push eax
    L_00433f94:
        mov eax,46ED14h
    L_00433f99:
        mov dword ptr [esp+20h],0
    L_00433fa1:
        call asm_FUN_0044b360_0044b360
    L_00433fa6:
        test eax,eax
    L_00433fa8:
        mov dword ptr [ebp+5AACh],eax
    L_00433fae:
        je asm_target_00434803
    L_00433fb4:
        mov ecx,dword ptr [esp+30h]
    L_00433fb8:
        test ecx,ecx
    L_00433fba:
        jle asm_target_00434054
    L_00433fc0:
        lea ecx,[ebp+0E98h]
    L_00433fc6:
        lea edx,[ebp+698h]
    L_00433fcc:
        lea esi,[ebp+16D8h]
    L_00433fd2:
        mov dword ptr [esp+14h],ecx
    L_00433fd6:
        mov dword ptr [esp+10h],edx
    L_00433fda:
        lea ebx,[ebx+force_disp32_zero]
    L_00433fe0:
        mov cl,byte ptr [eax]
    L_00433fe2:
        cmp cl,23h
    L_00433fe5:
        je short L_00434043
    L_00433fe7:
        cmp cl,40h
    L_00433fea:
        jne short L_00434043
    L_00433fec:
        lea ecx,[eax+1]
    L_00433fef:
        mov eax,dword ptr [esp+10h]
    L_00433ff3:
        push eax
    L_00433ff4:
        lea edi,[esp+34h]
    L_00433ff8:
        call asm_StageText_ExtractLine_00434a20
    L_00433ffd:
        mov ecx,dword ptr [esp+14h]
    L_00434001:
        push ecx
    L_00434002:
        mov ecx,eax
    L_00434004:
        call asm_StageText_ExtractLine_00434a20
    L_00434009:
        mov ebx,8
    L_0043400e:
        mov edi,edi
    L_00434010:
        push esi
    L_00434011:
        lea edi,[esp+34h]
    L_00434015:
        mov ecx,eax
    L_00434017:
        call asm_StageText_ExtractLine_00434a20
    L_0043401c:
        add esi,42h
    L_0043401f:
        dec ebx
    L_00434020:
        jne short L_00434010
    L_00434022:
        mov edi,dword ptr [esp+18h]
    L_00434026:
        mov edx,dword ptr [esp+10h]
    L_0043402a:
        mov ecx,dword ptr [esp+14h]
    L_0043402e:
        inc edi
    L_0043402f:
        add edx,40h
    L_00434032:
        add ecx,42h
    L_00434035:
        mov dword ptr [esp+18h],edi
    L_00434039:
        mov dword ptr [esp+10h],edx
    L_0043403d:
        mov dword ptr [esp+14h],ecx
    L_00434041:
        jmp short L_0043404c
    L_00434043:
        lea edx,[esp+30h]
    L_00434047:
        call asm_StageText_SkipLine_004349e0
    L_0043404c:
        mov ecx,dword ptr [esp+30h]
    L_00434050:
        test ecx,ecx
    L_00434052:
        jg short L_00433fe0
    L_00434054:
        mov ecx,dword ptr [esp+18h]
    L_00434058:
        mov eax,ecx
    L_0043405a:
        xor edi,edi
    L_0043405c:
        cmp eax,edi
    L_0043405e:
        mov dword ptr [ebp+2Ch],ecx
    L_00434061:
        je short L_00434072
    L_00434063:
        jg short L_0043406b
    L_00434065:
        dec eax
    L_00434066:
        mov dword ptr [ebp+24h],eax
    L_00434069:
        jmp short L_00434075
    L_0043406b:
        xor eax,eax
    L_0043406d:
        mov dword ptr [ebp+24h],eax
    L_00434070:
        jmp short L_00434075
    L_00434072:
        mov dword ptr [ebp+24h],edi
    L_00434075:
        lea edx,[ebp+664h]
    L_0043407b:
        mov dword ptr [ebp+58D8h],edi
    L_00434081:
        mov dword ptr [ebp+688h],ecx
    L_00434087:
        mov dword ptr [esp+30h],edx
    L_0043408b:
        TH10_REL8(0xeb, 0x0043408b, VA_asm_FUN_00433ef0_part_00434090)
    }
}

// 0x00434090..0x004349C9: FUN_00433ef0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00433ef0_part_00434090() {
    __asm {
    L_00434090:
        mov eax,dword ptr [data_00491fec]
    L_00434095:
        mov esi,dword ptr [data_00491c10]
    L_0043409b:
        mov dword ptr [esp+18h],eax
    L_0043409f:
        call asm_FUN_00449950_00449950
    L_004340a4:
        mov ebx,eax
    L_004340a6:
        or dword ptr [ebx+35Ch],40000000h
    L_004340b0:
        lea ecx,[edi+27h]
    L_004340b3:
        push ecx
    L_004340b4:
        mov ecx,dword ptr [esp+1Ch]
    L_004340b8:
        push ebx
    L_004340b9:
        mov dword ptr [ebx+20h],0Fh
    L_004340c0:
        call asm_FUN_00449870_00449870
    L_004340c5:
        mov edx,dword ptr [data_00491c10]
    L_004340cb:
        lea eax,[esp+14h]
    L_004340cf:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004340d4:
        mov eax,dword ptr [esp+30h]
    L_004340d8:
        mov edx,dword ptr [esp+14h]
    L_004340dc:
        mov dword ptr [eax],edx
    L_004340de:
        inc edi
    L_004340df:
        add eax,4
    L_004340e2:
        cmp edi,8
    L_004340e5:
        mov dword ptr [esp+30h],eax
    L_004340e9:
        jl short L_00434090
    L_004340eb:
        xor ecx,ecx
    L_004340ed:
        mov dword ptr [ebp+68Ch],ecx
    L_004340f3:
        mov dword ptr [ebp+690h],ecx
    L_004340f9:
        mov dword ptr [ebp+694h],ecx
    L_004340ff:
        jmp short L_00434103
    L_00434101:
        xor ecx,ecx
    L_00434103:
        mov eax,dword ptr [ebp+2B4h]
    L_00434109:
        cmp eax,0Ah
    L_0043410c:
        jge asm_target_004342dd
    L_00434112:
        fild dword ptr [ebp+58D8h]
    L_00434118:
        lea edx,[eax+eax*4]
    L_0043411b:
        lea edx,[edx*8-28h]
    L_00434122:
        mov dword ptr [esp+30h],edx
    L_00434126:
        fmul dword ptr [data_00470ca0]
    L_0043412c:
        add eax,eax
    L_0043412e:
        lea edi,[eax-2]
    L_00434131:
        cmp edi,eax
    L_00434133:
        fsubr dword ptr [data_00470c80]
    L_00434139:
        mov dword ptr [esp+20h],42800000h
    L_00434141:
        mov dword ptr [esp+28h],0
    L_00434149:
        fiadd dword ptr [esp+30h]
    L_0043414d:
        fstp dword ptr [esp+24h]
    L_00434151:
        jge asm_target_004342dd
    L_00434157:
        mov eax,edi
    L_00434159:
        imul eax,42h
    L_0043415c:
        lea edx,[eax+ebp+0E98h]
    L_00434163:
        lea eax,[ebp+edi*4+614h]
    L_0043416a:
        mov dword ptr [esp+18h],edx
    L_0043416e:
        mov dword ptr [esp+30h],eax
    L_00434172:
        cmp edi,dword ptr [ebp+688h]
    L_00434178:
        jge asm_target_004342dd
    L_0043417e:
        mov ecx,dword ptr [ebp+14h]
    L_00434181:
        mov esi,dword ptr [data_00491c10]
    L_00434187:
        mov dword ptr [esp+14h],ecx
    L_0043418b:
        call asm_FUN_00449950_00449950
    L_00434190:
        mov ecx,dword ptr [esp+14h]
    L_00434194:
        mov ebx,eax
    L_00434196:
        mov eax,dword ptr [ebx+35Ch]
    L_0043419c:
        lea edx,[edi+0ADh]
    L_004341a2:
        push edx
    L_004341a3:
        or eax,40000000h
    L_004341a8:
        push ebx
    L_004341a9:
        mov dword ptr [ebx+20h],0Fh
    L_004341b0:
        mov dword ptr [ebx+35Ch],eax
    L_004341b6:
        call asm_FUN_00449870_00449870
    L_004341bb:
        mov esi,dword ptr [data_00491c10]
    L_004341c1:
        lea eax,[esp+10h]
    L_004341c5:
        mov edx,esi
    L_004341c7:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004341cc:
        mov ecx,dword ptr [esp+10h]
    L_004341d0:
        mov eax,dword ptr [esp+30h]
    L_004341d4:
        mov edx,ecx
    L_004341d6:
        push edx
    L_004341d7:
        mov edx,esi
    L_004341d9:
        mov dword ptr [eax],ecx
    L_004341db:
        call asm_AnimationManager_Find_004491c0
    L_004341e0:
        mov ebx,eax
    L_004341e2:
        test ebx,ebx
    L_004341e4:
        jne short L_004341ec
    L_004341e6:
        mov eax,dword ptr [esp+30h]
    L_004341ea:
        mov dword ptr [eax],ebx
    L_004341ec:
        mov ecx,dword ptr [data_0047783c]
    L_004341f2:
        mov al,byte ptr [ecx+edi+1D892h]
    L_004341f9:
        test al,al
    L_004341fb:
        je short L_00434214
    L_004341fd:
        mov edx,dword ptr [esp+18h]
    L_00434201:
        push edx
    L_00434202:
        push 0FFFFFFh
    L_00434207:
        push esi
    L_00434208:
        mov esi,ebx
    L_0043420a:
        call asm_Recovery_MarkLogState_00447a50
    L_0043420f:
        add esp,0Ch
    L_00434212:
        jmp short L_0043422d
    L_00434214:
        lea eax,[edi+1]
    L_00434217:
        push eax
    L_00434218:
        push 46ECF4h
    L_0043421d:
        push 0FFFFFFh
    L_00434222:
        push esi
    L_00434223:
        mov esi,ebx
    L_00434225:
        call asm_Recovery_MarkLogState_00447a50
    L_0043422a:
        add esp,10h
    L_0043422d:
        mov eax,dword ptr [ebp+58D8h]
    L_00434233:
        cmp edi,eax
    L_00434235:
        jl short L_00434249
    L_00434237:
        add eax,0Ah
    L_0043423a:
        cmp edi,eax
    L_0043423c:
        jge short L_00434249
    L_0043423e:
        mov eax,dword ptr [ebx+35Ch]
    L_00434244:
        or eax,2
    L_00434247:
        jmp short L_00434252
    L_00434249:
        mov eax,dword ptr [ebx+35Ch]
    L_0043424f:
        and eax,0FFFFFFFDh
    L_00434252:
        mov dword ptr [ebx+35Ch],eax
    L_00434258:
        cmp edi,dword ptr [ebp+24h]
    L_0043425b:
        jne short L_0043426b
    L_0043425d:
        fld dword ptr [esp+20h]
    L_00434261:
        fsub qword ptr [data_00470c98]
    L_00434267:
        fstp dword ptr [esp+20h]
    L_0043426b:
        push 0
    L_0043426d:
        lea edx,[ebx+334h]
    L_00434273:
        push 4
    L_00434275:
        lea ecx,[esp+28h]
    L_00434279:
        mov eax,ebx
    L_0043427b:
        call asm_StageText_Initialize_00434a80
    L_00434280:
        mov eax,dword ptr [ebp+24h]
    L_00434283:
        cmp edi,eax
    L_00434285:
        jne short L_00434295
    L_00434287:
        fld dword ptr [esp+20h]
    L_0043428b:
        fadd qword ptr [data_00470c98]
    L_00434291:
        fstp dword ptr [esp+20h]
    L_00434295:
        mov edx,dword ptr [esp+18h]
    L_00434299:
        fld dword ptr [esp+24h]
    L_0043429d:
        mov esi,dword ptr [esp+30h]
    L_004342a1:
        fadd dword ptr [data_00470ca0]
    L_004342a7:
        xor ecx,ecx
    L_004342a9:
        cmp edi,eax
    L_004342ab:
        setne cl
    L_004342ae:
        fstp dword ptr [esp+24h]
    L_004342b2:
        add edx,42h
    L_004342b5:
        mov dword ptr [esp+18h],edx
    L_004342b9:
        add esi,4
    L_004342bc:
        mov dword ptr [esp+30h],esi
    L_004342c0:
        add ecx,2
    L_004342c3:
        mov word ptr [ebx+304h],cx
    L_004342ca:
        mov edx,dword ptr [ebp+2B4h]
    L_004342d0:
        inc edi
    L_004342d1:
        shl edx,1
    L_004342d3:
        xor ecx,ecx
    L_004342d5:
        cmp edi,edx
    L_004342d7:
        jl asm_target_00434172
    L_004342dd:
        cmp dword ptr [ebp+2B4h],0Ah
    L_004342e4:
        jl asm_target_004349be
    L_004342ea:
        mov dword ptr [ebp+20h],1
    L_004342f1:
        mov eax,dword ptr [ebp+2C0h]
    L_004342f7:
        test al,1
    L_004342f9:
        jne short L_00434324
    L_004342fb:
        or eax,1
    L_004342fe:
        mov dword ptr [ebp+2B4h],ecx
    L_00434304:
        mov dword ptr [ebp+2B0h],0FFF0BDC1h
    L_0043430e:
        mov dword ptr [ebp+2B8h],ecx
    L_00434314:
        mov dword ptr [ebp+2BCh],476F78h
    L_0043431e:
        mov dword ptr [ebp+2C0h],eax
    L_00434324:
        pop edi
    L_00434325:
        pop esi
    L_00434326:
        pop ebx
    L_00434327:
        mov dword ptr [ebp+2B4h],ecx
    L_0043432d:
        mov dword ptr [ebp+2B8h],ecx
    L_00434333:
        mov dword ptr [ebp+2B0h],0FFFFFFFFh
    L_0043433d:
        xor eax,eax
    L_0043433f:
        pop ebp
    L_00434340:
        add esp,1Ch
    L_00434343:
        ret 4
    L_00434346:
        mov eax,dword ptr [ebp+2B4h]
    L_0043434c:
        and eax,80000001h
    L_00434351:
        jns short L_00434358
    L_00434353:
        dec eax
    L_00434354:
        or eax,0FFFFFFFEh
    L_00434357:
        inc eax
    L_00434358:
        jne asm_target_004343f6
    L_0043435e:
        mov eax,dword ptr [ebp+68Ch]
    L_00434364:
        cmp eax,8
    L_00434367:
        jge asm_target_004343f6
    L_0043436d:
        lea esi,[ebp+eax*4+664h]
    L_00434374:
        call asm_AnimationManager_ValidateHandle_00449450
    L_00434379:
        mov ecx,dword ptr [data_0047783c]
    L_0043437f:
        mov esi,eax
    L_00434381:
        mov eax,dword ptr [ebp+690h]
    L_00434387:
        mov dl,byte ptr [eax+ecx+1D892h]
    L_0043438e:
        test dl,dl
    L_00434390:
        jne short L_004343b8
    L_00434392:
        mov ecx,dword ptr [ebp+694h]
    L_00434398:
        test ecx,ecx
    L_0043439a:
        je short L_004343b8
    L_0043439c:
        mov edx,dword ptr [ebp+68Ch]
    L_004343a2:
        mov eax,dword ptr [edx*4+476FD8h]
    L_004343a9:
        mov ecx,dword ptr [data_00491c10]
    L_004343af:
        push eax
    L_004343b0:
        push 8080FFh
    L_004343b5:
        push ecx
    L_004343b6:
        jmp short L_004343d8
    L_004343b8:
        mov edx,dword ptr [ebp+68Ch]
    L_004343be:
        lea eax,[edx+eax*8]
    L_004343c1:
        mov edx,dword ptr [data_00491c10]
    L_004343c7:
        imul eax,42h
    L_004343ca:
        lea ecx,[eax+ebp+16D8h]
    L_004343d1:
        push ecx
    L_004343d2:
        push 0FFFFFFh
    L_004343d7:
        push edx
    L_004343d8:
        call asm_Recovery_MarkLogState_00447a50
    L_004343dd:
        mov word ptr [esi+304h],2
    L_004343e6:
        mov eax,dword ptr [ebp+68Ch]
    L_004343ec:
        add esp,0Ch
    L_004343ef:
        inc eax
    L_004343f0:
        mov dword ptr [ebp+68Ch],eax
    L_004343f6:
        cmp dword ptr [ebp+2B4h],4
    L_004343fd:
        jle asm_target_004349be
    L_00434403:
        mov ecx,2
    L_00434408:
        mov eax,ebp
    L_0043440a:
        call asm_GameState_SetTimerTarget_0042c620
    L_0043440f:
        pop edi
    L_00434410:
        pop esi
    L_00434411:
        pop ebx
    L_00434412:
        xor eax,eax
    L_00434414:
        pop ebp
    L_00434415:
        add esp,1Ch
    L_00434418:
        ret 4
    L_0043441b:
        mov eax,dword ptr [ebp+2B4h]
    L_00434421:
        and eax,80000001h
    L_00434426:
        jns short L_0043442d
    L_00434428:
        dec eax
    L_00434429:
        or eax,0FFFFFFFEh
    L_0043442c:
        inc eax
    L_0043442d:
        jne asm_target_004344cd
    L_00434433:
        mov eax,dword ptr [ebp+68Ch]
    L_00434439:
        cmp eax,8
    L_0043443c:
        jge asm_target_004344cd
    L_00434442:
        lea esi,[ebp+eax*4+664h]
    L_00434449:
        call asm_AnimationManager_ValidateHandle_00449450
    L_0043444e:
        mov ecx,dword ptr [data_0047783c]
    L_00434454:
        mov esi,eax
    L_00434456:
        mov eax,dword ptr [ebp+690h]
    L_0043445c:
        mov dl,byte ptr [eax+ecx+1D892h]
    L_00434463:
        xor ebx,ebx
    L_00434465:
        test dl,dl
    L_00434467:
        jne short L_0043448d
    L_00434469:
        cmp dword ptr [ebp+694h],ebx
    L_0043446f:
        je short L_0043448d
    L_00434471:
        mov edx,dword ptr [ebp+68Ch]
    L_00434477:
        mov eax,dword ptr [edx*4+476FD8h]
    L_0043447e:
        mov ecx,dword ptr [data_00491c10]
    L_00434484:
        push eax
    L_00434485:
        push 8080FFh
    L_0043448a:
        push ecx
    L_0043448b:
        jmp short L_004344ad
    L_0043448d:
        mov edx,dword ptr [ebp+68Ch]
    L_00434493:
        lea eax,[edx+eax*8]
    L_00434496:
        mov edx,dword ptr [data_00491c10]
    L_0043449c:
        imul eax,42h
    L_0043449f:
        lea ecx,[eax+ebp+16D8h]
    L_004344a6:
        push ecx
    L_004344a7:
        push 0FFFFFFh
    L_004344ac:
        push edx
    L_004344ad:
        call asm_Recovery_MarkLogState_00447a50
    L_004344b2:
        mov word ptr [esi+304h],2
    L_004344bb:
        mov eax,dword ptr [ebp+68Ch]
    L_004344c1:
        add esp,0Ch
    L_004344c4:
        inc eax
    L_004344c5:
        mov dword ptr [ebp+68Ch],eax
    L_004344cb:
        jmp short L_004344cf
    L_004344cd:
        xor ebx,ebx
    L_004344cf:
        mov eax,dword ptr [ebp+24h]
    L_004344d2:
        lea esi,[ebp+24h]
    L_004344d5:
        mov dword ptr [esi+4],eax
    L_004344d8:
        test byte ptr [data_00474e36],10h
    L_004344df:
        jne short L_004344ea
    L_004344e1:
        test byte ptr [data_00474e34],10h
    L_004344e8:
        je short L_004344f3
    L_004344ea:
        push 0FFFFFFFFh
    L_004344ec:
        mov eax,esi
    L_004344ee:
        call asm_MenuCursor_Advance_0044bea0
    L_004344f3:
        mov cl,byte ptr [data_00474e36]
    L_004344f9:
        mov al,20h
    L_004344fb:
        test cl,al
    L_004344fd:
        jne short L_00434507
    L_004344ff:
        test byte ptr [data_00474e34],al
    L_00434505:
        je short L_00434510
    L_00434507:
        push 1
    L_00434509:
        mov eax,esi
    L_0043450b:
        call asm_MenuCursor_Advance_0044bea0
    L_00434510:
        mov ecx,dword ptr [esi+4]
    L_00434513:
        cmp ecx,dword ptr [esi]
    L_00434515:
        je asm_target_00434673
    L_0043451b:
        push ebx
    L_0043451c:
        mov edi,0Ch
    L_00434521:
        mov ecx,492590h
    L_00434526:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0043452b:
        mov ecx,dword ptr [ebp+58D8h]
    L_00434531:
        mov eax,dword ptr [esi]
    L_00434533:
        cmp eax,ecx
    L_00434535:
        jl short L_00434541
    L_00434537:
        add ecx,0Ah
    L_0043453a:
        cmp eax,ecx
    L_0043453c:
        jl short L_00434547
    L_0043453e:
        add eax,0FFFFFFF7h
    L_00434541:
        mov dword ptr [ebp+58D8h],eax
    L_00434547:
        fild dword ptr [ebp+58D8h]
    L_0043454d:
        mov eax,dword ptr [ebp+688h]
    L_00434553:
        xor edi,edi
    L_00434555:
        cmp eax,ebx
    L_00434557:
        fmul dword ptr [data_00470ca0]
    L_0043455d:
        mov dword ptr [esp+20h],42800000h
    L_00434565:
        mov dword ptr [esp+28h],0
    L_0043456d:
        fsubr dword ptr [data_00470c80]
    L_00434573:
        fstp dword ptr [esp+24h]
    L_00434577:
        jle asm_target_00434667
    L_0043457d:
        lea ebx,[ebp+614h]
    L_00434583:
        mov edx,dword ptr [ebx]
    L_00434585:
        push edx
    L_00434586:
        mov edx,dword ptr [data_00491c10]
    L_0043458c:
        call asm_AnimationManager_Find_004491c0
    L_00434591:
        mov esi,eax
    L_00434593:
        test esi,esi
    L_00434595:
        jne short L_00434599
    L_00434597:
        mov dword ptr [ebx],eax
    L_00434599:
        mov eax,dword ptr [ebp+58D8h]
    L_0043459f:
        cmp edi,eax
    L_004345a1:
        jl short L_004345b5
    L_004345a3:
        add eax,0Ah
    L_004345a6:
        cmp edi,eax
    L_004345a8:
        jge short L_004345b5
    L_004345aa:
        mov eax,dword ptr [esi+35Ch]
    L_004345b0:
        or eax,2
    L_004345b3:
        jmp short L_004345be
    L_004345b5:
        mov eax,dword ptr [esi+35Ch]
    L_004345bb:
        and eax,0FFFFFFFDh
    L_004345be:
        mov dword ptr [esi+35Ch],eax
    L_004345c4:
        cmp edi,dword ptr [ebp+24h]
    L_004345c7:
        jne short L_004345d7
    L_004345c9:
        fld dword ptr [esp+20h]
    L_004345cd:
        fsub qword ptr [data_00470c98]
    L_004345d3:
        fstp dword ptr [esp+20h]
    L_004345d7:
        fld dword ptr [esi+338h]
    L_004345dd:
        fsub dword ptr [esp+24h]
    L_004345e1:
        fabs
    L_004345e3:
        fcomp dword ptr [data_00470c64]
    L_004345e9:
        fnstsw ax
    L_004345eb:
        test ah,5
    L_004345ee:
        jp short L_00434607
    L_004345f0:
        push 0
    L_004345f2:
        lea edx,[esi+334h]
    L_004345f8:
        push 4
    L_004345fa:
        lea ecx,[esp+28h]
    L_004345fe:
        mov eax,esi
    L_00434600:
        call asm_StageText_Initialize_00434a80
    L_00434605:
        jmp short L_00434621
    L_00434607:
        mov ecx,dword ptr [esp+20h]
    L_0043460b:
        mov edx,dword ptr [esp+24h]
    L_0043460f:
        lea eax,[esi+334h]
    L_00434615:
        mov dword ptr [eax],ecx
    L_00434617:
        mov ecx,dword ptr [esp+28h]
    L_0043461b:
        mov dword ptr [eax+4],edx
    L_0043461e:
        mov dword ptr [eax+8],ecx
    L_00434621:
        mov eax,dword ptr [ebp+24h]
    L_00434624:
        cmp edi,eax
    L_00434626:
        jne short L_00434636
    L_00434628:
        fld dword ptr [esp+20h]
    L_0043462c:
        fadd qword ptr [data_00470c98]
    L_00434632:
        fstp dword ptr [esp+20h]
    L_00434636:
        fld dword ptr [esp+24h]
    L_0043463a:
        xor edx,edx
    L_0043463c:
        fadd dword ptr [data_00470ca0]
    L_00434642:
        cmp edi,eax
    L_00434644:
        setne dl
    L_00434647:
        add ebx,4
    L_0043464a:
        fstp dword ptr [esp+24h]
    L_0043464e:
        add edx,2
    L_00434651:
        mov word ptr [esi+304h],dx
    L_00434658:
        mov eax,dword ptr [ebp+688h]
    L_0043465e:
        inc edi
    L_0043465f:
        cmp edi,eax
    L_00434661:
        jl asm_target_00434583
    L_00434667:
        mov dword ptr [ebp+694h],0
    L_00434671:
        xor ebx,ebx
    L_00434673:
        mov eax,dword ptr [data_00474e36]
    L_00434678:
        test eax,1001h
    L_0043467d:
        je asm_target_004347fb
    L_00434683:
        lea esi,[ebp+664h]
    L_00434689:
        mov edi,8
    L_0043468e:
        mov edi,edi
    L_00434690:
        mov eax,dword ptr [esi]
    L_00434692:
        mov edx,dword ptr [data_00491c10]
    L_00434698:
        push eax
    L_00434699:
        call asm_AnimationManager_Find_004491c0
    L_0043469e:
        cmp eax,ebx
    L_004346a0:
        je short L_004346d0
    L_004346a2:
        cmp dword ptr [eax+18h],ebx
    L_004346a5:
        mov ecx,3
    L_004346aa:
        mov word ptr [eax+304h],cx
    L_004346b1:
        jne short L_004346d0
    L_004346b3:
        mov eax,dword ptr [eax+14h]
    L_004346b6:
        cmp eax,ebx
    L_004346b8:
        je short L_004346d0
    L_004346ba:
        lea ebx,[ebx+force_disp32_zero]
    L_004346c0:
        mov edx,dword ptr [eax]
    L_004346c2:
        mov word ptr [edx+304h],cx
    L_004346c9:
        mov eax,dword ptr [eax+4]
    L_004346cc:
        cmp eax,ebx
    L_004346ce:
        jne short L_004346c0
    L_004346d0:
        add esi,4
    L_004346d3:
        dec edi
    L_004346d4:
        jne short L_00434690
    L_004346d6:
        mov eax,dword ptr [ebp+24h]
    L_004346d9:
        mov dword ptr [ebp+690h],eax
    L_004346df:
        mov dword ptr [ebp+68Ch],ebx
    L_004346e5:
        mov eax,dword ptr [ebp+2C0h]
    L_004346eb:
        test al,1
    L_004346ed:
        jne short L_00434718
    L_004346ef:
        or eax,1
    L_004346f2:
        mov dword ptr [ebp+2B4h],ebx
    L_004346f8:
        mov dword ptr [ebp+2B0h],0FFF0BDC1h
    L_00434702:
        mov dword ptr [ebp+2B8h],ebx
    L_00434708:
        mov dword ptr [ebp+2BCh],476F78h
    L_00434712:
        mov dword ptr [ebp+2C0h],eax
    L_00434718:
        mov edx,dword ptr [data_0047783c]
    L_0043471e:
        mov dword ptr [ebp+2B4h],ebx
    L_00434724:
        mov dword ptr [ebp+2B8h],ebx
    L_0043472a:
        mov dword ptr [ebp+2B0h],0FFFFFFFFh
    L_00434734:
        mov ecx,dword ptr [ebp+690h]
    L_0043473a:
        mov al,byte ptr [ecx+edx+1D892h]
    L_00434741:
        test al,al
    L_00434743:
        jne short L_0043479b
    L_00434745:
        cmp dword ptr [ebp+694h],ebx
    L_0043474b:
        jne short L_0043479b
    L_0043474d:
        test byte ptr [data_00491d78],10h
    L_00434754:
        mov edx,46DF98h
    L_00434759:
        push ebx
    L_0043475a:
        mov eax,492590h
    L_0043475f:
        je short L_0043477e
    L_00434761:
        push 4
    L_00434763:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00434768:
        pop edi
    L_00434769:
        pop esi
    L_0043476a:
        pop ebx
    L_0043476b:
        mov dword ptr [ebp+694h],1
    L_00434775:
        xor eax,eax
    L_00434777:
        pop ebp
    L_00434778:
        add esp,1Ch
    L_0043477b:
        ret 4
    L_0043477e:
        push 3
    L_00434780:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00434785:
        pop edi
    L_00434786:
        pop esi
    L_00434787:
        pop ebx
    L_00434788:
        mov dword ptr [ebp+694h],1
    L_00434792:
        xor eax,eax
    L_00434794:
        pop ebp
    L_00434795:
        add esp,1Ch
    L_00434798:
        ret 4
    L_0043479b:
        mov eax,dword ptr [ebp+24h]
    L_0043479e:
        shl eax,6
    L_004347a1:
        lea ecx,[eax+ebp+698h]
    L_004347a8:
        push ecx
    L_004347a9:
        push ebx
    L_004347aa:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_004347af:
        test byte ptr [data_00491d78],10h
    L_004347b6:
        je short L_004347ca
    L_004347b8:
        push ebx
    L_004347b9:
        push 4
    L_004347bb:
        mov edx,46DF98h
    L_004347c0:
        mov eax,492590h
    L_004347c5:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004347ca:
        push ebx
    L_004347cb:
        push 2
    L_004347cd:
        mov edx,46DF98h
    L_004347d2:
        mov eax,492590h
    L_004347d7:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004347dc:
        mov edx,dword ptr [data_0047783c]
    L_004347e2:
        pop edi
    L_004347e3:
        pop esi
    L_004347e4:
        mov byte ptr [edx+1D892h],1
    L_004347eb:
        mov dword ptr [ebp+694h],ebx
    L_004347f1:
        pop ebx
    L_004347f2:
        xor eax,eax
    L_004347f4:
        pop ebp
    L_004347f5:
        add esp,1Ch
    L_004347f8:
        ret 4
    L_004347fb:
        test al,0Ah
    L_004347fd:
        je asm_target_004349be
    L_00434803:
        mov eax,dword ptr [ebp+5AACh]
    L_00434809:
        xor ebx,ebx
    L_0043480b:
        cmp eax,ebx
    L_0043480d:
        je short L_0043481e
    L_0043480f:
        push eax
    L_00434810:
        call asm_free_00452422
    L_00434815:
        add esp,4
    L_00434818:
        mov dword ptr [ebp+5AACh],ebx
    L_0043481e:
        lea eax,[ebp+24h]
    L_00434821:
        mov dword ptr [ebp+5AACh],ebx
    L_00434827:
        call asm_Score_InputHistoryStep_0044be70
    L_0043482c:
        mov eax,dword ptr [ebp+688h]
    L_00434832:
        xor esi,esi
    L_00434834:
        cmp eax,ebx
    L_00434836:
        jle short L_00434855
    L_00434838:
        lea edi,[ebp+614h]
    L_0043483e:
        mov edi,edi
    L_00434840:
        mov eax,edi
    L_00434842:
        call asm_FUN_00409e50_00409e50
    L_00434847:
        mov eax,dword ptr [ebp+688h]
    L_0043484d:
        inc esi
    L_0043484e:
        add edi,4
    L_00434851:
        cmp esi,eax
    L_00434853:
        jl short L_00434840
    L_00434855:
        mov esi,dword ptr [data_00491c10]
    L_0043485b:
        lea edx,[ebp+664h]
    L_00434861:
        mov dword ptr [esp+30h],8
    L_00434869:
        lea esp,[esp+force_disp32_zero]
    L_00434870:
        mov ecx,dword ptr [edx]
    L_00434872:
        cmp ecx,ebx
    L_00434874:
        je short L_004348d4
    L_00434876:
        mov eax,dword ptr [esi+72DAD4h]
    L_0043487c:
        cmp eax,ebx
    L_0043487e:
        je short L_0043488d
    L_00434880:
        mov edi,dword ptr [eax]
    L_00434882:
        cmp dword ptr [edi],ecx
    L_00434884:
        je short L_004348a6
    L_00434886:
        mov eax,dword ptr [eax+4]
    L_00434889:
        cmp eax,ebx
    L_0043488b:
        jne short L_00434880
    L_0043488d:
        mov eax,dword ptr [esi+72DADCh]
    L_00434893:
        cmp eax,ebx
    L_00434895:
        je short L_004348d4
    L_00434897:
        mov edi,dword ptr [eax]
    L_00434899:
        cmp dword ptr [edi],ecx
    L_0043489b:
        je short L_004348a6
    L_0043489d:
        mov eax,dword ptr [eax+4]
    L_004348a0:
        cmp eax,ebx
    L_004348a2:
        jne short L_00434897
    L_004348a4:
        jmp short L_004348d4
    L_004348a6:
        mov eax,dword ptr [eax]
    L_004348a8:
        cmp eax,ebx
    L_004348aa:
        je short L_004348d4
    L_004348ac:
        cmp dword ptr [eax+18h],ebx
    L_004348af:
        mov ecx,1
    L_004348b4:
        mov word ptr [eax+304h],cx
    L_004348bb:
        jne short L_004348d4
    L_004348bd:
        mov eax,dword ptr [eax+14h]
    L_004348c0:
        cmp eax,ebx
    L_004348c2:
        je short L_004348d4
    L_004348c4:
        mov edi,dword ptr [eax]
    L_004348c6:
        mov word ptr [edi+304h],cx
    L_004348cd:
        mov eax,dword ptr [eax+4]
    L_004348d0:
        cmp eax,ebx
    L_004348d2:
        jne short L_004348c4
    L_004348d4:
        mov eax,dword ptr [esp+30h]
    L_004348d8:
        add edx,4
    L_004348db:
        dec eax
    L_004348dc:
        mov dword ptr [esp+30h],eax
    L_004348e0:
        jne short L_00434870
    L_004348e2:
        push ebx
    L_004348e3:
        mov edi,0Bh
    L_004348e8:
        mov ecx,492590h
    L_004348ed:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004348f2:
        mov dword ptr [ebp+20h],3
    L_004348f9:
        mov eax,dword ptr [ebp+2C0h]
    L_004348ff:
        test al,1
    L_00434901:
        jne short L_0043492c
    L_00434903:
        or eax,1
    L_00434906:
        mov dword ptr [ebp+2B4h],ebx
    L_0043490c:
        mov dword ptr [ebp+2B0h],0FFF0BDC1h
    L_00434916:
        mov dword ptr [ebp+2B8h],ebx
    L_0043491c:
        mov dword ptr [ebp+2BCh],476F78h
    L_00434926:
        mov dword ptr [ebp+2C0h],eax
    L_0043492c:
        pop edi
    L_0043492d:
        pop esi
    L_0043492e:
        mov dword ptr [ebp+2B4h],ebx
    L_00434934:
        mov dword ptr [ebp+2B8h],ebx
    L_0043493a:
        pop ebx
    L_0043493b:
        mov dword ptr [ebp+2B0h],0FFFFFFFFh
    L_00434945:
        xor eax,eax
    L_00434947:
        pop ebp
    L_00434948:
        add esp,1Ch
    L_0043494b:
        ret 4
    L_0043494e:
        cmp dword ptr [ebp+2B4h],0Ah
    L_00434955:
        jl short L_004349be
    L_00434957:
        mov esi,67h
    L_0043495c:
        mov edi,ebp
    L_0043495e:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_00434963:
        mov esi,8
    L_00434968:
        mov ecx,5Ah
    L_0043496d:
        mov eax,ebp
    L_0043496f:
        call asm_FUN_0042c770_0042c770
    L_00434974:
        mov ecx,5Bh
    L_00434979:
        mov eax,ebp
    L_0043497b:
        call asm_FUN_0042c770_0042c770
    L_00434980:
        mov esi,5Fh
    L_00434985:
        call asm_Recovery_ClearAnimationSlot_0042c6d0
    L_0043498a:
        lea eax,[ebp+5D0h]
    L_00434990:
        call asm_FUN_00409e50_00409e50
    L_00434995:
        mov ecx,2
    L_0043499a:
        mov eax,ebp
    L_0043499c:
        call asm_GameState_DisableTimerWithOwner_0042c5c0
    L_004349a1:
        push 46F018h
    L_004349a6:
        push 0
    L_004349a8:
        call asm_Recovery_ReplaceExtensionWav_00420a90
    L_004349ad:
        push 0
    L_004349af:
        push 0
    L_004349b1:
        call asm_Sound_PlayDummyRetail_00420b10
    L_004349b6:
        lea eax,[ebp+24h]
    L_004349b9:
        call asm_Score_InputHistoryStep_0044be70
    L_004349be:
        pop edi
    L_004349bf:
        pop esi
    L_004349c0:
        pop ebx
    L_004349c1:
        xor eax,eax
    L_004349c3:
        pop ebp
    L_004349c4:
        add esp,1Ch
    L_004349c7:
        ret 4
    }
}
