#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/util/heap.hpp"

// 0x00418150..0x00418161: ?Heap_DestroyOwned@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Heap_DestroyOwned_00418150() {
    __asm {
    L_00418150:
        test esi,esi
    L_00418152:
        je short L_00418161
    L_00418154:
        push esi
    L_00418155:
        call asm_FUN_00417c80_00417c80
    L_0041815a:
        push esi
    L_0041815b:
        call asm_free_004524a1
    L_00418160:
        pop ecx
    L_00418161:
        ret
    }
}

// 0x0042CDB0..0x0042CDC1: ?Heap_DestroyOwnedSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Heap_DestroyOwnedSecondary_0042cdb0() {
    __asm {
    L_0042cdb0:
        test esi,esi
    L_0042cdb2:
        je short L_0042cdc1
    L_0042cdb4:
        push esi
    L_0042cdb5:
        call asm_FUN_0042cb60_0042cb60
    L_0042cdba:
        push esi
    L_0042cdbb:
        call asm_free_004524a1
    L_0042cdc0:
        pop ecx
    L_0042cdc1:
        ret
    }
}

// 0x00435220..0x0043524E: ?LegacyString_Duplicate@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_LegacyString_Duplicate_00435220() {
    __asm {
    L_00435220:
        mov eax,edi
    L_00435222:
        lea edx,[eax+1]
    L_00435225:
        mov cl,byte ptr [eax]
    L_00435227:
        inc eax
    L_00435228:
        test cl,cl
    L_0043522a:
        jne short L_00435225
    L_0043522c:
        sub eax,edx
    L_0043522e:
        inc eax
    L_0043522f:
        push eax
    L_00435230:
        call asm_malloc_00452706
    L_00435235:
        add esp,4
    L_00435238:
        test eax,eax
    L_0043523a:
        je short L_0043524e
    L_0043523c:
        push esi
    L_0043523d:
        mov esi,eax
    L_0043523f:
        mov ecx,edi
    L_00435241:
        sub esi,edi
    L_00435243:
        mov dl,byte ptr [ecx]
    L_00435245:
        mov byte ptr [esi+ecx],dl
    L_00435248:
        inc ecx
    L_00435249:
        test dl,dl
    L_0043524b:
        jne short L_00435243
    L_0043524d:
        pop esi
    L_0043524e:
        ret
    }
}

