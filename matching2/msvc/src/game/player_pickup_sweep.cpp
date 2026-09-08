#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428630..0x00428AC1: FUN_00428630
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428630_00428630() {
    __asm {
    L_00428630:
        sub esp,40h
    L_00428633:
        push ebp
    L_00428634:
        mov ebp,dword ptr [esp+48h]
    L_00428638:
        mov eax,dword ptr [ebp+478h]
    L_0042863e:
        cmp eax,dword ptr [ebp+474h]
    L_00428644:
        mov dword ptr [esp+48h],0
    L_0042864c:
        jne short L_00428657
    L_0042864e:
        xor eax,eax
    L_00428650:
        pop ebp
    L_00428651:
        add esp,40h
    L_00428654:
        ret 0Ch
    L_00428657:
        test ecx,ecx
    L_00428659:
        mov eax,dword ptr [esp+50h]
    L_0042865d:
        fld dword ptr [eax]
    L_0042865f:
        push ebx
    L_00428660:
        fmul dword ptr [data_00470b0c]
    L_00428666:
        push esi
    L_00428667:
        push edi
    L_00428668:
        mov edi,dword ptr [esp+58h]
    L_0042866c:
        fld dword ptr [edi]
    L_0042866e:
        lea ebx,[ebp+49Ch]
    L_00428674:
        fsub st,st(1)
    L_00428676:
        mov dword ptr [esp+10h],ebx
    L_0042867a:
        fstp dword ptr [esp+38h]
    L_0042867e:
        fld dword ptr [eax+4]
    L_00428681:
        fmul dword ptr [data_00470b0c]
    L_00428687:
        fld dword ptr [edi+4]
    L_0042868a:
        fsub st,st(1)
    L_0042868c:
        fstp dword ptr [esp+3Ch]
    L_00428690:
        fxch
    L_00428692:
        fadd dword ptr [edi]
    L_00428694:
        fstp dword ptr [esp+2Ch]
    L_00428698:
        fadd dword ptr [edi+4]
    L_0042869b:
        fstp dword ptr [esp+30h]
    L_0042869f:
        je short L_004286a7
    L_004286a1:
        mov dword ptr [ecx],0
    L_004286a7:
        lea esi,[ebx+44h]
    L_004286aa:
        mov dword ptr [esp+14h],80h
    L_004286b2:
        mov eax,dword ptr [esi-4]
    L_004286b5:
        test eax,eax
    L_004286b7:
        je asm_target_0042886c
    L_004286bd:
        cmp eax,2
    L_004286c0:
        je asm_target_0042886c
    L_004286c6:
        mov ecx,dword ptr [esi+14h]
    L_004286c9:
        fld dword ptr [ecx+0Ch]
    L_004286cc:
        fmul dword ptr [data_00470b0c]
    L_004286d2:
        fld dword ptr [esi-30h]
    L_004286d5:
        fsub st,st(1)
    L_004286d7:
        fstp dword ptr [esp+44h]
    L_004286db:
        fld dword ptr [ecx+10h]
    L_004286de:
        fmul dword ptr [data_00470b0c]
    L_004286e4:
        fld dword ptr [esi-2Ch]
    L_004286e7:
        fsub st,st(1)
    L_004286e9:
        fstp dword ptr [esp+48h]
    L_004286ed:
        fxch
    L_004286ef:
        fadd dword ptr [esi-30h]
    L_004286f2:
        fstp dword ptr [esp+20h]
    L_004286f6:
        fadd dword ptr [esi-2Ch]
    L_004286f9:
        fld dword ptr [esp+48h]
    L_004286fd:
        fcomp dword ptr [esp+30h]
    L_00428701:
        fnstsw ax
    L_00428703:
        test ah,41h
    L_00428706:
        je asm_target_0042894d
    L_0042870c:
        fld dword ptr [esp+44h]
    L_00428710:
        fcomp dword ptr [esp+2Ch]
    L_00428714:
        fnstsw ax
    L_00428716:
        test ah,41h
    L_00428719:
        je asm_target_0042894d
    L_0042871f:
        fcomp dword ptr [esp+3Ch]
    L_00428723:
        fnstsw ax
    L_00428725:
        test ah,5
    L_00428728:
        jnp asm_target_0042886c
    L_0042872e:
        fld dword ptr [esp+20h]
    L_00428732:
        fcomp dword ptr [esp+38h]
    L_00428736:
        fnstsw ax
    L_00428738:
        test ah,5
    L_0042873b:
        jnp asm_target_0042886c
    L_00428741:
        mov dl,byte ptr [ecx+1Dh]
    L_00428744:
        cmp dl,3
    L_00428747:
        je short L_00428763
    L_00428749:
        fld dword ptr [esp+48h]
    L_0042874d:
        fcomp dword ptr [data_00470b04]
    L_00428753:
        fnstsw ax
    L_00428755:
        test ah,5
    L_00428758:
        jnp asm_target_0042886c
    L_0042875e:
        cmp dl,3
    L_00428761:
        jne short L_00428778
    L_00428763:
        fld dword ptr [esp+30h]
    L_00428767:
        fcomp dword ptr [data_00470b04]
    L_0042876d:
        fnstsw ax
    L_0042876f:
        test ah,5
    L_00428772:
        jnp asm_target_0042886c
    L_00428778:
        mov eax,dword ptr [ecx+30h]
    L_0042877b:
        test eax,eax
    L_0042877d:
        je short L_0042878e
    L_0042877f:
        push edi
    L_00428780:
        mov edx,ebx
    L_00428782:
        mov ecx,ebp
    L_00428784:
        call eax
    L_00428786:
        test eax,eax
    L_00428788:
        jne asm_target_0042886c
    L_0042878e:
        mov eax,dword ptr [esi+10h]
    L_00428791:
        test eax,eax
    L_00428793:
        jne short L_004287a3
    L_00428795:
        mov eax,esi
    L_00428797:
        call asm_AnimationManager_StopAtFrame2_0040c480
    L_0042879c:
        mov dword ptr [esi+10h],1
    L_004287a3:
        mov edi,dword ptr [esi+14h]
    L_004287a6:
        mov dword ptr [esi+0Ch],1
    L_004287ad:
        mov bl,byte ptr [edi+1Dh]
    L_004287b0:
        cmp bl,3
    L_004287b3:
        jne short L_004287c4
    L_004287b5:
        mov ecx,dword ptr [esp+10h]
    L_004287b9:
        push 4
    L_004287bb:
        call asm_AtInterval_FrameCounterPair_00427c70
    L_004287c0:
        test eax,eax
    L_004287c2:
        je short L_004287cc
    L_004287c4:
        movsx ecx,word ptr [edi+2]
    L_004287c8:
        add dword ptr [esp+54h],ecx
    L_004287cc:
        cmp bl,3
    L_004287cf:
        je short L_00428835
    L_004287d1:
        call asm_AnimationManager_ValidateHandle_00449450
    L_004287d6:
        mov edx,dword ptr [eax+2Ch]
    L_004287d9:
        mov dword ptr [esp+18h],edx
    L_004287dd:
        call asm_AnimationManager_MarkForRemovalAndClearHandle_00449630
    L_004287e2:
        mov eax,dword ptr [esi+14h]
    L_004287e5:
        movsx ecx,word ptr [eax+20h]
    L_004287e9:
        mov edx,dword ptr [ebp+10h]
    L_004287ec:
        push 0Fh
    L_004287ee:
        add ecx,5
    L_004287f1:
        push ecx
    L_004287f2:
        push edx
    L_004287f3:
        lea edi,[esp+28h]
    L_004287f7:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_004287fc:
        mov eax,dword ptr [eax]
    L_004287fe:
        mov dword ptr [esi],eax
    L_00428800:
        call asm_AnimationManager_ValidateHandle_00449450
    L_00428805:
        mov ecx,dword ptr [esp+18h]
    L_00428809:
        mov dword ptr [eax+2Ch],ecx
    L_0042880c:
        mov ecx,dword ptr [eax+35Ch]
    L_00428812:
        or ecx,4
    L_00428815:
        mov dword ptr [eax+35Ch],ecx
    L_0042881b:
        fld dword ptr [esi-18h]
    L_0042881e:
        fmul dword ptr [data_00470b90]
    L_00428824:
        mov dword ptr [esi-28h],3DCCCCCDh
    L_0042882b:
        mov dword ptr [esi-4],2
    L_00428832:
        fstp dword ptr [esi-18h]
    L_00428835:
        mov eax,dword ptr [esi+14h]
    L_00428838:
        cmp byte ptr [eax+1Dh],2
    L_0042883c:
        jne short L_00428868
    L_0042883e:
        movsx ecx,word ptr [eax+2]
    L_00428842:
        mov eax,55555556h
    L_00428847:
        imul ecx
    L_00428849:
        mov eax,edx
    L_0042884b:
        shr eax,1Fh
    L_0042884e:
        add eax,edx
    L_00428850:
        push eax
    L_00428851:
        push 0Dh
    L_00428853:
        push 3FB33333h
    L_00428858:
        push 42000000h
    L_0042885d:
        lea eax,[esi-30h]
    L_00428860:
        push eax
    L_00428861:
        mov edx,ebp
    L_00428863:
        call asm_EffectIndicatorPool_AllocateRetail_00427b50
    L_00428868:
        mov edi,dword ptr [esp+58h]
    L_0042886c:
        mov ebx,dword ptr [esp+10h]
    L_00428870:
        mov eax,dword ptr [esp+14h]
    L_00428874:
        add ebx,5Ch
    L_00428877:
        add esi,5Ch
    L_0042887a:
        dec eax
    L_0042887b:
        mov dword ptr [esp+10h],ebx
    L_0042887f:
        mov dword ptr [esp+14h],eax
    L_00428883:
        jne asm_target_004286b2
    L_00428889:
        mov ecx,dword ptr [data_004776ec]
    L_0042888f:
        mov eax,edi
    L_00428891:
        call asm_Player_HitTestRetail_004059f0
    L_00428896:
        mov ecx,dword ptr [esp+54h]
    L_0042889a:
        add ecx,eax
    L_0042889c:
        add ebp,350Ch
    L_004288a2:
        mov dword ptr [esp+54h],ecx
    L_004288a6:
        lea ecx,[ebp+48h]
    L_004288a9:
        mov esi,20h
    L_004288ae:
        mov edi,edi
    L_004288b0:
        mov ebx,dword ptr [ecx+20h]
    L_004288b3:
        test bl,1
    L_004288b6:
        je asm_target_00428a60
    L_004288bc:
        mov eax,dword ptr [ecx]
    L_004288be:
        cmp eax,dword ptr [ecx-4]
    L_004288c1:
        je short L_004288cf
    L_004288c3:
        cdq
    L_004288c4:
        idiv dword ptr [ecx+1Ch]
    L_004288c7:
        test edx,edx
    L_004288c9:
        je asm_target_00428a60
    L_004288cf:
        test bl,2
    L_004288d2:
        jne asm_target_00428a0c
    L_004288d8:
        fld dword ptr [data_00470b04]
    L_004288de:
        fld dword ptr [ecx-40h]
    L_004288e1:
        fucompp
    L_004288e3:
        fnstsw ax
    L_004288e5:
        test ah,44h
    L_004288e8:
        jp short L_00428954
    L_004288ea:
        fld dword ptr [ecx-38h]
    L_004288ed:
        fmul dword ptr [data_00470b0c]
    L_004288f3:
        fld dword ptr [ecx-30h]
    L_004288f6:
        fsub st,st(1)
    L_004288f8:
        fcomp dword ptr [esp+2Ch]
    L_004288fc:
        fnstsw ax
    L_004288fe:
        test ah,41h
    L_00428901:
        je asm_target_00428a5e
    L_00428907:
        fadd dword ptr [ecx-30h]
    L_0042890a:
        fcomp dword ptr [esp+38h]
    L_0042890e:
        fnstsw ax
    L_00428910:
        test ah,5
    L_00428913:
        jnp asm_target_00428a60
    L_00428919:
        fld dword ptr [ecx-34h]
    L_0042891c:
        fmul dword ptr [data_00470b0c]
    L_00428922:
        fld dword ptr [ecx-2Ch]
    L_00428925:
        fsub st,st(1)
    L_00428927:
        fcomp dword ptr [esp+30h]
    L_0042892b:
        fnstsw ax
    L_0042892d:
        test ah,41h
    L_00428930:
        je asm_target_00428a5e
    L_00428936:
        fadd dword ptr [ecx-2Ch]
    L_00428939:
        fcomp dword ptr [esp+3Ch]
    L_0042893d:
        fnstsw ax
    L_0042893f:
        test ah,5
    L_00428942:
        jp asm_target_00428a37
    L_00428948:
        jmp asm_target_00428a60
    L_0042894d:
        fstp st(0)
    L_0042894f:
        jmp asm_target_0042886c
    L_00428954:
        fld dword ptr [edi]
    L_00428956:
        mov edx,dword ptr [esp+5Ch]
    L_0042895a:
        fsub dword ptr [ecx-30h]
    L_0042895d:
        fld dword ptr [edi+4]
    L_00428960:
        fsub dword ptr [ecx-2Ch]
    L_00428963:
        fld dword ptr [ecx-40h]
    L_00428966:
        fchs
    L_00428968:
        fld st(0)
    L_0042896a:
        fsin
    L_0042896c:
        fstp dword ptr [esp+58h]
    L_00428970:
        fcos
    L_00428972:
        fld st(0)
    L_00428974:
        fmul st,st(3)
    L_00428976:
        fld dword ptr [esp+58h]
    L_0042897a:
        fmul st,st(3)
    L_0042897c:
        fsubp st(1),st
    L_0042897e:
        fstp dword ptr [esp+20h]
    L_00428982:
        fld dword ptr [esp+58h]
    L_00428986:
        fmul st,st(3)
    L_00428988:
        fxch
    L_0042898a:
        fmul st,st(2)
    L_0042898c:
        faddp st(1),st
    L_0042898e:
        fstp dword ptr [esp+24h]
    L_00428992:
        fstp st(0)
    L_00428994:
        fstp st(0)
    L_00428996:
        fld dword ptr [edx]
    L_00428998:
        fmul dword ptr [data_00470b0c]
    L_0042899e:
        fld dword ptr [ecx-38h]
    L_004289a1:
        fmul dword ptr [data_00470b78]
    L_004289a7:
        fld st(1)
    L_004289a9:
        fadd dword ptr [esp+20h]
    L_004289ad:
        fcompp
    L_004289af:
        fnstsw ax
    L_004289b1:
        test ah,5
    L_004289b4:
        jnp asm_target_00428a5e
    L_004289ba:
        fld dword ptr [ecx-38h]
    L_004289bd:
        fmul dword ptr [data_00470b0c]
    L_004289c3:
        fld dword ptr [esp+20h]
    L_004289c7:
        fsub st,st(2)
    L_004289c9:
        fcompp
    L_004289cb:
        fnstsw ax
    L_004289cd:
        fstp st(0)
    L_004289cf:
        test ah,41h
    L_004289d2:
        je asm_target_00428a60
    L_004289d8:
        fld dword ptr [edx+4]
    L_004289db:
        fmul dword ptr [data_00470b0c]
    L_004289e1:
        fld dword ptr [ecx-34h]
    L_004289e4:
        fmul dword ptr [data_00470b78]
    L_004289ea:
        fld st(1)
    L_004289ec:
        fadd dword ptr [esp+24h]
    L_004289f0:
        fcompp
    L_004289f2:
        fnstsw ax
    L_004289f4:
        test ah,5
    L_004289f7:
        jnp short L_00428a5e
    L_004289f9:
        fld dword ptr [ecx-34h]
    L_004289fc:
        fmul dword ptr [data_00470b0c]
    L_00428a02:
        fld dword ptr [esp+24h]
    L_00428a06:
        fsub st,st(2)
    L_00428a08:
        fcompp
    L_00428a0a:
        jmp short L_00428a2e
    L_00428a0c:
        fld dword ptr [ebp]
    L_00428a0f:
        fld dword ptr [ecx-2Ch]
    L_00428a12:
        fsub dword ptr [edi+4]
    L_00428a15:
        fld dword ptr [ecx-30h]
    L_00428a18:
        fsub dword ptr [edi]
    L_00428a1a:
        fld st(2)
    L_00428a1c:
        fmul st,st(3)
    L_00428a1e:
        fld st(1)
    L_00428a20:
        fmul st,st(2)
    L_00428a22:
        fld st(3)
    L_00428a24:
        fmul st,st(4)
    L_00428a26:
        faddp st(1),st
    L_00428a28:
        fcompp
    L_00428a2a:
        fstp st(0)
    L_00428a2c:
        fstp st(0)
    L_00428a2e:
        fnstsw ax
    L_00428a30:
        fstp st(0)
    L_00428a32:
        test ah,41h
    L_00428a35:
        je short L_00428a60
    L_00428a37:
        mov eax,dword ptr [ecx+10h]
    L_00428a3a:
        mov edx,dword ptr [esp+54h]
    L_00428a3e:
        mov ebx,dword ptr [ecx+14h]
    L_00428a41:
        add edx,eax
    L_00428a43:
        add ebx,eax
    L_00428a45:
        mov dword ptr [esp+54h],edx
    L_00428a49:
        mov edx,dword ptr [ecx+18h]
    L_00428a4c:
        mov eax,ebx
    L_00428a4e:
        cmp edx,eax
    L_00428a50:
        mov dword ptr [ecx+14h],ebx
    L_00428a53:
        jg short L_00428a60
    L_00428a55:
        mov dword ptr [ecx+10h],0
    L_00428a5c:
        jmp short L_00428a60
    L_00428a5e:
        fstp st(0)
    L_00428a60:
        add ebp,6Ch
    L_00428a63:
        add ecx,6Ch
    L_00428a66:
        dec esi
    L_00428a67:
        jne asm_target_004288b0
    L_00428a6d:
        mov ecx,dword ptr [esp+54h]
    L_00428a71:
        test ecx,ecx
    L_00428a73:
        je short L_00428ab6
    L_00428a75:
        mov eax,66666667h
    L_00428a7a:
        imul ecx
    L_00428a7c:
        sar edx,2
    L_00428a7f:
        mov eax,edx
    L_00428a81:
        shr eax,1Fh
    L_00428a84:
        lea edx,[edx+eax+0Ah]
    L_00428a88:
        mov eax,66666667h
    L_00428a8d:
        imul edx
    L_00428a8f:
        mov eax,dword ptr [data_00474c44]
    L_00428a94:
        sar edx,2
    L_00428a97:
        mov esi,edx
    L_00428a99:
        shr esi,1Fh
    L_00428a9c:
        add esi,edx
    L_00428a9e:
        add eax,esi
    L_00428aa0:
        cmp eax,3B9ACA00h
    L_00428aa5:
        mov dword ptr [data_00474c44],eax
    L_00428aaa:
        jl short L_00428ab6
    L_00428aac:
        mov dword ptr [data_00474c44],3B9AC9FFh
    L_00428ab6:
        pop edi
    L_00428ab7:
        pop esi
    L_00428ab8:
        pop ebx
    L_00428ab9:
        mov eax,ecx
    L_00428abb:
        pop ebp
    L_00428abc:
        add esp,40h
    L_00428abf:
        ret 0Ch
    }
}
