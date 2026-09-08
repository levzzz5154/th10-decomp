#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041A200..0x0041AAC6: FUN_0041a200
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041a200_0041a200() {
    __asm {
    L_0041a200:
        push ebp
    L_0041a201:
        mov ebp,esp
    L_0041a203:
        and esp,0FFFFFFF8h
    L_0041a206:
        sub esp,4Ch
    L_0041a209:
        push ebx
    L_0041a20a:
        push esi
    L_0041a20b:
        push edi
    L_0041a20c:
        push 1000h
    L_0041a211:
        call asm_malloc_00452706
    L_0041a216:
        push 46D574h
    L_0041a21b:
        mov edi,eax
    L_0041a21d:
        call asm_FUN_00452abc_00452abc
    L_0041a222:
        mov eax,dword ptr [ebp+0Ch]
    L_0041a225:
        add esp,8
    L_0041a228:
        push eax
    L_0041a229:
        call asm_File_OpenSharedWrite_0044b620
    L_0041a22e:
        test eax,eax
    L_0041a230:
        jne asm_target_0041aa79
    L_0041a236:
        push 46D534h
    L_0041a23b:
        push edi
    L_0041a23c:
        call asm_sprintf_00452ae8
    L_0041a241:
        mov eax,edi
    L_0041a243:
        add esp,8
    L_0041a246:
        lea edx,[eax+1]
    L_0041a249:
        lea esp,[esp+force_disp32_zero]
    L_0041a250:
        mov cl,byte ptr [eax]
    L_0041a252:
        inc eax
    L_0041a253:
        test cl,cl
    L_0041a255:
        jne short L_0041a250
    L_0041a257:
        sub eax,edx
    L_0041a259:
        mov esi,eax
    L_0041a25b:
        mov edx,edi
    L_0041a25d:
        call asm_File_WriteShared_0044b740
    L_0041a262:
        push 46D510h
    L_0041a267:
        push edi
    L_0041a268:
        call asm_sprintf_00452ae8
    L_0041a26d:
        mov eax,edi
    L_0041a26f:
        add esp,8
    L_0041a272:
        lea edx,[eax+1]
    L_0041a275:
        mov cl,byte ptr [eax]
    L_0041a277:
        inc eax
    L_0041a278:
        test cl,cl
    L_0041a27a:
        jne short L_0041a275
    L_0041a27c:
        sub eax,edx
    L_0041a27e:
        mov esi,eax
    L_0041a280:
        mov edx,edi
    L_0041a282:
        call asm_File_WriteShared_0044b740
    L_0041a287:
        push 46D50Ch
    L_0041a28c:
        push edi
    L_0041a28d:
        call asm_sprintf_00452ae8
    L_0041a292:
        mov eax,edi
    L_0041a294:
        add esp,8
    L_0041a297:
        lea edx,[eax+1]
    L_0041a29a:
        lea ebx,[ebx+force_disp32_zero]
    L_0041a2a0:
        mov cl,byte ptr [eax]
    L_0041a2a2:
        inc eax
    L_0041a2a3:
        test cl,cl
    L_0041a2a5:
        jne short L_0041a2a0
    L_0041a2a7:
        sub eax,edx
    L_0041a2a9:
        mov esi,eax
    L_0041a2ab:
        mov edx,edi
    L_0041a2ad:
        call asm_File_WriteShared_0044b740
    L_0041a2b2:
        push 46D4D8h
    L_0041a2b7:
        push edi
    L_0041a2b8:
        call asm_sprintf_00452ae8
    L_0041a2bd:
        mov eax,edi
    L_0041a2bf:
        add esp,8
    L_0041a2c2:
        lea edx,[eax+1]
    L_0041a2c5:
        mov cl,byte ptr [eax]
    L_0041a2c7:
        inc eax
    L_0041a2c8:
        test cl,cl
    L_0041a2ca:
        jne short L_0041a2c5
    L_0041a2cc:
        sub eax,edx
    L_0041a2ce:
        mov esi,eax
    L_0041a2d0:
        mov edx,edi
    L_0041a2d2:
        call asm_File_WriteShared_0044b740
    L_0041a2d7:
        push 46D490h
    L_0041a2dc:
        push edi
    L_0041a2dd:
        call asm_sprintf_00452ae8
    L_0041a2e2:
        mov eax,edi
    L_0041a2e4:
        add esp,8
    L_0041a2e7:
        lea edx,[eax+1]
    L_0041a2ea:
        lea ebx,[ebx+force_disp32_zero]
    L_0041a2f0:
        mov cl,byte ptr [eax]
    L_0041a2f2:
        inc eax
    L_0041a2f3:
        test cl,cl
    L_0041a2f5:
        jne short L_0041a2f0
    L_0041a2f7:
        sub eax,edx
    L_0041a2f9:
        mov esi,eax
    L_0041a2fb:
        mov edx,edi
    L_0041a2fd:
        call asm_File_WriteShared_0044b740
    L_0041a302:
        push 46D50Ch
    L_0041a307:
        push edi
    L_0041a308:
        call asm_sprintf_00452ae8
    L_0041a30d:
        mov eax,edi
    L_0041a30f:
        add esp,8
    L_0041a312:
        lea edx,[eax+1]
    L_0041a315:
        mov cl,byte ptr [eax]
    L_0041a317:
        inc eax
    L_0041a318:
        test cl,cl
    L_0041a31a:
        jne short L_0041a315
    L_0041a31c:
        sub eax,edx
    L_0041a31e:
        mov esi,eax
    L_0041a320:
        mov edx,edi
    L_0041a322:
        call asm_File_WriteShared_0044b740
    L_0041a327:
        lea ecx,[esp+18h]
    L_0041a32b:
        push ecx
    L_0041a32c:
        call asm_FID_conflict___time32_00452b71
    L_0041a331:
        lea edx,[esp+1Ch]
    L_0041a335:
        push edx
    L_0041a336:
        call asm_localtime_00452baa
    L_0041a33b:
        mov ecx,dword ptr [eax+4]
    L_0041a33e:
        mov edx,dword ptr [eax+8]
    L_0041a341:
        push ecx
    L_0041a342:
        mov ecx,dword ptr [eax+0Ch]
    L_0041a345:
        push edx
    L_0041a346:
        mov edx,dword ptr [eax+10h]
    L_0041a349:
        mov eax,dword ptr [eax+14h]
    L_0041a34c:
        push ecx
    L_0041a34d:
        inc edx
    L_0041a34e:
        push edx
    L_0041a34f:
        add eax,76Ch
    L_0041a354:
        push eax
    L_0041a355:
        push 46D440h
    L_0041a35a:
        push edi
    L_0041a35b:
        call asm_sprintf_00452ae8
    L_0041a360:
        mov eax,edi
    L_0041a362:
        add esp,24h
    L_0041a365:
        lea edx,[eax+1]
    L_0041a368:
        mov cl,byte ptr [eax]
    L_0041a36a:
        inc eax
    L_0041a36b:
        test cl,cl
    L_0041a36d:
        jne short L_0041a368
    L_0041a36f:
        sub eax,edx
    L_0041a371:
        mov esi,eax
    L_0041a373:
        mov edx,edi
    L_0041a375:
        call asm_File_WriteShared_0044b740
    L_0041a37a:
        push 46D434h
    L_0041a37f:
        push edi
    L_0041a380:
        call asm_sprintf_00452ae8
    L_0041a385:
        mov eax,edi
    L_0041a387:
        add esp,8
    L_0041a38a:
        lea edx,[eax+1]
    L_0041a38d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041a390:
        mov cl,byte ptr [eax]
    L_0041a392:
        inc eax
    L_0041a393:
        test cl,cl
    L_0041a395:
        jne short L_0041a390
    L_0041a397:
        sub eax,edx
    L_0041a399:
        mov esi,eax
    L_0041a39b:
        mov edx,edi
    L_0041a39d:
        call asm_File_WriteShared_0044b740
    L_0041a3a2:
        push 46D654h
    L_0041a3a7:
        push 46D420h
    L_0041a3ac:
        push edi
    L_0041a3ad:
        call asm_sprintf_00452ae8
    L_0041a3b2:
        mov eax,edi
    L_0041a3b4:
        add esp,0Ch
    L_0041a3b7:
        lea edx,[eax+1]
    L_0041a3ba:
        lea ebx,[ebx+force_disp32_zero]
    L_0041a3c0:
        mov cl,byte ptr [eax]
    L_0041a3c2:
        inc eax
    L_0041a3c3:
        test cl,cl
    L_0041a3c5:
        jne short L_0041a3c0
    L_0041a3c7:
        sub eax,edx
    L_0041a3c9:
        mov esi,eax
    L_0041a3cb:
        mov edx,edi
    L_0041a3cd:
        call asm_File_WriteShared_0044b740
    L_0041a3d2:
        mov ecx,dword ptr [ebp+8]
    L_0041a3d5:
        add ecx,7Ch
    L_0041a3d8:
        mov dword ptr [esp+0Ch],0
    L_0041a3e0:
        mov dword ptr [esp+14h],ecx
    L_0041a3e4:
        mov edx,dword ptr [esp+14h]
    L_0041a3e8:
        mov eax,dword ptr [edx]
    L_0041a3ea:
        test eax,eax
    L_0041a3ec:
        mov dword ptr [esp+10h],0
    L_0041a3f4:
        je asm_target_0041aa5c
    L_0041a3fa:
        lea ebx,[ebx+force_disp32_zero]
    L_0041a400:
        mov ecx,dword ptr [eax+4]
    L_0041a403:
        mov ebx,dword ptr [eax]
    L_0041a405:
        mov eax,dword ptr [ebx+70h]
    L_0041a408:
        test eax,eax
    L_0041a40a:
        mov dword ptr [esp+18h],ecx
    L_0041a40e:
        jne short L_0041a417
    L_0041a410:
        mov eax,ecx
    L_0041a412:
        jmp asm_target_0041a9f0
    L_0041a417:
        mov eax,dword ptr [esp+10h]
    L_0041a41b:
        test eax,eax
    L_0041a41d:
        jne asm_target_0041a4e0
    L_0041a423:
        push 46D3F8h
    L_0041a428:
        push edi
    L_0041a429:
        call asm_sprintf_00452ae8
    L_0041a42e:
        mov eax,edi
    L_0041a430:
        add esp,8
    L_0041a433:
        lea edx,[eax+1]
    L_0041a436:
        mov cl,byte ptr [eax]
    L_0041a438:
        inc eax
    L_0041a439:
        test cl,cl
    L_0041a43b:
        jne short L_0041a436
    L_0041a43d:
        sub eax,edx
    L_0041a43f:
        mov esi,eax
    L_0041a441:
        mov eax,dword ptr [data_00474c38]
    L_0041a446:
        cmp eax,0FFFFFFFFh
    L_0041a449:
        je short L_0041a47f
    L_0041a44b:
        push 0
    L_0041a44d:
        lea ecx,[esp+20h]
    L_0041a451:
        push ecx
    L_0041a452:
        push esi
    L_0041a453:
        push edi
    L_0041a454:
        push eax
    L_0041a455:
        call dword ptr [data_004660d4]
    L_0041a45b:
        cmp esi,dword ptr [esp+1Ch]
    L_0041a45f:
        je short L_0041a47f
    L_0041a461:
        mov edx,dword ptr [data_00474c38]
    L_0041a467:
        push edx
    L_0041a468:
        call dword ptr [data_004660cc]
    L_0041a46e:
        push 4922A4h
    L_0041a473:
        call dword ptr [data_004660b4]
    L_0041a479:
        dec byte ptr [data_0049231e]
    L_0041a47f:
        mov eax,dword ptr [esp+0Ch]
    L_0041a483:
        push eax
    L_0041a484:
        push 46D3E8h
    L_0041a489:
        push edi
    L_0041a48a:
        call asm_sprintf_00452ae8
    L_0041a48f:
        mov eax,edi
    L_0041a491:
        add esp,0Ch
    L_0041a494:
        lea edx,[eax+1]
    L_0041a497:
        mov cl,byte ptr [eax]
    L_0041a499:
        inc eax
    L_0041a49a:
        test cl,cl
    L_0041a49c:
        jne short L_0041a497
    L_0041a49e:
        sub eax,edx
    L_0041a4a0:
        mov esi,eax
    L_0041a4a2:
        mov eax,dword ptr [data_00474c38]
    L_0041a4a7:
        cmp eax,0FFFFFFFFh
    L_0041a4aa:
        je short L_0041a4e0
    L_0041a4ac:
        push 0
    L_0041a4ae:
        lea ecx,[esp+24h]
    L_0041a4b2:
        push ecx
    L_0041a4b3:
        push esi
    L_0041a4b4:
        push edi
    L_0041a4b5:
        push eax
    L_0041a4b6:
        call dword ptr [data_004660d4]
    L_0041a4bc:
        cmp esi,dword ptr [esp+20h]
    L_0041a4c0:
        je short L_0041a4e0
    L_0041a4c2:
        mov edx,dword ptr [data_00474c38]
    L_0041a4c8:
        push edx
    L_0041a4c9:
        call dword ptr [data_004660cc]
    L_0041a4cf:
        push 4922A4h
    L_0041a4d4:
        call dword ptr [data_004660b4]
    L_0041a4da:
        dec byte ptr [data_0049231e]
    L_0041a4e0:
        mov eax,dword ptr [esp+0Ch]
    L_0041a4e4:
        push eax
    L_0041a4e5:
        push 46D3E0h
    L_0041a4ea:
        push edi
    L_0041a4eb:
        call asm_sprintf_00452ae8
    L_0041a4f0:
        mov eax,edi
    L_0041a4f2:
        add esp,0Ch
    L_0041a4f5:
        lea edx,[eax+1]
    L_0041a4f8:
        mov cl,byte ptr [eax]
    L_0041a4fa:
        inc eax
    L_0041a4fb:
        test cl,cl
    L_0041a4fd:
        jne short L_0041a4f8
    L_0041a4ff:
        sub eax,edx
    L_0041a501:
        mov esi,eax
    L_0041a503:
        mov eax,dword ptr [data_00474c38]
    L_0041a508:
        cmp eax,0FFFFFFFFh
    L_0041a50b:
        je short L_0041a542
    L_0041a50d:
        push 0
    L_0041a50f:
        lea ecx,[esp+28h]
    L_0041a513:
        push ecx
    L_0041a514:
        push esi
    L_0041a515:
        push edi
    L_0041a516:
        mov edx,eax
    L_0041a518:
        push edx
    L_0041a519:
        call dword ptr [data_004660d4]
    L_0041a51f:
        cmp esi,dword ptr [esp+24h]
    L_0041a523:
        je short L_0041a542
    L_0041a525:
        mov eax,dword ptr [data_00474c38]
    L_0041a52a:
        push eax
    L_0041a52b:
        call dword ptr [data_004660cc]
    L_0041a531:
        push 4922A4h
    L_0041a536:
        call dword ptr [data_004660b4]
    L_0041a53c:
        dec byte ptr [data_0049231e]
    L_0041a542:
        mov eax,dword ptr [ebx+70h]
    L_0041a545:
        test eax,eax
    L_0041a547:
        jle short L_0041a558
    L_0041a549:
        push eax
    L_0041a54a:
        push 46D3D0h
    L_0041a54f:
        push edi
    L_0041a550:
        call asm_sprintf_00452ae8
    L_0041a555:
        add esp,0Ch
    L_0041a558:
        mov eax,edi
    L_0041a55a:
        lea edx,[eax+1]
    L_0041a55d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041a560:
        mov cl,byte ptr [eax]
    L_0041a562:
        inc eax
    L_0041a563:
        test cl,cl
    L_0041a565:
        jne short L_0041a560
    L_0041a567:
        sub eax,edx
    L_0041a569:
        mov esi,eax
    L_0041a56b:
        mov eax,dword ptr [data_00474c38]
    L_0041a570:
        cmp eax,0FFFFFFFFh
    L_0041a573:
        je short L_0041a5aa
    L_0041a575:
        push 0
    L_0041a577:
        lea ecx,[esp+2Ch]
    L_0041a57b:
        push ecx
    L_0041a57c:
        push esi
    L_0041a57d:
        push edi
    L_0041a57e:
        mov edx,eax
    L_0041a580:
        push edx
    L_0041a581:
        call dword ptr [data_004660d4]
    L_0041a587:
        cmp esi,dword ptr [esp+28h]
    L_0041a58b:
        je short L_0041a5aa
    L_0041a58d:
        mov eax,dword ptr [data_00474c38]
    L_0041a592:
        push eax
    L_0041a593:
        call dword ptr [data_004660cc]
    L_0041a599:
        push 4922A4h
    L_0041a59e:
        call dword ptr [data_004660b4]
    L_0041a5a4:
        dec byte ptr [data_0049231e]
    L_0041a5aa:
        lea ecx,[ebx+1Ch]
    L_0041a5ad:
        push ecx
    L_0041a5ae:
        push 46D3C0h
    L_0041a5b3:
        push edi
    L_0041a5b4:
        call asm_sprintf_00452ae8
    L_0041a5b9:
        mov eax,edi
    L_0041a5bb:
        add esp,0Ch
    L_0041a5be:
        lea edx,[eax+1]
    L_0041a5c1:
        mov cl,byte ptr [eax]
    L_0041a5c3:
        inc eax
    L_0041a5c4:
        test cl,cl
    L_0041a5c6:
        jne short L_0041a5c1
    L_0041a5c8:
        sub eax,edx
    L_0041a5ca:
        mov esi,eax
    L_0041a5cc:
        mov eax,dword ptr [data_00474c38]
    L_0041a5d1:
        cmp eax,0FFFFFFFFh
    L_0041a5d4:
        je short L_0041a609
    L_0041a5d6:
        push 0
    L_0041a5d8:
        lea edx,[esp+30h]
    L_0041a5dc:
        push edx
    L_0041a5dd:
        push esi
    L_0041a5de:
        push edi
    L_0041a5df:
        push eax
    L_0041a5e0:
        call dword ptr [data_004660d4]
    L_0041a5e6:
        cmp esi,dword ptr [esp+2Ch]
    L_0041a5ea:
        je short L_0041a609
    L_0041a5ec:
        mov eax,dword ptr [data_00474c38]
    L_0041a5f1:
        push eax
    L_0041a5f2:
        call dword ptr [data_004660cc]
    L_0041a5f8:
        push 4922A4h
    L_0041a5fd:
        call dword ptr [data_004660b4]
    L_0041a603:
        dec byte ptr [data_0049231e]
    L_0041a609:
        fld dword ptr [ebx+4]
    L_0041a60c:
        call asm_FUN_00463b2c_00463b2c
    L_0041a611:
        fld dword ptr [ebx]
    L_0041a613:
        push eax
    L_0041a614:
        call asm_FUN_00463b2c_00463b2c
    L_0041a619:
        push eax
    L_0041a61a:
        push 46D3ACh
    L_0041a61f:
        push edi
    L_0041a620:
        call asm_sprintf_00452ae8
    L_0041a625:
        mov eax,edi
    L_0041a627:
        add esp,10h
    L_0041a62a:
        lea edx,[eax+1]
    L_0041a62d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041a630:
        mov cl,byte ptr [eax]
    L_0041a632:
        inc eax
    L_0041a633:
        test cl,cl
    L_0041a635:
        jne short L_0041a630
    L_0041a637:
        sub eax,edx
    L_0041a639:
        mov esi,eax
    L_0041a63b:
        mov eax,dword ptr [data_00474c38]
    L_0041a640:
        cmp eax,0FFFFFFFFh
    L_0041a643:
        je short L_0041a679
    L_0041a645:
        push 0
    L_0041a647:
        lea ecx,[esp+34h]
    L_0041a64b:
        push ecx
    L_0041a64c:
        push esi
    L_0041a64d:
        push edi
    L_0041a64e:
        push eax
    L_0041a64f:
        call dword ptr [data_004660d4]
    L_0041a655:
        cmp esi,dword ptr [esp+30h]
    L_0041a659:
        je short L_0041a679
    L_0041a65b:
        mov edx,dword ptr [data_00474c38]
    L_0041a661:
        push edx
    L_0041a662:
        call dword ptr [data_004660cc]
    L_0041a668:
        push 4922A4h
    L_0041a66d:
        call dword ptr [data_004660b4]
    L_0041a673:
        dec byte ptr [data_0049231e]
    L_0041a679:
        mov eax,dword ptr [ebx+60h]
    L_0041a67c:
        push eax
    L_0041a67d:
        push 46D39Ch
    L_0041a682:
        push edi
    L_0041a683:
        call asm_sprintf_00452ae8
    L_0041a688:
        mov eax,edi
    L_0041a68a:
        add esp,0Ch
    L_0041a68d:
        lea edx,[eax+1]
    L_0041a690:
        mov cl,byte ptr [eax]
    L_0041a692:
        inc eax
    L_0041a693:
        test cl,cl
    L_0041a695:
        jne short L_0041a690
    L_0041a697:
        sub eax,edx
    L_0041a699:
        mov esi,eax
    L_0041a69b:
        mov eax,dword ptr [data_00474c38]
    L_0041a6a0:
        cmp eax,0FFFFFFFFh
    L_0041a6a3:
        je short L_0041a6d9
    L_0041a6a5:
        push 0
    L_0041a6a7:
        lea ecx,[esp+38h]
    L_0041a6ab:
        push ecx
    L_0041a6ac:
        push esi
    L_0041a6ad:
        push edi
    L_0041a6ae:
        push eax
    L_0041a6af:
        call dword ptr [data_004660d4]
    L_0041a6b5:
        cmp esi,dword ptr [esp+34h]
    L_0041a6b9:
        je short L_0041a6d9
    L_0041a6bb:
        mov edx,dword ptr [data_00474c38]
    L_0041a6c1:
        push edx
    L_0041a6c2:
        call dword ptr [data_004660cc]
    L_0041a6c8:
        push 4922A4h
    L_0041a6cd:
        call dword ptr [data_004660b4]
    L_0041a6d3:
        dec byte ptr [data_0049231e]
    L_0041a6d9:
        mov ecx,dword ptr [ebx+68h]
    L_0041a6dc:
        xor eax,eax
    L_0041a6de:
        mov edi,edi
    L_0041a6e0:
        cmp dword ptr [eax*8+4744B4h],ecx
    L_0041a6e7:
        je asm_target_0041aaaf
    L_0041a6ed:
        inc eax
    L_0041a6ee:
        cmp eax,3Dh
    L_0041a6f1:
        jl short L_0041a6e0
    L_0041a6f3:
        xor eax,eax
    L_0041a6f5:
        push eax
    L_0041a6f6:
        push 46D38Ch
    L_0041a6fb:
        push edi
    L_0041a6fc:
        call asm_sprintf_00452ae8
    L_0041a701:
        mov eax,edi
    L_0041a703:
        add esp,0Ch
    L_0041a706:
        lea edx,[eax+1]
    L_0041a709:
        lea esp,[esp+force_disp32_zero]
    L_0041a710:
        mov cl,byte ptr [eax]
    L_0041a712:
        inc eax
    L_0041a713:
        test cl,cl
    L_0041a715:
        jne short L_0041a710
    L_0041a717:
        sub eax,edx
    L_0041a719:
        mov esi,eax
    L_0041a71b:
        mov eax,dword ptr [data_00474c38]
    L_0041a720:
        cmp eax,0FFFFFFFFh
    L_0041a723:
        je short L_0041a759
    L_0041a725:
        push 0
    L_0041a727:
        lea ecx,[esp+3Ch]
    L_0041a72b:
        push ecx
    L_0041a72c:
        push esi
    L_0041a72d:
        push edi
    L_0041a72e:
        push eax
    L_0041a72f:
        call dword ptr [data_004660d4]
    L_0041a735:
        cmp esi,dword ptr [esp+38h]
    L_0041a739:
        je short L_0041a759
    L_0041a73b:
        mov edx,dword ptr [data_00474c38]
    L_0041a741:
        push edx
    L_0041a742:
        call dword ptr [data_004660cc]
    L_0041a748:
        push 4922A4h
    L_0041a74d:
        call dword ptr [data_004660b4]
    L_0041a753:
        dec byte ptr [data_0049231e]
    L_0041a759:
        mov ecx,dword ptr [ebx+64h]
    L_0041a75c:
        xor eax,eax
    L_0041a75e:
        mov edi,edi
    L_0041a760:
        cmp dword ptr [eax*8+474498h],ecx
    L_0041a767:
        je asm_target_0041aabb
    L_0041a76d:
        inc eax
    L_0041a76e:
        cmp eax,3
    L_0041a771:
        jl short L_0041a760
    L_0041a773:
        xor eax,eax
    L_0041a775:
        push eax
    L_0041a776:
        push 46D37Ch
    L_0041a77b:
        push edi
    L_0041a77c:
        call asm_sprintf_00452ae8
    L_0041a781:
        mov eax,edi
    L_0041a783:
        add esp,0Ch
    L_0041a786:
        lea edx,[eax+1]
    L_0041a789:
        lea esp,[esp+force_disp32_zero]
    L_0041a790:
        mov cl,byte ptr [eax]
    L_0041a792:
        inc eax
    L_0041a793:
        test cl,cl
    L_0041a795:
        jne short L_0041a790
    L_0041a797:
        sub eax,edx
    L_0041a799:
        mov esi,eax
    L_0041a79b:
        mov eax,dword ptr [data_00474c38]
    L_0041a7a0:
        cmp eax,0FFFFFFFFh
    L_0041a7a3:
        je short L_0041a7d9
    L_0041a7a5:
        push 0
    L_0041a7a7:
        lea ecx,[esp+40h]
    L_0041a7ab:
        push ecx
    L_0041a7ac:
        push esi
    L_0041a7ad:
        push edi
    L_0041a7ae:
        push eax
    L_0041a7af:
        call dword ptr [data_004660d4]
    L_0041a7b5:
        cmp esi,dword ptr [esp+3Ch]
    L_0041a7b9:
        je short L_0041a7d9
    L_0041a7bb:
        mov edx,dword ptr [data_00474c38]
    L_0041a7c1:
        push edx
    L_0041a7c2:
        call dword ptr [data_004660cc]
    L_0041a7c8:
        push 4922A4h
    L_0041a7cd:
        call dword ptr [data_004660b4]
    L_0041a7d3:
        dec byte ptr [data_0049231e]
    L_0041a7d9:
        mov eax,dword ptr [ebx+6Ch]
    L_0041a7dc:
        push eax
    L_0041a7dd:
        push 46D36Ch
    L_0041a7e2:
        push edi
    L_0041a7e3:
        call asm_sprintf_00452ae8
    L_0041a7e8:
        mov eax,edi
    L_0041a7ea:
        add esp,0Ch
    L_0041a7ed:
        lea edx,[eax+1]
    L_0041a7f0:
        mov cl,byte ptr [eax]
    L_0041a7f2:
        inc eax
    L_0041a7f3:
        test cl,cl
    L_0041a7f5:
        jne short L_0041a7f0
    L_0041a7f7:
        sub eax,edx
    L_0041a7f9:
        mov esi,eax
    L_0041a7fb:
        mov eax,dword ptr [data_00474c38]
    L_0041a800:
        cmp eax,0FFFFFFFFh
    L_0041a803:
        je short L_0041a839
    L_0041a805:
        push 0
    L_0041a807:
        lea ecx,[esp+44h]
    L_0041a80b:
        push ecx
    L_0041a80c:
        push esi
    L_0041a80d:
        push edi
    L_0041a80e:
        push eax
    L_0041a80f:
        call dword ptr [data_004660d4]
    L_0041a815:
        cmp esi,dword ptr [esp+40h]
    L_0041a819:
        je short L_0041a839
    L_0041a81b:
        mov edx,dword ptr [data_00474c38]
    L_0041a821:
        push edx
    L_0041a822:
        call dword ptr [data_004660cc]
    L_0041a828:
        push 4922A4h
    L_0041a82d:
        call dword ptr [data_004660b4]
    L_0041a833:
        dec byte ptr [data_0049231e]
    L_0041a839:
        movzx eax,byte ptr [ebx+87h]
    L_0041a840:
        push eax
    L_0041a841:
        push 46D35Ch
    L_0041a846:
        push edi
    L_0041a847:
        call asm_sprintf_00452ae8
    L_0041a84c:
        mov eax,edi
    L_0041a84e:
        add esp,0Ch
    L_0041a851:
        lea edx,[eax+1]
    L_0041a854:
        mov cl,byte ptr [eax]
    L_0041a856:
        inc eax
    L_0041a857:
        test cl,cl
    L_0041a859:
        jne short L_0041a854
    L_0041a85b:
        sub eax,edx
    L_0041a85d:
        mov esi,eax
    L_0041a85f:
        mov eax,dword ptr [data_00474c38]
    L_0041a864:
        cmp eax,0FFFFFFFFh
    L_0041a867:
        je short L_0041a89d
    L_0041a869:
        push 0
    L_0041a86b:
        lea ecx,[esp+48h]
    L_0041a86f:
        push ecx
    L_0041a870:
        push esi
    L_0041a871:
        push edi
    L_0041a872:
        push eax
    L_0041a873:
        call dword ptr [data_004660d4]
    L_0041a879:
        cmp esi,dword ptr [esp+44h]
    L_0041a87d:
        je short L_0041a89d
    L_0041a87f:
        mov edx,dword ptr [data_00474c38]
    L_0041a885:
        push edx
    L_0041a886:
        call dword ptr [data_004660cc]
    L_0041a88c:
        push 4922A4h
    L_0041a891:
        call dword ptr [data_004660b4]
    L_0041a897:
        dec byte ptr [data_0049231e]
    L_0041a89d:
        movzx eax,byte ptr [ebx+84h]
    L_0041a8a4:
        movzx ecx,byte ptr [ebx+85h]
    L_0041a8ab:
        movzx edx,byte ptr [ebx+86h]
    L_0041a8b2:
        push eax
    L_0041a8b3:
        push ecx
    L_0041a8b4:
        push edx
    L_0041a8b5:
        push 46D344h
    L_0041a8ba:
        push edi
    L_0041a8bb:
        call asm_sprintf_00452ae8
    L_0041a8c0:
        mov eax,edi
    L_0041a8c2:
        add esp,14h
    L_0041a8c5:
        lea edx,[eax+1]
    L_0041a8c8:
        mov cl,byte ptr [eax]
    L_0041a8ca:
        inc eax
    L_0041a8cb:
        test cl,cl
    L_0041a8cd:
        jne short L_0041a8c8
    L_0041a8cf:
        sub eax,edx
    L_0041a8d1:
        mov esi,eax
    L_0041a8d3:
        mov eax,dword ptr [data_00474c38]
    L_0041a8d8:
        cmp eax,0FFFFFFFFh
    L_0041a8db:
        je short L_0041a911
    L_0041a8dd:
        push 0
    L_0041a8df:
        lea ecx,[esp+4Ch]
    L_0041a8e3:
        push ecx
    L_0041a8e4:
        push esi
    L_0041a8e5:
        push edi
    L_0041a8e6:
        push eax
    L_0041a8e7:
        call dword ptr [data_004660d4]
    L_0041a8ed:
        cmp esi,dword ptr [esp+48h]
    L_0041a8f1:
        je short L_0041a911
    L_0041a8f3:
        mov edx,dword ptr [data_00474c38]
    L_0041a8f9:
        push edx
    L_0041a8fa:
        call dword ptr [data_004660cc]
    L_0041a900:
        push 4922A4h
    L_0041a905:
        call dword ptr [data_004660b4]
    L_0041a90b:
        dec byte ptr [data_0049231e]
    L_0041a911:
        fld dword ptr [ebx+7Ch]
    L_0041a914:
        sub esp,8
    L_0041a917:
        fstp qword ptr [esp]
    L_0041a91a:
        push 46D334h
    L_0041a91f:
        push edi
    L_0041a920:
        call asm_sprintf_00452ae8
    L_0041a925:
        mov eax,edi
    L_0041a927:
        add esp,10h
    L_0041a92a:
        lea edx,[eax+1]
    L_0041a92d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041a930:
        mov cl,byte ptr [eax]
    L_0041a932:
        inc eax
    L_0041a933:
        test cl,cl
    L_0041a935:
        jne short L_0041a930
    L_0041a937:
        sub eax,edx
    L_0041a939:
        mov esi,eax
    L_0041a93b:
        mov eax,dword ptr [data_00474c38]
    L_0041a940:
        cmp eax,0FFFFFFFFh
    L_0041a943:
        je short L_0041a979
    L_0041a945:
        push 0
    L_0041a947:
        lea ecx,[esp+50h]
    L_0041a94b:
        push ecx
    L_0041a94c:
        push esi
    L_0041a94d:
        push edi
    L_0041a94e:
        push eax
    L_0041a94f:
        call dword ptr [data_004660d4]
    L_0041a955:
        cmp esi,dword ptr [esp+4Ch]
    L_0041a959:
        je short L_0041a979
    L_0041a95b:
        mov edx,dword ptr [data_00474c38]
    L_0041a961:
        push edx
    L_0041a962:
        call dword ptr [data_004660cc]
    L_0041a968:
        push 4922A4h
    L_0041a96d:
        call dword ptr [data_004660b4]
    L_0041a973:
        dec byte ptr [data_0049231e]
    L_0041a979:
        mov eax,dword ptr [esp+0Ch]
    L_0041a97d:
        push eax
    L_0041a97e:
        push 46D32Ch
    L_0041a983:
        push edi
    L_0041a984:
        call asm_sprintf_00452ae8
    L_0041a989:
        mov eax,edi
    L_0041a98b:
        add esp,0Ch
    L_0041a98e:
        lea edx,[eax+1]
    L_0041a991:
        mov cl,byte ptr [eax]
    L_0041a993:
        inc eax
    L_0041a994:
        test cl,cl
    L_0041a996:
        jne short L_0041a991
    L_0041a998:
        sub eax,edx
    L_0041a99a:
        mov esi,eax
    L_0041a99c:
        mov eax,dword ptr [data_00474c38]
    L_0041a9a1:
        cmp eax,0FFFFFFFFh
    L_0041a9a4:
        je short L_0041a9da
    L_0041a9a6:
        push 0
    L_0041a9a8:
        lea ecx,[esp+54h]
    L_0041a9ac:
        push ecx
    L_0041a9ad:
        push esi
    L_0041a9ae:
        push edi
    L_0041a9af:
        push eax
    L_0041a9b0:
        call dword ptr [data_004660d4]
    L_0041a9b6:
        cmp esi,dword ptr [esp+50h]
    L_0041a9ba:
        je short L_0041a9da
    L_0041a9bc:
        mov edx,dword ptr [data_00474c38]
    L_0041a9c2:
        push edx
    L_0041a9c3:
        call dword ptr [data_004660cc]
    L_0041a9c9:
        push 4922A4h
    L_0041a9ce:
        call dword ptr [data_004660b4]
    L_0041a9d4:
        dec byte ptr [data_0049231e]
    L_0041a9da:
        mov eax,dword ptr [esp+10h]
    L_0041a9de:
        inc eax
    L_0041a9df:
        cmp eax,0FFh
    L_0041a9e4:
        mov dword ptr [esp+10h],eax
    L_0041a9e8:
        jge short L_0041a9f8
    L_0041a9ea:
        mov eax,dword ptr [esp+18h]
    L_0041a9ee:
        mov ecx,eax
    L_0041a9f0:
        test ecx,ecx
    L_0041a9f2:
        jne asm_target_0041a400
    L_0041a9f8:
        mov eax,dword ptr [esp+10h]
    L_0041a9fc:
        test eax,eax
    L_0041a9fe:
        je short L_0041aa5c
    L_0041aa00:
        push 46D320h
    L_0041aa05:
        push edi
    L_0041aa06:
        call asm_sprintf_00452ae8
    L_0041aa0b:
        mov eax,edi
    L_0041aa0d:
        add esp,8
    L_0041aa10:
        lea edx,[eax+1]
    L_0041aa13:
        mov cl,byte ptr [eax]
    L_0041aa15:
        inc eax
    L_0041aa16:
        test cl,cl
    L_0041aa18:
        jne short L_0041aa13
    L_0041aa1a:
        sub eax,edx
    L_0041aa1c:
        mov esi,eax
    L_0041aa1e:
        mov eax,dword ptr [data_00474c38]
    L_0041aa23:
        cmp eax,0FFFFFFFFh
    L_0041aa26:
        je short L_0041aa5c
    L_0041aa28:
        push 0
    L_0041aa2a:
        lea ecx,[esp+58h]
    L_0041aa2e:
        push ecx
    L_0041aa2f:
        push esi
    L_0041aa30:
        push edi
    L_0041aa31:
        push eax
    L_0041aa32:
        call dword ptr [data_004660d4]
    L_0041aa38:
        cmp esi,dword ptr [esp+54h]
    L_0041aa3c:
        je short L_0041aa5c
    L_0041aa3e:
        mov edx,dword ptr [data_00474c38]
    L_0041aa44:
        push edx
    L_0041aa45:
        call dword ptr [data_004660cc]
    L_0041aa4b:
        push 4922A4h
    L_0041aa50:
        call dword ptr [data_004660b4]
    L_0041aa56:
        dec byte ptr [data_0049231e]
    L_0041aa5c:
        mov eax,dword ptr [esp+0Ch]
    L_0041aa60:
        mov edx,dword ptr [esp+14h]
    L_0041aa64:
        inc eax
    L_0041aa65:
        add edx,0Ch
    L_0041aa68:
        cmp eax,8
    L_0041aa6b:
        mov dword ptr [esp+0Ch],eax
    L_0041aa6f:
        mov dword ptr [esp+14h],edx
    L_0041aa73:
        jl asm_target_0041a3e4
    L_0041aa79:
        mov eax,dword ptr [data_00474c38]
    L_0041aa7e:
        cmp eax,0FFFFFFFFh
    L_0041aa81:
        je short L_0041aa9b
    L_0041aa83:
        push eax
    L_0041aa84:
        call dword ptr [data_004660cc]
    L_0041aa8a:
        push 4922A4h
    L_0041aa8f:
        call dword ptr [data_004660b4]
    L_0041aa95:
        dec byte ptr [data_0049231e]
    L_0041aa9b:
        push edi
    L_0041aa9c:
        call asm_free_00452422
    L_0041aaa1:
        add esp,4
    L_0041aaa4:
        pop edi
    L_0041aaa5:
        pop esi
    L_0041aaa6:
        xor eax,eax
    L_0041aaa8:
        pop ebx
    L_0041aaa9:
        mov esp,ebp
    L_0041aaab:
        pop ebp
    L_0041aaac:
        ret 8
    L_0041aaaf:
        mov eax,dword ptr [eax*8+4744B0h]
    L_0041aab6:
        jmp asm_target_0041a6f5
    L_0041aabb:
        mov eax,dword ptr [eax*8+474494h]
    L_0041aac2:
        jmp asm_target_0041a775
    }
}

