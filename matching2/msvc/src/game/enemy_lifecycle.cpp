#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004066e0_004066e0() {
    __asm {
    L_004066e0:
        push esi
    L_004066e1:
        mov esi,dword ptr [eax+ecx*4+14h]
    L_004066e5:
        test esi,esi
    L_004066e7:
        je short L_0040675f
    L_004066e9:
        lea esp,[esp+force_disp32_zero]
    L_004066f0:
        fld dword ptr [esi+3B4h]
    L_004066f6:
        fadd dword ptr [data_00470b4c]
    L_004066fc:
        fstp dword ptr [esi+33Ch]
    L_00406702:
        fld dword ptr [esi+3B8h]
    L_00406708:
        fadd dword ptr [data_00470b48]
    L_0040670e:
        fstp dword ptr [esi+340h]
    L_00406714:
        mov edx,dword ptr [esi+3BCh]
    L_0040671a:
        mov dword ptr [esi+344h],edx
    L_00406720:
        test dword ptr [esi+364h],8000000h
    L_0040672a:
        je short L_00406747
    L_0040672c:
        mov eax,dword ptr [esi+3E4h]
    L_00406732:
        push 3FC90FDBh
    L_00406737:
        push eax
    L_00406738:
        call asm_Angle_NormalizeSum_0044bc10
    L_0040673d:
        fstp dword ptr [esi+34h]
    L_00406740:
        or dword ptr [esi+364h],4
    L_00406747:
        mov ecx,dword ptr [data_00491c10]
    L_0040674d:
        lea eax,[esi+8]
    L_00406750:
        call asm_FUN_004451c0_004451c0
    L_00406755:
        mov esi,dword ptr [esi+44Ch]
    L_0040675b:
        test esi,esi
    L_0040675d:
        jne short L_004066f0
    L_0040675f:
        mov eax,1
    L_00406764:
        pop esi
    L_00406765:
        ret
    }
}

// 0x00408100..0x00408203: FUN_00408100
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408100_00408100() {
    __asm {
    L_00408100:
        sub esp,18h
    L_00408103:
        push ebp
    L_00408104:
        push esi
    L_00408105:
        mov esi,eax
    L_00408107:
        push edi
    L_00408108:
        add esi,60h
    L_0040810b:
        mov ebp,7D0h
    L_00408110:
        mov ax,word ptr [esi+446h]
    L_00408117:
        test ax,ax
    L_0040811a:
        je asm_target_004081ec
    L_00408120:
        cmp ax,3
    L_00408124:
        je asm_target_004081ec
    L_0040812a:
        mov eax,dword ptr [esp+30h]
    L_0040812e:
        test eax,eax
    L_00408130:
        je short L_0040813d
    L_00408132:
        mov eax,dword ptr [esi+4]
    L_00408135:
        test eax,eax
    L_00408137:
        jne asm_target_004081ec
    L_0040813d:
        fld dword ptr [esi+3B4h]
    L_00408143:
        lea edi,[esi+3B4h]
    L_00408149:
        fsub dword ptr [ebx]
    L_0040814b:
        fstp dword ptr [esp+18h]
    L_0040814f:
        mov eax,dword ptr [esp+18h]
    L_00408153:
        fld dword ptr [esi+3B8h]
    L_00408159:
        mov dword ptr [esp+0Ch],eax
    L_0040815d:
        fsub dword ptr [ebx+4]
    L_00408160:
        fstp dword ptr [esp+1Ch]
    L_00408164:
        mov ecx,dword ptr [esp+1Ch]
    L_00408168:
        fld dword ptr [esi+3BCh]
    L_0040816e:
        mov dword ptr [esp+10h],ecx
    L_00408172:
        fsub dword ptr [ebx+8]
    L_00408175:
        fstp dword ptr [esp+20h]
    L_00408179:
        mov edx,dword ptr [esp+20h]
    L_0040817d:
        fld dword ptr [esi+3F0h]
    L_00408183:
        mov dword ptr [esp+14h],edx
    L_00408187:
        fmul dword ptr [data_00470b0c]
    L_0040818d:
        fadd dword ptr [esp+28h]
    L_00408191:
        fld dword ptr [esp+10h]
    L_00408195:
        fmul dword ptr [esp+10h]
    L_00408199:
        fld dword ptr [esp+0Ch]
    L_0040819d:
        fmul dword ptr [esp+0Ch]
    L_004081a1:
        faddp st(1),st
    L_004081a3:
        fld st(1)
    L_004081a5:
        fmul st,st(2)
    L_004081a7:
        fcompp
    L_004081a9:
        fnstsw ax
    L_004081ab:
        fstp st(0)
    L_004081ad:
        test ah,5
    L_004081b0:
        jnp short L_004081ec
    L_004081b2:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_004081b7:
        push 40000000h
    L_004081bc:
        push 40000000h
    L_004081c1:
        mov ecx,edi
    L_004081c3:
        call asm_OutsideAxisAlignedBounds_004086b0
    L_004081c8:
        test eax,eax
    L_004081ca:
        jne short L_004081ec
    L_004081cc:
        mov eax,dword ptr [esp+2Ch]
    L_004081d0:
        test eax,eax
    L_004081d2:
        je short L_004081ec
    L_004081d4:
        mov eax,dword ptr [data_00477818]
    L_004081d9:
        push 3F19999Ah
    L_004081de:
        push 0BFC90FDBh
    L_004081e3:
        push 0FFFFFFFFh
    L_004081e5:
        push 8
    L_004081e7:
        call asm_FUN_0041bb00_0041bb00
    L_004081ec:
        add esi,7F0h
    L_004081f2:
        dec ebp
    L_004081f3:
        jne asm_target_00408110
    L_004081f9:
        pop edi
    L_004081fa:
        pop esi
    L_004081fb:
        xor eax,eax
    L_004081fd:
        pop ebp
    L_004081fe:
        add esp,18h
    L_00408201:
        ret 0Ch
    }
}

