#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401000..0x004010FA: GameThread_ConstructOverlay
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_Construct_00401000() {
    __asm {
    L_00401000:
        mov dword ptr [esi],46CB14h
    L_00401006:
        mov eax,dword ptr [esi+80h]
    L_0040100c:
        lea edx,[esi+14h]
    L_0040100f:
        push ebx
    L_00401010:
        mov ebx,0FFFFFFFEh
    L_00401015:
        push edi
    L_00401016:
        and eax,ebx
    L_00401018:
        mov dword ptr [edx+6Ch],eax
    L_0040101b:
        and dword ptr [edx+0B0h],ebx
    L_00401021:
        and dword ptr [edx+0FCh],ebx
    L_00401027:
        and dword ptr [edx+128h],ebx
    L_0040102d:
        and dword ptr [edx+174h],ebx
    L_00401033:
        and dword ptr [edx+1B0h],ebx
    L_00401039:
        and dword ptr [edx+1FCh],ebx
    L_0040103f:
        and dword ptr [edx+228h],ebx
    L_00401045:
        and dword ptr [edx+378h],ebx
    L_0040104b:
        xor eax,eax
    L_0040104d:
        mov edi,edx
    L_0040104f:
        mov ecx,0EBh
    L_00401054:
        rep stosd
    L_00401056:
        mov word ptr [edx+384h],0FFFFh
    L_0040105f:
        mov eax,dword ptr [esi+42Ch]
    L_00401065:
        lea edx,[esi+3C0h]
    L_0040106b:
        and eax,ebx
    L_0040106d:
        mov dword ptr [edx+6Ch],eax
    L_00401070:
        and dword ptr [edx+0B0h],ebx
    L_00401076:
        and dword ptr [edx+0FCh],ebx
    L_0040107c:
        and dword ptr [edx+128h],ebx
    L_00401082:
        and dword ptr [edx+174h],ebx
    L_00401088:
        and dword ptr [edx+1B0h],ebx
    L_0040108e:
        and dword ptr [edx+1FCh],ebx
    L_00401094:
        and dword ptr [edx+228h],ebx
    L_0040109a:
        and dword ptr [edx+378h],ebx
    L_004010a0:
        xor eax,eax
    L_004010a2:
        mov ecx,0EBh
    L_004010a7:
        mov edi,edx
    L_004010a9:
        rep stosd
    L_004010ab:
        mov word ptr [edx+384h],0FFFFh
    L_004010b4:
        mov ecx,226Bh
    L_004010b9:
        mov edi,esi
    L_004010bb:
        rep stosd
    L_004010bd:
        or dword ptr [esi+4],2
    L_004010c1:
        mov eax,3F800000h
    L_004010c6:
        mov dword ptr [data_004776e0],esi
    L_004010cc:
        mov dword ptr [esi+8974h],0FFFFFFFFh
    L_004010d6:
        mov dword ptr [esi+8978h],eax
    L_004010dc:
        mov dword ptr [esi+897Ch],eax
    L_004010e2:
        pop edi
    L_004010e3:
        mov dword ptr [esi+8984h],0
    L_004010ed:
        mov dword ptr [esi+898Ch],9
    L_004010f7:
        mov eax,esi
    L_004010f9:
        pop ebx
    L_004010fa:
        ret
    }
}