// 0x00438260..0x00438342: ?AssignSubstring@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AssignSubstring_LegacyString_00438260() {
    __asm {
    L_00438260:
        push ebx
    L_00438261:
        push ebp
    L_00438262:
        push esi
    L_00438263:
        mov esi,dword ptr [esp+14h]
    L_00438267:
        push edi
    L_00438268:
        mov edi,dword ptr [esp+14h]
    L_0043826c:
        cmp dword ptr [edi+14h],esi
    L_0043826f:
        mov ebx,ecx
    L_00438271:
        jae short L_00438278
    L_00438273:
        call asm_FUN_00462428_00462428
    L_00438278:
        mov ebp,dword ptr [edi+14h]
    L_0043827b:
        mov eax,dword ptr [esp+1Ch]
    L_0043827f:
        sub ebp,esi
    L_00438281:
        cmp eax,ebp
    L_00438283:
        jae short L_00438287
    L_00438285:
        mov ebp,eax
    L_00438287:
        cmp ebx,edi
    L_00438289:
        jne short L_004382aa
    L_0043828b:
        push 0FFFFFFFFh
    L_0043828d:
        add ebp,esi
    L_0043828f:
        push ebp
    L_00438290:
        mov ecx,ebx
    L_00438292:
        call asm_Erase_LegacyString_00438510
    L_00438297:
        push esi
    L_00438298:
        push 0
    L_0043829a:
        mov ecx,ebx
    L_0043829c:
        call asm_Erase_LegacyString_00438510
    L_004382a1:
        pop edi
    L_004382a2:
        pop esi
    L_004382a3:
        pop ebp
    L_004382a4:
        mov eax,ebx
    L_004382a6:
        pop ebx
    L_004382a7:
        ret 0Ch
    L_004382aa:
        cmp ebp,0FFFFFFFEh
    L_004382ad:
        jbe short L_004382b6
    L_004382af:
        mov ecx,ebx
    L_004382b1:
        call asm_FUN_004624e5_004624e5
    L_004382b6:
        mov eax,dword ptr [ebx+18h]
    L_004382b9:
        cmp eax,ebp
    L_004382bb:
        jae short L_004382de
    L_004382bd:
        mov eax,dword ptr [ebx+14h]
    L_004382c0:
        push eax
    L_004382c1:
        push ebp
    L_004382c2:
        mov ecx,ebx
    L_004382c4:
        call asm_Grow_LegacyString_004386b0
    L_004382c9:
        test ebp,ebp
    L_004382cb:
        jbe short L_0043833a
    L_004382cd:
        mov ecx,dword ptr [edi+18h]
    L_004382d0:
        mov eax,10h
    L_004382d5:
        cmp ecx,eax
    L_004382d7:
        jb short L_00438308
    L_004382d9:
        mov edx,dword ptr [edi+4]
    L_004382dc:
        jmp short L_0043830b
    L_004382de:
        test ebp,ebp
    L_004382e0:
        jne short L_004382cb
    L_004382e2:
        cmp eax,10h
    L_004382e5:
        mov dword ptr [ebx+14h],ebp
    L_004382e8:
        jb short L_004382f9
    L_004382ea:
        mov eax,dword ptr [ebx+4]
    L_004382ed:
        pop edi
    L_004382ee:
        pop esi
    L_004382ef:
        mov byte ptr [eax],0
    L_004382f2:
        pop ebp
    L_004382f3:
        mov eax,ebx
    L_004382f5:
        pop ebx
    L_004382f6:
        ret 0Ch
    L_004382f9:
        pop edi
    L_004382fa:
        lea eax,[ebx+4]
    L_004382fd:
        pop esi
    L_004382fe:
        mov byte ptr [eax],0
    L_00438301:
        pop ebp
    L_00438302:
        mov eax,ebx
    L_00438304:
        pop ebx
    L_00438305:
        ret 0Ch
    L_00438308:
        lea edx,[edi+4]
    L_0043830b:
        cmp dword ptr [ebx+18h],eax
    L_0043830e:
        lea eax,[ebx+4]
    L_00438311:
        jb short L_00438317
    L_00438313:
        mov edi,dword ptr [eax]
    L_00438315:
        jmp short L_00438319
    L_00438317:
        mov edi,eax
    L_00438319:
        add esi,edx
    L_0043831b:
        mov ecx,ebp
    L_0043831d:
        mov edx,ecx
    L_0043831f:
        shr ecx,2
    L_00438322:
        rep movsd
    L_00438324:
        mov ecx,edx
    L_00438326:
        and ecx,3
    L_00438329:
        rep movsb
    L_0043832b:
        cmp dword ptr [ebx+18h],10h
    L_0043832f:
        mov dword ptr [ebx+14h],ebp
    L_00438332:
        jb short L_00438336
    L_00438334:
        mov eax,dword ptr [eax]
    L_00438336:
        mov byte ptr [eax+ebp],0
    L_0043833a:
        pop edi
    L_0043833b:
        pop esi
    L_0043833c:
        pop ebp
    L_0043833d:
        mov eax,ebx
    L_0043833f:
        pop ebx
    L_00438340:
        ret 0Ch
    }
}

// 0x00438350..0x0043835C: ?Assign@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Assign_LegacyString_00438350() {
    __asm {
    L_00438350:
        push esi
    L_00438351:
        mov esi,dword ptr [esp+8]
    L_00438355:
        mov eax,esi
    L_00438357:
        push edi
    L_00438358:
        lea edi,[eax+1]
    L_0043835b:
        TH10_REL8(0xeb, 0x0043835b, VA_asm_Assign_LegacyString_part_00438360)
    }
}

// 0x00438360..0x00438374: ?Assign@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Assign_LegacyString_part_00438360() {
    __asm {
    L_00438360:
        mov dl,byte ptr [eax]
    L_00438362:
        inc eax
    L_00438363:
        test dl,dl
    L_00438365:
        jne short L_00438360
    L_00438367:
        sub eax,edi
    L_00438369:
        push eax
    L_0043836a:
        push esi
    L_0043836b:
        call asm_AssignRange_LegacyString_00438420
    L_00438370:
        pop edi
    L_00438371:
        pop esi
    L_00438372:
        ret 4
    }
}

