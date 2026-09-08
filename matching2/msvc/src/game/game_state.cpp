#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402160..0x0040221B: ConstructGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ConstructGameState_00402160() {
    __asm {
    L_00402160:
        mov eax,dword ptr fs:[0]
    L_00402166:
        push 0FFFFFFFFh
    L_00402168:
        push 46556Bh
    L_0040216d:
        push eax
    L_0040216e:
        mov dword ptr fs:[0],esp
    L_00402175:
        push esi
    L_00402176:
        mov esi,dword ptr [esp+14h]
    L_0040217a:
        mov ecx,dword ptr [esi+34h]
    L_0040217d:
        push edi
    L_0040217e:
        mov edi,0FFFFFFFEh
    L_00402183:
        and ecx,edi
    L_00402185:
        mov dword ptr [esi+34h],ecx
    L_00402188:
        and dword ptr [esi+48h],edi
    L_0040218b:
        and dword ptr [esi+90h],edi
    L_00402191:
        mov ecx,dword ptr [esi+0DCh]
    L_00402197:
        push 401FF0h
    L_0040219c:
        and ecx,edi
    L_0040219e:
        mov dword ptr [esi+0DCh],ecx
    L_004021a4:
        mov eax,dword ptr [esi+168h]
    L_004021aa:
        push 402050h
    L_004021af:
        and eax,edi
    L_004021b1:
        push 8
    L_004021b3:
        mov dword ptr [esi+168h],eax
    L_004021b9:
        push 3ACh
    L_004021be:
        lea eax,[esi+180h]
    L_004021c4:
        push eax
    L_004021c5:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004021ca:
        push 401FF0h
    L_004021cf:
        push 402050h
    L_004021d4:
        push 3
    L_004021d6:
        push 3ACh
    L_004021db:
        lea ecx,[esi+1F08h]
    L_004021e1:
        push ecx
    L_004021e2:
        mov dword ptr [esp+24h],0
    L_004021ea:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004021ef:
        and dword ptr [esi+2A2Ch],edi
    L_004021f5:
        xor eax,eax
    L_004021f7:
        mov edi,esi
    L_004021f9:
        mov ecx,0AD9h
    L_004021fe:
        rep stosd
    L_00402200:
        mov eax,dword ptr [esi]
    L_00402202:
        mov ecx,dword ptr [esp+8]
    L_00402206:
        or eax,2
    L_00402209:
        mov dword ptr [esi],eax
    L_0040220b:
        pop edi
    L_0040220c:
        mov eax,esi
    L_0040220e:
        mov dword ptr fs:[0],ecx
    L_00402215:
        pop esi
    L_00402216:
        add esp,0Ch
    L_00402219:
        ret 4
    }
}

