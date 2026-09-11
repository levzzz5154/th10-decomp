#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A910..0x0043A9AB: FUN_0043a910
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a910_0043a910() {
    __asm {
    L_0043a910:
        push ebx
    L_0043a911:
        push esi
    L_0043a912:
        mov esi,eax
    L_0043a914:
        push edi
    L_0043a915:
        mov edi,esi
    L_0043a917:
        mov dword ptr [esi],46F80Ch
    L_0043a91d:
        call asm_FUN_0043ae20_0043ae20
    L_0043a922:
        call asm_FUN_0043aa60_0043aa60
    L_0043a927:
        lea ebx,[esi+98h]
    L_0043a92d:
        mov edi,20h
    L_0043a932:
        mov eax,dword ptr [ebx]
    L_0043a934:
        test eax,eax
    L_0043a936:
        je short L_0043a947
    L_0043a938:
        push eax
    L_0043a939:
        call asm_free_00452422
    L_0043a93e:
        add esp,4
    L_0043a941:
        mov dword ptr [ebx],0
    L_0043a947:
        mov dword ptr [ebx],0
    L_0043a94d:
        add ebx,4
    L_0043a950:
        dec edi
    L_0043a951:
        jne short L_0043a932
    L_0043a953:
        mov eax,dword ptr [esi+13Ch]
    L_0043a959:
        test eax,eax
    L_0043a95b:
        je short L_0043a97b
    L_0043a95d:
        push eax
    L_0043a95e:
        call dword ptr [data_004662a8]
    L_0043a964:
        mov eax,dword ptr [esi+13Ch]
    L_0043a96a:
        push eax
    L_0043a96b:
        call dword ptr [data_004662a4]
    L_0043a971:
        mov dword ptr [esi+13Ch],0
    L_0043a97b:
        mov eax,dword ptr [esi+4]
    L_0043a97e:
        test eax,eax
    L_0043a980:
        mov dword ptr [esi],46F810h
    L_0043a986:
        je short L_0043a98f
    L_0043a988:
        push eax
    L_0043a989:
        call dword ptr [data_00466288]
    L_0043a98f:
        mov ecx,dword ptr [esi+8]
    L_0043a992:
        mov edi,dword ptr [data_00466274]
    L_0043a998:
        push ecx
    L_0043a999:
        call edi
    L_0043a99b:
        mov edx,dword ptr [esi+8]
    L_0043a99e:
        push edx
    L_0043a99f:
        mov dword ptr [esi+4],0
    L_0043a9a6:
        call edi
    L_0043a9a8:
        pop edi
    L_0043a9a9:
        pop esi
    L_0043a9aa:
        pop ebx
    L_0043a9ab:
        ret
    }
}

// 0x0043D120..0x0043D24C: FUN_0043d120
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d120_0043d120() {
    __asm {
    L_0043d120:
        push ebp
    L_0043d121:
        push esi
    L_0043d122:
        mov esi,eax
    L_0043d124:
        mov eax,dword ptr [esi+1F84h]
    L_0043d12a:
        xor ebp,ebp
    L_0043d12c:
        cmp eax,ebp
    L_0043d12e:
        push edi
    L_0043d12f:
        je short L_0043d140
    L_0043d131:
        push eax
    L_0043d132:
        call asm_free_00452422
    L_0043d137:
        add esp,4
    L_0043d13a:
        mov dword ptr [esi+1F84h],ebp
    L_0043d140:
        push ebx
    L_0043d141:
        lea edi,[esi+8]
    L_0043d144:
        mov ebx,80h
    L_0043d149:
        lea esp,[esp+force_disp32_zero]
    L_0043d150:
        mov eax,dword ptr [edi+200h]
    L_0043d156:
        cmp eax,ebp
    L_0043d158:
        je short L_0043d166
    L_0043d15a:
        mov ecx,dword ptr [eax]
    L_0043d15c:
        push eax
    L_0043d15d:
        call dword ptr [ecx+8]
    L_0043d160:
        mov dword ptr [edi+200h],ebp
    L_0043d166:
        mov eax,dword ptr [edi]
    L_0043d168:
        cmp eax,ebp
    L_0043d16a:
        je short L_0043d174
    L_0043d16c:
        mov edx,dword ptr [eax]
    L_0043d16e:
        push eax
    L_0043d16f:
        call dword ptr [edx+8]
    L_0043d172:
        mov dword ptr [edi],ebp
    L_0043d174:
        add edi,4
    L_0043d177:
        dec ebx
    L_0043d178:
        jne short L_0043d150
    L_0043d17a:
        lea edi,[esi+5230h]
    L_0043d180:
        mov ebx,25h
    L_0043d185:
        mov eax,dword ptr [edi]
    L_0043d187:
        cmp eax,ebp
    L_0043d189:
        je short L_0043d196
    L_0043d18b:
        push eax
    L_0043d18c:
        call asm_free_00452422
    L_0043d191:
        add esp,4
    L_0043d194:
        mov dword ptr [edi],ebp
    L_0043d196:
        add edi,4
    L_0043d199:
        dec ebx
    L_0043d19a:
        jne short L_0043d185
    L_0043d19c:
        cmp dword ptr [esi+610h],ebp
    L_0043d1a2:
        pop ebx
    L_0043d1a3:
        je asm_target_0043d247
    L_0043d1a9:
        mov eax,dword ptr [esi+60Ch]
    L_0043d1af:
        push 1
    L_0043d1b1:
        push eax
    L_0043d1b2:
        call dword ptr [data_00466214]
    L_0043d1b8:
        call asm_MidiWorker_StopRetail_0043dab0
    L_0043d1bd:
        mov eax,dword ptr [esi+608h]
    L_0043d1c3:
        mov dword ptr [esi],ebp
    L_0043d1c5:
        mov ecx,dword ptr [eax]
    L_0043d1c7:
        push eax
    L_0043d1c8:
        call dword ptr [ecx+48h]
    L_0043d1cb:
        mov eax,dword ptr [esi+608h]
    L_0043d1d1:
        cmp eax,ebp
    L_0043d1d3:
        je short L_0043d1e1
    L_0043d1d5:
        mov edx,dword ptr [eax]
    L_0043d1d7:
        push eax
    L_0043d1d8:
        call dword ptr [edx+8]
    L_0043d1db:
        mov dword ptr [esi+608h],ebp
    L_0043d1e1:
        mov ecx,dword ptr [esi+5208h]
    L_0043d1e7:
        cmp ecx,ebp
    L_0043d1e9:
        je short L_0043d1f7
    L_0043d1eb:
        mov eax,dword ptr [ecx]
    L_0043d1ed:
        push 1
    L_0043d1ef:
        call dword ptr [eax]
    L_0043d1f1:
        mov dword ptr [esi+5208h],ebp
    L_0043d1f7:
        mov edi,dword ptr [esi+610h]
    L_0043d1fd:
        cmp edi,ebp
    L_0043d1ff:
        je short L_0043d21e
    L_0043d201:
        mov eax,dword ptr [edi]
    L_0043d203:
        cmp eax,ebp
    L_0043d205:
        je short L_0043d20f
    L_0043d207:
        mov ecx,dword ptr [eax]
    L_0043d209:
        push eax
    L_0043d20a:
        call dword ptr [ecx+8]
    L_0043d20d:
        mov dword ptr [edi],ebp
    L_0043d20f:
        push edi
    L_0043d210:
        call asm_free_004524a1
    L_0043d215:
        add esp,4
    L_0043d218:
        mov dword ptr [esi+610h],ebp
    L_0043d21e:
        add esi,1EC0h
    L_0043d224:
        mov edi,10h
    L_0043d229:
        lea esp,[esp+force_disp32_zero]
    L_0043d230:
        mov eax,dword ptr [esi]
    L_0043d232:
        cmp eax,ebp
    L_0043d234:
        je short L_0043d241
    L_0043d236:
        push eax
    L_0043d237:
        call asm_free_00452422
    L_0043d23c:
        add esp,4
    L_0043d23f:
        mov dword ptr [esi],ebp
    L_0043d241:
        add esi,4
    L_0043d244:
        dec edi
    L_0043d245:
        jne short L_0043d230
    L_0043d247:
        pop edi
    L_0043d248:
        pop esi
    L_0043d249:
        xor eax,eax
    L_0043d24b:
        pop ebp
    L_0043d24c:
        ret
    }
}