// 0x00438380..0x004383D2: ?Reserve@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Reserve_LegacyString_00438380() {
    __asm {
    L_00438380:
        mov al,byte ptr [esp+4]
    L_00438384:
        test al,al
    L_00438386:
        push ebx
    L_00438387:
        push ebp
    L_00438388:
        mov ebp,dword ptr [esp+10h]
    L_0043838c:
        mov ebx,ecx
    L_0043838e:
        je short L_004383bf
    L_00438390:
        cmp dword ptr [ebx+18h],10h
    L_00438394:
        jb short L_004383bf
    L_00438396:
        test ebp,ebp
    L_00438398:
        mov eax,dword ptr [ebx+4]
    L_0043839b:
        push edi
    L_0043839c:
        lea edi,[ebx+4]
    L_0043839f:
        jbe short L_004383b5
    L_004383a1:
        push esi
    L_004383a2:
        mov ecx,ebp
    L_004383a4:
        mov edx,ecx
    L_004383a6:
        shr ecx,2
    L_004383a9:
        mov esi,eax
    L_004383ab:
        rep movsd
    L_004383ad:
        mov ecx,edx
    L_004383af:
        and ecx,3
    L_004383b2:
        rep movsb
    L_004383b4:
        pop esi
    L_004383b5:
        push eax
    L_004383b6:
        call asm_free_004524a1
    L_004383bb:
        add esp,4
    L_004383be:
        pop edi
    L_004383bf:
        mov dword ptr [ebx+14h],ebp
    L_004383c2:
        mov dword ptr [ebx+18h],0Fh
    L_004383c9:
        mov byte ptr [ebx+ebp+4],0
    L_004383ce:
        pop ebp
    L_004383cf:
        pop ebx
    L_004383d0:
        ret 8
    }
}

