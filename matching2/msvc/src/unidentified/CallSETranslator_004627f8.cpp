#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004627F8..0x004628BE: _CallSETranslator
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CallSETranslator_004627f8() {
    __asm {
    L_004627f8:
        push ebp
    L_004627f9:
        mov ebp,esp
    L_004627fb:
        sub esp,34h
    L_004627fe:
        push ebx
    L_004627ff:
        cmp dword ptr [ebp+8],123h
    L_00462806:
        jne short L_0046281a
    L_00462808:
        mov eax,462893h
    L_0046280d:
        mov ecx,dword ptr [ebp+0Ch]
    L_00462810:
        mov dword ptr [ecx],eax
    L_00462812:
        xor eax,eax
    L_00462814:
        inc eax
    L_00462815:
        jmp asm_target_004628bc
    L_0046281a:
        and dword ptr [ebp-28h],0
    L_0046281e:
        mov dword ptr [ebp-24h],4628BFh
    L_00462825:
        mov eax,dword ptr [data_00473660]
    L_0046282a:
        mov dword ptr [ebp-20h],eax
    L_0046282d:
        mov eax,dword ptr [ebp+18h]
    L_00462830:
        mov dword ptr [ebp-1Ch],eax
    L_00462833:
        mov eax,dword ptr [ebp+0Ch]
    L_00462836:
        mov dword ptr [ebp-18h],eax
    L_00462839:
        mov eax,dword ptr [ebp+1Ch]
    L_0046283c:
        mov dword ptr [ebp-14h],eax
    L_0046283f:
        mov eax,dword ptr [ebp+20h]
    L_00462842:
        mov dword ptr [ebp-10h],eax
    L_00462845:
        and dword ptr [ebp-0Ch],0
    L_00462849:
        and dword ptr [ebp-8],0
    L_0046284d:
        and dword ptr [ebp-4],0
    L_00462851:
        mov dword ptr [ebp-0Ch],esp
    L_00462854:
        mov dword ptr [ebp-8],ebp
    L_00462857:
        mov eax,dword ptr fs:[0]
    L_0046285d:
        mov dword ptr [ebp-28h],eax
    L_00462860:
        lea eax,[ebp-28h]
    L_00462863:
        mov dword ptr fs:[0],eax
    L_00462869:
        mov dword ptr [ebp-34h],1
    L_00462870:
        mov eax,dword ptr [ebp+8]
    L_00462873:
        mov dword ptr [ebp-30h],eax
    L_00462876:
        mov eax,dword ptr [ebp+10h]
    L_00462879:
        mov dword ptr [ebp-2Ch],eax
    L_0046287c:
        lea eax,[ebp-30h]
    L_0046287f:
        push eax
    L_00462880:
        mov eax,dword ptr [ebp+8]
    L_00462883:
        push dword ptr [eax]
    L_00462885:
        call asm_getptd_00456357
    L_0046288a:
        call dword ptr [eax+74h]
    L_0046288d:
        pop ecx
    L_0046288e:
        pop ecx
    L_0046288f:
        and dword ptr [ebp-34h],0
    L_00462893:
        cmp dword ptr [ebp-4],0
    L_00462897:
        je short L_004628b0
    L_00462899:
        mov ebx,dword ptr fs:[0]
    L_004628a0:
        mov eax,dword ptr [ebx]
    L_004628a2:
        mov ebx,dword ptr [ebp-28h]
    L_004628a5:
        mov dword ptr [ebx],eax
    L_004628a7:
        mov dword ptr fs:[0],ebx
    L_004628ae:
        jmp short L_004628b9
    L_004628b0:
        mov eax,dword ptr [ebp-28h]
    L_004628b3:
        mov dword ptr fs:[0],eax
    L_004628b9:
        mov eax,dword ptr [ebp-34h]
    L_004628bc:
        pop ebx
    L_004628bd:
        leave
    L_004628be:
        ret
    }
}