// 0x00401110..0x00401259: LoadGameThreadResources
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_LoadGameThreadResources_00401110() {
    __asm {
    L_00401110:
        mov edx,dword ptr [data_00491c10]
    L_00401116:
        push ebx
    L_00401117:
        push 46CB80h
    L_0040111c:
        mov ecx,2
    L_00401121:
        mov ebx,eax
    L_00401123:
        call asm_Recovery_LoadCachedResource_00447280
    L_00401128:
        test eax,eax
    L_0040112a:
        mov dword ptr [ebx+8994h],eax
    L_00401130:
        je short L_0040116d
    L_00401132:
        mov edx,dword ptr [data_00491c10]
    L_00401138:
        push 46CB5Ch
    L_0040113d:
        xor ecx,ecx
    L_0040113f:
        call asm_Recovery_LoadCachedResource_00447280
    L_00401144:
        test eax,eax
    L_00401146:
        mov dword ptr [ebx+899Ch],eax
    L_0040114c:
        je short L_0040116d
    L_0040114e:
        mov edx,dword ptr [data_00491c10]
    L_00401154:
        push 46CB50h
    L_00401159:
        mov ecx,3
    L_0040115e:
        call asm_Recovery_LoadCachedResource_00447280
    L_00401163:
        test eax,eax
    L_00401165:
        mov dword ptr [ebx+8998h],eax
    L_0040116b:
        jne short L_00401184
    L_0040116d:
        push 46CB68h
    L_00401172:
        mov ecx,474F70h
    L_00401177:
        call asm_TextLog_Append_0044b810
    L_0040117c:
        add esp,4
    L_0040117f:
        or eax,0FFFFFFFFh
    L_00401182:
        pop ebx
    L_00401183:
        ret
    L_00401184:
        push esi
    L_00401185:
        push edi
    L_00401186:
        push 4014F0h
    L_0040118b:
        call asm_SchedulerCallback_Create_00449ed0
    L_00401190:
        mov esi,eax
    L_00401192:
        mov edi,dword ptr [esi+4]
    L_00401195:
        mov eax,dword ptr [data_00491be4]
    L_0040119a:
        and edi,0FFFFFFFDh
    L_0040119d:
        mov dword ptr [esi+4],edi
    L_004011a0:
        push eax
    L_004011a1:
        mov edi,4
    L_004011a6:
        mov dword ptr [esi+20h],ebx
    L_004011a9:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004011ae:
        push 401510h
    L_004011b3:
        mov dword ptr [ebx+0Ch],esi
    L_004011b6:
        call asm_SchedulerCallback_Create_00449ed0
    L_004011bb:
        mov ecx,dword ptr [data_00491be4]
    L_004011c1:
        mov esi,eax
    L_004011c3:
        mov eax,dword ptr [esi+4]
    L_004011c6:
        and eax,0FFFFFFFDh
    L_004011c9:
        push ecx
    L_004011ca:
        mov edi,30h
    L_004011cf:
        mov dword ptr [esi+20h],ebx
    L_004011d2:
        mov dword ptr [esi+4],eax
    L_004011d5:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004011da:
        push 401520h
    L_004011df:
        mov dword ptr [ebx+10h],esi
    L_004011e2:
        call asm_SchedulerCallback_Create_00449ed0
    L_004011e7:
        mov edx,dword ptr [data_00491be4]
    L_004011ed:
        mov esi,eax
    L_004011ef:
        mov ecx,dword ptr [esi+4]
    L_004011f2:
        and ecx,0FFFFFFFDh
    L_004011f5:
        push edx
    L_004011f6:
        mov edi,26h
    L_004011fb:
        mov dword ptr [esi+20h],ebx
    L_004011fe:
        mov dword ptr [esi+4],ecx
    L_00401201:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00401206:
        mov edi,dword ptr [ebx+8994h]
    L_0040120c:
        mov dword ptr [ebx+89A8h],esi
    L_00401212:
        lea esi,[ebx+14h]
    L_00401215:
        mov edx,esi
    L_00401217:
        call asm_InitializeEntity_00401de0
    L_0040121c:
        xor edx,edx
    L_0040121e:
        mov eax,esi
    L_00401220:
        mov ecx,edi
    L_00401222:
        mov dword ptr [esi+308h],edi
    L_00401228:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0040122d:
        lea esi,[ebx+3C0h]
    L_00401233:
        mov ebx,dword ptr [ebx+8994h]
    L_00401239:
        mov edx,esi
    L_0040123b:
        call asm_InitializeEntity_00401de0
    L_00401240:
        mov edx,62h
    L_00401245:
        mov eax,esi
    L_00401247:
        mov ecx,ebx
    L_00401249:
        mov dword ptr [esi+308h],ebx
    L_0040124f:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00401254:
        pop edi
    L_00401255:
        pop esi
    L_00401256:
        xor eax,eax
    L_00401258:
        pop ebx
    L_00401259:
        ret
    }
}

