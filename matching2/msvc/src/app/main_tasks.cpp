#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF80..0x0041FFF0: FUN_0041ff80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ff80_0041ff80() {
    __asm {
    L_0041ff80:
        push esi
    L_0041ff81:
        mov esi,ecx
    L_0041ff83:
        mov al,byte ptr [esi+3CCh]
    L_0041ff89:
        test al,al
    L_0041ff8b:
        jns short L_0041ffa1
    L_0041ff8d:
        mov eax,dword ptr [esi+63Ch]
    L_0041ff93:
        test eax,eax
    L_0041ff95:
        jne short L_0041ffa1
    L_0041ff97:
        mov dword ptr [data_00491fb8],3
    L_0041ffa1:
        mov eax,492590h
    L_0041ffa6:
        call asm_FUN_00421e00_00421e00
    L_0041ffab:
        xor ecx,ecx
    L_0041ffad:
        call asm_FUN_0044a5f0_0044a5f0
    L_0041ffb2:
        mov eax,dword ptr [data_00491c10]
    L_0041ffb7:
        push eax
    L_0041ffb8:
        call asm_AnmPending_ServiceRetail_00447700
    L_0041ffbd:
        test eax,eax
    L_0041ffbf:
        je short L_0041ffc8
    L_0041ffc1:
        mov eax,4
    L_0041ffc6:
        pop esi
    L_0041ffc7:
        ret
    L_0041ffc8:
        mov eax,dword ptr [esi+648h]
    L_0041ffce:
        test eax,eax
    L_0041ffd0:
        je short L_0041ffe3
    L_0041ffd2:
        xor ecx,ecx
    L_0041ffd4:
        cmp eax,2
    L_0041ffd7:
        setne cl
    L_0041ffda:
        pop esi
    L_0041ffdb:
        dec ecx
    L_0041ffdc:
        and ecx,3
    L_0041ffdf:
        inc ecx
    L_0041ffe0:
        mov eax,ecx
    L_0041ffe2:
        ret
    L_0041ffe3:
        mov eax,esi
    L_0041ffe5:
        call asm_FUN_004218d0_004218d0
    L_0041ffea:
        cmp eax,1
    L_0041ffed:
        jne short L_0041ffef
    L_0041ffef:
        pop esi
    L_0041fff0:
        ret
    }
}

