#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00419120..0x004191D7: FUN_00419120
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00419120_00419120() {
    __asm {
    L_00419120:
        sub esp,3Ch
    L_00419123:
        test eax,eax
    L_00419125:
        push ebp
    L_00419126:
        mov ebp,dword ptr [esp+44h]
    L_0041912a:
        je asm_target_0041963c
    L_00419130:
        push ebx
    L_00419131:
        mov ebx,dword ptr [data_00491c10]
    L_00419137:
        push esi
    L_00419138:
        push edi
    L_00419139:
        lea esp,[esp+force_disp32_zero]
    L_00419140:
        mov ecx,dword ptr [eax+4]
    L_00419143:
        mov edi,dword ptr [eax]
    L_00419145:
        mov eax,dword ptr [edi+68h]
    L_00419148:
        test eax,eax
    L_0041914a:
        mov dword ptr [esp+50h],ecx
    L_0041914e:
        je short L_00419158
    L_00419150:
        cmp eax,dword ptr [data_00474c84]
    L_00419156:
        jne short L_0041915b
    L_00419158:
        dec dword ptr [edi+60h]
    L_0041915b:
        mov eax,dword ptr [edi+60h]
    L_0041915e:
        test eax,eax
    L_00419160:
        jg asm_target_0041962d
    L_00419166:
        mov edx,dword ptr [ebp+1A4h]
    L_0041916c:
        mov ecx,dword ptr [ebp+edx*4+0DCh]
    L_00419173:
        test ecx,ecx
    L_00419175:
        lea esi,[ebp+edx*4+0DCh]
    L_0041917c:
        TH10_REL8(0x74, 0x0041917c, VA_asm_target_004191ef)
    L_0041917e:
        mov eax,dword ptr [ebx+72DAD4h]
    L_00419184:
        test eax,eax
    L_00419186:
        je short L_00419195
    L_00419188:
        mov edx,dword ptr [eax]
    L_0041918a:
        cmp dword ptr [edx],ecx
    L_0041918c:
        je short L_004191af
    L_0041918e:
        mov eax,dword ptr [eax+4]
    L_00419191:
        test eax,eax
    L_00419193:
        jne short L_00419188
    L_00419195:
        mov eax,dword ptr [ebx+72DADCh]
    L_0041919b:
        test eax,eax
    L_0041919d:
        TH10_REL8(0x74, 0x0041919d, VA_asm_target_004191ef)
    L_0041919f:
        nop
    L_004191a0:
        mov edx,dword ptr [eax]
    L_004191a2:
        cmp dword ptr [edx],ecx
    L_004191a4:
        je short L_004191af
    L_004191a6:
        mov eax,dword ptr [eax+4]
    L_004191a9:
        test eax,eax
    L_004191ab:
        jne short L_004191a0
    L_004191ad:
        TH10_REL8(0xeb, 0x004191ad, VA_asm_target_004191ef)
    L_004191af:
        mov eax,dword ptr [eax]
    L_004191b1:
        test eax,eax
    L_004191b3:
        TH10_REL8(0x74, 0x004191b3, VA_asm_target_004191ef)
    L_004191b5:
        mov ebx,dword ptr [eax+35Ch]
    L_004191bb:
        mov ecx,dword ptr [eax+18h]
    L_004191be:
        mov edx,4000000h
    L_004191c3:
        or ebx,edx
    L_004191c5:
        test ecx,ecx
    L_004191c7:
        mov dword ptr [eax+35Ch],ebx
    L_004191cd:
        TH10_REL8(0x75, 0x004191cd, VA_asm_target_004191ef)
    L_004191cf:
        mov eax,dword ptr [eax+14h]
    L_004191d2:
        test eax,eax
    L_004191d4:
        TH10_REL8(0x74, 0x004191d4, VA_asm_target_004191ef)
    L_004191d6:
        TH10_REL8(0xeb, 0x004191d6, VA_asm_FUN_00419120_part_004191e0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_004191e0:
        mov ecx,dword ptr [eax]
    L_004191e2:
        or dword ptr [ecx+35Ch],edx
    L_004191e8:
        mov eax,dword ptr [eax+4]
    L_004191eb:
        test eax,eax
    L_004191ed:
        jne short L_004191e0
    L_004191ef:
        mov dword ptr [esi],0
    L_004191f5:
        fld dword ptr [edi+7Ch]
    L_004191f8:
        fmul dword ptr [data_00470bd0]
    L_004191fe:
        fadd dword ptr [edi+4]
    L_00419201:
        fstp dword ptr [edi+4]
    L_00419204:
        mov ecx,dword ptr [ebp+1A4h]
    L_0041920a:
        fld dword ptr [edi+7Ch]
    L_0041920d:
        fcomp dword ptr [data_00470afc]
    L_00419213:
        fnstsw ax
    L_00419215:
        test ah,41h
    L_00419218:
        jp asm_target_004192e8
    L_0041921e:
        mov eax,dword ptr [data_004776e0]
    L_00419223:
        mov eax,dword ptr [eax+899Ch]
    L_00419229:
        add ecx,2
    L_0041922c:
        push ecx
    L_0041922d:
        lea edx,[esp+14h]
    L_00419231:
        push edx
    L_00419232:
        push eax
    L_00419233:
        call asm_PlayerAnimation_Create_00448db0
    L_00419238:
        mov edx,dword ptr [eax]
    L_0041923a:
        mov ecx,dword ptr [ebp+1A4h]
    L_00419240:
        mov ebx,dword ptr [data_00491c10]
    L_00419246:
        mov dword ptr [ebp+ecx*4+0DCh],edx
    L_0041924d:
        mov eax,dword ptr [ebp+1A4h]
    L_00419253:
        mov ecx,dword ptr [ebp+eax*4+0DCh]
    L_0041925a:
        test ecx,ecx
    L_0041925c:
        lea edx,[ebp+eax*4+0DCh]
    L_00419263:
        jne short L_00419269
    L_00419265:
        xor eax,eax
    L_00419267:
        jmp short L_004192a5
    L_00419269:
        mov eax,dword ptr [ebx+72DAD4h]
    L_0041926f:
        test eax,eax
    L_00419271:
        je short L_00419280
    L_00419273:
        mov esi,dword ptr [eax]
    L_00419275:
        cmp dword ptr [esi],ecx
    L_00419277:
        je short L_0041929f
    L_00419279:
        mov eax,dword ptr [eax+4]
    L_0041927c:
        test eax,eax
    L_0041927e:
        jne short L_00419273
    L_00419280:
        mov eax,dword ptr [ebx+72DADCh]
    L_00419286:
        test eax,eax
    L_00419288:
        je short L_00419265
    L_0041928a:
        lea ebx,[ebx+force_disp32_zero]
    L_00419290:
        mov esi,dword ptr [eax]
    L_00419292:
        cmp dword ptr [esi],ecx
    L_00419294:
        je short L_0041929f
    L_00419296:
        mov eax,dword ptr [eax+4]
    L_00419299:
        test eax,eax
    L_0041929b:
        jne short L_00419290
    L_0041929d:
        jmp short L_004192a5
    L_0041929f:
        mov eax,dword ptr [eax]
    L_004192a1:
        test eax,eax
    L_004192a3:
        jne short L_004192ab
    L_004192a5:
        mov dword ptr [edx],0
    L_004192ab:
        mov byte ptr [eax+3A1h],0Fh
    L_004192b2:
        mov byte ptr [eax+3A0h],0Fh
    L_004192b9:
        fld dword ptr [edi+7Ch]
    L_004192bc:
        mov ecx,dword ptr [edi+7Ch]
    L_004192bf:
        fmul dword ptr [data_00470ca8]
    L_004192c5:
        mov edx,ecx
    L_004192c7:
        mov dword ptr [esp+1Ch],ecx
    L_004192cb:
        mov dword ptr [esp+20h],edx
    L_004192cf:
        fstp dword ptr [esp+24h]
    L_004192d3:
        mov dword ptr [esp+28h],0
    L_004192db:
        lea ecx,[esp+1Ch]
    L_004192df:
        lea edx,[esp+24h]
    L_004192e3:
        jmp asm_target_00419435
    L_004192e8:
        fld dword ptr [edi+7Ch]
    L_004192eb:
        add ecx,0Ch
    L_004192ee:
        fcomp dword ptr [data_00470b08]
    L_004192f4:
        push ecx
    L_004192f5:
        fnstsw ax
    L_004192f7:
        test ah,41h
    L_004192fa:
        jp asm_target_004193ab
    L_00419300:
        mov eax,dword ptr [data_004776e0]
    L_00419305:
        mov eax,dword ptr [eax+899Ch]
    L_0041930b:
        lea edx,[esp+18h]
    L_0041930f:
        push edx
    L_00419310:
        push eax
    L_00419311:
        call asm_PlayerAnimation_Create_00448db0
    L_00419316:
        mov edx,dword ptr [eax]
    L_00419318:
        mov ecx,dword ptr [ebp+1A4h]
    L_0041931e:
        mov dword ptr [ebp+ecx*4+0DCh],edx
    L_00419325:
        mov eax,dword ptr [ebp+1A4h]
    L_0041932b:
        mov ecx,dword ptr [ebp+eax*4+0DCh]
    L_00419332:
        mov edx,dword ptr [data_00491c10]
    L_00419338:
        lea ebx,[ebp+eax*4+0DCh]
    L_0041933f:
        push ecx
    L_00419340:
        call asm_AnimationManager_Find_004491c0
    L_00419345:
        mov esi,eax
    L_00419347:
        test esi,esi
    L_00419349:
        jne short L_0041934d
    L_0041934b:
        mov dword ptr [ebx],eax
    L_0041934d:
        fld dword ptr [edi+7Ch]
    L_00419350:
        fmul dword ptr [data_00470c08]
    L_00419356:
        call asm_FUN_00463b2c_00463b2c
    L_0041935b:
        mov byte ptr [esi+3A1h],al
    L_00419361:
        mov byte ptr [esi+3A0h],al
    L_00419367:
        fld dword ptr [edi+7Ch]
    L_0041936a:
        fmul dword ptr [data_00470ce4]
    L_00419370:
        push 4
    L_00419372:
        push 8
    L_00419374:
        lea ecx,[esp+34h]
    L_00419378:
        fstp dword ptr [esp+3Ch]
    L_0041937c:
        lea edx,[esp+3Ch]
    L_00419380:
        fld dword ptr [edi+7Ch]
    L_00419383:
        mov eax,esi
    L_00419385:
        fmul dword ptr [data_00470b0c]
    L_0041938b:
        mov dword ptr [esp+40h],0
    L_00419393:
        fst dword ptr [esp+34h]
    L_00419397:
        fstp dword ptr [esp+38h]
    L_0041939b:
        call asm_FUN_0041ab70_0041ab70
    L_004193a0:
        mov ebx,dword ptr [data_00491c10]
    L_004193a6:
        jmp asm_target_00419440
    L_004193ab:
        mov edx,dword ptr [data_004776e0]
    L_004193b1:
        mov eax,dword ptr [edx+899Ch]
    L_004193b7:
        lea edx,[esp+1Ch]
    L_004193bb:
        push edx
    L_004193bc:
        push eax
    L_004193bd:
        call asm_PlayerAnimation_Create_00448db0
    L_004193c2:
        mov edx,dword ptr [eax]
    L_004193c4:
        mov ecx,dword ptr [ebp+1A4h]
    L_004193ca:
        mov ebx,dword ptr [data_00491c10]
    L_004193d0:
        mov dword ptr [ebp+ecx*4+0DCh],edx
    L_004193d7:
        mov eax,dword ptr [ebp+1A4h]
    L_004193dd:
        mov ecx,dword ptr [ebp+eax*4+0DCh]
    L_004193e4:
        lea esi,[ebp+eax*4+0DCh]
    L_004193eb:
        push ecx
    L_004193ec:
        mov edx,ebx
    L_004193ee:
        call asm_AnimationManager_Find_004491c0
    L_004193f3:
        test eax,eax
    L_004193f5:
        jne short L_004193f9
    L_004193f7:
        mov dword ptr [esi],eax
    L_004193f9:
        mov byte ptr [eax+3A1h],1Eh
    L_00419400:
        mov byte ptr [eax+3A0h],1Eh
    L_00419407:
        fld dword ptr [edi+7Ch]
    L_0041940a:
        fmul dword ptr [data_00470ce4]
    L_00419410:
        mov dword ptr [esp+48h],0
    L_00419418:
        lea ecx,[esp+3Ch]
    L_0041941c:
        lea edx,[esp+44h]
    L_00419420:
        fstp dword ptr [esp+44h]
    L_00419424:
        fld dword ptr [edi+7Ch]
    L_00419427:
        fmul dword ptr [data_00470b0c]
    L_0041942d:
        fst dword ptr [esp+3Ch]
    L_00419431:
        fstp dword ptr [esp+40h]
    L_00419435:
        push 4
    L_00419437:
        push 8
    L_00419439:
        mov esi,eax
    L_0041943b:
        call asm_FUN_0041ab70_0041ab70
    L_00419440:
        mov eax,dword ptr [edi+64h]
    L_00419443:
        sub eax,0
    L_00419446:
        je asm_target_00419567
    L_0041944c:
        dec eax
    L_0041944d:
        je asm_target_004194e2
    L_00419453:
        dec eax
    L_00419454:
        jne asm_target_004195b8
    L_0041945a:
        mov eax,dword ptr [ebp+1A4h]
    L_00419460:
        lea eax,[eax+eax*2]
    L_00419463:
        lea ecx,[ebp+eax*4+104h]
    L_0041946a:
        lea edx,[esi+340h]
    L_00419470:
        mov eax,dword ptr [edx]
    L_00419472:
        mov dword ptr [ecx],eax
    L_00419474:
        mov eax,dword ptr [edx+4]
    L_00419477:
        mov dword ptr [ecx+4],eax
    L_0041947a:
        mov edx,dword ptr [edx+8]
    L_0041947d:
        mov dword ptr [ecx+8],edx
    L_00419480:
        fld dword ptr [edi+80h]
    L_00419486:
        mov eax,dword ptr [ebp+1A4h]
    L_0041948c:
        fmul dword ptr [data_00470b0c]
    L_00419492:
        lea eax,[eax+eax*2]
    L_00419495:
        lea eax,[ebp+eax*4+104h]
    L_0041949c:
        fsubr dword ptr [eax]
    L_0041949e:
        fstp dword ptr [eax]
    L_004194a0:
        mov ecx,dword ptr [ebp+1A4h]
    L_004194a6:
        mov edx,dword ptr [edi+80h]
    L_004194ac:
        lea eax,[edi+1Ch]
    L_004194af:
        push eax
    L_004194b0:
        push 0FFFFFFh
    L_004194b5:
        push ebx
    L_004194b6:
        mov dword ptr [ebp+ecx*4+17Ch],edx
    L_004194bd:
        call asm_Ascii_FormatShadowedRetail_00447ae0
    L_004194c2:
        mov ecx,dword ptr [esi+35Ch]
    L_004194c8:
        and ecx,0FFFBFFFFh
    L_004194ce:
        add esp,0Ch
    L_004194d1:
        or ecx,80000h
    L_004194d7:
        mov dword ptr [esi+35Ch],ecx
    L_004194dd:
        jmp asm_target_004195b2
    L_004194e2:
        mov eax,dword ptr [ebp+1A4h]
    L_004194e8:
        lea eax,[eax+eax*2]
    L_004194eb:
        lea ecx,[ebp+eax*4+104h]
    L_004194f2:
        lea edx,[esi+340h]
    L_004194f8:
        mov eax,dword ptr [edx]
    L_004194fa:
        mov dword ptr [ecx],eax
    L_004194fc:
        mov eax,dword ptr [edx+4]
    L_004194ff:
        mov dword ptr [ecx+4],eax
    L_00419502:
        mov edx,dword ptr [edx+8]
    L_00419505:
        mov dword ptr [ecx+8],edx
    L_00419508:
        fld dword ptr [edi+80h]
    L_0041950e:
        mov eax,dword ptr [ebp+1A4h]
    L_00419514:
        fmul dword ptr [data_00470b0c]
    L_0041951a:
        lea eax,[eax+eax*2]
    L_0041951d:
        lea eax,[ebp+eax*4+104h]
    L_00419524:
        fadd dword ptr [eax]
    L_00419526:
        fstp dword ptr [eax]
    L_00419528:
        mov ecx,dword ptr [ebp+1A4h]
    L_0041952e:
        mov edx,dword ptr [edi+80h]
    L_00419534:
        lea eax,[edi+1Ch]
    L_00419537:
        push eax
    L_00419538:
        push 0FFFFFFh
    L_0041953d:
        push ebx
    L_0041953e:
        mov dword ptr [ebp+ecx*4+17Ch],edx
    L_00419545:
        call asm_Recovery_MarkLogState_00447a50
    L_0041954a:
        mov ecx,dword ptr [esi+35Ch]
    L_00419550:
        and ecx,0FFF7FFFFh
    L_00419556:
        add esp,0Ch
    L_00419559:
        or ecx,40000h
    L_0041955f:
        mov dword ptr [esi+35Ch],ecx
    L_00419565:
        jmp short L_004195b2
    L_00419567:
        mov eax,dword ptr [ebp+1A4h]
    L_0041956d:
        lea eax,[eax+eax*2]
    L_00419570:
        lea ecx,[ebp+eax*4+104h]
    L_00419577:
        lea edx,[esi+340h]
    L_0041957d:
        mov eax,dword ptr [edx]
    L_0041957f:
        mov dword ptr [ecx],eax
    L_00419581:
        mov eax,dword ptr [edx+4]
    L_00419584:
        mov dword ptr [ecx+4],eax
    L_00419587:
        mov edx,dword ptr [edx+8]
    L_0041958a:
        mov dword ptr [ecx+8],edx
    L_0041958d:
        mov eax,dword ptr [ebp+1A4h]
    L_00419593:
        mov ecx,dword ptr [edi+80h]
    L_00419599:
        lea edx,[edi+1Ch]
    L_0041959c:
        push edx
    L_0041959d:
        push 0FFFFFFh
    L_004195a2:
        push ebx
    L_004195a3:
        mov dword ptr [ebp+eax*4+17Ch],ecx
    L_004195aa:
        call asm_FUN_00447bb0_00447bb0
    L_004195af:
        add esp,0Ch
    L_004195b2:
        mov ebx,dword ptr [data_00491c10]
    L_004195b8:
        mov eax,dword ptr [edi+84h]
    L_004195be:
        mov dword ptr [esi+2FCh],eax
    L_004195c4:
        mov byte ptr [esi+2FFh],0
    L_004195cb:
        mov ecx,dword ptr [edi+6Ch]
    L_004195ce:
        mov dword ptr [esi+30Ch],ecx
    L_004195d4:
        movzx edx,byte ptr [edi+87h]
    L_004195db:
        mov dword ptr [esi+310h],edx
    L_004195e1:
        mov eax,dword ptr [ebp+1A4h]
    L_004195e7:
        inc eax
    L_004195e8:
        cdq
    L_004195e9:
        mov ecx,0Ah
    L_004195ee:
        idiv ecx
    L_004195f0:
        xor ecx,ecx
    L_004195f2:
        mov dword ptr [ebp+1A4h],edx
    L_004195f8:
        mov eax,dword ptr [edi+10h]
    L_004195fb:
        cmp eax,ecx
    L_004195fd:
        je short L_00419605
    L_004195ff:
        mov edx,dword ptr [edi+14h]
    L_00419602:
        mov dword ptr [eax+8],edx
    L_00419605:
        mov eax,dword ptr [edi+14h]
    L_00419608:
        cmp eax,ecx
    L_0041960a:
        je short L_00419612
    L_0041960c:
        mov edx,dword ptr [edi+10h]
    L_0041960f:
        mov dword ptr [eax+4],edx
    L_00419612:
        cmp dword ptr [esp+54h],ecx
    L_00419616:
        mov dword ptr [edi+10h],ecx
    L_00419619:
        mov dword ptr [edi+14h],ecx
    L_0041961c:
        je short L_0041962d
    L_0041961e:
        push edi
    L_0041961f:
        call asm_free_004524a1
    L_00419624:
        mov ebx,dword ptr [data_00491c10]
    L_0041962a:
        add esp,4
    L_0041962d:
        mov eax,dword ptr [esp+50h]
    L_00419631:
        test eax,eax
    L_00419633:
        jne asm_target_00419140
    L_00419639:
        pop edi
    L_0041963a:
        pop esi
    L_0041963b:
        pop ebx
    L_0041963c:
        xor eax,eax
    L_0041963e:
        pop ebp
    L_0041963f:
        add esp,3Ch
    L_00419642:
        ret 8
    }
}