// 0x00402230..0x00402439: InitializeGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_InitializeGameState_00402230() {
    __asm {
    L_00402230:
        sub esp,0Ch
    L_00402233:
        push ebx
    L_00402234:
        push ebp
    L_00402235:
        mov ebp,dword ptr [esp+18h]
    L_00402239:
        test ebp,ebp
    L_0040223b:
        push edi
    L_0040223c:
        mov ebx,eax
    L_0040223e:
        jne short L_00402248
    L_00402240:
        mov dword ptr [data_004776e8],ebx
    L_00402246:
        jmp short L_0040224e
    L_00402248:
        mov dword ptr [data_004776e4],ebx
    L_0040224e:
        mov eax,dword ptr [data_00474c7c]
    L_00402253:
        push ecx
    L_00402254:
        mov dword ptr [ebx+2A30h],eax
    L_0040225a:
        call asm_FUN_00403850_00403850
    L_0040225f:
        test eax,eax
    L_00402261:
        je short L_00402281
    L_00402263:
        push 46CC70h
    L_00402268:
        mov edi,474F70h
    L_0040226d:
        call asm_TextLog_AppendLine_0044b8e0
    L_00402272:
        add esp,4
    L_00402275:
        pop edi
    L_00402276:
        pop ebp
    L_00402277:
        or eax,0FFFFFFFFh
    L_0040227a:
        pop ebx
    L_0040227b:
        add esp,0Ch
    L_0040227e:
        ret 4
    L_00402281:
        lea eax,[ebx+2A4Ch]
    L_00402287:
        mov edi,eax
    L_00402289:
        push esi
    L_0040228a:
        mov dword ptr [esp+10h],0
    L_00402292:
        mov edx,dword ptr [esp+10h]
    L_00402296:
        mov ecx,46h
    L_0040229b:
        mov esi,491D7Ch
    L_004022a0:
        rep movsd
    L_004022a2:
        mov dword ptr [eax],edx
    L_004022a4:
        mov dword ptr [esp+14h],0
    L_004022ac:
        mov ecx,dword ptr [esp+14h]
    L_004022b0:
        mov dword ptr [eax+4],ecx
    L_004022b3:
        mov dword ptr [esp+18h],0C4160000h
    L_004022bb:
        mov edx,dword ptr [esp+18h]
    L_004022bf:
        mov dword ptr [eax+8],edx
    L_004022c2:
        mov dword ptr [esp+10h],0
    L_004022ca:
        mov ecx,dword ptr [esp+10h]
    L_004022ce:
        lea eax,[ebx+2A58h]
    L_004022d4:
        mov dword ptr [eax],ecx
    L_004022d6:
        mov dword ptr [esp+14h],43960000h
    L_004022de:
        mov edx,dword ptr [esp+14h]
    L_004022e2:
        mov dword ptr [eax+4],edx
    L_004022e5:
        mov dword ptr [esp+18h],44160000h
    L_004022ed:
        mov ecx,dword ptr [esp+18h]
    L_004022f1:
        mov dword ptr [eax+8],ecx
    L_004022f4:
        mov dword ptr [esp+10h],0
    L_004022fc:
        mov eax,dword ptr [esp+10h]
    L_00402300:
        lea edx,[ebx+2A64h]
    L_00402306:
        mov dword ptr [edx],eax
    L_00402308:
        mov dword ptr [esp+14h],3F800000h
    L_00402310:
        mov ecx,dword ptr [esp+14h]
    L_00402314:
        mov dword ptr [edx+4],ecx
    L_00402317:
        mov dword ptr [esp+18h],0
    L_0040231f:
        mov eax,dword ptr [esp+18h]
    L_00402323:
        mov dword ptr [edx+8],eax
    L_00402326:
        mov dword ptr [esp+10h],0
    L_0040232e:
        mov edx,dword ptr [esp+10h]
    L_00402332:
        lea ecx,[ebx+2A88h]
    L_00402338:
        mov dword ptr [ecx],edx
    L_0040233a:
        mov dword ptr [esp+14h],0
    L_00402342:
        mov eax,dword ptr [esp+14h]
    L_00402346:
        mov dword ptr [esp+18h],0
    L_0040234e:
        mov edx,dword ptr [esp+18h]
    L_00402352:
        mov dword ptr [ecx+4],eax
    L_00402355:
        push 403050h
    L_0040235a:
        mov dword ptr [ecx+8],edx
    L_0040235d:
        mov dword ptr [ebx+1EE0h],4B12A310h
    L_00402367:
        call asm_SchedulerCallback_Create_00449ed0
    L_0040236c:
        mov esi,eax
    L_0040236e:
        mov edx,dword ptr [esi+4]
    L_00402371:
        mov eax,dword ptr [data_00491be4]
    L_00402376:
        and edx,0FFFFFFFDh
    L_00402379:
        lea edi,[ebp+0Ch]
    L_0040237c:
        push eax
    L_0040237d:
        mov dword ptr [esi+20h],ebx
    L_00402380:
        mov dword ptr [esi+4],edx
    L_00402383:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00402388:
        push 403060h
    L_0040238d:
        mov dword ptr [ebx+8],esi
    L_00402390:
        call asm_SchedulerCallback_Create_00449ed0
    L_00402395:
        mov ecx,dword ptr [data_00491be4]
    L_0040239b:
        mov esi,eax
    L_0040239d:
        and dword ptr [esi+4],0FFFFFFFDh
    L_004023a1:
        lea edi,[ebp+7]
    L_004023a4:
        push ecx
    L_004023a5:
        mov dword ptr [esi+20h],ebx
    L_004023a8:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004023ad:
        push 403070h
    L_004023b2:
        mov dword ptr [ebx+0Ch],esi
    L_004023b5:
        call asm_SchedulerCallback_Create_00449ed0
    L_004023ba:
        mov edx,dword ptr [data_00491be4]
    L_004023c0:
        mov esi,eax
    L_004023c2:
        mov eax,dword ptr [esi+4]
    L_004023c5:
        and eax,0FFFFFFFDh
    L_004023c8:
        lea edi,[ebp+0Ah]
    L_004023cb:
        push edx
    L_004023cc:
        mov dword ptr [esi+20h],ebx
    L_004023cf:
        mov dword ptr [esi+4],eax
    L_004023d2:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004023d7:
        xor ecx,ecx
    L_004023d9:
        mov dword ptr [ebx+2A40h],esi
    L_004023df:
        mov dword ptr [ebx+2A34h],ecx
    L_004023e5:
        mov eax,dword ptr [ebx+48h]
    L_004023e8:
        test al,1
    L_004023ea:
        pop esi
    L_004023eb:
        jne short L_00402407
    L_004023ed:
        or eax,1
    L_004023f0:
        mov dword ptr [ebx+3Ch],ecx
    L_004023f3:
        mov dword ptr [ebx+38h],0FFF0BDC1h
    L_004023fa:
        mov dword ptr [ebx+40h],ecx
    L_004023fd:
        mov dword ptr [ebx+44h],476F78h
    L_00402404:
        mov dword ptr [ebx+48h],eax
    L_00402407:
        mov dword ptr [ebx+3Ch],ecx
    L_0040240a:
        mov dword ptr [ebx+40h],ecx
    L_0040240d:
        mov dword ptr [ebx+38h],0FFFFFFFFh
    L_00402414:
        mov eax,dword ptr [ebx+2A18h]
    L_0040241a:
        pop edi
    L_0040241b:
        or eax,1
    L_0040241e:
        mov dword ptr [ebx+2A18h],eax
    L_00402424:
        pop ebp
    L_00402425:
        mov dword ptr [ebx+94h],ecx
    L_0040242b:
        mov dword ptr [ebx+0E0h],ecx
    L_00402431:
        xor eax,eax
    L_00402433:
        pop ebx
    L_00402434:
        add esp,0Ch
    L_00402437:
        ret 4
    }
}

