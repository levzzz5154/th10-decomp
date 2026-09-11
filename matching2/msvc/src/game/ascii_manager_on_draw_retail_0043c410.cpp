#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C2C0..0x0043C303: FUN_0043c2c0
// Naked body preserves the retail register/stack ABI.

// 0x0043C410..0x0043C453: AsciiManager_OnDrawRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AsciiManager_OnDrawRetail_0043c410() {
    __asm {
    L_0043c410:
        sub esp,10h
    L_0043c413:
        mov eax,dword ptr [ecx+20h]
    L_0043c416:
        push ebx
    L_0043c417:
        mov ebx,dword ptr [ecx+18h]
    L_0043c41a:
        shl ebx,18h
    L_0043c41d:
        push edi
    L_0043c41e:
        or ebx,eax
    L_0043c420:
        lea edi,[esp+8]
    L_0043c424:
        mov dword ptr [esp+8],42000000h
    L_0043c42c:
        mov dword ptr [esp+0Ch],41800000h
    L_0043c434:
        mov dword ptr [esp+10h],43D00000h
    L_0043c43c:
        mov dword ptr [esp+14h],43E80000h
    L_0043c444:
        call asm_FUN_0043bda0_0043bda0
    L_0043c449:
        pop edi
    L_0043c44a:
        mov eax,1
    L_0043c44f:
        pop ebx
    L_0043c450:
        add esp,10h
    L_0043c453:
        ret
    }
}