// 0x00401260..0x00401432: DestroyGameThread
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DestroyGameThread_00401260() {
    __asm {
    L_00401260:
        push 0FFFFFFFFh
    L_00401262:
        push 4652F9h
    L_00401267:
        mov eax,dword ptr fs:[0]
    L_0040126d:
        push eax
    L_0040126e:
        mov dword ptr fs:[0],esp
    L_00401275:
        push ecx
    L_00401276:
        push ebx
    L_00401277:
        push ebp
    L_00401278:
        mov ebp,dword ptr [esp+1Ch]
    L_0040127c:
        push esi
    L_0040127d:
        push edi
    L_0040127e:
        mov dword ptr [ebp],46CB14h
    L_00401285:
        mov dword ptr [esp+1Ch],1
    L_0040128d:
        mov esi,dword ptr [ebp+0Ch]
    L_00401290:
        test esi,esi
    L_00401292:
        mov eax,dword ptr [data_00491be4]
    L_00401297:
        mov edi,dword ptr [data_004660b0]
    L_0040129d:
        mov ebx,dword ptr [data_004660b4]
    L_004012a3:
        mov dword ptr [esp+10h],eax
    L_004012a7:
        je short L_004012ce
    L_004012a9:
        push 492274h
    L_004012ae:
        call edi
    L_004012b0:
        inc byte ptr [data_0049231c]
    L_004012b6:
        mov edx,dword ptr [esp+10h]
    L_004012ba:
        mov ecx,esi
    L_004012bc:
        call asm_Scheduler_Remove_00449f60
    L_004012c1:
        push 492274h
    L_004012c6:
        call ebx
    L_004012c8:
        dec byte ptr [data_0049231c]
    L_004012ce:
        mov esi,dword ptr [ebp+10h]
    L_004012d1:
        test esi,esi
    L_004012d3:
        mov ecx,dword ptr [data_00491be4]
    L_004012d9:
        mov dword ptr [esp+10h],ecx
    L_004012dd:
        je short L_00401304
    L_004012df:
        push 492274h
    L_004012e4:
        call edi
    L_004012e6:
        inc byte ptr [data_0049231c]
    L_004012ec:
        mov edx,dword ptr [esp+10h]
    L_004012f0:
        mov ecx,esi
    L_004012f2:
        call asm_Scheduler_Remove_00449f60
    L_004012f7:
        push 492274h
    L_004012fc:
        call ebx
    L_004012fe:
        dec byte ptr [data_0049231c]
    L_00401304:
        mov esi,dword ptr [ebp+89A8h]
    L_0040130a:
        test esi,esi
    L_0040130c:
        mov edx,dword ptr [data_00491be4]
    L_00401312:
        mov dword ptr [esp+10h],edx
    L_00401316:
        je short L_0040133d
    L_00401318:
        push 492274h
    L_0040131d:
        call edi
    L_0040131f:
        inc byte ptr [data_0049231c]
    L_00401325:
        mov edx,dword ptr [esp+10h]
    L_00401329:
        mov ecx,esi
    L_0040132b:
        call asm_Scheduler_Remove_00449f60
    L_00401330:
        push 492274h
    L_00401335:
        call ebx
    L_00401337:
        dec byte ptr [data_0049231c]
    L_0040133d:
        mov esi,dword ptr [data_00491c10]
    L_00401343:
        mov edi,dword ptr [esi+3AD074h]
    L_00401349:
        add esi,3AD074h
    L_0040134f:
        test edi,edi
    L_00401351:
        je short L_00401369
    L_00401353:
        call asm_FUN_00447810_00447810
    L_00401358:
        mov eax,dword ptr [esi]
    L_0040135a:
        push eax
    L_0040135b:
        call asm_free_004524a1
    L_00401360:
        add esp,4
    L_00401363:
        mov dword ptr [esi],0
    L_00401369:
        mov esi,dword ptr [data_00491c10]
    L_0040136f:
        mov edi,dword ptr [esi+3AD06Ch]
    L_00401375:
        add esi,3AD06Ch
    L_0040137b:
        test edi,edi
    L_0040137d:
        je short L_00401395
    L_0040137f:
        call asm_FUN_00447810_00447810
    L_00401384:
        mov ecx,dword ptr [esi]
    L_00401386:
        push ecx
    L_00401387:
        call asm_free_004524a1
    L_0040138c:
        add esp,4
    L_0040138f:
        mov dword ptr [esi],0
    L_00401395:
        mov esi,dword ptr [data_00491c10]
    L_0040139b:
        mov edi,dword ptr [esi+3AD078h]
    L_004013a1:
        add esi,3AD078h
    L_004013a7:
        test edi,edi
    L_004013a9:
        je short L_004013c1
    L_004013ab:
        call asm_FUN_00447810_00447810
    L_004013b0:
        mov edx,dword ptr [esi]
    L_004013b2:
        push edx
    L_004013b3:
        call asm_free_004524a1
    L_004013b8:
        add esp,4
    L_004013bb:
        mov dword ptr [esi],0
    L_004013c1:
        mov eax,dword ptr [ebp+718h]
    L_004013c7:
        test eax,eax
    L_004013c9:
        mov dword ptr [data_004776e0],0
    L_004013d3:
        je short L_004013de
    L_004013d5:
        push eax
    L_004013d6:
        call asm_free_00452422
    L_004013db:
        add esp,4
    L_004013de:
        xor ecx,ecx
    L_004013e0:
        mov dword ptr [ebp+718h],ecx
    L_004013e6:
        mov eax,dword ptr [ebp+36Ch]
    L_004013ec:
        cmp eax,ecx
    L_004013ee:
        je short L_00401418
    L_004013f0:
        push eax
    L_004013f1:
        call asm_free_00452422
    L_004013f6:
        add esp,4
    L_004013f9:
        pop edi
    L_004013fa:
        pop esi
    L_004013fb:
        mov dword ptr [ebp+36Ch],0
    L_00401405:
        pop ebp
    L_00401406:
        pop ebx
    L_00401407:
        mov ecx,dword ptr [esp+4]
    L_0040140b:
        mov dword ptr fs:[0],ecx
    L_00401412:
        add esp,10h
    L_00401415:
        ret 4
    L_00401418:
        pop edi
    L_00401419:
        mov dword ptr [ebp+36Ch],ecx
    L_0040141f:
        mov ecx,dword ptr [esp+10h]
    L_00401423:
        pop esi
    L_00401424:
        pop ebp
    L_00401425:
        pop ebx
    L_00401426:
        mov dword ptr fs:[0],ecx
    L_0040142d:
        add esp,10h
    L_00401430:
        ret 4
    }
}

