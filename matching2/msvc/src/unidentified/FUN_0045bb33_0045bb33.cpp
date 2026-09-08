#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BB33..0x0045BD20: FUN_0045bb33
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045bb33_0045bb33() {
    __asm {
    L_0045bb33:
        push ebp
    L_0045bb34:
        mov ebp,esp
    L_0045bb36:
        sub esp,24h
    L_0045bb39:
        mov eax,dword ptr [data_00473660]
    L_0045bb3e:
        push edi
    L_0045bb3f:
        xor edi,edi
    L_0045bb41:
        xor eax,ebp
    L_0045bb43:
        cmp dword ptr [data_00477654],edi
    L_0045bb49:
        mov dword ptr [ebp-4],eax
    L_0045bb4c:
        mov dword ptr [ebp-1Ch],edi
    L_0045bb4f:
        je asm_target_0045bcfc
    L_0045bb55:
        cmp dword ptr [data_00477664],edi
    L_0045bb5b:
        push ebx
    L_0045bb5c:
        push esi
    L_0045bb5d:
        jne short L_0045bb82
    L_0045bb5f:
        movzx eax,word ptr [data_00477678]
    L_0045bb66:
        push 477664h
    L_0045bb6b:
        push 1004h
    L_0045bb70:
        push eax
    L_0045bb71:
        push edi
    L_0045bb72:
        call asm_FUN_0046041e_0046041e
    L_0045bb77:
        add esp,10h
    L_0045bb7a:
        test eax,eax
    L_0045bb7c:
        jne asm_target_0045bce4
    L_0045bb82:
        push 4
    L_0045bb84:
        call asm_malloc_00452706
    L_0045bb89:
        mov ebx,eax
    L_0045bb8b:
        mov dword ptr [ebp-20h],ebx
    L_0045bb8e:
        mov dword ptr [esp],300h
    L_0045bb95:
        call asm_malloc_00452706
    L_0045bb9a:
        mov esi,eax
    L_0045bb9c:
        mov dword ptr [esp],101h
    L_0045bba3:
        call asm_malloc_00452706
    L_0045bba8:
        cmp ebx,edi
    L_0045bbaa:
        pop ecx
    L_0045bbab:
        mov dword ptr [ebp-1Ch],eax
    L_0045bbae:
        je asm_target_0045bce7
    L_0045bbb4:
        cmp esi,edi
    L_0045bbb6:
        je asm_target_0045bce7
    L_0045bbbc:
        cmp eax,edi
    L_0045bbbe:
        je asm_target_0045bce7
    L_0045bbc4:
        mov dword ptr [ebx],edi
    L_0045bbc6:
        xor eax,eax
    L_0045bbc8:
        mov edi,100h
    L_0045bbcd:
        mov ecx,dword ptr [ebp-1Ch]
    L_0045bbd0:
        mov byte ptr [eax+ecx],al
    L_0045bbd3:
        inc eax
    L_0045bbd4:
        cmp eax,edi
    L_0045bbd6:
        jl short L_0045bbcd
    L_0045bbd8:
        lea eax,[ebp-18h]
    L_0045bbdb:
        push eax
    L_0045bbdc:
        push dword ptr [data_00477664]
    L_0045bbe2:
        call dword ptr [data_00466064]
    L_0045bbe8:
        test eax,eax
    L_0045bbea:
        je asm_target_0045bce7
    L_0045bbf0:
        cmp dword ptr [ebp-18h],5
    L_0045bbf4:
        ja asm_target_0045bce7
    L_0045bbfa:
        movzx eax,word ptr [ebp-18h]
    L_0045bbfe:
        cmp eax,1
    L_0045bc01:
        mov dword ptr [data_00473af0],eax
    L_0045bc06:
        jle short L_0045bc37
    L_0045bc08:
        cmp byte ptr [ebp-12h],0
    L_0045bc0c:
        je short L_0045bc37
    L_0045bc0e:
        lea eax,[ebp-11h]
    L_0045bc11:
        mov dl,byte ptr [eax]
    L_0045bc13:
        test dl,dl
    L_0045bc15:
        je short L_0045bc37
    L_0045bc17:
        movzx ecx,byte ptr [eax-1]
    L_0045bc1b:
        movzx edx,dl
    L_0045bc1e:
        jmp short L_0045bc2b
    L_0045bc20:
        mov edx,dword ptr [ebp-1Ch]
    L_0045bc23:
        mov byte ptr [ecx+edx],0
    L_0045bc27:
        movzx edx,byte ptr [eax]
    L_0045bc2a:
        inc ecx
    L_0045bc2b:
        cmp ecx,edx
    L_0045bc2d:
        jle short L_0045bc20
    L_0045bc2f:
        inc eax
    L_0045bc30:
        inc eax
    L_0045bc31:
        cmp byte ptr [eax-1],0
    L_0045bc35:
        jne short L_0045bc11
    L_0045bc37:
        xor eax,eax
    L_0045bc39:
        push eax
    L_0045bc3a:
        push eax
    L_0045bc3b:
        push eax
    L_0045bc3c:
        lea ebx,[esi+100h]
    L_0045bc42:
        push ebx
    L_0045bc43:
        push edi
    L_0045bc44:
        push dword ptr [ebp-1Ch]
    L_0045bc47:
        mov dword ptr [ebp-24h],ebx
    L_0045bc4a:
        push 1
    L_0045bc4c:
        call asm_crtGetStringTypeA_0045a25d
    L_0045bc51:
        add esp,1Ch
    L_0045bc54:
        test eax,eax
    L_0045bc56:
        je asm_target_0045bce7
    L_0045bc5c:
        lea edi,[esi+0FEh]
    L_0045bc62:
        and word ptr [edi],0
    L_0045bc66:
        cmp dword ptr [data_00473af0],1
    L_0045bc6d:
        jle short L_0045bcaa
    L_0045bc6f:
        cmp byte ptr [ebp-12h],0
    L_0045bc73:
        je short L_0045bcaa
    L_0045bc75:
        lea eax,[ebp-11h]
    L_0045bc78:
        mov dl,byte ptr [eax]
    L_0045bc7a:
        test dl,dl
    L_0045bc7c:
        je short L_0045bcaa
    L_0045bc7e:
        movzx ecx,byte ptr [eax-1]
    L_0045bc82:
        movzx edx,dl
    L_0045bc85:
        cmp ecx,edx
    L_0045bc87:
        jg short L_0045bca2
    L_0045bc89:
        lea edx,[esi+ecx*2+100h]
    L_0045bc90:
        mov word ptr [edx],8000h
    L_0045bc95:
        movzx ebx,byte ptr [eax]
    L_0045bc98:
        inc ecx
    L_0045bc99:
        inc edx
    L_0045bc9a:
        inc edx
    L_0045bc9b:
        cmp ecx,ebx
    L_0045bc9d:
        jle short L_0045bc90
    L_0045bc9f:
        mov ebx,dword ptr [ebp-24h]
    L_0045bca2:
        inc eax
    L_0045bca3:
        inc eax
    L_0045bca4:
        cmp byte ptr [eax-1],0
    L_0045bca8:
        jne short L_0045bc78
    L_0045bcaa:
        push 0FEh
    L_0045bcaf:
        lea eax,[esi+200h]
    L_0045bcb5:
        push eax
    L_0045bcb6:
        push esi
    L_0045bcb7:
        call asm_memcpy_0045bfc0
    L_0045bcbc:
        mov eax,dword ptr [ebp-20h]
    L_0045bcbf:
        add esp,0Ch
    L_0045bcc2:
        mov dword ptr [data_004739d8],ebx
    L_0045bcc8:
        mov dword ptr [data_004981c4],eax
    L_0045bccd:
        mov dword ptr [data_004981c0],edi
    L_0045bcd3:
        xor esi,esi
    L_0045bcd5:
        push dword ptr [ebp-1Ch]
    L_0045bcd8:
        call asm_free_00452422
    L_0045bcdd:
        pop ecx
    L_0045bcde:
        mov eax,esi
    L_0045bce0:
        pop esi
    L_0045bce1:
        pop ebx
    L_0045bce2:
        jmp short L_0045bd14
    L_0045bce4:
        mov esi,dword ptr [ebp-24h]
    L_0045bce7:
        push dword ptr [ebp-20h]
    L_0045bcea:
        call asm_free_00452422
    L_0045bcef:
        push esi
    L_0045bcf0:
        call asm_free_00452422
    L_0045bcf5:
        pop ecx
    L_0045bcf6:
        xor esi,esi
    L_0045bcf8:
        pop ecx
    L_0045bcf9:
        inc esi
    L_0045bcfa:
        jmp short L_0045bcd5
    L_0045bcfc:
        mov dword ptr [data_004739d8],46B1C0h
    L_0045bd06:
        mov dword ptr [data_004981c4],edi
    L_0045bd0c:
        mov dword ptr [data_004981c0],edi
    L_0045bd12:
        xor eax,eax
    L_0045bd14:
        mov ecx,dword ptr [ebp-4]
    L_0045bd17:
        xor ecx,ebp
    L_0045bd19:
        pop edi
    L_0045bd1a:
        call asm_security_check_cookie_00458ea5
    L_0045bd1f:
        leave
    L_0045bd20:
        ret
    }
}
