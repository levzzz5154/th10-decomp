#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C5DC..0x0045C650: FUN_0045c5dc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045c5dc_0045c5dc() {
    __asm {
    L_0045c5dc:
        push ebp
    L_0045c5dd:
        mov ebp,esp
    L_0045c5df:
        sub esp,7Ch
    L_0045c5e2:
        mov eax,dword ptr [data_00473660]
    L_0045c5e7:
        xor eax,ebp
    L_0045c5e9:
        mov dword ptr [ebp-4],eax
    L_0045c5ec:
        push 78h
    L_0045c5ee:
        lea eax,[ebp-7Ch]
    L_0045c5f1:
        push eax
    L_0045c5f2:
        mov eax,dword ptr [ebp+8]
    L_0045c5f5:
        and eax,3FFh
    L_0045c5fa:
        push 1
    L_0045c5fc:
        or eax,400h
    L_0045c601:
        push eax
    L_0045c602:
        call dword ptr [data_00477648]
    L_0045c608:
        test eax,eax
    L_0045c60a:
        je short L_0045c63e
    L_0045c60c:
        lea edx,[ebp-7Ch]
    L_0045c60f:
        call asm_LcidFromHexString_0045c4f2
    L_0045c614:
        cmp dword ptr [ebp+8],eax
    L_0045c617:
        je short L_0045c642
    L_0045c619:
        cmp dword ptr [ebp+0Ch],0
    L_0045c61d:
        je short L_0045c642
    L_0045c61f:
        push esi
    L_0045c620:
        push dword ptr [data_00477644]
    L_0045c626:
        call asm_strlen_00456720
    L_0045c62b:
        mov edx,dword ptr [data_00477644]
    L_0045c631:
        pop ecx
    L_0045c632:
        mov esi,eax
    L_0045c634:
        call asm_GetPrimaryLen_0045c527
    L_0045c639:
        cmp eax,esi
    L_0045c63b:
        pop esi
    L_0045c63c:
        jne short L_0045c642
    L_0045c63e:
        xor eax,eax
    L_0045c640:
        jmp short L_0045c645
    L_0045c642:
        xor eax,eax
    L_0045c644:
        inc eax
    L_0045c645:
        mov ecx,dword ptr [ebp-4]
    L_0045c648:
        xor ecx,ebp
    L_0045c64a:
        call asm_security_check_cookie_00458ea5
    L_0045c64f:
        leave
    L_0045c650:
        ret
    }
}