// 0x0040B110..0x0040B1A3: FUN_0040b110
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b110_0040b110() {
    __asm {
    L_0040b110:
        push ebx
    L_0040b111:
        push ebp
    L_0040b112:
        push esi
    L_0040b113:
        mov esi,dword ptr [data_00491c10]
    L_0040b119:
        shl eax,4
    L_0040b11c:
        add eax,474430h
    L_0040b121:
        push edi
    L_0040b122:
        mov edi,eax
    L_0040b124:
        movsx ebp,word ptr [edi]
    L_0040b127:
        call asm_FUN_00449950_00449950
    L_0040b12c:
        mov ecx,dword ptr [esp+18h]
    L_0040b130:
        mov ebx,eax
    L_0040b132:
        mov eax,dword ptr [ebx+35Ch]
    L_0040b138:
        push ebp
    L_0040b139:
        or eax,40000000h
    L_0040b13e:
        push ebx
    L_0040b13f:
        mov dword ptr [ebx+20h],0Fh
    L_0040b146:
        mov dword ptr [ebx+35Ch],eax
    L_0040b14c:
        call asm_FUN_00449870_00449870
    L_0040b151:
        mov esi,dword ptr [data_00491c10]
    L_0040b157:
        lea eax,[esp+18h]
    L_0040b15b:
        mov edx,esi
    L_0040b15d:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0040b162:
        mov ebx,dword ptr [esp+18h]
    L_0040b166:
        push ebx
    L_0040b167:
        mov edx,esi
    L_0040b169:
        call asm_AnimationManager_Find_004491c0
    L_0040b16e:
        mov esi,eax
    L_0040b170:
        test esi,esi
    L_0040b172:
        jne short L_0040b176
    L_0040b174:
        xor ebx,ebx
    L_0040b176:
        mov eax,dword ptr [edi+4]
    L_0040b179:
        test eax,eax
    L_0040b17b:
        je short L_0040b185
    L_0040b17d:
        mov edx,dword ptr [esp+1Ch]
    L_0040b181:
        mov ecx,esi
    L_0040b183:
        call eax
    L_0040b185:
        mov eax,dword ptr [edi+8]
    L_0040b188:
        mov dword ptr [esi+398h],eax
    L_0040b18e:
        mov ecx,dword ptr [edi+0Ch]
    L_0040b191:
        mov eax,dword ptr [esp+14h]
    L_0040b195:
        pop edi
    L_0040b196:
        mov dword ptr [esi+39Ch],ecx
    L_0040b19c:
        pop esi
    L_0040b19d:
        pop ebp
    L_0040b19e:
        mov dword ptr [eax],ebx
    L_0040b1a0:
        pop ebx
    L_0040b1a1:
        ret 0Ch
    }
}