// 0x00402440..0x00402632: DestroyGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DestroyGameState_00402440() {
    __asm {
    L_00402440:
        push 0FFFFFFFFh
    L_00402442:
        push 4652D6h
    L_00402447:
        mov eax,dword ptr fs:[0]
    L_0040244d:
        push eax
    L_0040244e:
        mov dword ptr fs:[0],esp
    L_00402455:
        push ecx
    L_00402456:
        push ebx
    L_00402457:
        push ebp
    L_00402458:
        push esi
    L_00402459:
        mov esi,dword ptr [esp+20h]
    L_0040245d:
        push edi
    L_0040245e:
        mov dword ptr [esp+1Ch],1
    L_00402466:
        mov edi,dword ptr [esi+8]
    L_00402469:
        test edi,edi
    L_0040246b:
        mov eax,dword ptr [data_00491be4]
    L_00402470:
        mov ebp,dword ptr [data_004660b0]
    L_00402476:
        mov ebx,dword ptr [data_004660b4]
    L_0040247c:
        mov dword ptr [esp+10h],eax
    L_00402480:
        je short L_004024a7
    L_00402482:
        push 492274h
    L_00402487:
        call ebp
    L_00402489:
        inc byte ptr [data_0049231c]
    L_0040248f:
        mov edx,dword ptr [esp+10h]
    L_00402493:
        mov ecx,edi
    L_00402495:
        call asm_Scheduler_Remove_00449f60
    L_0040249a:
        push 492274h
    L_0040249f:
        call ebx
    L_004024a1:
        dec byte ptr [data_0049231c]
    L_004024a7:
        mov edi,dword ptr [esi+0Ch]
    L_004024aa:
        test edi,edi
    L_004024ac:
        mov ecx,dword ptr [data_00491be4]
    L_004024b2:
        mov dword ptr [esp+10h],ecx
    L_004024b6:
        je short L_004024dd
    L_004024b8:
        push 492274h
    L_004024bd:
        call ebp
    L_004024bf:
        inc byte ptr [data_0049231c]
    L_004024c5:
        mov edx,dword ptr [esp+10h]
    L_004024c9:
        mov ecx,edi
    L_004024cb:
        call asm_Scheduler_Remove_00449f60
    L_004024d0:
        push 492274h
    L_004024d5:
        call ebx
    L_004024d7:
        dec byte ptr [data_0049231c]
    L_004024dd:
        mov edi,dword ptr [esi+2A40h]
    L_004024e3:
        test edi,edi
    L_004024e5:
        mov edx,dword ptr [data_00491be4]
    L_004024eb:
        mov dword ptr [esp+10h],edx
    L_004024ef:
        je short L_00402516
    L_004024f1:
        push 492274h
    L_004024f6:
        call ebp
    L_004024f8:
        inc byte ptr [data_0049231c]
    L_004024fe:
        mov edx,dword ptr [esp+10h]
    L_00402502:
        mov ecx,edi
    L_00402504:
        call asm_Scheduler_Remove_00449f60
    L_00402509:
        push 492274h
    L_0040250e:
        call ebx
    L_00402510:
        dec byte ptr [data_0049231c]
    L_00402516:
        mov eax,dword ptr [esi+10h]
    L_00402519:
        test eax,eax
    L_0040251b:
        je short L_0040252d
    L_0040251d:
        push eax
    L_0040251e:
        call asm_free_00452422
    L_00402523:
        add esp,4
    L_00402526:
        mov dword ptr [esi+10h],0
    L_0040252d:
        mov eax,dword ptr [esi+2A44h]
    L_00402533:
        test eax,eax
    L_00402535:
        je short L_0040254a
    L_00402537:
        push eax
    L_00402538:
        call asm_free_00452422
    L_0040253d:
        add esp,4
    L_00402540:
        mov dword ptr [esi+2A44h],0
    L_0040254a:
        mov eax,dword ptr [esi+17Ch]
    L_00402550:
        test eax,eax
    L_00402552:
        mov dword ptr [esi+2A44h],0
    L_0040255c:
        je short L_00402571
    L_0040255e:
        push eax
    L_0040255f:
        call asm_free_00452422
    L_00402564:
        add esp,4
    L_00402567:
        mov dword ptr [esi+17Ch],0
    L_00402571:
        test byte ptr [data_00474ca0],1
    L_00402578:
        jne short L_004025bd
    L_0040257a:
        mov eax,dword ptr [esi+2A30h]
    L_00402580:
        and eax,1
    L_00402583:
        add eax,4
    L_00402586:
        js short L_004025bd
    L_00402588:
        cmp eax,21h
    L_0040258b:
        jae short L_004025bd
    L_0040258d:
        mov ecx,dword ptr [data_00491c10]
    L_00402593:
        mov edi,dword ptr [ecx+eax*4+3AD06Ch]
    L_0040259a:
        test edi,edi
    L_0040259c:
        lea ebp,[ecx+eax*4+3AD06Ch]
    L_004025a3:
        je short L_004025bd
    L_004025a5:
        call asm_FUN_00447810_00447810
    L_004025aa:
        mov eax,dword ptr [ebp]
    L_004025ad:
        push eax
    L_004025ae:
        call asm_free_004524a1
    L_004025b3:
        add esp,4
    L_004025b6:
        mov dword ptr [ebp],0
    L_004025bd:
        cmp dword ptr [data_004776e8],esi
    L_004025c3:
        jne short L_004025cf
    L_004025c5:
        mov dword ptr [data_004776e8],0
    L_004025cf:
        cmp dword ptr [data_004776e4],esi
    L_004025d5:
        jne short L_004025e1
    L_004025d7:
        mov dword ptr [data_004776e4],0
    L_004025e1:
        push 401FF0h
    L_004025e6:
        push 3
    L_004025e8:
        push 3ACh
    L_004025ed:
        lea edx,[esi+1F08h]
    L_004025f3:
        push edx
    L_004025f4:
        mov byte ptr [esp+2Ch],0
    L_004025f9:
        call asm_eh_vector_destructor_iterator_004525ff
    L_004025fe:
        push 401FF0h
    L_00402603:
        push 8
    L_00402605:
        push 3ACh
    L_0040260a:
        add esi,180h
    L_00402610:
        push esi
    L_00402611:
        mov dword ptr [esp+2Ch],0FFFFFFFFh
    L_00402619:
        call asm_eh_vector_destructor_iterator_004525ff
    L_0040261e:
        mov ecx,dword ptr [esp+14h]
    L_00402622:
        pop edi
    L_00402623:
        pop esi
    L_00402624:
        pop ebp
    L_00402625:
        pop ebx
    L_00402626:
        mov dword ptr fs:[0],ecx
    L_0040262d:
        add esp,10h
    L_00402630:
        ret 4
    }
}

