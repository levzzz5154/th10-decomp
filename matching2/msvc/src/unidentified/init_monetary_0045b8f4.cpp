#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045B8F4..0x0045BB32: ___init_monetary
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_init_monetary_0045b8f4() {
    __asm {
    L_0045b8f4:
        push ebp
    L_0045b8f5:
        mov ebp,esp
    L_0045b8f7:
        push ecx
    L_0045b8f8:
        push ebx
    L_0045b8f9:
        push esi
    L_0045b8fa:
        xor esi,esi
    L_0045b8fc:
        cmp dword ptr [data_00477658],esi
    L_0045b902:
        push edi
    L_0045b903:
        jne short L_0045b92e
    L_0045b905:
        cmp dword ptr [data_0047765c],esi
    L_0045b90b:
        jne short L_0045b92e
    L_0045b90d:
        mov dword ptr [data_004981c8],esi
    L_0045b913:
        mov dword ptr [data_004981cc],esi
    L_0045b919:
        mov dword ptr [data_00473ad4],473AA4h
    L_0045b923:
        mov dword ptr [data_00477624],esi
    L_0045b929:
        jmp asm_target_0045bb2c
    L_0045b92e:
        push 30h
    L_0045b930:
        push 1
    L_0045b932:
        call asm_FUN_0045794d_0045794d
    L_0045b937:
        mov ebx,eax
    L_0045b939:
        cmp ebx,esi
    L_0045b93b:
        pop ecx
    L_0045b93c:
        pop ecx
    L_0045b93d:
        je asm_target_0045baac
    L_0045b943:
        push 4
    L_0045b945:
        call asm_malloc_00452706
    L_0045b94a:
        mov edi,eax
    L_0045b94c:
        cmp edi,esi
    L_0045b94e:
        pop ecx
    L_0045b94f:
        mov dword ptr [ebp-4],edi
    L_0045b952:
        jne short L_0045b960
    L_0045b954:
        push ebx
    L_0045b955:
        call asm_free_00452422
    L_0045b95a:
        pop ecx
    L_0045b95b:
        jmp asm_target_0045baac
    L_0045b960:
        mov dword ptr [edi],esi
    L_0045b962:
        cmp dword ptr [data_00477658],esi
    L_0045b968:
        je asm_target_0045bae6
    L_0045b96e:
        push 4
    L_0045b970:
        call asm_malloc_00452706
    L_0045b975:
        cmp eax,esi
    L_0045b977:
        pop ecx
    L_0045b978:
        mov dword ptr [data_004981c8],eax
    L_0045b97d:
        jne short L_0045b98e
    L_0045b97f:
        push ebx
    L_0045b980:
        call asm_free_00452422
    L_0045b985:
        push edi
    L_0045b986:
        call asm_free_00452422
    L_0045b98b:
        pop ecx
    L_0045b98c:
        jmp short L_0045b95a
    L_0045b98e:
        mov dword ptr [eax],esi
    L_0045b990:
        movzx esi,word ptr [data_00477680]
    L_0045b997:
        lea eax,[ebx+0Ch]
    L_0045b99a:
        push eax
    L_0045b99b:
        push 15h
    L_0045b99d:
        push esi
    L_0045b99e:
        push 1
    L_0045b9a0:
        call asm_FUN_0046041e_0046041e
    L_0045b9a5:
        mov edi,eax
    L_0045b9a7:
        lea eax,[ebx+10h]
    L_0045b9aa:
        push eax
    L_0045b9ab:
        push 14h
    L_0045b9ad:
        push esi
    L_0045b9ae:
        push 1
    L_0045b9b0:
        call asm_FUN_0046041e_0046041e
    L_0045b9b5:
        or edi,eax
    L_0045b9b7:
        lea eax,[ebx+14h]
    L_0045b9ba:
        push eax
    L_0045b9bb:
        push 16h
    L_0045b9bd:
        push esi
    L_0045b9be:
        push 1
    L_0045b9c0:
        call asm_FUN_0046041e_0046041e
    L_0045b9c5:
        or edi,eax
    L_0045b9c7:
        lea eax,[ebx+18h]
    L_0045b9ca:
        push eax
    L_0045b9cb:
        push 17h
    L_0045b9cd:
        push esi
    L_0045b9ce:
        push 1
    L_0045b9d0:
        call asm_FUN_0046041e_0046041e
    L_0045b9d5:
        add esp,40h
    L_0045b9d8:
        or edi,eax
    L_0045b9da:
        lea eax,[ebx+1Ch]
    L_0045b9dd:
        push eax
    L_0045b9de:
        push 18h
    L_0045b9e0:
        push esi
    L_0045b9e1:
        push 1
    L_0045b9e3:
        call asm_FUN_0046041e_0046041e
    L_0045b9e8:
        or edi,eax
    L_0045b9ea:
        lea eax,[ebx+20h]
    L_0045b9ed:
        push eax
    L_0045b9ee:
        push 50h
    L_0045b9f0:
        push esi
    L_0045b9f1:
        push 1
    L_0045b9f3:
        call asm_FUN_0046041e_0046041e
    L_0045b9f8:
        or edi,eax
    L_0045b9fa:
        lea eax,[ebx+24h]
    L_0045b9fd:
        push eax
    L_0045b9fe:
        push 51h
    L_0045ba00:
        push esi
    L_0045ba01:
        push 1
    L_0045ba03:
        call asm_FUN_0046041e_0046041e
    L_0045ba08:
        or edi,eax
    L_0045ba0a:
        lea eax,[ebx+28h]
    L_0045ba0d:
        push eax
    L_0045ba0e:
        push 1Ah
    L_0045ba10:
        push esi
    L_0045ba11:
        push 0
    L_0045ba13:
        call asm_FUN_0046041e_0046041e
    L_0045ba18:
        add esp,40h
    L_0045ba1b:
        or edi,eax
    L_0045ba1d:
        lea eax,[ebx+29h]
    L_0045ba20:
        push eax
    L_0045ba21:
        push 19h
    L_0045ba23:
        push esi
    L_0045ba24:
        push 0
    L_0045ba26:
        call asm_FUN_0046041e_0046041e
    L_0045ba2b:
        or edi,eax
    L_0045ba2d:
        lea eax,[ebx+2Ah]
    L_0045ba30:
        push eax
    L_0045ba31:
        push 54h
    L_0045ba33:
        push esi
    L_0045ba34:
        push 0
    L_0045ba36:
        call asm_FUN_0046041e_0046041e
    L_0045ba3b:
        or edi,eax
    L_0045ba3d:
        lea eax,[ebx+2Bh]
    L_0045ba40:
        push eax
    L_0045ba41:
        push 55h
    L_0045ba43:
        push esi
    L_0045ba44:
        push 0
    L_0045ba46:
        call asm_FUN_0046041e_0046041e
    L_0045ba4b:
        or edi,eax
    L_0045ba4d:
        lea eax,[ebx+2Ch]
    L_0045ba50:
        push eax
    L_0045ba51:
        push 56h
    L_0045ba53:
        push esi
    L_0045ba54:
        push 0
    L_0045ba56:
        call asm_FUN_0046041e_0046041e
    L_0045ba5b:
        add esp,40h
    L_0045ba5e:
        or edi,eax
    L_0045ba60:
        lea eax,[ebx+2Dh]
    L_0045ba63:
        push eax
    L_0045ba64:
        push 57h
    L_0045ba66:
        push esi
    L_0045ba67:
        push 0
    L_0045ba69:
        call asm_FUN_0046041e_0046041e
    L_0045ba6e:
        or edi,eax
    L_0045ba70:
        lea eax,[ebx+2Eh]
    L_0045ba73:
        push eax
    L_0045ba74:
        push 52h
    L_0045ba76:
        push esi
    L_0045ba77:
        push 0
    L_0045ba79:
        call asm_FUN_0046041e_0046041e
    L_0045ba7e:
        or edi,eax
    L_0045ba80:
        lea eax,[ebx+2Fh]
    L_0045ba83:
        push eax
    L_0045ba84:
        push 53h
    L_0045ba86:
        push esi
    L_0045ba87:
        push 0
    L_0045ba89:
        call asm_FUN_0046041e_0046041e
    L_0045ba8e:
        add esp,30h
    L_0045ba91:
        or eax,edi
    L_0045ba93:
        je short L_0045bab1
    L_0045ba95:
        push ebx
    L_0045ba96:
        call asm_free_lconv_mon_0045b81b
    L_0045ba9b:
        push ebx
    L_0045ba9c:
        call asm_free_00452422
    L_0045baa1:
        push dword ptr [ebp-4]
    L_0045baa4:
        call asm_free_00452422
    L_0045baa9:
        add esp,0Ch
    L_0045baac:
        xor eax,eax
    L_0045baae:
        inc eax
    L_0045baaf:
        jmp short L_0045bb2e
    L_0045bab1:
        mov eax,dword ptr [ebx+1Ch]
    L_0045bab4:
        jmp short L_0045bac8
    L_0045bab6:
        mov cl,byte ptr [eax]
    L_0045bab8:
        cmp cl,30h
    L_0045babb:
        jl short L_0045bacf
    L_0045babd:
        cmp cl,39h
    L_0045bac0:
        jg short L_0045bacf
    L_0045bac2:
        sub cl,30h
    L_0045bac5:
        mov byte ptr [eax],cl
    L_0045bac7:
        inc eax
    L_0045bac8:
        cmp byte ptr [eax],0
    L_0045bacb:
        jne short L_0045bab6
    L_0045bacd:
        jmp short L_0045baf9
    L_0045bacf:
        cmp cl,3Bh
    L_0045bad2:
        jne short L_0045bac7
    L_0045bad4:
        mov esi,eax
    L_0045bad6:
        lea edi,[esi+1]
    L_0045bad9:
        mov cl,byte ptr [edi]
    L_0045badb:
        mov byte ptr [esi],cl
    L_0045badd:
        mov esi,edi
    L_0045badf:
        cmp byte ptr [esi],0
    L_0045bae2:
        jne short L_0045bad6
    L_0045bae4:
        jmp short L_0045bac8
    L_0045bae6:
        push 0Ch
    L_0045bae8:
        pop ecx
    L_0045bae9:
        mov esi,473AA4h
    L_0045baee:
        mov edi,ebx
    L_0045baf0:
        rep movsd
    L_0045baf2:
        and dword ptr [data_004981c8],0
    L_0045baf9:
        mov eax,dword ptr [data_00473ad4]
    L_0045bafe:
        mov eax,dword ptr [eax]
    L_0045bb00:
        mov dword ptr [ebx],eax
    L_0045bb02:
        mov eax,dword ptr [data_00473ad4]
    L_0045bb07:
        mov eax,dword ptr [eax+4]
    L_0045bb0a:
        mov dword ptr [ebx+4],eax
    L_0045bb0d:
        mov eax,dword ptr [data_00473ad4]
    L_0045bb12:
        mov eax,dword ptr [eax+8]
    L_0045bb15:
        mov dword ptr [ebx+8],eax
    L_0045bb18:
        mov eax,dword ptr [ebp-4]
    L_0045bb1b:
        mov dword ptr [data_00473ad4],ebx
    L_0045bb21:
        mov dword ptr [data_004981cc],eax
    L_0045bb26:
        mov dword ptr [data_00477624],ebx
    L_0045bb2c:
        xor eax,eax
    L_0045bb2e:
        pop edi
    L_0045bb2f:
        pop esi
    L_0045bb30:
        pop ebx
    L_0045bb31:
        leave
    L_0045bb32:
        ret
    }
}
