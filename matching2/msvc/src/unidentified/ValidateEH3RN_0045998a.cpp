#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045998A..0x00459BB2: __ValidateEH3RN
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ValidateEH3RN_0045998a() {
    __asm {
    L_0045998a:
        push ebp
    L_0045998b:
        mov ebp,esp
    L_0045998d:
        sub esp,20h
    L_00459990:
        push ebx
    L_00459991:
        push esi
    L_00459992:
        mov esi,dword ptr [ebp+8]
    L_00459995:
        mov ebx,dword ptr [esi+8]
    L_00459998:
        test bl,3
    L_0045999b:
        jne short L_004599b8
    L_0045999d:
        mov eax,dword ptr fs:[18h]
    L_004599a3:
        mov dword ptr [ebp+8],eax
    L_004599a6:
        mov eax,dword ptr [ebp+8]
    L_004599a9:
        mov ecx,dword ptr [eax+8]
    L_004599ac:
        cmp ebx,ecx
    L_004599ae:
        mov dword ptr [ebp-4],ecx
    L_004599b1:
        jb short L_004599bf
    L_004599b3:
        cmp ebx,dword ptr [eax+4]
    L_004599b6:
        jae short L_004599bf
    L_004599b8:
        xor eax,eax
    L_004599ba:
        jmp asm_target_00459baf
    L_004599bf:
        push edi
    L_004599c0:
        mov edi,dword ptr [esi+0Ch]
    L_004599c3:
        cmp edi,0FFFFFFFFh
    L_004599c6:
        jne short L_004599d0
    L_004599c8:
        xor eax,eax
    L_004599ca:
        inc eax
    L_004599cb:
        jmp asm_target_00459bae
    L_004599d0:
        xor edx,edx
    L_004599d2:
        mov dword ptr [ebp+8],edx
    L_004599d5:
        mov eax,ebx
    L_004599d7:
        mov ecx,dword ptr [eax]
    L_004599d9:
        cmp ecx,0FFFFFFFFh
    L_004599dc:
        je short L_004599e6
    L_004599de:
        cmp ecx,edx
    L_004599e0:
        jae asm_target_00459b2b
    L_004599e6:
        cmp dword ptr [eax+4],0
    L_004599ea:
        je short L_004599ef
    L_004599ec:
        inc dword ptr [ebp+8]
    L_004599ef:
        inc edx
    L_004599f0:
        add eax,0Ch
    L_004599f3:
        cmp edx,edi
    L_004599f5:
        jbe short L_004599d7
    L_004599f7:
        cmp dword ptr [ebp+8],0
    L_004599fb:
        je short L_00459a11
    L_004599fd:
        mov eax,dword ptr [esi-8]
    L_00459a00:
        cmp eax,dword ptr [ebp-4]
    L_00459a03:
        jb asm_target_00459b2b
    L_00459a09:
        cmp eax,esi
    L_00459a0b:
        jae asm_target_00459b2b
    L_00459a11:
        mov eax,dword ptr [data_004775c8]
    L_00459a16:
        mov edi,ebx
    L_00459a18:
        and edi,0FFFFF000h
    L_00459a1e:
        xor esi,esi
    L_00459a20:
        test eax,eax
    L_00459a22:
        jle short L_00459a36
    L_00459a24:
        cmp dword ptr [esi*4+4775D0h],edi
    L_00459a2b:
        je asm_target_00459b2f
    L_00459a31:
        inc esi
    L_00459a32:
        cmp esi,eax
    L_00459a34:
        jl short L_00459a24
    L_00459a36:
        push 1Ch
    L_00459a38:
        lea eax,[ebp-20h]
    L_00459a3b:
        push eax
    L_00459a3c:
        push ebx
    L_00459a3d:
        call dword ptr [data_0046609c]
    L_00459a43:
        test eax,eax
    L_00459a45:
        je asm_target_00459bab
    L_00459a4b:
        cmp dword ptr [ebp-8],1000000h
    L_00459a52:
        jne asm_target_00459bab
    L_00459a58:
        test byte ptr [ebp-0Ch],0CCh
    L_00459a5c:
        je short L_00459ab4
    L_00459a5e:
        mov ecx,dword ptr [ebp-1Ch]
    L_00459a61:
        cmp word ptr [ecx],5A4Dh
    L_00459a66:
        jne asm_target_00459bab
    L_00459a6c:
        mov eax,dword ptr [ecx+3Ch]
    L_00459a6f:
        add eax,ecx
    L_00459a71:
        cmp dword ptr [eax],4550h
    L_00459a77:
        jne asm_target_00459bab
    L_00459a7d:
        cmp word ptr [eax+18h],10Bh
    L_00459a83:
        jne asm_target_00459bab
    L_00459a89:
        sub ebx,ecx
    L_00459a8b:
        cmp word ptr [eax+6],0
    L_00459a90:
        movzx ecx,word ptr [eax+14h]
    L_00459a94:
        lea ecx,[ecx+eax+18h]
    L_00459a98:
        jbe asm_target_00459bab
    L_00459a9e:
        mov eax,dword ptr [ecx+0Ch]
    L_00459aa1:
        cmp ebx,eax
    L_00459aa3:
        jb short L_00459ab4
    L_00459aa5:
        mov edx,dword ptr [ecx+8]
    L_00459aa8:
        add edx,eax
    L_00459aaa:
        cmp ebx,edx
    L_00459aac:
        jae short L_00459ab4
    L_00459aae:
        test byte ptr [ecx+27h],80h
    L_00459ab2:
        jne short L_00459b2b
    L_00459ab4:
        push 1
    L_00459ab6:
        push 477610h
    L_00459abb:
        call dword ptr [data_00466078]
    L_00459ac1:
        test eax,eax
    L_00459ac3:
        jne asm_target_004599c8
    L_00459ac9:
        mov ecx,dword ptr [data_004775c8]
    L_00459acf:
        test ecx,ecx
    L_00459ad1:
        mov edx,ecx
    L_00459ad3:
        jle short L_00459ae8
    L_00459ad5:
        lea eax,[ecx*4+4775CCh]
    L_00459adc:
        cmp dword ptr [eax],edi
    L_00459ade:
        je short L_00459ae8
    L_00459ae0:
        dec edx
    L_00459ae1:
        sub eax,4
    L_00459ae4:
        test edx,edx
    L_00459ae6:
        jg short L_00459adc
    L_00459ae8:
        test edx,edx
    L_00459aea:
        jne short L_00459b19
    L_00459aec:
        push 0Fh
    L_00459aee:
        pop ebx
    L_00459aef:
        cmp ecx,ebx
    L_00459af1:
        jg short L_00459af5
    L_00459af3:
        mov ebx,ecx
    L_00459af5:
        xor edx,edx
    L_00459af7:
        test ebx,ebx
    L_00459af9:
        jl short L_00459b0d
    L_00459afb:
        lea eax,[edx*4+4775D0h]
    L_00459b02:
        mov esi,dword ptr [eax]
    L_00459b04:
        inc edx
    L_00459b05:
        cmp edx,ebx
    L_00459b07:
        mov dword ptr [eax],edi
    L_00459b09:
        mov edi,esi
    L_00459b0b:
        jle short L_00459afb
    L_00459b0d:
        cmp ecx,10h
    L_00459b10:
        jge short L_00459b19
    L_00459b12:
        inc ecx
    L_00459b13:
        mov dword ptr [data_004775c8],ecx
    L_00459b19:
        push 0
    L_00459b1b:
        push 477610h
    L_00459b20:
        call dword ptr [data_00466078]
    L_00459b26:
        jmp asm_target_004599c8
    L_00459b2b:
        xor eax,eax
    L_00459b2d:
        jmp short L_00459bae
    L_00459b2f:
        test esi,esi
    L_00459b31:
        jle asm_target_004599c8
    L_00459b37:
        mov ebx,dword ptr [data_00466078]
    L_00459b3d:
        push 1
    L_00459b3f:
        push 477610h
    L_00459b44:
        call ebx
    L_00459b46:
        test eax,eax
    L_00459b48:
        jne asm_target_004599c8
    L_00459b4e:
        cmp dword ptr [esi*4+4775D0h],edi
    L_00459b55:
        je short L_00459b85
    L_00459b57:
        mov eax,dword ptr [data_004775c8]
    L_00459b5c:
        lea esi,[eax-1]
    L_00459b5f:
        test esi,esi
    L_00459b61:
        jl short L_00459b73
    L_00459b63:
        cmp dword ptr [esi*4+4775D0h],edi
    L_00459b6a:
        je short L_00459b6f
    L_00459b6c:
        dec esi
    L_00459b6d:
        jns short L_00459b63
    L_00459b6f:
        test esi,esi
    L_00459b71:
        jge short L_00459b83
    L_00459b73:
        cmp eax,10h
    L_00459b76:
        jge short L_00459b7e
    L_00459b78:
        inc eax
    L_00459b79:
        mov dword ptr [data_004775c8],eax
    L_00459b7e:
        lea esi,[eax-1]
    L_00459b81:
        jmp short L_00459b85
    L_00459b83:
        je short L_00459b9d
    L_00459b85:
        xor ecx,ecx
    L_00459b87:
        test esi,esi
    L_00459b89:
        jl short L_00459b9d
    L_00459b8b:
        lea eax,[ecx*4+4775D0h]
    L_00459b92:
        mov edx,dword ptr [eax]
    L_00459b94:
        inc ecx
    L_00459b95:
        cmp ecx,esi
    L_00459b97:
        mov dword ptr [eax],edi
    L_00459b99:
        mov edi,edx
    L_00459b9b:
        jle short L_00459b8b
    L_00459b9d:
        push 0
    L_00459b9f:
        push 477610h
    L_00459ba4:
        call ebx
    L_00459ba6:
        jmp asm_target_004599c8
    L_00459bab:
        or eax,0FFFFFFFFh
    L_00459bae:
        pop edi
    L_00459baf:
        pop esi
    L_00459bb0:
        pop ebx
    L_00459bb1:
        leave
    L_00459bb2:
        ret
    }
}