// 0x00438420..0x00438509: ?AssignRange@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AssignRange_LegacyString_00438420() {
    __asm {
    L_00438420:
        push ebx
    L_00438421:
        mov ebx,ecx
    L_00438423:
        mov edx,dword ptr [ebx+18h]
    L_00438426:
        cmp edx,10h
    L_00438429:
        push esi
    L_0043842a:
        push edi
    L_0043842b:
        jb short L_00438432
    L_0043842d:
        mov eax,dword ptr [ebx+4]
    L_00438430:
        jmp short L_00438435
    L_00438432:
        lea eax,[ebx+4]
    L_00438435:
        mov esi,dword ptr [esp+10h]
    L_00438439:
        cmp esi,eax
    L_0043843b:
        jb short L_00438471
    L_0043843d:
        cmp edx,10h
    L_00438440:
        lea eax,[ebx+4]
    L_00438443:
        jb short L_00438449
    L_00438445:
        mov ecx,dword ptr [eax]
    L_00438447:
        jmp short L_0043844b
    L_00438449:
        mov ecx,eax
    L_0043844b:
        mov edi,dword ptr [ebx+14h]
    L_0043844e:
        add edi,ecx
    L_00438450:
        cmp edi,esi
    L_00438452:
        jbe short L_00438471
    L_00438454:
        cmp edx,10h
    L_00438457:
        jb short L_0043845b
    L_00438459:
        mov eax,dword ptr [eax]
    L_0043845b:
        mov ecx,dword ptr [esp+14h]
    L_0043845f:
        push ecx
    L_00438460:
        sub esi,eax
    L_00438462:
        push esi
    L_00438463:
        push ebx
    L_00438464:
        mov ecx,ebx
    L_00438466:
        call asm_AssignSubstring_LegacyString_00438260
    L_0043846b:
        pop edi
    L_0043846c:
        pop esi
    L_0043846d:
        pop ebx
    L_0043846e:
        ret 8
    L_00438471:
        push ebp
    L_00438472:
        mov ebp,dword ptr [esp+18h]
    L_00438476:
        cmp ebp,0FFFFFFFEh
    L_00438479:
        jbe short L_00438482
    L_0043847b:
        mov ecx,ebx
    L_0043847d:
        call asm_FUN_004624e5_004624e5
    L_00438482:
        mov eax,dword ptr [ebx+18h]
    L_00438485:
        cmp eax,ebp
    L_00438487:
        jae short L_004384a4
    L_00438489:
        mov edx,dword ptr [ebx+14h]
    L_0043848c:
        push edx
    L_0043848d:
        push ebp
    L_0043848e:
        mov ecx,ebx
    L_00438490:
        call asm_Grow_LegacyString_004386b0
    L_00438495:
        test ebp,ebp
    L_00438497:
        jbe short L_00438501
    L_00438499:
        cmp dword ptr [ebx+18h],10h
    L_0043849d:
        jb short L_004384ce
    L_0043849f:
        mov edi,dword ptr [ebx+4]
    L_004384a2:
        jmp short L_004384d1
    L_004384a4:
        test ebp,ebp
    L_004384a6:
        jne short L_00438497
    L_004384a8:
        cmp eax,10h
    L_004384ab:
        mov dword ptr [ebx+14h],ebp
    L_004384ae:
        jb short L_004384bf
    L_004384b0:
        mov eax,dword ptr [ebx+4]
    L_004384b3:
        pop ebp
    L_004384b4:
        pop edi
    L_004384b5:
        mov byte ptr [eax],0
    L_004384b8:
        pop esi
    L_004384b9:
        mov eax,ebx
    L_004384bb:
        pop ebx
    L_004384bc:
        ret 8
    L_004384bf:
        pop ebp
    L_004384c0:
        lea eax,[ebx+4]
    L_004384c3:
        pop edi
    L_004384c4:
        mov byte ptr [eax],0
    L_004384c7:
        pop esi
    L_004384c8:
        mov eax,ebx
    L_004384ca:
        pop ebx
    L_004384cb:
        ret 8
    L_004384ce:
        lea edi,[ebx+4]
    L_004384d1:
        mov ecx,ebp
    L_004384d3:
        mov eax,ecx
    L_004384d5:
        shr ecx,2
    L_004384d8:
        rep movsd
    L_004384da:
        mov ecx,eax
    L_004384dc:
        and ecx,3
    L_004384df:
        rep movsb
    L_004384e1:
        cmp dword ptr [ebx+18h],10h
    L_004384e5:
        mov dword ptr [ebx+14h],ebp
    L_004384e8:
        jb short L_004384fa
    L_004384ea:
        mov eax,dword ptr [ebx+4]
    L_004384ed:
        mov byte ptr [eax+ebp],0
    L_004384f1:
        pop ebp
    L_004384f2:
        pop edi
    L_004384f3:
        pop esi
    L_004384f4:
        mov eax,ebx
    L_004384f6:
        pop ebx
    L_004384f7:
        ret 8
    L_004384fa:
        lea eax,[ebx+4]
    L_004384fd:
        mov byte ptr [eax+ebp],0
    L_00438501:
        pop ebp
    L_00438502:
        pop edi
    L_00438503:
        pop esi
    L_00438504:
        mov eax,ebx
    L_00438506:
        pop ebx
    L_00438507:
        ret 8
    }
}

