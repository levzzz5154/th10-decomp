#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00425730..0x004257C7: FUN_00425730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00425730_00425730() {
    __asm {
    L_00425730:
        sub esp,1Ch
    L_00425733:
        push ebx
    L_00425734:
        push ebp
    L_00425735:
        mov ebp,dword ptr [esp+28h]
    L_00425739:
        mov eax,dword ptr [ebp+458h]
    L_0042573f:
        cmp eax,4
    L_00425742:
        push esi
    L_00425743:
        push edi
    L_00425744:
        ja asm_target_00425d72
    L_0042574a:
        jmp dword ptr [eax*4+426344h]
    L_00425751:
        mov ecx,dword ptr [ebp+478h]
    L_00425757:
        imul ecx,1F40h
    L_0042575d:
        mov eax,88888889h
    L_00425762:
        imul ecx
    L_00425764:
        add edx,ecx
    L_00425766:
        sar edx,5
    L_00425769:
        mov ecx,edx
    L_0042576b:
        shr ecx,1Fh
    L_0042576e:
        add ecx,edx
    L_00425770:
        mov eax,0BB80h
    L_00425775:
        sub eax,ecx
    L_00425777:
        mov dword ptr [esp+30h],eax
    L_0042577b:
        mov dword ptr [ebp+3D0h],eax
    L_00425781:
        mov ebx,1
    L_00425786:
        fild dword ptr [esp+30h]
    L_0042578a:
        mov eax,20h
    L_0042578f:
        fmul dword ptr [data_00470b00]
    L_00425795:
        fstp dword ptr [ebp+3C4h]
    L_0042579b:
        mov dword ptr [ebp+332Ch],ebx
    L_004257a1:
        mov dword ptr [ebp+33C4h],ebx
    L_004257a7:
        mov dword ptr [ebp+345Ch],ebx
    L_004257ad:
        mov dword ptr [ebp+34F4h],ebx
    L_004257b3:
        mov edx,dword ptr [ebp+3500h]
    L_004257b9:
        shl edx,3
    L_004257bc:
        cmp edx,eax
    L_004257be:
        TH10_REL8(0x7d, 0x004257be, VA_asm_target_00425804)
    L_004257c0:
        lea ecx,[ebp+446Ch]
    L_004257c6:
        TH10_REL8(0xeb, 0x004257c6, VA_asm_FUN_00425730_part_004257d0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_004257d0:
        mov edx,dword ptr [ebp+3500h]
    L_004257d6:
        shl edx,6
    L_004257d9:
        mov esi,dword ptr [edx+ebp+436Ch]
    L_004257e0:
        lea edx,[edx+ebp+436Ch]
    L_004257e7:
        mov dword ptr [ecx],esi
    L_004257e9:
        mov edx,dword ptr [edx+4]
    L_004257ec:
        mov dword ptr [ecx+4],edx
    L_004257ef:
        mov edx,dword ptr [ebp+3500h]
    L_004257f5:
        dec eax
    L_004257f6:
        shl edx,3
    L_004257f9:
        sub ecx,8
    L_004257fc:
        cmp eax,edx
    L_004257fe:
        jg short L_004257d0
    L_00425800:
        test eax,eax
    L_00425802:
        TH10_REL8(0x7e, 0x00425802, VA_asm_target_00425821)
    L_00425804:
        lea ecx,[ebp+eax*8+4370h]
    L_0042580b:
        TH10_REL8(0xeb, 0x0042580b, VA_asm_FUN_00425730_part_00425810)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00425810:
        mov edx,dword ptr [ecx-0Ch]
    L_00425813:
        mov dword ptr [ecx-4],edx
    L_00425816:
        mov edx,dword ptr [ecx-8]
    L_00425819:
        mov dword ptr [ecx],edx
    L_0042581b:
        add ecx,0FFFFFFF8h
    L_0042581e:
        dec eax
    L_0042581f:
        jne short L_00425810
    L_00425821:
        mov eax,dword ptr [ebp+3CCh]
    L_00425827:
        mov dword ptr [ebp+436Ch],eax
    L_0042582d:
        mov ecx,dword ptr [ebp+3D0h]
    L_00425833:
        mov dword ptr [ebp+4370h],ecx
    L_00425839:
        mov eax,dword ptr [ebp+478h]
    L_0042583f:
        cmp eax,1Eh
    L_00425842:
        mov dword ptr [esp+30h],eax
    L_00425846:
        TH10_REL8(0x7c, 0x00425846, VA_asm_target_004258ab)
    L_00425848:
        mov esi,dword ptr [data_004776f0]
    L_0042584e:
        add esi,60h
    L_00425851:
        mov edi,7D0h
    L_00425856:
        TH10_REL8(0xeb, 0x00425856, VA_asm_FUN_00425730_part_00425860)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_00425860:
        mov ax,word ptr [esi+446h]
    L_00425867:
        test ax,ax
    L_0042586a:
        je short L_0042587e
    L_0042586c:
        cmp ax,3
    L_00425870:
        je short L_0042587e
    L_00425872:
        mov eax,dword ptr [esi+4]
    L_00425875:
        test eax,eax
    L_00425877:
        jne short L_0042587e
    L_00425879:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_0042587e:
        add esi,7F0h
    L_00425884:
        dec edi
    L_00425885:
        jne short L_00425860
    L_00425887:
        mov edx,dword ptr [data_0047781c]
    L_0042588d:
        mov ecx,dword ptr [edx+18h]
    L_00425890:
        test ecx,ecx
    L_00425892:
        je short L_00425902
    L_00425894:
        cmp dword ptr [ecx+0Ch],ebx
    L_00425897:
        mov esi,dword ptr [ecx+8]
    L_0042589a:
        je short L_004258a3
    L_0042589c:
        mov eax,dword ptr [ecx]
    L_0042589e:
        push 0
    L_004258a0:
        call dword ptr [eax+14h]
    L_004258a3:
        test esi,esi
    L_004258a5:
        mov ecx,esi
    L_004258a7:
        jne short L_00425894
    L_004258a9:
        jmp short L_00425902
    L_004258ab:
        fild dword ptr [esp+30h]
    L_004258af:
        mov eax,dword ptr [data_004776f0]
    L_004258b4:
        push ebx
    L_004258b5:
        push 0
    L_004258b7:
        fmul dword ptr [data_00470d44]
    L_004258bd:
        lea esi,[ebp+440h]
    L_004258c3:
        mov ebx,esi
    L_004258c5:
        fadd dword ptr [data_00470bc8]
    L_004258cb:
        fstp dword ptr [esp+38h]
    L_004258cf:
        mov edi,dword ptr [esp+38h]
    L_004258d3:
        push edi
    L_004258d4:
        call asm_FUN_00408100_00408100
    L_004258d9:
        fld dword ptr [esp+30h]
    L_004258dd:
        fmul dword ptr [data_00470d40]
    L_004258e3:
        mov eax,dword ptr [data_004776f0]
    L_004258e8:
        push 0
    L_004258ea:
        push 0
    L_004258ec:
        push ecx
    L_004258ed:
        fstp dword ptr [esp]
    L_004258f0:
        call asm_FUN_00408100_00408100
    L_004258f5:
        mov eax,dword ptr [data_0047781c]
    L_004258fa:
        push 0
    L_004258fc:
        push edi
    L_004258fd:
        call asm_ScoreRecords_CopyVectorAndEvaluate_0041c800
    L_00425902:
        cmp dword ptr [ebp+478h],3Ch
    L_00425909:
        jl asm_target_00425d72
    L_0042590f:
        mov dword ptr [ebp+458h],1
    L_00425919:
        mov eax,dword ptr [ebp+484h]
    L_0042591f:
        xor ecx,ecx
    L_00425921:
        test al,1
    L_00425923:
        jne short L_0042594e
    L_00425925:
        or eax,1
    L_00425928:
        mov dword ptr [ebp+478h],ecx
    L_0042592e:
        mov dword ptr [ebp+474h],0FFF0BDC1h
    L_00425938:
        mov dword ptr [ebp+47Ch],ecx
    L_0042593e:
        mov dword ptr [ebp+480h],476F78h
    L_00425948:
        mov dword ptr [ebp+484h],eax
    L_0042594e:
        mov dword ptr [ebp+478h],ecx
    L_00425954:
        mov dword ptr [ebp+47Ch],ecx
    L_0042595a:
        mov dword ptr [ebp+474h],0FFFFFFFFh
    L_00425964:
        mov eax,dword ptr [data_0047770c]
    L_00425969:
        test eax,eax
    L_0042596b:
        je asm_target_00425a24
    L_00425971:
        mov ecx,dword ptr [eax+9EB8h]
    L_00425977:
        test ecx,ecx
    L_00425979:
        jne asm_target_00425a24
    L_0042597f:
        mov esi,dword ptr [data_004776ec]
    L_00425985:
        test esi,esi
    L_00425987:
        je asm_target_00425a24
    L_0042598d:
        mov eax,dword ptr [esi+28h]
    L_00425990:
        test eax,eax
    L_00425992:
        jne asm_target_00425a24
    L_00425998:
        movsx ecx,word ptr [data_00474c48]
    L_0042599f:
        mov eax,66666667h
    L_004259a4:
        imul ecx
    L_004259a6:
        sar edx,3
    L_004259a9:
        mov ecx,edx
    L_004259ab:
        shr ecx,1Fh
    L_004259ae:
        add ecx,edx
    L_004259b0:
        test cx,cx
    L_004259b3:
        je short L_00425a24
    L_004259b5:
        test byte ptr [data_00474e5c],2
    L_004259bc:
        je short L_00425a24
    L_004259be:
        push 10Eh
    L_004259c3:
        lea eax,[ebp+430Ch]
    L_004259c9:
        call asm_Player_SetSchedulerValue_00405410
    L_004259ce:
        push esi
    L_004259cf:
        call asm_InitializePlayer_00405860
    L_004259d4:
        add word ptr [data_00474c48],0FFECh
    L_004259dc:
        push ebp
    L_004259dd:
        call asm_FUN_00426f70_00426f70
    L_004259e2:
        movsx eax,word ptr [data_00474c48]
    L_004259e9:
        cdq
    L_004259ea:
        mov ecx,14h
    L_004259ef:
        idiv ecx
    L_004259f1:
        mov esi,dword ptr [data_0047770c]
    L_004259f7:
        imul edx,64h
    L_004259fa:
        mov ecx,eax
    L_004259fc:
        mov eax,66666667h
    L_00425a01:
        imul edx
    L_00425a03:
        sar edx,3
    L_00425a06:
        mov eax,edx
    L_00425a08:
        shr eax,1Fh
    L_00425a0b:
        add eax,edx
    L_00425a0d:
        push eax
    L_00425a0e:
        mov edx,ecx
    L_00425a10:
        call asm_FUN_004054b0_004054b0
    L_00425a15:
        push 0BB8h
    L_00425a1a:
        mov ecx,474C40h
    L_00425a1f:
        call asm_ScoreGauge_AddWithMinimum_00412e70
    L_00425a24:
        cmp dword ptr [ebp+478h],1Eh
    L_00425a2b:
        TH10_REL8(0x7d, 0x00425a2b, VA_asm_target_00425a8a)
    L_00425a2d:
        mov esi,dword ptr [data_004776f0]
    L_00425a33:
        add esi,60h
    L_00425a36:
        mov edi,7D0h
    L_00425a3b:
        TH10_REL8(0xeb, 0x00425a3b, VA_asm_FUN_00425730_part_00425a40)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00425a40:
        mov ax,word ptr [esi+446h]
    L_00425a47:
        test ax,ax
    L_00425a4a:
        je short L_00425a5e
    L_00425a4c:
        cmp ax,3
    L_00425a50:
        je short L_00425a5e
    L_00425a52:
        mov eax,dword ptr [esi+4]
    L_00425a55:
        test eax,eax
    L_00425a57:
        jne short L_00425a5e
    L_00425a59:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_00425a5e:
        add esi,7F0h
    L_00425a64:
        dec edi
    L_00425a65:
        jne short L_00425a40
    L_00425a67:
        mov ecx,dword ptr [data_0047781c]
    L_00425a6d:
        mov ecx,dword ptr [ecx+18h]
    L_00425a70:
        test ecx,ecx
    L_00425a72:
        je short L_00425a8a
    L_00425a74:
        cmp dword ptr [ecx+0Ch],1
    L_00425a78:
        mov esi,dword ptr [ecx+8]
    L_00425a7b:
        je short L_00425a84
    L_00425a7d:
        mov edx,dword ptr [ecx]
    L_00425a7f:
        push 0
    L_00425a81:
        call dword ptr [edx+14h]
    L_00425a84:
        test esi,esi
    L_00425a86:
        mov ecx,esi
    L_00425a88:
        jne short L_00425a74
    L_00425a8a:
        mov edi,ebp
    L_00425a8c:
        call asm_FUN_004250b0_004250b0
    L_00425a91:
        jmp asm_target_00425d72
    L_00425a96:
        cmp dword ptr [ebp+478h],8
    L_00425a9d:
        jl asm_target_00425bd9
    L_00425aa3:
        push ebp
    L_00425aa4:
        call asm_FUN_004269d0_004269d0
    L_00425aa9:
        cmp dword ptr [ebp+478h],3
    L_00425ab0:
        jne asm_target_00425b9d
    L_00425ab6:
        add word ptr [data_00474c48],0FFC0h
    L_00425abe:
        jns short L_00425ac9
    L_00425ac0:
        mov word ptr [data_00474c48],0
    L_00425ac9:
        movsx eax,word ptr [data_00474c48]
    L_00425ad0:
        cdq
    L_00425ad1:
        mov ecx,14h
    L_00425ad6:
        idiv ecx
    L_00425ad8:
        mov esi,dword ptr [data_0047770c]
    L_00425ade:
        imul edx,64h
    L_00425ae1:
        mov ecx,eax
    L_00425ae3:
        mov eax,66666667h
    L_00425ae8:
        imul edx
    L_00425aea:
        sar edx,3
    L_00425aed:
        mov eax,edx
    L_00425aef:
        shr eax,1Fh
    L_00425af2:
        add eax,edx
    L_00425af4:
        push eax
    L_00425af5:
        mov edx,ecx
    L_00425af7:
        call asm_FUN_004054b0_004054b0
    L_00425afc:
        lea eax,[esp+14h]
    L_00425b00:
        fld dword ptr [ebp+3C4h]
    L_00425b06:
        mov ecx,ebp
    L_00425b08:
        fsub dword ptr [data_00470b4c]
    L_00425b0e:
        mov dword ptr [esp+14h],0
    L_00425b16:
        mov dword ptr [esp+1Ch],0
    L_00425b1e:
        fstp dword ptr [esp+18h]
    L_00425b22:
        call asm_Entity_AngleToPoint_00426610
    L_00425b27:
        xor esi,esi
    L_00425b29:
        fstp dword ptr [esp+10h]
    L_00425b2d:
        mov dword ptr [esp+30h],esi
    L_00425b31:
        lea edi,[ebp+3C0h]
    L_00425b37:
        TH10_REL8(0xeb, 0x00425b37, VA_asm_FUN_00425730_part_00425b40)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00425b40:
        cmp esi,1
    L_00425b43:
        fild dword ptr [esp+30h]
    L_00425b47:
        fmul dword ptr [data_00470d3c]
    L_00425b4d:
        fadd dword ptr [esp+10h]
    L_00425b51:
        fsub dword ptr [data_00470d38]
    L_00425b57:
        fstp dword ptr [esp+30h]
    L_00425b5b:
        je short L_00425b6c
    L_00425b5d:
        cmp esi,3
    L_00425b60:
        je short L_00425b6c
    L_00425b62:
        cmp esi,5
    L_00425b65:
        mov eax,1
    L_00425b6a:
        jne short L_00425b71
    L_00425b6c:
        mov eax,4
    L_00425b71:
        mov ecx,dword ptr [esp+30h]
    L_00425b75:
        push 40400000h
    L_00425b7a:
        push ecx
    L_00425b7b:
        push 0FFFFFFh
    L_00425b80:
        push eax
    L_00425b81:
        mov eax,dword ptr [data_00477818]
    L_00425b86:
        mov ecx,edi
    L_00425b88:
        call asm_FUN_0041bb00_0041bb00
    L_00425b8d:
        inc esi
    L_00425b8e:
        cmp esi,7
    L_00425b91:
        mov dword ptr [esp+30h],esi
    L_00425b95:
        jl short L_00425b40
    L_00425b97:
        push ebp
    L_00425b98:
        call asm_FUN_00426f70_00426f70
    L_00425b9d:
        cmp dword ptr [ebp+478h],1Eh
    L_00425ba4:
        jl asm_target_00425d72
    L_00425baa:
        mov eax,dword ptr [data_00474c70]
    L_00425baf:
        xor edi,edi
    L_00425bb1:
        cmp eax,edi
    L_00425bb3:
        jge asm_target_00425ca4
    L_00425bb9:
        mov edx,dword ptr [data_00477838]
    L_00425bbf:
        cmp dword ptr [edx+10h],1
    L_00425bc3:
        je asm_target_00425c93
    L_00425bc9:
        mov edi,dword ptr [data_00477830]
    L_00425bcf:
        call asm_FUN_004231d0_004231d0
    L_00425bd4:
        jmp asm_target_00425d72
    L_00425bd9:
        mov esi,dword ptr [data_004776ec]
    L_00425bdf:
        test esi,esi
    L_00425be1:
        je asm_target_00425d72
    L_00425be7:
        mov eax,dword ptr [esi+28h]
    L_00425bea:
        test eax,eax
    L_00425bec:
        jne asm_target_00425d72
    L_00425bf2:
        movsx ecx,word ptr [data_00474c48]
    L_00425bf9:
        mov eax,66666667h
    L_00425bfe:
        imul ecx
    L_00425c00:
        sar edx,3
    L_00425c03:
        mov eax,edx
    L_00425c05:
        shr eax,1Fh
    L_00425c08:
        add eax,edx
    L_00425c0a:
        test ax,ax
    L_00425c0d:
        je asm_target_00425d72
    L_00425c13:
        test byte ptr [data_00474e5c],2
    L_00425c1a:
        je asm_target_00425d72
    L_00425c20:
        push 3Ch
    L_00425c22:
        lea eax,[ebp+474h]
    L_00425c28:
        call asm_Player_SetSchedulerValue_00405410
    L_00425c2d:
        push 0C8h
    L_00425c32:
        lea eax,[ebp+430Ch]
    L_00425c38:
        call asm_Player_SetSchedulerValue_00405410
    L_00425c3d:
        push esi
    L_00425c3e:
        call asm_InitializePlayer_00405860
    L_00425c43:
        add word ptr [data_00474c48],0FFECh
    L_00425c4b:
        push ebp
    L_00425c4c:
        call asm_FUN_00426f70_00426f70
    L_00425c51:
        movsx eax,word ptr [data_00474c48]
    L_00425c58:
        cdq
    L_00425c59:
        mov ecx,14h
    L_00425c5e:
        idiv ecx
    L_00425c60:
        mov esi,dword ptr [data_0047770c]
    L_00425c66:
        imul edx,64h
    L_00425c69:
        mov ecx,eax
    L_00425c6b:
        mov eax,66666667h
    L_00425c70:
        imul edx
    L_00425c72:
        sar edx,3
    L_00425c75:
        mov eax,edx
    L_00425c77:
        shr eax,1Fh
    L_00425c7a:
        add eax,edx
    L_00425c7c:
        push eax
    L_00425c7d:
        mov edx,ecx
    L_00425c7f:
        call asm_FUN_004054b0_004054b0
    L_00425c84:
        mov dword ptr [ebp+458h],1
    L_00425c8e:
        jmp asm_target_00425d72
    L_00425c93:
        push 4
    L_00425c95:
        mov eax,491C28h
    L_00425c9a:
        call asm_SetInputMode_0040ac90
    L_00425c9f:
        jmp asm_target_00425d72
    L_00425ca4:
        push 96h
    L_00425ca9:
        push 1Eh
    L_00425cab:
        push 41800000h
    L_00425cb0:
        push 42000000h
    L_00425cb5:
        lea esi,[ebp+3C0h]
    L_00425cbb:
        mov dword ptr [ebp+458h],edi
    L_00425cc1:
        push esi
    L_00425cc2:
        mov edx,ebp
    L_00425cc4:
        mov dword ptr [data_00476f78],3F800000h
    L_00425cce:
        call asm_EffectIndicatorPool_AllocateRetail_00427b50
    L_00425cd3:
        mov ecx,esi
    L_00425cd5:
        mov edx,dword ptr [ecx]
    L_00425cd7:
        lea eax,[ebp+440h]
    L_00425cdd:
        mov dword ptr [eax],edx
    L_00425cdf:
        mov edx,dword ptr [ecx+4]
    L_00425ce2:
        mov ecx,dword ptr [ecx+8]
    L_00425ce5:
        mov dword ptr [eax+4],edx
    L_00425ce8:
        mov dword ptr [eax+8],ecx
    L_00425ceb:
        push 118h
    L_00425cf0:
        lea eax,[ebp+430Ch]
    L_00425cf6:
        mov dword ptr [ebp+3CCh],edi
    L_00425cfc:
        mov dword ptr [ebp+3D0h],0BB80h
    L_00425d06:
        mov dword ptr [esi],edi
    L_00425d08:
        mov dword ptr [ebp+3C4h],43F00000h
    L_00425d12:
        call asm_Player_SetSchedulerValue_00405410
    L_00425d17:
        push edi
    L_00425d18:
        lea eax,[ebp+474h]
    L_00425d1e:
        call asm_Player_SetSchedulerValue_00405410
    L_00425d23:
        jmp short L_00425d72
    L_00425d25:
        mov eax,dword ptr [ebp+478h]
    L_00425d2b:
        cmp eax,4
    L_00425d2e:
        je short L_00425d72
    L_00425d30:
        cmp eax,0Fh
    L_00425d33:
        jne short L_00425d72
    L_00425d35:
        mov esi,dword ptr [data_004776f0]
    L_00425d3b:
        add esi,60h
    L_00425d3e:
        mov edi,7D0h
    L_00425d43:
        mov ax,word ptr [esi+446h]
    L_00425d4a:
        test ax,ax
    L_00425d4d:
        je short L_00425d5a
    L_00425d4f:
        cmp ax,3
    L_00425d53:
        je short L_00425d5a
    L_00425d55:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_00425d5a:
        add esi,7F0h
    L_00425d60:
        dec edi
    L_00425d61:
        jne short L_00425d43
    L_00425d63:
        mov eax,dword ptr [data_0047781c]
    L_00425d68:
        mov ebx,1
    L_00425d6d:
        call asm_FUN_0041c850_0041c850
    L_00425d72:
        lea ebx,[ebp+350Ch]
    L_00425d78:
        lea edi,[ebx+24h]
    L_00425d7b:
        mov dword ptr [esp+30h],20h
    L_00425d83:
        test byte ptr [edi+44h],1
    L_00425d87:
        je asm_target_00425e31
    L_00425d8d:
        test byte ptr [edi+1Ch],1
    L_00425d91:
        jne short L_00425dab
    L_00425d93:
        mov edx,dword ptr [edi+0Ch]
    L_00425d96:
        mov eax,dword ptr [edi+10h]
    L_00425d99:
        push edx
    L_00425d9a:
        push eax
    L_00425d9b:
        mov ecx,edi
    L_00425d9d:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_00425da2:
        mov dword ptr [edi+8],0
    L_00425da9:
        jmp short L_00425dc6
    L_00425dab:
        fld dword ptr [edi+18h]
    L_00425dae:
        push ecx
    L_00425daf:
        fadd dword ptr [edi+14h]
    L_00425db2:
        fstp dword ptr [edi+14h]
    L_00425db5:
        fld dword ptr [edi+0Ch]
    L_00425db8:
        fadd dword ptr [edi+10h]
    L_00425dbb:
        fstp dword ptr [esp]
    L_00425dbe:
        call asm_Angle_Normalize_0044bc70
    L_00425dc3:
        fstp dword ptr [edi+10h]
    L_00425dc6:
        lea esi,[edi-0Ch]
    L_00425dc9:
        call asm_Recovery_AdvancePolarMotion_0044c2a0
    L_00425dce:
        fld dword ptr [edi-20h]
    L_00425dd1:
        fadd dword ptr [ebx]
    L_00425dd3:
        fstp dword ptr [ebx]
    L_00425dd5:
        fld dword ptr [edi-18h]
    L_00425dd8:
        fadd dword ptr [edi-1Ch]
    L_00425ddb:
        fstp dword ptr [edi-1Ch]
    L_00425dde:
        mov ecx,dword ptr [edi+24h]
    L_00425de1:
        mov dword ptr [edi+20h],ecx
    L_00425de4:
        mov ecx,dword ptr [edi+2Ch]
    L_00425de7:
        fld dword ptr [ecx]
    L_00425de9:
        fcomp dword ptr [data_00470b68]
    L_00425def:
        fnstsw ax
    L_00425df1:
        test ah,41h
    L_00425df4:
        jne short L_00425e10
    L_00425df6:
        fld dword ptr [ecx]
    L_00425df8:
        fcomp dword ptr [data_00470b64]
    L_00425dfe:
        fnstsw ax
    L_00425e00:
        test ah,5
    L_00425e03:
        jp short L_00425e10
    L_00425e05:
        fld dword ptr [edi+28h]
    L_00425e08:
        fsub dword ptr [data_00470afc]
    L_00425e0e:
        jmp short L_00425e1b
    L_00425e10:
        fld dword ptr [ecx]
    L_00425e12:
        fmul dword ptr [data_00470afc]
    L_00425e18:
        fsubr dword ptr [edi+28h]
    L_00425e1b:
        fstp dword ptr [edi+28h]
    L_00425e1e:
        fld dword ptr [edi+28h]
    L_00425e21:
        call asm_FUN_00463b2c_00463b2c
    L_00425e26:
        test eax,eax
    L_00425e28:
        mov dword ptr [edi+24h],eax
    L_00425e2b:
        jg short L_00425e31
    L_00425e2d:
        and dword ptr [edi+44h],0FFFFFFFEh
    L_00425e31:
        mov eax,dword ptr [esp+30h]
    L_00425e35:
        add ebx,6Ch
    L_00425e38:
        add edi,6Ch
    L_00425e3b:
        dec eax
    L_00425e3c:
        mov dword ptr [esp+30h],eax
    L_00425e40:
        jne asm_target_00425d83
    L_00425e46:
        mov eax,dword ptr [ebp+4310h]
    L_00425e4c:
        xor edi,edi
    L_00425e4e:
        cmp eax,edi
    L_00425e50:
        jle asm_target_00425ee6
    L_00425e56:
        mov ecx,dword ptr [ebp+4318h]
    L_00425e5c:
        mov edx,eax
    L_00425e5e:
        mov dword ptr [ebp+430Ch],edx
    L_00425e64:
        fld dword ptr [ecx]
    L_00425e66:
        fcomp dword ptr [data_00470b68]
    L_00425e6c:
        fnstsw ax
    L_00425e6e:
        test ah,41h
    L_00425e71:
        jne short L_00425e90
    L_00425e73:
        fld dword ptr [ecx]
    L_00425e75:
        fcomp dword ptr [data_00470b64]
    L_00425e7b:
        fnstsw ax
    L_00425e7d:
        test ah,5
    L_00425e80:
        jp short L_00425e90
    L_00425e82:
        fld dword ptr [ebp+4314h]
    L_00425e88:
        fsub dword ptr [data_00470afc]
    L_00425e8e:
        jmp short L_00425e9e
    L_00425e90:
        fld dword ptr [ecx]
    L_00425e92:
        fmul dword ptr [data_00470afc]
    L_00425e98:
        fsubr dword ptr [ebp+4314h]
    L_00425e9e:
        fstp dword ptr [ebp+4314h]
    L_00425ea4:
        fld dword ptr [ebp+4314h]
    L_00425eaa:
        call asm_FUN_00463b2c_00463b2c
    L_00425eaf:
        mov dword ptr [ebp+4310h],eax
    L_00425eb5:
        mov eax,dword ptr [ebp+478h]
    L_00425ebb:
        cmp eax,dword ptr [ebp+474h]
    L_00425ec1:
        je short L_00425ee6
    L_00425ec3:
        cdq
    L_00425ec4:
        mov ecx,3
    L_00425ec9:
        idiv ecx
    L_00425ecb:
        test edx,edx
    L_00425ecd:
        jne short L_00425ee6
    L_00425ecf:
        mov eax,dword ptr [ebp+370h]
    L_00425ed5:
        mov dword ptr [ebp+314h],0FF0000FFh
    L_00425edf:
        or eax,8000h
    L_00425ee4:
        jmp short L_00425ef1
    L_00425ee6:
        mov eax,dword ptr [ebp+370h]
    L_00425eec:
        and eax,0FFFF7FFFh
    L_00425ef1:
        lea edx,[ebp+14h]
    L_00425ef4:
        push edx
    L_00425ef5:
        mov dword ptr [ebp+370h],eax
    L_00425efb:
        call asm_FUN_0043ee30_0043ee30
    L_00425f00:
        fld dword ptr [ebp+3C0h]
    L_00425f06:
        fsub dword ptr [ebp+41Ch]
    L_00425f0c:
        lea eax,[ebp+404h]
    L_00425f12:
        fstp dword ptr [esp+14h]
    L_00425f16:
        mov ecx,dword ptr [esp+14h]
    L_00425f1a:
        fld dword ptr [ebp+3C4h]
    L_00425f20:
        fsub dword ptr [ebp+420h]
    L_00425f26:
        fstp dword ptr [esp+18h]
    L_00425f2a:
        mov edx,dword ptr [esp+18h]
    L_00425f2e:
        fld dword ptr [ebp+3C8h]
    L_00425f34:
        fsub dword ptr [ebp+424h]
    L_00425f3a:
        mov dword ptr [eax],ecx
    L_00425f3c:
        mov dword ptr [eax+4],edx
    L_00425f3f:
        lea edx,[ebp+410h]
    L_00425f45:
        fstp dword ptr [esp+1Ch]
    L_00425f49:
        mov ecx,dword ptr [esp+1Ch]
    L_00425f4d:
        mov dword ptr [eax+8],ecx
    L_00425f50:
        fld dword ptr [ebp+41Ch]
    L_00425f56:
        fadd dword ptr [ebp+3C0h]
    L_00425f5c:
        fstp dword ptr [esp+14h]
    L_00425f60:
        mov eax,dword ptr [esp+14h]
    L_00425f64:
        fld dword ptr [ebp+420h]
    L_00425f6a:
        fadd dword ptr [ebp+3C4h]
    L_00425f70:
        fstp dword ptr [esp+18h]
    L_00425f74:
        mov ecx,dword ptr [esp+18h]
    L_00425f78:
        fld dword ptr [ebp+424h]
    L_00425f7e:
        fadd dword ptr [ebp+3C8h]
    L_00425f84:
        mov dword ptr [edx],eax
    L_00425f86:
        mov dword ptr [edx+4],ecx
    L_00425f89:
        lea ecx,[ebp+4324h]
    L_00425f8f:
        fstp dword ptr [esp+1Ch]
    L_00425f93:
        mov eax,dword ptr [esp+1Ch]
    L_00425f97:
        mov dword ptr [edx+8],eax
    L_00425f9a:
        fld dword ptr [ebp+428h]
    L_00425fa0:
        fmul dword ptr [data_00470b0c]
    L_00425fa6:
        fld dword ptr [ebp+42Ch]
    L_00425fac:
        fmul dword ptr [data_00470b0c]
    L_00425fb2:
        fld dword ptr [ebp+430h]
    L_00425fb8:
        fmul dword ptr [data_00470b0c]
    L_00425fbe:
        fstp dword ptr [esp+28h]
    L_00425fc2:
        fld dword ptr [ebp+3C0h]
    L_00425fc8:
        fsub st,st(2)
    L_00425fca:
        fstp dword ptr [esp+14h]
    L_00425fce:
        mov edx,dword ptr [esp+14h]
    L_00425fd2:
        fld dword ptr [ebp+3C4h]
    L_00425fd8:
        fsub st,st(1)
    L_00425fda:
        fstp dword ptr [esp+18h]
    L_00425fde:
        mov eax,dword ptr [esp+18h]
    L_00425fe2:
        fstp st(0)
    L_00425fe4:
        fstp st(0)
    L_00425fe6:
        fld dword ptr [ebp+3C8h]
    L_00425fec:
        mov dword ptr [ecx],edx
    L_00425fee:
        fsub dword ptr [esp+28h]
    L_00425ff2:
        mov dword ptr [ecx+4],eax
    L_00425ff5:
        lea eax,[ebp+4330h]
    L_00425ffb:
        fstp dword ptr [esp+1Ch]
    L_00425fff:
        mov edx,dword ptr [esp+1Ch]
    L_00426003:
        mov dword ptr [ecx+8],edx
    L_00426006:
        fld dword ptr [ebp+428h]
    L_0042600c:
        fmul dword ptr [data_00470b0c]
    L_00426012:
        fld dword ptr [ebp+42Ch]
    L_00426018:
        fmul dword ptr [data_00470b0c]
    L_0042601e:
        fld dword ptr [ebp+430h]
    L_00426024:
        fmul dword ptr [data_00470b0c]
    L_0042602a:
        fstp dword ptr [esp+28h]
    L_0042602e:
        fxch
    L_00426030:
        fadd dword ptr [ebp+3C0h]
    L_00426036:
        fstp dword ptr [esp+14h]
    L_0042603a:
        mov ecx,dword ptr [esp+14h]
    L_0042603e:
        fadd dword ptr [ebp+3C4h]
    L_00426044:
        fstp dword ptr [esp+18h]
    L_00426048:
        mov edx,dword ptr [esp+18h]
    L_0042604c:
        fld dword ptr [esp+28h]
    L_00426050:
        fadd dword ptr [ebp+3C8h]
    L_00426056:
        mov dword ptr [eax],ecx
    L_00426058:
        mov dword ptr [eax+4],edx
    L_0042605b:
        fstp dword ptr [esp+1Ch]
    L_0042605f:
        mov ecx,dword ptr [esp+1Ch]
    L_00426063:
        mov dword ptr [eax+8],ecx
    L_00426066:
        fld dword ptr [ebp+3C0h]
    L_0042606c:
        fsub dword ptr [ebp+434h]
    L_00426072:
        lea edx,[ebp+433Ch]
    L_00426078:
        fstp dword ptr [esp+14h]
    L_0042607c:
        mov eax,dword ptr [esp+14h]
    L_00426080:
        fld dword ptr [ebp+3C4h]
    L_00426086:
        fsub dword ptr [ebp+438h]
    L_0042608c:
        fstp dword ptr [esp+18h]
    L_00426090:
        mov ecx,dword ptr [esp+18h]
    L_00426094:
        fld dword ptr [ebp+3C8h]
    L_0042609a:
        fsub dword ptr [ebp+43Ch]
    L_004260a0:
        mov dword ptr [edx],eax
    L_004260a2:
        mov dword ptr [edx+4],ecx
    L_004260a5:
        lea ecx,[ebp+4348h]
    L_004260ab:
        fstp dword ptr [esp+1Ch]
    L_004260af:
        mov eax,dword ptr [esp+1Ch]
    L_004260b3:
        mov dword ptr [edx+8],eax
    L_004260b6:
        fld dword ptr [ebp+434h]
    L_004260bc:
        fadd dword ptr [ebp+3C0h]
    L_004260c2:
        fstp dword ptr [esp+14h]
    L_004260c6:
        mov edx,dword ptr [esp+14h]
    L_004260ca:
        fld dword ptr [ebp+438h]
    L_004260d0:
        fadd dword ptr [ebp+3C4h]
    L_004260d6:
        fstp dword ptr [esp+18h]
    L_004260da:
        mov eax,dword ptr [esp+18h]
    L_004260de:
        fld dword ptr [ebp+43Ch]
    L_004260e4:
        fadd dword ptr [ebp+3C8h]
    L_004260ea:
        mov dword ptr [ecx],edx
    L_004260ec:
        mov dword ptr [ecx+4],eax
    L_004260ef:
        lea eax,[ebp+4354h]
    L_004260f5:
        fstp dword ptr [esp+1Ch]
    L_004260f9:
        mov edx,dword ptr [esp+1Ch]
    L_004260fd:
        mov dword ptr [ecx+8],edx
    L_00426100:
        fld dword ptr [ebp+3C0h]
    L_00426106:
        fsub dword ptr [ebp+428h]
    L_0042610c:
        fstp dword ptr [esp+14h]
    L_00426110:
        mov ecx,dword ptr [esp+14h]
    L_00426114:
        fld dword ptr [ebp+3C4h]
    L_0042611a:
        fsub dword ptr [ebp+42Ch]
    L_00426120:
        fstp dword ptr [esp+18h]
    L_00426124:
        mov edx,dword ptr [esp+18h]
    L_00426128:
        fld dword ptr [ebp+3C8h]
    L_0042612e:
        fsub dword ptr [ebp+430h]
    L_00426134:
        mov dword ptr [eax],ecx
    L_00426136:
        mov dword ptr [eax+4],edx
    L_00426139:
        lea edx,[ebp+4360h]
    L_0042613f:
        fstp dword ptr [esp+1Ch]
    L_00426143:
        mov ecx,dword ptr [esp+1Ch]
    L_00426147:
        mov dword ptr [eax+8],ecx
    L_0042614a:
        fld dword ptr [ebp+428h]
    L_00426150:
        fadd dword ptr [ebp+3C0h]
    L_00426156:
        fstp dword ptr [esp+14h]
    L_0042615a:
        mov eax,dword ptr [esp+14h]
    L_0042615e:
        fld dword ptr [ebp+42Ch]
    L_00426164:
        fadd dword ptr [ebp+3C4h]
    L_0042616a:
        fstp dword ptr [esp+18h]
    L_0042616e:
        mov ecx,dword ptr [esp+18h]
    L_00426172:
        fld dword ptr [ebp+430h]
    L_00426178:
        fadd dword ptr [ebp+3C8h]
    L_0042617e:
        mov dword ptr [edx],eax
    L_00426180:
        mov dword ptr [edx+4],ecx
    L_00426183:
        fstp dword ptr [esp+1Ch]
    L_00426187:
        mov eax,dword ptr [esp+1Ch]
    L_0042618b:
        mov dword ptr [edx+8],eax
    L_0042618e:
        mov edx,dword ptr [ebp+478h]
    L_00426194:
        mov ecx,dword ptr [ebp+480h]
    L_0042619a:
        mov dword ptr [ebp+474h],edx
    L_004261a0:
        fld dword ptr [ecx]
    L_004261a2:
        fcomp dword ptr [data_00470b68]
    L_004261a8:
        fnstsw ax
    L_004261aa:
        test ah,41h
    L_004261ad:
        jne short L_004261d9
    L_004261af:
        fld dword ptr [ecx]
    L_004261b1:
        fcomp dword ptr [data_00470b64]
    L_004261b7:
        fnstsw ax
    L_004261b9:
        test ah,5
    L_004261bc:
        jp short L_004261d9
    L_004261be:
        fld dword ptr [ebp+47Ch]
    L_004261c4:
        inc edx
    L_004261c5:
        fadd dword ptr [data_00470afc]
    L_004261cb:
        mov dword ptr [ebp+478h],edx
    L_004261d1:
        fstp dword ptr [ebp+47Ch]
    L_004261d7:
        jmp short L_004261f2
    L_004261d9:
        fld dword ptr [ecx]
    L_004261db:
        fadd dword ptr [ebp+47Ch]
    L_004261e1:
        fst dword ptr [ebp+47Ch]
    L_004261e7:
        call asm_FUN_00463b2c_00463b2c
    L_004261ec:
        mov dword ptr [ebp+478h],eax
    L_004261f2:
        mov edx,dword ptr [ebp+48Ch]
    L_004261f8:
        mov ecx,dword ptr [ebp+494h]
    L_004261fe:
        mov dword ptr [ebp+488h],edx
    L_00426204:
        fld dword ptr [ecx]
    L_00426206:
        fcomp dword ptr [data_00470b68]
    L_0042620c:
        fnstsw ax
    L_0042620e:
        test ah,41h
    L_00426211:
        jne short L_0042623d
    L_00426213:
        fld dword ptr [ecx]
    L_00426215:
        fcomp dword ptr [data_00470b64]
    L_0042621b:
        fnstsw ax
    L_0042621d:
        test ah,5
    L_00426220:
        jp short L_0042623d
    L_00426222:
        fld dword ptr [ebp+490h]
    L_00426228:
        inc edx
    L_00426229:
        fadd dword ptr [data_00470afc]
    L_0042622f:
        mov dword ptr [ebp+48Ch],edx
    L_00426235:
        fstp dword ptr [ebp+490h]
    L_0042623b:
        jmp short L_00426256
    L_0042623d:
        fld dword ptr [ecx]
    L_0042623f:
        fadd dword ptr [ebp+490h]
    L_00426245:
        fst dword ptr [ebp+490h]
    L_0042624b:
        call asm_FUN_00463b2c_00463b2c
    L_00426250:
        mov dword ptr [ebp+48Ch],eax
    L_00426256:
        mov esi,dword ptr [data_0047770c]
    L_0042625c:
        cmp dword ptr [esi+9EB8h],edi
    L_00426262:
        mov ecx,dword ptr [data_00477704]
    L_00426268:
        jne short L_004262ce
    L_0042626a:
        cmp ecx,edi
    L_0042626c:
        je short L_004262b4
    L_0042626e:
        cmp dword ptr [ecx+60h],edi
    L_00426271:
        je short L_004262b4
    L_00426273:
        mov eax,dword ptr [ebp+478h]
    L_00426279:
        cdq
    L_0042627a:
        mov ebx,3Ch
    L_0042627f:
        idiv ebx
    L_00426281:
        test edx,edx
    L_00426283:
        jne short L_004262b4
    L_00426285:
        mov eax,dword ptr [data_00474c98]
    L_0042628a:
        inc eax
    L_0042628b:
        cmp eax,400h
    L_00426290:
        mov dword ptr [data_00474c98],eax
    L_00426295:
        jle short L_004262a3
    L_00426297:
        mov dword ptr [data_00474c98],400h
    L_004262a1:
        jmp short L_004262b4
    L_004262a3:
        cmp eax,0FFFFFC00h
    L_004262a8:
        jge short L_004262b4
    L_004262aa:
        mov dword ptr [data_00474c98],0FFFFFC00h
    L_004262b4:
        cmp dword ptr [esi+9EB8h],edi
    L_004262ba:
        jne short L_004262ce
    L_004262bc:
        cmp ecx,edi
    L_004262be:
        je short L_004262ce
    L_004262c0:
        cmp dword ptr [ecx+60h],edi
    L_004262c3:
        je short L_004262ce
    L_004262c5:
        mov eax,ebp
    L_004262c7:
        call asm_Recovery_UpdateStageSequence_004281d0
    L_004262cc:
        jmp short L_0042632c
    L_004262ce:
        mov eax,dword ptr [ebp+470h]
    L_004262d4:
        test al,1
    L_004262d6:
        jne short L_00426301
    L_004262d8:
        or eax,1
    L_004262db:
        mov dword ptr [ebp+464h],edi
    L_004262e1:
        mov dword ptr [ebp+460h],0FFF0BDC1h
    L_004262eb:
        mov dword ptr [ebp+468h],edi
    L_004262f1:
        mov dword ptr [ebp+46Ch],476F78h
    L_004262fb:
        mov dword ptr [ebp+470h],eax
    L_00426301:
        mov dword ptr [ebp+464h],0FFFFFFFFh
    L_0042630b:
        mov dword ptr [ebp+468h],0BF800000h
    L_00426315:
        mov dword ptr [ebp+460h],0FFFFFFFEh
    L_0042631f:
        mov dword ptr [ebp+3504h],edi
    L_00426325:
        mov byte ptr [ebp+3508h],0
    L_0042632c:
        push ebp
    L_0042632d:
        call asm_FUN_00428280_00428280
    L_00426332:
        pop edi
    L_00426333:
        pop esi
    L_00426334:
        pop ebp
    L_00426335:
        mov eax,1
    L_0042633a:
        pop ebx
    L_0042633b:
        add esp,1Ch
    L_0042633e:
        ret 4
    }
}