// 0x0043D7D0..0x0043D940: FUN_0043d7d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d7d0_0043d7d0() {
    __asm {
    L_0043d7d0:
        push ecx
    L_0043d7d1:
        push ebx
    L_0043d7d2:
        push ebp
    L_0043d7d3:
        mov ebp,dword ptr [esp+10h]
    L_0043d7d7:
        mov ebx,eax
    L_0043d7d9:
        mov eax,dword ptr [esi+ebp*4+1EC0h]
    L_0043d7e0:
        test eax,eax
    L_0043d7e2:
        push edi
    L_0043d7e3:
        je short L_0043d824
    L_0043d7e5:
        mov eax,ebp
    L_0043d7e7:
        shl eax,8
    L_0043d7ea:
        lea edi,[eax+esi+4108h]
    L_0043d7f1:
        mov eax,ebx
    L_0043d7f3:
        mov dl,byte ptr [eax]
    L_0043d7f5:
        mov cl,dl
    L_0043d7f7:
        cmp dl,byte ptr [edi]
    L_0043d7f9:
        jne short L_0043d817
    L_0043d7fb:
        test cl,cl
    L_0043d7fd:
        je short L_0043d813
    L_0043d7ff:
        mov dl,byte ptr [eax+1]
    L_0043d802:
        mov cl,dl
    L_0043d804:
        cmp dl,byte ptr [edi+1]
    L_0043d807:
        jne short L_0043d817
    L_0043d809:
        add eax,2
    L_0043d80c:
        add edi,2
    L_0043d80f:
        test cl,cl
    L_0043d811:
        jne short L_0043d7f3
    L_0043d813:
        xor eax,eax
    L_0043d815:
        jmp short L_0043d81c
    L_0043d817:
        sbb eax,eax
    L_0043d819:
        sbb eax,0FFFFFFFFh
    L_0043d81c:
        test eax,eax
    L_0043d81e:
        je asm_target_0043d938
    L_0043d824:
        mov ecx,ebp
    L_0043d826:
        shl ecx,8
    L_0043d829:
        lea edx,[ecx+496698h]
    L_0043d82f:
        mov eax,ebx
    L_0043d831:
        sub edx,ebx
    L_0043d833:
        mov cl,byte ptr [eax]
    L_0043d835:
        mov byte ptr [edx+eax],cl
    L_0043d838:
        inc eax
    L_0043d839:
        test cl,cl
    L_0043d83b:
        jne short L_0043d833
    L_0043d83d:
        test byte ptr [data_00491d78],10h
    L_0043d844:
        je asm_target_0043d938
    L_0043d84a:
        mov eax,dword ptr [esi+610h]
    L_0043d850:
        test eax,eax
    L_0043d852:
        je asm_target_0043d938
    L_0043d858:
        mov eax,dword ptr [esi+ebp*4+1EC0h]
    L_0043d85f:
        test eax,eax
    L_0043d861:
        je short L_0043d877
    L_0043d863:
        push eax
    L_0043d864:
        call asm_free_00452422
    L_0043d869:
        add esp,4
    L_0043d86c:
        mov dword ptr [esi+ebp*4+1EC0h],0
    L_0043d877:
        push 0
    L_0043d879:
        push 8000080h
    L_0043d87e:
        push 3
    L_0043d880:
        push 0
    L_0043d882:
        push 1
    L_0043d884:
        push 80000000h
    L_0043d889:
        lea edx,[esi+5108h]
    L_0043d88f:
        push edx
    L_0043d890:
        call dword ptr [data_004660c4]
    L_0043d896:
        mov ebp,eax
    L_0043d898:
        cmp ebp,0FFFFFFFFh
    L_0043d89b:
        je short L_0043d8e0
    L_0043d89d:
        push esi
    L_0043d89e:
        mov ecx,ebx
    L_0043d8a0:
        call asm_Path_FindBasenameSlot_0043d2a0
    L_0043d8a5:
        mov edi,eax
    L_0043d8a7:
        mov eax,dword ptr [esi+1F84h]
    L_0043d8ad:
        imul edi,34h
    L_0043d8b0:
        mov ecx,dword ptr [eax+edi+10h]
    L_0043d8b4:
        push 0
    L_0043d8b6:
        push 0
    L_0043d8b8:
        push ecx
    L_0043d8b9:
        push ebp
    L_0043d8ba:
        call dword ptr [data_004660c8]
    L_0043d8c0:
        mov edx,dword ptr [esi+1F84h]
    L_0043d8c6:
        mov eax,dword ptr [edx+edi+14h]
    L_0043d8ca:
        push eax
    L_0043d8cb:
        call asm_malloc_00452706
    L_0043d8d0:
        mov ebx,eax
    L_0043d8d2:
        add esp,4
    L_0043d8d5:
        test ebx,ebx
    L_0043d8d7:
        jne short L_0043d8ea
    L_0043d8d9:
        push ebp
    L_0043d8da:
        call dword ptr [data_004660cc]
    L_0043d8e0:
        pop edi
    L_0043d8e1:
        pop ebp
    L_0043d8e2:
        or eax,0FFFFFFFFh
    L_0043d8e5:
        pop ebx
    L_0043d8e6:
        pop ecx
    L_0043d8e7:
        ret 4
    L_0043d8ea:
        mov ecx,dword ptr [esi+1F84h]
    L_0043d8f0:
        mov edx,dword ptr [ecx+edi+14h]
    L_0043d8f4:
        push 0
    L_0043d8f6:
        lea eax,[esp+10h]
    L_0043d8fa:
        push eax
    L_0043d8fb:
        push edx
    L_0043d8fc:
        push ebx
    L_0043d8fd:
        push ebp
    L_0043d8fe:
        call dword ptr [data_004660d0]
    L_0043d904:
        push ebp
    L_0043d905:
        call dword ptr [data_004660cc]
    L_0043d90b:
        mov ecx,dword ptr [esi+1F84h]
    L_0043d911:
        mov eax,dword ptr [esp+14h]
    L_0043d915:
        add ecx,edi
    L_0043d917:
        mov edx,ecx
    L_0043d919:
        mov dword ptr [esi+eax*4+1E80h],ecx
    L_0043d920:
        mov dword ptr [esi+eax*4+1EC0h],ebx
    L_0043d927:
        mov dword ptr [esi+eax*4+1F00h],ebx
    L_0043d92e:
        mov ecx,dword ptr [edx+14h]
    L_0043d931:
        mov dword ptr [esi+eax*4+1F40h],ecx
    L_0043d938:
        pop edi
    L_0043d939:
        pop ebp
    L_0043d93a:
        xor eax,eax
    L_0043d93c:
        pop ebx
    L_0043d93d:
        pop ecx
    L_0043d93e:
        ret 4
    }
}

// 0x0043D950..0x0043DA79: FUN_0043d950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d950_0043d950() {
    __asm {
    L_0043d950:
        push ebx
    L_0043d951:
        mov ebx,eax
    L_0043d953:
        mov eax,dword ptr [esi+610h]
    L_0043d959:
        test eax,eax
    L_0043d95b:
        push ebp
    L_0043d95c:
        push edi
    L_0043d95d:
        je asm_target_0043da67
    L_0043d963:
        mov al,byte ptr [data_00491d63]
    L_0043d968:
        test al,al
    L_0043d96a:
        jne short L_0043d975
    L_0043d96c:
        mov eax,0FFFFFFFFh
    L_0043d971:
        pop edi
    L_0043d972:
        pop ebp
    L_0043d973:
        pop ebx
    L_0043d974:
        ret
    L_0043d975:
        cmp dword ptr [esi],0
    L_0043d978:
        je asm_target_0043da67
    L_0043d97e:
        test byte ptr [data_00491d78],10h
    L_0043d985:
        jne short L_0043d99b
    L_0043d987:
        shl ebx,8
    L_0043d98a:
        lea ecx,[ebx+esi+4108h]
    L_0043d991:
        mov eax,esi
    L_0043d993:
        pop edi
    L_0043d994:
        pop ebp
    L_0043d995:
        pop ebx
    L_0043d996:
        jmp asm_Recovery_SelectArchiveEntry_0043d790
    L_0043d99b:
        mov eax,dword ptr [esi+ebx*4+1EC0h]
    L_0043d9a2:
        test eax,eax
    L_0043d9a4:
        je asm_target_0043da67
    L_0043d9aa:
        mov eax,dword ptr [esi+ebx*4+1E80h]
    L_0043d9b1:
        movzx ebp,word ptr [eax+2Ch]
    L_0043d9b5:
        mov edi,dword ptr [eax+24h]
    L_0043d9b8:
        imul edi,ebp
    L_0043d9bb:
        push 0
    L_0043d9bd:
        push 0
    L_0043d9bf:
        push 0
    L_0043d9c1:
        shl edi,2
    L_0043d9c4:
        push 0
    L_0043d9c6:
        shr edi,4
    L_0043d9c9:
        call dword ptr [data_00466120]
    L_0043d9cf:
        mov dword ptr [esi+520Ch],eax
    L_0043d9d5:
        mov ecx,dword ptr [data_00491c70]
    L_0043d9db:
        lea eax,[esi+614h]
    L_0043d9e1:
        push eax
    L_0043d9e2:
        push 0
    L_0043d9e4:
        push ecx
    L_0043d9e5:
        push 43E3A0h
    L_0043d9ea:
        push 0
    L_0043d9ec:
        push 0
    L_0043d9ee:
        call dword ptr [data_00466118]
    L_0043d9f4:
        mov edx,dword ptr [esi+520Ch]
    L_0043d9fa:
        push edx
    L_0043d9fb:
        mov dword ptr [esi+618h],eax
    L_0043da01:
        xor edx,edx
    L_0043da03:
        mov eax,edi
    L_0043da05:
        div ebp
    L_0043da07:
        mov ecx,dword ptr [data_0046a67c]
    L_0043da0d:
        sub edi,edx
    L_0043da0f:
        mov edx,dword ptr [data_0046a680]
    L_0043da15:
        push edi
    L_0043da16:
        push 10h
    L_0043da18:
        sub esp,10h
    L_0043da1b:
        mov eax,esp
    L_0043da1d:
        mov dword ptr [eax],ecx
    L_0043da1f:
        mov ecx,dword ptr [data_0046a684]
    L_0043da25:
        mov dword ptr [eax+4],edx
    L_0043da28:
        mov edx,dword ptr [data_0046a688]
    L_0043da2e:
        mov dword ptr [eax+8],ecx
    L_0043da31:
        mov ecx,dword ptr [esi+ebx*4+1F40h]
    L_0043da38:
        mov dword ptr [eax+0Ch],edx
    L_0043da3b:
        mov eax,dword ptr [esi+ebx*4+1E80h]
    L_0043da42:
        mov edx,dword ptr [esi+ebx*4+1F00h]
    L_0043da49:
        push eax
    L_0043da4a:
        mov eax,dword ptr [esi+610h]
    L_0043da50:
        push ecx
    L_0043da51:
        push edx
    L_0043da52:
        lea ecx,[esi+5208h]
    L_0043da58:
        push eax
    L_0043da59:
        mov edx,10100h
    L_0043da5e:
        call asm_FUN_0044cbf0_0044cbf0
    L_0043da63:
        test eax,eax
    L_0043da65:
        jge short L_0043da6e
    L_0043da67:
        or eax,0FFFFFFFFh
    L_0043da6a:
        pop edi
    L_0043da6b:
        pop ebp
    L_0043da6c:
        pop ebx
    L_0043da6d:
        ret
    L_0043da6e:
        pop edi
    L_0043da6f:
        pop ebp
    L_0043da70:
        mov dword ptr [esi+1F80h],ebx
    L_0043da76:
        xor eax,eax
    L_0043da78:
        pop ebx
    L_0043da79:
        ret
    }
}