// 0x00438510..0x00438584: ?Erase@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Erase_LegacyString_00438510() {
    __asm {
    L_00438510:
        push ebp
    L_00438511:
        mov ebp,dword ptr [esp+8]
    L_00438515:
        push esi
    L_00438516:
        mov esi,ecx
    L_00438518:
        cmp dword ptr [esi+14h],ebp
    L_0043851b:
        push edi
    L_0043851c:
        jae short L_00438523
    L_0043851e:
        call asm_FUN_00462428_00462428
    L_00438523:
        mov eax,dword ptr [esi+14h]
    L_00438526:
        mov edi,dword ptr [esp+14h]
    L_0043852a:
        sub eax,ebp
    L_0043852c:
        cmp eax,edi
    L_0043852e:
        jae short L_00438532
    L_00438530:
        mov edi,eax
    L_00438532:
        test edi,edi
    L_00438534:
        jbe short L_0043857d
    L_00438536:
        mov ecx,dword ptr [esi+18h]
    L_00438539:
        cmp ecx,10h
    L_0043853c:
        push ebx
    L_0043853d:
        lea ebx,[esi+4]
    L_00438540:
        jb short L_00438546
    L_00438542:
        mov edx,dword ptr [ebx]
    L_00438544:
        jmp short L_00438548
    L_00438546:
        mov edx,ebx
    L_00438548:
        cmp ecx,10h
    L_0043854b:
        jb short L_00438551
    L_0043854d:
        mov ecx,dword ptr [ebx]
    L_0043854f:
        jmp short L_00438553
    L_00438551:
        mov ecx,ebx
    L_00438553:
        sub eax,edi
    L_00438555:
        add edx,ebp
    L_00438557:
        push eax
    L_00438558:
        add edx,edi
    L_0043855a:
        push edx
    L_0043855b:
        add ecx,ebp
    L_0043855d:
        push ecx
    L_0043855e:
        call asm_memmove_00453280
    L_00438563:
        mov eax,dword ptr [esi+14h]
    L_00438566:
        mov ecx,dword ptr [esi+18h]
    L_00438569:
        sub eax,edi
    L_0043856b:
        add esp,0Ch
    L_0043856e:
        cmp ecx,10h
    L_00438571:
        mov dword ptr [esi+14h],eax
    L_00438574:
        jb short L_00438578
    L_00438576:
        mov ebx,dword ptr [ebx]
    L_00438578:
        mov byte ptr [ebx+eax],0
    L_0043857c:
        pop ebx
    L_0043857d:
        pop edi
    L_0043857e:
        mov eax,esi
    L_00438580:
        pop esi
    L_00438581:
        pop ebp
    L_00438582:
        ret 8
    }
}

// 0x00438590..0x004385AE: update the logical length and terminate the active
// inline or heap-backed character buffer.
void LegacyString::SetLength(uint32_t new_length) {
    length = new_length;

    char* data;
    if (capacity >= 16)
        data = storage.heap_data;
    else
        data = storage.inline_data;
    data[new_length] = 0;
}

// 0x004386B0..0x00438722: ?Grow@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Grow_LegacyString_004386b0() {
    __asm {
    L_004386b0:
        push ebp
    L_004386b1:
        mov ebp,esp
    L_004386b3:
        push 0FFFFFFFFh
    L_004386b5:
        push 465370h
    L_004386ba:
        mov eax,dword ptr fs:[0]
    L_004386c0:
        push eax
    L_004386c1:
        mov dword ptr fs:[0],esp
    L_004386c8:
        sub esp,0Ch
    L_004386cb:
        mov eax,dword ptr [ebp+8]
    L_004386ce:
        push ebx
    L_004386cf:
        push esi
    L_004386d0:
        mov ebx,eax
    L_004386d2:
        or ebx,0Fh
    L_004386d5:
        cmp ebx,0FFFFFFFEh
    L_004386d8:
        push edi
    L_004386d9:
        mov esi,ecx
    L_004386db:
        mov dword ptr [ebp-10h],esp
    L_004386de:
        mov dword ptr [ebp-14h],esi
    L_004386e1:
        jbe short L_004386e7
    L_004386e3:
        mov ebx,eax
    L_004386e5:
        jmp short L_00438709
    L_004386e7:
        mov edi,dword ptr [esi+18h]
    L_004386ea:
        mov eax,0AAAAAAABh
    L_004386ef:
        mul ebx
    L_004386f1:
        mov ecx,edi
    L_004386f3:
        shr ecx,1
    L_004386f5:
        shr edx,1
    L_004386f7:
        cmp edx,ecx
    L_004386f9:
        jae short L_00438709
    L_004386fb:
        mov eax,0FFFFFFFEh
    L_00438700:
        sub eax,ecx
    L_00438702:
        cmp edi,eax
    L_00438704:
        ja short L_00438709
    L_00438706:
        lea ebx,[ecx+edi]
    L_00438709:
        lea ecx,[ebx+1]
    L_0043870c:
        push ecx
    L_0043870d:
        mov dword ptr [ebp-4],0
    L_00438714:
        call asm_operator_new_00452493
    L_00438719:
        mov edx,eax
    L_0043871b:
        add esp,4
    L_0043871e:
        mov dword ptr [ebp+8],edx
    L_00438721:
        TH10_REL8(0xeb, 0x00438721, VA_asm_FUN_0043874c_0043874c)
    }
}

