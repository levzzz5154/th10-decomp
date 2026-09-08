#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043B8D0..0x0043BA86: FUN_0043b8d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043b8d0_0043b8d0() {
    __asm {
    L_0043b8d0:
        push esi
    L_0043b8d1:
        mov esi,eax
    L_0043b8d3:
        mov eax,dword ptr [esi+48h]
    L_0043b8d6:
        push 0FFFFFFFAh
    L_0043b8d8:
        push eax
    L_0043b8d9:
        call dword ptr [data_0046621c]
    L_0043b8df:
        test byte ptr [esi+150h],8
    L_0043b8e6:
        je short L_0043b8ed
    L_0043b8e8:
        or eax,0FFFFFFFFh
    L_0043b8eb:
        pop esi
    L_0043b8ec:
        ret
    L_0043b8ed:
        push ebx
    L_0043b8ee:
        push 0
    L_0043b8f0:
        lea ebx,[esi+0Ch]
    L_0043b8f3:
        push ebx
    L_0043b8f4:
        push 467AACh
    L_0043b8f9:
        push 800h
    L_0043b8fe:
        push eax
    L_0043b8ff:
        call asm_DirectInput8Create_0045071e
    L_0043b904:
        test eax,eax
    L_0043b906:
        jge short L_0043b926
    L_0043b908:
        push 46F9E0h
    L_0043b90d:
        mov ecx,474F70h
    L_0043b912:
        mov dword ptr [ebx],0
    L_0043b918:
        call asm_TextLog_Append_0044b810
    L_0043b91d:
        add esp,4
    L_0043b920:
        pop ebx
    L_0043b921:
        or eax,0FFFFFFFFh
    L_0043b924:
        pop esi
    L_0043b925:
        ret
    L_0043b926:
        mov eax,dword ptr [ebx]
    L_0043b928:
        mov ecx,dword ptr [eax]
    L_0043b92a:
        push edi
    L_0043b92b:
        push 0
    L_0043b92d:
        lea edi,[esi+10h]
    L_0043b930:
        push edi
    L_0043b931:
        push 46793Ch
    L_0043b936:
        push eax
    L_0043b937:
        call dword ptr [ecx+0Ch]
    L_0043b93a:
        test eax,eax
    L_0043b93c:
        jge short L_0043b969
    L_0043b93e:
        mov eax,dword ptr [ebx]
    L_0043b940:
        test eax,eax
    L_0043b942:
        je short L_0043b950
    L_0043b944:
        mov edx,dword ptr [eax]
    L_0043b946:
        push eax
    L_0043b947:
        call dword ptr [edx+8]
    L_0043b94a:
        mov dword ptr [ebx],0
    L_0043b950:
        push 46F9E0h
    L_0043b955:
        mov ecx,474F70h
    L_0043b95a:
        call asm_TextLog_Append_0044b810
    L_0043b95f:
        add esp,4
    L_0043b962:
        pop edi
    L_0043b963:
        pop ebx
    L_0043b964:
        or eax,0FFFFFFFFh
    L_0043b967:
        pop esi
    L_0043b968:
        ret
    L_0043b969:
        mov eax,dword ptr [edi]
    L_0043b96b:
        mov ecx,dword ptr [eax]
    L_0043b96d:
        push 4664FCh
    L_0043b972:
        push eax
    L_0043b973:
        call dword ptr [ecx+2Ch]
    L_0043b976:
        test eax,eax
    L_0043b978:
        mov eax,dword ptr [edi]
    L_0043b97a:
        jge short L_0043b9b7
    L_0043b97c:
        test eax,eax
    L_0043b97e:
        je short L_0043b98c
    L_0043b980:
        mov edx,dword ptr [eax]
    L_0043b982:
        push eax
    L_0043b983:
        call dword ptr [edx+8]
    L_0043b986:
        mov dword ptr [edi],0
    L_0043b98c:
        mov eax,dword ptr [ebx]
    L_0043b98e:
        test eax,eax
    L_0043b990:
        je short L_0043b99e
    L_0043b992:
        mov ecx,dword ptr [eax]
    L_0043b994:
        push eax
    L_0043b995:
        call dword ptr [ecx+8]
    L_0043b998:
        mov dword ptr [ebx],0
    L_0043b99e:
        push 46F9B0h
    L_0043b9a3:
        mov ecx,474F70h
    L_0043b9a8:
        call asm_TextLog_Append_0044b810
    L_0043b9ad:
        add esp,4
    L_0043b9b0:
        pop edi
    L_0043b9b1:
        pop ebx
    L_0043b9b2:
        or eax,0FFFFFFFFh
    L_0043b9b5:
        pop esi
    L_0043b9b6:
        ret
    L_0043b9b7:
        mov ecx,dword ptr [esi+48h]
    L_0043b9ba:
        mov edx,dword ptr [eax]
    L_0043b9bc:
        push 16h
    L_0043b9be:
        push ecx
    L_0043b9bf:
        push eax
    L_0043b9c0:
        call dword ptr [edx+34h]
    L_0043b9c3:
        test eax,eax
    L_0043b9c5:
        jge short L_0043b9f7
    L_0043b9c7:
        mov eax,dword ptr [edi]
    L_0043b9c9:
        test eax,eax
    L_0043b9cb:
        je short L_0043b9d9
    L_0043b9cd:
        mov edx,dword ptr [eax]
    L_0043b9cf:
        push eax
    L_0043b9d0:
        call dword ptr [edx+8]
    L_0043b9d3:
        mov dword ptr [edi],0
    L_0043b9d9:
        call asm_CachedComSlot_ReleaseRetail_00421d20
    L_0043b9de:
        push 46F97Ch
    L_0043b9e3:
        mov ecx,474F70h
    L_0043b9e8:
        call asm_TextLog_Append_0044b810
    L_0043b9ed:
        add esp,4
    L_0043b9f0:
        pop edi
    L_0043b9f1:
        pop ebx
    L_0043b9f2:
        or eax,0FFFFFFFFh
    L_0043b9f5:
        pop esi
    L_0043b9f6:
        ret
    L_0043b9f7:
        mov edi,dword ptr [edi]
    L_0043b9f9:
        mov eax,dword ptr [edi]
    L_0043b9fb:
        push edi
    L_0043b9fc:
        call dword ptr [eax+1Ch]
    L_0043b9ff:
        push 46F954h
    L_0043ba04:
        mov ecx,474F70h
    L_0043ba09:
        call asm_TextLog_Append_0044b810
    L_0043ba0e:
        mov ebx,dword ptr [ebx]
    L_0043ba10:
        mov ecx,dword ptr [ebx]
    L_0043ba12:
        add esp,4
    L_0043ba15:
        push 1
    L_0043ba17:
        push 0
    L_0043ba19:
        push 43BAF0h
    L_0043ba1e:
        push 4
    L_0043ba20:
        push ebx
    L_0043ba21:
        call dword ptr [ecx+10h]
    L_0043ba24:
        mov eax,dword ptr [esi+14h]
    L_0043ba27:
        test eax,eax
    L_0043ba29:
        je short L_0043ba81
    L_0043ba2b:
        mov edx,dword ptr [eax]
    L_0043ba2d:
        push 466704h
    L_0043ba32:
        push eax
    L_0043ba33:
        call dword ptr [edx+2Ch]
    L_0043ba36:
        mov edx,dword ptr [esi+48h]
    L_0043ba39:
        mov eax,dword ptr [esi+14h]
    L_0043ba3c:
        mov ecx,dword ptr [eax]
    L_0043ba3e:
        push 0Ah
    L_0043ba40:
        push edx
    L_0043ba41:
        push eax
    L_0043ba42:
        call dword ptr [ecx+34h]
    L_0043ba45:
        mov dword ptr [data_00491c44],2Ch
    L_0043ba4f:
        mov eax,dword ptr [esi+14h]
    L_0043ba52:
        mov ecx,dword ptr [eax]
    L_0043ba54:
        push 491C44h
    L_0043ba59:
        push eax
    L_0043ba5a:
        call dword ptr [ecx+0Ch]
    L_0043ba5d:
        mov esi,dword ptr [esi+14h]
    L_0043ba60:
        mov edx,dword ptr [esi]
    L_0043ba62:
        push 0
    L_0043ba64:
        push 0
    L_0043ba66:
        push 43BB30h
    L_0043ba6b:
        push esi
    L_0043ba6c:
        call dword ptr [edx+10h]
    L_0043ba6f:
        push 46F934h
    L_0043ba74:
        mov ecx,474F70h
    L_0043ba79:
        call asm_TextLog_Append_0044b810
    L_0043ba7e:
        add esp,4
    L_0043ba81:
        pop edi
    L_0043ba82:
        pop ebx
    L_0043ba83:
        xor eax,eax
    L_0043ba85:
        pop esi
    L_0043ba86:
        ret
    }
}