// 0x0043DDF0..0x0043DE24: FUN_0043ddf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ddf0_0043ddf0() {
    __asm {
    L_0043ddf0:
        sub esp,0Ch
    L_0043ddf3:
        push ebp
    L_0043ddf4:
        mov ebp,dword ptr [esp+14h]
    L_0043ddf8:
        mov eax,dword ptr [ebp+610h]
    L_0043ddfe:
        test eax,eax
    L_0043de00:
        jne short L_0043de0b
    L_0043de02:
        xor eax,eax
    L_0043de04:
        pop ebp
    L_0043de05:
        add esp,0Ch
    L_0043de08:
        ret 4
    L_0043de0b:
        push ebx
    L_0043de0c:
        push edi
    L_0043de0d:
        lea ebx,[ebp+1F88h]
    L_0043de13:
        mov dword ptr [esp+10h],ebx
    L_0043de17:
        push esi
    L_0043de18:
        mov eax,dword ptr [ebx]
    L_0043de1a:
        dec eax
    L_0043de1b:
        cmp eax,7
    L_0043de1e:
        mov edi,1
    L_0043de23:
        TH10_REL8(0xeb, 0x0043de23, VA_asm_FUN_0043ddf0_part_0043de30)
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

    L_0043de30:
        mov dword ptr [esp+20h],0
    L_0043de38:
        ja asm_target_0043e212
    L_0043de3e:
        jmp dword ptr [eax*4+43E37Ch]
    L_0043de45:
        mov eax,dword ptr [ebp+5208h]
    L_0043de4b:
        test eax,eax
    L_0043de4d:
        je asm_target_0043e0e5
    L_0043de53:
        mov ecx,dword ptr [ebp+52C4h]
    L_0043de59:
        push ecx
    L_0043de5a:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_0043de5f:
        jmp asm_target_0043e0e5
    L_0043de64:
        test byte ptr [data_00491d78],10h
    L_0043de6b:
        je short L_0043de94
    L_0043de6d:
        mov eax,dword ptr [ebx+8]
    L_0043de70:
        test eax,eax
    L_0043de72:
        jne asm_target_0043e20f
    L_0043de78:
        mov esi,ebp
    L_0043de7a:
        call asm_MidiWorker_StopRetail_0043dab0
    L_0043de7f:
        mov edx,dword ptr [ebx+4]
    L_0043de82:
        lea eax,[ebx+0Ch]
    L_0043de85:
        push edx
    L_0043de86:
        call asm_FUN_0043d7d0_0043d7d0
    L_0043de8b:
        mov dword ptr [esp+20h],edi
    L_0043de8f:
        jmp asm_target_0043e0e5
    L_0043de94:
        mov ecx,dword ptr [ebx+4]
    L_0043de97:
        lea eax,[ebx+0Ch]
    L_0043de9a:
        push ecx
    L_0043de9b:
        mov esi,ebp
    L_0043de9d:
        call asm_FUN_0043d7d0_0043d7d0
    L_0043dea2:
        mov dword ptr [esp+20h],edi
    L_0043dea6:
        jmp asm_target_0043e0e5
    L_0043deab:
        test byte ptr [data_00491d78],10h
    L_0043deb2:
        je asm_target_0043df6b
    L_0043deb8:
        mov eax,dword ptr [ebx+4]
    L_0043debb:
        test eax,eax
    L_0043debd:
        jl asm_target_0043df6b
    L_0043dec3:
        mov ecx,dword ptr [ebx+8]
    L_0043dec6:
        test ecx,ecx
    L_0043dec8:
        jne short L_0043dede
    L_0043deca:
        mov esi,ebp
    L_0043decc:
        call asm_FUN_0043d950_0043d950
    L_0043ded1:
        test eax,eax
    L_0043ded3:
        je asm_target_0043e20f
    L_0043ded9:
        jmp asm_target_0043e0e5
    L_0043dede:
        cmp ecx,2
    L_0043dee1:
        jne short L_0043df03
    L_0043dee3:
        mov edi,dword ptr [ebp+5208h]
    L_0043dee9:
        test edi,edi
    L_0043deeb:
        je asm_target_0043e20f
    L_0043def1:
        call asm_Streamer_RestartRetail_0044dad0
    L_0043def6:
        test eax,eax
    L_0043def8:
        jge asm_target_0043e20f
    L_0043defe:
        jmp asm_target_0043e0e5
    L_0043df03:
        cmp ecx,5
    L_0043df06:
        jne short L_0043df54
    L_0043df08:
        mov eax,dword ptr [ebp+5208h]
    L_0043df0e:
        mov ecx,dword ptr [eax+4]
    L_0043df11:
        test ecx,ecx
    L_0043df13:
        je short L_0043df22
    L_0043df15:
        mov edx,dword ptr [eax+10h]
    L_0043df18:
        test edx,edx
    L_0043df1a:
        ja short L_0043df20
    L_0043df1c:
        xor ecx,ecx
    L_0043df1e:
        jmp short L_0043df22
    L_0043df20:
        mov ecx,dword ptr [ecx]
    L_0043df22:
        mov edx,dword ptr [eax+0Ch]
    L_0043df25:
        mov eax,dword ptr [edx+90h]
    L_0043df2b:
        mov edi,dword ptr [eax+1Ch]
    L_0043df2e:
        xor edx,edx
    L_0043df30:
        test edi,edi
    L_0043df32:
        setne dl
    L_0043df35:
        mov eax,edx
    L_0043df37:
        push eax
    L_0043df38:
        push ecx
    L_0043df39:
        mov dword ptr [ebx+4],eax
    L_0043df3c:
        mov eax,dword ptr [ebp+5208h]
    L_0043df42:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0043df47:
        test eax,eax
    L_0043df49:
        jge asm_target_0043e20f
    L_0043df4f:
        jmp asm_target_0043e0e5
    L_0043df54:
        cmp ecx,7
    L_0043df57:
        je asm_target_0043e17a
    L_0043df5d:
        cmp ecx,14h
    L_0043df60:
        jl asm_target_0043e20f
    L_0043df66:
        jmp asm_target_0043e0e5
    L_0043df6b:
        mov ecx,dword ptr [ebp+5208h]
    L_0043df71:
        test ecx,ecx
    L_0043df73:
        je asm_target_0043e0e5
    L_0043df79:
        mov eax,dword ptr [ebx+8]
    L_0043df7c:
        test eax,eax
    L_0043df7e:
        je asm_target_0043e204
    L_0043df84:
        cmp eax,edi
    L_0043df86:
        je asm_target_0043e123
    L_0043df8c:
        cmp eax,2
    L_0043df8f:
        je asm_target_0043e13e
    L_0043df95:
        cmp eax,3
    L_0043df98:
        jne short L_0043dfd9
    L_0043df9a:
        mov eax,dword ptr [ecx+4]
    L_0043df9d:
        test eax,eax
    L_0043df9f:
        jne short L_0043dfa5
    L_0043dfa1:
        xor esi,esi
    L_0043dfa3:
        jmp short L_0043dfb2
    L_0043dfa5:
        mov edx,dword ptr [ecx+10h]
    L_0043dfa8:
        test edx,edx
    L_0043dfaa:
        ja short L_0043dfb0
    L_0043dfac:
        xor esi,esi
    L_0043dfae:
        jmp short L_0043dfb2
    L_0043dfb0:
        mov esi,dword ptr [eax]
    L_0043dfb2:
        mov edi,ecx
    L_0043dfb4:
        call asm_Streamer_RestartRetail_0044dad0
    L_0043dfb9:
        mov eax,dword ptr [ebp+5208h]
    L_0043dfbf:
        mov ecx,dword ptr [eax+0Ch]
    L_0043dfc2:
        mov edx,dword ptr [ecx+90h]
    L_0043dfc8:
        mov ecx,dword ptr [edx+1Ch]
    L_0043dfcb:
        xor eax,eax
    L_0043dfcd:
        test ecx,ecx
    L_0043dfcf:
        setne al
    L_0043dfd2:
        push eax
    L_0043dfd3:
        push esi
    L_0043dfd4:
        jmp asm_target_0043df39
    L_0043dfd9:
        cmp eax,4
    L_0043dfdc:
        je asm_target_0043e17a
    L_0043dfe2:
        cmp eax,7
    L_0043dfe5:
        jl asm_target_0043e20f
    L_0043dfeb:
        jmp asm_target_0043e0e5
    L_0043dff0:
        mov eax,dword ptr [ebp+5208h]
    L_0043dff6:
        test eax,eax
    L_0043dff8:
        je asm_target_0043e0e5
    L_0043dffe:
        mov eax,dword ptr [ebx+8]
    L_0043e001:
        test eax,eax
    L_0043e003:
        je asm_target_0043e204
    L_0043e009:
        cmp eax,edi
    L_0043e00b:
        jne short L_0043e033
    L_0043e00d:
        mov eax,dword ptr [ebp+618h]
    L_0043e013:
        test eax,eax
    L_0043e015:
        je asm_target_0043e0e5
    L_0043e01b:
        mov ecx,dword ptr [ebp+614h]
    L_0043e021:
        push 0
    L_0043e023:
        push 0
    L_0043e025:
        push 12h
    L_0043e027:
        push ecx
    L_0043e028:
        call dword ptr [data_00466210]
    L_0043e02e:
        jmp asm_target_0043e20f
    L_0043e033:
        cmp eax,2
    L_0043e036:
        je asm_target_0043e18d
    L_0043e03c:
        cmp eax,3
    L_0043e03f:
        je asm_target_0043e1c7
    L_0043e045:
        cmp eax,0Ah
    L_0043e048:
        jne asm_target_0043e20f
    L_0043e04e:
        jmp asm_target_0043e0e5
    L_0043e053:
        mov eax,dword ptr [ebp+5208h]
    L_0043e059:
        test eax,eax
    L_0043e05b:
        je asm_target_0043e0e5
    L_0043e061:
        mov eax,dword ptr [ebx+8]
    L_0043e064:
        test eax,eax
    L_0043e066:
        je asm_target_0043e204
    L_0043e06c:
        cmp eax,edi
    L_0043e06e:
        jne asm_target_0043e20f
    L_0043e074:
        jmp short L_0043e0e5
    L_0043e076:
        mov esi,dword ptr [data_00497798]
    L_0043e07c:
        fild dword ptr [ebx+4]
    L_0043e07f:
        test esi,esi
    L_0043e081:
        je short L_0043e0e3
    L_0043e083:
        fmul dword ptr [data_00470b1c]
    L_0043e089:
        mov dword ptr [esi+1Ch],edi
    L_0043e08c:
        call asm_FUN_00463b2c_00463b2c
    L_0043e091:
        mov dword ptr [esi+14h],eax
    L_0043e094:
        mov dword ptr [esi+18h],eax
    L_0043e097:
        jmp short L_0043e0e5
    L_0043e099:
        cmp byte ptr [data_00491d63],1
    L_0043e0a0:
        jne short L_0043e0e5
    L_0043e0a2:
        mov ecx,dword ptr [ebp+5208h]
    L_0043e0a8:
        mov eax,dword ptr [ecx+74h]
    L_0043e0ab:
        test eax,eax
    L_0043e0ad:
        jne asm_target_0043e212
    L_0043e0b3:
        test ecx,ecx
    L_0043e0b5:
        je short L_0043e0e5
    L_0043e0b7:
        call asm_Platform_InvokeInterface_0044d5b0
    L_0043e0bc:
        jmp short L_0043e0e5
    L_0043e0be:
        cmp byte ptr [data_00491d63],1
    L_0043e0c5:
        jne short L_0043e0e5
    L_0043e0c7:
        mov eax,dword ptr [ebp+5208h]
    L_0043e0cd:
        mov ecx,dword ptr [eax+74h]
    L_0043e0d0:
        test ecx,ecx
    L_0043e0d2:
        jne asm_target_0043e212
    L_0043e0d8:
        test eax,eax
    L_0043e0da:
        je short L_0043e0e5
    L_0043e0dc:
        call asm_Platform_InvokeConfigured_0044d5d0
    L_0043e0e1:
        jmp short L_0043e0e5
    L_0043e0e3:
        fstp st(0)
    L_0043e0e5:
        xor eax,eax
    L_0043e0e7:
        lea edx,[ebx+10Ch]
    L_0043e0ed:
        TH10_NOP_LEA_ECX_DISP8()
    L_0043e0f0:
        cmp dword ptr [ebx],0
    L_0043e0f3:
        je short L_0043e112
    L_0043e0f5:
        mov esi,edx
    L_0043e0f7:
        mov edi,ebx
    L_0043e0f9:
        inc eax
    L_0043e0fa:
        mov ecx,43h
    L_0043e0ff:
        add ebx,10Ch
    L_0043e105:
        add edx,10Ch
    L_0043e10b:
        cmp eax,1Fh
    L_0043e10e:
        rep movsd
    L_0043e110:
        jl short L_0043e0f0
    L_0043e112:
        mov eax,dword ptr [esp+20h]
    L_0043e116:
        test eax,eax
    L_0043e118:
        je asm_target_0043e212
    L_0043e11e:
        jmp asm_target_0043de18
    L_0043e123:
        mov esi,dword ptr [ebp+5208h]
    L_0043e129:
        mov eax,dword ptr [esi+74h]
    L_0043e12c:
        test eax,eax
    L_0043e12e:
        jne asm_target_0043e212
    L_0043e134:
        call asm_FUN_0044cf20_0044cf20
    L_0043e139:
        jmp asm_target_0043e20f
    L_0043e13e:
        mov eax,dword ptr [ebx+4]
    L_0043e141:
        test eax,eax
    L_0043e143:
        jl short L_0043e151
    L_0043e145:
        shl eax,8
    L_0043e148:
        lea ecx,[eax+ebp+4108h]
    L_0043e14f:
        jmp short L_0043e154
    L_0043e151:
        lea ecx,[ebx+0Ch]
    L_0043e154:
        push ebp
    L_0043e155:
        call asm_Path_FindBasenameSlot_0043d2a0
    L_0043e15a:
        mov ecx,eax
    L_0043e15c:
        mov eax,dword ptr [ebp+1F84h]
    L_0043e162:
        imul ecx,34h
    L_0043e165:
        add ecx,eax
    L_0043e167:
        mov eax,dword ptr [ebp+5208h]
    L_0043e16d:
        mov esi,dword ptr [eax+0Ch]
    L_0043e170:
        call asm_Platform_SelectStreamRecord_0044dca0
    L_0043e175:
        jmp asm_target_0043e20f
    L_0043e17a:
        mov eax,dword ptr [ebp+5208h]
    L_0043e180:
        push edi
    L_0043e181:
        push 0
    L_0043e183:
        call asm_SoundStream_Start_0044d440
    L_0043e188:
        jmp asm_target_0043e20f
    L_0043e18d:
        mov edx,dword ptr [ebp+618h]
    L_0043e193:
        push 100h
    L_0043e198:
        push edx
    L_0043e199:
        call dword ptr [data_0046611c]
    L_0043e19f:
        test eax,eax
    L_0043e1a1:
        je short L_0043e1bb
    L_0043e1a3:
        mov eax,dword ptr [ebp+614h]
    L_0043e1a9:
        push 0
    L_0043e1ab:
        push 0
    L_0043e1ad:
        push 12h
    L_0043e1af:
        push eax
    L_0043e1b0:
        call dword ptr [data_00466210]
    L_0043e1b6:
        dec dword ptr [ebx+8]
    L_0043e1b9:
        jmp short L_0043e20f
    L_0043e1bb:
        mov dword ptr [ebp+618h],0
    L_0043e1c5:
        jmp short L_0043e20f
    L_0043e1c7:
        mov ecx,dword ptr [ebp+618h]
    L_0043e1cd:
        mov esi,dword ptr [data_004660cc]
    L_0043e1d3:
        push ecx
    L_0043e1d4:
        call esi
    L_0043e1d6:
        mov edx,dword ptr [ebp+520Ch]
    L_0043e1dc:
        push edx
    L_0043e1dd:
        call esi
    L_0043e1df:
        mov ecx,dword ptr [ebp+5208h]
    L_0043e1e5:
        xor esi,esi
    L_0043e1e7:
        cmp ecx,esi
    L_0043e1e9:
        mov dword ptr [ebp+618h],esi
    L_0043e1ef:
        je short L_0043e1fc
    L_0043e1f1:
        mov eax,dword ptr [ecx]
    L_0043e1f3:
        push edi
    L_0043e1f4:
        call dword ptr [eax]
    L_0043e1f6:
        mov dword ptr [ebp+5208h],esi
    L_0043e1fc:
        mov dword ptr [ebp+5208h],esi
    L_0043e202:
        jmp short L_0043e20f
    L_0043e204:
        mov edi,dword ptr [ebp+5208h]
    L_0043e20a:
        call asm_Platform_AggregateInterfaces_0044d550
    L_0043e20f:
        inc dword ptr [ebx+8]
    L_0043e212:
        mov al,byte ptr [data_00491d64]
    L_0043e217:
        test al,al
    L_0043e219:
        jne short L_0043e22b
    L_0043e21b:
        mov ecx,dword ptr [esp+14h]
    L_0043e21f:
        mov eax,dword ptr [ecx]
    L_0043e221:
        pop esi
    L_0043e222:
        pop edi
    L_0043e223:
        pop ebx
    L_0043e224:
        pop ebp
    L_0043e225:
        add esp,0Ch
    L_0043e228:
        ret 4
    L_0043e22b:
        lea edx,[ebp+680h]
    L_0043e231:
        mov dword ptr [esp+10h],0
    L_0043e239:
        lea ebx,[ebp+650h]
    L_0043e23f:
        mov dword ptr [esp+20h],edx
    L_0043e243:
        mov esi,dword ptr [ebx-30h]
    L_0043e246:
        test esi,esi
    L_0043e248:
        jl asm_target_0043e36b
    L_0043e24e:
        mov edi,dword ptr [ebx]
    L_0043e250:
        test edi,edi
    L_0043e252:
        mov dword ptr [ebx-30h],0FFFFFFFFh
    L_0043e259:
        jge short L_0043e279
    L_0043e25b:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e262:
        test eax,eax
    L_0043e264:
        je short L_0043e26e
    L_0043e266:
        mov esi,eax
    L_0043e268:
        mov eax,dword ptr [esi]
    L_0043e26a:
        push esi
    L_0043e26b:
        call dword ptr [eax+48h]
    L_0043e26e:
        mov dword ptr [ebx],0
    L_0043e274:
        jmp asm_target_0043e348
    L_0043e279:
        xor eax,eax
    L_0043e27b:
        test edi,edi
    L_0043e27d:
        jle short L_0043e28d
    L_0043e27f:
        mov ecx,dword ptr [esp+20h]
    L_0043e283:
        mov edx,dword ptr [ebx]
    L_0043e285:
        add eax,dword ptr [ecx]
    L_0043e287:
        add ecx,4
    L_0043e28a:
        dec edx
    L_0043e28b:
        jne short L_0043e285
    L_0043e28d:
        cdq
    L_0043e28e:
        idiv edi
    L_0043e290:
        mov dword ptr [ebx],0
    L_0043e296:
        mov edi,eax
    L_0043e298:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e29f:
        test eax,eax
    L_0043e2a1:
        je asm_target_0043e348
    L_0043e2a7:
        mov ecx,dword ptr [eax]
    L_0043e2a9:
        push eax
    L_0043e2aa:
        call dword ptr [ecx+48h]
    L_0043e2ad:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e2b4:
        mov edx,dword ptr [eax]
    L_0043e2b6:
        push 0
    L_0043e2b8:
        push eax
    L_0043e2b9:
        call dword ptr [edx+34h]
    L_0043e2bc:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e2c3:
        mov ecx,dword ptr [eax]
    L_0043e2c5:
        push edi
    L_0043e2c6:
        push eax
    L_0043e2c7:
        call dword ptr [ecx+40h]
    L_0043e2ca:
        mov eax,dword ptr [data_00497858]
    L_0043e2cf:
        test eax,eax
    L_0043e2d1:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e2d8:
        je short L_0043e32a
    L_0043e2da:
        fild dword ptr [data_00497858]
    L_0043e2e0:
        movsx edx,word ptr [esi*8+4749CCh]
    L_0043e2e8:
        mov edi,dword ptr [eax]
    L_0043e2ea:
        add edx,1388h
    L_0043e2f0:
        fmul dword ptr [data_00470b00]
    L_0043e2f6:
        mov dword ptr [esp+18h],edx
    L_0043e2fa:
        fsubr dword ptr [data_00470afc]
    L_0043e300:
        fld st(0)
    L_0043e302:
        fmul st,st(1)
    L_0043e304:
        fmul st,st(1)
    L_0043e306:
        fsubr dword ptr [data_00470afc]
    L_0043e30c:
        fimul dword ptr [esp+18h]
    L_0043e310:
        call asm_FUN_00463b2c_00463b2c
    L_0043e315:
        fstp st(0)
    L_0043e317:
        sub eax,1388h
    L_0043e31c:
        push eax
    L_0043e31d:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e324:
        push eax
    L_0043e325:
        call dword ptr [edi+3Ch]
    L_0043e328:
        jmp short L_0043e335
    L_0043e32a:
        mov ecx,dword ptr [eax]
    L_0043e32c:
        push 0FFFFD8F0h
    L_0043e331:
        push eax
    L_0043e332:
        call dword ptr [ecx+3Ch]
    L_0043e335:
        mov esi,dword ptr [ebp+esi*4+208h]
    L_0043e33c:
        mov edx,dword ptr [esi]
    L_0043e33e:
        push 0
    L_0043e340:
        push 0
    L_0043e342:
        push 0
    L_0043e344:
        push esi
    L_0043e345:
        call dword ptr [edx+30h]
    L_0043e348:
        mov eax,dword ptr [esp+10h]
    L_0043e34c:
        mov edx,dword ptr [esp+20h]
    L_0043e350:
        inc eax
    L_0043e351:
        add edx,200h
    L_0043e357:
        add ebx,4
    L_0043e35a:
        cmp eax,0Ch
    L_0043e35d:
        mov dword ptr [esp+10h],eax
    L_0043e361:
        mov dword ptr [esp+20h],edx
    L_0043e365:
        jl asm_target_0043e243
    L_0043e36b:
        mov eax,dword ptr [esp+14h]
    L_0043e36f:
        mov eax,dword ptr [eax]
    L_0043e371:
        pop esi
    L_0043e372:
        pop edi
    L_0043e373:
        pop ebx
    L_0043e374:
        pop ebp
    L_0043e375:
        add esp,0Ch
    L_0043e378:
        ret 4
    }
}