// 0x00420270..0x00420394: FUN_00420270
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420270_00420270() {
    __asm {
    L_00420270:
        push ebp
    L_00420271:
        push esi
    L_00420272:
        push edi
    L_00420273:
        mov esi,474DD4h
    L_00420278:
        mov edi,eax
    L_0042027a:
        call asm_Platform_StopWorker_0044c150
    L_0042027f:
        mov esi,492254h
    L_00420284:
        mov dword ptr [data_004977b4],2
    L_0042028e:
        call asm_Platform_StopWorker_0044c150
    L_00420293:
        mov eax,dword ptr [data_0049238c]
    L_00420298:
        xor ebp,ebp
    L_0042029a:
        cmp eax,ebp
    L_0042029c:
        je short L_004202ad
    L_0042029e:
        push eax
    L_0042029f:
        call asm_free_00452422
    L_004202a4:
        add esp,4
    L_004202a7:
        mov dword ptr [data_0049238c],ebp
    L_004202ad:
        push ebx
    L_004202ae:
        call asm_Recovery_ReleaseGlobalStates_004203f0
    L_004202b3:
        mov ebx,dword ptr [data_00477708]
    L_004202b9:
        call asm_Platform_ReleaseOwnedHandle_00413450
    L_004202be:
        mov esi,dword ptr [data_00491c10]
    L_004202c4:
        mov eax,dword ptr [esi+3ADA74h]
    L_004202ca:
        add esi,3ADA74h
    L_004202d0:
        cmp eax,ebp
    L_004202d2:
        pop ebx
    L_004202d3:
        je short L_004202dd
    L_004202d5:
        mov ecx,dword ptr [eax]
    L_004202d7:
        push eax
    L_004202d8:
        call dword ptr [ecx+8]
    L_004202db:
        mov dword ptr [esi],ebp
    L_004202dd:
        push ebp
    L_004202de:
        push 4
    L_004202e0:
        mov edx,46DF98h
    L_004202e5:
        mov eax,492590h
    L_004202ea:
        call asm_AnimationManager_RegisterResource_0043e460
    L_004202ef:
        call asm_FontCache_DeleteGdiObjectsRetail_00437d10
    L_004202f4:
        mov eax,dword ptr [edi+10h]
    L_004202f7:
        cmp eax,ebp
    L_004202f9:
        je short L_00420311
    L_004202fb:
        mov edx,dword ptr [eax]
    L_004202fd:
        push eax
    L_004202fe:
        call dword ptr [edx+20h]
    L_00420301:
        mov eax,dword ptr [edi+10h]
    L_00420304:
        cmp eax,ebp
    L_00420306:
        je short L_00420311
    L_00420308:
        mov ecx,dword ptr [eax]
    L_0042030a:
        push eax
    L_0042030b:
        call dword ptr [ecx+8]
    L_0042030e:
        mov dword ptr [edi+10h],ebp
    L_00420311:
        mov eax,dword ptr [edi+14h]
    L_00420314:
        cmp eax,ebp
    L_00420316:
        je short L_0042032e
    L_00420318:
        mov edx,dword ptr [eax]
    L_0042031a:
        push eax
    L_0042031b:
        call dword ptr [edx+20h]
    L_0042031e:
        mov eax,dword ptr [edi+14h]
    L_00420321:
        cmp eax,ebp
    L_00420323:
        je short L_0042032e
    L_00420325:
        mov ecx,dword ptr [eax]
    L_00420327:
        push eax
    L_00420328:
        call dword ptr [ecx+8]
    L_0042032b:
        mov dword ptr [edi+14h],ebp
    L_0042032e:
        mov eax,dword ptr [edi+0Ch]
    L_00420331:
        cmp eax,ebp
    L_00420333:
        je short L_0042033e
    L_00420335:
        mov edx,dword ptr [eax]
    L_00420337:
        push eax
    L_00420338:
        call dword ptr [edx+8]
    L_0042033b:
        mov dword ptr [edi+0Ch],ebp
    L_0042033e:
        mov eax,dword ptr [data_00491d44]
    L_00420343:
        cmp eax,ebp
    L_00420345:
        je short L_00420385
    L_00420347:
        lea esi,[eax+4]
    L_0042034a:
        mov edi,eax
    L_0042034c:
        mov eax,dword ptr [esi]
    L_0042034e:
        cmp eax,ebp
    L_00420350:
        je short L_00420359
    L_00420352:
        push eax
    L_00420353:
        call dword ptr [data_00466288]
    L_00420359:
        mov eax,dword ptr [edi+8]
    L_0042035c:
        push eax
    L_0042035d:
        call dword ptr [data_00466274]
    L_00420363:
        mov dword ptr [esi],ebp
    L_00420365:
        mov esi,dword ptr [data_00491d44]
    L_0042036b:
        cmp esi,ebp
    L_0042036d:
        mov edi,esi
    L_0042036f:
        je short L_0042037f
    L_00420371:
        call asm_TimerWin32_Release_004203c0
    L_00420376:
        push edi
    L_00420377:
        call asm_free_004524a1
    L_0042037c:
        add esp,4
    L_0042037f:
        mov dword ptr [data_00491d44],ebp
    L_00420385:
        mov esi,497990h
    L_0042038a:
        call asm_DatArchive_Close_00434d10
    L_0042038f:
        pop edi
    L_00420390:
        pop esi
    L_00420391:
        xor eax,eax
    L_00420393:
        pop ebp
    L_00420394:
        ret
    }
}

