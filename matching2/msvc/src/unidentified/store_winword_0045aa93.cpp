#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045AA93..0x0045AB65: __store_winword
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_store_winword_0045aa93() {
    __asm {
    L_0045aa93:
        push 38h
    L_0045aa95:
        push 46B710h
    L_0045aa9a:
        call asm_SEH_prolog_00454bbc
    L_0045aa9f:
        mov eax,dword ptr [ebp+0Ch]
    L_0045aaa2:
        xor esi,esi
    L_0045aaa4:
        sub eax,esi
    L_0045aaa6:
        je short L_0045aabe
    L_0045aaa8:
        dec eax
    L_0045aaa9:
        mov eax,dword ptr [ebp+1Ch]
    L_0045aaac:
        je short L_0045aab6
    L_0045aaae:
        mov eax,dword ptr [eax+0A8h]
    L_0045aab4:
        jmp short L_0045aac7
    L_0045aab6:
        mov eax,dword ptr [eax+0A4h]
    L_0045aabc:
        jmp short L_0045aac7
    L_0045aabe:
        mov eax,dword ptr [ebp+1Ch]
    L_0045aac1:
        mov eax,dword ptr [eax+0A0h]
    L_0045aac7:
        mov dword ptr [ebp-20h],eax
    L_0045aaca:
        mov ecx,dword ptr [ebp+1Ch]
    L_0045aacd:
        cmp dword ptr [ecx+0B0h],1
    L_0045aad4:
        je asm_target_0045abf0
    L_0045aada:
        cmp dword ptr [ebp+0Ch],2
    L_0045aade:
        mov eax,dword ptr [data_00466068]
    L_0045aae3:
        jne short L_0045aaea
    L_0045aae5:
        mov eax,dword ptr [data_0046606c]
    L_0045aaea:
        mov dword ptr [ebp-30h],eax
    L_0045aaed:
        mov ebx,dword ptr [ebp+10h]
    L_0045aaf0:
        mov dx,word ptr [ebx+14h]
    L_0045aaf4:
        add dx,76Ch
    L_0045aaf9:
        mov word ptr [ebp-48h],dx
    L_0045aafd:
        mov dx,word ptr [ebx+10h]
    L_0045ab01:
        inc dx
    L_0045ab03:
        mov word ptr [ebp-46h],dx
    L_0045ab07:
        mov dx,word ptr [ebx+0Ch]
    L_0045ab0b:
        mov word ptr [ebp-42h],dx
    L_0045ab0f:
        mov dx,word ptr [ebx+8]
    L_0045ab13:
        mov word ptr [ebp-40h],dx
    L_0045ab17:
        mov dx,word ptr [ebx+4]
    L_0045ab1b:
        mov word ptr [ebp-3Eh],dx
    L_0045ab1f:
        mov dx,word ptr [ebx]
    L_0045ab22:
        mov word ptr [ebp-3Ch],dx
    L_0045ab26:
        mov word ptr [ebp-3Ah],si
    L_0045ab2a:
        push esi
    L_0045ab2b:
        push esi
    L_0045ab2c:
        push dword ptr [ebp-20h]
    L_0045ab2f:
        lea edx,[ebp-48h]
    L_0045ab32:
        push edx
    L_0045ab33:
        push esi
    L_0045ab34:
        push dword ptr [ecx+0ACh]
    L_0045ab3a:
        call eax
    L_0045ab3c:
        mov dword ptr [ebp-2Ch],eax
    L_0045ab3f:
        cmp eax,esi
    L_0045ab41:
        je asm_target_0045abf3
    L_0045ab47:
        mov dword ptr [ebp-34h],esi
    L_0045ab4a:
        mov dword ptr [ebp-4],esi
    L_0045ab4d:
        add eax,3
    L_0045ab50:
        and eax,0FFFFFFFCh
    L_0045ab53:
        call asm_chkstk_00458ec0
    L_0045ab58:
        mov dword ptr [ebp-18h],esp
    L_0045ab5b:
        mov edi,esp
    L_0045ab5d:
        mov dword ptr [ebp-38h],edi
    L_0045ab60:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045ab64:
        TH10_REL8(0xeb, 0x0045ab64, VA_asm_store_winword_part_0045ab7d)
    }
}

