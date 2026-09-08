#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D6BB..0x0045D700: FUN_0045d6bb
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045d6bb_0045d6bb() {
    __asm {
    L_0045d6bb:
        push ebp
    L_0045d6bc:
        mov ebp,esp
    L_0045d6be:
        sub esp,14h
    L_0045d6c1:
        mov eax,dword ptr [data_00473660]
    L_0045d6c6:
        push esi
    L_0045d6c7:
        mov esi,dword ptr [ebp+8]
    L_0045d6ca:
        xor ecx,ecx
    L_0045d6cc:
        push ecx
    L_0045d6cd:
        push ecx
    L_0045d6ce:
        xor eax,ebp
    L_0045d6d0:
        push ecx
    L_0045d6d1:
        mov dword ptr [ebp-4],eax
    L_0045d6d4:
        mov eax,dword ptr [ebp+0Ch]
    L_0045d6d7:
        push 1
    L_0045d6d9:
        push eax
    L_0045d6da:
        lea eax,[ebp-14h]
    L_0045d6dd:
        push eax
    L_0045d6de:
        lea eax,[ebp-10h]
    L_0045d6e1:
        push eax
    L_0045d6e2:
        call asm_FUN_0045d746_0045d746
    L_0045d6e7:
        lea eax,[ebp-10h]
    L_0045d6ea:
        push esi
    L_0045d6eb:
        push eax
    L_0045d6ec:
        call asm_ld12told_0045d5fa
    L_0045d6f1:
        mov ecx,dword ptr [ebp-4]
    L_0045d6f4:
        add esp,24h
    L_0045d6f7:
        xor ecx,ebp
    L_0045d6f9:
        pop esi
    L_0045d6fa:
        call asm_security_check_cookie_00458ea5
    L_0045d6ff:
        leave
    L_0045d700:
        ret
    }
}
