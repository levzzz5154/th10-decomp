#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460872..0x00460959: FUN_00460872
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00460872_00460872() {
    __asm {
    L_00460872:
        push ebp
    L_00460873:
        mov ebp,esp
    L_00460875:
        sub esp,1Ch
    L_00460878:
        mov eax,dword ptr [data_00473660]
    L_0046087d:
        xor eax,ebp
    L_0046087f:
        mov dword ptr [ebp-4],eax
    L_00460882:
        mov eax,dword ptr [ebp+8]
    L_00460885:
        push ebx
    L_00460886:
        mov ebx,dword ptr [ebp+10h]
    L_00460889:
        xor edx,edx
    L_0046088b:
        mov dword ptr [ebp-18h],eax
    L_0046088e:
        mov eax,dword ptr [ebp+0Ch]
    L_00460891:
        cmp eax,edx
    L_00460893:
        push esi
    L_00460894:
        push edi
    L_00460895:
        mov dword ptr [ebp-14h],404Eh
    L_0046089c:
        mov dword ptr [ebx],edx
    L_0046089e:
        mov dword ptr [ebx+4],edx
    L_004608a1:
        mov dword ptr [ebx+8],edx
    L_004608a4:
        jbe short L_004608f5
    L_004608a6:
        mov dword ptr [ebp-1Ch],eax
    L_004608a9:
        mov esi,ebx
    L_004608ab:
        lea edi,[ebp-10h]
    L_004608ae:
        movsd
    L_004608af:
        movsd
    L_004608b0:
        push ebx
    L_004608b1:
        movsd
    L_004608b2:
        call asm_shl_12_00460817
    L_004608b7:
        push ebx
    L_004608b8:
        call asm_shl_12_00460817
    L_004608bd:
        lea eax,[ebp-10h]
    L_004608c0:
        push eax
    L_004608c1:
        push ebx
    L_004608c2:
        call asm_add_12_004607b9
    L_004608c7:
        push ebx
    L_004608c8:
        call asm_shl_12_00460817
    L_004608cd:
        mov eax,dword ptr [ebp-18h]
    L_004608d0:
        movsx eax,byte ptr [eax]
    L_004608d3:
        and dword ptr [ebp-0Ch],0
    L_004608d7:
        and dword ptr [ebp-8],0
    L_004608db:
        mov dword ptr [ebp-10h],eax
    L_004608de:
        lea eax,[ebp-10h]
    L_004608e1:
        push eax
    L_004608e2:
        push ebx
    L_004608e3:
        call asm_add_12_004607b9
    L_004608e8:
        add esp,1Ch
    L_004608eb:
        inc dword ptr [ebp-18h]
    L_004608ee:
        dec dword ptr [ebp-1Ch]
    L_004608f1:
        jne short L_004608a9
    L_004608f3:
        xor edx,edx
    L_004608f5:
        cmp dword ptr [ebx+8],edx
    L_004608f8:
        jne short L_00460929
    L_004608fa:
        mov edi,dword ptr [ebx+8]
    L_004608fd:
        mov ecx,dword ptr [ebx+4]
    L_00460900:
        add dword ptr [ebp-14h],0FFF0h
    L_00460907:
        mov eax,ecx
    L_00460909:
        shr eax,10h
    L_0046090c:
        mov edi,eax
    L_0046090e:
        mov eax,dword ptr [ebx]
    L_00460910:
        mov esi,eax
    L_00460912:
        shr esi,10h
    L_00460915:
        shl ecx,10h
    L_00460918:
        or esi,ecx
    L_0046091a:
        shl eax,10h
    L_0046091d:
        cmp edi,edx
    L_0046091f:
        mov dword ptr [ebx+4],esi
    L_00460922:
        mov dword ptr [ebx],eax
    L_00460924:
        je short L_004608fd
    L_00460926:
        mov dword ptr [ebx+8],edi
    L_00460929:
        mov esi,8000h
    L_0046092e:
        jmp short L_0046093e
    L_00460930:
        push ebx
    L_00460931:
        call asm_shl_12_00460817
    L_00460936:
        add dword ptr [ebp-14h],0FFFFh
    L_0046093d:
        pop ecx
    L_0046093e:
        test dword ptr [ebx+8],esi
    L_00460941:
        je short L_00460930
    L_00460943:
        mov ax,word ptr [ebp-14h]
    L_00460947:
        mov ecx,dword ptr [ebp-4]
    L_0046094a:
        pop edi
    L_0046094b:
        pop esi
    L_0046094c:
        mov word ptr [ebx+0Ah],ax
    L_00460950:
        xor ecx,ebp
    L_00460952:
        pop ebx
    L_00460953:
        call asm_security_check_cookie_00458ea5
    L_00460958:
        leave
    L_00460959:
        ret
    }
}