// 0x0043874C..0x004387C1: FUN_0043874c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043874c_0043874c() {
    __asm {
    L_0043874c:
        mov ecx,dword ptr [ebp+0Ch]
    L_0043874f:
        test ecx,ecx
    L_00438751:
        mov dword ptr [ebp-4],0FFFFFFFFh
    L_00438758:
        jbe short L_0043877e
    L_0043875a:
        cmp dword ptr [esi+18h],10h
    L_0043875e:
        jb short L_00438765
    L_00438760:
        mov esi,dword ptr [esi+4]
    L_00438763:
        jmp short L_00438768
    L_00438765:
        add esi,4
    L_00438768:
        mov eax,ecx
    L_0043876a:
        shr ecx,2
    L_0043876d:
        mov edi,edx
    L_0043876f:
        rep movsd
    L_00438771:
        mov ecx,eax
    L_00438773:
        and ecx,3
    L_00438776:
        rep movsb
    L_00438778:
        mov esi,dword ptr [ebp-14h]
    L_0043877b:
        mov ecx,dword ptr [ebp+0Ch]
    L_0043877e:
        cmp dword ptr [esi+18h],10h
    L_00438782:
        jb short L_00438796
    L_00438784:
        mov ecx,dword ptr [esi+4]
    L_00438787:
        push ecx
    L_00438788:
        call asm_free_004524a1
    L_0043878d:
        mov edx,dword ptr [ebp+8]
    L_00438790:
        mov ecx,dword ptr [ebp+0Ch]
    L_00438793:
        add esp,4
    L_00438796:
        cmp ebx,10h
    L_00438799:
        lea eax,[esi+4]
    L_0043879c:
        mov byte ptr [eax],0
    L_0043879f:
        mov dword ptr [eax],edx
    L_004387a1:
        mov dword ptr [esi+18h],ebx
    L_004387a4:
        mov dword ptr [esi+14h],ecx
    L_004387a7:
        jb short L_004387ab
    L_004387a9:
        mov eax,edx
    L_004387ab:
        pop edi
    L_004387ac:
        mov byte ptr [eax+ecx],0
    L_004387b0:
        mov ecx,dword ptr [ebp-0Ch]
    L_004387b3:
        pop esi
    L_004387b4:
        mov dword ptr fs:[0],ecx
    L_004387bb:
        pop ebx
    L_004387bc:
        mov esp,ebp
    L_004387be:
        pop ebp
    L_004387bf:
        ret 8
    }
}

// Recovered semantic C++ definitions.

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void __cdecl entry_free_004524a1(void*);
#ifdef _MSC_VER
void* __cdecl operator new(uint32_t size);
#else
void* operator new(decltype(sizeof(0)) size);
#endif

HeapBuffer::HeapBuffer() : data(0) {
}

void* LegacyAllocator::Allocate(uint32_t count) {
    return ::operator new(count);
}

void LegacyAllocator::Deallocate(void* memory, uint32_t count) {
    (void)count;
    entry_free_004524a1(memory);
}

uint32_t LegacyAllocator::MaxSize() const {
    return 0xFFFFFFFE;
}

void __fastcall HeapBuffer_Release(HeapBuffer* buffer) {
    void* data = buffer->data;
    if (data != 0) {
        entry_free_00452422(data);
        buffer->data = 0;
    }
}

void __fastcall LegacyString_Clear(LegacyString* string) {
    if (string->capacity >= 16)
        entry_free_004524a1(string->storage.heap_data);
    string->capacity = 15;
    string->length = 0;
    string->storage.inline_data[0] = 0;
}

uint32_t LegacyString::Length() const {
    return length;
}

bool LegacyString::OwnsPointer(const char* pointer) const {
    if (pointer >= Data() && Data() + length > pointer)
        return true;
    return false;
}

char* LegacyString::Data() {
    if (capacity >= 16)
        return (char*)storage.heap_data;
    return storage.inline_data;
}

const char* LegacyString::Data() const {
    if (capacity >= 16)
        return (const char*)storage.heap_data;
    return storage.inline_data;
}