// 0x0044CBF0..0x0044CE7A: FUN_0044cbf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044cbf0_0044cbf0() {
    __asm {
    L_0044cbf0:
        push 0FFFFFFFFh
    L_0044cbf2:
        push 46531Bh
    L_0044cbf7:
        mov eax,dword ptr fs:[0]
    L_0044cbfd:
        push eax
    L_0044cbfe:
        mov dword ptr fs:[0],esp
    L_0044cc05:
        sub esp,4Ch
    L_0044cc08:
        mov eax,dword ptr [data_00473660]
    L_0044cc0d:
        xor eax,esp
    L_0044cc0f:
        push ebx
    L_0044cc10:
        mov ebx,dword ptr [esp+64h]
    L_0044cc14:
        mov dword ptr [esp+10h],ecx
    L_0044cc18:
        mov ecx,dword ptr [esp+74h]
    L_0044cc1c:
        push ebp
    L_0044cc1d:
        mov ebp,dword ptr [esp+84h]
    L_0044cc24:
        push esi
    L_0044cc25:
        mov dword ptr [esp+48h],ecx
    L_0044cc29:
        mov ecx,dword ptr [esp+84h]
    L_0044cc30:
        mov esi,edx
    L_0044cc32:
        mov edx,dword ptr [esp+78h]
    L_0044cc36:
        mov dword ptr [esp+54h],eax
    L_0044cc3a:
        mov eax,dword ptr [esp+68h]
    L_0044cc3e:
        push edi
    L_0044cc3f:
        mov dword ptr [esp+54h],ecx
    L_0044cc43:
        mov ecx,dword ptr [eax]
    L_0044cc45:
        mov dword ptr [esp+48h],edx
    L_0044cc49:
        mov edx,dword ptr [esp+84h]
    L_0044cc50:
        xor edi,edi
    L_0044cc52:
        cmp ecx,edi
    L_0044cc54:
        mov dword ptr [esp+18h],eax
    L_0044cc58:
        mov dword ptr [esp+50h],edx
    L_0044cc5c:
        jne short L_0044cc68
    L_0044cc5e:
        mov eax,800401F0h
    L_0044cc63:
        jmp asm_target_0044ce5b
    L_0044cc68:
        push 94h
    L_0044cc6d:
        mov dword ptr [esp+18h],edi
    L_0044cc71:
        mov dword ptr [esp+14h],edi
    L_0044cc75:
        call asm_operator_new_00452493
    L_0044cc7a:
        add esp,4
    L_0044cc7d:
        cmp eax,edi
    L_0044cc7f:
        je short L_0044cc91
    L_0044cc81:
        mov dword ptr [eax+90h],edi
    L_0044cc87:
        mov dword ptr [eax],edi
    L_0044cc89:
        mov dword ptr [eax+2Ch],edi
    L_0044cc8c:
        mov dword ptr [eax+7Ch],edi
    L_0044cc8f:
        mov edi,eax
    L_0044cc91:
        mov edx,dword ptr [esp+78h]
    L_0044cc95:
        mov eax,dword ptr [esp+74h]
    L_0044cc99:
        mov dword ptr [edi+90h],edx
    L_0044cc9f:
        mov edx,dword ptr [esp+48h]
    L_0044cca3:
        mov dword ptr [edi+88h],eax
    L_0044cca9:
        mov eax,dword ptr [esp+4Ch]
    L_0044ccad:
        mov dword ptr [edi+80h],ebx
    L_0044ccb3:
        mov dword ptr [edi+84h],ebx
    L_0044ccb9:
        xor ecx,ecx
    L_0044ccbb:
        mov dword ptr [edi+7Ch],1
    L_0044ccc2:
        mov dword ptr [esp+24h],ecx
    L_0044ccc6:
        mov dword ptr [esp+28h],ecx
    L_0044ccca:
        mov dword ptr [esp+2Ch],ecx
    L_0044ccce:
        mov dword ptr [esp+30h],ecx
    L_0044ccd2:
        mov dword ptr [esp+34h],ecx
    L_0044ccd6:
        mov dword ptr [esp+38h],ecx
    L_0044ccda:
        mov dword ptr [esp+3Ch],ecx
    L_0044ccde:
        mov ebx,ebp
    L_0044cce0:
        imul ebx,dword ptr [esp+90h]
    L_0044cce8:
        mov dword ptr [esp+40h],ecx
    L_0044ccec:
        mov dword ptr [esp+44h],ecx
    L_0044ccf0:
        mov ecx,dword ptr [esp+50h]
    L_0044ccf4:
        mov dword ptr [esp+38h],edx
    L_0044ccf8:
        mov edx,dword ptr [esp+54h]
    L_0044ccfc:
        mov dword ptr [esp+40h],ecx
    L_0044cd00:
        mov ecx,dword ptr [esp+18h]
    L_0044cd04:
        mov dword ptr [esp+3Ch],eax
    L_0044cd08:
        mov dword ptr [esp+24h],24h
    L_0044cd10:
        or esi,18188h
    L_0044cd16:
        mov dword ptr [esp+28h],esi
    L_0044cd1a:
        mov dword ptr [esp+2Ch],ebx
    L_0044cd1e:
        mov dword ptr [esp+44h],edx
    L_0044cd22:
        mov eax,dword ptr [edi+90h]
    L_0044cd28:
        add eax,20h
    L_0044cd2b:
        mov dword ptr [esp+34h],eax
    L_0044cd2f:
        mov eax,dword ptr [ecx]
    L_0044cd31:
        mov edx,dword ptr [eax]
    L_0044cd33:
        push 0
    L_0044cd35:
        lea ecx,[esp+18h]
    L_0044cd39:
        push ecx
    L_0044cd3a:
        lea ecx,[esp+2Ch]
    L_0044cd3e:
        push ecx
    L_0044cd3f:
        push eax
    L_0044cd40:
        call dword ptr [edx+0Ch]
    L_0044cd43:
        test eax,eax
    L_0044cd45:
        jl asm_target_0044cdd9
    L_0044cd4b:
        mov eax,dword ptr [esp+14h]
    L_0044cd4f:
        mov edx,dword ptr [eax]
    L_0044cd51:
        lea ecx,[esp+10h]
    L_0044cd55:
        push ecx
    L_0044cd56:
        push 46743Ch
    L_0044cd5b:
        push eax
    L_0044cd5c:
        call dword ptr [edx]
    L_0044cd5e:
        test eax,eax
    L_0044cd60:
        jl short L_0044cdd9
    L_0044cd62:
        lea edx,[ebp*8]
    L_0044cd69:
        push edx
    L_0044cd6a:
        call asm_operator_new_00452493
    L_0044cd6f:
        mov esi,eax
    L_0044cd71:
        add esp,4
    L_0044cd74:
        test esi,esi
    L_0044cd76:
        jne short L_0044cd82
    L_0044cd78:
        mov eax,8007000Eh
    L_0044cd7d:
        jmp asm_target_0044ce5b
    L_0044cd82:
        xor eax,eax
    L_0044cd84:
        test ebp,ebp
    L_0044cd86:
        jbe short L_0044cdac
    L_0044cd88:
        mov ecx,dword ptr [esp+90h]
    L_0044cd8f:
        dec ecx
    L_0044cd90:
        mov edx,dword ptr [esp+94h]
    L_0044cd97:
        mov dword ptr [esi+eax*8+4],edx
    L_0044cd9b:
        mov edx,dword ptr [esp+90h]
    L_0044cda2:
        mov dword ptr [esi+eax*8],ecx
    L_0044cda5:
        inc eax
    L_0044cda6:
        add ecx,edx
    L_0044cda8:
        cmp eax,ebp
    L_0044cdaa:
        jb short L_0044cd90
    L_0044cdac:
        mov eax,dword ptr [esp+10h]
    L_0044cdb0:
        mov ecx,dword ptr [eax]
    L_0044cdb2:
        push esi
    L_0044cdb3:
        push ebp
    L_0044cdb4:
        push eax
    L_0044cdb5:
        call dword ptr [ecx+0Ch]
    L_0044cdb8:
        xor ebp,ebp
    L_0044cdba:
        cmp eax,ebp
    L_0044cdbc:
        mov eax,dword ptr [esp+10h]
    L_0044cdc0:
        jge short L_0044cde3
    L_0044cdc2:
        cmp eax,ebp
    L_0044cdc4:
        je short L_0044cdd0
    L_0044cdc6:
        mov edx,dword ptr [eax]
    L_0044cdc8:
        push eax
    L_0044cdc9:
        call dword ptr [edx+8]
    L_0044cdcc:
        mov dword ptr [esp+10h],ebp
    L_0044cdd0:
        push esi
    L_0044cdd1:
        call asm_free_004524a1
    L_0044cdd6:
        add esp,4
    L_0044cdd9:
        mov eax,80004005h
    L_0044cdde:
        jmp asm_target_0044ce5b
    L_0044cde3:
        cmp eax,ebp
    L_0044cde5:
        je short L_0044cdf1
    L_0044cde7:
        mov ecx,dword ptr [eax]
    L_0044cde9:
        push eax
    L_0044cdea:
        call dword ptr [ecx+8]
    L_0044cded:
        mov dword ptr [esp+10h],ebp
    L_0044cdf1:
        push esi
    L_0044cdf2:
        call asm_free_004524a1
    L_0044cdf7:
        push 78h
    L_0044cdf9:
        call asm_operator_new_00452493
    L_0044cdfe:
        add esp,8
    L_0044ce01:
        mov dword ptr [esp+20h],eax
    L_0044ce05:
        cmp eax,ebp
    L_0044ce07:
        mov dword ptr [esp+64h],ebp
    L_0044ce0b:
        je short L_0044ce25
    L_0044ce0d:
        mov edx,dword ptr [esp+90h]
    L_0044ce14:
        mov ecx,dword ptr [esp+14h]
    L_0044ce18:
        push edx
    L_0044ce19:
        push edi
    L_0044ce1a:
        push ebx
    L_0044ce1b:
        push ecx
    L_0044ce1c:
        mov esi,eax
    L_0044ce1e:
        call asm_Recovery_InitializeSingleInterface_0044d6a0
    L_0044ce23:
        jmp short L_0044ce27
    L_0044ce25:
        xor eax,eax
    L_0044ce27:
        mov edx,dword ptr [esp+1Ch]
    L_0044ce2b:
        mov dword ptr [edx],eax
    L_0044ce2d:
        lea edi,[eax+34h]
    L_0044ce30:
        mov ecx,9
    L_0044ce35:
        lea esi,[esp+24h]
    L_0044ce39:
        rep movsd
    L_0044ce3b:
        mov eax,dword ptr [edx]
    L_0044ce3d:
        mov ecx,dword ptr [esp+18h]
    L_0044ce41:
        mov dword ptr [eax+58h],ecx
    L_0044ce44:
        mov eax,dword ptr [edx]
    L_0044ce46:
        mov ecx,dword ptr [esp+94h]
    L_0044ce4d:
        mov dword ptr [eax+70h],ecx
    L_0044ce50:
        mov edx,dword ptr [edx]
    L_0044ce52:
        mov dword ptr [edx+74h],0
    L_0044ce59:
        xor eax,eax
    L_0044ce5b:
        mov ecx,dword ptr [esp+5Ch]
    L_0044ce5f:
        pop edi
    L_0044ce60:
        pop esi
    L_0044ce61:
        pop ebp
    L_0044ce62:
        mov dword ptr fs:[0],ecx
    L_0044ce69:
        mov ecx,dword ptr [esp+4Ch]
    L_0044ce6d:
        pop ebx
    L_0044ce6e:
        xor ecx,esp
    L_0044ce70:
        call asm_security_check_cookie_00458ea5
    L_0044ce75:
        add esp,58h
    L_0044ce78:
        ret 2Ch
    }
}