// 0x00401440..0x00401484: CreateGameThread
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CreateGameThread_00401440() {
    __asm {
    L_00401440:
        push esi
    L_00401441:
        push 89ACh
    L_00401446:
        call asm_operator_new_00452493
    L_0040144b:
        add esp,4
    L_0040144e:
        test eax,eax
    L_00401450:
        je short L_0040145d
    L_00401452:
        mov esi,eax
    L_00401454:
        call asm_GameThread_Construct_00401000
    L_00401459:
        mov esi,eax
    L_0040145b:
        jmp short L_0040145f
    L_0040145d:
        xor esi,esi
    L_0040145f:
        mov eax,esi
    L_00401461:
        call asm_LoadGameThreadResources_00401110
    L_00401466:
        test eax,eax
    L_00401468:
        je short L_00401481
    L_0040146a:
        test esi,esi
    L_0040146c:
        je short L_0040147d
    L_0040146e:
        push esi
    L_0040146f:
        call asm_DestroyGameThread_00401260
    L_00401474:
        push esi
    L_00401475:
        call asm_free_004524a1
    L_0040147a:
        add esp,4
    L_0040147d:
        xor eax,eax
    L_0040147f:
        pop esi
    L_00401480:
        ret
    L_00401481:
        mov eax,esi
    L_00401483:
        pop esi
    L_00401484:
        ret
    }
}

