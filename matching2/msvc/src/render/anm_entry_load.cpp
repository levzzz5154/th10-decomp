#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447470..0x004475E6: FUN_00447470
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447470_00447470() {
    __asm {
    L_00447470:
        sub esp,68h
    L_00447473:
        push ebp
    L_00447474:
        mov ebp,dword ptr [esp+80h]
    L_0044747b:
        test ebp,ebp
    L_0044747d:
        push edi
    L_0044747e:
        jne short L_00447487
    L_00447480:
        push 470274h
    L_00447485:
        jmp short L_00447492
    L_00447487:
        cmp dword ptr [ebp+28h],4
    L_0044748b:
        je short L_004474aa
    L_0044748d:
        push 470254h
    L_00447492:
        mov edi,474F70h
    L_00447497:
        call asm_TextLog_AppendLine_0044b8e0
    L_0044749c:
        add esp,4
    L_0044749f:
        pop edi
    L_004474a0:
        or eax,0FFFFFFFFh
    L_004474a3:
        pop ebp
    L_004474a4:
        add esp,68h
    L_004474a7:
        ret 14h
    L_004474aa:
        mov cl,byte ptr [ebp+34h]
    L_004474ad:
        shl eax,4
    L_004474b0:
        test cl,cl
    L_004474b2:
        push ebx
    L_004474b3:
        push esi
    L_004474b4:
        mov dword ptr [esp+8Ch],eax
    L_004474bb:
        jne short L_0044753a
    L_004474bd:
        mov edi,dword ptr [ebp+1Ch]
    L_004474c0:
        mov cl,byte ptr [edi+ebp]
    L_004474c3:
        add edi,ebp
    L_004474c5:
        cmp cl,40h
    L_004474c8:
        jne short L_004474ec
    L_004474ca:
        mov ebx,dword ptr [esp+80h]
    L_004474d1:
        mov edi,dword ptr [ebx+120h]
    L_004474d7:
        mov esi,dword ptr [ebp+14h]
    L_004474da:
        mov ecx,dword ptr [ebp+10h]
    L_004474dd:
        mov edx,dword ptr [ebp+0Ch]
    L_004474e0:
        add edi,eax
    L_004474e2:
        call asm_AnimationTexture_Create_00447050
    L_004474e7:
        jmp asm_target_00447588
    L_004474ec:
        mov ecx,dword ptr [ebp+0Ch]
    L_004474ef:
        mov edx,dword ptr [ebp+18h]
    L_004474f2:
        push ecx
    L_004474f3:
        mov ecx,dword ptr [esp+84h]
    L_004474fa:
        mov esi,dword ptr [ecx+120h]
    L_00447500:
        push edx
    L_00447501:
        mov edx,dword ptr [esp+84h]
    L_00447508:
        add esi,eax
    L_0044750a:
        mov eax,dword ptr [ebp+14h]
    L_0044750d:
        push edx
    L_0044750e:
        mov edx,dword ptr [ebp+10h]
    L_00447511:
        call asm_Recovery_CreateTextureFromMemory_00446eb0
    L_00447516:
        test eax,eax
    L_00447518:
        je short L_00447581
    L_0044751a:
        push edi
    L_0044751b:
        push 4701B0h
    L_00447520:
        mov edi,474F70h
    L_00447525:
        call asm_TextLog_AppendLine_0044b8e0
    L_0044752a:
        add esp,8
    L_0044752d:
        pop esi
    L_0044752e:
        pop ebx
    L_0044752f:
        pop edi
    L_00447530:
        or eax,0FFFFFFFFh
    L_00447533:
        pop ebp
    L_00447534:
        add esp,68h
    L_00447537:
        ret 14h
    L_0044753a:
        mov ecx,dword ptr [ebp+10h]
    L_0044753d:
        mov edx,dword ptr [ebp+0Ch]
    L_00447540:
        push ecx
    L_00447541:
        mov ecx,dword ptr [ebp+30h]
    L_00447544:
        push edx
    L_00447545:
        mov edx,dword ptr [esp+88h]
    L_0044754c:
        mov ebx,dword ptr [edx+120h]
    L_00447552:
        add ebx,eax
    L_00447554:
        mov eax,dword ptr [ebp+14h]
    L_00447557:
        add ecx,ebp
    L_00447559:
        call asm_AnmTexture_CreateAndUploadRetail_00446f40
    L_0044755e:
        test eax,eax
    L_00447560:
        je short L_00447581
    L_00447562:
        push 47016Ch
    L_00447567:
        mov edi,474F70h
    L_0044756c:
        call asm_TextLog_AppendLine_0044b8e0
    L_00447571:
        add esp,4
    L_00447574:
        pop esi
    L_00447575:
        pop ebx
    L_00447576:
        pop edi
    L_00447577:
        or eax,0FFFFFFFFh
    L_0044757a:
        pop ebp
    L_0044757b:
        add esp,68h
    L_0044757e:
        ret 14h
    L_00447581:
        mov ebx,dword ptr [esp+80h]
    L_00447588:
        mov eax,dword ptr [ebx+120h]
    L_0044758e:
        mov edx,dword ptr [ebp+2Ch]
    L_00447591:
        mov edi,dword ptr [esp+8Ch]
    L_00447598:
        mov eax,dword ptr [edi+eax]
    L_0044759b:
        mov ecx,dword ptr [eax]
    L_0044759d:
        push edx
    L_0044759e:
        push eax
    L_0044759f:
        call dword ptr [ecx+1Ch]
    L_004475a2:
        mov eax,dword ptr [ebx+120h]
    L_004475a8:
        mov eax,dword ptr [edi+eax]
    L_004475ab:
        mov ecx,dword ptr [eax]
    L_004475ad:
        push eax
    L_004475ae:
        call dword ptr [ecx+24h]
    L_004475b1:
        mov edx,dword ptr [ebx+120h]
    L_004475b7:
        mov eax,dword ptr [edi+edx]
    L_004475ba:
        mov ecx,dword ptr [eax]
    L_004475bc:
        lea edx,[esp+14h]
    L_004475c0:
        push edx
    L_004475c1:
        push 0
    L_004475c3:
        push eax
    L_004475c4:
        call dword ptr [ecx+44h]
    L_004475c7:
        cmp dword ptr [ebp],0
    L_004475cb:
        lea esi,[ebp+40h]
    L_004475ce:
        mov dword ptr [esp+7Ch],0
    L_004475d6:
        jle asm_target_004476b8
    L_004475dc:
        TH10_REL8(0xeb, 0x004475dc, VA_asm_FUN_00447470_part_004475f0)
    L_004475de:
        mov edi,dword ptr [esp+8Ch]
    L_004475e5:
        TH10_REL8(0xeb, 0x004475e5, VA_asm_FUN_00447470_part_004475f0)
    }
}