// 0x0044CF20..0x0044D071: FUN_0044cf20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044cf20_0044cf20() {
    __asm {
    L_0044cf20:
        push ecx
    L_0044cf21:
        mov eax,dword ptr [esi+10h]
    L_0044cf24:
        push ebx
    L_0044cf25:
        push ebp
    L_0044cf26:
        xor ebx,ebx
    L_0044cf28:
        push edi
    L_0044cf29:
        xor edi,edi
    L_0044cf2b:
        cmp eax,ebx
    L_0044cf2d:
        mov dword ptr [esi+30h],ebx
    L_0044cf30:
        jbe short L_0044cf55
    L_0044cf32:
        mov eax,dword ptr [esi+4]
    L_0044cf35:
        mov ecx,dword ptr [eax+edi*4]
    L_0044cf38:
        cmp ecx,ebx
    L_0044cf3a:
        lea eax,[eax+edi*4]
    L_0044cf3d:
        je short L_0044cf4d
    L_0044cf3f:
        mov eax,ecx
    L_0044cf41:
        mov ecx,dword ptr [eax]
    L_0044cf43:
        push eax
    L_0044cf44:
        call dword ptr [ecx+8]
    L_0044cf47:
        mov edx,dword ptr [esi+4]
    L_0044cf4a:
        mov dword ptr [edx+edi*4],ebx
    L_0044cf4d:
        mov eax,dword ptr [esi+10h]
    L_0044cf50:
        inc edi
    L_0044cf51:
        cmp edi,eax
    L_0044cf53:
        jb short L_0044cf32
    L_0044cf55:
        mov eax,dword ptr [esi+4]
    L_0044cf58:
        cmp eax,ebx
    L_0044cf5a:
        je short L_0044cf68
    L_0044cf5c:
        push eax
    L_0044cf5d:
        call asm_free_004524a1
    L_0044cf62:
        add esp,4
    L_0044cf65:
        mov dword ptr [esi+4],ebx
    L_0044cf68:
        mov eax,dword ptr [esi+10h]
    L_0044cf6b:
        shl eax,2
    L_0044cf6e:
        push eax
    L_0044cf6f:
        mov dword ptr [esp+10h],ebx
    L_0044cf73:
        call asm_operator_new_00452493
    L_0044cf78:
        mov dword ptr [esi+4],eax
    L_0044cf7b:
        mov eax,dword ptr [esi+10h]
    L_0044cf7e:
        add esp,4
    L_0044cf81:
        cmp eax,ebx
    L_0044cf83:
        jbe asm_target_0044d03c
    L_0044cf89:
        lea ebp,[esi+34h]
    L_0044cf8c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0044cf90:
        mov ecx,dword ptr [esi+58h]
    L_0044cf93:
        mov eax,dword ptr [ecx]
    L_0044cf95:
        mov ecx,dword ptr [esi+4]
    L_0044cf98:
        mov edx,dword ptr [eax]
    L_0044cf9a:
        push 0
    L_0044cf9c:
        lea edi,[ebx*4]
    L_0044cfa3:
        add ecx,edi
    L_0044cfa5:
        push ecx
    L_0044cfa6:
        push ebp
    L_0044cfa7:
        push eax
    L_0044cfa8:
        call dword ptr [edx+0Ch]
    L_0044cfab:
        test eax,eax
    L_0044cfad:
        jl asm_target_0044d068
    L_0044cfb3:
        mov edx,dword ptr [esi+4]
    L_0044cfb6:
        mov edi,dword ptr [edi+edx]
    L_0044cfb9:
        mov eax,dword ptr [edi]
    L_0044cfbb:
        lea ecx,[esp+0Ch]
    L_0044cfbf:
        push ecx
    L_0044cfc0:
        push 46743Ch
    L_0044cfc5:
        push edi
    L_0044cfc6:
        call dword ptr [eax]
    L_0044cfc8:
        test eax,eax
    L_0044cfca:
        jl asm_target_0044d068
    L_0044cfd0:
        push 80h
    L_0044cfd5:
        call asm_operator_new_00452493
    L_0044cfda:
        mov edi,eax
    L_0044cfdc:
        add esp,4
    L_0044cfdf:
        test edi,edi
    L_0044cfe1:
        je short L_0044d043
    L_0044cfe3:
        xor eax,eax
    L_0044cfe5:
        mov edx,dword ptr [esi+6Ch]
    L_0044cfe8:
        lea ecx,[eax+1]
    L_0044cfeb:
        imul edx,ecx
    L_0044cfee:
        dec edx
    L_0044cfef:
        mov dword ptr [edi+eax*8],edx
    L_0044cff2:
        mov edx,dword ptr [esi+70h]
    L_0044cff5:
        mov dword ptr [edi+eax*8+4],edx
    L_0044cff9:
        mov eax,ecx
    L_0044cffb:
        cmp eax,10h
    L_0044cffe:
        jb short L_0044cfe5
    L_0044d000:
        mov eax,dword ptr [esp+0Ch]
    L_0044d004:
        mov ecx,dword ptr [eax]
    L_0044d006:
        push edi
    L_0044d007:
        push 10h
    L_0044d009:
        push eax
    L_0044d00a:
        call dword ptr [ecx+0Ch]
    L_0044d00d:
        test eax,eax
    L_0044d00f:
        mov eax,dword ptr [esp+0Ch]
    L_0044d013:
        jl short L_0044d04d
    L_0044d015:
        test eax,eax
    L_0044d017:
        je short L_0044d027
    L_0044d019:
        mov edx,dword ptr [eax]
    L_0044d01b:
        push eax
    L_0044d01c:
        call dword ptr [edx+8]
    L_0044d01f:
        mov dword ptr [esp+0Ch],0
    L_0044d027:
        push edi
    L_0044d028:
        call asm_free_004524a1
    L_0044d02d:
        mov eax,dword ptr [esi+10h]
    L_0044d030:
        add esp,4
    L_0044d033:
        inc ebx
    L_0044d034:
        cmp ebx,eax
    L_0044d036:
        jb asm_target_0044cf90
    L_0044d03c:
        pop edi
    L_0044d03d:
        pop ebp
    L_0044d03e:
        xor eax,eax
    L_0044d040:
        pop ebx
    L_0044d041:
        pop ecx
    L_0044d042:
        ret
    L_0044d043:
        pop edi
    L_0044d044:
        pop ebp
    L_0044d045:
        mov eax,8007000Eh
    L_0044d04a:
        pop ebx
    L_0044d04b:
        pop ecx
    L_0044d04c:
        ret
    L_0044d04d:
        test eax,eax
    L_0044d04f:
        je short L_0044d05f
    L_0044d051:
        mov ecx,dword ptr [eax]
    L_0044d053:
        push eax
    L_0044d054:
        call dword ptr [ecx+8]
    L_0044d057:
        mov dword ptr [esp+0Ch],0
    L_0044d05f:
        push edi
    L_0044d060:
        call asm_free_004524a1
    L_0044d065:
        add esp,4
    L_0044d068:
        pop edi
    L_0044d069:
        pop ebp
    L_0044d06a:
        mov eax,80004005h
    L_0044d06f:
        pop ebx
    L_0044d070:
        pop ecx
    L_0044d071:
        ret
    }
}

