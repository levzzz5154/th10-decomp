#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BDA0..0x0043BF82: FUN_0043bda0
// Naked body preserves the retail register/stack ABI.

// 0x0043C500..0x0043C549: FUN_0043c500
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c500_0043c500() {
    __asm {
    L_0043c500:
        sub esp,10h
    L_0043c503:
        mov eax,dword ptr [ecx+18h]
    L_0043c506:
        push ebx
    L_0043c507:
        mov ebx,dword ptr [ecx+24h]
    L_0043c50a:
        and ebx,0FFFFFFh
    L_0043c510:
        shl eax,18h
    L_0043c513:
        push edi
    L_0043c514:
        or ebx,eax
    L_0043c516:
        lea edi,[esp+8]
    L_0043c51a:
        mov dword ptr [esp+8],42000000h
    L_0043c522:
        mov dword ptr [esp+0Ch],41800000h
    L_0043c52a:
        mov dword ptr [esp+10h],43D00000h
    L_0043c532:
        mov dword ptr [esp+14h],43E80000h
    L_0043c53a:
        call asm_FUN_0043bda0_0043bda0
    L_0043c53f:
        pop edi
    L_0043c540:
        mov eax,1
    L_0043c545:
        pop ebx
    L_0043c546:
        add esp,10h
    L_0043c549:
        ret
    }
}
