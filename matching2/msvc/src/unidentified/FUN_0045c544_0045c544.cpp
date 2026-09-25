#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C544..0x0045C5DB: FUN_0045c544
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045c544_0045c544() {
    __asm {
    L_0045c544:
        push ebp
    L_0045c545:
        mov ebp,esp
    L_0045c547:
        sub esp,7Ch
    L_0045c54a:
        mov eax,dword ptr [data_00473660]
    L_0045c54f:
        mov edx,dword ptr [ebp+8]
    L_0045c552:
        xor eax,ebp
    L_0045c554:
        push esi
    L_0045c555:
        mov dword ptr [ebp-4],eax
    L_0045c558:
        call asm_LcidFromHexString_0045c4f2
    L_0045c55d:
        mov esi,eax
    L_0045c55f:
        push 78h
    L_0045c561:
        lea eax,[ebp-7Ch]
    L_0045c564:
        push eax
    L_0045c565:
        mov eax,dword ptr [data_00477638]
    L_0045c56a:
        neg eax
    L_0045c56c:
        sbb eax,eax
    L_0045c56e:
        and eax,0FFFFF005h
    L_0045c573:
        add eax,1002h
    L_0045c578:
        push eax
    L_0045c579:
        push esi
    L_0045c57a:
        call dword ptr [data_00477648]
    L_0045c580:
        test eax,eax
    L_0045c582:
        jne short L_0045c58d
    L_0045c584:
        and dword ptr [data_00477628],eax
    L_0045c58a:
        inc eax
    L_0045c58b:
        jmp short L_0045c5cd
    L_0045c58d:
        lea eax,[ebp-7Ch]
    L_0045c590:
        push eax
    L_0045c591:
        push dword ptr [data_0047763c]
    L_0045c597:
        call asm_stricmp_0046054e
    L_0045c59c:
        test eax,eax
    L_0045c59e:
        pop ecx
    L_0045c59f:
        pop ecx
    L_0045c5a0:
        jne short L_0045c5c0
    L_0045c5a2:
        push esi
    L_0045c5a3:
        call asm_FUN_0045c3f1_0045c3f1
    L_0045c5a8:
        test eax,eax
    L_0045c5aa:
        pop ecx
    L_0045c5ab:
        je short L_0045c5c0
    L_0045c5ad:
        or dword ptr [data_00477628],4
    L_0045c5b4:
        mov dword ptr [data_00477630],esi
    L_0045c5ba:
        mov dword ptr [data_0047762c],esi
    L_0045c5c0:
        mov eax,dword ptr [data_00477628]
    L_0045c5c5:
        shr eax,2
    L_0045c5c8:
        not eax
    L_0045c5ca:
        and eax,1
    L_0045c5cd:
        mov ecx,dword ptr [ebp-4]
    L_0045c5d0:
        xor ecx,ebp
    L_0045c5d2:
        pop esi
    L_0045c5d3:
        call asm_security_check_cookie_00458ea5
    L_0045c5d8:
        leave
    L_0045c5d9:
        ret 4
    }
}