// 0x0042B1E0..0x0042B413: FUN_0042b1e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b1e0_0042b1e0() {
    __asm {
    L_0042b1e0:
        mov eax,dword ptr [ebx]
    L_0042b1e2:
        sub esp,0Ch
    L_0042b1e5:
        test eax,eax
    L_0042b1e7:
        jne short L_0042b1f0
    L_0042b1e9:
        or eax,0FFFFFFFFh
    L_0042b1ec:
        add esp,0Ch
    L_0042b1ef:
        ret
    L_0042b1f0:
        push ebp
    L_0042b1f1:
        push 200000h
    L_0042b1f6:
        call asm_malloc_00452706
    L_0042b1fb:
        mov ecx,dword ptr [ebx]
    L_0042b1fd:
        mov edx,dword ptr [ecx]
    L_0042b1ff:
        mov dword ptr [esp+8],eax
    L_0042b203:
        mov dword ptr [eax],edx
    L_0042b205:
        mov edx,dword ptr [ecx+4]
    L_0042b208:
        mov dword ptr [eax+4],edx
    L_0042b20b:
        mov edx,dword ptr [ecx+8]
    L_0042b20e:
        mov dword ptr [eax+8],edx
    L_0042b211:
        mov edx,dword ptr [ecx+0Ch]
    L_0042b214:
        mov dword ptr [eax+0Ch],edx
    L_0042b217:
        mov edx,dword ptr [ecx+10h]
    L_0042b21a:
        mov dword ptr [eax+10h],edx
    L_0042b21d:
        mov ecx,dword ptr [ecx+14h]
    L_0042b220:
        add esp,4
    L_0042b223:
        mov dword ptr [eax+14h],ecx
    L_0042b226:
        mov ebp,18h
    L_0042b22b:
        xor eax,eax
    L_0042b22d:
        push esi
    L_0042b22e:
        mov dword ptr [esp+0Ch],ebp
    L_0042b232:
        mov dword ptr [esp+10h],eax
    L_0042b236:
        lea edx,[ebx+14h]
    L_0042b239:
        push edi
    L_0042b23a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042b240:
        cmp word ptr [edx-0Ch],5243h
    L_0042b246:
        jne short L_0042b2a3
    L_0042b248:
        mov dword ptr [edx],eax
    L_0042b24a:
        xor ecx,ecx
    L_0042b24c:
        mov eax,edx
    L_0042b24e:
        mov edi,0B3Eh
    L_0042b253:
        movzx ebp,byte ptr [eax-3]
    L_0042b257:
        movzx esi,byte ptr [eax-4]
    L_0042b25b:
        add esi,ebp
    L_0042b25d:
        movzx ebp,byte ptr [eax-2]
    L_0042b261:
        add esi,ebp
    L_0042b263:
        movzx ebp,byte ptr [eax-1]
    L_0042b267:
        add esi,ebp
    L_0042b269:
        movzx ebp,byte ptr [eax+1]
    L_0042b26d:
        add esi,ebp
    L_0042b26f:
        movzx ebp,byte ptr [eax]
    L_0042b272:
        add ebp,ecx
    L_0042b274:
        add eax,6
    L_0042b277:
        dec edi
    L_0042b278:
        lea ecx,[esi+ebp]
    L_0042b27b:
        jne short L_0042b253
    L_0042b27d:
        mov ebp,dword ptr [esp+10h]
    L_0042b281:
        mov eax,dword ptr [esp+0Ch]
    L_0042b285:
        lea edi,[eax+ebp]
    L_0042b288:
        mov eax,dword ptr [esp+14h]
    L_0042b28c:
        mov dword ptr [edx-8],ecx
    L_0042b28f:
        mov ecx,10DFh
    L_0042b294:
        lea esi,[edx-0Ch]
    L_0042b297:
        add ebp,437Ch
    L_0042b29d:
        rep movsd
    L_0042b29f:
        mov dword ptr [esp+10h],ebp
    L_0042b2a3:
        inc eax
    L_0042b2a4:
        add edx,437Ch
    L_0042b2aa:
        cmp eax,7
    L_0042b2ad:
        mov dword ptr [esp+14h],eax
    L_0042b2b1:
        jb short L_0042b240
    L_0042b2b3:
        xor ecx,ecx
    L_0042b2b5:
        lea eax,[ebx+1D876h]
    L_0042b2bb:
        mov edx,110h
    L_0042b2c0:
        movzx edi,byte ptr [eax-1]
    L_0042b2c4:
        movzx esi,byte ptr [eax-2]
    L_0042b2c8:
        add esi,edi
    L_0042b2ca:
        movzx edi,byte ptr [eax+1]
    L_0042b2ce:
        add esi,edi
    L_0042b2d0:
        movzx edi,byte ptr [eax]
    L_0042b2d3:
        add edi,ecx
    L_0042b2d5:
        add eax,4
    L_0042b2d8:
        dec edx
    L_0042b2d9:
        lea ecx,[edi+esi]
    L_0042b2dc:
        jne short L_0042b2c0
    L_0042b2de:
        mov dword ptr [ebx+1D870h],ecx
    L_0042b2e4:
        mov ecx,dword ptr [esp+0Ch]
    L_0042b2e8:
        lea edi,[ecx+ebp]
    L_0042b2eb:
        lea esi,[ebx+1D86Ch]
    L_0042b2f1:
        mov ecx,112h
    L_0042b2f6:
        rep movsd
    L_0042b2f8:
        mov edx,dword ptr [ebx]
    L_0042b2fa:
        add ebp,430h
    L_0042b300:
        mov dword ptr [edx+14h],ebp
    L_0042b303:
        mov eax,dword ptr [ebx]
    L_0042b305:
        mov edx,dword ptr [eax+14h]
    L_0042b308:
        lea ecx,[eax+10h]
    L_0042b30b:
        mov eax,dword ptr [esp+0Ch]
    L_0042b30f:
        push ecx
    L_0042b310:
        push edx
    L_0042b311:
        add eax,18h
    L_0042b314:
        push eax
    L_0042b315:
        call asm_FUN_004359b0_004359b0
    L_0042b31a:
        mov edi,eax
    L_0042b31c:
        mov eax,dword ptr [ebx]
    L_0042b31e:
        mov ecx,dword ptr [eax+10h]
    L_0042b321:
        add ecx,18h
    L_0042b324:
        mov dword ptr [eax+4],ecx
    L_0042b327:
        mov edx,dword ptr [ebx]
    L_0042b329:
        mov eax,dword ptr [edx+10h]
    L_0042b32c:
        push eax
    L_0042b32d:
        push 10h
    L_0042b32f:
        push 35h
    L_0042b331:
        push eax
    L_0042b332:
        push edi
    L_0042b333:
        mov al,0ACh
    L_0042b335:
        call asm_EncryptDatBuffer_0044b220
    L_0042b33a:
        push 46E848h
    L_0042b33f:
        call asm_File_OpenSharedWrite_0044b620
    L_0042b344:
        test eax,eax
    L_0042b346:
        je short L_0042b352
    L_0042b348:
        pop edi
    L_0042b349:
        pop esi
    L_0042b34a:
        or eax,0FFFFFFFFh
    L_0042b34d:
        pop ebp
    L_0042b34e:
        add esp,0Ch
    L_0042b351:
        ret
    L_0042b352:
        mov eax,dword ptr [data_00474c38]
    L_0042b357:
        cmp eax,0FFFFFFFFh
    L_0042b35a:
        mov ebp,dword ptr [data_004660cc]
    L_0042b360:
        je short L_0042b39a
    L_0042b362:
        mov edx,dword ptr [ebx]
    L_0042b364:
        push 0
    L_0042b366:
        lea ecx,[esp+18h]
    L_0042b36a:
        push ecx
    L_0042b36b:
        push 18h
    L_0042b36d:
        push edx
    L_0042b36e:
        push eax
    L_0042b36f:
        call dword ptr [data_004660d4]
    L_0042b375:
        cmp dword ptr [esp+14h],18h
    L_0042b37a:
        mov eax,dword ptr [data_00474c38]
    L_0042b37f:
        je short L_0042b39a
    L_0042b381:
        push eax
    L_0042b382:
        call ebp
    L_0042b384:
        push 4922A4h
    L_0042b389:
        call dword ptr [data_004660b4]
    L_0042b38f:
        dec byte ptr [data_0049231e]
    L_0042b395:
        mov eax,dword ptr [data_00474c38]
    L_0042b39a:
        cmp eax,0FFFFFFFFh
    L_0042b39d:
        mov ecx,dword ptr [ebx]
    L_0042b39f:
        mov esi,dword ptr [ecx+10h]
    L_0042b3a2:
        je short L_0042b3f1
    L_0042b3a4:
        push 0
    L_0042b3a6:
        lea edx,[esp+18h]
    L_0042b3aa:
        push edx
    L_0042b3ab:
        push esi
    L_0042b3ac:
        push edi
    L_0042b3ad:
        push eax
    L_0042b3ae:
        call dword ptr [data_004660d4]
    L_0042b3b4:
        cmp esi,dword ptr [esp+14h]
    L_0042b3b8:
        je short L_0042b3d3
    L_0042b3ba:
        mov eax,dword ptr [data_00474c38]
    L_0042b3bf:
        push eax
    L_0042b3c0:
        call ebp
    L_0042b3c2:
        push 4922A4h
    L_0042b3c7:
        call dword ptr [data_004660b4]
    L_0042b3cd:
        dec byte ptr [data_0049231e]
    L_0042b3d3:
        mov eax,dword ptr [data_00474c38]
    L_0042b3d8:
        cmp eax,0FFFFFFFFh
    L_0042b3db:
        je short L_0042b3f1
    L_0042b3dd:
        push eax
    L_0042b3de:
        call ebp
    L_0042b3e0:
        push 4922A4h
    L_0042b3e5:
        call dword ptr [data_004660b4]
    L_0042b3eb:
        dec byte ptr [data_0049231e]
    L_0042b3f1:
        test edi,edi
    L_0042b3f3:
        je short L_0042b3fe
    L_0042b3f5:
        push edi
    L_0042b3f6:
        call asm_free_00452422
    L_0042b3fb:
        add esp,4
    L_0042b3fe:
        mov ecx,dword ptr [esp+0Ch]
    L_0042b402:
        push ecx
    L_0042b403:
        call asm_free_00452422
    L_0042b408:
        add esp,4
    L_0042b40b:
        pop edi
    L_0042b40c:
        pop esi
    L_0042b40d:
        xor eax,eax
    L_0042b40f:
        pop ebp
    L_0042b410:
        add esp,0Ch
    L_0042b413:
        ret
    }
}