// 0x0040D750..0x0040D7F5: Enemy_TimerSweepRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Enemy_TimerSweepRetail_0040d750() {
    __asm {
    L_0040d750:
        push esi
    L_0040d751:
        mov esi,dword ptr [edi+58h]
    L_0040d754:
        test esi,esi
    L_0040d756:
        je short L_0040d7a2
    L_0040d758:
        push ebx
    L_0040d759:
        lea esp,[esp+force_disp32_zero]
    L_0040d760:
        mov eax,dword ptr [esi]
    L_0040d762:
        test dword ptr [eax+2480h],20000h
    L_0040d76c:
        mov ebx,dword ptr [esi+4]
    L_0040d76f:
        jne short L_0040d78e
    L_0040d771:
        add eax,103Ch
    L_0040d776:
        push eax
    L_0040d777:
        call asm_FUN_0040dc80_0040dc80
    L_0040d77c:
        test eax,eax
    L_0040d77e:
        jne short L_0040d78e
    L_0040d780:
        mov esi,dword ptr [esi]
    L_0040d782:
        and dword ptr [esi+2480h],0FFFFFBFFh
    L_0040d78c:
        jmp short L_0040d79b
    L_0040d78e:
        mov ecx,dword ptr [esi]
    L_0040d790:
        test ecx,ecx
    L_0040d792:
        je short L_0040d79b
    L_0040d794:
        mov eax,dword ptr [ecx]
    L_0040d796:
        push 1
    L_0040d798:
        call dword ptr [eax+14h]
    L_0040d79b:
        test ebx,ebx
    L_0040d79d:
        mov esi,ebx
    L_0040d79f:
        jne short L_0040d760
    L_0040d7a1:
        pop ebx
    L_0040d7a2:
        mov edx,dword ptr [edi+44h]
    L_0040d7a5:
        mov ecx,dword ptr [edi+4Ch]
    L_0040d7a8:
        mov dword ptr [edi+40h],edx
    L_0040d7ab:
        fld dword ptr [ecx]
    L_0040d7ad:
        fcomp dword ptr [data_00470b68]
    L_0040d7b3:
        pop esi
    L_0040d7b4:
        fnstsw ax
    L_0040d7b6:
        test ah,41h
    L_0040d7b9:
        jne short L_0040d7e0
    L_0040d7bb:
        fld dword ptr [ecx]
    L_0040d7bd:
        fcomp dword ptr [data_00470b64]
    L_0040d7c3:
        fnstsw ax
    L_0040d7c5:
        test ah,5
    L_0040d7c8:
        jp short L_0040d7e0
    L_0040d7ca:
        fld dword ptr [edi+48h]
    L_0040d7cd:
        inc edx
    L_0040d7ce:
        fadd dword ptr [data_00470afc]
    L_0040d7d4:
        mov dword ptr [edi+44h],edx
    L_0040d7d7:
        mov eax,1
    L_0040d7dc:
        fstp dword ptr [edi+48h]
    L_0040d7df:
        ret
    L_0040d7e0:
        fld dword ptr [ecx]
    L_0040d7e2:
        fadd dword ptr [edi+48h]
    L_0040d7e5:
        fst dword ptr [edi+48h]
    L_0040d7e8:
        call asm_FUN_00463b2c_00463b2c
    L_0040d7ed:
        mov dword ptr [edi+44h],eax
    L_0040d7f0:
        mov eax,1
    L_0040d7f5:
        ret
    }
}