// 0x00401760..0x00401A41: FUN_00401760
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401760_00401760() {
    __asm {
    L_00401760:
        sub esp,10h
    L_00401763:
        push ebx
    L_00401764:
        push ebp
    L_00401765:
        mov ebp,dword ptr [esp+1Ch]
    L_00401769:
        mov eax,dword ptr [ebp+370h]
    L_0040176f:
        and eax,0FFD7FFFFh
    L_00401774:
        or eax,140001h
    L_00401779:
        mov dword ptr [ebp+370h],eax
    L_0040177f:
        mov eax,dword ptr [ebp+896Ch]
    L_00401785:
        test eax,eax
    L_00401787:
        push esi
    L_00401788:
        push edi
    L_00401789:
        mov dword ptr [esp+10h],1
    L_00401791:
        lea ebx,[ebp+76Ch]
    L_00401797:
        mov dword ptr [esp+1Ch],0
    L_0040179f:
        jle asm_target_004019e9
    L_004017a5:
        lea eax,[ebx+40h]
    L_004017a8:
        mov ecx,eax
    L_004017aa:
        mov edx,dword ptr [ecx]
    L_004017ac:
        lea eax,[ebp+348h]
    L_004017b2:
        mov dword ptr [eax],edx
    L_004017b4:
        mov edx,dword ptr [ecx+4]
    L_004017b7:
        mov dword ptr [eax+4],edx
    L_004017ba:
        mov ecx,dword ptr [ecx+8]
    L_004017bd:
        mov dword ptr [eax+8],ecx
    L_004017c0:
        fld dword ptr [ebx+54h]
    L_004017c3:
        mov ecx,dword ptr [ebp+370h]
    L_004017c9:
        mov edx,dword ptr [ebx+50h]
    L_004017cc:
        fstp dword ptr [ebp+54h]
    L_004017cf:
        or ecx,8
    L_004017d2:
        mov dword ptr [ebp+50h],edx
    L_004017d5:
        mov dword ptr [ebp+370h],ecx
    L_004017db:
        cmp dword ptr [ebx+60h],1
    L_004017df:
        mov edi,ebx
    L_004017e1:
        mov dword ptr [esp+14h],edi
    L_004017e5:
        jne short L_004017f9
    L_004017e7:
        mov dword ptr [esp+24h],40E00000h
    L_004017ef:
        mov dword ptr [esp+18h],41100000h
    L_004017f7:
        jmp short L_0040180e
    L_004017f9:
        fild dword ptr [ebp+898Ch]
    L_004017ff:
        mov dword ptr [esp+18h],41600000h
    L_00401807:
        fmul dword ptr [ebx+50h]
    L_0040180a:
        fstp dword ptr [esp+24h]
    L_0040180e:
        mov eax,dword ptr [ebx+5Ch]
    L_00401811:
        cmp dword ptr [esp+10h],eax
    L_00401815:
        je asm_target_004018a0
    L_0040181b:
        mov esi,dword ptr [data_00491c10]
    L_00401821:
        mov edi,eax
    L_00401823:
        mov dword ptr [esp+10h],edi
    L_00401827:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0040182c:
        test edi,edi
    L_0040182e:
        je short L_00401867
    L_00401830:
        mov edi,491D7Ch
    L_00401835:
        mov dword ptr [data_00491fac],edi
    L_0040183b:
        call asm_FUN_004215a0_004215a0
    L_00401840:
        mov edx,dword ptr [data_00491fac]
    L_00401846:
        mov eax,dword ptr [data_00491c30]
    L_0040184b:
        mov ecx,dword ptr [eax]
    L_0040184d:
        add edx,0CCh
    L_00401853:
        push edx
    L_00401854:
        push eax
    L_00401855:
        call dword ptr [ecx+0BCh]
    L_0040185b:
        mov dword ptr [data_00491fb0],0
    L_00401865:
        jmp short L_0040189c
    L_00401867:
        mov edi,491E94h
    L_0040186c:
        mov dword ptr [data_00491fac],edi
    L_00401872:
        call asm_FUN_004215a0_004215a0
    L_00401877:
        mov edx,dword ptr [data_00491fac]
    L_0040187d:
        mov eax,dword ptr [data_00491c30]
    L_00401882:
        mov ecx,dword ptr [eax]
    L_00401884:
        add edx,0CCh
    L_0040188a:
        push edx
    L_0040188b:
        push eax
    L_0040188c:
        call dword ptr [ecx+0BCh]
    L_00401892:
        mov dword ptr [data_00491fb0],1
    L_0040189c:
        mov edi,dword ptr [esp+14h]
    L_004018a0:
        cmp byte ptr [ebx],0
    L_004018a3:
        je asm_target_004019c7
    L_004018a9:
        lea esp,[esp+force_disp32_zero]
    L_004018b0:
        mov al,byte ptr [edi]
    L_004018b2:
        cmp al,0Ah
    L_004018b4:
        jne short L_004018d7
    L_004018b6:
        fld dword ptr [esp+18h]
    L_004018ba:
        fmul dword ptr [ebx+54h]
    L_004018bd:
        fadd dword ptr [ebp+34Ch]
    L_004018c3:
        fstp dword ptr [ebp+34Ch]
    L_004018c9:
        mov eax,dword ptr [ebx+40h]
    L_004018cc:
        mov dword ptr [ebp+348h],eax
    L_004018d2:
        jmp asm_target_004019bb
    L_004018d7:
        cmp al,20h
    L_004018d9:
        je asm_target_004019ab
    L_004018df:
        mov ecx,dword ptr [ebx+60h]
    L_004018e2:
        imul ecx,62h
    L_004018e5:
        movzx edx,al
    L_004018e8:
        lea eax,[ecx+edx-20h]
    L_004018ec:
        mov ecx,dword ptr [ebp+8994h]
    L_004018f2:
        imul eax,44h
    L_004018f5:
        mov edx,dword ptr [ecx+118h]
    L_004018fb:
        add eax,edx
    L_004018fd:
        mov dword ptr [ebp+3A8h],eax
    L_00401903:
        mov ecx,dword ptr [ebp+370h]
    L_00401909:
        fld dword ptr [eax+30h]
    L_0040190c:
        mov eax,dword ptr [eax+34h]
    L_0040190f:
        lea esi,[ebp+14h]
    L_00401912:
        or ecx,8
    L_00401915:
        mov dword ptr [esi+4Ch],eax
    L_00401918:
        fstp dword ptr [esi+50h]
    L_0040191b:
        mov dword ptr [esi+35Ch],ecx
    L_00401921:
        mov eax,dword ptr [ebx+64h]
    L_00401924:
        test eax,eax
    L_00401926:
        je short L_00401996
    L_00401928:
        mov ecx,dword ptr [ebx+4Ch]
    L_0040192b:
        fld dword ptr [ebp+348h]
    L_00401931:
        fadd dword ptr [data_00470b08]
    L_00401937:
        mov eax,dword ptr [data_00491c10]
    L_0040193c:
        and ecx,0FF000000h
    L_00401942:
        mov dword ptr [ebp+310h],ecx
    L_00401948:
        mov edx,dword ptr [ebx+4Ch]
    L_0040194b:
        fstp dword ptr [ebp+348h]
    L_00401951:
        fld dword ptr [ebp+34Ch]
    L_00401957:
        shr edx,19h
    L_0040195a:
        fadd dword ptr [data_00470b08]
    L_00401960:
        push eax
    L_00401961:
        mov byte ptr [ebp+313h],dl
    L_00401967:
        fstp dword ptr [ebp+34Ch]
    L_0040196d:
        call asm_FUN_00443080_00443080
    L_00401972:
        fld dword ptr [ebp+348h]
    L_00401978:
        fsub dword ptr [data_00470b08]
    L_0040197e:
        fstp dword ptr [ebp+348h]
    L_00401984:
        fld dword ptr [ebp+34Ch]
    L_0040198a:
        fsub dword ptr [data_00470b08]
    L_00401990:
        fstp dword ptr [ebp+34Ch]
    L_00401996:
        mov edx,dword ptr [data_00491c10]
    L_0040199c:
        mov ecx,dword ptr [ebx+4Ch]
    L_0040199f:
        push edx
    L_004019a0:
        mov dword ptr [ebp+310h],ecx
    L_004019a6:
        call asm_FUN_00443080_00443080
    L_004019ab:
        fld dword ptr [esp+24h]
    L_004019af:
        fadd dword ptr [ebp+348h]
    L_004019b5:
        fstp dword ptr [ebp+348h]
    L_004019bb:
        mov al,byte ptr [edi+1]
    L_004019be:
        inc edi
    L_004019bf:
        test al,al
    L_004019c1:
        jne asm_target_004018b0
    L_004019c7:
        mov eax,dword ptr [esp+1Ch]
    L_004019cb:
        mov ecx,dword ptr [ebp+896Ch]
    L_004019d1:
        inc eax
    L_004019d2:
        add ebx,68h
    L_004019d5:
        cmp eax,ecx
    L_004019d7:
        mov dword ptr [esp+1Ch],eax
    L_004019db:
        jl asm_target_004017a5
    L_004019e1:
        mov eax,dword ptr [esp+10h]
    L_004019e5:
        test eax,eax
    L_004019e7:
        je short L_00401a33
    L_004019e9:
        mov esi,dword ptr [data_00491c10]
    L_004019ef:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004019f4:
        mov edi,491E94h
    L_004019f9:
        mov dword ptr [data_00491fac],edi
    L_004019ff:
        call asm_FUN_004215a0_004215a0
    L_00401a04:
        mov edx,dword ptr [data_00491fac]
    L_00401a0a:
        mov eax,dword ptr [data_00491c30]
    L_00401a0f:
        mov ecx,dword ptr [eax]
    L_00401a11:
        add edx,0CCh
    L_00401a17:
        push edx
    L_00401a18:
        push eax
    L_00401a19:
        call dword ptr [ecx+0BCh]
    L_00401a1f:
        pop edi
    L_00401a20:
        pop esi
    L_00401a21:
        mov eax,1
    L_00401a26:
        pop ebp
    L_00401a27:
        mov dword ptr [data_00491fb0],eax
    L_00401a2c:
        pop ebx
    L_00401a2d:
        add esp,10h
    L_00401a30:
        ret 4
    L_00401a33:
        pop edi
    L_00401a34:
        pop esi
    L_00401a35:
        pop ebp
    L_00401a36:
        mov eax,1
    L_00401a3b:
        pop ebx
    L_00401a3c:
        add esp,10h
    L_00401a3f:
        ret 4
    }
}

