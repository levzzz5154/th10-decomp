#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460B90..0x00460C1D: FUN_00460b90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00460b90_00460b90() {
    __asm {
    L_00460b90:
        push ebp
    L_00460b91:
        mov ebp,esp
    L_00460b93:
        sub esp,14h
    L_00460b96:
        mov eax,dword ptr [data_00473660]
    L_00460b9b:
        mov ecx,dword ptr [ebp+8]
    L_00460b9e:
        push ebx
    L_00460b9f:
        mov ebx,473DC0h
    L_00460ba4:
        xor eax,ebp
    L_00460ba6:
        xor edx,edx
    L_00460ba8:
        sub ebx,60h
    L_00460bab:
        cmp dword ptr [ebp+0Ch],edx
    L_00460bae:
        mov dword ptr [ebp-4],eax
    L_00460bb1:
        mov dword ptr [ebp-14h],ecx
    L_00460bb4:
        je short L_00460c11
    L_00460bb6:
        jge short L_00460bc3
    L_00460bb8:
        neg dword ptr [ebp+0Ch]
    L_00460bbb:
        mov ebx,473F20h
    L_00460bc0:
        sub ebx,60h
    L_00460bc3:
        cmp dword ptr [ebp+10h],edx
    L_00460bc6:
        jne short L_00460bcb
    L_00460bc8:
        mov word ptr [ecx],dx
    L_00460bcb:
        cmp dword ptr [ebp+0Ch],edx
    L_00460bce:
        je short L_00460c11
    L_00460bd0:
        push esi
    L_00460bd1:
        push edi
    L_00460bd2:
        mov eax,dword ptr [ebp+0Ch]
    L_00460bd5:
        sar dword ptr [ebp+0Ch],3
    L_00460bd9:
        and eax,7
    L_00460bdc:
        add ebx,54h
    L_00460bdf:
        cmp eax,edx
    L_00460be1:
        je short L_00460c0a
    L_00460be3:
        lea eax,[eax+eax*2]
    L_00460be6:
        lea esi,[ebx+eax*4]
    L_00460be9:
        cmp word ptr [esi],8000h
    L_00460bee:
        jb short L_00460bfc
    L_00460bf0:
        lea edi,[ebp-10h]
    L_00460bf3:
        movsd
    L_00460bf4:
        movsd
    L_00460bf5:
        movsd
    L_00460bf6:
        dec dword ptr [ebp-0Eh]
    L_00460bf9:
        lea esi,[ebp-10h]
    L_00460bfc:
        push esi
    L_00460bfd:
        push ecx
    L_00460bfe:
        call asm_FUN_0046095a_0046095a
    L_00460c03:
        pop ecx
    L_00460c04:
        pop ecx
    L_00460c05:
        mov ecx,dword ptr [ebp-14h]
    L_00460c08:
        xor edx,edx
    L_00460c0a:
        cmp dword ptr [ebp+0Ch],edx
    L_00460c0d:
        jne short L_00460bd2
    L_00460c0f:
        pop edi
    L_00460c10:
        pop esi
    L_00460c11:
        mov ecx,dword ptr [ebp-4]
    L_00460c14:
        xor ecx,ebp
    L_00460c16:
        pop ebx
    L_00460c17:
        call asm_security_check_cookie_00458ea5
    L_00460c1c:
        leave
    L_00460c1d:
        ret
    }
}
