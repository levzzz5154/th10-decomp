// BLOCKED (D3305): closest_byte_count=3999/3999; first_diff=none
// (authoritative retail overlay probe exact; no readable candidate retained).
// residual_class=private EDI receiver, private-register AnimationManager
// helper ABIs, and long repeated control-flow/source-shape scheduling with
// x87 volume arithmetic and shared animation-object layout.
// variants_tested=live Ghidra decompilation plus callers/callees
// (0x0042D920; 0x0043E460, 0x0043E5A0, 0x004491C0, 0x00463B2C);
// standalone readable conversion was not retained because the current
// region is kind=asm and native-LTCG selection rejects non-semantic ownership.
// next_lever=schema2 native-LTCG cluster over 0x0042D920 and this member,
// with AnimationManager_Find/ConfigureFromResource/RegisterResource visible.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"




// 0x0042E5A0..0x0042E644: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.

// 0x0042E5A0..0x0042E644: FUN_0042e5a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042e5a0_0042e5a0() {
    __asm {
    L_0042e5a0:
        movsx eax,byte ptr [data_00491d68]
    L_0042e5a7:
        push ebx
    L_0042e5a8:
        push ebp
    L_0042e5a9:
        push esi
    L_0042e5aa:
        xor ebx,ebx
    L_0042e5ac:
        push ebx
    L_0042e5ad:
        mov dword ptr [data_00497854],eax
    L_0042e5b2:
        push 8
    L_0042e5b4:
        mov edx,46ECE8h
    L_0042e5b9:
        mov eax,492590h
    L_0042e5be:
        call asm_AnimationManager_RegisterResource_0043e460
    L_0042e5c3:
        movsx eax,byte ptr [data_00491d69]
    L_0042e5ca:
        cmp eax,ebx
    L_0042e5cc:
        mov dword ptr [data_00497858],eax
    L_0042e5d1:
        je short L_0042e60f
    L_0042e5d3:
        fild dword ptr [data_00497854]
    L_0042e5d9:
        fmul dword ptr [data_00470b00]
    L_0042e5df:
        fsubr dword ptr [data_00470afc]
    L_0042e5e5:
        fld st(0)
    L_0042e5e7:
        fmulp st(1),st
    L_0042e5e9:
        fld st(0)
    L_0042e5eb:
        fmul st,st(1)
    L_0042e5ed:
        fsubr dword ptr [data_00470afc]
    L_0042e5f3:
        fmul dword ptr [data_00470b80]
    L_0042e5f9:
        call asm_FUN_00463b2c_00463b2c
    L_0042e5fe:
        fstp st(0)
    L_0042e600:
        mov ecx,0FFFFEC78h
    L_0042e605:
        sub ecx,eax
    L_0042e607:
        mov dword ptr [data_0049785c],ecx
    L_0042e60d:
        jmp short L_0042e619
    L_0042e60f:
        mov dword ptr [data_0049785c],0FFFFD8F0h
    L_0042e619:
        mov edx,dword ptr [edi+2C8h]
    L_0042e61f:
        mov esi,dword ptr [data_00491c10]
    L_0042e625:
        push edx
    L_0042e626:
        mov edx,esi
    L_0042e628:
        call asm_AnimationManager_Find_004491c0
    L_0042e62d:
        cmp eax,ebx
    L_0042e62f:
        jne short L_0042e637
    L_0042e631:
        mov dword ptr [edi+2C8h],ebx
    L_0042e637:
        add eax,10h
    L_0042e63a:
        cmp eax,ebx
    L_0042e63c:
        mov ecx,25h
    L_0042e641:
        TH10_REL8(0x74, 0x0042e641, VA_asm_target_0042e666)
    L_0042e643:
        TH10_REL8(0xeb, 0x0042e643, VA_asm_FUN_0042e5a0_part_0042e650)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00

    L_0042e650:
        mov edx,dword ptr [eax]
    L_0042e652:
        cmp word ptr [edx+38Ah],cx
    L_0042e659:
        je asm_target_0042ed23
    L_0042e65f:
        mov eax,dword ptr [eax+4]
    L_0042e662:
        cmp eax,ebx
    L_0042e664:
        jne short L_0042e650
    L_0042e666:
        xor eax,eax
    L_0042e668:
        push eax
    L_0042e669:
        mov edx,esi
    L_0042e66b:
        call asm_AnimationManager_Find_004491c0
    L_0042e670:
        mov ecx,eax
    L_0042e672:
        cmp ecx,ebx
    L_0042e674:
        je short L_0042e69d
    L_0042e676:
        movsx edx,byte ptr [data_00491d68]
    L_0042e67d:
        mov eax,51EB851Fh
    L_0042e682:
        imul edx
    L_0042e684:
        sar edx,5
    L_0042e687:
        mov eax,edx
    L_0042e689:
        shr eax,1Fh
    L_0042e68c:
        lea edx,[edx+eax+33h]
    L_0042e690:
        mov eax,ecx
    L_0042e692:
        mov ecx,dword ptr [ecx+308h]
    L_0042e698:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e69d:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e6a3:
        push ecx
    L_0042e6a4:
        mov edx,esi
    L_0042e6a6:
        call asm_AnimationManager_Find_004491c0
    L_0042e6ab:
        cmp eax,ebx
    L_0042e6ad:
        jne short L_0042e6b5
    L_0042e6af:
        mov dword ptr [edi+2C8h],ebx
    L_0042e6b5:
        add eax,10h
    L_0042e6b8:
        cmp eax,ebx
    L_0042e6ba:
        mov ecx,26h
    L_0042e6bf:
        je short L_0042e6d7
    L_0042e6c1:
        mov edx,dword ptr [eax]
    L_0042e6c3:
        cmp word ptr [edx+38Ah],cx
    L_0042e6ca:
        je asm_target_0042ed2c
    L_0042e6d0:
        mov eax,dword ptr [eax+4]
    L_0042e6d3:
        cmp eax,ebx
    L_0042e6d5:
        jne short L_0042e6c1
    L_0042e6d7:
        xor eax,eax
    L_0042e6d9:
        push eax
    L_0042e6da:
        mov edx,esi
    L_0042e6dc:
        call asm_AnimationManager_Find_004491c0
    L_0042e6e1:
        mov ecx,eax
    L_0042e6e3:
        cmp ecx,ebx
    L_0042e6e5:
        je short L_0042e717
    L_0042e6e7:
        movsx edx,byte ptr [data_00491d68]
    L_0042e6ee:
        mov eax,66666667h
    L_0042e6f3:
        imul edx
    L_0042e6f5:
        sar edx,2
    L_0042e6f8:
        mov eax,edx
    L_0042e6fa:
        shr eax,1Fh
    L_0042e6fd:
        add eax,edx
    L_0042e6ff:
        cdq
    L_0042e700:
        mov ebp,0Ah
    L_0042e705:
        idiv ebp
    L_0042e707:
        mov eax,ecx
    L_0042e709:
        mov ecx,dword ptr [ecx+308h]
    L_0042e70f:
        add edx,33h
    L_0042e712:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e717:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e71d:
        push ecx
    L_0042e71e:
        mov edx,esi
    L_0042e720:
        call asm_AnimationManager_Find_004491c0
    L_0042e725:
        cmp eax,ebx
    L_0042e727:
        jne short L_0042e72f
    L_0042e729:
        mov dword ptr [edi+2C8h],ebx
    L_0042e72f:
        add eax,10h
    L_0042e732:
        cmp eax,ebx
    L_0042e734:
        TH10_REL8(0x74, 0x0042e734, VA_asm_target_0042e756)
    L_0042e736:
        mov ecx,27h
    L_0042e73b:
        TH10_REL8(0xeb, 0x0042e73b, VA_asm_FUN_0042e5a0_part_0042e740)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042e740:
        mov edx,dword ptr [eax]
    L_0042e742:
        cmp word ptr [edx+38Ah],cx
    L_0042e749:
        je asm_target_0042ed35
    L_0042e74f:
        mov eax,dword ptr [eax+4]
    L_0042e752:
        cmp eax,ebx
    L_0042e754:
        jne short L_0042e740
    L_0042e756:
        xor eax,eax
    L_0042e758:
        push eax
    L_0042e759:
        mov edx,esi
    L_0042e75b:
        call asm_AnimationManager_Find_004491c0
    L_0042e760:
        mov ecx,eax
    L_0042e762:
        cmp ecx,ebx
    L_0042e764:
        je short L_0042e785
    L_0042e766:
        movsx eax,byte ptr [data_00491d68]
    L_0042e76d:
        cdq
    L_0042e76e:
        mov ebp,0Ah
    L_0042e773:
        idiv ebp
    L_0042e775:
        mov eax,ecx
    L_0042e777:
        mov ecx,dword ptr [ecx+308h]
    L_0042e77d:
        add edx,33h
    L_0042e780:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e785:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e78b:
        push ecx
    L_0042e78c:
        mov edx,esi
    L_0042e78e:
        call asm_AnimationManager_Find_004491c0
    L_0042e793:
        cmp eax,ebx
    L_0042e795:
        jne short L_0042e79d
    L_0042e797:
        mov dword ptr [edi+2C8h],ebx
    L_0042e79d:
        add eax,10h
    L_0042e7a0:
        cmp eax,ebx
    L_0042e7a2:
        mov ebp,29h
    L_0042e7a7:
        je short L_0042e7c6
    L_0042e7a9:
        lea esp,[esp+force_disp32_zero]
    L_0042e7b0:
        mov edx,dword ptr [eax]
    L_0042e7b2:
        cmp word ptr [edx+38Ah],bp
    L_0042e7b9:
        je asm_target_0042ed3e
    L_0042e7bf:
        mov eax,dword ptr [eax+4]
    L_0042e7c2:
        cmp eax,ebx
    L_0042e7c4:
        jne short L_0042e7b0
    L_0042e7c6:
        xor eax,eax
    L_0042e7c8:
        push eax
    L_0042e7c9:
        mov edx,esi
    L_0042e7cb:
        call asm_AnimationManager_Find_004491c0
    L_0042e7d0:
        mov ecx,eax
    L_0042e7d2:
        cmp ecx,ebx
    L_0042e7d4:
        je short L_0042e7fd
    L_0042e7d6:
        movsx edx,byte ptr [data_00491d68]
    L_0042e7dd:
        mov eax,51EB851Fh
    L_0042e7e2:
        imul edx
    L_0042e7e4:
        sar edx,5
    L_0042e7e7:
        mov eax,edx
    L_0042e7e9:
        shr eax,1Fh
    L_0042e7ec:
        lea edx,[edx+eax+3Dh]
    L_0042e7f0:
        mov eax,ecx
    L_0042e7f2:
        mov ecx,dword ptr [ecx+308h]
    L_0042e7f8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e7fd:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e803:
        push ecx
    L_0042e804:
        mov edx,esi
    L_0042e806:
        call asm_AnimationManager_Find_004491c0
    L_0042e80b:
        cmp eax,ebx
    L_0042e80d:
        jne short L_0042e815
    L_0042e80f:
        mov dword ptr [edi+2C8h],ebx
    L_0042e815:
        add eax,10h
    L_0042e818:
        cmp eax,ebx
    L_0042e81a:
        mov ecx,2Ah
    L_0042e81f:
        je short L_0042e837
    L_0042e821:
        mov edx,dword ptr [eax]
    L_0042e823:
        cmp word ptr [edx+38Ah],cx
    L_0042e82a:
        je asm_target_0042ed47
    L_0042e830:
        mov eax,dword ptr [eax+4]
    L_0042e833:
        cmp eax,ebx
    L_0042e835:
        jne short L_0042e821
    L_0042e837:
        xor eax,eax
    L_0042e839:
        push eax
    L_0042e83a:
        mov edx,esi
    L_0042e83c:
        call asm_AnimationManager_Find_004491c0
    L_0042e841:
        mov ecx,eax
    L_0042e843:
        cmp ecx,ebx
    L_0042e845:
        je short L_0042e87c
    L_0042e847:
        movsx edx,byte ptr [data_00491d68]
    L_0042e84e:
        mov eax,66666667h
    L_0042e853:
        imul edx
    L_0042e855:
        sar edx,2
    L_0042e858:
        mov eax,edx
    L_0042e85a:
        shr eax,1Fh
    L_0042e85d:
        add eax,edx
    L_0042e85f:
        cdq
    L_0042e860:
        mov ebp,0Ah
    L_0042e865:
        idiv ebp
    L_0042e867:
        mov eax,ecx
    L_0042e869:
        mov ecx,dword ptr [ecx+308h]
    L_0042e86f:
        add edx,3Dh
    L_0042e872:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e877:
        mov ebp,29h
    L_0042e87c:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e882:
        push ecx
    L_0042e883:
        mov edx,esi
    L_0042e885:
        call asm_AnimationManager_Find_004491c0
    L_0042e88a:
        cmp eax,ebx
    L_0042e88c:
        jne short L_0042e894
    L_0042e88e:
        mov dword ptr [edi+2C8h],ebx
    L_0042e894:
        add eax,10h
    L_0042e897:
        cmp eax,ebx
    L_0042e899:
        je short L_0042e8b6
    L_0042e89b:
        mov ecx,2Bh
    L_0042e8a0:
        mov edx,dword ptr [eax]
    L_0042e8a2:
        cmp word ptr [edx+38Ah],cx
    L_0042e8a9:
        je asm_target_0042ed50
    L_0042e8af:
        mov eax,dword ptr [eax+4]
    L_0042e8b2:
        cmp eax,ebx
    L_0042e8b4:
        jne short L_0042e8a0
    L_0042e8b6:
        xor eax,eax
    L_0042e8b8:
        push eax
    L_0042e8b9:
        mov edx,esi
    L_0042e8bb:
        call asm_AnimationManager_Find_004491c0
    L_0042e8c0:
        mov ecx,eax
    L_0042e8c2:
        cmp ecx,ebx
    L_0042e8c4:
        je short L_0042e8ea
    L_0042e8c6:
        movsx eax,byte ptr [data_00491d68]
    L_0042e8cd:
        cdq
    L_0042e8ce:
        mov ebp,0Ah
    L_0042e8d3:
        idiv ebp
    L_0042e8d5:
        mov eax,ecx
    L_0042e8d7:
        mov ecx,dword ptr [ecx+308h]
    L_0042e8dd:
        add edx,3Dh
    L_0042e8e0:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e8e5:
        mov ebp,29h
    L_0042e8ea:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e8f0:
        push ecx
    L_0042e8f1:
        mov edx,esi
    L_0042e8f3:
        call asm_AnimationManager_Find_004491c0
    L_0042e8f8:
        cmp eax,ebx
    L_0042e8fa:
        jne short L_0042e902
    L_0042e8fc:
        mov dword ptr [edi+2C8h],ebx
    L_0042e902:
        add eax,10h
    L_0042e905:
        cmp eax,ebx
    L_0042e907:
        mov ecx,2Dh
    L_0042e90c:
        je short L_0042e926
    L_0042e90e:
        mov edi,edi
    L_0042e910:
        mov edx,dword ptr [eax]
    L_0042e912:
        cmp word ptr [edx+38Ah],cx
    L_0042e919:
        je asm_target_0042ed59
    L_0042e91f:
        mov eax,dword ptr [eax+4]
    L_0042e922:
        cmp eax,ebx
    L_0042e924:
        jne short L_0042e910
    L_0042e926:
        xor eax,eax
    L_0042e928:
        push eax
    L_0042e929:
        mov edx,esi
    L_0042e92b:
        call asm_AnimationManager_Find_004491c0
    L_0042e930:
        mov ecx,eax
    L_0042e932:
        cmp ecx,ebx
    L_0042e934:
        je short L_0042e95d
    L_0042e936:
        movsx edx,byte ptr [data_00491d69]
    L_0042e93d:
        mov eax,51EB851Fh
    L_0042e942:
        imul edx
    L_0042e944:
        sar edx,5
    L_0042e947:
        mov eax,edx
    L_0042e949:
        shr eax,1Fh
    L_0042e94c:
        lea edx,[edx+eax+33h]
    L_0042e950:
        mov eax,ecx
    L_0042e952:
        mov ecx,dword ptr [ecx+308h]
    L_0042e958:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e95d:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e963:
        push ecx
    L_0042e964:
        mov edx,esi
    L_0042e966:
        call asm_AnimationManager_Find_004491c0
    L_0042e96b:
        cmp eax,ebx
    L_0042e96d:
        jne short L_0042e975
    L_0042e96f:
        mov dword ptr [edi+2C8h],ebx
    L_0042e975:
        add eax,10h
    L_0042e978:
        cmp eax,ebx
    L_0042e97a:
        mov ecx,2Eh
    L_0042e97f:
        je short L_0042e997
    L_0042e981:
        mov edx,dword ptr [eax]
    L_0042e983:
        cmp word ptr [edx+38Ah],cx
    L_0042e98a:
        je asm_target_0042ed62
    L_0042e990:
        mov eax,dword ptr [eax+4]
    L_0042e993:
        cmp eax,ebx
    L_0042e995:
        jne short L_0042e981
    L_0042e997:
        xor eax,eax
    L_0042e999:
        push eax
    L_0042e99a:
        mov edx,esi
    L_0042e99c:
        call asm_AnimationManager_Find_004491c0
    L_0042e9a1:
        mov ecx,eax
    L_0042e9a3:
        cmp ecx,ebx
    L_0042e9a5:
        je short L_0042e9dc
    L_0042e9a7:
        movsx edx,byte ptr [data_00491d69]
    L_0042e9ae:
        mov eax,66666667h
    L_0042e9b3:
        imul edx
    L_0042e9b5:
        sar edx,2
    L_0042e9b8:
        mov eax,edx
    L_0042e9ba:
        shr eax,1Fh
    L_0042e9bd:
        add eax,edx
    L_0042e9bf:
        cdq
    L_0042e9c0:
        mov ebp,0Ah
    L_0042e9c5:
        idiv ebp
    L_0042e9c7:
        mov eax,ecx
    L_0042e9c9:
        mov ecx,dword ptr [ecx+308h]
    L_0042e9cf:
        add edx,33h
    L_0042e9d2:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042e9d7:
        mov ebp,29h
    L_0042e9dc:
        mov ecx,dword ptr [edi+2C8h]
    L_0042e9e2:
        push ecx
    L_0042e9e3:
        mov edx,esi
    L_0042e9e5:
        call asm_AnimationManager_Find_004491c0
    L_0042e9ea:
        cmp eax,ebx
    L_0042e9ec:
        jne short L_0042e9f4
    L_0042e9ee:
        mov dword ptr [edi+2C8h],ebx
    L_0042e9f4:
        add eax,10h
    L_0042e9f7:
        cmp eax,ebx
    L_0042e9f9:
        je short L_0042ea16
    L_0042e9fb:
        mov ecx,2Fh
    L_0042ea00:
        mov edx,dword ptr [eax]
    L_0042ea02:
        cmp word ptr [edx+38Ah],cx
    L_0042ea09:
        je asm_target_0042ed6b
    L_0042ea0f:
        mov eax,dword ptr [eax+4]
    L_0042ea12:
        cmp eax,ebx
    L_0042ea14:
        jne short L_0042ea00
    L_0042ea16:
        xor eax,eax
    L_0042ea18:
        push eax
    L_0042ea19:
        mov edx,esi
    L_0042ea1b:
        call asm_AnimationManager_Find_004491c0
    L_0042ea20:
        mov ecx,eax
    L_0042ea22:
        cmp ecx,ebx
    L_0042ea24:
        je short L_0042ea4a
    L_0042ea26:
        movsx eax,byte ptr [data_00491d69]
    L_0042ea2d:
        cdq
    L_0042ea2e:
        mov ebp,0Ah
    L_0042ea33:
        idiv ebp
    L_0042ea35:
        mov eax,ecx
    L_0042ea37:
        mov ecx,dword ptr [ecx+308h]
    L_0042ea3d:
        add edx,33h
    L_0042ea40:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042ea45:
        mov ebp,29h
    L_0042ea4a:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ea50:
        push ecx
    L_0042ea51:
        mov edx,esi
    L_0042ea53:
        call asm_AnimationManager_Find_004491c0
    L_0042ea58:
        cmp eax,ebx
    L_0042ea5a:
        jne short L_0042ea62
    L_0042ea5c:
        mov dword ptr [edi+2C8h],ebx
    L_0042ea62:
        add eax,10h
    L_0042ea65:
        cmp eax,ebx
    L_0042ea67:
        mov ecx,31h
    L_0042ea6c:
        je short L_0042ea86
    L_0042ea6e:
        mov edi,edi
    L_0042ea70:
        mov edx,dword ptr [eax]
    L_0042ea72:
        cmp word ptr [edx+38Ah],cx
    L_0042ea79:
        je asm_target_0042ed74
    L_0042ea7f:
        mov eax,dword ptr [eax+4]
    L_0042ea82:
        cmp eax,ebx
    L_0042ea84:
        jne short L_0042ea70
    L_0042ea86:
        xor eax,eax
    L_0042ea88:
        push eax
    L_0042ea89:
        mov edx,esi
    L_0042ea8b:
        call asm_AnimationManager_Find_004491c0
    L_0042ea90:
        mov ecx,eax
    L_0042ea92:
        cmp ecx,ebx
    L_0042ea94:
        je short L_0042eabd
    L_0042ea96:
        movsx edx,byte ptr [data_00491d69]
    L_0042ea9d:
        mov eax,51EB851Fh
    L_0042eaa2:
        imul edx
    L_0042eaa4:
        sar edx,5
    L_0042eaa7:
        mov eax,edx
    L_0042eaa9:
        shr eax,1Fh
    L_0042eaac:
        lea edx,[edx+eax+3Dh]
    L_0042eab0:
        mov eax,ecx
    L_0042eab2:
        mov ecx,dword ptr [ecx+308h]
    L_0042eab8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042eabd:
        mov ecx,dword ptr [edi+2C8h]
    L_0042eac3:
        push ecx
    L_0042eac4:
        mov edx,esi
    L_0042eac6:
        call asm_AnimationManager_Find_004491c0
    L_0042eacb:
        cmp eax,ebx
    L_0042eacd:
        jne short L_0042ead5
    L_0042eacf:
        mov dword ptr [edi+2C8h],ebx
    L_0042ead5:
        add eax,10h
    L_0042ead8:
        cmp eax,ebx
    L_0042eada:
        mov ecx,32h
    L_0042eadf:
        je short L_0042eaf7
    L_0042eae1:
        mov edx,dword ptr [eax]
    L_0042eae3:
        cmp word ptr [edx+38Ah],cx
    L_0042eaea:
        je asm_target_0042ed7d
    L_0042eaf0:
        mov eax,dword ptr [eax+4]
    L_0042eaf3:
        cmp eax,ebx
    L_0042eaf5:
        jne short L_0042eae1
    L_0042eaf7:
        xor eax,eax
    L_0042eaf9:
        push eax
    L_0042eafa:
        mov edx,esi
    L_0042eafc:
        call asm_AnimationManager_Find_004491c0
    L_0042eb01:
        mov ecx,eax
    L_0042eb03:
        cmp ecx,ebx
    L_0042eb05:
        je short L_0042eb3c
    L_0042eb07:
        movsx edx,byte ptr [data_00491d69]
    L_0042eb0e:
        mov eax,66666667h
    L_0042eb13:
        imul edx
    L_0042eb15:
        sar edx,2
    L_0042eb18:
        mov eax,edx
    L_0042eb1a:
        shr eax,1Fh
    L_0042eb1d:
        add eax,edx
    L_0042eb1f:
        cdq
    L_0042eb20:
        mov ebp,0Ah
    L_0042eb25:
        idiv ebp
    L_0042eb27:
        mov eax,ecx
    L_0042eb29:
        mov ecx,dword ptr [ecx+308h]
    L_0042eb2f:
        add edx,3Dh
    L_0042eb32:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042eb37:
        mov ebp,29h
    L_0042eb3c:
        mov ecx,dword ptr [edi+2C8h]
    L_0042eb42:
        push ecx
    L_0042eb43:
        mov edx,esi
    L_0042eb45:
        call asm_AnimationManager_Find_004491c0
    L_0042eb4a:
        cmp eax,ebx
    L_0042eb4c:
        jne short L_0042eb54
    L_0042eb4e:
        mov dword ptr [edi+2C8h],ebx
    L_0042eb54:
        add eax,10h
    L_0042eb57:
        cmp eax,ebx
    L_0042eb59:
        je short L_0042eb76
    L_0042eb5b:
        mov ecx,33h
    L_0042eb60:
        mov edx,dword ptr [eax]
    L_0042eb62:
        cmp word ptr [edx+38Ah],cx
    L_0042eb69:
        je asm_target_0042ed86
    L_0042eb6f:
        mov eax,dword ptr [eax+4]
    L_0042eb72:
        cmp eax,ebx
    L_0042eb74:
        jne short L_0042eb60
    L_0042eb76:
        xor eax,eax
    L_0042eb78:
        push eax
    L_0042eb79:
        mov edx,esi
    L_0042eb7b:
        call asm_AnimationManager_Find_004491c0
    L_0042eb80:
        mov ecx,eax
    L_0042eb82:
        cmp ecx,ebx
    L_0042eb84:
        je short L_0042ebaa
    L_0042eb86:
        movsx eax,byte ptr [data_00491d69]
    L_0042eb8d:
        cdq
    L_0042eb8e:
        mov ebp,0Ah
    L_0042eb93:
        idiv ebp
    L_0042eb95:
        mov eax,ecx
    L_0042eb97:
        mov ecx,dword ptr [ecx+308h]
    L_0042eb9d:
        add edx,3Dh
    L_0042eba0:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042eba5:
        mov ebp,29h
    L_0042ebaa:
        mov al,byte ptr [data_00491d68]
    L_0042ebaf:
        cmp al,0Ah
    L_0042ebb1:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ebb7:
        mov edx,esi
    L_0042ebb9:
        push ecx
    L_0042ebba:
        jge asm_target_0042edb3
    L_0042ebc0:
        call asm_AnimationManager_Find_004491c0
    L_0042ebc5:
        cmp eax,ebx
    L_0042ebc7:
        jne short L_0042ebcf
    L_0042ebc9:
        mov dword ptr [edi+2C8h],ebx
    L_0042ebcf:
        add eax,10h
    L_0042ebd2:
        cmp eax,ebx
    L_0042ebd4:
        TH10_REL8(0x74, 0x0042ebd4, VA_asm_target_0042ebf6)
    L_0042ebd6:
        mov ecx,25h
    L_0042ebdb:
        TH10_REL8(0xeb, 0x0042ebdb, VA_asm_FUN_0042e5a0_part_0042ebe0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042ebe0:
        mov edx,dword ptr [eax]
    L_0042ebe2:
        cmp word ptr [edx+38Ah],cx
    L_0042ebe9:
        je asm_target_0042ed8f
    L_0042ebef:
        mov eax,dword ptr [eax+4]
    L_0042ebf2:
        cmp eax,ebx
    L_0042ebf4:
        jne short L_0042ebe0
    L_0042ebf6:
        xor eax,eax
    L_0042ebf8:
        push eax
    L_0042ebf9:
        mov edx,esi
    L_0042ebfb:
        call asm_AnimationManager_Find_004491c0
    L_0042ec00:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ec06:
        add eax,35Ch
    L_0042ec0b:
        and ecx,0FFFFFFFDh
    L_0042ec0e:
        mov dword ptr [eax],ecx
    L_0042ec10:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ec16:
        push ecx
    L_0042ec17:
        mov edx,esi
    L_0042ec19:
        call asm_AnimationManager_Find_004491c0
    L_0042ec1e:
        cmp eax,ebx
    L_0042ec20:
        jne short L_0042ec28
    L_0042ec22:
        mov dword ptr [edi+2C8h],ebx
    L_0042ec28:
        add eax,10h
    L_0042ec2b:
        cmp eax,ebx
    L_0042ec2d:
        TH10_REL8(0x74, 0x0042ec2d, VA_asm_target_0042ec56)
    L_0042ec2f:
        mov ecx,26h
    L_0042ec34:
        TH10_REL8(0xeb, 0x0042ec34, VA_asm_FUN_0042e5a0_part_0042ec40)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042ec40:
        mov edx,dword ptr [eax]
    L_0042ec42:
        cmp word ptr [edx+38Ah],cx
    L_0042ec49:
        je asm_target_0042ed98
    L_0042ec4f:
        mov eax,dword ptr [eax+4]
    L_0042ec52:
        cmp eax,ebx
    L_0042ec54:
        jne short L_0042ec40
    L_0042ec56:
        xor eax,eax
    L_0042ec58:
        push eax
    L_0042ec59:
        mov edx,esi
    L_0042ec5b:
        call asm_AnimationManager_Find_004491c0
    L_0042ec60:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ec66:
        add eax,35Ch
    L_0042ec6b:
        and ecx,0FFFFFFFDh
    L_0042ec6e:
        mov dword ptr [eax],ecx
    L_0042ec70:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ec76:
        push ecx
    L_0042ec77:
        mov edx,esi
    L_0042ec79:
        call asm_AnimationManager_Find_004491c0
    L_0042ec7e:
        cmp eax,ebx
    L_0042ec80:
        jne short L_0042ec88
    L_0042ec82:
        mov dword ptr [edi+2C8h],ebx
    L_0042ec88:
        add eax,10h
    L_0042ec8b:
        cmp eax,ebx
    L_0042ec8d:
        je short L_0042eca6
    L_0042ec8f:
        nop
    L_0042ec90:
        mov edx,dword ptr [eax]
    L_0042ec92:
        cmp word ptr [edx+38Ah],bp
    L_0042ec99:
        je asm_target_0042eda1
    L_0042ec9f:
        mov eax,dword ptr [eax+4]
    L_0042eca2:
        cmp eax,ebx
    L_0042eca4:
        jne short L_0042ec90
    L_0042eca6:
        xor eax,eax
    L_0042eca8:
        push eax
    L_0042eca9:
        mov edx,esi
    L_0042ecab:
        call asm_AnimationManager_Find_004491c0
    L_0042ecb0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042ecb6:
        add eax,35Ch
    L_0042ecbb:
        and ebp,0FFFFFFFDh
    L_0042ecbe:
        mov dword ptr [eax],ebp
    L_0042ecc0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ecc6:
        push ecx
    L_0042ecc7:
        mov edx,esi
    L_0042ecc9:
        call asm_AnimationManager_Find_004491c0
    L_0042ecce:
        cmp eax,ebx
    L_0042ecd0:
        jne short L_0042ecd8
    L_0042ecd2:
        mov dword ptr [edi+2C8h],ebx
    L_0042ecd8:
        add eax,10h
    L_0042ecdb:
        cmp eax,ebx
    L_0042ecdd:
        TH10_REL8(0x74, 0x0042ecdd, VA_asm_target_0042ed06)
    L_0042ecdf:
        mov ecx,2Ah
    L_0042ece4:
        TH10_REL8(0xeb, 0x0042ece4, VA_asm_FUN_0042e5a0_part_0042ecf0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042ecf0:
        mov edx,dword ptr [eax]
    L_0042ecf2:
        cmp word ptr [edx+38Ah],cx
    L_0042ecf9:
        je asm_target_0042edaa
    L_0042ecff:
        mov eax,dword ptr [eax+4]
    L_0042ed02:
        cmp eax,ebx
    L_0042ed04:
        jne short L_0042ecf0
    L_0042ed06:
        xor eax,eax
    L_0042ed08:
        push eax
    L_0042ed09:
        mov edx,esi
    L_0042ed0b:
        call asm_AnimationManager_Find_004491c0
    L_0042ed10:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ed16:
        add eax,35Ch
    L_0042ed1b:
        and ecx,0FFFFFFFDh
    L_0042ed1e:
        jmp asm_target_0042f07e
    L_0042ed23:
        mov eax,dword ptr [eax]
    L_0042ed25:
        mov eax,dword ptr [eax]
    L_0042ed27:
        jmp asm_target_0042e668
    L_0042ed2c:
        mov eax,dword ptr [eax]
    L_0042ed2e:
        mov eax,dword ptr [eax]
    L_0042ed30:
        jmp asm_target_0042e6d9
    L_0042ed35:
        mov eax,dword ptr [eax]
    L_0042ed37:
        mov eax,dword ptr [eax]
    L_0042ed39:
        jmp asm_target_0042e758
    L_0042ed3e:
        mov eax,dword ptr [eax]
    L_0042ed40:
        mov eax,dword ptr [eax]
    L_0042ed42:
        jmp asm_target_0042e7c8
    L_0042ed47:
        mov eax,dword ptr [eax]
    L_0042ed49:
        mov eax,dword ptr [eax]
    L_0042ed4b:
        jmp asm_target_0042e839
    L_0042ed50:
        mov eax,dword ptr [eax]
    L_0042ed52:
        mov eax,dword ptr [eax]
    L_0042ed54:
        jmp asm_target_0042e8b8
    L_0042ed59:
        mov eax,dword ptr [eax]
    L_0042ed5b:
        mov eax,dword ptr [eax]
    L_0042ed5d:
        jmp asm_target_0042e928
    L_0042ed62:
        mov eax,dword ptr [eax]
    L_0042ed64:
        mov eax,dword ptr [eax]
    L_0042ed66:
        jmp asm_target_0042e999
    L_0042ed6b:
        mov eax,dword ptr [eax]
    L_0042ed6d:
        mov eax,dword ptr [eax]
    L_0042ed6f:
        jmp asm_target_0042ea18
    L_0042ed74:
        mov eax,dword ptr [eax]
    L_0042ed76:
        mov eax,dword ptr [eax]
    L_0042ed78:
        jmp asm_target_0042ea88
    L_0042ed7d:
        mov eax,dword ptr [eax]
    L_0042ed7f:
        mov eax,dword ptr [eax]
    L_0042ed81:
        jmp asm_target_0042eaf9
    L_0042ed86:
        mov eax,dword ptr [eax]
    L_0042ed88:
        mov eax,dword ptr [eax]
    L_0042ed8a:
        jmp asm_target_0042eb78
    L_0042ed8f:
        mov eax,dword ptr [eax]
    L_0042ed91:
        mov eax,dword ptr [eax]
    L_0042ed93:
        jmp asm_target_0042ebf8
    L_0042ed98:
        mov eax,dword ptr [eax]
    L_0042ed9a:
        mov eax,dword ptr [eax]
    L_0042ed9c:
        jmp asm_target_0042ec58
    L_0042eda1:
        mov eax,dword ptr [eax]
    L_0042eda3:
        mov eax,dword ptr [eax]
    L_0042eda5:
        jmp asm_target_0042eca8
    L_0042edaa:
        mov eax,dword ptr [eax]
    L_0042edac:
        mov eax,dword ptr [eax]
    L_0042edae:
        jmp asm_target_0042ed08
    L_0042edb3:
        cmp al,64h
    L_0042edb5:
        jge asm_target_0042ef1c
    L_0042edbb:
        call asm_AnimationManager_Find_004491c0
    L_0042edc0:
        cmp eax,ebx
    L_0042edc2:
        jne short L_0042edca
    L_0042edc4:
        mov dword ptr [edi+2C8h],ebx
    L_0042edca:
        add eax,10h
    L_0042edcd:
        cmp eax,ebx
    L_0042edcf:
        TH10_REL8(0x74, 0x0042edcf, VA_asm_target_0042edf6)
    L_0042edd1:
        mov ecx,25h
    L_0042edd6:
        TH10_REL8(0xeb, 0x0042edd6, VA_asm_FUN_0042e5a0_part_0042ede0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0042ede0:
        mov edx,dword ptr [eax]
    L_0042ede2:
        cmp word ptr [edx+38Ah],cx
    L_0042ede9:
        je asm_target_0042eefb
    L_0042edef:
        mov eax,dword ptr [eax+4]
    L_0042edf2:
        cmp eax,ebx
    L_0042edf4:
        jne short L_0042ede0
    L_0042edf6:
        xor eax,eax
    L_0042edf8:
        push eax
    L_0042edf9:
        mov edx,esi
    L_0042edfb:
        call asm_AnimationManager_Find_004491c0
    L_0042ee00:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ee06:
        add eax,35Ch
    L_0042ee0b:
        and ecx,0FFFFFFFDh
    L_0042ee0e:
        mov dword ptr [eax],ecx
    L_0042ee10:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ee16:
        push ecx
    L_0042ee17:
        mov edx,esi
    L_0042ee19:
        call asm_AnimationManager_Find_004491c0
    L_0042ee1e:
        cmp eax,ebx
    L_0042ee20:
        jne short L_0042ee28
    L_0042ee22:
        mov dword ptr [edi+2C8h],ebx
    L_0042ee28:
        add eax,10h
    L_0042ee2b:
        cmp eax,ebx
    L_0042ee2d:
        TH10_REL8(0x74, 0x0042ee2d, VA_asm_target_0042ee56)
    L_0042ee2f:
        mov ecx,26h
    L_0042ee34:
        TH10_REL8(0xeb, 0x0042ee34, VA_asm_FUN_0042e5a0_part_0042ee40)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042ee40:
        mov edx,dword ptr [eax]
    L_0042ee42:
        cmp word ptr [edx+38Ah],cx
    L_0042ee49:
        je asm_target_0042ef04
    L_0042ee4f:
        mov eax,dword ptr [eax+4]
    L_0042ee52:
        cmp eax,ebx
    L_0042ee54:
        jne short L_0042ee40
    L_0042ee56:
        xor eax,eax
    L_0042ee58:
        push eax
    L_0042ee59:
        mov edx,esi
    L_0042ee5b:
        call asm_AnimationManager_Find_004491c0
    L_0042ee60:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ee66:
        add eax,35Ch
    L_0042ee6b:
        or ecx,2
    L_0042ee6e:
        mov dword ptr [eax],ecx
    L_0042ee70:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ee76:
        push ecx
    L_0042ee77:
        mov edx,esi
    L_0042ee79:
        call asm_AnimationManager_Find_004491c0
    L_0042ee7e:
        cmp eax,ebx
    L_0042ee80:
        jne short L_0042ee88
    L_0042ee82:
        mov dword ptr [edi+2C8h],ebx
    L_0042ee88:
        add eax,10h
    L_0042ee8b:
        cmp eax,ebx
    L_0042ee8d:
        je short L_0042eea2
    L_0042ee8f:
        nop
    L_0042ee90:
        mov edx,dword ptr [eax]
    L_0042ee92:
        cmp word ptr [edx+38Ah],bp
    L_0042ee99:
        je short L_0042ef0d
    L_0042ee9b:
        mov eax,dword ptr [eax+4]
    L_0042ee9e:
        cmp eax,ebx
    L_0042eea0:
        jne short L_0042ee90
    L_0042eea2:
        xor eax,eax
    L_0042eea4:
        push eax
    L_0042eea5:
        mov edx,esi
    L_0042eea7:
        call asm_AnimationManager_Find_004491c0
    L_0042eeac:
        mov ebp,dword ptr [eax+35Ch]
    L_0042eeb2:
        add eax,35Ch
    L_0042eeb7:
        and ebp,0FFFFFFFDh
    L_0042eeba:
        mov dword ptr [eax],ebp
    L_0042eebc:
        mov ecx,dword ptr [edi+2C8h]
    L_0042eec2:
        push ecx
    L_0042eec3:
        mov edx,esi
    L_0042eec5:
        call asm_AnimationManager_Find_004491c0
    L_0042eeca:
        cmp eax,ebx
    L_0042eecc:
        jne short L_0042eed4
    L_0042eece:
        mov dword ptr [edi+2C8h],ebx
    L_0042eed4:
        add eax,10h
    L_0042eed7:
        cmp eax,ebx
    L_0042eed9:
        je asm_target_0042f066
    L_0042eedf:
        mov ecx,2Ah
    L_0042eee4:
        mov edx,dword ptr [eax]
    L_0042eee6:
        cmp word ptr [edx+38Ah],cx
    L_0042eeed:
        je short L_0042ef13
    L_0042eeef:
        mov eax,dword ptr [eax+4]
    L_0042eef2:
        cmp eax,ebx
    L_0042eef4:
        jne short L_0042eee4
    L_0042eef6:
        jmp asm_target_0042f066
    L_0042eefb:
        mov eax,dword ptr [eax]
    L_0042eefd:
        mov eax,dword ptr [eax]
    L_0042eeff:
        jmp asm_target_0042edf8
    L_0042ef04:
        mov eax,dword ptr [eax]
    L_0042ef06:
        mov eax,dword ptr [eax]
    L_0042ef08:
        jmp asm_target_0042ee58
    L_0042ef0d:
        mov eax,dword ptr [eax]
    L_0042ef0f:
        mov eax,dword ptr [eax]
    L_0042ef11:
        jmp short L_0042eea4
    L_0042ef13:
        mov eax,dword ptr [eax]
    L_0042ef15:
        mov eax,dword ptr [eax]
    L_0042ef17:
        jmp asm_target_0042f068
    L_0042ef1c:
        call asm_AnimationManager_Find_004491c0
    L_0042ef21:
        cmp eax,ebx
    L_0042ef23:
        jne short L_0042ef2b
    L_0042ef25:
        mov dword ptr [edi+2C8h],ebx
    L_0042ef2b:
        add eax,10h
    L_0042ef2e:
        cmp eax,ebx
    L_0042ef30:
        TH10_REL8(0x74, 0x0042ef30, VA_asm_target_0042ef56)
    L_0042ef32:
        mov ecx,25h
    L_0042ef37:
        TH10_REL8(0xeb, 0x0042ef37, VA_asm_FUN_0042e5a0_part_0042ef40)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0042ef40:
        mov edx,dword ptr [eax]
    L_0042ef42:
        cmp word ptr [edx+38Ah],cx
    L_0042ef49:
        je asm_target_0042f1f4
    L_0042ef4f:
        mov eax,dword ptr [eax+4]
    L_0042ef52:
        cmp eax,ebx
    L_0042ef54:
        jne short L_0042ef40
    L_0042ef56:
        xor eax,eax
    L_0042ef58:
        push eax
    L_0042ef59:
        mov edx,esi
    L_0042ef5b:
        call asm_AnimationManager_Find_004491c0
    L_0042ef60:
        mov ecx,dword ptr [eax+35Ch]
    L_0042ef66:
        add eax,35Ch
    L_0042ef6b:
        or ecx,2
    L_0042ef6e:
        mov dword ptr [eax],ecx
    L_0042ef70:
        mov ecx,dword ptr [edi+2C8h]
    L_0042ef76:
        push ecx
    L_0042ef77:
        mov edx,esi
    L_0042ef79:
        call asm_AnimationManager_Find_004491c0
    L_0042ef7e:
        cmp eax,ebx
    L_0042ef80:
        jne short L_0042ef88
    L_0042ef82:
        mov dword ptr [edi+2C8h],ebx
    L_0042ef88:
        add eax,10h
    L_0042ef8b:
        cmp eax,ebx
    L_0042ef8d:
        TH10_REL8(0x74, 0x0042ef8d, VA_asm_target_0042efb6)
    L_0042ef8f:
        mov ecx,26h
    L_0042ef94:
        TH10_REL8(0xeb, 0x0042ef94, VA_asm_FUN_0042e5a0_part_0042efa0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042efa0:
        mov edx,dword ptr [eax]
    L_0042efa2:
        cmp word ptr [edx+38Ah],cx
    L_0042efa9:
        je asm_target_0042f1fd
    L_0042efaf:
        mov eax,dword ptr [eax+4]
    L_0042efb2:
        cmp eax,ebx
    L_0042efb4:
        jne short L_0042efa0
    L_0042efb6:
        xor eax,eax
    L_0042efb8:
        push eax
    L_0042efb9:
        mov edx,esi
    L_0042efbb:
        call asm_AnimationManager_Find_004491c0
    L_0042efc0:
        mov ecx,dword ptr [eax+35Ch]
    L_0042efc6:
        add eax,35Ch
    L_0042efcb:
        or ecx,2
    L_0042efce:
        mov dword ptr [eax],ecx
    L_0042efd0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042efd6:
        push ecx
    L_0042efd7:
        mov edx,esi
    L_0042efd9:
        call asm_AnimationManager_Find_004491c0
    L_0042efde:
        cmp eax,ebx
    L_0042efe0:
        jne short L_0042efe8
    L_0042efe2:
        mov dword ptr [edi+2C8h],ebx
    L_0042efe8:
        add eax,10h
    L_0042efeb:
        cmp eax,ebx
    L_0042efed:
        je short L_0042f006
    L_0042efef:
        nop
    L_0042eff0:
        mov edx,dword ptr [eax]
    L_0042eff2:
        cmp word ptr [edx+38Ah],bp
    L_0042eff9:
        je asm_target_0042f206
    L_0042efff:
        mov eax,dword ptr [eax+4]
    L_0042f002:
        cmp eax,ebx
    L_0042f004:
        jne short L_0042eff0
    L_0042f006:
        xor eax,eax
    L_0042f008:
        push eax
    L_0042f009:
        mov edx,esi
    L_0042f00b:
        call asm_AnimationManager_Find_004491c0
    L_0042f010:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f016:
        add eax,35Ch
    L_0042f01b:
        or ebp,2
    L_0042f01e:
        mov dword ptr [eax],ebp
    L_0042f020:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f026:
        push ecx
    L_0042f027:
        mov edx,esi
    L_0042f029:
        call asm_AnimationManager_Find_004491c0
    L_0042f02e:
        cmp eax,ebx
    L_0042f030:
        jne short L_0042f038
    L_0042f032:
        mov dword ptr [edi+2C8h],ebx
    L_0042f038:
        add eax,10h
    L_0042f03b:
        cmp eax,ebx
    L_0042f03d:
        TH10_REL8(0x74, 0x0042f03d, VA_asm_target_0042f066)
    L_0042f03f:
        mov ecx,2Ah
    L_0042f044:
        TH10_REL8(0xeb, 0x0042f044, VA_asm_FUN_0042e5a0_part_0042f050)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042f050:
        mov edx,dword ptr [eax]
    L_0042f052:
        cmp word ptr [edx+38Ah],cx
    L_0042f059:
        je asm_target_0042ef13
    L_0042f05f:
        mov eax,dword ptr [eax+4]
    L_0042f062:
        cmp eax,ebx
    L_0042f064:
        jne short L_0042f050
    L_0042f066:
        xor eax,eax
    L_0042f068:
        mov edx,esi
    L_0042f06a:
        push eax
    L_0042f06b:
        call asm_AnimationManager_Find_004491c0
    L_0042f070:
        mov ecx,dword ptr [eax+35Ch]
    L_0042f076:
        add eax,35Ch
    L_0042f07b:
        or ecx,2
    L_0042f07e:
        mov dword ptr [eax],ecx
    L_0042f080:
        mov al,byte ptr [data_00491d69]
    L_0042f085:
        cmp al,0Ah
    L_0042f087:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f08d:
        mov edx,esi
    L_0042f08f:
        push ecx
    L_0042f090:
        jge asm_target_0042f230
    L_0042f096:
        call asm_AnimationManager_Find_004491c0
    L_0042f09b:
        cmp eax,ebx
    L_0042f09d:
        jne short L_0042f0a5
    L_0042f09f:
        mov dword ptr [edi+2C8h],ebx
    L_0042f0a5:
        add eax,10h
    L_0042f0a8:
        cmp eax,ebx
    L_0042f0aa:
        je short L_0042f0c7
    L_0042f0ac:
        mov ecx,2Dh
    L_0042f0b1:
        mov edx,dword ptr [eax]
    L_0042f0b3:
        cmp word ptr [edx+38Ah],cx
    L_0042f0ba:
        je asm_target_0042f20f
    L_0042f0c0:
        mov eax,dword ptr [eax+4]
    L_0042f0c3:
        cmp eax,ebx
    L_0042f0c5:
        jne short L_0042f0b1
    L_0042f0c7:
        xor eax,eax
    L_0042f0c9:
        push eax
    L_0042f0ca:
        mov edx,esi
    L_0042f0cc:
        call asm_AnimationManager_Find_004491c0
    L_0042f0d1:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f0d7:
        add eax,35Ch
    L_0042f0dc:
        and ebp,0FFFFFFFDh
    L_0042f0df:
        mov dword ptr [eax],ebp
    L_0042f0e1:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f0e7:
        push ecx
    L_0042f0e8:
        mov edx,esi
    L_0042f0ea:
        call asm_AnimationManager_Find_004491c0
    L_0042f0ef:
        cmp eax,ebx
    L_0042f0f1:
        jne short L_0042f0f9
    L_0042f0f3:
        mov dword ptr [edi+2C8h],ebx
    L_0042f0f9:
        add eax,10h
    L_0042f0fc:
        cmp eax,ebx
    L_0042f0fe:
        TH10_REL8(0x74, 0x0042f0fe, VA_asm_target_0042f126)
    L_0042f100:
        mov ecx,2Eh
    L_0042f105:
        TH10_REL8(0xeb, 0x0042f105, VA_asm_FUN_0042e5a0_part_0042f110)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_0042f110:
        mov edx,dword ptr [eax]
    L_0042f112:
        cmp word ptr [edx+38Ah],cx
    L_0042f119:
        je asm_target_0042f218
    L_0042f11f:
        mov eax,dword ptr [eax+4]
    L_0042f122:
        cmp eax,ebx
    L_0042f124:
        jne short L_0042f110
    L_0042f126:
        xor eax,eax
    L_0042f128:
        push eax
    L_0042f129:
        mov edx,esi
    L_0042f12b:
        call asm_AnimationManager_Find_004491c0
    L_0042f130:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f136:
        add eax,35Ch
    L_0042f13b:
        and ebp,0FFFFFFFDh
    L_0042f13e:
        mov dword ptr [eax],ebp
    L_0042f140:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f146:
        push ecx
    L_0042f147:
        mov edx,esi
    L_0042f149:
        call asm_AnimationManager_Find_004491c0
    L_0042f14e:
        cmp eax,ebx
    L_0042f150:
        jne short L_0042f158
    L_0042f152:
        mov dword ptr [edi+2C8h],ebx
    L_0042f158:
        add eax,10h
    L_0042f15b:
        cmp eax,ebx
    L_0042f15d:
        TH10_REL8(0x74, 0x0042f15d, VA_asm_target_0042f186)
    L_0042f15f:
        mov ecx,31h
    L_0042f164:
        TH10_REL8(0xeb, 0x0042f164, VA_asm_FUN_0042e5a0_part_0042f170)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042f170:
        mov edx,dword ptr [eax]
    L_0042f172:
        cmp word ptr [edx+38Ah],cx
    L_0042f179:
        je asm_target_0042f221
    L_0042f17f:
        mov eax,dword ptr [eax+4]
    L_0042f182:
        cmp eax,ebx
    L_0042f184:
        jne short L_0042f170
    L_0042f186:
        xor eax,eax
    L_0042f188:
        push eax
    L_0042f189:
        mov edx,esi
    L_0042f18b:
        call asm_AnimationManager_Find_004491c0
    L_0042f190:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f196:
        add eax,35Ch
    L_0042f19b:
        and ebp,0FFFFFFFDh
    L_0042f19e:
        mov dword ptr [eax],ebp
    L_0042f1a0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f1a6:
        push ecx
    L_0042f1a7:
        mov edx,esi
    L_0042f1a9:
        call asm_AnimationManager_Find_004491c0
    L_0042f1ae:
        cmp eax,ebx
    L_0042f1b0:
        jne short L_0042f1b8
    L_0042f1b2:
        mov dword ptr [edi+2C8h],ebx
    L_0042f1b8:
        add eax,10h
    L_0042f1bb:
        cmp eax,ebx
    L_0042f1bd:
        je short L_0042f1d6
    L_0042f1bf:
        mov ecx,32h
    L_0042f1c4:
        mov edx,dword ptr [eax]
    L_0042f1c6:
        cmp word ptr [edx+38Ah],cx
    L_0042f1cd:
        je short L_0042f22a
    L_0042f1cf:
        mov eax,dword ptr [eax+4]
    L_0042f1d2:
        cmp eax,ebx
    L_0042f1d4:
        jne short L_0042f1c4
    L_0042f1d6:
        xor eax,eax
    L_0042f1d8:
        push eax
    L_0042f1d9:
        mov edx,esi
    L_0042f1db:
        call asm_AnimationManager_Find_004491c0
    L_0042f1e0:
        mov ecx,dword ptr [eax+35Ch]
    L_0042f1e6:
        add eax,35Ch
    L_0042f1eb:
        pop esi
    L_0042f1ec:
        and ecx,0FFFFFFFDh
    L_0042f1ef:
        pop ebp
    L_0042f1f0:
        mov dword ptr [eax],ecx
    L_0042f1f2:
        pop ebx
    L_0042f1f3:
        ret
    L_0042f1f4:
        mov eax,dword ptr [eax]
    L_0042f1f6:
        mov eax,dword ptr [eax]
    L_0042f1f8:
        jmp asm_target_0042ef58
    L_0042f1fd:
        mov eax,dword ptr [eax]
    L_0042f1ff:
        mov eax,dword ptr [eax]
    L_0042f201:
        jmp asm_target_0042efb8
    L_0042f206:
        mov eax,dword ptr [eax]
    L_0042f208:
        mov eax,dword ptr [eax]
    L_0042f20a:
        jmp asm_target_0042f008
    L_0042f20f:
        mov eax,dword ptr [eax]
    L_0042f211:
        mov eax,dword ptr [eax]
    L_0042f213:
        jmp asm_target_0042f0c9
    L_0042f218:
        mov eax,dword ptr [eax]
    L_0042f21a:
        mov eax,dword ptr [eax]
    L_0042f21c:
        jmp asm_target_0042f128
    L_0042f221:
        mov eax,dword ptr [eax]
    L_0042f223:
        mov eax,dword ptr [eax]
    L_0042f225:
        jmp asm_target_0042f188
    L_0042f22a:
        mov eax,dword ptr [eax]
    L_0042f22c:
        mov eax,dword ptr [eax]
    L_0042f22e:
        jmp short L_0042f1d8
    L_0042f230:
        cmp al,64h
    L_0042f232:
        jge asm_target_0042f3a8
    L_0042f238:
        call asm_AnimationManager_Find_004491c0
    L_0042f23d:
        cmp eax,ebx
    L_0042f23f:
        jne short L_0042f247
    L_0042f241:
        mov dword ptr [edi+2C8h],ebx
    L_0042f247:
        add eax,10h
    L_0042f24a:
        cmp eax,ebx
    L_0042f24c:
        TH10_REL8(0x74, 0x0042f24c, VA_asm_target_0042f276)
    L_0042f24e:
        mov ecx,2Dh
    L_0042f253:
        TH10_REL8(0xeb, 0x0042f253, VA_asm_FUN_0042e5a0_part_0042f260)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00

    L_0042f260:
        mov edx,dword ptr [eax]
    L_0042f262:
        cmp word ptr [edx+38Ah],cx
    L_0042f269:
        je asm_target_0042f387
    L_0042f26f:
        mov eax,dword ptr [eax+4]
    L_0042f272:
        cmp eax,ebx
    L_0042f274:
        jne short L_0042f260
    L_0042f276:
        xor eax,eax
    L_0042f278:
        push eax
    L_0042f279:
        mov edx,esi
    L_0042f27b:
        call asm_AnimationManager_Find_004491c0
    L_0042f280:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f286:
        add eax,35Ch
    L_0042f28b:
        and ebp,0FFFFFFFDh
    L_0042f28e:
        mov dword ptr [eax],ebp
    L_0042f290:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f296:
        push ecx
    L_0042f297:
        mov edx,esi
    L_0042f299:
        call asm_AnimationManager_Find_004491c0
    L_0042f29e:
        cmp eax,ebx
    L_0042f2a0:
        jne short L_0042f2a8
    L_0042f2a2:
        mov dword ptr [edi+2C8h],ebx
    L_0042f2a8:
        add eax,10h
    L_0042f2ab:
        cmp eax,ebx
    L_0042f2ad:
        TH10_REL8(0x74, 0x0042f2ad, VA_asm_target_0042f2d6)
    L_0042f2af:
        mov ecx,2Eh
    L_0042f2b4:
        TH10_REL8(0xeb, 0x0042f2b4, VA_asm_FUN_0042e5a0_part_0042f2c0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042f2c0:
        mov edx,dword ptr [eax]
    L_0042f2c2:
        cmp word ptr [edx+38Ah],cx
    L_0042f2c9:
        je asm_target_0042f390
    L_0042f2cf:
        mov eax,dword ptr [eax+4]
    L_0042f2d2:
        cmp eax,ebx
    L_0042f2d4:
        jne short L_0042f2c0
    L_0042f2d6:
        xor eax,eax
    L_0042f2d8:
        push eax
    L_0042f2d9:
        mov edx,esi
    L_0042f2db:
        call asm_AnimationManager_Find_004491c0
    L_0042f2e0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f2e6:
        add eax,35Ch
    L_0042f2eb:
        or ebp,2
    L_0042f2ee:
        mov dword ptr [eax],ebp
    L_0042f2f0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f2f6:
        push ecx
    L_0042f2f7:
        mov edx,esi
    L_0042f2f9:
        call asm_AnimationManager_Find_004491c0
    L_0042f2fe:
        cmp eax,ebx
    L_0042f300:
        jne short L_0042f308
    L_0042f302:
        mov dword ptr [edi+2C8h],ebx
    L_0042f308:
        add eax,10h
    L_0042f30b:
        cmp eax,ebx
    L_0042f30d:
        je short L_0042f326
    L_0042f30f:
        mov ecx,31h
    L_0042f314:
        mov edx,dword ptr [eax]
    L_0042f316:
        cmp word ptr [edx+38Ah],cx
    L_0042f31d:
        TH10_REL8(0x74, 0x0042f31d, VA_asm_target_0042f399)
    L_0042f31f:
        mov eax,dword ptr [eax+4]
    L_0042f322:
        cmp eax,ebx
    L_0042f324:
        jne short L_0042f314
    L_0042f326:
        xor eax,eax
    L_0042f328:
        push eax
    L_0042f329:
        mov edx,esi
    L_0042f32b:
        call asm_AnimationManager_Find_004491c0
    L_0042f330:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f336:
        add eax,35Ch
    L_0042f33b:
        and ebp,0FFFFFFFDh
    L_0042f33e:
        mov dword ptr [eax],ebp
    L_0042f340:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f346:
        push ecx
    L_0042f347:
        mov edx,esi
    L_0042f349:
        call asm_AnimationManager_Find_004491c0
    L_0042f34e:
        cmp eax,ebx
    L_0042f350:
        jne short L_0042f358
    L_0042f352:
        mov dword ptr [edi+2C8h],ebx
    L_0042f358:
        add eax,10h
    L_0042f35b:
        cmp eax,ebx
    L_0042f35d:
        je asm_target_0042f506
    L_0042f363:
        mov ecx,32h
    L_0042f368:
        TH10_REL8(0xeb, 0x0042f368, VA_asm_FUN_0042e5a0_part_0042f370)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0042f370:
        mov edx,dword ptr [eax]
    L_0042f372:
        cmp word ptr [edx+38Ah],cx
    L_0042f379:
        je short L_0042f39f
    L_0042f37b:
        mov eax,dword ptr [eax+4]
    L_0042f37e:
        cmp eax,ebx
    L_0042f380:
        jne short L_0042f370
    L_0042f382:
        jmp asm_target_0042f506
    L_0042f387:
        mov eax,dword ptr [eax]
    L_0042f389:
        mov eax,dword ptr [eax]
    L_0042f38b:
        jmp asm_target_0042f278
    L_0042f390:
        mov eax,dword ptr [eax]
    L_0042f392:
        mov eax,dword ptr [eax]
    L_0042f394:
        jmp asm_target_0042f2d8
    L_0042f399:
        mov eax,dword ptr [eax]
    L_0042f39b:
        mov eax,dword ptr [eax]
    L_0042f39d:
        TH10_REL8(0xeb, 0x0042f39d, VA_asm_target_0042f328)
    L_0042f39f:
        mov eax,dword ptr [eax]
    L_0042f3a1:
        mov eax,dword ptr [eax]
    L_0042f3a3:
        jmp asm_target_0042f508
    L_0042f3a8:
        call asm_AnimationManager_Find_004491c0
    L_0042f3ad:
        cmp eax,ebx
    L_0042f3af:
        jne short L_0042f3b7
    L_0042f3b1:
        mov dword ptr [edi+2C8h],ebx
    L_0042f3b7:
        add eax,10h
    L_0042f3ba:
        cmp eax,ebx
    L_0042f3bc:
        TH10_REL8(0x74, 0x0042f3bc, VA_asm_target_0042f3e6)
    L_0042f3be:
        mov ecx,2Dh
    L_0042f3c3:
        TH10_REL8(0xeb, 0x0042f3c3, VA_asm_FUN_0042e5a0_part_0042f3d0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00

    L_0042f3d0:
        mov edx,dword ptr [eax]
    L_0042f3d2:
        cmp word ptr [edx+38Ah],cx
    L_0042f3d9:
        je asm_target_0042f524
    L_0042f3df:
        mov eax,dword ptr [eax+4]
    L_0042f3e2:
        cmp eax,ebx
    L_0042f3e4:
        jne short L_0042f3d0
    L_0042f3e6:
        xor eax,eax
    L_0042f3e8:
        push eax
    L_0042f3e9:
        mov edx,esi
    L_0042f3eb:
        call asm_AnimationManager_Find_004491c0
    L_0042f3f0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f3f6:
        add eax,35Ch
    L_0042f3fb:
        or ebp,2
    L_0042f3fe:
        mov dword ptr [eax],ebp
    L_0042f400:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f406:
        push ecx
    L_0042f407:
        mov edx,esi
    L_0042f409:
        call asm_AnimationManager_Find_004491c0
    L_0042f40e:
        cmp eax,ebx
    L_0042f410:
        jne short L_0042f418
    L_0042f412:
        mov dword ptr [edi+2C8h],ebx
    L_0042f418:
        add eax,10h
    L_0042f41b:
        cmp eax,ebx
    L_0042f41d:
        TH10_REL8(0x74, 0x0042f41d, VA_asm_target_0042f446)
    L_0042f41f:
        mov ecx,2Eh
    L_0042f424:
        TH10_REL8(0xeb, 0x0042f424, VA_asm_FUN_0042e5a0_part_0042f430)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042f430:
        mov edx,dword ptr [eax]
    L_0042f432:
        cmp word ptr [edx+38Ah],cx
    L_0042f439:
        je asm_target_0042f52d
    L_0042f43f:
        mov eax,dword ptr [eax+4]
    L_0042f442:
        cmp eax,ebx
    L_0042f444:
        jne short L_0042f430
    L_0042f446:
        xor eax,eax
    L_0042f448:
        push eax
    L_0042f449:
        mov edx,esi
    L_0042f44b:
        call asm_AnimationManager_Find_004491c0
    L_0042f450:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f456:
        add eax,35Ch
    L_0042f45b:
        or ebp,2
    L_0042f45e:
        mov dword ptr [eax],ebp
    L_0042f460:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f466:
        push ecx
    L_0042f467:
        mov edx,esi
    L_0042f469:
        call asm_AnimationManager_Find_004491c0
    L_0042f46e:
        cmp eax,ebx
    L_0042f470:
        jne short L_0042f478
    L_0042f472:
        mov dword ptr [edi+2C8h],ebx
    L_0042f478:
        add eax,10h
    L_0042f47b:
        cmp eax,ebx
    L_0042f47d:
        TH10_REL8(0x74, 0x0042f47d, VA_asm_target_0042f4a6)
    L_0042f47f:
        mov ecx,31h
    L_0042f484:
        TH10_REL8(0xeb, 0x0042f484, VA_asm_FUN_0042e5a0_part_0042f490)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042f490:
        mov edx,dword ptr [eax]
    L_0042f492:
        cmp word ptr [edx+38Ah],cx
    L_0042f499:
        je asm_target_0042f536
    L_0042f49f:
        mov eax,dword ptr [eax+4]
    L_0042f4a2:
        cmp eax,ebx
    L_0042f4a4:
        jne short L_0042f490
    L_0042f4a6:
        xor eax,eax
    L_0042f4a8:
        push eax
    L_0042f4a9:
        mov edx,esi
    L_0042f4ab:
        call asm_AnimationManager_Find_004491c0
    L_0042f4b0:
        mov ebp,dword ptr [eax+35Ch]
    L_0042f4b6:
        add eax,35Ch
    L_0042f4bb:
        or ebp,2
    L_0042f4be:
        mov dword ptr [eax],ebp
    L_0042f4c0:
        mov ecx,dword ptr [edi+2C8h]
    L_0042f4c6:
        push ecx
    L_0042f4c7:
        mov edx,esi
    L_0042f4c9:
        call asm_AnimationManager_Find_004491c0
    L_0042f4ce:
        cmp eax,ebx
    L_0042f4d0:
        jne short L_0042f4d8
    L_0042f4d2:
        mov dword ptr [edi+2C8h],ebx
    L_0042f4d8:
        add eax,10h
    L_0042f4db:
        cmp eax,ebx
    L_0042f4dd:
        TH10_REL8(0x74, 0x0042f4dd, VA_asm_target_0042f506)
    L_0042f4df:
        mov ecx,32h
    L_0042f4e4:
        TH10_REL8(0xeb, 0x0042f4e4, VA_asm_FUN_0042e5a0_part_0042f4f0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042f4f0:
        mov edx,dword ptr [eax]
    L_0042f4f2:
        cmp word ptr [edx+38Ah],cx
    L_0042f4f9:
        je asm_target_0042f39f
    L_0042f4ff:
        mov eax,dword ptr [eax+4]
    L_0042f502:
        cmp eax,ebx
    L_0042f504:
        jne short L_0042f4f0
    L_0042f506:
        xor eax,eax
    L_0042f508:
        mov edx,esi
    L_0042f50a:
        push eax
    L_0042f50b:
        call asm_AnimationManager_Find_004491c0
    L_0042f510:
        mov ecx,dword ptr [eax+35Ch]
    L_0042f516:
        add eax,35Ch
    L_0042f51b:
        pop esi
    L_0042f51c:
        or ecx,2
    L_0042f51f:
        pop ebp
    L_0042f520:
        mov dword ptr [eax],ecx
    L_0042f522:
        pop ebx
    L_0042f523:
        ret
    L_0042f524:
        mov eax,dword ptr [eax]
    L_0042f526:
        mov eax,dword ptr [eax]
    L_0042f528:
        jmp asm_target_0042f3e8
    L_0042f52d:
        mov eax,dword ptr [eax]
    L_0042f52f:
        mov eax,dword ptr [eax]
    L_0042f531:
        jmp asm_target_0042f448
    L_0042f536:
        mov eax,dword ptr [eax]
    L_0042f538:
        mov eax,dword ptr [eax]
    L_0042f53a:
        jmp asm_target_0042f4a8
    }
}