// 0x0044D110..0x0044D2F2: Streamer_FillBufferRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Streamer_FillBufferRetail_0044d110() {
    __asm {
    L_0044d110:
        sub esp,0Ch
    L_0044d113:
        push ebx
    L_0044d114:
        push ebp
    L_0044d115:
        mov ebp,dword ptr [esp+18h]
    L_0044d119:
        push edi
    L_0044d11a:
        xor edi,edi
    L_0044d11c:
        cmp ebp,edi
    L_0044d11e:
        mov ebx,eax
    L_0044d120:
        mov dword ptr [esp+0Ch],edi
    L_0044d124:
        mov dword ptr [esp+1Ch],edi
    L_0044d128:
        mov dword ptr [esp+10h],edi
    L_0044d12c:
        jne short L_0044d13c
    L_0044d12e:
        pop edi
    L_0044d12f:
        pop ebp
    L_0044d130:
        mov eax,800401F0h
    L_0044d135:
        pop ebx
    L_0044d136:
        add esp,0Ch
    L_0044d139:
        ret 8
    L_0044d13c:
        mov eax,dword ptr [ebp]
    L_0044d13f:
        lea ecx,[esp+14h]
    L_0044d143:
        push ecx
    L_0044d144:
        push ebp
    L_0044d145:
        call dword ptr [eax+24h]
    L_0044d148:
        cmp eax,edi
    L_0044d14a:
        jl asm_target_0044d2ea
    L_0044d150:
        test byte ptr [esp+14h],2
    L_0044d155:
        push esi
    L_0044d156:
        je short L_0044d17d
    L_0044d158:
        mov esi,dword ptr [data_004660ac]
    L_0044d15e:
        mov edi,edi
    L_0044d160:
        mov edx,dword ptr [ebp]
    L_0044d163:
        push ebp
    L_0044d164:
        call dword ptr [edx+50h]
    L_0044d167:
        cmp eax,88780096h
    L_0044d16c:
        jne short L_0044d172
    L_0044d16e:
        push 0Ah
    L_0044d170:
        call esi
    L_0044d172:
        mov eax,dword ptr [ebp]
    L_0044d175:
        push ebp
    L_0044d176:
        call dword ptr [eax+50h]
    L_0044d179:
        test eax,eax
    L_0044d17b:
        jne short L_0044d160
    L_0044d17d:
        mov ecx,dword ptr [ebp]
    L_0044d180:
        push edi
    L_0044d181:
        push edi
    L_0044d182:
        push edi
    L_0044d183:
        lea edx,[esp+2Ch]
    L_0044d187:
        push edx
    L_0044d188:
        mov edx,dword ptr [ebx+8]
    L_0044d18b:
        lea eax,[esp+20h]
    L_0044d18f:
        push eax
    L_0044d190:
        push edx
    L_0044d191:
        push edi
    L_0044d192:
        push ebp
    L_0044d193:
        call dword ptr [ecx+2Ch]
    L_0044d196:
        cmp eax,edi
    L_0044d198:
        jl asm_target_0044d2e9
    L_0044d19e:
        mov esi,dword ptr [ebx+0Ch]
    L_0044d1a1:
        cmp dword ptr [esi+7Ch],edi
    L_0044d1a4:
        je short L_0044d1c7
    L_0044d1a6:
        mov eax,dword ptr [esi+80h]
    L_0044d1ac:
        mov ecx,dword ptr [esi+90h]
    L_0044d1b2:
        mov dword ptr [esi+84h],eax
    L_0044d1b8:
        mov eax,dword ptr [ecx+1Ch]
    L_0044d1bb:
        cmp eax,edi
    L_0044d1bd:
        jle short L_0044d1f8
    L_0044d1bf:
        mov dword ptr [esi+88h],eax
    L_0044d1c5:
        jmp short L_0044d1f8
    L_0044d1c7:
        mov eax,dword ptr [esi+8Ch]
    L_0044d1cd:
        cmp eax,edi
    L_0044d1cf:
        je short L_0044d1f8
    L_0044d1d1:
        mov edx,dword ptr [esi+90h]
    L_0044d1d7:
        mov ecx,dword ptr [edx+10h]
    L_0044d1da:
        mov edx,dword ptr [data_004977a4]
    L_0044d1e0:
        push edi
    L_0044d1e1:
        push edi
    L_0044d1e2:
        add ecx,edx
    L_0044d1e4:
        push ecx
    L_0044d1e5:
        push eax
    L_0044d1e6:
        call dword ptr [data_004660c8]
    L_0044d1ec:
        mov edx,dword ptr [esi+90h]
    L_0044d1f2:
        mov eax,dword ptr [edx+1Ch]
    L_0044d1f5:
        mov dword ptr [esi+8],eax
    L_0044d1f8:
        mov edx,dword ptr [esp+10h]
    L_0044d1fc:
        mov eax,dword ptr [ebx+0Ch]
    L_0044d1ff:
        lea ecx,[esp+14h]
    L_0044d203:
        push ecx
    L_0044d204:
        push edx
    L_0044d205:
        mov edx,dword ptr [esp+28h]
    L_0044d209:
        call asm_ArchiveCursor_ReadRetail_0044de10
    L_0044d20e:
        cmp eax,edi
    L_0044d210:
        jl asm_target_0044d2e9
    L_0044d216:
        mov edi,dword ptr [esp+14h]
    L_0044d21a:
        test edi,edi
    L_0044d21c:
        mov ecx,dword ptr [esp+20h]
    L_0044d220:
        jne short L_0044d243
    L_0044d222:
        mov eax,dword ptr [ebx+0Ch]
    L_0044d225:
        mov edx,dword ptr [eax+90h]
    L_0044d22b:
        cmp word ptr [edx+2Eh],8
    L_0044d230:
        mov edi,dword ptr [esp+10h]
    L_0044d234:
        setne al
    L_0044d237:
        dec al
    L_0044d239:
        and eax,80h
    L_0044d23e:
        movzx eax,al
    L_0044d241:
        jmp short L_0044d2b8
    L_0044d243:
        cmp edi,ecx
    L_0044d245:
        jae asm_target_0044d2d2
    L_0044d24b:
        mov eax,dword ptr [esp+24h]
    L_0044d24f:
        test eax,eax
    L_0044d251:
        je short L_0044d294
    L_0044d253:
        mov esi,dword ptr [ebx+0Ch]
    L_0044d256:
        xor al,al
    L_0044d258:
        call asm_ArchiveCursor_SeekRetail_0044dd40
    L_0044d25d:
        test eax,eax
    L_0044d25f:
        jl asm_target_0044d2e9
    L_0044d265:
        mov ecx,dword ptr [esp+10h]
    L_0044d269:
        mov edx,dword ptr [esp+20h]
    L_0044d26d:
        lea eax,[esp+14h]
    L_0044d271:
        push eax
    L_0044d272:
        lea eax,[edi+ecx]
    L_0044d275:
        push eax
    L_0044d276:
        mov eax,dword ptr [ebx+0Ch]
    L_0044d279:
        sub edx,edi
    L_0044d27b:
        call asm_ArchiveCursor_ReadRetail_0044de10
    L_0044d280:
        test eax,eax
    L_0044d282:
        jl short L_0044d2e9
    L_0044d284:
        mov ecx,dword ptr [esp+14h]
    L_0044d288:
        mov eax,dword ptr [esp+20h]
    L_0044d28c:
        add edi,ecx
    L_0044d28e:
        cmp edi,eax
    L_0044d290:
        jb short L_0044d253
    L_0044d292:
        jmp short L_0044d2d2
    L_0044d294:
        mov edx,dword ptr [ebx+0Ch]
    L_0044d297:
        mov eax,dword ptr [edx+90h]
    L_0044d29d:
        sub ecx,edi
    L_0044d29f:
        cmp word ptr [eax+2Eh],8
    L_0044d2a4:
        setne dl
    L_0044d2a7:
        dec dl
    L_0044d2a9:
        and edx,80h
    L_0044d2af:
        movzx eax,dl
    L_0044d2b2:
        mov edx,dword ptr [esp+10h]
    L_0044d2b6:
        add edi,edx
    L_0044d2b8:
        mov bl,al
    L_0044d2ba:
        mov bh,bl
    L_0044d2bc:
        mov edx,ecx
    L_0044d2be:
        shr ecx,2
    L_0044d2c1:
        mov eax,ebx
    L_0044d2c3:
        shl eax,10h
    L_0044d2c6:
        mov ax,bx
    L_0044d2c9:
        rep stosd
    L_0044d2cb:
        mov ecx,edx
    L_0044d2cd:
        and ecx,3
    L_0044d2d0:
        rep stosb
    L_0044d2d2:
        mov ecx,dword ptr [esp+20h]
    L_0044d2d6:
        mov edx,dword ptr [esp+10h]
    L_0044d2da:
        mov eax,dword ptr [ebp]
    L_0044d2dd:
        push 0
    L_0044d2df:
        push 0
    L_0044d2e1:
        push ecx
    L_0044d2e2:
        push edx
    L_0044d2e3:
        push ebp
    L_0044d2e4:
        call dword ptr [eax+4Ch]
    L_0044d2e7:
        xor eax,eax
    L_0044d2e9:
        pop esi
    L_0044d2ea:
        pop edi
    L_0044d2eb:
        pop ebp
    L_0044d2ec:
        pop ebx
    L_0044d2ed:
        add esp,0Ch
    L_0044d2f0:
        ret 8
    }
}