// 0x004359B0..0x00435B2C: FUN_004359b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004359b0_004359b0() {
    __asm {
    L_004359b0:
        sub esp,2Ch
    L_004359b3:
        push ebx
    L_004359b4:
        push ebp
    L_004359b5:
        mov ebp,dword ptr [esp+3Ch]
    L_004359b9:
        lea eax,[ebp+ebp]
    L_004359bd:
        push eax
    L_004359be:
        mov bl,80h
    L_004359c0:
        mov dword ptr [esp+10h],0
    L_004359c8:
        call asm_malloc_00452706
    L_004359cd:
        add esp,4
    L_004359d0:
        test eax,eax
    L_004359d2:
        mov dword ptr [esp+30h],eax
    L_004359d6:
        jne short L_004359e0
    L_004359d8:
        pop ebp
    L_004359d9:
        pop ebx
    L_004359da:
        add esp,2Ch
    L_004359dd:
        ret 0Ch
    L_004359e0:
        mov ecx,dword ptr [esp+38h]
    L_004359e4:
        mov edx,dword ptr [esp+40h]
    L_004359e8:
        push esi
    L_004359e9:
        mov esi,eax
    L_004359eb:
        push edi
    L_004359ec:
        mov dword ptr [esp+1Ch],ecx
    L_004359f0:
        xor eax,eax
    L_004359f2:
        mov ecx,800h
    L_004359f7:
        mov edi,48F868h
    L_004359fc:
        mov dword ptr [edx],0
    L_00435a02:
        rep stosd
    L_00435a04:
        mov dword ptr [esp+18h],esi
    L_00435a08:
        mov eax,47785Ch
    L_00435a0d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00435a10:
        xor ecx,ecx
    L_00435a12:
        mov dword ptr [eax-4],ecx
    L_00435a15:
        mov dword ptr [eax],ecx
    L_00435a17:
        mov dword ptr [eax+4],ecx
    L_00435a1a:
        add eax,0Ch
    L_00435a1d:
        cmp eax,48F868h
    L_00435a22:
        jl short L_00435a10
    L_00435a24:
        xor eax,eax
    L_00435a26:
        mov dword ptr [esp+24h],1
    L_00435a2e:
        xor edx,edx
    L_00435a30:
        jmp short L_00435a34
    L_00435a32:
        xor ecx,ecx
    L_00435a34:
        cmp edx,ebp
    L_00435a36:
        jge short L_00435a58
    L_00435a38:
        mov edi,dword ptr [esp+1Ch]
    L_00435a3c:
        movzx ecx,byte ptr [edi]
    L_00435a3f:
        inc edi
    L_00435a40:
        inc edx
    L_00435a41:
        cmp ecx,0FFFFFFFFh
    L_00435a44:
        mov dword ptr [esp+1Ch],edi
    L_00435a48:
        je short L_00435a56
    L_00435a4a:
        mov byte ptr [eax+48F869h],cl
    L_00435a50:
        inc eax
    L_00435a51:
        cmp eax,12h
    L_00435a54:
        jl short L_00435a32
    L_00435a56:
        xor ecx,ecx
    L_00435a58:
        xor ebp,ebp
    L_00435a5a:
        cmp eax,ecx
    L_00435a5c:
        mov edx,eax
    L_00435a5e:
        mov dword ptr [esp+28h],edx
    L_00435a62:
        mov dword ptr [data_0048f860],1
    L_00435a6c:
        mov dword ptr [data_00477864],2000h
    L_00435a76:
        mov dword ptr [data_0047786c],ecx
    L_00435a7c:
        mov dword ptr [data_00477868],ecx
    L_00435a82:
        mov dword ptr [esp+20h],ebp
    L_00435a86:
        mov dword ptr [esp+30h],ecx
    L_00435a8a:
        jle asm_target_00435d6e
    L_00435a90:
        cmp ebp,edx
    L_00435a92:
        jle short L_00435a9a
    L_00435a94:
        mov dword ptr [esp+20h],edx
    L_00435a98:
        mov ebp,edx
    L_00435a9a:
        cmp ebp,2
    L_00435a9d:
        jg short L_00435b0f
    L_00435a9f:
        mov ebp,dword ptr [esp+14h]
    L_00435aa3:
        movzx eax,bl
    L_00435aa6:
        or ebp,eax
    L_00435aa8:
        shr bl,1
    L_00435aaa:
        test bl,bl
    L_00435aac:
        mov edi,1
    L_00435ab1:
        mov dword ptr [esp+14h],ebp
    L_00435ab5:
        jne short L_00435ac8
    L_00435ab7:
        mov dl,byte ptr [esp+14h]
    L_00435abb:
        mov byte ptr [esi],dl
    L_00435abd:
        inc esi
    L_00435abe:
        mov dword ptr [esp+18h],esi
    L_00435ac2:
        mov dword ptr [esp+14h],ecx
    L_00435ac6:
        mov bl,80h
    L_00435ac8:
        mov eax,80h
    L_00435acd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00435ad0:
        mov edx,dword ptr [esp+24h]
    L_00435ad4:
        test byte ptr [edx+48F868h],al
    L_00435ada:
        je short L_00435ae9
    L_00435adc:
        mov ebp,dword ptr [esp+14h]
    L_00435ae0:
        movzx edx,bl
    L_00435ae3:
        or ebp,edx
    L_00435ae5:
        mov dword ptr [esp+14h],ebp
    L_00435ae9:
        shr bl,1
    L_00435aeb:
        test bl,bl
    L_00435aed:
        jne short L_00435afc
    L_00435aef:
        mov dl,byte ptr [esp+14h]
    L_00435af3:
        mov byte ptr [esi],dl
    L_00435af5:
        inc esi
    L_00435af6:
        mov dword ptr [esp+14h],ecx
    L_00435afa:
        mov bl,80h
    L_00435afc:
        shr eax,1
    L_00435afe:
        cmp eax,ecx
    L_00435b00:
        jne short L_00435ad0
    L_00435b02:
        mov dword ptr [esp+18h],esi
    L_00435b06:
        mov byte ptr [esp+13h],bl
    L_00435b0a:
        jmp asm_target_00435bb0
    L_00435b0f:
        shr bl,1
    L_00435b11:
        test bl,bl
    L_00435b13:
        jne short L_00435b26
    L_00435b15:
        mov al,byte ptr [esp+14h]
    L_00435b19:
        mov byte ptr [esi],al
    L_00435b1b:
        inc esi
    L_00435b1c:
        mov dword ptr [esp+18h],esi
    L_00435b20:
        mov dword ptr [esp+14h],ecx
    L_00435b24:
        mov bl,80h
    L_00435b26:
        mov eax,1000h
    L_00435b2b:
        TH10_REL8(0xeb, 0x00435b2b, VA_asm_FUN_004359b0_part_00435b30)
    }
}

