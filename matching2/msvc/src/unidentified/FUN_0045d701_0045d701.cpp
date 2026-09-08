#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D701..0x0045D745: FUN_0045d701
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045d701_0045d701() {
    __asm {
    L_0045d701:
        push ebp
    L_0045d702:
        mov ebp,esp
    L_0045d704:
        sub esp,14h
    L_0045d707:
        mov eax,dword ptr [data_00473660]
    L_0045d70c:
        push esi
    L_0045d70d:
        mov esi,dword ptr [ebp+8]
    L_0045d710:
        xor ecx,ecx
    L_0045d712:
        push ecx
    L_0045d713:
        push ecx
    L_0045d714:
        xor eax,ebp
    L_0045d716:
        push ecx
    L_0045d717:
        mov dword ptr [ebp-4],eax
    L_0045d71a:
        mov eax,dword ptr [ebp+0Ch]
    L_0045d71d:
        push ecx
    L_0045d71e:
        push eax
    L_0045d71f:
        lea eax,[ebp-14h]
    L_0045d722:
        push eax
    L_0045d723:
        lea eax,[ebp-10h]
    L_0045d726:
        push eax
    L_0045d727:
        call asm_FUN_0045d746_0045d746
    L_0045d72c:
        lea eax,[ebp-10h]
    L_0045d72f:
        push esi
    L_0045d730:
        push eax
    L_0045d731:
        call asm_FID_conflict___ld12tod_0045d5e4
    L_0045d736:
        mov ecx,dword ptr [ebp-4]
    L_0045d739:
        add esp,24h
    L_0045d73c:
        xor ecx,ebp
    L_0045d73e:
        pop esi
    L_0045d73f:
        call asm_security_check_cookie_00458ea5
    L_0045d744:
        leave
    L_0045d745:
        ret
    }
}
