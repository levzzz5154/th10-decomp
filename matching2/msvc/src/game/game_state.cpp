#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3604): closest_byte_count=0/188; first_diff=compile failure;
// residual_class=compiler-generated SEH registration/handler frame plus the
// existing C-linkage declaration and EH vector-constructor ABI.
// variants_tested=live Ghidra decompilation, caller CreateGameState 0x00402640,
// readable unsigned-long/vector-constructor candidate (MSVC C2733/C2664), and
// exact retail wrapper baseline.
// next_lever=typed native-LTCG constructor cluster with an updated declaration
// contract for the stdcall entry and EH vector helper.
// Current Ghidra entry/caller/callee audit: see
// matching2/reference/recovery_notes/construct_game_state_00402160_ghidra_audit.md.

// 0x00402160..0x0040221B: ConstructGameState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ConstructGameState_00402160() {
    __asm {
    L_00402160:
        mov eax,dword ptr fs:[0]
    L_00402166:
        push 0FFFFFFFFh
    L_00402168:
        push 46556Bh
    L_0040216d:
        push eax
    L_0040216e:
        mov dword ptr fs:[0],esp
    L_00402175:
        push esi
    L_00402176:
        mov esi,dword ptr [esp+14h]
    L_0040217a:
        mov ecx,dword ptr [esi+34h]
    L_0040217d:
        push edi
    L_0040217e:
        mov edi,0FFFFFFFEh
    L_00402183:
        and ecx,edi
    L_00402185:
        mov dword ptr [esi+34h],ecx
    L_00402188:
        and dword ptr [esi+48h],edi
    L_0040218b:
        and dword ptr [esi+90h],edi
    L_00402191:
        mov ecx,dword ptr [esi+0DCh]
    L_00402197:
        push 401FF0h
    L_0040219c:
        and ecx,edi
    L_0040219e:
        mov dword ptr [esi+0DCh],ecx
    L_004021a4:
        mov eax,dword ptr [esi+168h]
    L_004021aa:
        push 402050h
    L_004021af:
        and eax,edi
    L_004021b1:
        push 8
    L_004021b3:
        mov dword ptr [esi+168h],eax
    L_004021b9:
        push 3ACh
    L_004021be:
        lea eax,[esi+180h]
    L_004021c4:
        push eax
    L_004021c5:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004021ca:
        push 401FF0h
    L_004021cf:
        push 402050h
    L_004021d4:
        push 3
    L_004021d6:
        push 3ACh
    L_004021db:
        lea ecx,[esi+1F08h]
    L_004021e1:
        push ecx
    L_004021e2:
        mov dword ptr [esp+24h],0
    L_004021ea:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004021ef:
        and dword ptr [esi+2A2Ch],edi
    L_004021f5:
        xor eax,eax
    L_004021f7:
        mov edi,esi
    L_004021f9:
        mov ecx,0AD9h
    L_004021fe:
        rep stosd
    L_00402200:
        mov eax,dword ptr [esi]
    L_00402202:
        mov ecx,dword ptr [esp+8]
    L_00402206:
        or eax,2
    L_00402209:
        mov dword ptr [esi],eax
    L_0040220b:
        pop edi
    L_0040220c:
        mov eax,esi
    L_0040220e:
        mov dword ptr fs:[0],ecx
    L_00402215:
        pop esi
    L_00402216:
        add esp,0Ch
    L_00402219:
        ret 4
    }
}