// 0x00426F70..0x00427019: FUN_00426f70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426f70_00426f70() {
    __asm {
    L_00426f70:
        sub esp,38h
    L_00426f73:
        mov cx,word ptr [data_00474c48]
    L_00426f7a:
        movsx edx,cx
    L_00426f7d:
        mov eax,66666667h
    L_00426f82:
        imul edx
    L_00426f84:
        sar edx,3
    L_00426f87:
        push ebx
    L_00426f88:
        push ebp
    L_00426f89:
        mov ebp,dword ptr [esp+44h]
    L_00426f8d:
        mov eax,edx
    L_00426f8f:
        shr eax,1Fh
    L_00426f92:
        add eax,edx
    L_00426f94:
        cmp cx,64h
    L_00426f98:
        push esi
    L_00426f99:
        push edi
    L_00426f9a:
        mov dword ptr [esp+4Ch],eax
    L_00426f9e:
        mov ebx,4000000h
    L_00426fa3:
        jl asm_target_004270e6
    L_00426fa9:
        lea esi,[ebp+330Ch]
    L_00426faf:
        mov dword ptr [esp+10h],4
    L_00426fb7:
        mov ecx,dword ptr [esi]
    L_00426fb9:
        test ecx,ecx
    L_00426fbb:
        TH10_REL8(0x74, 0x00426fbb, VA_asm_target_0042702f)
    L_00426fbd:
        mov edx,dword ptr [data_00491c10]
    L_00426fc3:
        mov eax,dword ptr [edx+72DAD4h]
    L_00426fc9:
        test eax,eax
    L_00426fcb:
        je short L_00426fdd
    L_00426fcd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00426fd0:
        mov edi,dword ptr [eax]
    L_00426fd2:
        cmp dword ptr [edi],ecx
    L_00426fd4:
        je short L_00426ff6
    L_00426fd6:
        mov eax,dword ptr [eax+4]
    L_00426fd9:
        test eax,eax
    L_00426fdb:
        jne short L_00426fd0
    L_00426fdd:
        mov eax,dword ptr [edx+72DADCh]
    L_00426fe3:
        test eax,eax
    L_00426fe5:
        TH10_REL8(0x74, 0x00426fe5, VA_asm_target_0042702f)
    L_00426fe7:
        mov edx,dword ptr [eax]
    L_00426fe9:
        cmp dword ptr [edx],ecx
    L_00426feb:
        je short L_00426ff6
    L_00426fed:
        mov eax,dword ptr [eax+4]
    L_00426ff0:
        test eax,eax
    L_00426ff2:
        jne short L_00426fe7
    L_00426ff4:
        TH10_REL8(0xeb, 0x00426ff4, VA_asm_target_0042702f)
    L_00426ff6:
        mov eax,dword ptr [eax]
    L_00426ff8:
        test eax,eax
    L_00426ffa:
        TH10_REL8(0x74, 0x00426ffa, VA_asm_target_0042702f)
    L_00426ffc:
        mov edx,dword ptr [eax+35Ch]
    L_00427002:
        mov ecx,dword ptr [eax+18h]
    L_00427005:
        or edx,ebx
    L_00427007:
        test ecx,ecx
    L_00427009:
        mov dword ptr [eax+35Ch],edx
    L_0042700f:
        TH10_REL8(0x75, 0x0042700f, VA_asm_target_0042702f)
    L_00427011:
        mov eax,dword ptr [eax+14h]
    L_00427014:
        test eax,eax
    L_00427016:
        TH10_REL8(0x74, 0x00427016, VA_asm_target_0042702f)
    L_00427018:
        TH10_REL8(0xeb, 0x00427018, VA_asm_FUN_00426f70_part_00427020)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00427020:
        mov ecx,dword ptr [eax]
    L_00427022:
        or dword ptr [ecx+35Ch],ebx
    L_00427028:
        mov eax,dword ptr [eax+4]
    L_0042702b:
        test eax,eax
    L_0042702d:
        jne short L_00427020
    L_0042702f:
        mov dword ptr [esi],0
    L_00427035:
        mov eax,dword ptr [data_00474c68]
    L_0042703a:
        mov ecx,dword ptr [data_00474c6c]
    L_00427040:
        lea edx,[ecx+eax*2]
    L_00427043:
        add eax,edx
    L_00427045:
        cmp eax,5
    L_00427048:
        ja asm_target_004270cc
    L_0042704e:
        jmp dword ptr [eax*4+427930h]
    L_00427055:
        mov eax,dword ptr [ebp+10h]
    L_00427058:
        push 0Fh
    L_0042705a:
        push 14h
    L_0042705c:
        push eax
    L_0042705d:
        lea edi,[esp+3Ch]
    L_00427061:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_00427066:
        mov ecx,dword ptr [eax]
    L_00427068:
        mov dword ptr [esi],ecx
    L_0042706a:
        jmp short L_004270cc
    L_0042706c:
        mov edx,dword ptr [ebp+10h]
    L_0042706f:
        push 0Fh
    L_00427071:
        push 15h
    L_00427073:
        push edx
    L_00427074:
        lea edi,[esp+40h]
    L_00427078:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0042707d:
        mov eax,dword ptr [eax]
    L_0042707f:
        mov dword ptr [esi],eax
    L_00427081:
        jmp short L_004270cc
    L_00427083:
        lea edi,[esp+38h]
    L_00427087:
        jmp short L_004270bb
    L_00427089:
        mov eax,dword ptr [ebp+10h]
    L_0042708c:
        push 0Fh
    L_0042708e:
        push 14h
    L_00427090:
        push eax
    L_00427091:
        lea edi,[esp+48h]
    L_00427095:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_0042709a:
        mov ecx,dword ptr [eax]
    L_0042709c:
        mov dword ptr [esi],ecx
    L_0042709e:
        jmp short L_004270cc
    L_004270a0:
        mov edx,dword ptr [ebp+10h]
    L_004270a3:
        push 0Fh
    L_004270a5:
        push 15h
    L_004270a7:
        push edx
    L_004270a8:
        lea edi,[esp+4Ch]
    L_004270ac:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_004270b1:
        mov eax,dword ptr [eax]
    L_004270b3:
        mov dword ptr [esi],eax
    L_004270b5:
        jmp short L_004270cc
    L_004270b7:
        lea edi,[esp+44h]
    L_004270bb:
        mov ecx,dword ptr [ebp+10h]
    L_004270be:
        push 0Fh
    L_004270c0:
        push 16h
    L_004270c2:
        push ecx
    L_004270c3:
        call asm_AnimationManager_CreatePrimaryFront_00448e30
    L_004270c8:
        mov edx,dword ptr [eax]
    L_004270ca:
        mov dword ptr [esi],edx
    L_004270cc:
        mov eax,dword ptr [esp+10h]
    L_004270d0:
        add esi,98h
    L_004270d6:
        dec eax
    L_004270d7:
        mov dword ptr [esp+10h],eax
    L_004270db:
        jne asm_target_00426fb7
    L_004270e1:
        jmp asm_target_00427169
    L_004270e6:
        mov ebx,dword ptr [data_00491c10]
    L_004270ec:
        lea edx,[ebp+330Ch]
    L_004270f2:
        mov esi,4
    L_004270f7:
        mov ecx,dword ptr [edx]
    L_004270f9:
        test ecx,ecx
    L_004270fb:
        je short L_00427160
    L_004270fd:
        mov eax,dword ptr [ebx+72DAD4h]
    L_00427103:
        test eax,eax
    L_00427105:
        je short L_00427114
    L_00427107:
        mov edi,dword ptr [eax]
    L_00427109:
        cmp dword ptr [edi],ecx
    L_0042710b:
        je short L_0042712f
    L_0042710d:
        mov eax,dword ptr [eax+4]
    L_00427110:
        test eax,eax
    L_00427112:
        jne short L_00427107
    L_00427114:
        mov eax,dword ptr [ebx+72DADCh]
    L_0042711a:
        test eax,eax
    L_0042711c:
        je short L_00427160
    L_0042711e:
        mov edi,edi
    L_00427120:
        mov edi,dword ptr [eax]
    L_00427122:
        cmp dword ptr [edi],ecx
    L_00427124:
        je short L_0042712f
    L_00427126:
        mov eax,dword ptr [eax+4]
    L_00427129:
        test eax,eax
    L_0042712b:
        jne short L_00427120
    L_0042712d:
        jmp short L_00427160
    L_0042712f:
        mov eax,dword ptr [eax]
    L_00427131:
        test eax,eax
    L_00427133:
        je short L_00427160
    L_00427135:
        mov edi,dword ptr [eax+18h]
    L_00427138:
        test edi,edi
    L_0042713a:
        mov ecx,1
    L_0042713f:
        mov word ptr [eax+304h],cx
    L_00427146:
        jne short L_00427160
    L_00427148:
        mov eax,dword ptr [eax+14h]
    L_0042714b:
        test eax,eax
    L_0042714d:
        je short L_00427160
    L_0042714f:
        nop
    L_00427150:
        mov edi,dword ptr [eax]
    L_00427152:
        mov word ptr [edi+304h],cx
    L_00427159:
        mov eax,dword ptr [eax+4]
    L_0042715c:
        test eax,eax
    L_0042715e:
        jne short L_00427150
    L_00427160:
        add edx,98h
    L_00427166:
        dec esi
    L_00427167:
        jne short L_004270f7
    L_00427169:
        mov eax,dword ptr [esp+4Ch]
    L_0042716d:
        cmp eax,5
    L_00427170:
        jl short L_0042717b
    L_00427172:
        mov eax,4
    L_00427177:
        mov dword ptr [esp+4Ch],eax
    L_0042717b:
        cmp dword ptr [ebp+3500h],eax
    L_00427181:
        je asm_target_00427924
    L_00427187:
        xor esi,esi
    L_00427189:
        test eax,eax
    L_0042718b:
        mov dword ptr [esp+10h],esi
    L_0042718f:
        jle asm_target_00427857
    L_00427195:
        TH10_REL8(0xeb, 0x00427195, VA_asm_FUN_00426f70_part_004271a0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_004271a0:
        mov ecx,dword ptr [ebp+3CCh]
    L_004271a6:
        mov eax,esi
    L_004271a8:
        imul eax,98h
    L_004271ae:
        lea edi,[eax+ebp]
    L_004271b1:
        mov dword ptr [edi+32DCh],ecx
    L_004271b7:
        mov edx,dword ptr [ebp+3D0h]
    L_004271bd:
        mov dword ptr [edi+32E0h],edx
    L_004271c3:
        mov ecx,dword ptr [edi+3308h]
    L_004271c9:
        test ecx,ecx
    L_004271cb:
        je short L_0042723f
    L_004271cd:
        mov edx,dword ptr [data_00491c10]
    L_004271d3:
        mov eax,dword ptr [edx+72DAD4h]
    L_004271d9:
        test eax,eax
    L_004271db:
        je short L_004271ed
    L_004271dd:
        TH10_NOP_LEA_ECX_DISP8()
    L_004271e0:
        mov ebx,dword ptr [eax]
    L_004271e2:
        cmp dword ptr [ebx],ecx
    L_004271e4:
        je short L_00427206
    L_004271e6:
        mov eax,dword ptr [eax+4]
    L_004271e9:
        test eax,eax
    L_004271eb:
        jne short L_004271e0
    L_004271ed:
        mov eax,dword ptr [edx+72DADCh]
    L_004271f3:
        test eax,eax
    L_004271f5:
        je short L_0042723f
    L_004271f7:
        mov edx,dword ptr [eax]
    L_004271f9:
        cmp dword ptr [edx],ecx
    L_004271fb:
        je short L_00427206
    L_004271fd:
        mov eax,dword ptr [eax+4]
    L_00427200:
        test eax,eax
    L_00427202:
        jne short L_004271f7
    L_00427204:
        jmp short L_0042723f
    L_00427206:
        mov eax,dword ptr [eax]
    L_00427208:
        test eax,eax
    L_0042720a:
        je short L_0042723f
    L_0042720c:
        mov ebx,dword ptr [eax+35Ch]
    L_00427212:
        mov ecx,dword ptr [eax+18h]
    L_00427215:
        mov edx,4000000h
    L_0042721a:
        or ebx,edx
    L_0042721c:
        test ecx,ecx
    L_0042721e:
        mov dword ptr [eax+35Ch],ebx
    L_00427224:
        jne short L_0042723f
    L_00427226:
        mov eax,dword ptr [eax+14h]
    L_00427229:
        test eax,eax
    L_0042722b:
        je short L_0042723f
    L_0042722d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00427230:
        mov ecx,dword ptr [eax]
    L_00427232:
        or dword ptr [ecx+35Ch],edx
    L_00427238:
        mov eax,dword ptr [eax+4]
    L_0042723b:
        test eax,eax
    L_0042723d:
        jne short L_00427230
    L_0042723f:
        mov dword ptr [edi+3308h],0
    L_00427249:
        mov dword ptr [edi+3328h],esi
    L_0042724f:
        mov eax,dword ptr [data_00474c68]
    L_00427254:
        sub eax,0
    L_00427257:
        je asm_target_0042764e
    L_0042725d:
        dec eax
    L_0042725e:
        jne asm_target_00427833
    L_00427264:
        mov eax,dword ptr [data_00474c6c]
    L_00427269:
        sub eax,0
    L_0042726c:
        je asm_target_0042749b
    L_00427272:
        dec eax
    L_00427273:
        je asm_target_00427381
    L_00427279:
        dec eax
    L_0042727a:
        jne asm_target_00427833
    L_00427280:
        mov eax,dword ptr [esp+4Ch]
    L_00427284:
        mov eax,dword ptr [eax*4+476F7Ch]
    L_0042728b:
        mov edx,dword ptr [ebp+45Ch]
    L_00427291:
        add eax,esi
    L_00427293:
        lea ecx,[eax+eax*2]
    L_00427296:
        fld dword ptr [edx+ecx*4+20h]
    L_0042729a:
        lea esi,[edx+ecx*4+20h]
    L_0042729e:
        fmul dword ptr [data_00470b44]
    L_004272a4:
        call asm_FUN_00463b2c_00463b2c
    L_004272a9:
        mov dword ptr [edi+32E4h],eax
    L_004272af:
        fld dword ptr [esi+4]
    L_004272b2:
        fmul dword ptr [data_00470b44]
    L_004272b8:
        call asm_FUN_00463b2c_00463b2c
    L_004272bd:
        mov dword ptr [edi+32E8h],eax
    L_004272c3:
        mov eax,dword ptr [ebp+4474h]
    L_004272c9:
        test eax,eax
    L_004272cb:
        je short L_004272d7
    L_004272cd:
        mov eax,dword ptr [edi+32A0h]
    L_004272d3:
        test eax,eax
    L_004272d5:
        jne short L_0042730b
    L_004272d7:
        mov eax,dword ptr [ebp+3CCh]
    L_004272dd:
        mov esi,dword ptr [edi+32E4h]
    L_004272e3:
        mov ecx,dword ptr [edi+32E8h]
    L_004272e9:
        mov edx,dword ptr [ebp+3D0h]
    L_004272ef:
        add eax,esi
    L_004272f1:
        add ecx,edx
    L_004272f3:
        mov dword ptr [edi+32D4h],eax
    L_004272f9:
        mov dword ptr [edi+32D8h],ecx
    L_004272ff:
        mov dword ptr [edi+32ECh],eax
    L_00427305:
        mov dword ptr [edi+32F0h],ecx
    L_0042730b:
        mov esi,dword ptr [data_00491c10]
    L_00427311:
        mov ebx,dword ptr [ebp+10h]
    L_00427314:
        call asm_FUN_00449950_00449950
    L_00427319:
        mov esi,eax
    L_0042731b:
        mov eax,dword ptr [esi+35Ch]
    L_00427321:
        push 13h
    L_00427323:
        or eax,40000000h
    L_00427328:
        push esi
    L_00427329:
        mov ecx,ebx
    L_0042732b:
        mov dword ptr [esi+20h],0Fh
    L_00427332:
        mov dword ptr [esi+35Ch],eax
    L_00427338:
        call asm_FUN_00449870_00449870
    L_0042733d:
        mov edx,dword ptr [data_00491c10]
    L_00427343:
        mov ebx,esi
    L_00427345:
        lea eax,[esp+14h]
    L_00427349:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042734e:
        mov eax,dword ptr [esp+14h]
    L_00427352:
        mov dword ptr [edi+3308h],eax
    L_00427358:
        mov eax,dword ptr [ebp+4474h]
    L_0042735e:
        test eax,eax
    L_00427360:
        je short L_00427372
    L_00427362:
        mov esi,3
    L_00427367:
        lea eax,[edi+3308h]
    L_0042736d:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00427372:
        mov dword ptr [edi+3330h],427AD0h
    L_0042737c:
        jmp asm_target_0042782f
    L_00427381:
        mov ecx,dword ptr [esp+4Ch]
    L_00427385:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_0042738c:
        add eax,esi
    L_0042738e:
        lea edx,[eax+eax*2]
    L_00427391:
        mov eax,dword ptr [ebp+45Ch]
    L_00427397:
        fld dword ptr [eax+edx*4+20h]
    L_0042739b:
        lea eax,[eax+edx*4+20h]
    L_0042739f:
        fmul dword ptr [data_00470b44]
    L_004273a5:
        mov dword ptr [esp+18h],eax
    L_004273a9:
        lea ebx,[edi+32E4h]
    L_004273af:
        call asm_FUN_00463b2c_00463b2c
    L_004273b4:
        mov ecx,dword ptr [esp+18h]
    L_004273b8:
        mov dword ptr [ebx],eax
    L_004273ba:
        fld dword ptr [ecx+4]
    L_004273bd:
        fmul dword ptr [data_00470b44]
    L_004273c3:
        call asm_FUN_00463b2c_00463b2c
    L_004273c8:
        mov edx,dword ptr [esp+4Ch]
    L_004273cc:
        mov dword ptr [ebx+4],eax
    L_004273cf:
        mov eax,dword ptr [edx*4+476F7Ch]
    L_004273d6:
        mov ecx,dword ptr [ebp+45Ch]
    L_004273dc:
        add eax,esi
    L_004273de:
        lea eax,[eax+eax*2]
    L_004273e1:
        fld dword ptr [ecx+eax*4+98h]
    L_004273e8:
        lea eax,[ecx+eax*4+98h]
    L_004273ef:
        fmul dword ptr [data_00470b44]
    L_004273f5:
        mov dword ptr [esp+18h],eax
    L_004273f9:
        lea esi,[edi+32ECh]
    L_004273ff:
        call asm_FUN_00463b2c_00463b2c
    L_00427404:
        mov edx,dword ptr [esp+18h]
    L_00427408:
        mov dword ptr [esi],eax
    L_0042740a:
        fld dword ptr [edx+4]
    L_0042740d:
        fmul dword ptr [data_00470b44]
    L_00427413:
        call asm_FUN_00463b2c_00463b2c
    L_00427418:
        mov dword ptr [esi+4],eax
    L_0042741b:
        mov eax,dword ptr [ebp+4474h]
    L_00427421:
        test eax,eax
    L_00427423:
        jne short L_00427427
    L_00427425:
        mov esi,ebx
    L_00427427:
        mov eax,dword ptr [esi]
    L_00427429:
        mov ecx,dword ptr [ebp+3CCh]
    L_0042742f:
        mov ebx,dword ptr [esi+4]
    L_00427432:
        mov esi,dword ptr [data_00491c10]
    L_00427438:
        add eax,ecx
    L_0042743a:
        mov ecx,dword ptr [ebp+3D0h]
    L_00427440:
        add ecx,ebx
    L_00427442:
        mov dword ptr [edi+32D4h],eax
    L_00427448:
        mov dword ptr [edi+32D8h],ecx
    L_0042744e:
        mov ebx,dword ptr [ebp+10h]
    L_00427451:
        call asm_FUN_00449950_00449950
    L_00427456:
        mov esi,eax
    L_00427458:
        mov edx,dword ptr [esi+35Ch]
    L_0042745e:
        push 12h
    L_00427460:
        or edx,40000000h
    L_00427466:
        push esi
    L_00427467:
        mov ecx,ebx
    L_00427469:
        mov dword ptr [esi+20h],0Fh
    L_00427470:
        mov dword ptr [esi+35Ch],edx
    L_00427476:
        call asm_FUN_00449870_00449870
    L_0042747b:
        mov edx,dword ptr [data_00491c10]
    L_00427481:
        mov ebx,esi
    L_00427483:
        lea eax,[esp+1Ch]
    L_00427487:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042748c:
        mov eax,dword ptr [esp+1Ch]
    L_00427490:
        mov dword ptr [edi+3308h],eax
    L_00427496:
        jmp asm_target_0042782f
    L_0042749b:
        mov eax,dword ptr [ebp+4474h]
    L_004274a1:
        test eax,eax
    L_004274a3:
        jne short L_004274e8
    L_004274a5:
        mov ecx,dword ptr [esp+4Ch]
    L_004274a9:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_004274b0:
        add eax,esi
    L_004274b2:
        lea edx,[eax+eax*2]
    L_004274b5:
        mov eax,dword ptr [ebp+45Ch]
    L_004274bb:
        fld dword ptr [eax+edx*4+20h]
    L_004274bf:
        lea ebx,[eax+edx*4+20h]
    L_004274c3:
        fmul dword ptr [data_00470b44]
    L_004274c9:
        call asm_FUN_00463b2c_00463b2c
    L_004274ce:
        mov dword ptr [edi+32E4h],eax
    L_004274d4:
        fld dword ptr [ebx+4]
    L_004274d7:
        fmul dword ptr [data_00470b44]
    L_004274dd:
        call asm_FUN_00463b2c_00463b2c
    L_004274e2:
        mov dword ptr [edi+32E8h],eax
    L_004274e8:
        mov ecx,dword ptr [esp+4Ch]
    L_004274ec:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_004274f3:
        add eax,esi
    L_004274f5:
        lea edx,[eax+eax*2]
    L_004274f8:
        mov eax,dword ptr [ebp+45Ch]
    L_004274fe:
        fld dword ptr [eax+edx*4+98h]
    L_00427505:
        lea ebx,[eax+edx*4+98h]
    L_0042750c:
        fmul dword ptr [data_00470b44]
    L_00427512:
        call asm_FUN_00463b2c_00463b2c
    L_00427517:
        mov dword ptr [edi+32ECh],eax
    L_0042751d:
        fld dword ptr [ebx+4]
    L_00427520:
        fmul dword ptr [data_00470b44]
    L_00427526:
        call asm_FUN_00463b2c_00463b2c
    L_0042752b:
        mov ecx,dword ptr [data_00477834]
    L_00427531:
        mov dword ptr [edi+32F0h],eax
    L_00427537:
        mov eax,esi
    L_00427539:
        shl eax,6
    L_0042753c:
        mov edx,dword ptr [eax+ecx+43ACh]
    L_00427543:
        mov dword ptr [esp+18h],eax
    L_00427547:
        mov dword ptr [edi+32D4h],edx
    L_0042754d:
        mov eax,dword ptr [eax+ecx+43B0h]
    L_00427554:
        mov dword ptr [edi+32D8h],eax
    L_0042755a:
        mov eax,dword ptr [ebp+4474h]
    L_00427560:
        test eax,eax
    L_00427562:
        je short L_004275d3
    L_00427564:
        mov eax,dword ptr [edi+32A0h]
    L_0042756a:
        test eax,eax
    L_0042756c:
        jne short L_004275d3
    L_0042756e:
        test esi,esi
    L_00427570:
        jne short L_004275bb
    L_00427572:
        mov ecx,dword ptr [esp+4Ch]
    L_00427576:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_0042757d:
        lea edx,[eax+eax*2]
    L_00427580:
        mov eax,dword ptr [ebp+45Ch]
    L_00427586:
        fld dword ptr [eax+edx*4+98h]
    L_0042758d:
        lea esi,[eax+edx*4+98h]
    L_00427594:
        fmul dword ptr [data_00470b44]
    L_0042759a:
        call asm_FUN_00463b2c_00463b2c
    L_0042759f:
        mov dword ptr [ebp+32E4h],eax
    L_004275a5:
        fld dword ptr [esi+4]
    L_004275a8:
        fmul dword ptr [data_00470b44]
    L_004275ae:
        call asm_FUN_00463b2c_00463b2c
    L_004275b3:
        mov dword ptr [ebp+32E8h],eax
    L_004275b9:
        jmp short L_004275d3
    L_004275bb:
        mov ecx,dword ptr [edi+324Ch]
    L_004275c1:
        mov dword ptr [edi+32E4h],ecx
    L_004275c7:
        mov edx,dword ptr [edi+3250h]
    L_004275cd:
        mov dword ptr [edi+32E8h],edx
    L_004275d3:
        mov esi,dword ptr [data_00491c10]
    L_004275d9:
        mov dword ptr [edi+3330h],427950h
    L_004275e3:
        mov ebx,dword ptr [ebp+10h]
    L_004275e6:
        call asm_FUN_00449950_00449950
    L_004275eb:
        mov esi,eax
    L_004275ed:
        mov edx,dword ptr [esi+35Ch]
    L_004275f3:
        push 11h
    L_004275f5:
        or edx,40000000h
    L_004275fb:
        push esi
    L_004275fc:
        mov ecx,ebx
    L_004275fe:
        mov dword ptr [esi+20h],0Fh
    L_00427605:
        mov dword ptr [esi+35Ch],edx
    L_0042760b:
        call asm_FUN_00449870_00449870
    L_00427610:
        mov edx,dword ptr [data_00491c10]
    L_00427616:
        mov ebx,esi
    L_00427618:
        lea eax,[esp+20h]
    L_0042761c:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00427621:
        mov eax,dword ptr [esp+20h]
    L_00427625:
        mov dword ptr [edi+3308h],eax
    L_0042762b:
        mov eax,dword ptr [esp+18h]
    L_0042762f:
        mov ecx,dword ptr [eax+ebp+436Ch]
    L_00427636:
        mov dword ptr [edi+32DCh],ecx
    L_0042763c:
        mov edx,dword ptr [eax+ebp+4370h]
    L_00427643:
        mov dword ptr [edi+32E0h],edx
    L_00427649:
        jmp asm_target_0042782f
    L_0042764e:
        mov eax,dword ptr [esp+4Ch]
    L_00427652:
        mov eax,dword ptr [eax*4+476F7Ch]
    L_00427659:
        mov edx,dword ptr [ebp+45Ch]
    L_0042765f:
        add eax,esi
    L_00427661:
        lea ecx,[eax+eax*2]
    L_00427664:
        fld dword ptr [edx+ecx*4+20h]
    L_00427668:
        lea eax,[edx+ecx*4+20h]
    L_0042766c:
        fmul dword ptr [data_00470b44]
    L_00427672:
        mov dword ptr [esp+18h],eax
    L_00427676:
        lea ebx,[edi+32E4h]
    L_0042767c:
        call asm_FUN_00463b2c_00463b2c
    L_00427681:
        mov dword ptr [ebx],eax
    L_00427683:
        mov eax,dword ptr [esp+18h]
    L_00427687:
        fld dword ptr [eax+4]
    L_0042768a:
        fmul dword ptr [data_00470b44]
    L_00427690:
        call asm_FUN_00463b2c_00463b2c
    L_00427695:
        mov ecx,dword ptr [esp+4Ch]
    L_00427699:
        mov dword ptr [ebx+4],eax
    L_0042769c:
        mov eax,dword ptr [ecx*4+476F7Ch]
    L_004276a3:
        add eax,esi
    L_004276a5:
        lea edx,[eax+eax*2]
    L_004276a8:
        mov eax,dword ptr [ebp+45Ch]
    L_004276ae:
        fld dword ptr [eax+edx*4+98h]
    L_004276b5:
        lea eax,[eax+edx*4+98h]
    L_004276bc:
        fmul dword ptr [data_00470b44]
    L_004276c2:
        mov dword ptr [esp+18h],eax
    L_004276c6:
        call asm_FUN_00463b2c_00463b2c
    L_004276cb:
        mov ecx,dword ptr [esp+18h]
    L_004276cf:
        mov dword ptr [edi+32ECh],eax
    L_004276d5:
        fld dword ptr [ecx+4]
    L_004276d8:
        fmul dword ptr [data_00470b44]
    L_004276de:
        call asm_FUN_00463b2c_00463b2c
    L_004276e3:
        mov dword ptr [edi+32F0h],eax
    L_004276e9:
        mov eax,dword ptr [ebp+4474h]
    L_004276ef:
        test eax,eax
    L_004276f1:
        je short L_004276f9
    L_004276f3:
        lea ebx,[edi+32ECh]
    L_004276f9:
        mov ecx,dword ptr [ebx]
    L_004276fb:
        mov eax,dword ptr [ebp+3CCh]
    L_00427701:
        mov edx,dword ptr [ebx+4]
    L_00427704:
        add eax,ecx
    L_00427706:
        mov ecx,dword ptr [ebp+3D0h]
    L_0042770c:
        add ecx,edx
    L_0042770e:
        mov dword ptr [edi+32D4h],eax
    L_00427714:
        mov dword ptr [edi+32D8h],ecx
    L_0042771a:
        mov dword ptr [edi+32DCh],eax
    L_00427720:
        mov dword ptr [edi+32E0h],ecx
    L_00427726:
        mov eax,dword ptr [data_00474c6c]
    L_0042772b:
        sub eax,0
    L_0042772e:
        je asm_target_004277e1
    L_00427734:
        dec eax
    L_00427735:
        je short L_00427791
    L_00427737:
        dec eax
    L_00427738:
        jne asm_target_00427833
    L_0042773e:
        mov esi,dword ptr [data_00491c10]
    L_00427744:
        mov ebx,dword ptr [ebp+10h]
    L_00427747:
        call asm_FUN_00449950_00449950
    L_0042774c:
        mov esi,eax
    L_0042774e:
        mov edx,dword ptr [esi+35Ch]
    L_00427754:
        push 13h
    L_00427756:
        or edx,40000000h
    L_0042775c:
        push esi
    L_0042775d:
        mov ecx,ebx
    L_0042775f:
        mov dword ptr [esi+20h],0Fh
    L_00427766:
        mov dword ptr [esi+35Ch],edx
    L_0042776c:
        call asm_FUN_00449870_00449870
    L_00427771:
        mov edx,dword ptr [data_00491c10]
    L_00427777:
        mov ebx,esi
    L_00427779:
        lea eax,[esp+24h]
    L_0042777d:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00427782:
        mov edx,dword ptr [esp+24h]
    L_00427786:
        mov dword ptr [edi+3308h],edx
    L_0042778c:
        jmp asm_target_0042782f
    L_00427791:
        mov esi,dword ptr [data_00491c10]
    L_00427797:
        mov ebx,dword ptr [ebp+10h]
    L_0042779a:
        call asm_FUN_00449950_00449950
    L_0042779f:
        mov esi,eax
    L_004277a1:
        mov edx,dword ptr [esi+35Ch]
    L_004277a7:
        push 12h
    L_004277a9:
        or edx,40000000h
    L_004277af:
        push esi
    L_004277b0:
        mov ecx,ebx
    L_004277b2:
        mov dword ptr [esi+20h],0Fh
    L_004277b9:
        mov dword ptr [esi+35Ch],edx
    L_004277bf:
        call asm_FUN_00449870_00449870
    L_004277c4:
        mov edx,dword ptr [data_00491c10]
    L_004277ca:
        mov ebx,esi
    L_004277cc:
        lea eax,[esp+28h]
    L_004277d0:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004277d5:
        mov eax,dword ptr [esp+28h]
    L_004277d9:
        mov dword ptr [edi+3308h],eax
    L_004277df:
        jmp short L_0042782f
    L_004277e1:
        mov esi,dword ptr [data_00491c10]
    L_004277e7:
        mov ebx,dword ptr [ebp+10h]
    L_004277ea:
        call asm_FUN_00449950_00449950
    L_004277ef:
        mov esi,eax
    L_004277f1:
        mov edx,dword ptr [esi+35Ch]
    L_004277f7:
        push 11h
    L_004277f9:
        or edx,40000000h
    L_004277ff:
        push esi
    L_00427800:
        mov ecx,ebx
    L_00427802:
        mov dword ptr [esi+20h],0Fh
    L_00427809:
        mov dword ptr [esi+35Ch],edx
    L_0042780f:
        call asm_FUN_00449870_00449870
    L_00427814:
        mov edx,dword ptr [data_00491c10]
    L_0042781a:
        mov ebx,esi
    L_0042781c:
        lea eax,[esp+2Ch]
    L_00427820:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00427825:
        mov ecx,dword ptr [esp+2Ch]
    L_00427829:
        mov dword ptr [edi+3308h],ecx
    L_0042782f:
        mov esi,dword ptr [esp+10h]
    L_00427833:
        mov eax,dword ptr [esp+4Ch]
    L_00427837:
        inc esi
    L_00427838:
        cmp esi,eax
    L_0042783a:
        mov dword ptr [edi+32A0h],2
    L_00427844:
        mov dword ptr [esp+10h],esi
    L_00427848:
        jl asm_FUN_00426f70_part_004271a0
    L_0042784e:
        cmp esi,4
    L_00427851:
        jge asm_target_004278fd
    L_00427857:
        mov ebx,dword ptr [data_00491c10]
    L_0042785d:
        mov edx,esi
    L_0042785f:
        imul edx,98h
    L_00427865:
        mov edi,4
    L_0042786a:
        lea edx,[edx+ebp+3308h]
    L_00427871:
        sub edi,esi
    L_00427873:
        mov ecx,dword ptr [edx]
    L_00427875:
        test ecx,ecx
    L_00427877:
        mov dword ptr [edx-68h],0
    L_0042787e:
        TH10_REL8(0x74, 0x0042787e, VA_asm_target_004278f0)
    L_00427880:
        mov eax,dword ptr [ebx+72DAD4h]
    L_00427886:
        test eax,eax
    L_00427888:
        je short L_0042789d
    L_0042788a:
        lea ebx,[ebx+force_disp32_zero]
    L_00427890:
        mov esi,dword ptr [eax]
    L_00427892:
        cmp dword ptr [esi],ecx
    L_00427894:
        je short L_004278b6
    L_00427896:
        mov eax,dword ptr [eax+4]
    L_00427899:
        test eax,eax
    L_0042789b:
        jne short L_00427890
    L_0042789d:
        mov eax,dword ptr [ebx+72DADCh]
    L_004278a3:
        test eax,eax
    L_004278a5:
        TH10_REL8(0x74, 0x004278a5, VA_asm_target_004278f0)
    L_004278a7:
        mov esi,dword ptr [eax]
    L_004278a9:
        cmp dword ptr [esi],ecx
    L_004278ab:
        je short L_004278b6
    L_004278ad:
        mov eax,dword ptr [eax+4]
    L_004278b0:
        test eax,eax
    L_004278b2:
        jne short L_004278a7
    L_004278b4:
        TH10_REL8(0xeb, 0x004278b4, VA_asm_target_004278f0)
    L_004278b6:
        mov eax,dword ptr [eax]
    L_004278b8:
        test eax,eax
    L_004278ba:
        TH10_REL8(0x74, 0x004278ba, VA_asm_target_004278f0)
    L_004278bc:
        mov esi,dword ptr [eax+18h]
    L_004278bf:
        test esi,esi
    L_004278c1:
        mov ecx,1
    L_004278c6:
        mov word ptr [eax+304h],cx
    L_004278cd:
        TH10_REL8(0x75, 0x004278cd, VA_asm_target_004278f0)
    L_004278cf:
        mov eax,dword ptr [eax+14h]
    L_004278d2:
        test eax,eax
    L_004278d4:
        TH10_REL8(0x74, 0x004278d4, VA_asm_target_004278f0)
    L_004278d6:
        TH10_REL8(0xeb, 0x004278d6, VA_asm_FUN_00426f70_part_004278e0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_004278e0:
        mov esi,dword ptr [eax]
    L_004278e2:
        mov word ptr [esi+304h],cx
    L_004278e9:
        mov eax,dword ptr [eax+4]
    L_004278ec:
        test eax,eax
    L_004278ee:
        jne short L_004278e0
    L_004278f0:
        add edx,98h
    L_004278f6:
        dec edi
    L_004278f7:
        jne asm_target_00427873
    L_004278fd:
        mov ecx,dword ptr [esp+4Ch]
    L_00427901:
        mov eax,1
    L_00427906:
        mov dword ptr [ebp+3500h],ecx
    L_0042790c:
        mov dword ptr [ebp+332Ch],eax
    L_00427912:
        mov dword ptr [ebp+33C4h],eax
    L_00427918:
        mov dword ptr [ebp+345Ch],eax
    L_0042791e:
        mov dword ptr [ebp+34F4h],eax
    L_00427924:
        pop edi
    L_00427925:
        pop esi
    L_00427926:
        pop ebp
    L_00427927:
        pop ebx
    L_00427928:
        add esp,38h
    L_0042792b:
        ret 4
    }
}
