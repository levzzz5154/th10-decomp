#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A82D..0x0045AA92: __expandtime
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_expandtime_0045a82d() {
    __asm {
    L_0045a82d:
        push ebp
    L_0045a82e:
        mov ebp,esp
    L_0045a830:
        movsx eax,al
    L_0045a833:
        cmp eax,5Ah
    L_0045a836:
        push esi
    L_0045a837:
        mov esi,dword ptr [ebp+0Ch]
    L_0045a83a:
        push edi
    L_0045a83b:
        mov edi,ecx
    L_0045a83d:
        jg asm_target_0045a963
    L_0045a843:
        je asm_target_0045aa1e
    L_0045a849:
        cmp eax,4Dh
    L_0045a84c:
        jg short L_0045a8c3
    L_0045a84e:
        je short L_0045a8b9
    L_0045a850:
        sub eax,25h
    L_0045a853:
        je short L_0045a8ab
    L_0045a855:
        sub eax,1Ch
    L_0045a858:
        je short L_0045a89c
    L_0045a85a:
        dec eax
    L_0045a85b:
        je short L_0045a88d
    L_0045a85d:
        sub eax,6
    L_0045a860:
        je short L_0045a883
    L_0045a862:
        dec eax
    L_0045a863:
        jne asm_target_0045aa8c
    L_0045a869:
        mov eax,dword ptr [esi+8]
    L_0045a86c:
        cdq
    L_0045a86d:
        push 0Ch
    L_0045a86f:
        pop ecx
    L_0045a870:
        idiv ecx
    L_0045a872:
        mov eax,edx
    L_0045a874:
        test eax,eax
    L_0045a876:
        jne asm_target_0045aa01
    L_0045a87c:
        push ecx
    L_0045a87d:
        pop eax
    L_0045a87e:
        jmp asm_target_0045aa01
    L_0045a883:
        push dword ptr [ebp+14h]
    L_0045a886:
        mov eax,dword ptr [esi+8]
    L_0045a889:
        push 2
    L_0045a88b:
        jmp short L_0045a8f4
    L_0045a88d:
        mov edx,dword ptr [esi+10h]
    L_0045a890:
        mov esi,dword ptr [ebp+10h]
    L_0045a893:
        mov edx,dword ptr [esi+edx*4+68h]
    L_0045a897:
        jmp asm_target_0045aa83
    L_0045a89c:
        mov edx,dword ptr [esi+18h]
    L_0045a89f:
        mov esi,dword ptr [ebp+10h]
    L_0045a8a2:
        mov edx,dword ptr [esi+edx*4+1Ch]
    L_0045a8a6:
        jmp asm_target_0045aa83
    L_0045a8ab:
        mov eax,dword ptr [edi]
    L_0045a8ad:
        mov byte ptr [eax],25h
    L_0045a8b0:
        inc dword ptr [edi]
    L_0045a8b2:
        dec dword ptr [ebx]
    L_0045a8b4:
        jmp asm_target_0045aa8c
    L_0045a8b9:
        push dword ptr [ebp+14h]
    L_0045a8bc:
        mov eax,dword ptr [esi+4]
    L_0045a8bf:
        push 2
    L_0045a8c1:
        jmp short L_0045a8f4
    L_0045a8c3:
        sub eax,53h
    L_0045a8c6:
        je asm_target_0045a95a
    L_0045a8cc:
        dec eax
    L_0045a8cd:
        dec eax
    L_0045a8ce:
        je short L_0045a935
    L_0045a8d0:
        dec eax
    L_0045a8d1:
        dec eax
    L_0045a8d2:
        je short L_0045a924
    L_0045a8d4:
        dec eax
    L_0045a8d5:
        je short L_0045a902
    L_0045a8d7:
        dec eax
    L_0045a8d8:
        jne asm_target_0045aa8c
    L_0045a8de:
        mov eax,dword ptr [esi+14h]
    L_0045a8e1:
        cdq
    L_0045a8e2:
        push 64h
    L_0045a8e4:
        pop ecx
    L_0045a8e5:
        idiv ecx
    L_0045a8e7:
        push dword ptr [ebp+14h]
    L_0045a8ea:
        push 4
    L_0045a8ec:
        add eax,13h
    L_0045a8ef:
        imul eax,64h
    L_0045a8f2:
        add eax,edx
    L_0045a8f4:
        pop edx
    L_0045a8f5:
        mov ecx,ebx
    L_0045a8f7:
        call asm_store_num_0045a7b4
    L_0045a8fc:
        pop ecx
    L_0045a8fd:
        jmp asm_target_0045aa8c
    L_0045a902:
        push dword ptr [ebp+10h]
    L_0045a905:
        push ebx
    L_0045a906:
        push edi
    L_0045a907:
        push esi
    L_0045a908:
        push 2
    L_0045a90a:
        push dword ptr [ebp+8]
    L_0045a90d:
        call asm_store_winword_0045aa93
    L_0045a912:
        add esp,18h
    L_0045a915:
        test eax,eax
    L_0045a917:
        jne asm_target_0045aa8c
    L_0045a91d:
        xor eax,eax
    L_0045a91f:
        jmp asm_target_0045aa8f
    L_0045a924:
        mov eax,dword ptr [esi+18h]
    L_0045a927:
        test eax,eax
    L_0045a929:
        jne short L_0045a930
    L_0045a92b:
        push 6
    L_0045a92d:
        pop ecx
    L_0045a92e:
        jmp short L_0045a938
    L_0045a930:
        lea ecx,[eax-1]
    L_0045a933:
        jmp short L_0045a938
    L_0045a935:
        mov ecx,dword ptr [esi+18h]
    L_0045a938:
        cmp dword ptr [esi+1Ch],ecx
    L_0045a93b:
        jge short L_0045a944
    L_0045a93d:
        xor eax,eax
    L_0045a93f:
        jmp asm_target_0045aa01
    L_0045a944:
        mov eax,dword ptr [esi+1Ch]
    L_0045a947:
        push 7
    L_0045a949:
        cdq
    L_0045a94a:
        pop esi
    L_0045a94b:
        idiv esi
    L_0045a94d:
        cmp edx,ecx
    L_0045a94f:
        jl asm_target_0045aa01
    L_0045a955:
        jmp asm_target_0045aa00
    L_0045a95a:
        push dword ptr [ebp+14h]
    L_0045a95d:
        mov eax,dword ptr [esi]
    L_0045a95f:
        push 2
    L_0045a961:
        jmp short L_0045a8f4
    L_0045a963:
        cmp eax,6Dh
    L_0045a966:
        jg asm_target_0045aa0b
    L_0045a96c:
        je asm_target_0045a9fd
    L_0045a972:
        sub eax,61h
    L_0045a975:
        je short L_0045a9ef
    L_0045a977:
        dec eax
    L_0045a978:
        je short L_0045a9e0
    L_0045a97a:
        dec eax
    L_0045a97b:
        je short L_0045a9a4
    L_0045a97d:
        dec eax
    L_0045a97e:
        je short L_0045a997
    L_0045a980:
        sub eax,6
    L_0045a983:
        jne asm_target_0045aa8c
    L_0045a989:
        push dword ptr [ebp+14h]
    L_0045a98c:
        mov eax,dword ptr [esi+1Ch]
    L_0045a98f:
        inc eax
    L_0045a990:
        push 3
    L_0045a992:
        jmp asm_target_0045a8f4
    L_0045a997:
        push dword ptr [ebp+14h]
    L_0045a99a:
        mov eax,dword ptr [esi+0Ch]
    L_0045a99d:
        push 2
    L_0045a99f:
        jmp asm_target_0045a8f4
    L_0045a9a4:
        cmp dword ptr [ebp+14h],0
    L_0045a9a8:
        push dword ptr [ebp+10h]
    L_0045a9ab:
        push ebx
    L_0045a9ac:
        push edi
    L_0045a9ad:
        push esi
    L_0045a9ae:
        je short L_0045a9dc
    L_0045a9b0:
        push 1
    L_0045a9b2:
        push dword ptr [ebp+8]
    L_0045a9b5:
        call asm_store_winword_0045aa93
    L_0045a9ba:
        add esp,18h
    L_0045a9bd:
        test eax,eax
    L_0045a9bf:
        je asm_target_0045a91d
    L_0045a9c5:
        cmp dword ptr [ebx],0
    L_0045a9c8:
        je asm_target_0045a91d
    L_0045a9ce:
        mov eax,dword ptr [edi]
    L_0045a9d0:
        mov byte ptr [eax],20h
    L_0045a9d3:
        inc dword ptr [edi]
    L_0045a9d5:
        dec dword ptr [ebx]
    L_0045a9d7:
        jmp asm_target_0045a902
    L_0045a9dc:
        push 0
    L_0045a9de:
        jmp short L_0045a9b2
    L_0045a9e0:
        mov edx,dword ptr [esi+10h]
    L_0045a9e3:
        mov esi,dword ptr [ebp+10h]
    L_0045a9e6:
        mov edx,dword ptr [esi+edx*4+38h]
    L_0045a9ea:
        jmp asm_target_0045aa83
    L_0045a9ef:
        mov edx,dword ptr [esi+18h]
    L_0045a9f2:
        mov esi,dword ptr [ebp+10h]
    L_0045a9f5:
        mov edx,dword ptr [esi+edx*4]
    L_0045a9f8:
        jmp asm_target_0045aa83
    L_0045a9fd:
        mov eax,dword ptr [esi+10h]
    L_0045aa00:
        inc eax
    L_0045aa01:
        push dword ptr [ebp+14h]
    L_0045aa04:
        push 2
    L_0045aa06:
        jmp asm_target_0045a8f4
    L_0045aa0b:
        sub eax,70h
    L_0045aa0e:
        je short L_0045aa6c
    L_0045aa10:
        sub eax,7
    L_0045aa13:
        je short L_0045aa5e
    L_0045aa15:
        dec eax
    L_0045aa16:
        je short L_0045aa44
    L_0045aa18:
        dec eax
    L_0045aa19:
        je short L_0045aa34
    L_0045aa1b:
        dec eax
    L_0045aa1c:
        jne short L_0045aa8c
    L_0045aa1e:
        call asm_tzset_004571cf
    L_0045aa23:
        xor edx,edx
    L_0045aa25:
        cmp dword ptr [esi+20h],edx
    L_0045aa28:
        setne dl
    L_0045aa2b:
        mov edx,dword ptr [edx*4+4735B0h]
    L_0045aa32:
        jmp short L_0045aa83
    L_0045aa34:
        push dword ptr [ebp+14h]
    L_0045aa37:
        mov eax,dword ptr [esi+14h]
    L_0045aa3a:
        cdq
    L_0045aa3b:
        push 64h
    L_0045aa3d:
        pop ecx
    L_0045aa3e:
        idiv ecx
    L_0045aa40:
        mov eax,edx
    L_0045aa42:
        jmp short L_0045aa04
    L_0045aa44:
        cmp dword ptr [ebp+14h],0
    L_0045aa48:
        push dword ptr [ebp+10h]
    L_0045aa4b:
        push ebx
    L_0045aa4c:
        push edi
    L_0045aa4d:
        push esi
    L_0045aa4e:
        je short L_0045aa57
    L_0045aa50:
        push 1
    L_0045aa52:
        jmp asm_target_0045a90a
    L_0045aa57:
        push 0
    L_0045aa59:
        jmp asm_target_0045a90a
    L_0045aa5e:
        push dword ptr [ebp+14h]
    L_0045aa61:
        mov eax,dword ptr [esi+18h]
    L_0045aa64:
        xor edx,edx
    L_0045aa66:
        inc edx
    L_0045aa67:
        jmp asm_target_0045a8f5
    L_0045aa6c:
        cmp dword ptr [esi+8],0Bh
    L_0045aa70:
        mov edx,dword ptr [ebp+10h]
    L_0045aa73:
        jg short L_0045aa7d
    L_0045aa75:
        mov edx,dword ptr [edx+98h]
    L_0045aa7b:
        jmp short L_0045aa83
    L_0045aa7d:
        mov edx,dword ptr [edx+9Ch]
    L_0045aa83:
        mov ecx,edi
    L_0045aa85:
        mov eax,ebx
    L_0045aa87:
        call asm_store_str_0045a75e
    L_0045aa8c:
        xor eax,eax
    L_0045aa8e:
        inc eax
    L_0045aa8f:
        pop edi
    L_0045aa90:
        pop esi
    L_0045aa91:
        pop ebp
    L_0045aa92:
        ret
    }
}
