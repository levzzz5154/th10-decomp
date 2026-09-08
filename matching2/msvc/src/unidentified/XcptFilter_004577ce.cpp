#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004577CE..0x00457931: __XcptFilter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_XcptFilter_004577ce() {
    __asm {
    L_004577ce:
        push ebp
    L_004577cf:
        mov ebp,esp
    L_004577d1:
        push ecx
    L_004577d2:
        push ebx
    L_004577d3:
        push esi
    L_004577d4:
        push edi
    L_004577d5:
        call asm_getptd_00456357
    L_004577da:
        mov edi,dword ptr [ebp+8]
    L_004577dd:
        mov esi,eax
    L_004577df:
        mov edx,dword ptr [esi+54h]
    L_004577e2:
        mov eax,dword ptr [data_00473654]
    L_004577e7:
        mov ecx,edx
    L_004577e9:
        cmp dword ptr [ecx],edi
    L_004577eb:
        je short L_004577fa
    L_004577ed:
        lea ebx,[eax+eax*2]
    L_004577f0:
        add ecx,0Ch
    L_004577f3:
        lea ebx,[edx+ebx*4]
    L_004577f6:
        cmp ecx,ebx
    L_004577f8:
        jb short L_004577e9
    L_004577fa:
        lea eax,[eax+eax*2]
    L_004577fd:
        lea eax,[edx+eax*4]
    L_00457800:
        cmp ecx,eax
    L_00457802:
        jae short L_00457808
    L_00457804:
        cmp dword ptr [ecx],edi
    L_00457806:
        je short L_0045780a
    L_00457808:
        xor ecx,ecx
    L_0045780a:
        test ecx,ecx
    L_0045780c:
        je asm_target_00457924
    L_00457812:
        mov ebx,dword ptr [ecx+8]
    L_00457815:
        test ebx,ebx
    L_00457817:
        mov dword ptr [ebp+8],ebx
    L_0045781a:
        je asm_target_00457924
    L_00457820:
        cmp ebx,5
    L_00457823:
        jne short L_00457831
    L_00457825:
        and dword ptr [ecx+8],0
    L_00457829:
        xor eax,eax
    L_0045782b:
        inc eax
    L_0045782c:
        jmp asm_target_0045792d
    L_00457831:
        cmp ebx,1
    L_00457834:
        je asm_target_0045791f
    L_0045783a:
        mov eax,dword ptr [esi+58h]
    L_0045783d:
        mov dword ptr [ebp-4],eax
    L_00457840:
        mov eax,dword ptr [ebp+0Ch]
    L_00457843:
        mov dword ptr [esi+58h],eax
    L_00457846:
        mov eax,dword ptr [ecx+4]
    L_00457849:
        cmp eax,8
    L_0045784c:
        jne asm_target_00457911
    L_00457852:
        mov edx,dword ptr [data_00473648]
    L_00457858:
        mov eax,dword ptr [data_0047364c]
    L_0045785d:
        add eax,edx
    L_0045785f:
        cmp edx,eax
    L_00457861:
        jge short L_0045788a
    L_00457863:
        lea eax,[edx+edx*2]
    L_00457866:
        shl eax,2
    L_00457869:
        mov edi,dword ptr [esi+54h]
    L_0045786c:
        and dword ptr [eax+edi+8],0
    L_00457871:
        mov edi,dword ptr [data_00473648]
    L_00457877:
        mov ebx,dword ptr [data_0047364c]
    L_0045787d:
        inc edx
    L_0045787e:
        add ebx,edi
    L_00457880:
        add eax,0Ch
    L_00457883:
        cmp edx,ebx
    L_00457885:
        jl short L_00457869
    L_00457887:
        mov ebx,dword ptr [ebp+8]
    L_0045788a:
        mov ecx,dword ptr [ecx]
    L_0045788c:
        cmp ecx,0C000008Eh
    L_00457892:
        mov edi,dword ptr [esi+5Ch]
    L_00457895:
        jne short L_004578a0
    L_00457897:
        mov dword ptr [esi+5Ch],83h
    L_0045789e:
        jmp short L_00457904
    L_004578a0:
        cmp ecx,0C0000090h
    L_004578a6:
        jne short L_004578b1
    L_004578a8:
        mov dword ptr [esi+5Ch],81h
    L_004578af:
        jmp short L_00457904
    L_004578b1:
        cmp ecx,0C0000091h
    L_004578b7:
        jne short L_004578c2
    L_004578b9:
        mov dword ptr [esi+5Ch],84h
    L_004578c0:
        jmp short L_00457904
    L_004578c2:
        cmp ecx,0C0000093h
    L_004578c8:
        jne short L_004578d3
    L_004578ca:
        mov dword ptr [esi+5Ch],85h
    L_004578d1:
        jmp short L_00457904
    L_004578d3:
        cmp ecx,0C000008Dh
    L_004578d9:
        jne short L_004578e4
    L_004578db:
        mov dword ptr [esi+5Ch],82h
    L_004578e2:
        jmp short L_00457904
    L_004578e4:
        cmp ecx,0C000008Fh
    L_004578ea:
        jne short L_004578f5
    L_004578ec:
        mov dword ptr [esi+5Ch],86h
    L_004578f3:
        jmp short L_00457904
    L_004578f5:
        cmp ecx,0C0000092h
    L_004578fb:
        jne short L_00457904
    L_004578fd:
        mov dword ptr [esi+5Ch],8Ah
    L_00457904:
        push dword ptr [esi+5Ch]
    L_00457907:
        push 8
    L_00457909:
        call ebx
    L_0045790b:
        pop ecx
    L_0045790c:
        mov dword ptr [esi+5Ch],edi
    L_0045790f:
        jmp short L_00457918
    L_00457911:
        and dword ptr [ecx+8],0
    L_00457915:
        push eax
    L_00457916:
        call ebx
    L_00457918:
        mov eax,dword ptr [ebp-4]
    L_0045791b:
        pop ecx
    L_0045791c:
        mov dword ptr [esi+58h],eax
    L_0045791f:
        or eax,0FFFFFFFFh
    L_00457922:
        jmp short L_0045792d
    L_00457924:
        push dword ptr [ebp+0Ch]
    L_00457927:
        call dword ptr [data_0046613c]
    L_0045792d:
        pop edi
    L_0045792e:
        pop esi
    L_0045792f:
        pop ebx
    L_00457930:
        leave
    L_00457931:
        ret
    }
}