// 0x0040DAE0..0x0040DC61: FUN_0040dae0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040dae0_0040dae0() {
    __asm {
    L_0040dae0:
        push ecx
    L_0040dae1:
        mov ecx,dword ptr [data_00477704]
    L_0040dae7:
        push ebx
    L_0040dae8:
        push ebp
    L_0040dae9:
        mov ebp,dword ptr [esp+10h]
    L_0040daed:
        mov dword ptr [ebp],46D0C0h
    L_0040daf4:
        mov edx,dword ptr [ecx+58h]
    L_0040daf7:
        lea eax,[ebp+116Ch]
    L_0040dafd:
        cmp edx,eax
    L_0040daff:
        push esi
    L_0040db00:
        push edi
    L_0040db01:
        jne short L_0040db0c
    L_0040db03:
        mov edx,dword ptr [ebp+1170h]
    L_0040db09:
        mov dword ptr [ecx+58h],edx
    L_0040db0c:
        cmp dword ptr [ecx+5Ch],eax
    L_0040db0f:
        jne short L_0040db1a
    L_0040db11:
        mov edx,dword ptr [ebp+1174h]
    L_0040db17:
        mov dword ptr [ecx+5Ch],edx
    L_0040db1a:
        mov edx,dword ptr [eax+4]
    L_0040db1d:
        xor ebx,ebx
    L_0040db1f:
        cmp edx,ebx
    L_0040db21:
        je short L_0040db29
    L_0040db23:
        mov esi,dword ptr [eax+8]
    L_0040db26:
        mov dword ptr [edx+8],esi
    L_0040db29:
        mov edx,dword ptr [eax+8]
    L_0040db2c:
        cmp edx,ebx
    L_0040db2e:
        je short L_0040db36
    L_0040db30:
        mov esi,dword ptr [eax+4]
    L_0040db33:
        mov dword ptr [edx+4],esi
    L_0040db36:
        mov dword ptr [eax+4],ebx
    L_0040db39:
        mov dword ptr [eax+8],ebx
    L_0040db3c:
        dec dword ptr [ecx+60h]
    L_0040db3f:
        mov eax,dword ptr [ebp+2480h]
    L_0040db45:
        test ah,ah
    L_0040db47:
        jns short L_0040db53
    L_0040db49:
        mov eax,dword ptr [ebp+248Ch]
    L_0040db4f:
        mov dword ptr [ecx+eax*4+10h],ebx
    L_0040db53:
        mov edi,dword ptr [data_00491c10]
    L_0040db59:
        lea edx,[ebp+10FCh]
    L_0040db5f:
        mov dword ptr [esp+10h],0Ah
    L_0040db67:
        mov esi,4000000h
    L_0040db6c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040db70:
        mov ecx,dword ptr [edx]
    L_0040db72:
        cmp ecx,ebx
    L_0040db74:
        je short L_0040dbe5
    L_0040db76:
        mov eax,dword ptr [edi+72DAD4h]
    L_0040db7c:
        cmp eax,ebx
    L_0040db7e:
        je short L_0040db92
    L_0040db80:
        mov ebp,dword ptr [eax]
    L_0040db82:
        cmp dword ptr [ebp],ecx
    L_0040db85:
        je short L_0040dbb0
    L_0040db87:
        mov eax,dword ptr [eax+4]
    L_0040db8a:
        cmp eax,ebx
    L_0040db8c:
        jne short L_0040db80
    L_0040db8e:
        mov ebp,dword ptr [esp+18h]
    L_0040db92:
        mov eax,dword ptr [edi+72DADCh]
    L_0040db98:
        cmp eax,ebx
    L_0040db9a:
        je short L_0040dbe5
    L_0040db9c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040dba0:
        mov ebp,dword ptr [eax]
    L_0040dba2:
        cmp dword ptr [ebp],ecx
    L_0040dba5:
        je short L_0040dbb0
    L_0040dba7:
        mov eax,dword ptr [eax+4]
    L_0040dbaa:
        cmp eax,ebx
    L_0040dbac:
        jne short L_0040dba0
    L_0040dbae:
        jmp short L_0040dbe1
    L_0040dbb0:
        mov eax,dword ptr [eax]
    L_0040dbb2:
        cmp eax,ebx
    L_0040dbb4:
        je short L_0040dbe1
    L_0040dbb6:
        mov ebp,dword ptr [eax+35Ch]
    L_0040dbbc:
        mov ecx,dword ptr [eax+18h]
    L_0040dbbf:
        or ebp,esi
    L_0040dbc1:
        cmp ecx,ebx
    L_0040dbc3:
        mov dword ptr [eax+35Ch],ebp
    L_0040dbc9:
        jne short L_0040dbe1
    L_0040dbcb:
        mov eax,dword ptr [eax+14h]
    L_0040dbce:
        cmp eax,ebx
    L_0040dbd0:
        je short L_0040dbe1
    L_0040dbd2:
        mov ecx,dword ptr [eax]
    L_0040dbd4:
        or dword ptr [ecx+35Ch],esi
    L_0040dbda:
        mov eax,dword ptr [eax+4]
    L_0040dbdd:
        cmp eax,ebx
    L_0040dbdf:
        jne short L_0040dbd2
    L_0040dbe1:
        mov ebp,dword ptr [esp+18h]
    L_0040dbe5:
        mov eax,dword ptr [esp+10h]
    L_0040dbe9:
        mov dword ptr [edx],ebx
    L_0040dbeb:
        add edx,4
    L_0040dbee:
        dec eax
    L_0040dbef:
        mov dword ptr [esp+10h],eax
    L_0040dbf3:
        jne asm_target_0040db70
    L_0040dbf9:
        mov eax,dword ptr [data_00477834]
    L_0040dbfe:
        cmp eax,ebx
    L_0040dc00:
        je short L_0040dc2c
    L_0040dc02:
        cmp dword ptr [eax+3504h],ebp
    L_0040dc08:
        jne short L_0040dc16
    L_0040dc0a:
        mov dword ptr [eax+3504h],ebx
    L_0040dc10:
        mov byte ptr [eax+3508h],bl
    L_0040dc16:
        add eax,4E8h
    L_0040dc1b:
        mov ecx,80h
    L_0040dc20:
        cmp dword ptr [eax],ebp
    L_0040dc22:
        jne short L_0040dc26
    L_0040dc24:
        mov dword ptr [eax],ebx
    L_0040dc26:
        add eax,5Ch
    L_0040dc29:
        dec ecx
    L_0040dc2a:
        jne short L_0040dc20
    L_0040dc2c:
        mov esi,dword ptr [ebp+1034h]
    L_0040dc32:
        cmp esi,ebx
    L_0040dc34:
        mov dword ptr [ebp],46D0D8h
    L_0040dc3b:
        je short L_0040dc5a
    L_0040dc3d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0040dc40:
        mov ecx,dword ptr [esi]
    L_0040dc42:
        mov edi,dword ptr [esi+4]
    L_0040dc45:
        push ecx
    L_0040dc46:
        call asm_free_004524a1
    L_0040dc4b:
        push esi
    L_0040dc4c:
        call asm_free_004524a1
    L_0040dc51:
        add esp,8
    L_0040dc54:
        cmp edi,ebx
    L_0040dc56:
        mov esi,edi
    L_0040dc58:
        jne short L_0040dc40
    L_0040dc5a:
        pop edi
    L_0040dc5b:
        pop esi
    L_0040dc5c:
        pop ebp
    L_0040dc5d:
        pop ebx
    L_0040dc5e:
        pop ecx
    L_0040dc5f:
        ret 4
    }
}