// 0x00402640..0x004026D6: CreateGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CreateGameState_00402640() {
    __asm {
    L_00402640:
        push 0FFFFFFFFh
    L_00402642:
        push 46588Bh
    L_00402647:
        mov eax,dword ptr fs:[0]
    L_0040264d:
        push eax
    L_0040264e:
        mov dword ptr fs:[0],esp
    L_00402655:
        push ecx
    L_00402656:
        push esi
    L_00402657:
        push 2B64h
    L_0040265c:
        call asm_operator_new_00452493
    L_00402661:
        add esp,4
    L_00402664:
        mov dword ptr [esp+4],eax
    L_00402668:
        test eax,eax
    L_0040266a:
        mov dword ptr [esp+10h],0
    L_00402672:
        je short L_0040267e
    L_00402674:
        push eax
    L_00402675:
        call asm_ConstructGameState_00402160
    L_0040267a:
        mov esi,eax
    L_0040267c:
        jmp short L_00402680
    L_0040267e:
        xor esi,esi
    L_00402680:
        mov eax,dword ptr [esp+1Ch]
    L_00402684:
        mov ecx,dword ptr [esp+18h]
    L_00402688:
        push eax
    L_00402689:
        mov eax,esi
    L_0040268b:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_00402693:
        call asm_InitializeGameState_00402230
    L_00402698:
        test eax,eax
    L_0040269a:
        je short L_004026c3
    L_0040269c:
        test esi,esi
    L_0040269e:
        je short L_004026af
    L_004026a0:
        push esi
    L_004026a1:
        call asm_DestroyGameState_00402440
    L_004026a6:
        push esi
    L_004026a7:
        call asm_free_004524a1
    L_004026ac:
        add esp,4
    L_004026af:
        xor eax,eax
    L_004026b1:
        pop esi
    L_004026b2:
        mov ecx,dword ptr [esp+4]
    L_004026b6:
        mov dword ptr fs:[0],ecx
    L_004026bd:
        add esp,10h
    L_004026c0:
        ret 8
    L_004026c3:
        mov ecx,dword ptr [esp+8]
    L_004026c7:
        mov eax,esi
    L_004026c9:
        pop esi
    L_004026ca:
        mov dword ptr fs:[0],ecx
    L_004026d1:
        add esp,10h
    L_004026d4:
        ret 8
    }
}