// 0x004475F0..0x004476F9: FUN_00447470
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00447470_part_004475f0() {
    __asm {
    L_004475f0:
        mov ecx,dword ptr [ebx]
    L_004475f2:
        fild dword ptr [esp+2Ch]
    L_004475f6:
        mov edx,dword ptr [ebx+120h]
    L_004475fc:
        mov eax,dword ptr [esi]
    L_004475fe:
        mov dword ptr [esp+34h],ecx
    L_00447602:
        mov ecx,dword ptr [edi+edx]
    L_00447605:
        mov edx,dword ptr [esp+2Ch]
    L_00447609:
        add eax,ebp
    L_0044760b:
        test edx,edx
    L_0044760d:
        mov dword ptr [esp+38h],ecx
    L_00447611:
        jge short L_00447619
    L_00447613:
        fadd dword ptr [data_00470b98]
    L_00447619:
        fild dword ptr [ebp+0Ch]
    L_0044761c:
        mov ecx,dword ptr [esp+30h]
    L_00447620:
        test ecx,ecx
    L_00447622:
        fdivr st,st(1)
    L_00447624:
        fstp dword ptr [esp+6Ch]
    L_00447628:
        fild dword ptr [esp+30h]
    L_0044762c:
        jge short L_00447634
    L_0044762e:
        fadd dword ptr [data_00470b98]
    L_00447634:
        fild dword ptr [ebp+10h]
    L_00447637:
        mov edi,dword ptr [esp+84h]
    L_0044763e:
        mov edx,dword ptr [esp+80h]
    L_00447645:
        lea ebx,[esp+34h]
    L_00447649:
        fdivr st,st(1)
    L_0044764b:
        fstp dword ptr [esp+70h]
    L_0044764f:
        fld dword ptr [esp+6Ch]
    L_00447653:
        fmul dword ptr [eax+4]
    L_00447656:
        fstp dword ptr [esp+3Ch]
    L_0044765a:
        fld dword ptr [esp+70h]
    L_0044765e:
        fmul dword ptr [eax+8]
    L_00447661:
        fstp dword ptr [esp+40h]
    L_00447665:
        fld dword ptr [eax+0Ch]
    L_00447668:
        fadd dword ptr [eax+4]
    L_0044766b:
        fmul dword ptr [esp+6Ch]
    L_0044766f:
        fstp dword ptr [esp+44h]
    L_00447673:
        fld dword ptr [eax+10h]
    L_00447676:
        fadd dword ptr [eax+8]
    L_00447679:
        mov eax,edi
    L_0044767b:
        fmul dword ptr [esp+70h]
    L_0044767f:
        fstp dword ptr [esp+48h]
    L_00447683:
        fxch
    L_00447685:
        fstp dword ptr [esp+50h]
    L_00447689:
        fstp dword ptr [esp+4Ch]
    L_0044768d:
        call asm_AnimationManager_CopyPositionRecord_00447940
    L_00447692:
        mov eax,dword ptr [esp+7Ch]
    L_00447696:
        mov ecx,dword ptr [ebp]
    L_00447699:
        mov ebx,dword ptr [esp+80h]
    L_004476a0:
        inc edi
    L_004476a1:
        inc eax
    L_004476a2:
        add esi,4
    L_004476a5:
        cmp eax,ecx
    L_004476a7:
        mov dword ptr [esp+84h],edi
    L_004476ae:
        mov dword ptr [esp+7Ch],eax
    L_004476b2:
        jl asm_target_004475de
    L_004476b8:
        mov eax,dword ptr [ebp+4]
    L_004476bb:
        xor edx,edx
    L_004476bd:
        test eax,eax
    L_004476bf:
        jle short L_004476eb
    L_004476c1:
        mov eax,dword ptr [esp+88h]
    L_004476c8:
        shl eax,2
    L_004476cb:
        lea ecx,[esi+4]
    L_004476ce:
        mov edi,edi
    L_004476d0:
        mov esi,dword ptr [ecx]
    L_004476d2:
        mov edi,dword ptr [ebx+11Ch]
    L_004476d8:
        add esi,ebp
    L_004476da:
        mov dword ptr [eax+edi],esi
    L_004476dd:
        mov esi,dword ptr [ebp+4]
    L_004476e0:
        add eax,4
    L_004476e3:
        inc edx
    L_004476e4:
        add ecx,8
    L_004476e7:
        cmp edx,esi
    L_004476e9:
        jl short L_004476d0
    L_004476eb:
        pop esi
    L_004476ec:
        pop ebx
    L_004476ed:
        pop edi
    L_004476ee:
        mov eax,1
    L_004476f3:
        pop ebp
    L_004476f4:
        add esp,68h
    L_004476f7:
        ret 14h
    }
}