// 0x0044DAD0..0x0044DBA4: Streamer_RestartRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Streamer_RestartRetail_0044dad0() {
    __asm {
    L_0044dad0:
        push ecx
    L_0044dad1:
        mov eax,dword ptr [edi+4]
    L_0044dad4:
        mov ecx,dword ptr [eax]
    L_0044dad6:
        push ebp
    L_0044dad7:
        xor ebp,ebp
    L_0044dad9:
        cmp ecx,ebp
    L_0044dadb:
        je asm_target_0044db9d
    L_0044dae1:
        cmp dword ptr [edi+0Ch],ebp
    L_0044dae4:
        je asm_target_0044db9d
    L_0044daea:
        push ebx
    L_0044daeb:
        push esi
    L_0044daec:
        mov dword ptr [edi+5Ch],ebp
    L_0044daef:
        mov dword ptr [edi+60h],ebp
    L_0044daf2:
        mov dword ptr [edi+64h],ebp
    L_0044daf5:
        mov dword ptr [edi+68h],ebp
    L_0044daf8:
        mov esi,dword ptr [eax]
    L_0044dafa:
        lea ebx,[esp+0Ch]
    L_0044dafe:
        call asm_Platform_RunInterface_0044d300
    L_0044db03:
        cmp eax,ebp
    L_0044db05:
        jl asm_target_0044db98
    L_0044db0b:
        cmp dword ptr [esp+0Ch],ebp
    L_0044db0f:
        je short L_0044db23
    L_0044db11:
        mov eax,dword ptr [edi+4]
    L_0044db14:
        mov ecx,dword ptr [eax]
    L_0044db16:
        push ebp
    L_0044db17:
        push ecx
    L_0044db18:
        mov eax,edi
    L_0044db1a:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044db1f:
        cmp eax,ebp
    L_0044db21:
        jl short L_0044db98
    L_0044db23:
        mov esi,dword ptr [edi+0Ch]
    L_0044db26:
        cmp dword ptr [esi+7Ch],ebp
    L_0044db29:
        je short L_0044db5b
    L_0044db2b:
        mov edx,dword ptr [esi+80h]
    L_0044db31:
        mov eax,dword ptr [esi+90h]
    L_0044db37:
        mov dword ptr [esi+84h],edx
    L_0044db3d:
        mov eax,dword ptr [eax+1Ch]
    L_0044db40:
        cmp eax,ebp
    L_0044db42:
        jle short L_0044db8c
    L_0044db44:
        mov dword ptr [esi+88h],eax
    L_0044db4a:
        mov edx,dword ptr [edi+4]
    L_0044db4d:
        mov eax,dword ptr [edx]
    L_0044db4f:
        mov ecx,dword ptr [eax]
    L_0044db51:
        push ebp
    L_0044db52:
        push eax
    L_0044db53:
        call dword ptr [ecx+34h]
    L_0044db56:
        pop esi
    L_0044db57:
        pop ebx
    L_0044db58:
        pop ebp
    L_0044db59:
        pop ecx
    L_0044db5a:
        ret
    L_0044db5b:
        mov eax,dword ptr [esi+8Ch]
    L_0044db61:
        cmp eax,ebp
    L_0044db63:
        je short L_0044db8c
    L_0044db65:
        mov ecx,dword ptr [esi+90h]
    L_0044db6b:
        mov edx,dword ptr [ecx+10h]
    L_0044db6e:
        mov ecx,dword ptr [data_004977a4]
    L_0044db74:
        push ebp
    L_0044db75:
        push ebp
    L_0044db76:
        add edx,ecx
    L_0044db78:
        push edx
    L_0044db79:
        push eax
    L_0044db7a:
        call dword ptr [data_004660c8]
    L_0044db80:
        mov eax,dword ptr [esi+90h]
    L_0044db86:
        mov ecx,dword ptr [eax+1Ch]
    L_0044db89:
        mov dword ptr [esi+8],ecx
    L_0044db8c:
        mov edx,dword ptr [edi+4]
    L_0044db8f:
        mov eax,dword ptr [edx]
    L_0044db91:
        mov ecx,dword ptr [eax]
    L_0044db93:
        push ebp
    L_0044db94:
        push eax
    L_0044db95:
        call dword ptr [ecx+34h]
    L_0044db98:
        pop esi
    L_0044db99:
        pop ebx
    L_0044db9a:
        pop ebp
    L_0044db9b:
        pop ecx
    L_0044db9c:
        ret
    L_0044db9d:
        mov eax,800401F0h
    L_0044dba2:
        pop ebp
    L_0044dba3:
        pop ecx
    L_0044dba4:
        ret
    }
}