// 0x00401A50..0x00401C89: FUN_00401a50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00401a50_00401a50() {
    __asm {
    L_00401a50:
        sub esp,10h
    L_00401a53:
        mov eax,dword ptr [ebx+370h]
    L_00401a59:
        and eax,0FFD7FFFFh
    L_00401a5e:
        or eax,140001h
    L_00401a63:
        push ebp
    L_00401a64:
        mov dword ptr [ebx+370h],eax
    L_00401a6a:
        mov eax,dword ptr [ebx+8970h]
    L_00401a70:
        test eax,eax
    L_00401a72:
        push esi
    L_00401a73:
        push edi
    L_00401a74:
        mov dword ptr [esp+0Ch],1
    L_00401a7c:
        lea ebp,[ebx+6F6Ch]
    L_00401a82:
        mov dword ptr [esp+18h],0
    L_00401a8a:
        jle asm_target_00401c37
    L_00401a90:
        lea eax,[ebp+40h]
    L_00401a93:
        mov ecx,eax
    L_00401a95:
        mov edx,dword ptr [ecx]
    L_00401a97:
        lea eax,[ebx+348h]
    L_00401a9d:
        mov dword ptr [eax],edx
    L_00401a9f:
        mov edx,dword ptr [ecx+4]
    L_00401aa2:
        mov dword ptr [eax+4],edx
    L_00401aa5:
        mov ecx,dword ptr [ecx+8]
    L_00401aa8:
        mov dword ptr [eax+8],ecx
    L_00401aab:
        fld dword ptr [ebp+54h]
    L_00401aae:
        mov edx,dword ptr [ebp+50h]
    L_00401ab1:
        fstp dword ptr [ebx+54h]
    L_00401ab4:
        mov ecx,dword ptr [esp+0Ch]
    L_00401ab8:
        mov dword ptr [ebx+50h],edx
    L_00401abb:
        mov edx,dword ptr [ebx+370h]
    L_00401ac1:
        or edx,8
    L_00401ac4:
        mov dword ptr [ebx+370h],edx
    L_00401aca:
        fild dword ptr [ebx+898Ch]
    L_00401ad0:
        mov eax,dword ptr [ebp+5Ch]
    L_00401ad3:
        cmp ecx,eax
    L_00401ad5:
        fmul dword ptr [ebp+50h]
    L_00401ad8:
        mov edi,ebp
    L_00401ada:
        mov dword ptr [esp+10h],edi
    L_00401ade:
        fstp dword ptr [esp+14h]
    L_00401ae2:
        je asm_target_00401b6d
    L_00401ae8:
        mov esi,dword ptr [data_00491c10]
    L_00401aee:
        mov edi,eax
    L_00401af0:
        mov dword ptr [esp+0Ch],edi
    L_00401af4:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00401af9:
        test edi,edi
    L_00401afb:
        je short L_00401b34
    L_00401afd:
        mov edi,491D7Ch
    L_00401b02:
        mov dword ptr [data_00491fac],edi
    L_00401b08:
        call asm_FUN_004215a0_004215a0
    L_00401b0d:
        mov edx,dword ptr [data_00491fac]
    L_00401b13:
        mov eax,dword ptr [data_00491c30]
    L_00401b18:
        mov ecx,dword ptr [eax]
    L_00401b1a:
        add edx,0CCh
    L_00401b20:
        push edx
    L_00401b21:
        push eax
    L_00401b22:
        call dword ptr [ecx+0BCh]
    L_00401b28:
        mov dword ptr [data_00491fb0],0
    L_00401b32:
        jmp short L_00401b69
    L_00401b34:
        mov edi,491E94h
    L_00401b39:
        mov dword ptr [data_00491fac],edi
    L_00401b3f:
        call asm_FUN_004215a0_004215a0
    L_00401b44:
        mov edx,dword ptr [data_00491fac]
    L_00401b4a:
        mov eax,dword ptr [data_00491c30]
    L_00401b4f:
        mov ecx,dword ptr [eax]
    L_00401b51:
        add edx,0CCh
    L_00401b57:
        push edx
    L_00401b58:
        push eax
    L_00401b59:
        call dword ptr [ecx+0BCh]
    L_00401b5f:
        mov dword ptr [data_00491fb0],1
    L_00401b69:
        mov edi,dword ptr [esp+10h]
    L_00401b6d:
        cmp byte ptr [ebp],0
    L_00401b71:
        je asm_target_00401c15
    L_00401b77:
        mov al,byte ptr [edi]
    L_00401b79:
        cmp al,0Ah
    L_00401b7b:
        jne short L_00401b9d
    L_00401b7d:
        fld dword ptr [ebp+54h]
    L_00401b80:
        fmul dword ptr [data_00470c88]
    L_00401b86:
        fadd dword ptr [ebx+34Ch]
    L_00401b8c:
        fstp dword ptr [ebx+34Ch]
    L_00401b92:
        mov eax,dword ptr [ebp+40h]
    L_00401b95:
        mov dword ptr [ebx+348h],eax
    L_00401b9b:
        jmp short L_00401c09
    L_00401b9d:
        cmp al,20h
    L_00401b9f:
        je short L_00401bf9
    L_00401ba1:
        mov edx,dword ptr [ebx+8994h]
    L_00401ba7:
        fld dword ptr [data_00470afc]
    L_00401bad:
        fld dword ptr [ebx+50h]
    L_00401bb0:
        movzx ecx,al
    L_00401bb3:
        mov eax,dword ptr [edx+118h]
    L_00401bb9:
        fucompp
    L_00401bbb:
        sub ecx,20h
    L_00401bbe:
        imul ecx,44h
    L_00401bc1:
        add ecx,eax
    L_00401bc3:
        mov dword ptr [ebx+3A8h],ecx
    L_00401bc9:
        mov eax,dword ptr [ebp+4Ch]
    L_00401bcc:
        mov dword ptr [ebx+310h],eax
    L_00401bd2:
        fnstsw ax
    L_00401bd4:
        test ah,44h
    L_00401bd7:
        jnp short L_00401bea
    L_00401bd9:
        mov ecx,dword ptr [data_00491c10]
    L_00401bdf:
        push ecx
    L_00401be0:
        lea eax,[ebx+14h]
    L_00401be3:
        call asm_FUN_00443290_00443290
    L_00401be8:
        jmp short L_00401bf9
    L_00401bea:
        mov edx,dword ptr [data_00491c10]
    L_00401bf0:
        push edx
    L_00401bf1:
        lea esi,[ebx+14h]
    L_00401bf4:
        call asm_FUN_00443080_00443080
    L_00401bf9:
        fld dword ptr [esp+14h]
    L_00401bfd:
        fadd dword ptr [ebx+348h]
    L_00401c03:
        fstp dword ptr [ebx+348h]
    L_00401c09:
        mov al,byte ptr [edi+1]
    L_00401c0c:
        inc edi
    L_00401c0d:
        test al,al
    L_00401c0f:
        jne asm_target_00401b77
    L_00401c15:
        mov eax,dword ptr [esp+18h]
    L_00401c19:
        mov ecx,dword ptr [ebx+8970h]
    L_00401c1f:
        inc eax
    L_00401c20:
        add ebp,68h
    L_00401c23:
        cmp eax,ecx
    L_00401c25:
        mov dword ptr [esp+18h],eax
    L_00401c29:
        jl asm_target_00401a90
    L_00401c2f:
        mov eax,dword ptr [esp+0Ch]
    L_00401c33:
        test eax,eax
    L_00401c35:
        je short L_00401c7e
    L_00401c37:
        mov esi,dword ptr [data_00491c10]
    L_00401c3d:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00401c42:
        mov edi,491E94h
    L_00401c47:
        mov dword ptr [data_00491fac],edi
    L_00401c4d:
        call asm_FUN_004215a0_004215a0
    L_00401c52:
        mov edx,dword ptr [data_00491fac]
    L_00401c58:
        mov eax,dword ptr [data_00491c30]
    L_00401c5d:
        mov ecx,dword ptr [eax]
    L_00401c5f:
        add edx,0CCh
    L_00401c65:
        push edx
    L_00401c66:
        push eax
    L_00401c67:
        call dword ptr [ecx+0BCh]
    L_00401c6d:
        pop edi
    L_00401c6e:
        mov eax,1
    L_00401c73:
        pop esi
    L_00401c74:
        mov dword ptr [data_00491fb0],eax
    L_00401c79:
        pop ebp
    L_00401c7a:
        add esp,10h
    L_00401c7d:
        ret
    L_00401c7e:
        pop edi
    L_00401c7f:
        pop esi
    L_00401c80:
        mov eax,1
    L_00401c85:
        pop ebp
    L_00401c86:
        add esp,10h
    L_00401c89:
        ret
    }
}
