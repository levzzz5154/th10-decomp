#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"


// BLOCKED (D3301): closest_byte_count=3/2247; first_diff=0x0041A200;
// residual_class=large-schema2 archive traversal/write sequencing and helper
// ABI; variants_tested=live-Ghidra decompile plus callers/callees (caller
// 0x00418EE0; callees 0x0044B620, 0x0044B740, 0x00452AE8, 0x00463B2C),
// MSVC 13.10 readable call-graph probe (41-byte extent, 3 matching bytes);
// native-LTCG was not applicable without a real caller/layout cluster;
// next_lever=derive typed stage/tip node layouts and real WriteSharedFile
// argument homes, then compile a native-LTCG caller/callee cluster.

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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a45b:
        cmp esi,dword ptr [esp+1Ch]
    L_0041a45f:
        je short L_0041a47f
    L_0041a461:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a467:
        push edx
    L_0041a468:
        call dword ptr [imp_CloseHandle]
    L_0041a46e:
        push 4922A4h
    L_0041a473:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a479:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a4bc:
        cmp esi,dword ptr [esp+20h]
    L_0041a4c0:
        je short L_0041a4e0
    L_0041a4c2:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a4c8:
        push edx
    L_0041a4c9:
        call dword ptr [imp_CloseHandle]
    L_0041a4cf:
        push 4922A4h
    L_0041a4d4:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a4da:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a51f:
        cmp esi,dword ptr [esp+24h]
    L_0041a523:
        je short L_0041a542
    L_0041a525:
        mov eax,dword ptr [g_file_write_handle]
    L_0041a52a:
        push eax
    L_0041a52b:
        call dword ptr [imp_CloseHandle]
    L_0041a531:
        push 4922A4h
    L_0041a536:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a53c:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a587:
        cmp esi,dword ptr [esp+28h]
    L_0041a58b:
        je short L_0041a5aa
    L_0041a58d:
        mov eax,dword ptr [g_file_write_handle]
    L_0041a592:
        push eax
    L_0041a593:
        call dword ptr [imp_CloseHandle]
    L_0041a599:
        push 4922A4h
    L_0041a59e:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a5a4:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a5e6:
        cmp esi,dword ptr [esp+2Ch]
    L_0041a5ea:
        je short L_0041a609
    L_0041a5ec:
        mov eax,dword ptr [g_file_write_handle]
    L_0041a5f1:
        push eax
    L_0041a5f2:
        call dword ptr [imp_CloseHandle]
    L_0041a5f8:
        push 4922A4h
    L_0041a5fd:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a603:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a655:
        cmp esi,dword ptr [esp+30h]
    L_0041a659:
        je short L_0041a679
    L_0041a65b:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a661:
        push edx
    L_0041a662:
        call dword ptr [imp_CloseHandle]
    L_0041a668:
        push 4922A4h
    L_0041a66d:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a673:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a6b5:
        cmp esi,dword ptr [esp+34h]
    L_0041a6b9:
        je short L_0041a6d9
    L_0041a6bb:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a6c1:
        push edx
    L_0041a6c2:
        call dword ptr [imp_CloseHandle]
    L_0041a6c8:
        push 4922A4h
    L_0041a6cd:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a6d3:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a735:
        cmp esi,dword ptr [esp+38h]
    L_0041a739:
        je short L_0041a759
    L_0041a73b:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a741:
        push edx
    L_0041a742:
        call dword ptr [imp_CloseHandle]
    L_0041a748:
        push 4922A4h
    L_0041a74d:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a753:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a7b5:
        cmp esi,dword ptr [esp+3Ch]
    L_0041a7b9:
        je short L_0041a7d9
    L_0041a7bb:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a7c1:
        push edx
    L_0041a7c2:
        call dword ptr [imp_CloseHandle]
    L_0041a7c8:
        push 4922A4h
    L_0041a7cd:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a7d3:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a815:
        cmp esi,dword ptr [esp+40h]
    L_0041a819:
        je short L_0041a839
    L_0041a81b:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a821:
        push edx
    L_0041a822:
        call dword ptr [imp_CloseHandle]
    L_0041a828:
        push 4922A4h
    L_0041a82d:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a833:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a879:
        cmp esi,dword ptr [esp+44h]
    L_0041a87d:
        je short L_0041a89d
    L_0041a87f:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a885:
        push edx
    L_0041a886:
        call dword ptr [imp_CloseHandle]
    L_0041a88c:
        push 4922A4h
    L_0041a891:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a897:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a8ed:
        cmp esi,dword ptr [esp+48h]
    L_0041a8f1:
        je short L_0041a911
    L_0041a8f3:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a8f9:
        push edx
    L_0041a8fa:
        call dword ptr [imp_CloseHandle]
    L_0041a900:
        push 4922A4h
    L_0041a905:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a90b:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a955:
        cmp esi,dword ptr [esp+4Ch]
    L_0041a959:
        je short L_0041a979
    L_0041a95b:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a961:
        push edx
    L_0041a962:
        call dword ptr [imp_CloseHandle]
    L_0041a968:
        push 4922A4h
    L_0041a96d:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a973:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041a9b6:
        cmp esi,dword ptr [esp+50h]
    L_0041a9ba:
        je short L_0041a9da
    L_0041a9bc:
        mov edx,dword ptr [g_file_write_handle]
    L_0041a9c2:
        push edx
    L_0041a9c3:
        call dword ptr [imp_CloseHandle]
    L_0041a9c9:
        push 4922A4h
    L_0041a9ce:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041a9d4:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
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
        call dword ptr [imp_WriteFile]
    L_0041aa38:
        cmp esi,dword ptr [esp+54h]
    L_0041aa3c:
        je short L_0041aa5c
    L_0041aa3e:
        mov edx,dword ptr [g_file_write_handle]
    L_0041aa44:
        push edx
    L_0041aa45:
        call dword ptr [imp_CloseHandle]
    L_0041aa4b:
        push 4922A4h
    L_0041aa50:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041aa56:
        dec byte ptr [g_file_lock_depth]
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
        mov eax,dword ptr [g_file_write_handle]
    L_0041aa7e:
        cmp eax,0FFFFFFFFh
    L_0041aa81:
        je short L_0041aa9b
    L_0041aa83:
        push eax
    L_0041aa84:
        call dword ptr [imp_CloseHandle]
    L_0041aa8a:
        push 4922A4h
    L_0041aa8f:
        call dword ptr [imp_LeaveCriticalSection]
    L_0041aa95:
        dec byte ptr [g_file_lock_depth]
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