// 0x00402850..0x00402C9A: FUN_00402850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00402850_00402850() {
    __asm {
    L_00402850:
        sub esp,20h
    L_00402853:
        push ebp
    L_00402854:
        mov ebp,dword ptr [esp+28h]
    L_00402858:
        mov eax,dword ptr [ebp+2A18h]
    L_0040285e:
        test al,8
    L_00402860:
        je short L_0040286e
    L_00402862:
        mov eax,1
    L_00402867:
        pop ebp
    L_00402868:
        add esp,20h
    L_0040286b:
        ret 4
    L_0040286e:
        test al,4
    L_00402870:
        push ebx
    L_00402871:
        push esi
    L_00402872:
        push edi
    L_00402873:
        je short L_00402882
    L_00402875:
        cmp dword ptr [ebp+2A20h],3Ch
    L_0040287c:
        jge asm_target_00402a40
    L_00402882:
        mov esi,dword ptr [data_00491c10]
    L_00402888:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0040288d:
        mov eax,dword ptr [data_00491e64]
    L_00402892:
        mov dword ptr [ebp+2B34h],eax
    L_00402898:
        mov ecx,dword ptr [data_00491e68]
    L_0040289e:
        mov dword ptr [ebp+2B38h],ecx
    L_004028a4:
        lea esi,[ebp+2A4Ch]
    L_004028aa:
        mov ecx,46h
    L_004028af:
        mov edi,491D7Ch
    L_004028b4:
        rep movsd
    L_004028b6:
        mov edi,491D7Ch
    L_004028bb:
        mov dword ptr [data_00491fac],edi
    L_004028c1:
        call asm_FUN_004215a0_004215a0
    L_004028c6:
        mov ecx,dword ptr [data_00491fac]
    L_004028cc:
        mov eax,dword ptr [data_00491c30]
    L_004028d1:
        mov edx,dword ptr [eax]
    L_004028d3:
        add ecx,0CCh
    L_004028d9:
        push ecx
    L_004028da:
        push eax
    L_004028db:
        call dword ptr [edx+0BCh]
    L_004028e1:
        mov esi,dword ptr [data_00491c10]
    L_004028e7:
        xor ebx,ebx
    L_004028e9:
        mov dword ptr [data_00491fb0],ebx
    L_004028ef:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004028f4:
        mov eax,dword ptr [data_00491c30]
    L_004028f9:
        mov edx,dword ptr [eax]
    L_004028fb:
        push 1
    L_004028fd:
        push 0Eh
    L_004028ff:
        push eax
    L_00402900:
        call dword ptr [edx+0E4h]
    L_00402906:
        mov esi,dword ptr [data_00491c10]
    L_0040290c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402911:
        mov eax,dword ptr [data_00491c30]
    L_00402916:
        mov ecx,dword ptr [eax]
    L_00402918:
        push 4
    L_0040291a:
        push 17h
    L_0040291c:
        push eax
    L_0040291d:
        call dword ptr [ecx+0E4h]
    L_00402923:
        mov esi,dword ptr [data_00491c10]
    L_00402929:
        mov edi,dword ptr [ebp+2B60h]
    L_0040292f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402934:
        mov eax,dword ptr [data_00491c30]
    L_00402939:
        mov edx,dword ptr [eax]
    L_0040293b:
        push edi
    L_0040293c:
        push 22h
    L_0040293e:
        push eax
    L_0040293f:
        call dword ptr [edx+0E4h]
    L_00402945:
        mov esi,dword ptr [data_00491c10]
    L_0040294b:
        mov edi,dword ptr [ebp+2B48h]
    L_00402951:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402956:
        mov eax,dword ptr [data_00491c30]
    L_0040295b:
        mov ecx,dword ptr [eax]
    L_0040295d:
        push edi
    L_0040295e:
        push 24h
    L_00402960:
        push eax
    L_00402961:
        call dword ptr [ecx+0E4h]
    L_00402967:
        mov esi,dword ptr [data_00491c10]
    L_0040296d:
        mov edi,dword ptr [ebp+2B4Ch]
    L_00402973:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402978:
        mov eax,dword ptr [data_00491c30]
    L_0040297d:
        mov edx,dword ptr [eax]
    L_0040297f:
        push edi
    L_00402980:
        push 25h
    L_00402982:
        push eax
    L_00402983:
        call dword ptr [edx+0E4h]
    L_00402989:
        mov eax,dword ptr [data_00491c30]
    L_0040298e:
        mov ecx,dword ptr [eax]
    L_00402990:
        push ebx
    L_00402991:
        push 3F800000h
    L_00402996:
        push ebx
    L_00402997:
        push 2
    L_00402999:
        push ebx
    L_0040299a:
        push ebx
    L_0040299b:
        push eax
    L_0040299c:
        call dword ptr [ecx+0ACh]
    L_004029a2:
        test byte ptr [ebp+2A18h],4
    L_004029a9:
        je short L_004029f4
    L_004029ab:
        cmp dword ptr [ebp+2A34h],22h
    L_004029b2:
        jge short L_004029f4
    L_004029b4:
        mov eax,dword ptr [data_00491c30]
    L_004029b9:
        push ebx
    L_004029ba:
        push 3F800000h
    L_004029bf:
        push ebx
    L_004029c0:
        push 1
    L_004029c2:
        lea ecx,[esp+20h]
    L_004029c6:
        push ecx
    L_004029c7:
        push 1
    L_004029c9:
        mov dword ptr [esp+28h],20h
    L_004029d1:
        mov dword ptr [esp+2Ch],10h
    L_004029d9:
        mov dword ptr [esp+30h],1A0h
    L_004029e1:
        mov dword ptr [esp+34h],1D0h
    L_004029e9:
        mov edx,dword ptr [eax]
    L_004029eb:
        push eax
    L_004029ec:
        call dword ptr [edx+0ACh]
    L_004029f2:
        jmp short L_00402a42
    L_004029f4:
        mov ecx,dword ptr [ebp+2B60h]
    L_004029fa:
        mov eax,dword ptr [data_00491c30]
    L_004029ff:
        push ebx
    L_00402a00:
        push 3F800000h
    L_00402a05:
        and ecx,0FFFFFFh
    L_00402a0b:
        push ecx
    L_00402a0c:
        push 1
    L_00402a0e:
        lea ecx,[esp+30h]
    L_00402a12:
        push ecx
    L_00402a13:
        push 1
    L_00402a15:
        mov dword ptr [esp+38h],20h
    L_00402a1d:
        mov dword ptr [esp+3Ch],10h
    L_00402a25:
        mov dword ptr [esp+40h],1A0h
    L_00402a2d:
        mov dword ptr [esp+44h],1D0h
    L_00402a35:
        mov edx,dword ptr [eax]
    L_00402a37:
        push eax
    L_00402a38:
        call dword ptr [edx+0ACh]
    L_00402a3e:
        jmp short L_00402a42
    L_00402a40:
        xor ebx,ebx
    L_00402a42:
        mov eax,dword ptr [ebp+2A18h]
    L_00402a48:
        test al,4
    L_00402a4a:
        je short L_00402a95
    L_00402a4c:
        cmp dword ptr [ebp+2A20h],1Eh
    L_00402a53:
        jge short L_00402a86
    L_00402a55:
        push ebx
    L_00402a56:
        push ebx
    L_00402a57:
        push ebx
    L_00402a58:
        push 1Eh
    L_00402a5a:
        push 3
    L_00402a5c:
        mov ebx,0Fh
    L_00402a61:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00402a66:
        mov ecx,dword ptr [ebp+2A18h]
    L_00402a6c:
        or ecx,1
    L_00402a6f:
        push 1
    L_00402a71:
        lea eax,[ebp+2A1Ch]
    L_00402a77:
        mov dword ptr [ebp+2A18h],ecx
    L_00402a7d:
        call asm_Player_SetSchedulerValue_00405410
    L_00402a82:
        xor ebx,ebx
    L_00402a84:
        jmp short L_00402a95
    L_00402a86:
        and eax,0FFFFFFFEh
    L_00402a89:
        mov byte ptr [ebp+1EEBh],bl
    L_00402a8f:
        mov dword ptr [ebp+2A18h],eax
    L_00402a95:
        cmp byte ptr [ebp+1EEBh],bl
    L_00402a9b:
        mov esi,dword ptr [data_00491c10]
    L_00402aa1:
        mov edi,1
    L_00402aa6:
        je short L_00402aba
    L_00402aa8:
        mov eax,dword ptr [ebp+1EE8h]
    L_00402aae:
        mov dword ptr [esi+73245Ch],edi
    L_00402ab4:
        mov dword ptr [esi+732458h],eax
    L_00402aba:
        test byte ptr [ebp+2A18h],1
    L_00402ac1:
        mov dword ptr [ebp+2A0Ch],ebx
    L_00402ac7:
        mov dword ptr [ebp+2A10h],ebx
    L_00402acd:
        mov dword ptr [ebp+2A14h],ebx
    L_00402ad3:
        je asm_target_00402c34
    L_00402ad9:
        cmp dword ptr [ebp+514h],ebx
    L_00402adf:
        je asm_target_00402baa
    L_00402ae5:
        xor ebx,ebx
    L_00402ae7:
        mov esi,491C28h
    L_00402aec:
        call asm_FUN_00405300_00405300
    L_00402af1:
        mov edi,esi
    L_00402af3:
        call asm_FUN_00420cd0_00420cd0
    L_00402af8:
        mov esi,dword ptr [data_00491c10]
    L_00402afe:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402b03:
        mov esi,dword ptr [data_00491c10]
    L_00402b09:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402b0e:
        mov eax,dword ptr [data_00491c30]
    L_00402b13:
        mov edx,dword ptr [eax]
    L_00402b15:
        push ebx
    L_00402b16:
        push 0Eh
    L_00402b18:
        push eax
    L_00402b19:
        call dword ptr [edx+0E4h]
    L_00402b1f:
        lea esi,[ebp+180h]
    L_00402b25:
        mov edi,8
    L_00402b2a:
        lea ebx,[ebx+force_disp32_zero]
    L_00402b30:
        mov eax,dword ptr [esi+394h]
    L_00402b36:
        test eax,eax
    L_00402b38:
        je short L_00402b47
    L_00402b3a:
        mov ecx,dword ptr [data_00491c10]
    L_00402b40:
        mov eax,esi
    L_00402b42:
        call asm_FUN_004451c0_004451c0
    L_00402b47:
        add esi,3ACh
    L_00402b4d:
        dec edi
    L_00402b4e:
        jne short L_00402b30
    L_00402b50:
        mov esi,dword ptr [data_00491c10]
    L_00402b56:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402b5b:
        mov eax,dword ptr [data_00491c30]
    L_00402b60:
        mov ecx,dword ptr [eax]
    L_00402b62:
        push 1
    L_00402b64:
        push 0Eh
    L_00402b66:
        push eax
    L_00402b67:
        call dword ptr [ecx+0E4h]
    L_00402b6d:
        mov edi,491D7Ch
    L_00402b72:
        mov dword ptr [data_00491fac],edi
    L_00402b78:
        call asm_FUN_004215a0_004215a0
    L_00402b7d:
        mov ecx,dword ptr [data_00491fac]
    L_00402b83:
        mov eax,dword ptr [data_00491c30]
    L_00402b88:
        mov edx,dword ptr [eax]
    L_00402b8a:
        add ecx,0CCh
    L_00402b90:
        push ecx
    L_00402b91:
        push eax
    L_00402b92:
        call dword ptr [edx+0BCh]
    L_00402b98:
        mov esi,dword ptr [data_00491c10]
    L_00402b9e:
        mov dword ptr [data_00491fb0],0
    L_00402ba8:
        xor ebx,ebx
    L_00402baa:
        mov eax,dword ptr [data_00492378]
    L_00402baf:
        mov edi,1
    L_00402bb4:
        cmp eax,edi
    L_00402bb6:
        je short L_00402bd4
    L_00402bb8:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402bbd:
        mov eax,dword ptr [data_00491c30]
    L_00402bc2:
        push edi
    L_00402bc3:
        push 1Ch
    L_00402bc5:
        mov dword ptr [data_00492378],edi
    L_00402bcb:
        mov edx,dword ptr [eax]
    L_00402bcd:
        push eax
    L_00402bce:
        call dword ptr [edx+0E4h]
    L_00402bd4:
        push ebx
    L_00402bd5:
        push ebp
    L_00402bd6:
        call asm_FUN_00403a30_00403a30
    L_00402bdb:
        push edi
    L_00402bdc:
        push ebp
    L_00402bdd:
        call asm_FUN_00403a30_00403a30
    L_00402be2:
        push 2
    L_00402be4:
        push ebp
    L_00402be5:
        call asm_FUN_00403a30_00403a30
    L_00402bea:
        push 3
    L_00402bec:
        push ebp
    L_00402bed:
        call asm_FUN_00403a30_00403a30
    L_00402bf2:
        push 4
    L_00402bf4:
        push ebp
    L_00402bf5:
        call asm_FUN_00403a30_00403a30
    L_00402bfa:
        push 5
    L_00402bfc:
        push ebp
    L_00402bfd:
        call asm_FUN_00403a30_00403a30
    L_00402c02:
        push 6
    L_00402c04:
        push ebp
    L_00402c05:
        call asm_FUN_00403a30_00403a30
    L_00402c0a:
        push 7
    L_00402c0c:
        push ebp
    L_00402c0d:
        call asm_FUN_00403a30_00403a30
    L_00402c12:
        mov esi,dword ptr [data_00491c10]
    L_00402c18:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402c1d:
        mov eax,dword ptr [ebp+1EE4h]
    L_00402c23:
        cmp eax,ebx
    L_00402c25:
        mov esi,dword ptr [data_00491c10]
    L_00402c2b:
        je short L_00402c34
    L_00402c2d:
        inc eax
    L_00402c2e:
        mov dword ptr [ebp+1EE4h],eax
    L_00402c34:
        mov dword ptr [esi+73245Ch],ebx
    L_00402c3a:
        mov dword ptr [esi+732458h],80808080h
    L_00402c44:
        cmp dword ptr [ebp+1EECh],ebx
    L_00402c4a:
        je short L_00402c5c
    L_00402c4c:
        mov dword ptr [esi+73245Ch],edi
    L_00402c52:
        mov dword ptr [esi+732458h],0FF404040h
    L_00402c5c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402c61:
        mov eax,dword ptr [data_00491c30]
    L_00402c66:
        mov ecx,dword ptr [eax]
    L_00402c68:
        push ebx
    L_00402c69:
        push 0Eh
    L_00402c6b:
        push eax
    L_00402c6c:
        call dword ptr [ecx+0E4h]
    L_00402c72:
        mov esi,dword ptr [data_00491c10]
    L_00402c78:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402c7d:
        mov eax,dword ptr [data_00491c30]
    L_00402c82:
        mov edx,dword ptr [eax]
    L_00402c84:
        push 8
    L_00402c86:
        push 17h
    L_00402c88:
        push eax
    L_00402c89:
        call dword ptr [edx+0E4h]
    L_00402c8f:
        mov eax,edi
    L_00402c91:
        pop edi
    L_00402c92:
        pop esi
    L_00402c93:
        pop ebx
    L_00402c94:
        pop ebp
    L_00402c95:
        add esp,20h
    L_00402c98:
        ret 4
    }
}