// 0x00435B30..0x00435DB4: FUN_004359b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004359b0_part_00435b30() {
    __asm {
    L_00435b30:
        mov edx,dword ptr [esp+30h]
    L_00435b34:
        test eax,edx
    L_00435b36:
        je short L_00435b45
    L_00435b38:
        mov edi,dword ptr [esp+14h]
    L_00435b3c:
        movzx edx,bl
    L_00435b3f:
        or edi,edx
    L_00435b41:
        mov dword ptr [esp+14h],edi
    L_00435b45:
        shr bl,1
    L_00435b47:
        test bl,bl
    L_00435b49:
        jne short L_00435b58
    L_00435b4b:
        mov dl,byte ptr [esp+14h]
    L_00435b4f:
        mov byte ptr [esi],dl
    L_00435b51:
        inc esi
    L_00435b52:
        mov dword ptr [esp+14h],ecx
    L_00435b56:
        mov bl,80h
    L_00435b58:
        shr eax,1
    L_00435b5a:
        cmp eax,ecx
    L_00435b5c:
        jne short L_00435b30
    L_00435b5e:
        mov dword ptr [esp+18h],esi
    L_00435b62:
        mov eax,8
    L_00435b67:
        lea edi,[ebp-3]
    L_00435b6a:
        lea ebx,[ebx+force_disp32_zero]
    L_00435b70:
        test edi,eax
    L_00435b72:
        je short L_00435b85
    L_00435b74:
        mov ebp,dword ptr [esp+14h]
    L_00435b78:
        movzx edx,bl
    L_00435b7b:
        or ebp,edx
    L_00435b7d:
        mov dword ptr [esp+14h],ebp
    L_00435b81:
        mov ebp,dword ptr [esp+20h]
    L_00435b85:
        shr bl,1
    L_00435b87:
        test bl,bl
    L_00435b89:
        jne short L_00435b98
    L_00435b8b:
        mov dl,byte ptr [esp+14h]
    L_00435b8f:
        mov byte ptr [esi],dl
    L_00435b91:
        inc esi
    L_00435b92:
        mov dword ptr [esp+14h],ecx
    L_00435b96:
        mov bl,80h
    L_00435b98:
        shr eax,1
    L_00435b9a:
        cmp eax,ecx
    L_00435b9c:
        jne short L_00435b70
    L_00435b9e:
        cmp ebp,ecx
    L_00435ba0:
        mov dword ptr [esp+18h],esi
    L_00435ba4:
        mov byte ptr [esp+13h],bl
    L_00435ba8:
        mov edi,ebp
    L_00435baa:
        jle asm_target_00435d62
    L_00435bb0:
        mov eax,dword ptr [esp+1Ch]
    L_00435bb4:
        sub eax,dword ptr [esp+40h]
    L_00435bb8:
        mov dword ptr [esp+2Ch],eax
    L_00435bbc:
        mov dword ptr [esp+34h],edi
    L_00435bc0:
        mov ebp,dword ptr [esp+24h]
    L_00435bc4:
        add ebp,12h
    L_00435bc7:
        and ebp,1FFFh
    L_00435bcd:
        lea eax,[ebp+ebp*2]
    L_00435bd1:
        shl eax,2
    L_00435bd4:
        mov ecx,dword ptr [eax+477858h]
    L_00435bda:
        test ecx,ecx
    L_00435bdc:
        lea edi,[eax+477858h]
    L_00435be2:
        je asm_target_00435cfb
    L_00435be8:
        mov edx,dword ptr [eax+477860h]
    L_00435bee:
        test edx,edx
    L_00435bf0:
        mov eax,dword ptr [eax+47785Ch]
    L_00435bf6:
        jne short L_00435c28
    L_00435bf8:
        lea edx,[eax+eax*2]
    L_00435bfb:
        mov dword ptr [edx*4+477858h],ecx
    L_00435c02:
        mov ecx,dword ptr [edi]
    L_00435c04:
        lea ecx,[ecx+ecx*2]
    L_00435c07:
        shl ecx,2
    L_00435c0a:
        cmp dword ptr [ecx+477860h],ebp
    L_00435c10:
        jne short L_00435c1d
    L_00435c12:
        mov dword ptr [ecx+477860h],eax
    L_00435c18:
        jmp asm_target_00435cf5
    L_00435c1d:
        mov dword ptr [ecx+47785Ch],eax
    L_00435c23:
        jmp asm_target_00435cf5
    L_00435c28:
        test eax,eax
    L_00435c2a:
        jne short L_00435c5c
    L_00435c2c:
        lea eax,[edx+edx*2]
    L_00435c2f:
        mov dword ptr [eax*4+477858h],ecx
    L_00435c36:
        mov eax,dword ptr [edi]
    L_00435c38:
        lea eax,[eax+eax*2]
    L_00435c3b:
        shl eax,2
    L_00435c3e:
        cmp dword ptr [eax+477860h],ebp
    L_00435c44:
        jne short L_00435c51
    L_00435c46:
        mov dword ptr [eax+477860h],edx
    L_00435c4c:
        jmp asm_target_00435cf5
    L_00435c51:
        mov dword ptr [eax+47785Ch],edx
    L_00435c57:
        jmp asm_target_00435cf5
    L_00435c5c:
        mov esi,eax
    L_00435c5e:
        lea eax,[esi+esi*2]
    L_00435c61:
        mov ecx,dword ptr [eax*4+477860h]
    L_00435c68:
        test ecx,ecx
    L_00435c6a:
        lea eax,[eax*4+477860h]
    L_00435c71:
        je short L_00435c8a
    L_00435c73:
        mov esi,dword ptr [eax]
    L_00435c75:
        lea eax,[esi+esi*2]
    L_00435c78:
        mov ecx,dword ptr [eax*4+477860h]
    L_00435c7f:
        test ecx,ecx
    L_00435c81:
        lea eax,[eax*4+477860h]
    L_00435c88:
        jne short L_00435c73
    L_00435c8a:
        mov ecx,esi
    L_00435c8c:
        call asm_MemoryFile_RemoveNode_00436210
    L_00435c91:
        mov eax,dword ptr [edi]
    L_00435c93:
        lea eax,[eax+eax*2]
    L_00435c96:
        shl eax,2
    L_00435c99:
        cmp dword ptr [eax+47785Ch],ebp
    L_00435c9f:
        jne short L_00435ca9
    L_00435ca1:
        mov dword ptr [eax+47785Ch],esi
    L_00435ca7:
        jmp short L_00435caf
    L_00435ca9:
        mov dword ptr [eax+477860h],esi
    L_00435caf:
        lea eax,[esi+esi*2]
    L_00435cb2:
        shl eax,2
    L_00435cb5:
        lea ecx,[eax+477858h]
    L_00435cbb:
        mov edx,edi
    L_00435cbd:
        mov ebx,dword ptr [edx]
    L_00435cbf:
        mov dword ptr [ecx],ebx
    L_00435cc1:
        mov ebx,dword ptr [edx+4]
    L_00435cc4:
        mov dword ptr [ecx+4],ebx
    L_00435cc7:
        mov edx,dword ptr [edx+8]
    L_00435cca:
        mov bl,byte ptr [esp+13h]
    L_00435cce:
        mov dword ptr [ecx+8],edx
    L_00435cd1:
        mov ecx,dword ptr [eax+47785Ch]
    L_00435cd7:
        lea ecx,[ecx+ecx*2]
    L_00435cda:
        mov dword ptr [ecx*4+477858h],esi
    L_00435ce1:
        mov eax,dword ptr [eax+477860h]
    L_00435ce7:
        lea edx,[eax+eax*2]
    L_00435cea:
        mov dword ptr [edx*4+477858h],esi
    L_00435cf1:
        mov esi,dword ptr [esp+18h]
    L_00435cf5:
        mov dword ptr [edi],0
    L_00435cfb:
        mov eax,dword ptr [esp+2Ch]
    L_00435cff:
        cmp eax,dword ptr [esp+44h]
    L_00435d03:
        jge short L_00435d1f
    L_00435d05:
        mov ecx,dword ptr [esp+1Ch]
    L_00435d09:
        movzx eax,byte ptr [ecx]
    L_00435d0c:
        mov edx,dword ptr [esp+2Ch]
    L_00435d10:
        inc ecx
    L_00435d11:
        inc edx
    L_00435d12:
        cmp eax,0FFFFFFFFh
    L_00435d15:
        mov dword ptr [esp+1Ch],ecx
    L_00435d19:
        mov dword ptr [esp+2Ch],edx
    L_00435d1d:
        jne short L_00435d25
    L_00435d1f:
        dec dword ptr [esp+28h]
    L_00435d23:
        jmp short L_00435d2b
    L_00435d25:
        mov byte ptr [ebp+48F868h],al
    L_00435d2b:
        mov ecx,dword ptr [esp+24h]
    L_00435d2f:
        mov eax,dword ptr [esp+28h]
    L_00435d33:
        lea edx,[ecx+1]
    L_00435d36:
        and edx,1FFFh
    L_00435d3c:
        test eax,eax
    L_00435d3e:
        mov dword ptr [esp+24h],edx
    L_00435d42:
        je short L_00435d52
    L_00435d44:
        lea eax,[esp+30h]
    L_00435d48:
        push eax
    L_00435d49:
        call asm_FUN_00436000_00436000
    L_00435d4e:
        mov dword ptr [esp+20h],eax
    L_00435d52:
        dec dword ptr [esp+34h]
    L_00435d56:
        jne asm_target_00435bc0
    L_00435d5c:
        mov ebp,dword ptr [esp+20h]
    L_00435d60:
        xor ecx,ecx
    L_00435d62:
        mov edx,dword ptr [esp+28h]
    L_00435d66:
        cmp edx,ecx
    L_00435d68:
        jg asm_target_00435a90
    L_00435d6e:
        shr bl,1
    L_00435d70:
        test bl,bl
    L_00435d72:
        jne short L_00435d81
    L_00435d74:
        mov dl,byte ptr [esp+14h]
    L_00435d78:
        mov byte ptr [esi],dl
    L_00435d7a:
        inc esi
    L_00435d7b:
        mov dword ptr [esp+14h],ecx
    L_00435d7f:
        mov bl,80h
    L_00435d81:
        mov eax,1000h
    L_00435d86:
        shr bl,1
    L_00435d88:
        test bl,bl
    L_00435d8a:
        jne short L_00435d99
    L_00435d8c:
        mov dl,byte ptr [esp+14h]
    L_00435d90:
        mov byte ptr [esi],dl
    L_00435d92:
        inc esi
    L_00435d93:
        mov dword ptr [esp+14h],ecx
    L_00435d97:
        mov bl,80h
    L_00435d99:
        shr eax,1
    L_00435d9b:
        cmp eax,ecx
    L_00435d9d:
        jne short L_00435d86
    L_00435d9f:
        mov eax,dword ptr [esp+38h]
    L_00435da3:
        mov ecx,dword ptr [esp+48h]
    L_00435da7:
        sub esi,eax
    L_00435da9:
        pop edi
    L_00435daa:
        mov dword ptr [ecx],esi
    L_00435dac:
        pop esi
    L_00435dad:
        pop ebp
    L_00435dae:
        pop ebx
    L_00435daf:
        add esp,2Ch
    L_00435db2:
        ret 0Ch
    }
}