// BLOCKED (D3604): closest_byte_count=0/1099; first_diff=unmeasured;
// residual_class=private caller ABI through 0x00403060, renderer/device
// virtual-call schedule, state layout spanning 0x2A0C..0x2B60, and eight
// live-in helper clusters (0x00405300, 0x00405410, 0x004451C0, and peers).
// variants_tested=live Ghidra decompilation, xref caller 0x00403060, native
// forwarder layout inspection, and exact retail wrapper baseline.
// next_lever=native-LTCG cluster joining 0x00403060 and this helper with the
// D3D/device and game-state callees rooted in one schema-2 scope.
// 0x00402850..0x00402C9A: FUN_00402850
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00402850_00402850() {
    __asm {
    L_00402850:
        sub esp,20h
    L_00402853:
        push ebp
    L_00402854:
        mov ebp,dword ptr [esp+28h]
    L_00402858:
        mov eax,dword ptr [ebp+2A18h]
    L_0040285e:
        test al,8
    L_00402860:
        je short L_0040286e
    L_00402862:
        mov eax,1
    L_00402867:
        pop ebp
    L_00402868:
        add esp,20h
    L_0040286b:
        ret 4
    L_0040286e:
        test al,4
    L_00402870:
        push ebx
    L_00402871:
        push esi
    L_00402872:
        push edi
    L_00402873:
        je short L_00402882
    L_00402875:
        cmp dword ptr [ebp+2A20h],3Ch
    L_0040287c:
        jge asm_target_00402a40
    L_00402882:
        mov esi,dword ptr [data_00491c10]
    L_00402888:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0040288d:
        mov eax,dword ptr [data_00491e64]
    L_00402892:
        mov dword ptr [ebp+2B34h],eax
    L_00402898:
        mov ecx,dword ptr [data_00491e68]
    L_0040289e:
        mov dword ptr [ebp+2B38h],ecx
    L_004028a4:
        lea esi,[ebp+2A4Ch]
    L_004028aa:
        mov ecx,46h
    L_004028af:
        mov edi,491D7Ch
    L_004028b4:
        rep movsd
    L_004028b6:
        mov edi,491D7Ch
    L_004028bb:
        mov dword ptr [data_00491fac],edi
    L_004028c1:
        call asm_FUN_004215a0_004215a0
    L_004028c6:
        mov ecx,dword ptr [data_00491fac]
    L_004028cc:
        mov eax,dword ptr [data_00491c30]
    L_004028d1:
        mov edx,dword ptr [eax]
    L_004028d3:
        add ecx,0CCh
    L_004028d9:
        push ecx
    L_004028da:
        push eax
    L_004028db:
        call dword ptr [edx+0BCh]
    L_004028e1:
        mov esi,dword ptr [data_00491c10]
    L_004028e7:
        xor ebx,ebx
    L_004028e9:
        mov dword ptr [data_00491fb0],ebx
    L_004028ef:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004028f4:
        mov eax,dword ptr [data_00491c30]
    L_004028f9:
        mov edx,dword ptr [eax]
    L_004028fb:
        push 1
    L_004028fd:
        push 0Eh
    L_004028ff:
        push eax
    L_00402900:
        call dword ptr [edx+0E4h]
    L_00402906:
        mov esi,dword ptr [data_00491c10]
    L_0040290c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402911:
        mov eax,dword ptr [data_00491c30]
    L_00402916:
        mov ecx,dword ptr [eax]
    L_00402918:
        push 4
    L_0040291a:
        push 17h
    L_0040291c:
        push eax
    L_0040291d:
        call dword ptr [ecx+0E4h]
    L_00402923:
        mov esi,dword ptr [data_00491c10]
    L_00402929:
        mov edi,dword ptr [ebp+2B60h]
    L_0040292f:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402934:
        mov eax,dword ptr [data_00491c30]
    L_00402939:
        mov edx,dword ptr [eax]
    L_0040293b:
        push edi
    L_0040293c:
        push 22h
    L_0040293e:
        push eax
    L_0040293f:
        call dword ptr [edx+0E4h]
    L_00402945:
        mov esi,dword ptr [data_00491c10]
    L_0040294b:
        mov edi,dword ptr [ebp+2B48h]
    L_00402951:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402956:
        mov eax,dword ptr [data_00491c30]
    L_0040295b:
        mov ecx,dword ptr [eax]
    L_0040295d:
        push edi
    L_0040295e:
        push 24h
    L_00402960:
        push eax
    L_00402961:
        call dword ptr [ecx+0E4h]
    L_00402967:
        mov esi,dword ptr [data_00491c10]
    L_0040296d:
        mov edi,dword ptr [ebp+2B4Ch]
    L_00402973:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402978:
        mov eax,dword ptr [data_00491c30]
    L_0040297d:
        mov edx,dword ptr [eax]
    L_0040297f:
        push edi
    L_00402980:
        push 25h
    L_00402982:
        push eax
    L_00402983:
        call dword ptr [edx+0E4h]
    L_00402989:
        mov eax,dword ptr [data_00491c30]
    L_0040298e:
        mov ecx,dword ptr [eax]
    L_00402990:
        push ebx
    L_00402991:
        push 3F800000h
    L_00402996:
        push ebx
    L_00402997:
        push 2
    L_00402999:
        push ebx
    L_0040299a:
        push ebx
    L_0040299b:
        push eax
    L_0040299c:
        call dword ptr [ecx+0ACh]
    L_004029a2:
        test byte ptr [ebp+2A18h],4
    L_004029a9:
        je short L_004029f4
    L_004029ab:
        cmp dword ptr [ebp+2A34h],22h
    L_004029b2:
        jge short L_004029f4
    L_004029b4:
        mov eax,dword ptr [data_00491c30]
    L_004029b9:
        push ebx
    L_004029ba:
        push 3F800000h
    L_004029bf:
        push ebx
    L_004029c0:
        push 1
    L_004029c2:
        lea ecx,[esp+20h]
    L_004029c6:
        push ecx
    L_004029c7:
        push 1
    L_004029c9:
        mov dword ptr [esp+28h],20h
    L_004029d1:
        mov dword ptr [esp+2Ch],10h
    L_004029d9:
        mov dword ptr [esp+30h],1A0h
    L_004029e1:
        mov dword ptr [esp+34h],1D0h
    L_004029e9:
        mov edx,dword ptr [eax]
    L_004029eb:
        push eax
    L_004029ec:
        call dword ptr [edx+0ACh]
    L_004029f2:
        jmp short L_00402a42
    L_004029f4:
        mov ecx,dword ptr [ebp+2B60h]
    L_004029fa:
        mov eax,dword ptr [data_00491c30]
    L_004029ff:
        push ebx
    L_00402a00:
        push 3F800000h
    L_00402a05:
        and ecx,0FFFFFFh
    L_00402a0b:
        push ecx
    L_00402a0c:
        push 1
    L_00402a0e:
        lea ecx,[esp+30h]
    L_00402a12:
        push ecx
    L_00402a13:
        push 1
    L_00402a15:
        mov dword ptr [esp+38h],20h
    L_00402a1d:
        mov dword ptr [esp+3Ch],10h
    L_00402a25:
        mov dword ptr [esp+40h],1A0h
    L_00402a2d:
        mov dword ptr [esp+44h],1D0h
    L_00402a35:
        mov edx,dword ptr [eax]
    L_00402a37:
        push eax
    L_00402a38:
        call dword ptr [edx+0ACh]
    L_00402a3e:
        jmp short L_00402a42
    L_00402a40:
        xor ebx,ebx
    L_00402a42:
        mov eax,dword ptr [ebp+2A18h]
    L_00402a48:
        test al,4
    L_00402a4a:
        je short L_00402a95
    L_00402a4c:
        cmp dword ptr [ebp+2A20h],1Eh
    L_00402a53:
        jge short L_00402a86
    L_00402a55:
        push ebx
    L_00402a56:
        push ebx
    L_00402a57:
        push ebx
    L_00402a58:
        push 1Eh
    L_00402a5a:
        push 3
    L_00402a5c:
        mov ebx,0Fh
    L_00402a61:
        call asm_AsciiManager_CreateRetail_0043c8b0
    L_00402a66:
        mov ecx,dword ptr [ebp+2A18h]
    L_00402a6c:
        or ecx,1
    L_00402a6f:
        push 1
    L_00402a71:
        lea eax,[ebp+2A1Ch]
    L_00402a77:
        mov dword ptr [ebp+2A18h],ecx
    L_00402a7d:
        call asm_Player_SetSchedulerValue_00405410
    L_00402a82:
        xor ebx,ebx
    L_00402a84:
        jmp short L_00402a95
    L_00402a86:
        and eax,0FFFFFFFEh
    L_00402a89:
        mov byte ptr [ebp+1EEBh],bl
    L_00402a8f:
        mov dword ptr [ebp+2A18h],eax
    L_00402a95:
        cmp byte ptr [ebp+1EEBh],bl
    L_00402a9b:
        mov esi,dword ptr [data_00491c10]
    L_00402aa1:
        mov edi,1
    L_00402aa6:
        je short L_00402aba
    L_00402aa8:
        mov eax,dword ptr [ebp+1EE8h]
    L_00402aae:
        mov dword ptr [esi+73245Ch],edi
    L_00402ab4:
        mov dword ptr [esi+732458h],eax
    L_00402aba:
        test byte ptr [ebp+2A18h],1
    L_00402ac1:
        mov dword ptr [ebp+2A0Ch],ebx
    L_00402ac7:
        mov dword ptr [ebp+2A10h],ebx
    L_00402acd:
        mov dword ptr [ebp+2A14h],ebx
    L_00402ad3:
        je asm_target_00402c34
    L_00402ad9:
        cmp dword ptr [ebp+514h],ebx
    L_00402adf:
        je asm_target_00402baa
    L_00402ae5:
        xor ebx,ebx
    L_00402ae7:
        mov esi,491C28h
    L_00402aec:
        call asm_FUN_00405300_00405300
    L_00402af1:
        mov edi,esi
    L_00402af3:
        call asm_FUN_00420cd0_00420cd0
    L_00402af8:
        mov esi,dword ptr [data_00491c10]
    L_00402afe:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402b03:
        mov esi,dword ptr [data_00491c10]
    L_00402b09:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402b0e:
        mov eax,dword ptr [data_00491c30]
    L_00402b13:
        mov edx,dword ptr [eax]
    L_00402b15:
        push ebx
    L_00402b16:
        push 0Eh
    L_00402b18:
        push eax
    L_00402b19:
        call dword ptr [edx+0E4h]
    L_00402b1f:
        lea esi,[ebp+180h]
    L_00402b25:
        mov edi,8
    L_00402b2a:
        lea ebx,[ebx+force_disp32_zero]
    L_00402b30:
        mov eax,dword ptr [esi+394h]
    L_00402b36:
        test eax,eax
    L_00402b38:
        je short L_00402b47
    L_00402b3a:
        mov ecx,dword ptr [data_00491c10]
    L_00402b40:
        mov eax,esi
    L_00402b42:
        call asm_FUN_004451c0_004451c0
    L_00402b47:
        add esi,3ACh
    L_00402b4d:
        dec edi
    L_00402b4e:
        jne short L_00402b30
    L_00402b50:
        mov esi,dword ptr [data_00491c10]
    L_00402b56:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402b5b:
        mov eax,dword ptr [data_00491c30]
    L_00402b60:
        mov ecx,dword ptr [eax]
    L_00402b62:
        push 1
    L_00402b64:
        push 0Eh
    L_00402b66:
        push eax
    L_00402b67:
        call dword ptr [ecx+0E4h]
    L_00402b6d:
        mov edi,491D7Ch
    L_00402b72:
        mov dword ptr [data_00491fac],edi
    L_00402b78:
        call asm_FUN_004215a0_004215a0
    L_00402b7d:
        mov ecx,dword ptr [data_00491fac]
    L_00402b83:
        mov eax,dword ptr [data_00491c30]
    L_00402b88:
        mov edx,dword ptr [eax]
    L_00402b8a:
        add ecx,0CCh
    L_00402b90:
        push ecx
    L_00402b91:
        push eax
    L_00402b92:
        call dword ptr [edx+0BCh]
    L_00402b98:
        mov esi,dword ptr [data_00491c10]
    L_00402b9e:
        mov dword ptr [data_00491fb0],0
    L_00402ba8:
        xor ebx,ebx
    L_00402baa:
        mov eax,dword ptr [data_00492378]
    L_00402baf:
        mov edi,1
    L_00402bb4:
        cmp eax,edi
    L_00402bb6:
        je short L_00402bd4
    L_00402bb8:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402bbd:
        mov eax,dword ptr [data_00491c30]
    L_00402bc2:
        push edi
    L_00402bc3:
        push 1Ch
    L_00402bc5:
        mov dword ptr [data_00492378],edi
    L_00402bcb:
        mov edx,dword ptr [eax]
    L_00402bcd:
        push eax
    L_00402bce:
        call dword ptr [edx+0E4h]
    L_00402bd4:
        push ebx
    L_00402bd5:
        push ebp
    L_00402bd6:
        call asm_FUN_00403a30_00403a30
    L_00402bdb:
        push edi
    L_00402bdc:
        push ebp
    L_00402bdd:
        call asm_FUN_00403a30_00403a30
    L_00402be2:
        push 2
    L_00402be4:
        push ebp
    L_00402be5:
        call asm_FUN_00403a30_00403a30
    L_00402bea:
        push 3
    L_00402bec:
        push ebp
    L_00402bed:
        call asm_FUN_00403a30_00403a30
    L_00402bf2:
        push 4
    L_00402bf4:
        push ebp
    L_00402bf5:
        call asm_FUN_00403a30_00403a30
    L_00402bfa:
        push 5
    L_00402bfc:
        push ebp
    L_00402bfd:
        call asm_FUN_00403a30_00403a30
    L_00402c02:
        push 6
    L_00402c04:
        push ebp
    L_00402c05:
        call asm_FUN_00403a30_00403a30
    L_00402c0a:
        push 7
    L_00402c0c:
        push ebp
    L_00402c0d:
        call asm_FUN_00403a30_00403a30
    L_00402c12:
        mov esi,dword ptr [data_00491c10]
    L_00402c18:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402c1d:
        mov eax,dword ptr [ebp+1EE4h]
    L_00402c23:
        cmp eax,ebx
    L_00402c25:
        mov esi,dword ptr [data_00491c10]
    L_00402c2b:
        je short L_00402c34
    L_00402c2d:
        inc eax
    L_00402c2e:
        mov dword ptr [ebp+1EE4h],eax
    L_00402c34:
        mov dword ptr [esi+73245Ch],ebx
    L_00402c3a:
        mov dword ptr [esi+732458h],80808080h
    L_00402c44:
        cmp dword ptr [ebp+1EECh],ebx
    L_00402c4a:
        je short L_00402c5c
    L_00402c4c:
        mov dword ptr [esi+73245Ch],edi
    L_00402c52:
        mov dword ptr [esi+732458h],0FF404040h
    L_00402c5c:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402c61:
        mov eax,dword ptr [data_00491c30]
    L_00402c66:
        mov ecx,dword ptr [eax]
    L_00402c68:
        push ebx
    L_00402c69:
        push 0Eh
    L_00402c6b:
        push eax
    L_00402c6c:
        call dword ptr [ecx+0E4h]
    L_00402c72:
        mov esi,dword ptr [data_00491c10]
    L_00402c78:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_00402c7d:
        mov eax,dword ptr [data_00491c30]
    L_00402c82:
        mov edx,dword ptr [eax]
    L_00402c84:
        push 8
    L_00402c86:
        push 17h
    L_00402c88:
        push eax
    L_00402c89:
        call dword ptr [edx+0E4h]
    L_00402c8f:
        mov eax,edi
    L_00402c91:
        pop edi
    L_00402c92:
        pop esi
    L_00402c93:
        pop ebx
    L_00402c94:
        pop ebp
    L_00402c95:
        add esp,20h
    L_00402c98:
        ret 4
    }
}