// 0x0045AB7D..0x0045AF1C: __store_winword
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_store_winword_part_0045ab7d() {
    __asm {
    L_0045ab7d:
        cmp edi,esi
    L_0045ab7f:
        jne short L_0045ab97
    L_0045ab81:
        push dword ptr [ebp-2Ch]
    L_0045ab84:
        call asm_malloc_00452706
    L_0045ab89:
        pop ecx
    L_0045ab8a:
        mov edi,eax
    L_0045ab8c:
        cmp edi,esi
    L_0045ab8e:
        je short L_0045abf3
    L_0045ab90:
        mov dword ptr [ebp-34h],1
    L_0045ab97:
        mov dword ptr [ebp-24h],edi
    L_0045ab9a:
        push dword ptr [ebp-2Ch]
    L_0045ab9d:
        push edi
    L_0045ab9e:
        push dword ptr [ebp-20h]
    L_0045aba1:
        lea eax,[ebp-48h]
    L_0045aba4:
        push eax
    L_0045aba5:
        push esi
    L_0045aba6:
        mov eax,dword ptr [ebp+1Ch]
    L_0045aba9:
        push dword ptr [eax+0ACh]
    L_0045abaf:
        call dword ptr [ebp-30h]
    L_0045abb2:
        dec eax
    L_0045abb3:
        cmp eax,esi
    L_0045abb5:
        jle short L_0045abd7
    L_0045abb7:
        mov esi,dword ptr [ebp+18h]
    L_0045abba:
        mov ecx,dword ptr [ebp+14h]
    L_0045abbd:
        cmp dword ptr [esi],0
    L_0045abc0:
        jbe short L_0045abd7
    L_0045abc2:
        mov edx,dword ptr [ecx]
    L_0045abc4:
        mov ebx,dword ptr [ebp-24h]
    L_0045abc7:
        mov bl,byte ptr [ebx]
    L_0045abc9:
        mov byte ptr [edx],bl
    L_0045abcb:
        inc dword ptr [ecx]
    L_0045abcd:
        inc dword ptr [ebp-24h]
    L_0045abd0:
        dec dword ptr [esi]
    L_0045abd2:
        dec eax
    L_0045abd3:
        test eax,eax
    L_0045abd5:
        jg short L_0045abbd
    L_0045abd7:
        cmp dword ptr [ebp-34h],0
    L_0045abdb:
        je short L_0045abe4
    L_0045abdd:
        push edi
    L_0045abde:
        call asm_free_00452422
    L_0045abe3:
        pop ecx
    L_0045abe4:
        xor eax,eax
    L_0045abe6:
        inc eax
    L_0045abe7:
        lea esp,[ebp-54h]
    L_0045abea:
        call asm_SEH_epilog_00454bf7
    L_0045abef:
        ret
    L_0045abf0:
        mov ebx,dword ptr [ebp+10h]
    L_0045abf3:
        mov eax,dword ptr [ebp-20h]
    L_0045abf6:
        mov cl,byte ptr [eax]
    L_0045abf8:
        test cl,cl
    L_0045abfa:
        je short L_0045abe4
    L_0045abfc:
        mov edi,dword ptr [ebp+18h]
    L_0045abff:
        mov esi,dword ptr [ebp+14h]
    L_0045ac02:
        jmp short L_0045ac07
    L_0045ac04:
        mov ebx,dword ptr [ebp+10h]
    L_0045ac07:
        cmp dword ptr [edi],0
    L_0045ac0a:
        je short L_0045abe4
    L_0045ac0c:
        mov byte ptr [ebp-19h],0
    L_0045ac10:
        xor edx,edx
    L_0045ac12:
        mov dword ptr [ebp-28h],edx
    L_0045ac15:
        mov eax,dword ptr [ebp-20h]
    L_0045ac18:
        inc eax
    L_0045ac19:
        inc edx
    L_0045ac1a:
        cmp byte ptr [eax],cl
    L_0045ac1c:
        je short L_0045ac18
    L_0045ac1e:
        mov dword ptr [ebp-24h],eax
    L_0045ac21:
        movsx ecx,cl
    L_0045ac24:
        cmp ecx,64h
    L_0045ac27:
        jg asm_target_0045ad83
    L_0045ac2d:
        je asm_target_0045ad4f
    L_0045ac33:
        cmp ecx,27h
    L_0045ac36:
        je asm_target_0045acde
    L_0045ac3c:
        cmp ecx,41h
    L_0045ac3f:
        je short L_0045ac54
    L_0045ac41:
        cmp ecx,48h
    L_0045ac44:
        je short L_0045aca1
    L_0045ac46:
        cmp ecx,4Dh
    L_0045ac49:
        je short L_0045ac6d
    L_0045ac4b:
        cmp ecx,61h
    L_0045ac4e:
        jne asm_target_0045aeab
    L_0045ac54:
        push 46B704h
    L_0045ac59:
        mov ebx,dword ptr [ebp-20h]
    L_0045ac5c:
        push ebx
    L_0045ac5d:
        call asm_ascii_stricmp_004603d0
    L_0045ac62:
        pop ecx
    L_0045ac63:
        pop ecx
    L_0045ac64:
        test eax,eax
    L_0045ac66:
        jne short L_0045acbe
    L_0045ac68:
        add ebx,5
    L_0045ac6b:
        jmp short L_0045acd2
    L_0045ac6d:
        mov ecx,edx
    L_0045ac6f:
        dec ecx
    L_0045ac70:
        je short L_0045ac91
    L_0045ac72:
        dec ecx
    L_0045ac73:
        je short L_0045ac98
    L_0045ac75:
        dec ecx
    L_0045ac76:
        je short L_0045ac88
    L_0045ac78:
        dec ecx
    L_0045ac79:
        jne asm_target_0045aeab
    L_0045ac7f:
        mov byte ptr [ebp-19h],42h
    L_0045ac83:
        jmp asm_target_0045aeab
    L_0045ac88:
        mov byte ptr [ebp-19h],62h
    L_0045ac8c:
        jmp asm_target_0045aeab
    L_0045ac91:
        mov dword ptr [ebp-28h],1
    L_0045ac98:
        mov byte ptr [ebp-19h],6Dh
    L_0045ac9c:
        jmp asm_target_0045aeab
    L_0045aca1:
        mov ecx,edx
    L_0045aca3:
        dec ecx
    L_0045aca4:
        je short L_0045acae
    L_0045aca6:
        dec ecx
    L_0045aca7:
        je short L_0045acb5
    L_0045aca9:
        jmp asm_target_0045aeab
    L_0045acae:
        mov dword ptr [ebp-28h],1
    L_0045acb5:
        mov byte ptr [ebp-19h],48h
    L_0045acb9:
        jmp asm_target_0045aeab
    L_0045acbe:
        push 46B700h
    L_0045acc3:
        push ebx
    L_0045acc4:
        call asm_ascii_stricmp_004603d0
    L_0045acc9:
        pop ecx
    L_0045acca:
        pop ecx
    L_0045accb:
        test eax,eax
    L_0045accd:
        jne short L_0045acd5
    L_0045accf:
        add ebx,3
    L_0045acd2:
        mov dword ptr [ebp-24h],ebx
    L_0045acd5:
        mov byte ptr [ebp-19h],70h
    L_0045acd9:
        jmp asm_target_0045aeab
    L_0045acde:
        add dword ptr [ebp-20h],edx
    L_0045ace1:
        test dl,1
    L_0045ace4:
        je asm_target_0045af0b
    L_0045acea:
        mov eax,dword ptr [ebp-20h]
    L_0045aced:
        jmp short L_0045ad3c
    L_0045acef:
        mov ecx,dword ptr [edi]
    L_0045acf1:
        test ecx,ecx
    L_0045acf3:
        je asm_target_0045af0b
    L_0045acf9:
        cmp al,27h
    L_0045acfb:
        je short L_0045ad47
    L_0045acfd:
        movzx edx,al
    L_0045ad00:
        mov ebx,dword ptr [ebp+8]
    L_0045ad03:
        mov ebx,dword ptr [ebx+48h]
    L_0045ad06:
        test byte ptr [ebx+edx*2+1],80h
    L_0045ad0b:
        je short L_0045ad2b
    L_0045ad0d:
        cmp ecx,1
    L_0045ad10:
        jbe short L_0045ad2b
    L_0045ad12:
        mov ecx,dword ptr [ebp-20h]
    L_0045ad15:
        inc ecx
    L_0045ad16:
        cmp byte ptr [ecx],0
    L_0045ad19:
        je asm_target_0045aece
    L_0045ad1f:
        mov edx,dword ptr [esi]
    L_0045ad21:
        mov byte ptr [edx],al
    L_0045ad23:
        inc dword ptr [esi]
    L_0045ad25:
        mov eax,ecx
    L_0045ad27:
        dec dword ptr [edi]
    L_0045ad29:
        jmp short L_0045ad2e
    L_0045ad2b:
        mov eax,dword ptr [ebp-20h]
    L_0045ad2e:
        mov ecx,dword ptr [esi]
    L_0045ad30:
        mov dl,byte ptr [eax]
    L_0045ad32:
        mov byte ptr [ecx],dl
    L_0045ad34:
        inc dword ptr [esi]
    L_0045ad36:
        inc eax
    L_0045ad37:
        mov dword ptr [ebp-20h],eax
    L_0045ad3a:
        dec dword ptr [edi]
    L_0045ad3c:
        mov al,byte ptr [eax]
    L_0045ad3e:
        test al,al
    L_0045ad40:
        jne short L_0045acef
    L_0045ad42:
        jmp asm_target_0045af0b
    L_0045ad47:
        inc dword ptr [ebp-20h]
    L_0045ad4a:
        jmp asm_target_0045af0b
    L_0045ad4f:
        mov ecx,edx
    L_0045ad51:
        dec ecx
    L_0045ad52:
        je short L_0045ad73
    L_0045ad54:
        dec ecx
    L_0045ad55:
        je short L_0045ad7a
    L_0045ad57:
        dec ecx
    L_0045ad58:
        je short L_0045ad6a
    L_0045ad5a:
        dec ecx
    L_0045ad5b:
        jne asm_target_0045aeab
    L_0045ad61:
        mov byte ptr [ebp-19h],41h
    L_0045ad65:
        jmp asm_target_0045aeab
    L_0045ad6a:
        mov byte ptr [ebp-19h],61h
    L_0045ad6e:
        jmp asm_target_0045aeab
    L_0045ad73:
        mov dword ptr [ebp-28h],1
    L_0045ad7a:
        mov byte ptr [ebp-19h],64h
    L_0045ad7e:
        jmp asm_target_0045aeab
    L_0045ad83:
        sub ecx,68h
    L_0045ad86:
        je asm_target_0045ae96
    L_0045ad8c:
        sub ecx,5
    L_0045ad8f:
        je asm_target_0045ae7f
    L_0045ad95:
        sub ecx,6
    L_0045ad98:
        je asm_target_0045ae68
    L_0045ad9e:
        dec ecx
    L_0045ad9f:
        je short L_0045adca
    L_0045ada1:
        sub ecx,5
    L_0045ada4:
        jne asm_target_0045aeab
    L_0045adaa:
        mov ecx,edx
    L_0045adac:
        dec ecx
    L_0045adad:
        dec ecx
    L_0045adae:
        je short L_0045adc1
    L_0045adb0:
        dec ecx
    L_0045adb1:
        dec ecx
    L_0045adb2:
        jne asm_target_0045aeab
    L_0045adb8:
        mov byte ptr [ebp-19h],59h
    L_0045adbc:
        jmp asm_target_0045aeab
    L_0045adc1:
        mov byte ptr [ebp-19h],79h
    L_0045adc5:
        jmp asm_target_0045aeab
    L_0045adca:
        mov eax,dword ptr [ebp+1Ch]
    L_0045adcd:
        cmp dword ptr [ebx+8],0Bh
    L_0045add1:
        jg short L_0045addb
    L_0045add3:
        mov eax,dword ptr [eax+98h]
    L_0045add9:
        jmp short L_0045ade1
    L_0045addb:
        mov eax,dword ptr [eax+9Ch]
    L_0045ade1:
        cmp edx,1
    L_0045ade4:
        jne short L_0045ae57
    L_0045ade6:
        cmp dword ptr [edi],0
    L_0045ade9:
        jbe short L_0045ae57
    L_0045adeb:
        mov cl,byte ptr [eax]
    L_0045aded:
        movzx edx,cl
    L_0045adf0:
        mov ebx,dword ptr [ebp+8]
    L_0045adf3:
        mov ebx,dword ptr [ebx+48h]
    L_0045adf6:
        test byte ptr [ebx+edx*2+1],80h
    L_0045adfb:
        je short L_0045ae14
    L_0045adfd:
        cmp dword ptr [edi],1
    L_0045ae00:
        jbe short L_0045ae14
    L_0045ae02:
        inc eax
    L_0045ae03:
        cmp byte ptr [eax],0
    L_0045ae06:
        je asm_target_0045aece
    L_0045ae0c:
        mov edx,dword ptr [esi]
    L_0045ae0e:
        mov byte ptr [edx],cl
    L_0045ae10:
        inc dword ptr [esi]
    L_0045ae12:
        dec dword ptr [edi]
    L_0045ae14:
        mov ecx,dword ptr [esi]
    L_0045ae16:
        mov al,byte ptr [eax]
    L_0045ae18:
        mov byte ptr [ecx],al
    L_0045ae1a:
        inc dword ptr [esi]
    L_0045ae1c:
        dec dword ptr [edi]
    L_0045ae1e:
        jmp short L_0045ae5d
    L_0045ae20:
        cmp dword ptr [edi],0
    L_0045ae23:
        jbe short L_0045ae5d
    L_0045ae25:
        movzx edx,cl
    L_0045ae28:
        mov ebx,dword ptr [ebp+8]
    L_0045ae2b:
        mov ebx,dword ptr [ebx+48h]
    L_0045ae2e:
        test byte ptr [ebx+edx*2+1],80h
    L_0045ae33:
        je short L_0045ae4c
    L_0045ae35:
        cmp dword ptr [edi],1
    L_0045ae38:
        jbe short L_0045ae4c
    L_0045ae3a:
        inc eax
    L_0045ae3b:
        cmp byte ptr [eax],0
    L_0045ae3e:
        je asm_target_0045aece
    L_0045ae44:
        mov edx,dword ptr [esi]
    L_0045ae46:
        mov byte ptr [edx],cl
    L_0045ae48:
        inc dword ptr [esi]
    L_0045ae4a:
        dec dword ptr [edi]
    L_0045ae4c:
        mov ecx,dword ptr [esi]
    L_0045ae4e:
        mov dl,byte ptr [eax]
    L_0045ae50:
        mov byte ptr [ecx],dl
    L_0045ae52:
        inc dword ptr [esi]
    L_0045ae54:
        inc eax
    L_0045ae55:
        dec dword ptr [edi]
    L_0045ae57:
        mov cl,byte ptr [eax]
    L_0045ae59:
        test cl,cl
    L_0045ae5b:
        jne short L_0045ae20
    L_0045ae5d:
        mov eax,dword ptr [ebp-24h]
    L_0045ae60:
        mov dword ptr [ebp-20h],eax
    L_0045ae63:
        jmp asm_target_0045af0b
    L_0045ae68:
        mov ecx,edx
    L_0045ae6a:
        dec ecx
    L_0045ae6b:
        je short L_0045ae72
    L_0045ae6d:
        dec ecx
    L_0045ae6e:
        je short L_0045ae79
    L_0045ae70:
        jmp short L_0045aeab
    L_0045ae72:
        mov dword ptr [ebp-28h],1
    L_0045ae79:
        mov byte ptr [ebp-19h],53h
    L_0045ae7d:
        jmp short L_0045aeab
    L_0045ae7f:
        mov ecx,edx
    L_0045ae81:
        dec ecx
    L_0045ae82:
        je short L_0045ae89
    L_0045ae84:
        dec ecx
    L_0045ae85:
        je short L_0045ae90
    L_0045ae87:
        jmp short L_0045aeab
    L_0045ae89:
        mov dword ptr [ebp-28h],1
    L_0045ae90:
        mov byte ptr [ebp-19h],4Dh
    L_0045ae94:
        jmp short L_0045aeab
    L_0045ae96:
        mov ecx,edx
    L_0045ae98:
        dec ecx
    L_0045ae99:
        je short L_0045aea0
    L_0045ae9b:
        dec ecx
    L_0045ae9c:
        je short L_0045aea7
    L_0045ae9e:
        jmp short L_0045aeab
    L_0045aea0:
        mov dword ptr [ebp-28h],1
    L_0045aea7:
        mov byte ptr [ebp-19h],49h
    L_0045aeab:
        mov al,byte ptr [ebp-19h]
    L_0045aeae:
        test al,al
    L_0045aeb0:
        je short L_0045aed5
    L_0045aeb2:
        push dword ptr [ebp-28h]
    L_0045aeb5:
        push dword ptr [ebp+1Ch]
    L_0045aeb8:
        push dword ptr [ebp+10h]
    L_0045aebb:
        push dword ptr [ebp+8]
    L_0045aebe:
        mov ebx,edi
    L_0045aec0:
        mov ecx,esi
    L_0045aec2:
        call asm_expandtime_0045a82d
    L_0045aec7:
        add esp,10h
    L_0045aeca:
        test eax,eax
    L_0045aecc:
        jne short L_0045ae5d
    L_0045aece:
        xor eax,eax
    L_0045aed0:
        jmp asm_target_0045abe7
    L_0045aed5:
        mov ecx,dword ptr [ebp-20h]
    L_0045aed8:
        mov al,byte ptr [ecx]
    L_0045aeda:
        movzx edx,al
    L_0045aedd:
        mov ebx,dword ptr [ebp+8]
    L_0045aee0:
        mov ebx,dword ptr [ebx+48h]
    L_0045aee3:
        test byte ptr [ebx+edx*2+1],80h
    L_0045aee8:
        je short L_0045aefd
    L_0045aeea:
        cmp dword ptr [edi],1
    L_0045aeed:
        jbe short L_0045aefd
    L_0045aeef:
        inc ecx
    L_0045aef0:
        cmp byte ptr [ecx],0
    L_0045aef3:
        je short L_0045aece
    L_0045aef5:
        mov edx,dword ptr [esi]
    L_0045aef7:
        mov byte ptr [edx],al
    L_0045aef9:
        inc dword ptr [esi]
    L_0045aefb:
        dec dword ptr [edi]
    L_0045aefd:
        mov eax,dword ptr [esi]
    L_0045aeff:
        mov dl,byte ptr [ecx]
    L_0045af01:
        mov byte ptr [eax],dl
    L_0045af03:
        inc dword ptr [esi]
    L_0045af05:
        inc ecx
    L_0045af06:
        mov dword ptr [ebp-20h],ecx
    L_0045af09:
        dec dword ptr [edi]
    L_0045af0b:
        mov eax,dword ptr [ebp-20h]
    L_0045af0e:
        mov cl,byte ptr [eax]
    L_0045af10:
        test cl,cl
    L_0045af12:
        jne asm_target_0045ac04
    L_0045af18:
        jmp asm_target_0045abe4
    }
}
