#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00406240..0x004065B4: FUN_00406240
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00406240_00406240() {
    __asm {
    L_00406240:
        sub esp,18h
    L_00406243:
        push ebp
    L_00406244:
        mov ebp,dword ptr [esp+20h]
    L_00406248:
        test byte ptr [ebp],8
    L_0040624c:
        je short L_0040625f
    L_0040624e:
        mov eax,ebp
    L_00406250:
        call asm_Player_ResetSchedulerLinksRetail_00405be0
    L_00406255:
        or eax,0FFFFFFFFh
    L_00406258:
        pop ebp
    L_00406259:
        add esp,18h
    L_0040625c:
        ret 4
    L_0040625f:
        movzx eax,word ptr [ebp+446h]
    L_00406266:
        dec eax
    L_00406267:
        push ebx
    L_00406268:
        mov ebx,1
    L_0040626d:
        je asm_target_00406373
    L_00406273:
        dec eax
    L_00406274:
        je short L_004062f0
    L_00406276:
        dec eax
    L_00406277:
        jne asm_target_0040651b
    L_0040627d:
        fld dword ptr [data_00476f78]
    L_00406283:
        fmul dword ptr [ebp+3C0h]
    L_00406289:
        fld dword ptr [data_00476f78]
    L_0040628f:
        fmul dword ptr [ebp+3C4h]
    L_00406295:
        fld dword ptr [data_00476f78]
    L_0040629b:
        fmul dword ptr [ebp+3C8h]
    L_004062a1:
        fstp dword ptr [esp+10h]
    L_004062a5:
        fxch
    L_004062a7:
        fmul dword ptr [data_00470b0c]
    L_004062ad:
        fstp dword ptr [esp+14h]
    L_004062b1:
        fmul dword ptr [data_00470b0c]
    L_004062b7:
        fld dword ptr [esp+10h]
    L_004062bb:
        fmul dword ptr [data_00470b0c]
    L_004062c1:
        fld dword ptr [esp+14h]
    L_004062c5:
        fadd dword ptr [ebp+3B4h]
    L_004062cb:
        fstp dword ptr [ebp+3B4h]
    L_004062d1:
        fxch
    L_004062d3:
        fadd dword ptr [ebp+3B8h]
    L_004062d9:
        fstp dword ptr [ebp+3B8h]
    L_004062df:
        fadd dword ptr [ebp+3BCh]
    L_004062e5:
        fstp dword ptr [ebp+3BCh]
    L_004062eb:
        jmp asm_target_0040651b
    L_004062f0:
        fld dword ptr [data_00476f78]
    L_004062f6:
        fmul dword ptr [ebp+3C0h]
    L_004062fc:
        fld dword ptr [data_00476f78]
    L_00406302:
        fmul dword ptr [ebp+3C4h]
    L_00406308:
        fld dword ptr [data_00476f78]
    L_0040630e:
        fmul dword ptr [ebp+3C8h]
    L_00406314:
        fstp dword ptr [esp+1Ch]
    L_00406318:
        fxch
    L_0040631a:
        fmul dword ptr [data_00470b0c]
    L_00406320:
        fstp dword ptr [esp+8]
    L_00406324:
        fmul dword ptr [data_00470b0c]
    L_0040632a:
        fld dword ptr [esp+1Ch]
    L_0040632e:
        fmul dword ptr [data_00470b0c]
    L_00406334:
        fld dword ptr [esp+8]
    L_00406338:
        fadd dword ptr [ebp+3B4h]
    L_0040633e:
        fstp dword ptr [ebp+3B4h]
    L_00406344:
        fxch
    L_00406346:
        fadd dword ptr [ebp+3B8h]
    L_0040634c:
        fstp dword ptr [ebp+3B8h]
    L_00406352:
        fadd dword ptr [ebp+3BCh]
    L_00406358:
        fstp dword ptr [ebp+3BCh]
    L_0040635e:
        mov eax,dword ptr [ebp+314h]
    L_00406364:
        test eax,eax
    L_00406366:
        je asm_target_0040651b
    L_0040636c:
        mov word ptr [ebp+446h],bx
    L_00406373:
        push esi
    L_00406374:
        mov ecx,ebp
    L_00406376:
        call asm_FUN_00406d90_00406d90
    L_0040637b:
        mov eax,dword ptr [ebp+43Ch]
    L_00406381:
        test eax,eax
    L_00406383:
        je asm_target_0040643e
    L_00406389:
        test al,bl
    L_0040638b:
        je short L_00406394
    L_0040638d:
        mov esi,ebp
    L_0040638f:
        call asm_PlayerAnimation_AdvanceFrame_004074b0
    L_00406394:
        test byte ptr [ebp+43Ch],10h
    L_0040639b:
        je short L_004063a4
    L_0040639d:
        mov esi,ebp
    L_0040639f:
        call asm_FUN_00407560_00407560
    L_004063a4:
        test byte ptr [ebp+43Ch],20h
    L_004063ab:
        je short L_004063b4
    L_004063ad:
        mov esi,ebp
    L_004063af:
        call asm_Player_DeathShrink_004076a0
    L_004063b4:
        test byte ptr [ebp+43Ch],40h
    L_004063bb:
        je short L_004063c4
    L_004063bd:
        mov esi,ebp
    L_004063bf:
        call asm_FUN_00407780_00407780
    L_004063c4:
        mov eax,dword ptr [ebp+43Ch]
    L_004063ca:
        test ah,1
    L_004063cd:
        je short L_004063d6
    L_004063cf:
        mov esi,ebp
    L_004063d1:
        call asm_FUN_004078e0_004078e0
    L_004063d6:
        mov al,byte ptr [ebp+43Ch]
    L_004063dc:
        test al,al
    L_004063de:
        jns short L_004063e7
    L_004063e0:
        mov esi,ebp
    L_004063e2:
        call asm_FUN_00407a30_00407a30
    L_004063e7:
        test dword ptr [ebp+43Ch],8000C00h
    L_004063f1:
        je short L_004063fa
    L_004063f3:
        mov esi,ebp
    L_004063f5:
        call asm_FUN_00407be0_00407be0
    L_004063fa:
        test dword ptr [ebp+43Ch],4000000h
    L_00406404:
        je short L_0040640d
    L_00406406:
        mov esi,ebp
    L_00406408:
        call asm_FUN_00407ef0_00407ef0
    L_0040640d:
        mov eax,dword ptr [ebp+43Ch]
    L_00406413:
        test ah,ah
    L_00406415:
        jns short L_0040643e
    L_00406417:
        mov ecx,dword ptr [ebp+71Ch]
    L_0040641d:
        test ecx,ecx
    L_0040641f:
        jg short L_0040642e
    L_00406421:
        xor eax,8000h
    L_00406426:
        mov dword ptr [ebp+43Ch],eax
    L_0040642c:
        jmp short L_0040643e
    L_0040642e:
        push 0BF800000h
    L_00406433:
        lea esi,[ebp+718h]
    L_00406439:
        call asm_FrameTimer_Advance_0044bf40
    L_0040643e:
        fld dword ptr [data_00476f78]
    L_00406444:
        push edi
    L_00406445:
        fmul dword ptr [ebp+3C0h]
    L_0040644b:
        lea edi,[ebp+3B4h]
    L_00406451:
        fld dword ptr [data_00476f78]
    L_00406457:
        fmul dword ptr [ebp+3C4h]
    L_0040645d:
        fld dword ptr [data_00476f78]
    L_00406463:
        fmul dword ptr [ebp+3C8h]
    L_00406469:
        fstp dword ptr [esp+24h]
    L_0040646d:
        fxch
    L_0040646f:
        fadd dword ptr [edi]
    L_00406471:
        fstp dword ptr [edi]
    L_00406473:
        fadd dword ptr [edi+4]
    L_00406476:
        fstp dword ptr [edi+4]
    L_00406479:
        fld dword ptr [esp+24h]
    L_0040647d:
        fadd dword ptr [edi+8]
    L_00406480:
        fstp dword ptr [edi+8]
    L_00406483:
        mov al,byte ptr [ebp]
    L_00406486:
        test al,2
    L_00406488:
        je L_00406519
    L_0040648e:
        mov edx,dword ptr [data_00477834]
    L_00406494:
        lea eax,[ebp+3F0h]
    L_0040649a:
        mov ecx,edi
    // Explicit stack arguments replace the retail EAX/ECX/EDX private ABI.
    L_0040649c:
        push edx
        push eax
        push ecx
        call asm_FUN_004266b0_004266b0
        add esp,0Ch
    L_item_field_contact_result_004064a1:
        cmp eax,ebx
    L_004064a3:
        jne short L_004064d9
    L_004064a5:
        mov eax,dword ptr [ebp+438h]
    L_004064ab:
        test eax,eax
    L_004064ad:
        mov word ptr [ebp+446h],3
    L_004064b6:
        mov word ptr [ebp+30Ch],bx
    L_004064bd:
        jl short L_00406519
    L_004064bf:
        mov ecx,dword ptr [data_004776f0]
    L_004064c5:
        mov edx,dword ptr [ecx+3E0B50h]
    L_004064cb:
        push eax
    L_004064cc:
        lea eax,[esp+30h]
    L_004064d0:
        push eax
    L_004064d1:
        push edx
    L_004064d2:
        call asm_PlayerAnimation_Create_00448db0
    L_004064d7:
        jmp short L_00406519
    L_004064d9:
        cmp eax,2
    L_004064dc:
        jne short L_00406519
    L_004064de:
        mov eax,dword ptr [ebp]
    L_004064e1:
        test al,4
    L_004064e3:
        jne short L_00406519
    L_004064e5:
        mov ecx,dword ptr [data_004776f0]
    L_004064eb:
        or eax,4
    L_004064ee:
        mov dword ptr [ebp],eax
    L_004064f1:
        mov edx,dword ptr [ecx+3E0B50h]
    L_004064f7:
        push 1B2h
    L_004064fc:
        lea eax,[esp+30h]
    L_00406500:
        push eax
    L_00406501:
        push edx
    L_00406502:
        call asm_PlayerAnimation_Create_00448db0
    L_00406507:
        mov eax,dword ptr [edi]
    L_00406509:
        push eax
    L_0040650a:
        mov ebx,1Ch
    L_0040650f:
        mov esi,492590h
    L_00406514:
        call asm_FUN_0043dd10_0043dd10
    L_00406519:
        pop edi
    L_0040651a:
        pop esi
    L_0040651b:
        mov eax,dword ptr [ebp+39Ch]
    L_00406521:
        test eax,eax
    L_00406523:
        je short L_00406584
    L_00406525:
        test dword ptr [ebp+43Ch],100000h
    L_0040652f:
        je short L_00406538
    L_00406531:
        mov ebx,ebp
    L_00406533:
        call asm_Player_WrapHorizontal_00407da0
    L_00406538:
        test dword ptr [ebp+43Ch],200000h
    L_00406542:
        je short L_0040654b
    L_00406544:
        mov ebx,ebp
    L_00406546:
        call asm_Player_WrapVertical_00407e40
    L_0040654b:
        mov eax,dword ptr [ebp+434h]
    L_00406551:
        test eax,eax
    L_00406553:
        jg short L_00406584
    L_00406555:
        mov eax,dword ptr [ebp+39Ch]
    L_0040655b:
        mov ecx,dword ptr [eax+30h]
    L_0040655e:
        mov edx,dword ptr [eax+34h]
    L_00406561:
        push ecx
    L_00406562:
        push edx
    L_00406563:
        lea ecx,[ebp+3B4h]
    L_00406569:
        call asm_Entity_PointWithinBounds_00406160
    L_0040656e:
        test eax,eax
    L_00406570:
        je short L_00406584
    L_00406572:
        mov eax,ebp
    L_00406574:
        call asm_Player_ResetSchedulerLinksRetail_00405be0
    L_00406579:
        pop ebx
    L_0040657a:
        or eax,0FFFFFFFFh
    L_0040657d:
        pop ebp
    L_0040657e:
        add esp,18h
    L_00406581:
        ret 4
    L_00406584:
        mov eax,dword ptr [ebp+4]
    L_00406587:
        test eax,eax
    L_00406589:
        je short L_0040658f
    L_0040658b:
        dec eax
    L_0040658c:
        mov dword ptr [ebp+4],eax
    L_0040658f:
        mov eax,dword ptr [ebp+434h]
    L_00406595:
        test eax,eax
    L_00406597:
        jle short L_004065a0
    L_00406599:
        dec eax
    L_0040659a:
        mov dword ptr [ebp+434h],eax
    L_004065a0:
        lea eax,[ebp+8]
    L_004065a3:
        push eax
    L_004065a4:
        call asm_FUN_0043ee30_0043ee30
    L_004065a9:
        test eax,eax
    L_004065ab:
        jne short L_00406572
    L_004065ad:
        pop ebx
    L_004065ae:
        pop ebp
    L_004065af:
        add esp,18h
    L_004065b2:
        ret 4
    }
}
