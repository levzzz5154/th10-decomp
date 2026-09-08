#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A5C0..0x0043A5FE: FUN_0043a5c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a5c0_0043a5c0() {
    __asm {
    L_0043a5c0:
        sub esp,38h
    L_0043a5c3:
        mov eax,dword ptr [data_00473660]
    L_0043a5c8:
        xor eax,esp
    L_0043a5ca:
        mov dword ptr [esp+34h],eax
    L_0043a5ce:
        push 34h
    L_0043a5d0:
        lea eax,[esp+4]
    L_0043a5d4:
        push eax
    L_0043a5d5:
        push ecx
    L_0043a5d6:
        call dword ptr [data_00466294]
    L_0043a5dc:
        lea eax,[esp+8]
    L_0043a5e0:
        mov edx,esi
    L_0043a5e2:
        mov ecx,eax
    L_0043a5e4:
        sub edx,ecx
    L_0043a5e6:
        mov cl,byte ptr [eax]
    L_0043a5e8:
        mov byte ptr [edx+eax],cl
    L_0043a5eb:
        inc eax
    L_0043a5ec:
        test cl,cl
    L_0043a5ee:
        jne short L_0043a5e6
    L_0043a5f0:
        mov ecx,dword ptr [esp+34h]
    L_0043a5f4:
        xor ecx,esp
    L_0043a5f6:
        call asm_security_check_cookie_00458ea5
    L_0043a5fb:
        add esp,38h
    L_0043a5fe:
        ret
    }
}