// 0x00420470..0x0042053B: FUN_00420470
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420470_00420470() {
    __asm {
    L_00420470:
        push ebx
    L_00420471:
        push ebp
    L_00420472:
        push esi
    L_00420473:
        push edi
    L_00420474:
        xor eax,eax
    L_00420476:
        push 41FF80h
    L_0042047b:
        mov dword ptr [data_00491fb4],0FFFFFFFEh
    L_00420485:
        mov dword ptr [data_00491fb8],eax
    L_0042048a:
        mov dword ptr [data_00491fc0],eax
    L_0042048f:
        call asm_SchedulerCallback_Create_00449ed0
    L_00420494:
        mov esi,dword ptr [eax+4]
    L_00420497:
        mov ecx,dword ptr [data_00491be4]
    L_0042049d:
        mov ebx,2
    L_004204a2:
        or esi,ebx
    L_004204a4:
        mov dword ptr [eax+4],esi
    L_004204a7:
        mov ebp,491C28h
    L_004204ac:
        push ecx
    L_004204ad:
        mov edi,1
    L_004204b2:
        mov esi,eax
    L_004204b4:
        mov dword ptr [eax+20h],ebp
    L_004204b7:
        mov dword ptr [eax+0Ch],4201B0h
    L_004204be:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004204c3:
        test eax,eax
    L_004204c5:
        jne short L_00420537
    L_004204c7:
        push 420000h
    L_004204cc:
        call asm_SchedulerCallback_Create_00449ed0
    L_004204d1:
        mov edi,dword ptr [eax+4]
    L_004204d4:
        mov edx,dword ptr [data_00491be4]
    L_004204da:
        or edi,ebx
    L_004204dc:
        mov dword ptr [eax+4],edi
    L_004204df:
        push edx
    L_004204e0:
        mov edi,1
    L_004204e5:
        mov esi,eax
    L_004204e7:
        mov dword ptr [eax+20h],ebp
    L_004204ea:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004204ef:
        push 4200C0h
    L_004204f4:
        call asm_SchedulerCallback_Create_00449ed0
    L_004204f9:
        or dword ptr [eax+4],ebx
    L_004204fc:
        mov ecx,dword ptr [data_00491be4]
    L_00420502:
        push ecx
    L_00420503:
        mov edi,28h
    L_00420508:
        mov esi,eax
    L_0042050a:
        mov dword ptr [eax+20h],ebp
    L_0042050d:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00420512:
        push 4200D0h
    L_00420517:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042051c:
        or dword ptr [eax+4],ebx
    L_0042051f:
        mov edx,dword ptr [data_00491be4]
    L_00420525:
        push edx
    L_00420526:
        mov edi,32h
    L_0042052b:
        mov esi,eax
    L_0042052d:
        mov dword ptr [eax+20h],ebp
    L_00420530:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00420535:
        xor eax,eax
    L_00420537:
        pop edi
    L_00420538:
        pop esi
    L_00420539:
        pop ebp
    L_0042053a:
        pop ebx
    L_0042053b:
        ret
    }
}

