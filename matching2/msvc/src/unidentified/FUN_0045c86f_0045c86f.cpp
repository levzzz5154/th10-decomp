#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C86F..0x0045C93D: FUN_0045c86f
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045c86f_0045c86f() {
    __asm {
    L_0045c86f:
        push ebp
    L_0045c870:
        mov ebp,esp
    L_0045c872:
        sub esp,7Ch
    L_0045c875:
        mov eax,dword ptr [data_00473660]
    L_0045c87a:
        mov edx,dword ptr [ebp+8]
    L_0045c87d:
        xor eax,ebp
    L_0045c87f:
        push esi
    L_0045c880:
        mov dword ptr [ebp-4],eax
    L_0045c883:
        call asm_LcidFromHexString_0045c4f2
    L_0045c888:
        mov esi,eax
    L_0045c88a:
        push 78h
    L_0045c88c:
        lea eax,[ebp-7Ch]
    L_0045c88f:
        push eax
    L_0045c890:
        mov eax,dword ptr [data_00477634]
    L_0045c895:
        neg eax
    L_0045c897:
        sbb eax,eax
    L_0045c899:
        and eax,0FFFFF002h
    L_0045c89e:
        add eax,1001h
    L_0045c8a3:
        push eax
    L_0045c8a4:
        push esi
    L_0045c8a5:
        call dword ptr [data_00477648]
    L_0045c8ab:
        test eax,eax
    L_0045c8ad:
        jne short L_0045c8b8
    L_0045c8af:
        and dword ptr [data_00477628],eax
    L_0045c8b5:
        inc eax
    L_0045c8b6:
        jmp short L_0045c92f
    L_0045c8b8:
        lea eax,[ebp-7Ch]
    L_0045c8bb:
        push eax
    L_0045c8bc:
        push dword ptr [data_00477644]
    L_0045c8c2:
        call asm_stricmp_0046054e
    L_0045c8c7:
        test eax,eax
    L_0045c8c9:
        pop ecx
    L_0045c8ca:
        pop ecx
    L_0045c8cb:
        jne short L_0045c8d9
    L_0045c8cd:
        cmp dword ptr [data_00477634],eax
    L_0045c8d3:
        jne short L_0045c90f
    L_0045c8d5:
        push 1
    L_0045c8d7:
        jmp short L_0045c903
    L_0045c8d9:
        cmp dword ptr [data_00477634],0
    L_0045c8e0:
        jne short L_0045c922
    L_0045c8e2:
        mov eax,dword ptr [data_00477640]
    L_0045c8e7:
        test eax,eax
    L_0045c8e9:
        je short L_0045c922
    L_0045c8eb:
        push eax
    L_0045c8ec:
        lea eax,[ebp-7Ch]
    L_0045c8ef:
        push eax
    L_0045c8f0:
        push dword ptr [data_00477644]
    L_0045c8f6:
        call asm_strnicmp_004605b7
    L_0045c8fb:
        add esp,0Ch
    L_0045c8fe:
        test eax,eax
    L_0045c900:
        jne short L_0045c922
    L_0045c902:
        push eax
    L_0045c903:
        push esi
    L_0045c904:
        call asm_FUN_0045c5dc_0045c5dc
    L_0045c909:
        test eax,eax
    L_0045c90b:
        pop ecx
    L_0045c90c:
        pop ecx
    L_0045c90d:
        je short L_0045c922
    L_0045c90f:
        or dword ptr [data_00477628],4
    L_0045c916:
        mov dword ptr [data_00477630],esi
    L_0045c91c:
        mov dword ptr [data_0047762c],esi
    L_0045c922:
        mov eax,dword ptr [data_00477628]
    L_0045c927:
        shr eax,2
    L_0045c92a:
        not eax
    L_0045c92c:
        and eax,1
    L_0045c92f:
        mov ecx,dword ptr [ebp-4]
    L_0045c932:
        xor ecx,ebp
    L_0045c934:
        pop esi
    L_0045c935:
        call asm_security_check_cookie_00458ea5
    L_0045c93a:
        leave
    L_0045c93b:
        ret 4
    }
}
