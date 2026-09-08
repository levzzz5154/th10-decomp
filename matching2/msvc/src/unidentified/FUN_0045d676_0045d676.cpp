#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D676..0x0045D6BA: FUN_0045d676
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045d676_0045d676() {
    __asm {
    L_0045d676:
        push ebp
    L_0045d677:
        mov ebp,esp
    L_0045d679:
        sub esp,14h
    L_0045d67c:
        mov eax,dword ptr [data_00473660]
    L_0045d681:
        push esi
    L_0045d682:
        mov esi,dword ptr [ebp+8]
    L_0045d685:
        xor ecx,ecx
    L_0045d687:
        push ecx
    L_0045d688:
        push ecx
    L_0045d689:
        xor eax,ebp
    L_0045d68b:
        push ecx
    L_0045d68c:
        mov dword ptr [ebp-4],eax
    L_0045d68f:
        mov eax,dword ptr [ebp+0Ch]
    L_0045d692:
        push ecx
    L_0045d693:
        push eax
    L_0045d694:
        lea eax,[ebp-14h]
    L_0045d697:
        push eax
    L_0045d698:
        lea eax,[ebp-10h]
    L_0045d69b:
        push eax
    L_0045d69c:
        call asm_FUN_0045d746_0045d746
    L_0045d6a1:
        lea eax,[ebp-10h]
    L_0045d6a4:
        push esi
    L_0045d6a5:
        push eax
    L_0045d6a6:
        call asm_FID_conflict___ld12tod_0045d5ce
    L_0045d6ab:
        mov ecx,dword ptr [ebp-4]
    L_0045d6ae:
        add esp,24h
    L_0045d6b1:
        xor ecx,ebp
    L_0045d6b3:
        pop esi
    L_0045d6b4:
        call asm_security_check_cookie_00458ea5
    L_0045d6b9:
        leave
    L_0045d6ba:
        ret
    }
}
