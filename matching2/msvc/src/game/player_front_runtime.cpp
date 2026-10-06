#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3401): closest_byte_count=1656/1656; first_diff=none
// (authoritative MSVC 13.10 probe exact for the retained retail body).
// residual_class=private EDI receiver/EAX input ABI, direction-state switch
// scheduling, x87 position updates, callback function-pointer fields, and
// four-slot animation object layout. variants_tested=live Ghidra decompile
// plus xrefs/callers/callees, dependency paths, and dataflow request; Ghidra
// exposes the full control flow but no PCode for this private-ABI region.
// next_lever=co-compile with 0x0043E710, 0x004489D0, 0x00449210,
// 0x004492F0, 0x00449350, and 0x00449950 in a native-LTCG cluster using
// caller 0x00425730.
//
// 0x004250B0..0x0042558C: FUN_004250b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004250b0_004250b0() {
    __asm {
    L_004250b0:
        sub esp,18h
    L_004250b3:
        mov al,byte ptr [data_00474e5c]
    L_004250b8:
        push ebx
    L_004250b9:
        mov cl,al
    L_004250bb:
        push ebp
    L_004250bc:
        xor ebp,ebp
    L_004250be:
        xor ebx,ebx
    L_004250c0:
        and cl,50h
    L_004250c3:
        cmp cl,50h
    L_004250c6:
        push esi
    L_004250c7:
        mov dword ptr [esp+10h],ebp
    L_004250cb:
        mov dword ptr [esp+0Ch],ebx
    L_004250cf:
        mov esi,1
    L_004250d4:
        jne short L_004250e5
    L_004250d6:
        mov dword ptr [edi+454h],5
    L_004250e0:
        jmp asm_target_00425169
    L_004250e5:
        mov dl,al
    L_004250e7:
        and dl,60h
    L_004250ea:
        cmp dl,60h
    L_004250ed:
        jne short L_004250fb
    L_004250ef:
        mov dword ptr [edi+454h],7
    L_004250f9:
        jmp short L_00425169
    L_004250fb:
        mov cl,al
    L_004250fd:
        and cl,90h
    L_00425100:
        cmp cl,90h
    L_00425103:
        jne short L_00425111
    L_00425105:
        mov dword ptr [edi+454h],6
    L_0042510f:
        jmp short L_00425169
    L_00425111:
        mov dl,al
    L_00425113:
        and dl,0A0h
    L_00425116:
        cmp dl,0A0h
    L_00425119:
        jne short L_00425127
    L_0042511b:
        mov dword ptr [edi+454h],8
    L_00425125:
        jmp short L_00425169
    L_00425127:
        test al,20h
    L_00425129:
        je short L_00425137
    L_0042512b:
        mov dword ptr [edi+454h],2
    L_00425135:
        jmp short L_00425169
    L_00425137:
        test al,10h
    L_00425139:
        je short L_00425143
    L_0042513b:
        mov dword ptr [edi+454h],esi
    L_00425141:
        jmp short L_00425169
    L_00425143:
        test al,40h
    L_00425145:
        je short L_00425153
    L_00425147:
        mov dword ptr [edi+454h],3
    L_00425151:
        jmp short L_00425169
    L_00425153:
        test al,al
    L_00425155:
        jns short L_00425163
    L_00425157:
        mov dword ptr [edi+454h],4
    L_00425161:
        jmp short L_00425169
    L_00425163:
        mov dword ptr [edi+454h],ebp
    L_00425169:
        mov eax,dword ptr [data_00477704]
    L_0042516e:
        cmp eax,ebp
    L_00425170:
        je short L_004251ca
    L_00425172:
        cmp dword ptr [eax+60h],ebp
    L_00425175:
        je short L_004251ca
    L_00425177:
        cmp dword ptr [edi+48Ch],4
    L_0042517e:
        jl short L_004251ca
    L_00425180:
        mov eax,dword ptr [data_00474e5c]
    L_00425185:
        shr eax,2
    L_00425188:
        and eax,esi
    L_0042518a:
        mov dword ptr [edi+4474h],eax
    L_00425190:
        mov eax,dword ptr [data_00474c68]
    L_00425195:
        mov ecx,dword ptr [data_00474c6c]
    L_0042519b:
        lea edx,[ecx+eax*2]
    L_0042519e:
        add edx,eax
    L_004251a0:
        cmp edx,5
    L_004251a3:
        jne short L_004251da
    L_004251a5:
        test byte ptr [data_00474e5c],4
    L_004251ac:
        je short L_004251b6
    L_004251ae:
        mov dword ptr [edi+4308h],ebp
    L_004251b4:
        jmp short L_004251da
    L_004251b6:
        mov eax,dword ptr [edi+4308h]
    L_004251bc:
        cmp eax,1Eh
    L_004251bf:
        jge short L_004251da
    L_004251c1:
        inc eax
    L_004251c2:
        mov dword ptr [edi+4308h],eax
    L_004251c8:
        jmp short L_004251da
    L_004251ca:
        mov dword ptr [edi+4474h],ebp
    L_004251d0:
        mov dword ptr [edi+4308h],1Eh
    L_004251da:
        cmp dword ptr [edi+4474h],ebp
    L_004251e0:
        je asm_target_004252d0
    L_004251e6:
        cmp dword ptr [edi+329Ch],ebp
    L_004251ec:
        jne short L_0042524b
    L_004251ee:
        mov eax,dword ptr [data_004776f0]
    L_004251f3:
        mov esi,dword ptr [data_00491c10]
    L_004251f9:
        mov ebx,dword ptr [eax+3E0B50h]
    L_004251ff:
        call asm_FUN_00449950_00449950
    L_00425204:
        mov esi,eax
    L_00425206:
        mov edx,dword ptr [esi+35Ch]
    L_0042520c:
        push 160h
    L_00425211:
        or edx,40000000h
    L_00425217:
        push esi
    L_00425218:
        mov ecx,ebx
    L_0042521a:
        mov dword ptr [esi+20h],9
    L_00425221:
        mov dword ptr [esi+35Ch],edx
    L_00425227:
        call asm_FUN_00449870_00449870
    L_0042522c:
        mov edx,dword ptr [data_00491c10]
    L_00425232:
        mov ebx,esi
    L_00425234:
        lea eax,[esp+14h]
    L_00425238:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042523d:
        mov ecx,dword ptr [esp+14h]
    L_00425241:
        mov ebx,dword ptr [esp+0Ch]
    L_00425245:
        mov dword ptr [edi+329Ch],ecx
    L_0042524b:
        mov eax,dword ptr [edi+454h]
    L_00425251:
        dec eax
    L_00425252:
        cmp eax,7
    L_00425255:
        ja asm_target_004253b2
    L_0042525b:
        jmp dword ptr [eax*4+4256E8h]
    L_00425262:
        mov ebp,dword ptr [edi+3D8h]
    L_00425268:
        jmp asm_target_00425373
    L_0042526d:
        mov ebp,dword ptr [edi+3D8h]
    L_00425273:
        neg ebp
    L_00425275:
        jmp asm_target_00425373
    L_0042527a:
        mov ebx,dword ptr [edi+3D8h]
    L_00425280:
        neg ebx
    L_00425282:
        mov dword ptr [esp+0Ch],ebx
    L_00425286:
        jmp asm_target_004253b2
    L_0042528b:
        mov ebx,dword ptr [edi+3D8h]
    L_00425291:
        mov dword ptr [esp+0Ch],ebx
    L_00425295:
        jmp asm_target_004253b2
    L_0042529a:
        mov ebp,dword ptr [edi+3E0h]
    L_004252a0:
        neg ebp
    L_004252a2:
        jmp asm_target_0042536d
    L_004252a7:
        mov ebx,dword ptr [edi+3E0h]
    L_004252ad:
        mov ebp,ebx
    L_004252af:
        neg ebp
    L_004252b1:
        jmp asm_target_0042536f
    L_004252b6:
        mov ebp,dword ptr [edi+3E0h]
    L_004252bc:
        mov ebx,ebp
    L_004252be:
        neg ebx
    L_004252c0:
        jmp asm_target_0042536f
    L_004252c5:
        mov ebp,dword ptr [edi+3E0h]
    L_004252cb:
        jmp asm_target_0042536d
    L_004252d0:
        mov edx,dword ptr [edi+329Ch]
    L_004252d6:
        push edx
    L_004252d7:
        mov edx,dword ptr [data_00491c10]
    L_004252dd:
        call asm_AnimationManager_Find_004491c0
    L_004252e2:
        test eax,eax
    L_004252e4:
        je short L_004252f8
    L_004252e6:
        mov eax,dword ptr [edi+329Ch]
    L_004252ec:
        mov edx,dword ptr [data_00491c10]
    L_004252f2:
        push eax
    L_004252f3:
        call asm_AnimationManager_SetStopFrame_00449210
    L_004252f8:
        mov dword ptr [edi+329Ch],0
    L_00425302:
        mov eax,dword ptr [edi+454h]
    L_00425308:
        dec eax
    L_00425309:
        cmp eax,7
    L_0042530c:
        ja asm_target_004253b2
    L_00425312:
        jmp dword ptr [eax*4+425708h]
    L_00425319:
        mov ebp,dword ptr [edi+3D4h]
    L_0042531f:
        jmp short L_00425373
    L_00425321:
        mov ebp,dword ptr [edi+3D4h]
    L_00425327:
        neg ebp
    L_00425329:
        jmp short L_00425373
    L_0042532b:
        mov ebx,dword ptr [edi+3D4h]
    L_00425331:
        neg ebx
    L_00425333:
        mov dword ptr [esp+0Ch],ebx
    L_00425337:
        jmp short L_004253b2
    L_00425339:
        mov ebx,dword ptr [edi+3D4h]
    L_0042533f:
        mov dword ptr [esp+0Ch],ebx
    L_00425343:
        jmp short L_004253b2
    L_00425345:
        mov ebp,dword ptr [edi+3DCh]
    L_0042534b:
        neg ebp
    L_0042534d:
        jmp short L_0042536d
    L_0042534f:
        mov ebx,dword ptr [edi+3DCh]
    L_00425355:
        mov ebp,ebx
    L_00425357:
        neg ebp
    L_00425359:
        jmp short L_0042536f
    L_0042535b:
        mov ebp,dword ptr [edi+3DCh]
    L_00425361:
        mov ebx,ebp
    L_00425363:
        neg ebx
    L_00425365:
        jmp short L_0042536f
    L_00425367:
        mov ebp,dword ptr [edi+3DCh]
    L_0042536d:
        mov ebx,ebp
    L_0042536f:
        mov dword ptr [esp+0Ch],ebx
    L_00425373:
        test ebp,ebp
    L_00425375:
        mov dword ptr [esp+10h],ebp
    L_00425379:
        jge short L_004253b0
    L_0042537b:
        mov eax,dword ptr [edi+44Ch]
    L_00425381:
        test eax,eax
    L_00425383:
        jl short L_004253ae
    L_00425385:
        mov ecx,dword ptr [edi+10h]
    L_00425388:
        lea eax,[edi+14h]
    L_0042538b:
        mov ebx,1
    L_00425390:
        call asm_AnimationObject_LoadScript_0043e710
    L_00425395:
        mov ebx,dword ptr [esp+0Ch]
    L_00425399:
        test ebp,ebp
    L_0042539b:
        jle short L_004253d4
    L_0042539d:
        mov eax,dword ptr [edi+44Ch]
    L_004253a3:
        test eax,eax
    L_004253a5:
        jg short L_004253d2
    L_004253a7:
        mov ebx,3
    L_004253ac:
        jmp short L_004253e5
    L_004253ae:
        test ebp,ebp
    L_004253b0:
        jne short L_00425399
    L_004253b2:
        mov eax,dword ptr [edi+44Ch]
    L_004253b8:
        test eax,eax
    L_004253ba:
        jge short L_004253de
    L_004253bc:
        mov ecx,dword ptr [edi+10h]
    L_004253bf:
        lea eax,[edi+14h]
    L_004253c2:
        mov ebx,2
    L_004253c7:
        call asm_AnimationObject_LoadScript_0043e710
    L_004253cc:
        mov ebx,dword ptr [esp+0Ch]
    L_004253d0:
        jmp short L_004253d6
    L_004253d2:
        test ebp,ebp
    L_004253d4:
        jne short L_004253f4
    L_004253d6:
        mov eax,dword ptr [edi+44Ch]
    L_004253dc:
        test eax,eax
    L_004253de:
        jle short L_004253f4
    L_004253e0:
        mov ebx,4
    L_004253e5:
        mov ecx,dword ptr [edi+10h]
    L_004253e8:
        lea eax,[edi+14h]
    L_004253eb:
        call asm_AnimationObject_LoadScript_0043e710
    L_004253f0:
        mov ebx,dword ptr [esp+0Ch]
    L_004253f4:
        fild dword ptr [esp+10h]
    L_004253f8:
        mov dword ptr [edi+44Ch],ebp
    L_004253fe:
        mov dword ptr [edi+450h],ebx
    L_00425404:
        fmul dword ptr [data_00476f78]
    L_0042540a:
        call asm_FUN_00463b2c_00463b2c
    L_0042540f:
        fild dword ptr [esp+0Ch]
    L_00425413:
        mov dword ptr [edi+3F0h],eax
    L_00425419:
        fmul dword ptr [data_00476f78]
    L_0042541f:
        call asm_FUN_00463b2c_00463b2c
    L_00425424:
        mov ecx,dword ptr [edi+3F0h]
    L_0042542a:
        mov esi,dword ptr [edi+3D0h]
    L_00425430:
        mov dword ptr [edi+3F4h],eax
    L_00425436:
        mov eax,dword ptr [edi+3CCh]
    L_0042543c:
        mov edx,dword ptr [edi+3F4h]
    L_00425442:
        add eax,ecx
    L_00425444:
        add esi,edx
    L_00425446:
        cmp eax,0FFFFB820h
    L_0042544b:
        mov dword ptr [edi+3CCh],eax
    L_00425451:
        mov dword ptr [edi+3D0h],esi
    L_00425457:
        mov ecx,esi
    L_00425459:
        jge short L_00425467
    L_0042545b:
        mov dword ptr [edi+3CCh],0FFFFB820h
    L_00425465:
        jmp short L_00425478
    L_00425467:
        cmp eax,47E0h
    L_0042546c:
        jle short L_00425478
    L_0042546e:
        mov dword ptr [edi+3CCh],47E0h
    L_00425478:
        cmp ecx,0C80h
    L_0042547e:
        jge short L_0042548c
    L_00425480:
        mov dword ptr [edi+3D0h],0C80h
    L_0042548a:
        jmp short L_0042549e
    L_0042548c:
        cmp ecx,0A8C0h
    L_00425492:
        jle short L_0042549e
    L_00425494:
        mov dword ptr [edi+3D0h],0A8C0h
    L_0042549e:
        fild dword ptr [edi+3CCh]
    L_004254a4:
        mov edx,dword ptr [data_00491c10]
    L_004254aa:
        fmul dword ptr [data_00470b00]
    L_004254b0:
        fstp dword ptr [edi+3C0h]
    L_004254b6:
        fild dword ptr [edi+3D0h]
    L_004254bc:
        fmul dword ptr [data_00470b00]
    L_004254c2:
        fstp dword ptr [edi+3C4h]
    L_004254c8:
        mov eax,dword ptr [edi+329Ch]
    L_004254ce:
        push eax
    L_004254cf:
        call asm_AnimationManager_Find_004491c0
    L_004254d4:
        test eax,eax
    L_004254d6:
        jne short L_004254e0
    L_004254d8:
        mov dword ptr [edi+329Ch],eax
    L_004254de:
        jmp short L_00425520
    L_004254e0:
        fld dword ptr [edi+3C0h]
    L_004254e6:
        mov edx,dword ptr [edi+329Ch]
    L_004254ec:
        fadd dword ptr [data_00470b4c]
    L_004254f2:
        mov ecx,dword ptr [edi+3C8h]
    L_004254f8:
        push edx
    L_004254f9:
        mov edx,dword ptr [data_00491c10]
    L_004254ff:
        fstp dword ptr [esp+1Ch]
    L_00425503:
        lea esi,[esp+1Ch]
    L_00425507:
        fld dword ptr [edi+3C4h]
    L_0042550d:
        mov dword ptr [esp+24h],ecx
    L_00425511:
        fadd dword ptr [data_00470b48]
    L_00425517:
        fstp dword ptr [esp+20h]
    L_0042551b:
        call asm_AnimationManager_SetPosition_004492f0
    L_00425520:
        mov eax,dword ptr [edi+4474h]
    L_00425526:
        test eax,eax
    L_00425528:
        TH10_REL8(0x75, 0x00425528, VA_asm_target_004255a1)
    L_0042552a:
        test ebx,ebx
    L_0042552c:
        jne short L_00425532
    L_0042552e:
        test ebp,ebp
    L_00425530:
        TH10_REL8(0x74, 0x00425530, VA_asm_target_004255a1)
    L_00425532:
        mov ecx,dword ptr [edi+3500h]
    L_00425538:
        mov eax,20h
    L_0042553d:
        shl ecx,3
    L_00425540:
        cmp ecx,eax
    L_00425542:
        jge short L_00425584
    L_00425544:
        lea ecx,[edi+446Ch]
    L_0042554a:
        lea ebx,[ebx+force_disp32_zero]
    L_00425550:
        mov edx,dword ptr [edi+3500h]
    L_00425556:
        shl edx,6
    L_00425559:
        mov esi,dword ptr [edx+edi+436Ch]
    L_00425560:
        lea edx,[edx+edi+436Ch]
    L_00425567:
        mov dword ptr [ecx],esi
    L_00425569:
        mov edx,dword ptr [edx+4]
    L_0042556c:
        mov dword ptr [ecx+4],edx
    L_0042556f:
        mov edx,dword ptr [edi+3500h]
    L_00425575:
        dec eax
    L_00425576:
        shl edx,3
    L_00425579:
        sub ecx,8
    L_0042557c:
        cmp eax,edx
    L_0042557e:
        jg short L_00425550
    L_00425580:
        test eax,eax
    L_00425582:
        TH10_REL8(0x7e, 0x00425582, VA_asm_target_004255a1)
    L_00425584:
        lea ecx,[edi+eax*8+4370h]
    L_0042558b:
        TH10_REL8(0xeb, 0x0042558b, VA_asm_FUN_004250b0_part_00425590)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00425590:
        mov edx,dword ptr [ecx-0Ch]
    L_00425593:
        mov dword ptr [ecx-4],edx
    L_00425596:
        mov edx,dword ptr [ecx-8]
    L_00425599:
        mov dword ptr [ecx],edx
    L_0042559b:
        add ecx,0FFFFFFF8h
    L_0042559e:
        dec eax
    L_0042559f:
        jne short L_00425590
    L_004255a1:
        mov eax,dword ptr [edi+3CCh]
    L_004255a7:
        mov dword ptr [edi+436Ch],eax
    L_004255ad:
        mov ecx,dword ptr [edi+3D0h]
    L_004255b3:
        mov dword ptr [edi+4370h],ecx
    L_004255b9:
        lea ebx,[edi+32E0h]
    L_004255bf:
        mov dword ptr [esp+10h],4
    L_004255c7:
        mov eax,dword ptr [ebx-40h]
    L_004255ca:
        test eax,eax
    L_004255cc:
        lea ecx,[ebx-40h]
    L_004255cf:
        je asm_target_004256c9
    L_004255d5:
        mov eax,dword ptr [edi+4474h]
    L_004255db:
        test eax,eax
    L_004255dd:
        lea esi,[ebx+0Ch]
    L_004255e0:
        jne short L_004255e5
    L_004255e2:
        lea esi,[ebx+4]
    L_004255e5:
        mov edx,dword ptr [edi+3CCh]
    L_004255eb:
        mov eax,dword ptr [esi]
    L_004255ed:
        mov ebp,dword ptr [esi+4]
    L_004255f0:
        add eax,edx
    L_004255f2:
        mov edx,dword ptr [edi+3D0h]
    L_004255f8:
        add edx,ebp
    L_004255fa:
        mov dword ptr [ebx-0Ch],eax
    L_004255fd:
        mov dword ptr [ebx-8],edx
    L_00425600:
        mov eax,dword ptr [ebx+50h]
    L_00425603:
        test eax,eax
    L_00425605:
        je short L_00425609
    L_00425607:
        call eax
    L_00425609:
        mov eax,dword ptr [ebx+4Ch]
    L_0042560c:
        test eax,eax
    L_0042560e:
        jne short L_00425676
    L_00425610:
        mov edx,dword ptr [edi+4308h]
    L_00425616:
        cmp edx,1Eh
    L_00425619:
        jl short L_00425688
    L_0042561b:
        mov ebp,dword ptr [ebx-0Ch]
    L_0042561e:
        mov ecx,dword ptr [ebx-4]
    L_00425621:
        mov esi,dword ptr [ebx]
    L_00425623:
        mov eax,ebp
    L_00425625:
        sub eax,ecx
    L_00425627:
        mov ecx,dword ptr [ebx-8]
    L_0042562a:
        imul eax,edx
    L_0042562d:
        sub ecx,esi
    L_0042562f:
        mov esi,eax
    L_00425631:
        imul ecx,edx
    L_00425634:
        mov eax,51EB851Fh
    L_00425639:
        imul esi
    L_0042563b:
        sar edx,5
    L_0042563e:
        mov esi,edx
    L_00425640:
        shr esi,1Fh
    L_00425643:
        add esi,edx
    L_00425645:
        mov eax,51EB851Fh
    L_0042564a:
        imul ecx
    L_0042564c:
        sar edx,5
    L_0042564f:
        mov eax,edx
    L_00425651:
        shr eax,1Fh
    L_00425654:
        add eax,edx
    L_00425656:
        test esi,esi
    L_00425658:
        jne short L_0042565e
    L_0042565a:
        test eax,eax
    L_0042565c:
        je short L_0042566c
    L_0042565e:
        mov edx,dword ptr [ebx-4]
    L_00425661:
        mov ecx,dword ptr [ebx]
    L_00425663:
        add edx,esi
    L_00425665:
        mov dword ptr [ebx-4],edx
    L_00425668:
        add ecx,eax
    L_0042566a:
        jmp short L_00425686
    L_0042566c:
        mov dword ptr [ebx-4],ebp
    L_0042566f:
        mov edx,dword ptr [ebx-8]
    L_00425672:
        mov dword ptr [ebx],edx
    L_00425674:
        jmp short L_00425688
    L_00425676:
        mov dword ptr [ebx+4Ch],0
    L_0042567d:
        mov eax,dword ptr [ebx-0Ch]
    L_00425680:
        mov dword ptr [ebx-4],eax
    L_00425683:
        mov ecx,dword ptr [ebx-8]
    L_00425686:
        mov dword ptr [ebx],ecx
    L_00425688:
        fild dword ptr [ebx-4]
    L_0042568b:
        mov edx,dword ptr [ebx+28h]
    L_0042568e:
        mov ebp,dword ptr [data_00491c10]
    L_00425694:
        push edx
    L_00425695:
        fmul dword ptr [data_00470b00]
    L_0042569b:
        lea esi,[esp+1Ch]
    L_0042569f:
        mov edx,ebp
    L_004256a1:
        mov dword ptr [esp+24h],0
    L_004256a9:
        fstp dword ptr [esp+1Ch]
    L_004256ad:
        fild dword ptr [ebx]
    L_004256af:
        fmul dword ptr [data_00470b00]
    L_004256b5:
        fstp dword ptr [esp+20h]
    L_004256b9:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_004256be:
        mov eax,dword ptr [ebx+2Ch]
    L_004256c1:
        push eax
    L_004256c2:
        mov edx,ebp
    L_004256c4:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_004256c9:
        mov eax,dword ptr [esp+10h]
    L_004256cd:
        add ebx,98h
    L_004256d3:
        dec eax
    L_004256d4:
        mov dword ptr [esp+10h],eax
    L_004256d8:
        jne asm_target_004255c7
    L_004256de:
        pop esi
    L_004256df:
        pop ebp
    L_004256e0:
        xor eax,eax
    L_004256e2:
        pop ebx
    L_004256e3:
        add esp,18h
    L_004256e6:
        ret
        _emit 0x90
        _emit 0x7a
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0x8b
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0x6d
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0x62
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0x9a
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0xb6
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0xa7
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0xc5
        _emit 0x52
        _emit 0x42
        _emit 0x00
        _emit 0x2b
        _emit 0x53
        _emit 0x42
        _emit 0x00
        _emit 0x39
        _emit 0x53
        _emit 0x42
        _emit 0x00
        _emit 0x21
        _emit 0x53
        _emit 0x42
        _emit 0x00
        _emit 0x19
        _emit 0x53
        _emit 0x42
        _emit 0x00
        _emit 0x45
        _emit 0x53
        _emit 0x42
        _emit 0x00
        _emit 0x5b
        _emit 0x53
        _emit 0x42
        _emit 0x00
        _emit 0x4f
        _emit 0x53
        _emit 0x42
        _emit 0x00
        _emit 0x67
        _emit 0x53
        _emit 0x42
        _emit 0x00
    }
}
