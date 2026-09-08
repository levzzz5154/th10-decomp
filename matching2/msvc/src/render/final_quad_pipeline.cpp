#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442670..0x00442AC6: FUN_00442670
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442670_00442670() {
    __asm {
    L_00442670:
        fld dword ptr [data_004978c0]
    L_00442676:
        sub esp,0Ch
    L_00442679:
        push ebx
    L_0044267a:
        push ebp
    L_0044267b:
        push esi
    L_0044267c:
        mov esi,ecx
    L_0044267e:
        fadd dword ptr [esi+5Ch]
    L_00442681:
        mov bl,byte ptr [esp+1Ch]
    L_00442685:
        test bl,1
    L_00442688:
        push edi
    L_00442689:
        fstp dword ptr [data_004978c0]
    L_0044268f:
        mov edi,eax
    L_00442691:
        fld dword ptr [data_004978c4]
    L_00442697:
        fadd dword ptr [esi+60h]
    L_0044269a:
        fstp dword ptr [data_004978c4]
    L_004426a0:
        fld dword ptr [data_004978dc]
    L_004426a6:
        fadd dword ptr [esi+5Ch]
    L_004426a9:
        fstp dword ptr [data_004978dc]
    L_004426af:
        fld dword ptr [data_004978e0]
    L_004426b5:
        fadd dword ptr [esi+60h]
    L_004426b8:
        fstp dword ptr [data_004978e0]
    L_004426be:
        fld dword ptr [data_004978f8]
    L_004426c4:
        fadd dword ptr [esi+5Ch]
    L_004426c7:
        fstp dword ptr [data_004978f8]
    L_004426cd:
        fld dword ptr [data_004978fc]
    L_004426d3:
        fadd dword ptr [esi+60h]
    L_004426d6:
        fstp dword ptr [data_004978fc]
    L_004426dc:
        fld dword ptr [data_00497914]
    L_004426e2:
        fadd dword ptr [esi+5Ch]
    L_004426e5:
        fstp dword ptr [data_00497914]
    L_004426eb:
        fld dword ptr [data_00497918]
    L_004426f1:
        fadd dword ptr [esi+60h]
    L_004426f4:
        fstp dword ptr [data_00497918]
    L_004426fa:
        je short L_00442764
    L_004426fc:
        fld dword ptr [data_004978c0]
    L_00442702:
        frndint
    L_00442704:
        fsub dword ptr [data_004700ec]
    L_0044270a:
        fld dword ptr [data_004978dc]
    L_00442710:
        frndint
    L_00442712:
        fsub dword ptr [data_004700ec]
    L_00442718:
        fld dword ptr [data_004978c4]
    L_0044271e:
        frndint
    L_00442720:
        fsub dword ptr [data_004700ec]
    L_00442726:
        fld dword ptr [data_004978fc]
    L_0044272c:
        frndint
    L_0044272e:
        fsub dword ptr [data_004700ec]
    L_00442734:
        fst dword ptr [data_004978fc]
    L_0044273a:
        fstp dword ptr [data_00497918]
    L_00442740:
        fst dword ptr [data_004978c4]
    L_00442746:
        fstp dword ptr [data_004978e0]
    L_0044274c:
        fst dword ptr [data_004978dc]
    L_00442752:
        fstp dword ptr [data_00497914]
    L_00442758:
        fst dword ptr [data_004978c0]
    L_0044275e:
        fstp dword ptr [data_004978f8]
    L_00442764:
        mov eax,dword ptr [edi+394h]
    L_0044276a:
        fld dword ptr [eax+20h]
    L_0044276d:
        fadd dword ptr [edi+54h]
    L_00442770:
        fst dword ptr [data_0049790c]
    L_00442776:
        fstp dword ptr [data_004978d4]
    L_0044277c:
        mov ecx,dword ptr [edi+394h]
    L_00442782:
        fld dword ptr [ecx+28h]
    L_00442785:
        fadd dword ptr [edi+54h]
    L_00442788:
        fst dword ptr [data_00497928]
    L_0044278e:
        fstp dword ptr [data_004978f0]
    L_00442794:
        mov edx,dword ptr [edi+394h]
    L_0044279a:
        fld dword ptr [edx+24h]
    L_0044279d:
        fadd dword ptr [edi+58h]
    L_004427a0:
        fst dword ptr [data_004978f4]
    L_004427a6:
        fstp dword ptr [data_004978d8]
    L_004427ac:
        mov eax,dword ptr [edi+394h]
    L_004427b2:
        fld dword ptr [eax+2Ch]
    L_004427b5:
        fadd dword ptr [edi+58h]
    L_004427b8:
        fst dword ptr [data_0049792c]
    L_004427be:
        fstp dword ptr [data_00497910]
    L_004427c4:
        fld dword ptr [data_004978c0]
    L_004427ca:
        fcomp dword ptr [data_004978dc]
    L_004427d0:
        fnstsw ax
    L_004427d2:
        test ah,41h
    L_004427d5:
        jne short L_004427df
    L_004427d7:
        fld dword ptr [data_004978c0]
    L_004427dd:
        jmp short L_004427e5
    L_004427df:
        fld dword ptr [data_004978dc]
    L_004427e5:
        fld dword ptr [data_004978f8]
    L_004427eb:
        fcomp
    L_004427ed:
        fnstsw ax
    L_004427ef:
        test ah,41h
    L_004427f2:
        jne short L_004427fc
    L_004427f4:
        fstp st(0)
    L_004427f6:
        fld dword ptr [data_004978f8]
    L_004427fc:
        fld dword ptr [data_00497914]
    L_00442802:
        fcomp
    L_00442804:
        fnstsw ax
    L_00442806:
        test ah,41h
    L_00442809:
        jne short L_00442813
    L_0044280b:
        fstp st(0)
    L_0044280d:
        fld dword ptr [data_00497914]
    L_00442813:
        fld dword ptr [data_004978c4]
    L_00442819:
        fcomp dword ptr [data_004978e0]
    L_0044281f:
        fnstsw ax
    L_00442821:
        test ah,41h
    L_00442824:
        jne short L_00442832
    L_00442826:
        mov ecx,dword ptr [data_004978c4]
    L_0044282c:
        mov dword ptr [esp+20h],ecx
    L_00442830:
        jmp short L_0044283c
    L_00442832:
        mov edx,dword ptr [data_004978e0]
    L_00442838:
        mov dword ptr [esp+20h],edx
    L_0044283c:
        fld dword ptr [data_004978fc]
    L_00442842:
        fcomp dword ptr [esp+20h]
    L_00442846:
        fnstsw ax
    L_00442848:
        test ah,41h
    L_0044284b:
        jne short L_00442856
    L_0044284d:
        mov eax,dword ptr [data_004978fc]
    L_00442852:
        mov dword ptr [esp+20h],eax
    L_00442856:
        fld dword ptr [data_00497918]
    L_0044285c:
        fcomp dword ptr [esp+20h]
    L_00442860:
        fnstsw ax
    L_00442862:
        test ah,41h
    L_00442865:
        jne short L_00442871
    L_00442867:
        mov ecx,dword ptr [data_00497918]
    L_0044286d:
        mov dword ptr [esp+20h],ecx
    L_00442871:
        fld dword ptr [data_004978c0]
    L_00442877:
        fcomp dword ptr [data_004978dc]
    L_0044287d:
        fnstsw ax
    L_0044287f:
        test ah,5
    L_00442882:
        jp short L_00442890
    L_00442884:
        mov edx,dword ptr [data_004978c0]
    L_0044288a:
        mov dword ptr [esp+10h],edx
    L_0044288e:
        jmp short L_00442899
    L_00442890:
        mov eax,dword ptr [data_004978dc]
    L_00442895:
        mov dword ptr [esp+10h],eax
    L_00442899:
        fld dword ptr [data_004978f8]
    L_0044289f:
        fcomp dword ptr [esp+10h]
    L_004428a3:
        fnstsw ax
    L_004428a5:
        test ah,5
    L_004428a8:
        jp short L_004428b4
    L_004428aa:
        mov ecx,dword ptr [data_004978f8]
    L_004428b0:
        mov dword ptr [esp+10h],ecx
    L_004428b4:
        fld dword ptr [data_00497914]
    L_004428ba:
        fcomp dword ptr [esp+10h]
    L_004428be:
        fnstsw ax
    L_004428c0:
        test ah,5
    L_004428c3:
        jp short L_004428cf
    L_004428c5:
        mov edx,dword ptr [data_00497914]
    L_004428cb:
        mov dword ptr [esp+10h],edx
    L_004428cf:
        fld dword ptr [data_004978c4]
    L_004428d5:
        fcomp dword ptr [data_004978e0]
    L_004428db:
        fnstsw ax
    L_004428dd:
        test ah,5
    L_004428e0:
        jp short L_004428ed
    L_004428e2:
        mov eax,dword ptr [data_004978c4]
    L_004428e7:
        mov dword ptr [esp+14h],eax
    L_004428eb:
        jmp short L_004428f7
    L_004428ed:
        mov ecx,dword ptr [data_004978e0]
    L_004428f3:
        mov dword ptr [esp+14h],ecx
    L_004428f7:
        fld dword ptr [data_004978fc]
    L_004428fd:
        fcomp dword ptr [esp+14h]
    L_00442901:
        fnstsw ax
    L_00442903:
        test ah,5
    L_00442906:
        jp short L_00442912
    L_00442908:
        mov edx,dword ptr [data_004978fc]
    L_0044290e:
        mov dword ptr [esp+14h],edx
    L_00442912:
        fld dword ptr [data_00497918]
    L_00442918:
        fcomp dword ptr [esp+14h]
    L_0044291c:
        fnstsw ax
    L_0044291e:
        test ah,5
    L_00442921:
        jp short L_0044292c
    L_00442923:
        mov eax,dword ptr [data_00497918]
    L_00442928:
        mov dword ptr [esp+14h],eax
    L_0044292c:
        mov ecx,dword ptr [data_00491fac]
    L_00442932:
        mov ebp,dword ptr [ecx+0CCh]
    L_00442938:
        fild dword ptr [ecx+0CCh]
    L_0044293e:
        test ebp,ebp
    L_00442940:
        jge short L_00442948
    L_00442942:
        fadd dword ptr [data_00470b98]
    L_00442948:
        fxch
    L_0044294a:
        fcompp
    L_0044294c:
        fnstsw ax
    L_0044294e:
        test ah,5
    L_00442951:
        jnp asm_target_00442abb
    L_00442957:
        mov edx,dword ptr [ecx+0D0h]
    L_0044295d:
        fild dword ptr [ecx+0D0h]
    L_00442963:
        test edx,edx
    L_00442965:
        jge short L_0044296d
    L_00442967:
        fadd dword ptr [data_00470b98]
    L_0044296d:
        fcomp dword ptr [esp+20h]
    L_00442971:
        fnstsw ax
    L_00442973:
        test ah,41h
    L_00442976:
        je asm_target_00442abb
    L_0044297c:
        mov eax,dword ptr [ecx+0D4h]
    L_00442982:
        add eax,ebp
    L_00442984:
        test eax,eax
    L_00442986:
        mov dword ptr [esp+20h],eax
    L_0044298a:
        fild dword ptr [esp+20h]
    L_0044298e:
        jge short L_00442996
    L_00442990:
        fadd dword ptr [data_00470b98]
    L_00442996:
        fcomp dword ptr [esp+10h]
    L_0044299a:
        fnstsw ax
    L_0044299c:
        test ah,5
    L_0044299f:
        jnp asm_target_00442abb
    L_004429a5:
        mov ecx,dword ptr [ecx+0D8h]
    L_004429ab:
        add ecx,edx
    L_004429ad:
        test ecx,ecx
    L_004429af:
        mov dword ptr [esp+20h],ecx
    L_004429b3:
        fild dword ptr [esp+20h]
    L_004429b7:
        jge short L_004429bf
    L_004429b9:
        fadd dword ptr [data_00470b98]
    L_004429bf:
        fcomp dword ptr [esp+14h]
    L_004429c3:
        fnstsw ax
    L_004429c5:
        test ah,5
    L_004429c8:
        jnp asm_target_00442abb
    L_004429ce:
        mov edx,dword ptr [edi+394h]
    L_004429d4:
        mov eax,dword ptr [edx+4]
    L_004429d7:
        cmp dword ptr [esi+3ADA64h],eax
    L_004429dd:
        je short L_00442a01
    L_004429df:
        mov dword ptr [esi+3ADA64h],eax
    L_004429e5:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004429ea:
        mov edx,dword ptr [esi+3ADA64h]
    L_004429f0:
        mov eax,dword ptr [data_00491c30]
    L_004429f5:
        mov ecx,dword ptr [eax]
    L_004429f7:
        push edx
    L_004429f8:
        push 0
    L_004429fa:
        push eax
    L_004429fb:
        call dword ptr [ecx+104h]
    L_00442a01:
        cmp byte ptr [esi+3ADA6Ah],1
    L_00442a08:
        je short L_00442a16
    L_00442a0a:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00442a0f:
        mov byte ptr [esi+3ADA6Ah],1
    L_00442a16:
        test bl,2
    L_00442a19:
        jne asm_target_00442aa8
    L_00442a1f:
        mov eax,dword ptr [edi+35Ch]
    L_00442a25:
        test ah,ah
    L_00442a27:
        jns short L_00442a31
    L_00442a29:
        mov eax,dword ptr [edi+300h]
    L_00442a2f:
        jmp short L_00442a37
    L_00442a31:
        mov eax,dword ptr [edi+2FCh]
    L_00442a37:
        mov ecx,dword ptr [esi+73245Ch]
    L_00442a3d:
        test ecx,ecx
    L_00442a3f:
        mov dword ptr [esp+20h],eax
    L_00442a43:
        je short L_00442a94
    L_00442a45:
        mov cl,byte ptr [esi+73245Ah]
    L_00442a4b:
        shr eax,10h
    L_00442a4e:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442a53:
        mov cl,byte ptr [esi+732459h]
    L_00442a59:
        mov byte ptr [esp+22h],al
    L_00442a5d:
        mov al,byte ptr [esp+21h]
    L_00442a61:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442a66:
        mov cl,byte ptr [esi+732458h]
    L_00442a6c:
        mov byte ptr [esp+21h],al
    L_00442a70:
        mov al,byte ptr [esp+20h]
    L_00442a74:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442a79:
        mov cl,byte ptr [esi+73245Bh]
    L_00442a7f:
        mov byte ptr [esp+20h],al
    L_00442a83:
        mov al,byte ptr [esp+23h]
    L_00442a87:
        call asm_AnimationColor_MultiplyChannel_004423c0
    L_00442a8c:
        mov byte ptr [esp+23h],al
    L_00442a90:
        mov eax,dword ptr [esp+20h]
    L_00442a94:
        mov dword ptr [data_004978d0],eax
    L_00442a99:
        mov dword ptr [data_004978ec],eax
    L_00442a9e:
        mov dword ptr [data_00497908],eax
    L_00442aa3:
        mov dword ptr [data_00497924],eax
    L_00442aa8:
        mov eax,esi
    L_00442aaa:
        call asm_AnmManager_SyncEntityRenderStateRetail_004425a0
    L_00442aaf:
        mov edx,4978C0h
    L_00442ab4:
        mov eax,esi
    L_00442ab6:
        call asm_AnimationManager_AppendQuadVertices_00442fe0
    L_00442abb:
        pop edi
    L_00442abc:
        pop esi
    L_00442abd:
        pop ebp
    L_00442abe:
        xor eax,eax
    L_00442ac0:
        pop ebx
    L_00442ac1:
        add esp,0Ch
    L_00442ac4:
        ret 4
    }
}
