#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046095A..0x00460B8F: FUN_0046095a
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046095a_0046095a() {
    __asm {
    L_0046095a:
        push ebp
    L_0046095b:
        mov ebp,esp
    L_0046095d:
        sub esp,30h
    L_00460960:
        mov eax,dword ptr [data_00473660]
    L_00460965:
        xor eax,ebp
    L_00460967:
        push ebx
    L_00460968:
        mov ebx,dword ptr [ebp+0Ch]
    L_0046096b:
        mov dword ptr [ebp-4],eax
    L_0046096e:
        xor eax,eax
    L_00460970:
        xor ecx,ecx
    L_00460972:
        mov cx,word ptr [ebx+0Ah]
    L_00460976:
        push esi
    L_00460977:
        mov esi,dword ptr [ebp+8]
    L_0046097a:
        mov dword ptr [ebp-24h],eax
    L_0046097d:
        mov dword ptr [ebp-10h],eax
    L_00460980:
        mov dword ptr [ebp-0Ch],eax
    L_00460983:
        mov dword ptr [ebp-8],eax
    L_00460986:
        mov ax,word ptr [esi+0Ah]
    L_0046098a:
        push edi
    L_0046098b:
        mov edi,ecx
    L_0046098d:
        mov edx,7FFFh
    L_00460992:
        and ecx,edx
    L_00460994:
        xor edi,eax
    L_00460996:
        and eax,edx
    L_00460998:
        and edi,8000h
    L_0046099e:
        cmp ax,7FFFh
    L_004609a2:
        lea edx,[ecx+eax]
    L_004609a5:
        mov dword ptr [ebp-14h],edx
    L_004609a8:
        jae asm_target_00460b66
    L_004609ae:
        cmp cx,7FFFh
    L_004609b3:
        jae asm_target_00460b66
    L_004609b9:
        cmp dx,0BFFDh
    L_004609be:
        ja asm_target_00460b66
    L_004609c4:
        cmp dx,3FBFh
    L_004609c9:
        ja short L_004609cf
    L_004609cb:
        xor eax,eax
    L_004609cd:
        jmp short L_00460a09
    L_004609cf:
        test ax,ax
    L_004609d2:
        mov edx,7FFFFFFFh
    L_004609d7:
        jne short L_004609f1
    L_004609d9:
        inc dword ptr [ebp-14h]
    L_004609dc:
        xor eax,eax
    L_004609de:
        test dword ptr [esi+8],edx
    L_004609e1:
        jne short L_004609f3
    L_004609e3:
        cmp dword ptr [esi+4],eax
    L_004609e6:
        jne short L_004609f3
    L_004609e8:
        cmp dword ptr [esi],eax
    L_004609ea:
        jne short L_004609f3
    L_004609ec:
        jmp asm_target_00460b60
    L_004609f1:
        xor eax,eax
    L_004609f3:
        cmp cx,ax
    L_004609f6:
        jne short L_00460a16
    L_004609f8:
        inc dword ptr [ebp-14h]
    L_004609fb:
        test dword ptr [ebx+8],edx
    L_004609fe:
        jne short L_00460a16
    L_00460a00:
        cmp dword ptr [ebx+4],eax
    L_00460a03:
        jne short L_00460a16
    L_00460a05:
        cmp dword ptr [ebx],eax
    L_00460a07:
        jne short L_00460a16
    L_00460a09:
        mov dword ptr [esi+8],eax
    L_00460a0c:
        mov dword ptr [esi+4],eax
    L_00460a0f:
        mov dword ptr [esi],eax
    L_00460a11:
        jmp asm_target_00460b81
    L_00460a16:
        mov dword ptr [ebp-2Ch],eax
    L_00460a19:
        lea eax,[ebp-0Ch]
    L_00460a1c:
        mov dword ptr [ebp-1Ch],eax
    L_00460a1f:
        mov dword ptr [ebp-18h],5
    L_00460a26:
        mov eax,dword ptr [ebp-2Ch]
    L_00460a29:
        add eax,eax
    L_00460a2b:
        cmp dword ptr [ebp-18h],0
    L_00460a2f:
        jle short L_00460a7a
    L_00460a31:
        add eax,esi
    L_00460a33:
        mov dword ptr [ebp-28h],eax
    L_00460a36:
        lea eax,[ebx+8]
    L_00460a39:
        mov dword ptr [ebp-20h],eax
    L_00460a3c:
        mov eax,dword ptr [ebp-18h]
    L_00460a3f:
        mov dword ptr [ebp-30h],eax
    L_00460a42:
        mov eax,dword ptr [ebp-20h]
    L_00460a45:
        mov ecx,dword ptr [ebp-28h]
    L_00460a48:
        movzx ecx,word ptr [ecx]
    L_00460a4b:
        movzx eax,word ptr [eax]
    L_00460a4e:
        imul eax,ecx
    L_00460a51:
        mov ecx,dword ptr [ebp-1Ch]
    L_00460a54:
        add ecx,0FFFFFFFCh
    L_00460a57:
        push ecx
    L_00460a58:
        push eax
    L_00460a59:
        push dword ptr [ecx]
    L_00460a5b:
        call asm_addl_00460798
    L_00460a60:
        add esp,0Ch
    L_00460a63:
        test eax,eax
    L_00460a65:
        je short L_00460a6d
    L_00460a67:
        mov eax,dword ptr [ebp-1Ch]
    L_00460a6a:
        inc word ptr [eax]
    L_00460a6d:
        add dword ptr [ebp-28h],2
    L_00460a71:
        sub dword ptr [ebp-20h],2
    L_00460a75:
        dec dword ptr [ebp-30h]
    L_00460a78:
        jne short L_00460a42
    L_00460a7a:
        add dword ptr [ebp-1Ch],2
    L_00460a7e:
        inc dword ptr [ebp-2Ch]
    L_00460a81:
        dec dword ptr [ebp-18h]
    L_00460a84:
        cmp dword ptr [ebp-18h],0
    L_00460a88:
        jg short L_00460a26
    L_00460a8a:
        add dword ptr [ebp-14h],0C002h
    L_00460a91:
        cmp word ptr [ebp-14h],0
    L_00460a96:
        jle short L_00460abd
    L_00460a98:
        test byte ptr [ebp-5],80h
    L_00460a9c:
        jne short L_00460ab6
    L_00460a9e:
        lea eax,[ebp-10h]
    L_00460aa1:
        push eax
    L_00460aa2:
        call asm_shl_12_00460817
    L_00460aa7:
        add dword ptr [ebp-14h],0FFFFh
    L_00460aae:
        cmp word ptr [ebp-14h],0
    L_00460ab3:
        pop ecx
    L_00460ab4:
        jg short L_00460a98
    L_00460ab6:
        cmp word ptr [ebp-14h],0
    L_00460abb:
        jg short L_00460af6
    L_00460abd:
        add dword ptr [ebp-14h],0FFFFh
    L_00460ac4:
        cmp word ptr [ebp-14h],0
    L_00460ac9:
        jge short L_00460af6
    L_00460acb:
        mov eax,dword ptr [ebp-14h]
    L_00460ace:
        neg eax
    L_00460ad0:
        movzx ebx,ax
    L_00460ad3:
        add dword ptr [ebp-14h],ebx
    L_00460ad6:
        test byte ptr [ebp-10h],1
    L_00460ada:
        je short L_00460adf
    L_00460adc:
        inc dword ptr [ebp-24h]
    L_00460adf:
        lea eax,[ebp-10h]
    L_00460ae2:
        push eax
    L_00460ae3:
        call asm_shr_12_00460845
    L_00460ae8:
        dec ebx
    L_00460ae9:
        pop ecx
    L_00460aea:
        jne short L_00460ad6
    L_00460aec:
        cmp dword ptr [ebp-24h],0
    L_00460af0:
        je short L_00460af6
    L_00460af2:
        or byte ptr [ebp-10h],1
    L_00460af6:
        cmp word ptr [ebp-10h],8000h
    L_00460afc:
        ja short L_00460b0d
    L_00460afe:
        mov eax,dword ptr [ebp-10h]
    L_00460b01:
        and eax,1FFFFh
    L_00460b06:
        cmp eax,18000h
    L_00460b0b:
        jne short L_00460b42
    L_00460b0d:
        cmp dword ptr [ebp-0Eh],0FFFFFFFFh
    L_00460b11:
        jne short L_00460b3f
    L_00460b13:
        and dword ptr [ebp-0Eh],0
    L_00460b17:
        cmp dword ptr [ebp-0Ah],0FFFFFFFFh
    L_00460b1b:
        jne short L_00460b3a
    L_00460b1d:
        and dword ptr [ebp-0Ah],0
    L_00460b21:
        TH10_CMP_EBP_DISP8_IMM16(-6, 0xffff)
    L_00460b27:
        jne short L_00460b34
    L_00460b29:
        inc dword ptr [ebp-14h]
    L_00460b2c:
        mov word ptr [ebp-6],8000h
    L_00460b32:
        jmp short L_00460b42
    L_00460b34:
        inc word ptr [ebp-6]
    L_00460b38:
        jmp short L_00460b42
    L_00460b3a:
        inc dword ptr [ebp-0Ah]
    L_00460b3d:
        jmp short L_00460b42
    L_00460b3f:
        inc dword ptr [ebp-0Eh]
    L_00460b42:
        mov eax,dword ptr [ebp-14h]
    L_00460b45:
        cmp ax,7FFFh
    L_00460b49:
        jae short L_00460b66
    L_00460b4b:
        mov cx,word ptr [ebp-0Eh]
    L_00460b4f:
        mov word ptr [esi],cx
    L_00460b52:
        mov ecx,dword ptr [ebp-0Ch]
    L_00460b55:
        mov dword ptr [esi+2],ecx
    L_00460b58:
        mov ecx,dword ptr [ebp-8]
    L_00460b5b:
        mov dword ptr [esi+6],ecx
    L_00460b5e:
        or eax,edi
    L_00460b60:
        mov word ptr [esi+0Ah],ax
    L_00460b64:
        jmp short L_00460b81
    L_00460b66:
        neg di
    L_00460b69:
        sbb edi,edi
    L_00460b6b:
        and dword ptr [esi+4],0
    L_00460b6f:
        and edi,80000000h
    L_00460b75:
        add edi,7FFF8000h
    L_00460b7b:
        and dword ptr [esi],0
    L_00460b7e:
        mov dword ptr [esi+8],edi
    L_00460b81:
        mov ecx,dword ptr [ebp-4]
    L_00460b84:
        pop edi
    L_00460b85:
        pop esi
    L_00460b86:
        xor ecx,ebp
    L_00460b88:
        pop ebx
    L_00460b89:
        call asm_security_check_cookie_00458ea5
    L_00460b8e:
        leave
    L_00460b8f:
        ret
    }
}