// 0x00420670..0x00420867: FUN_00420670
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420670_00420670() {
    __asm {
    L_00420670:
        sub esp,0Ch
    L_00420673:
        push ebx
    L_00420674:
        push ebp
    L_00420675:
        push edi
    L_00420676:
        mov edi,eax
    L_00420678:
        mov eax,dword ptr [esi+50Ch]
    L_0042067e:
        xor ebp,ebp
    L_00420680:
        cmp eax,ebp
    L_00420682:
        je short L_0042069c
    L_00420684:
        mov ebx,dword ptr [data_004660ac]
    L_0042068a:
        lea ebx,[ebx+force_disp32_zero]
    L_00420690:
        push 0Ah
    L_00420692:
        call ebx
    L_00420694:
        cmp dword ptr [esi+50Ch],ebp
    L_0042069a:
        jne short L_00420690
    L_0042069c:
        mov eax,dword ptr [esi+8]
    L_0042069f:
        lea edx,[esp+0Ch]
    L_004206a3:
        push edx
    L_004206a4:
        push ebp
    L_004206a5:
        push ebp
    L_004206a6:
        push ebp
    L_004206a7:
        mov dword ptr [esp+1Ch],ebp
    L_004206ab:
        mov ecx,dword ptr [eax]
    L_004206ad:
        push eax
    L_004206ae:
        call dword ptr [ecx+48h]
    L_004206b1:
        lea eax,[esi+510h]
    L_004206b7:
        xor ecx,ecx
    L_004206b9:
        mov edx,eax
    L_004206bb:
        mov dword ptr [edx],ecx
    L_004206bd:
        mov dword ptr [edx+4],ecx
    L_004206c0:
        mov dword ptr [edx+8],ecx
    L_004206c3:
        mov word ptr [edx+0Ch],cx
    L_004206c7:
        mov word ptr [eax],4D42h
    L_004206cc:
        mov eax,36h
    L_004206d1:
        mov ecx,esi
    L_004206d3:
        sub ecx,edi
    L_004206d5:
        mov dword ptr [esi+51Ah],eax
    L_004206db:
        mov dword ptr [esi+512h],eax
    L_004206e1:
        mov eax,edi
    L_004206e3:
        lea edx,[ecx+528h]
    L_004206e9:
        lea esp,[esp+force_disp32_zero]
    L_004206f0:
        mov cl,byte ptr [eax]
    L_004206f2:
        mov byte ptr [edx+eax],cl
    L_004206f5:
        inc eax
    L_004206f6:
        test cl,cl
    L_004206f8:
        jne short L_004206f0
    L_004206fa:
        mov eax,dword ptr [esi+0ECh]
    L_00420700:
        sub eax,16h
    L_00420703:
        je short L_00420738
    L_00420705:
        dec eax
    L_00420706:
        mov ecx,474F70h
    L_0042070b:
        je short L_00420726
    L_0042070d:
        push 46DEB0h
    L_00420712:
        call asm_TextLog_Append_0044b810
    L_00420717:
        add esp,4
    L_0042071a:
        pop edi
    L_0042071b:
        pop ebp
    L_0042071c:
        mov eax,1
    L_00420721:
        pop ebx
    L_00420722:
        add esp,0Ch
    L_00420725:
        ret
    L_00420726:
        push 46DF38h
    L_0042072b:
        call asm_TextLog_Append_0044b810
    L_00420730:
        add esp,4
    L_00420733:
        jmp asm_target_00420851
    L_00420738:
        push 2Ch
    L_0042073a:
        call asm_malloc_00452706
    L_0042073f:
        mov edi,eax
    L_00420741:
        add esp,4
    L_00420744:
        cmp edi,ebp
    L_00420746:
        mov dword ptr [esi+520h],edi
    L_0042074c:
        jne short L_00420765
    L_0042074e:
        push 46DEF0h
    L_00420753:
        mov ecx,474F70h
    L_00420758:
        call asm_TextLog_Append_0044b810
    L_0042075d:
        add esp,4
    L_00420760:
        jmp asm_target_00420851
    L_00420765:
        xor eax,eax
    L_00420767:
        mov ecx,0Bh
    L_0042076c:
        push 0E1000h
    L_00420771:
        rep stosd
    L_00420773:
        call asm_malloc_00452706
    L_00420778:
        add esp,4
    L_0042077b:
        cmp eax,ebp
    L_0042077d:
        mov dword ptr [esi+524h],eax
    L_00420783:
        je short L_0042074e
    L_00420785:
        add dword ptr [esi+512h],0E1000h
    L_0042078f:
        mov edx,dword ptr [esi+520h]
    L_00420795:
        mov word ptr [edx+0Eh],18h
    L_0042079b:
        mov eax,dword ptr [esi+520h]
    L_004207a1:
        mov dword ptr [eax],28h
    L_004207a7:
        mov ecx,dword ptr [esi+520h]
    L_004207ad:
        mov dword ptr [ecx+4],280h
    L_004207b4:
        mov edx,dword ptr [esi+520h]
    L_004207ba:
        mov dword ptr [edx+8],1E0h
    L_004207c1:
        mov eax,dword ptr [esi+520h]
    L_004207c7:
        mov word ptr [eax+0Ch],1
    L_004207cd:
        mov ecx,dword ptr [esi+520h]
    L_004207d3:
        push ebp
    L_004207d4:
        mov dword ptr [ecx+10h],ebp
    L_004207d7:
        mov eax,dword ptr [esp+10h]
    L_004207db:
        mov edx,dword ptr [eax]
    L_004207dd:
        push ebp
    L_004207de:
        lea ecx,[esp+18h]
    L_004207e2:
        push ecx
    L_004207e3:
        push eax
    L_004207e4:
        call dword ptr [edx+34h]
    L_004207e7:
        mov ebp,1DFh
    L_004207ec:
        xor edx,edx
    L_004207ee:
        mov edi,edi
    L_004207f0:
        mov eax,dword ptr [esp+10h]
    L_004207f4:
        mov ecx,dword ptr [esi+524h]
    L_004207fa:
        imul eax,ebp
    L_004207fd:
        mov edi,dword ptr [esp+14h]
    L_00420801:
        add ecx,edx
    L_00420803:
        add eax,edi
    L_00420805:
        mov edi,280h
    L_0042080a:
        lea ebx,[ebx+force_disp32_zero]
    L_00420810:
        mov bx,word ptr [eax]
    L_00420813:
        mov word ptr [ecx],bx
    L_00420816:
        mov bl,byte ptr [eax+2]
    L_00420819:
        mov byte ptr [ecx+2],bl
    L_0042081c:
        add eax,4
    L_0042081f:
        add ecx,3
    L_00420822:
        dec edi
    L_00420823:
        jne short L_00420810
    L_00420825:
        dec ebp
    L_00420826:
        add edx,780h
    L_0042082c:
        cmp ebp,0FFFFFFFFh
    L_0042082f:
        jg short L_004207f0
    L_00420831:
        mov eax,dword ptr [esp+0Ch]
    L_00420835:
        mov edx,dword ptr [eax]
    L_00420837:
        push eax
    L_00420838:
        call dword ptr [edx+38h]
    L_0042083b:
        push 0
    L_0042083d:
        push 0
    L_0042083f:
        push 420540h
    L_00420844:
        call asm_beginthread_00452eec
    L_00420849:
        add esp,0Ch
    L_0042084c:
        mov dword ptr [data_00492134],eax
    L_00420851:
        mov eax,dword ptr [esp+0Ch]
    L_00420855:
        test eax,eax
    L_00420857:
        je short L_0042085f
    L_00420859:
        mov ecx,dword ptr [eax]
    L_0042085b:
        push eax
    L_0042085c:
        call dword ptr [ecx+8]
    L_0042085f:
        pop edi
    L_00420860:
        pop ebp
    L_00420861:
        xor eax,eax
    L_00420863:
        pop ebx
    L_00420864:
        add esp,0Ch
    L_00420867:
        ret
    }
}