// 0x0040E6A0..0x0040E755: Enemy_DeathSweepRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Enemy_DeathSweepRetail_0040e6a0() {
    __asm {
    L_0040e6a0:
        push ebp
    L_0040e6a1:
        mov ebp,dword ptr [esp+8]
    L_0040e6a5:
        mov eax,dword ptr [ebp+58h]
    L_0040e6a8:
        test eax,eax
    L_0040e6aa:
        je short L_0040e707
    L_0040e6ac:
        push ebx
    L_0040e6ad:
        push esi
    L_0040e6ae:
        push edi
    L_0040e6af:
        nop
    L_0040e6b0:
        mov esi,dword ptr [eax]
    L_0040e6b2:
        mov ebx,dword ptr [eax+4]
    L_0040e6b5:
        mov eax,dword ptr [esi+2480h]
    L_0040e6bb:
        test al,50h
    L_0040e6bd:
        jne short L_0040e6c4
    L_0040e6bf:
        test ah,0C0h
    L_0040e6c2:
        je short L_0040e6c8
    L_0040e6c4:
        test al,al
    L_0040e6c6:
        jns short L_0040e6fe
    L_0040e6c8:
        mov eax,dword ptr [esi+2448h]
    L_0040e6ce:
        test eax,eax
    L_0040e6d0:
        jl short L_0040e6f4
    L_0040e6d2:
        mov ecx,dword ptr [esi+244Ch]
    L_0040e6d8:
        mov edx,dword ptr [data_00477704]
    L_0040e6de:
        push eax
    L_0040e6df:
        lea eax,[esp+18h]
    L_0040e6e3:
        push eax
    L_0040e6e4:
        mov eax,dword ptr [edx+ecx*4+30h]
    L_0040e6e8:
        lea edi,[esi+1068h]
    L_0040e6ee:
        push eax
    L_0040e6ef:
        call asm_PlayerAnimation_Create_00448db0
    L_0040e6f4:
        or dword ptr [esi+2480h],20000h
    L_0040e6fe:
        test ebx,ebx
    L_0040e700:
        mov eax,ebx
    L_0040e702:
        jne short L_0040e6b0
    L_0040e704:
        pop edi
    L_0040e705:
        pop esi
    L_0040e706:
        pop ebx
    L_0040e707:
        mov edx,dword ptr [ebp+44h]
    L_0040e70a:
        mov ecx,dword ptr [ebp+4Ch]
    L_0040e70d:
        mov dword ptr [ebp+40h],edx
    L_0040e710:
        fld dword ptr [ecx]
    L_0040e712:
        fcomp dword ptr [data_00470b68]
    L_0040e718:
        fnstsw ax
    L_0040e71a:
        test ah,41h
    L_0040e71d:
        jne short L_0040e742
    L_0040e71f:
        fld dword ptr [ecx]
    L_0040e721:
        fcomp dword ptr [data_00470b64]
    L_0040e727:
        fnstsw ax
    L_0040e729:
        test ah,5
    L_0040e72c:
        jp short L_0040e742
    L_0040e72e:
        fld dword ptr [ebp+48h]
    L_0040e731:
        inc edx
    L_0040e732:
        fadd dword ptr [data_00470afc]
    L_0040e738:
        mov dword ptr [ebp+44h],edx
    L_0040e73b:
        fstp dword ptr [ebp+48h]
    L_0040e73e:
        pop ebp
    L_0040e73f:
        ret 4
    L_0040e742:
        fld dword ptr [ecx]
    L_0040e744:
        fadd dword ptr [ebp+48h]
    L_0040e747:
        fst dword ptr [ebp+48h]
    L_0040e74a:
        call asm_FUN_00463b2c_00463b2c
    L_0040e74f:
        mov dword ptr [ebp+44h],eax
    L_0040e752:
        pop ebp
    L_0040e753:
        ret 4
    }
}
