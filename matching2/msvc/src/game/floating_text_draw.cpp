#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042B780..0x0042B99B: FUN_0042b780
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b780_0042b780() {
    __asm {
    L_0042b780:
        mov al,byte ptr [data_00491d78]
    L_0042b785:
        sub esp,10h
    L_0042b788:
        test al,4
    L_0042b78a:
        push ebx
    L_0042b78b:
        push ebp
    L_0042b78c:
        push esi
    L_0042b78d:
        lea ebp,[edi+3C4h]
    L_0042b793:
        jne short L_0042b7c5
    L_0042b795:
        mov eax,dword ptr [data_00492378]
    L_0042b79a:
        test eax,eax
    L_0042b79c:
        je short L_0042b7c5
    L_0042b79e:
        mov esi,dword ptr [data_00491c10]
    L_0042b7a4:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_0042b7a9:
        mov eax,dword ptr [data_00491c30]
    L_0042b7ae:
        push 0
    L_0042b7b0:
        push 1Ch
    L_0042b7b2:
        mov dword ptr [data_00492378],0
    L_0042b7bc:
        mov ecx,dword ptr [eax]
    L_0042b7be:
        push eax
    L_0042b7bf:
        call dword ptr [ecx+0E4h]
    L_0042b7c5:
        mov esi,dword ptr [data_00477834]
    L_0042b7cb:
        mov dword ptr [esp+18h],2D3h
    L_0042b7d3:
        mov al,byte ptr [ebp+38h]
    L_0042b7d6:
        test al,al
    L_0042b7d8:
        je asm_target_0042b97e
    L_0042b7de:
        cmp dword ptr [ebp+20h],8
    L_0042b7e2:
        jge short L_0042b7f3
    L_0042b7e4:
        fld dword ptr [data_00470bd0]
    L_0042b7ea:
        fdiv dword ptr [ebp+24h]
    L_0042b7ed:
        fstp dword ptr [esp+0Ch]
    L_0042b7f1:
        jmp short L_0042b7fb
    L_0042b7f3:
        mov dword ptr [esp+0Ch],41000000h
    L_0042b7fb:
        movzx edx,byte ptr [ebp+39h]
    L_0042b7ff:
        mov dword ptr [esp+14h],edx
    L_0042b803:
        fild dword ptr [esp+14h]
    L_0042b807:
        fmul dword ptr [esp+0Ch]
    L_0042b80b:
        fmul dword ptr [data_00470b0c]
    L_0042b811:
        fsubr dword ptr [ebp+0Ch]
    L_0042b814:
        fadd dword ptr [data_00470b4c]
    L_0042b81a:
        fstp dword ptr [edi+358h]
    L_0042b820:
        fld dword ptr [ebp+10h]
    L_0042b823:
        fadd dword ptr [data_00470b48]
    L_0042b829:
        fstp dword ptr [edi+35Ch]
    L_0042b82f:
        mov eax,dword ptr [ebp+18h]
    L_0042b832:
        mov dword ptr [edi+314h],eax
    L_0042b838:
        fld dword ptr [esi+3C0h]
    L_0042b83e:
        fsub dword ptr [ebp+0Ch]
    L_0042b841:
        fld dword ptr [esi+3C4h]
    L_0042b847:
        fsub dword ptr [ebp+10h]
    L_0042b84a:
        fld st(0)
    L_0042b84c:
        fmul st,st(1)
    L_0042b84e:
        fld st(2)
    L_0042b850:
        fmul st,st(3)
    L_0042b852:
        faddp st(1),st
    L_0042b854:
        call asm_FUN_00463b2c_00463b2c
    L_0042b859:
        fstp st(0)
    L_0042b85b:
        cmp eax,1000h
    L_0042b860:
        fstp st(0)
    L_0042b862:
        jle short L_0042b86b
    L_0042b864:
        mov ebx,0D0h
    L_0042b869:
        jmp short L_0042b895
    L_0042b86b:
        cmp eax,400h
    L_0042b870:
        jle short L_0042b890
    L_0042b872:
        lea ecx,[eax-400h]
    L_0042b878:
        shl ecx,7
    L_0042b87b:
        mov eax,2AAAAAABh
    L_0042b880:
        imul ecx
    L_0042b882:
        sar edx,9
    L_0042b885:
        mov ecx,edx
    L_0042b887:
        shr ecx,1Fh
    L_0042b88a:
        lea ebx,[edx+ecx+50h]
    L_0042b88e:
        jmp short L_0042b895
    L_0042b890:
        mov ebx,50h
    L_0042b895:
        movzx eax,byte ptr [ebp+39h]
    L_0042b899:
        test eax,eax
    L_0042b89b:
        lea edx,[eax+ebp-1]
    L_0042b89f:
        mov dword ptr [esp+10h],edx
    L_0042b8a3:
        jle asm_target_0042b97e
    L_0042b8a9:
        lea esi,[edi+18h]
    L_0042b8ac:
        mov dword ptr [esp+14h],eax
    L_0042b8b0:
        jmp short L_0042b8b6
    L_0042b8b2:
        mov edx,dword ptr [esp+10h]
    L_0042b8b6:
        mov ecx,dword ptr [ebp+20h]
    L_0042b8b9:
        cmp ecx,34h
    L_0042b8bc:
        jl short L_0042b907
    L_0042b8be:
        mov al,byte ptr [edx]
    L_0042b8c0:
        cmp al,0Ah
    L_0042b8c2:
        je short L_0042b907
    L_0042b8c4:
        cmp ecx,38h
    L_0042b8c7:
        jge short L_0042b8e8
    L_0042b8c9:
        movzx edx,al
    L_0042b8cc:
        mov eax,dword ptr [edi+10h]
    L_0042b8cf:
        mov ecx,dword ptr [eax+118h]
    L_0042b8d5:
        add edx,0CFh
    L_0042b8db:
        imul edx,44h
    L_0042b8de:
        add edx,ecx
    L_0042b8e0:
        mov dword ptr [edi+3ACh],edx
    L_0042b8e6:
        jmp short L_0042b923
    L_0042b8e8:
        mov edx,dword ptr [edi+10h]
    L_0042b8eb:
        movzx ecx,al
    L_0042b8ee:
        mov eax,dword ptr [edx+118h]
    L_0042b8f4:
        add ecx,0D9h
    L_0042b8fa:
        imul ecx,44h
    L_0042b8fd:
        add ecx,eax
    L_0042b8ff:
        mov dword ptr [edi+3ACh],ecx
    L_0042b905:
        jmp short L_0042b923
    L_0042b907:
        movzx eax,byte ptr [edx]
    L_0042b90a:
        mov ecx,dword ptr [edi+10h]
    L_0042b90d:
        mov edx,dword ptr [ecx+118h]
    L_0042b913:
        add eax,0C4h
    L_0042b918:
        imul eax,44h
    L_0042b91b:
        add eax,edx
    L_0042b91d:
        mov dword ptr [edi+3ACh],eax
    L_0042b923:
        mov edx,dword ptr [edi+3ACh]
    L_0042b929:
        mov ecx,dword ptr [data_00491c10]
    L_0042b92f:
        mov byte ptr [edi+317h],bl
    L_0042b935:
        mov eax,dword ptr [edx+34h]
    L_0042b938:
        mov dword ptr [esi+4Ch],eax
    L_0042b93b:
        mov eax,dword ptr [esi+35Ch]
    L_0042b941:
        or eax,8
    L_0042b944:
        push ecx
    L_0042b945:
        mov dword ptr [esi+35Ch],eax
    L_0042b94b:
        call asm_FUN_00443080_00443080
    L_0042b950:
        fld dword ptr [esp+0Ch]
    L_0042b954:
        mov ecx,dword ptr [esp+10h]
    L_0042b958:
        fadd dword ptr [edi+358h]
    L_0042b95e:
        mov eax,dword ptr [esp+14h]
    L_0042b962:
        dec ecx
    L_0042b963:
        dec eax
    L_0042b964:
        fstp dword ptr [edi+358h]
    L_0042b96a:
        mov dword ptr [esp+10h],ecx
    L_0042b96e:
        mov dword ptr [esp+14h],eax
    L_0042b972:
        jne asm_target_0042b8b2
    L_0042b978:
        mov esi,dword ptr [data_00477834]
    L_0042b97e:
        mov eax,dword ptr [esp+18h]
    L_0042b982:
        add ebp,40h
    L_0042b985:
        dec eax
    L_0042b986:
        mov dword ptr [esp+18h],eax
    L_0042b98a:
        jne asm_target_0042b7d3
    L_0042b990:
        pop esi
    L_0042b991:
        pop ebp
    L_0042b992:
        mov eax,1
    L_0042b997:
        pop ebx
    L_0042b998:
        add esp,10h
    L_0042b99b:
        ret
    }
}