// 0x00436000..0x0043601C: FUN_00436000
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436000_00436000() {
    __asm {
    L_00436000:
        test edx,edx
    L_00436002:
        jne short L_00436009
    L_00436004:
        xor eax,eax
    L_00436006:
        ret 4
    L_00436009:
        push ebx
    L_0043600a:
        push esi
    L_0043600b:
        mov esi,dword ptr [data_0048f860]
    L_00436011:
        push ebp
    L_00436012:
        xor ebx,ebx
    L_00436014:
        push edi
    L_00436015:
        mov edi,esi
    L_00436017:
        xor eax,eax
    L_00436019:
        sub edi,edx
    L_0043601b:
        TH10_REL8(0xeb, 0x0043601b, VA_asm_FUN_00436000_part_00436020)
    }
}

// 0x00436020..0x00436203: FUN_00436000
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436000_part_00436020() {
    __asm {
    L_00436020:
        lea ecx,[eax+edx]
    L_00436023:
        lea ebp,[edi+ecx]
    L_00436026:
        and ebp,1FFFh
    L_0043602c:
        movzx ebp,byte ptr [ebp+48F868h]
    L_00436033:
        and ecx,1FFFh
    L_00436039:
        movzx ecx,byte ptr [ecx+48F868h]
    L_00436040:
        sub ecx,ebp
    L_00436042:
        jne asm_target_00436131
    L_00436048:
        lea ecx,[eax+esi+1]
    L_0043604c:
        and ecx,1FFFh
    L_00436052:
        movzx ebp,byte ptr [ecx+48F868h]
    L_00436059:
        lea ecx,[eax+edx+1]
    L_0043605d:
        and ecx,1FFFh
    L_00436063:
        movzx ecx,byte ptr [ecx+48F868h]
    L_0043606a:
        sub ecx,ebp
    L_0043606c:
        jne asm_target_0043611c
    L_00436072:
        lea ecx,[eax+esi+2]
    L_00436076:
        and ecx,1FFFh
    L_0043607c:
        movzx ebp,byte ptr [ecx+48F868h]
    L_00436083:
        lea ecx,[eax+edx+2]
    L_00436087:
        and ecx,1FFFh
    L_0043608d:
        movzx ecx,byte ptr [ecx+48F868h]
    L_00436094:
        sub ecx,ebp
    L_00436096:
        jne asm_target_0043611f
    L_0043609c:
        lea ecx,[eax+esi+3]
    L_004360a0:
        and ecx,1FFFh
    L_004360a6:
        movzx ebp,byte ptr [ecx+48F868h]
    L_004360ad:
        lea ecx,[eax+edx+3]
    L_004360b1:
        and ecx,1FFFh
    L_004360b7:
        movzx ecx,byte ptr [ecx+48F868h]
    L_004360be:
        sub ecx,ebp
    L_004360c0:
        jne short L_00436124
    L_004360c2:
        lea ecx,[eax+esi+4]
    L_004360c6:
        and ecx,1FFFh
    L_004360cc:
        movzx ebp,byte ptr [ecx+48F868h]
    L_004360d3:
        lea ecx,[eax+edx+4]
    L_004360d7:
        and ecx,1FFFh
    L_004360dd:
        movzx ecx,byte ptr [ecx+48F868h]
    L_004360e4:
        sub ecx,ebp
    L_004360e6:
        jne short L_00436129
    L_004360e8:
        lea ecx,[eax+esi+5]
    L_004360ec:
        and ecx,1FFFh
    L_004360f2:
        movzx ebp,byte ptr [ecx+48F868h]
    L_004360f9:
        lea ecx,[eax+edx+5]
    L_004360fd:
        and ecx,1FFFh
    L_00436103:
        movzx ecx,byte ptr [ecx+48F868h]
    L_0043610a:
        sub ecx,ebp
    L_0043610c:
        jne short L_0043612e
    L_0043610e:
        add eax,6
    L_00436111:
        cmp eax,12h
    L_00436114:
        jl asm_FUN_00436000_part_00436020
    L_0043611a:
        jmp short L_00436131
    L_0043611c:
        inc eax
    L_0043611d:
        jmp short L_00436131
    L_0043611f:
        add eax,2
    L_00436122:
        jmp short L_00436131
    L_00436124:
        add eax,3
    L_00436127:
        jmp short L_00436131
    L_00436129:
        add eax,4
    L_0043612c:
        jmp short L_00436131
    L_0043612e:
        add eax,5
    L_00436131:
        cmp eax,ebx
    L_00436133:
        jl short L_00436142
    L_00436135:
        cmp eax,12h
    L_00436138:
        mov edi,dword ptr [esp+14h]
    L_0043613c:
        mov ebx,eax
    L_0043613e:
        mov dword ptr [edi],esi
    L_00436140:
        jge short L_00436166
    L_00436142:
        test ecx,ecx
    L_00436144:
        lea eax,[esi+esi*2]
    L_00436147:
        jl short L_00436152
    L_00436149:
        lea eax,[eax*4+477860h]
    L_00436150:
        jmp short L_00436159
    L_00436152:
        lea eax,[eax*4+47785Ch]
    L_00436159:
        mov ecx,dword ptr [eax]
    L_0043615b:
        test ecx,ecx
    L_0043615d:
        je short L_004361d9
    L_0043615f:
        mov esi,ecx
    L_00436161:
        jmp asm_target_00436015
    L_00436166:
        lea ecx,[esi+esi*2]
    L_00436169:
        lea edi,[ecx*4+477858h]
    L_00436170:
        mov ecx,dword ptr [edi]
    L_00436172:
        lea ecx,[ecx+ecx*2]
    L_00436175:
        shl ecx,2
    L_00436178:
        cmp dword ptr [ecx+47785Ch],esi
    L_0043617e:
        jne short L_00436188
    L_00436180:
        mov dword ptr [ecx+47785Ch],edx
    L_00436186:
        jmp short L_0043618e
    L_00436188:
        mov dword ptr [ecx+477860h],edx
    L_0043618e:
        lea ecx,[edx+edx*2]
    L_00436191:
        shl ecx,2
    L_00436194:
        lea esi,[ecx+477858h]
    L_0043619a:
        mov ebx,edi
    L_0043619c:
        mov ebp,dword ptr [ebx]
    L_0043619e:
        mov dword ptr [esi],ebp
    L_004361a0:
        mov ebp,dword ptr [ebx+4]
    L_004361a3:
        mov dword ptr [esi+4],ebp
    L_004361a6:
        mov ebx,dword ptr [ebx+8]
    L_004361a9:
        mov dword ptr [esi+8],ebx
    L_004361ac:
        mov esi,dword ptr [ecx+47785Ch]
    L_004361b2:
        lea esi,[esi+esi*2]
    L_004361b5:
        mov dword ptr [esi*4+477858h],edx
    L_004361bc:
        mov ecx,dword ptr [ecx+477860h]
    L_004361c2:
        lea ecx,[ecx+ecx*2]
    L_004361c5:
        mov dword ptr [ecx*4+477858h],edx
    L_004361cc:
        mov dword ptr [edi],0
    L_004361d2:
        pop edi
    L_004361d3:
        pop ebp
    L_004361d4:
        pop esi
    L_004361d5:
        pop ebx
    L_004361d6:
        ret 4
    L_004361d9:
        mov dword ptr [eax],edx
    L_004361db:
        pop edi
    L_004361dc:
        lea eax,[edx+edx*2]
    L_004361df:
        shl eax,2
    L_004361e2:
        pop ebp
    L_004361e3:
        mov dword ptr [eax+477858h],esi
    L_004361e9:
        mov dword ptr [eax+477860h],0
    L_004361f3:
        mov dword ptr [eax+47785Ch],0
    L_004361fd:
        pop esi
    L_004361fe:
        mov eax,ebx
    L_00436200:
        pop ebx
    L_00436201:
        ret 4
    }
}
