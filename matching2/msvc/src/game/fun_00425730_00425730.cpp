#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00425730..0x004257C7: FUN_00425730
// Naked body preserves the retail register/stack ABI.

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
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0x51
        _emit 0x57
        _emit 0x42
        _emit 0x00
        _emit 0x64
        _emit 0x59
        _emit 0x42
        _emit 0x00
        _emit 0xa9
        _emit 0x5a
        _emit 0x42
        _emit 0x00
        _emit 0x25
        _emit 0x5d
        _emit 0x42
        _emit 0x00
        _emit 0x96
        _emit 0x5a
        _emit 0x42
        _emit 0x00
    }
}