// 0x00420870..0x00420A85: FUN_00420870
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420870_00420870() {
    __asm {
    L_00420870:
        push ebp
    L_00420871:
        mov ebp,dword ptr [esp+8]
    L_00420875:
        push edi
    L_00420876:
        mov edx,491D48h
    L_0042087b:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00420880:
        push 1
    L_00420882:
        lea eax,[esp+10h]
    L_00420886:
        push eax
    L_00420887:
        mov eax,ebx
    L_00420889:
        call asm_FUN_0044b360_0044b360
    L_0042088e:
        test eax,eax
    L_00420890:
        jne short L_0042089c
    L_00420892:
        push 46DE7Ch
    L_00420897:
        jmp asm_target_00420942
    L_0042089c:
        push esi
    L_0042089d:
        mov esi,eax
    L_0042089f:
        mov ecx,0Dh
    L_004208a4:
        mov edi,491D48h
    L_004208a9:
        push eax
    L_004208aa:
        rep movsd
    L_004208ac:
        call asm_free_00452422
    L_004208b1:
        mov al,byte ptr [data_00491d62]
    L_004208b6:
        add esp,4
    L_004208b9:
        cmp al,2
    L_004208bb:
        pop esi
    L_004208bc:
        jae short L_0042093d
    L_004208be:
        mov cl,byte ptr [data_00491d63]
    L_004208c4:
        mov al,3
    L_004208c6:
        cmp cl,al
    L_004208c8:
        jae short L_0042093d
    L_004208ca:
        cmp byte ptr [data_00491d64],2
    L_004208d1:
        jae short L_0042093d
    L_004208d3:
        cmp byte ptr [data_00491d65],2
    L_004208da:
        jae short L_0042093d
    L_004208dc:
        cmp byte ptr [data_00491d66],al
    L_004208e2:
        jae short L_0042093d
    L_004208e4:
        cmp byte ptr [data_00491d67],al
    L_004208ea:
        jae short L_0042093d
    L_004208ec:
        cmp dword ptr [data_00491d48],100003h
    L_004208f6:
        jne short L_0042093d
    L_004208f8:
        cmp dword ptr [esp+0Ch],34h
    L_004208fd:
        jne short L_0042093d
    L_004208ff:
        mov ecx,dword ptr [data_00491d4c]
    L_00420905:
        mov edx,dword ptr [data_00491d50]
    L_0042090b:
        mov eax,dword ptr [data_00491d54]
    L_00420910:
        mov dword ptr [data_00474e88],ecx
    L_00420916:
        mov ecx,dword ptr [data_00491d58]
    L_0042091c:
        mov dword ptr [data_00474e8c],edx
    L_00420922:
        mov dx,word ptr [data_00491d5c]
    L_00420929:
        mov dword ptr [data_00474e90],eax
    L_0042092e:
        mov dword ptr [data_00474e94],ecx
    L_00420934:
        mov word ptr [data_00474e98],dx
    L_0042093b:
        jmp short L_00420959
    L_0042093d:
        push 46DE48h
    L_00420942:
        mov ecx,474F70h
    L_00420947:
        call asm_TextLog_Append_0044b810
    L_0042094c:
        add esp,4
    L_0042094f:
        mov edx,491D48h
    L_00420954:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00420959:
        test byte ptr [ebp+150h],4
    L_00420960:
        mov dword ptr [ebp+3B4h],0
    L_0042096a:
        je short L_0042097e
    L_0042096c:
        push 46DE2Ch
    L_00420971:
        mov ecx,474F70h
    L_00420976:
        call asm_TextLog_Append_0044b810
    L_0042097b:
        add esp,4
    L_0042097e:
        test byte ptr [ebp+150h],1
    L_00420985:
        je short L_00420999
    L_00420987:
        push 46DE04h
    L_0042098c:
        mov ecx,474F70h
    L_00420991:
        call asm_TextLog_Append_0044b810
    L_00420996:
        add esp,4
    L_00420999:
        mov al,byte ptr [ebp+13Dh]
    L_0042099f:
        test al,al
    L_004209a1:
        je short L_004209b5
    L_004209a3:
        push 46DDE4h
    L_004209a8:
        mov ecx,474F70h
    L_004209ad:
        call asm_TextLog_Append_0044b810
    L_004209b2:
        add esp,4
    L_004209b5:
        test byte ptr [ebp+150h],2
    L_004209bc:
        je short L_004209d0
    L_004209be:
        push 46DDBCh
    L_004209c3:
        mov ecx,474F70h
    L_004209c8:
        call asm_TextLog_Append_0044b810
    L_004209cd:
        add esp,4
    L_004209d0:
        test byte ptr [ebp+150h],8
    L_004209d7:
        je short L_004209eb
    L_004209d9:
        push 46DD84h
    L_004209de:
        mov ecx,474F70h
    L_004209e3:
        call asm_TextLog_Append_0044b810
    L_004209e8:
        add esp,4
    L_004209eb:
        test byte ptr [ebp+150h],10h
    L_004209f2:
        je short L_00420a06
    L_004209f4:
        push 46DD64h
    L_004209f9:
        mov ecx,474F70h
    L_004209fe:
        call asm_TextLog_Append_0044b810
    L_00420a03:
        add esp,4
    L_00420a06:
        test byte ptr [ebp+150h],20h
    L_00420a0d:
        je short L_00420a2b
    L_00420a0f:
        push 46DD4Ch
    L_00420a14:
        mov ecx,474F70h
    L_00420a19:
        call asm_TextLog_Append_0044b810
    L_00420a1e:
        add esp,4
    L_00420a21:
        mov dword ptr [data_00491fdc],1
    L_00420a2b:
        test byte ptr [ebp+150h],40h
    L_00420a32:
        je short L_00420a46
    L_00420a34:
        push 46DD28h
    L_00420a39:
        mov ecx,474F70h
    L_00420a3e:
        call asm_TextLog_Append_0044b810
    L_00420a43:
        add esp,4
    L_00420a46:
        push 491D48h
    L_00420a4b:
        push ebx
    L_00420a4c:
        mov edi,34h
    L_00420a51:
        call asm_File_WriteWholeFile_0044b540
    L_00420a56:
        test eax,eax
    L_00420a58:
        je short L_00420a7f
    L_00420a5a:
        push ebx
    L_00420a5b:
        push 46DD08h
    L_00420a60:
        mov edi,474F70h
    L_00420a65:
        call asm_TextLog_AppendLine_0044b8e0
    L_00420a6a:
        push 46DCB0h
    L_00420a6f:
        call asm_TextLog_AppendLine_0044b8e0
    L_00420a74:
        add esp,0Ch
    L_00420a77:
        pop edi
    L_00420a78:
        or eax,0FFFFFFFFh
    L_00420a7b:
        pop ebp
    L_00420a7c:
        ret 4
    L_00420a7f:
        pop edi
    L_00420a80:
        xor eax,eax
    L_00420a82:
        pop ebp
    L_00420a83:
        ret 4
    }
}