// 0x00402CA0..0x00403040: FUN_00402ca0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00402ca0_00402ca0() {
    __asm {
    L_00402ca0:
        push ebp
    L_00402ca1:
        mov ebp,dword ptr [esp+8]
    L_00402ca5:
        mov eax,dword ptr [ebp+2A18h]
    L_00402cab:
        test al,8
    L_00402cad:
        je short L_00402cb8
    L_00402caf:
        mov eax,1
    L_00402cb4:
        pop ebp
    L_00402cb5:
        ret 4
    L_00402cb8:
        push ebx
    L_00402cb9:
        push esi
    L_00402cba:
        xor ebx,ebx
    L_00402cbc:
        test al,4
    L_00402cbe:
        push edi
    L_00402cbf:
        je short L_00402cce
    L_00402cc1:
        cmp dword ptr [ebp+2A20h],3Ch
    L_00402cc8:
        jge asm_target_00402e86
    L_00402cce:
        mov esi,dword ptr [data_00491c10]
    L_00402cd4:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402cd9:
        mov eax,dword ptr [data_00491e64]
    L_00402cde:
        mov dword ptr [ebp+2B34h],eax
    L_00402ce4:
        mov ecx,dword ptr [data_00491e68]
    L_00402cea:
        mov dword ptr [ebp+2B38h],ecx
    L_00402cf0:
        lea esi,[ebp+2A4Ch]
    L_00402cf6:
        mov ecx,46h
    L_00402cfb:
        mov edi,491D7Ch
    L_00402d00:
        rep movsd
    L_00402d02:
        mov edi,491D7Ch
    L_00402d07:
        mov dword ptr [data_00491fac],edi
    L_00402d0d:
        call asm_FUN_004215a0_004215a0
    L_00402d12:
        mov ecx,dword ptr [data_00491fac]
    L_00402d18:
        mov eax,dword ptr [data_00491c30]
    L_00402d1d:
        mov edx,dword ptr [eax]
    L_00402d1f:
        add ecx,0CCh
    L_00402d25:
        push ecx
    L_00402d26:
        push eax
    L_00402d27:
        call dword ptr [edx+0BCh]
    L_00402d2d:
        mov eax,dword ptr [data_00492378]
    L_00402d32:
        mov edi,1
    L_00402d37:
        cmp eax,edi
    L_00402d39:
        mov dword ptr [data_00491fb0],ebx
    L_00402d3f:
        je short L_00402d63
    L_00402d41:
        mov esi,dword ptr [data_00491c10]
    L_00402d47:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402d4c:
        mov eax,dword ptr [data_00491c30]
    L_00402d51:
        push edi
    L_00402d52:
        push 1Ch
    L_00402d54:
        mov dword ptr [data_00492378],edi
    L_00402d5a:
        mov edx,dword ptr [eax]
    L_00402d5c:
        push eax
    L_00402d5d:
        call dword ptr [edx+0E4h]
    L_00402d63:
        mov esi,dword ptr [data_00491c10]
    L_00402d69:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402d6e:
        mov eax,dword ptr [data_00491c30]
    L_00402d73:
        mov ecx,dword ptr [eax]
    L_00402d75:
        push ebx
    L_00402d76:
        push 0Eh
    L_00402d78:
        push eax
    L_00402d79:
        call dword ptr [ecx+0E4h]
    L_00402d7f:
        mov esi,dword ptr [data_00491c10]
    L_00402d85:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402d8a:
        mov eax,dword ptr [data_00491c30]
    L_00402d8f:
        mov edx,dword ptr [eax]
    L_00402d91:
        push 8
    L_00402d93:
        push 17h
    L_00402d95:
        push eax
    L_00402d96:
        call dword ptr [edx+0E4h]
    L_00402d9c:
        mov edi,dword ptr [data_00491c10]
    L_00402da2:
        mov eax,11h
    L_00402da7:
        call asm_AnimationManager_RenderBucket_00448980
    L_00402dac:
        mov esi,dword ptr [data_00491c10]
    L_00402db2:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402db7:
        mov eax,dword ptr [data_00491c30]
    L_00402dbc:
        mov ecx,dword ptr [eax]
    L_00402dbe:
        push 4
    L_00402dc0:
        push 17h
    L_00402dc2:
        push eax
    L_00402dc3:
        call dword ptr [ecx+0E4h]
    L_00402dc9:
        cmp dword ptr [data_00492378],ebx
    L_00402dcf:
        je short L_00402df3
    L_00402dd1:
        mov esi,dword ptr [data_00491c10]
    L_00402dd7:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402ddc:
        mov eax,dword ptr [data_00491c30]
    L_00402de1:
        push ebx
    L_00402de2:
        push 1Ch
    L_00402de4:
        mov dword ptr [data_00492378],ebx
    L_00402dea:
        mov edx,dword ptr [eax]
    L_00402dec:
        push eax
    L_00402ded:
        call dword ptr [edx+0E4h]
    L_00402df3:
        mov edi,dword ptr [data_00491c10]
    L_00402df9:
        mov eax,12h
    L_00402dfe:
        call asm_AnimationManager_RenderBucket_00448980
    L_00402e03:
        mov esi,dword ptr [data_00491c10]
    L_00402e09:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e0e:
        mov eax,dword ptr [data_00491c30]
    L_00402e13:
        mov ecx,dword ptr [eax]
    L_00402e15:
        push 4
    L_00402e17:
        push 17h
    L_00402e19:
        push eax
    L_00402e1a:
        call dword ptr [ecx+0E4h]
    L_00402e20:
        mov esi,dword ptr [data_00491c10]
    L_00402e26:
        mov edi,dword ptr [ebp+2B60h]
    L_00402e2c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e31:
        mov eax,dword ptr [data_00491c30]
    L_00402e36:
        mov edx,dword ptr [eax]
    L_00402e38:
        push edi
    L_00402e39:
        push 22h
    L_00402e3b:
        push eax
    L_00402e3c:
        call dword ptr [edx+0E4h]
    L_00402e42:
        mov esi,dword ptr [data_00491c10]
    L_00402e48:
        mov edi,dword ptr [ebp+2B48h]
    L_00402e4e:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e53:
        mov eax,dword ptr [data_00491c30]
    L_00402e58:
        mov ecx,dword ptr [eax]
    L_00402e5a:
        push edi
    L_00402e5b:
        push 24h
    L_00402e5d:
        push eax
    L_00402e5e:
        call dword ptr [ecx+0E4h]
    L_00402e64:
        mov esi,dword ptr [data_00491c10]
    L_00402e6a:
        mov edi,dword ptr [ebp+2B4Ch]
    L_00402e70:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402e75:
        mov eax,dword ptr [data_00491c30]
    L_00402e7a:
        mov edx,dword ptr [eax]
    L_00402e7c:
        push edi
    L_00402e7d:
        push 25h
    L_00402e7f:
        push eax
    L_00402e80:
        call dword ptr [edx+0E4h]
    L_00402e86:
        mov eax,dword ptr [ebp+2A18h]
    L_00402e8c:
        test al,4
    L_00402e8e:
        je short L_00402e9f
    L_00402e90:
        cmp dword ptr [ebp+2A20h],1Eh
    L_00402e97:
        jl short L_00402e9f
    L_00402e99:
        mov byte ptr [ebp+1EEBh],bl
    L_00402e9f:
        test al,1
    L_00402ea1:
        je short L_00402f1c
    L_00402ea3:
        mov esi,dword ptr [data_00491c10]
    L_00402ea9:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402eae:
        mov eax,dword ptr [data_00491c30]
    L_00402eb3:
        mov ecx,dword ptr [eax]
    L_00402eb5:
        push ebx
    L_00402eb6:
        push 0Eh
    L_00402eb8:
        push eax
    L_00402eb9:
        call dword ptr [ecx+0E4h]
    L_00402ebf:
        mov eax,dword ptr [data_00492378]
    L_00402ec4:
        mov edi,1
    L_00402ec9:
        cmp eax,edi
    L_00402ecb:
        je short L_00402eef
    L_00402ecd:
        mov esi,dword ptr [data_00491c10]
    L_00402ed3:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402ed8:
        mov eax,dword ptr [data_00491c30]
    L_00402edd:
        push edi
    L_00402ede:
        push 1Ch
    L_00402ee0:
        mov dword ptr [data_00492378],edi
    L_00402ee6:
        mov edx,dword ptr [eax]
    L_00402ee8:
        push eax
    L_00402ee9:
        call dword ptr [edx+0E4h]
    L_00402eef:
        push 8
    L_00402ef1:
        push ebp
    L_00402ef2:
        call asm_FUN_00403a30_00403a30
    L_00402ef7:
        push 9
    L_00402ef9:
        push ebp
    L_00402efa:
        call asm_FUN_00403a30_00403a30
    L_00402eff:
        push 0Ah
    L_00402f01:
        push ebp
    L_00402f02:
        call asm_FUN_00403a30_00403a30
    L_00402f07:
        push 0Bh
    L_00402f09:
        push ebp
    L_00402f0a:
        call asm_FUN_00403a30_00403a30
    L_00402f0f:
        mov esi,dword ptr [data_00491c10]
    L_00402f15:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402f1a:
        jmp short L_00402f21
    L_00402f1c:
        mov edi,1
    L_00402f21:
        mov esi,dword ptr [data_00491c10]
    L_00402f27:
        mov dword ptr [esi+73245Ch],ebx
    L_00402f2d:
        mov dword ptr [esi+732458h],80808080h
    L_00402f37:
        cmp dword ptr [ebp+1EECh],ebx
    L_00402f3d:
        je short L_00402f4f
    L_00402f3f:
        mov dword ptr [esi+73245Ch],edi
    L_00402f45:
        mov dword ptr [esi+732458h],0FF404040h
    L_00402f4f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402f54:
        mov eax,dword ptr [data_00491c30]
    L_00402f59:
        mov ecx,dword ptr [eax]
    L_00402f5b:
        push ebx
    L_00402f5c:
        push 0Eh
    L_00402f5e:
        push eax
    L_00402f5f:
        call dword ptr [ecx+0E4h]
    L_00402f65:
        mov esi,dword ptr [data_00491c10]
    L_00402f6b:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402f70:
        mov eax,dword ptr [data_00491c30]
    L_00402f75:
        mov edx,dword ptr [eax]
    L_00402f77:
        push 8
    L_00402f79:
        push 17h
    L_00402f7b:
        push eax
    L_00402f7c:
        call dword ptr [edx+0E4h]
    L_00402f82:
        cmp dword ptr [ebp+2A20h],ebx
    L_00402f88:
        jle short L_00402fd5
    L_00402f8a:
        push 0BF800000h
    L_00402f8f:
        lea esi,[ebp+2A1Ch]
    L_00402f95:
        call asm_FrameTimer_Advance_0044bf40
    L_00402f9a:
        cmp dword ptr [ebp+2A20h],ebx
    L_00402fa0:
        jg short L_00402fd5
    L_00402fa2:
        mov eax,dword ptr [ebp+2A18h]
    L_00402fa8:
        test al,2
    L_00402faa:
        mov byte ptr [ebp+1EEBh],0FFh
    L_00402fb1:
        je short L_00402fbc
    L_00402fb3:
        or eax,8
    L_00402fb6:
        mov dword ptr [ebp+2A18h],eax
    L_00402fbc:
        mov eax,dword ptr [ebp+2A18h]
    L_00402fc2:
        and eax,0FFFFFFF9h
    L_00402fc5:
        mov dword ptr [ebp+1EE8h],0FFFFFFh
    L_00402fcf:
        mov dword ptr [ebp+2A18h],eax
    L_00402fd5:
        mov esi,dword ptr [data_00491c10]
    L_00402fdb:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402fe0:
        mov eax,dword ptr [data_00491c30]
    L_00402fe5:
        mov ecx,dword ptr [eax]
    L_00402fe7:
        push ebx
    L_00402fe8:
        push 0Eh
    L_00402fea:
        push eax
    L_00402feb:
        call dword ptr [ecx+0E4h]
    L_00402ff1:
        mov esi,dword ptr [data_00491c10]
    L_00402ff7:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402ffc:
        mov eax,dword ptr [data_00491c30]
    L_00403001:
        mov edx,dword ptr [eax]
    L_00403003:
        push 8
    L_00403005:
        push 17h
    L_00403007:
        push eax
    L_00403008:
        call dword ptr [edx+0E4h]
    L_0040300e:
        cmp dword ptr [data_00492378],ebx
    L_00403014:
        je short L_00403038
    L_00403016:
        mov esi,dword ptr [data_00491c10]
    L_0040301c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00403021:
        mov eax,dword ptr [data_00491c30]
    L_00403026:
        push ebx
    L_00403027:
        push 1Ch
    L_00403029:
        mov dword ptr [data_00492378],ebx
    L_0040302f:
        mov ecx,dword ptr [eax]
    L_00403031:
        push eax
    L_00403032:
        call dword ptr [ecx+0E4h]
    L_00403038:
        mov eax,edi
    L_0040303a:
        pop edi
    L_0040303b:
        pop esi
    L_0040303c:
        pop ebx
    L_0040303d:
        pop ebp
    L_0040303e:
        ret 4
    }
}
