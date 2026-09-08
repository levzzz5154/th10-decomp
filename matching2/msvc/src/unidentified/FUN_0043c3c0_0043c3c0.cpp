#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C3C0..0x0043C403: FUN_0043c3c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c3c0_0043c3c0() {
    __asm {
    L_0043c3c0:
        sub esp,10h
    L_0043c3c3:
        mov eax,dword ptr [ecx+20h]
    L_0043c3c6:
        push ebx
    L_0043c3c7:
        mov ebx,dword ptr [ecx+18h]
    L_0043c3ca:
        shl ebx,18h
    L_0043c3cd:
        push edi
    L_0043c3ce:
        or ebx,eax
    L_0043c3d0:
        lea edi,[esp+8]
    L_0043c3d4:
        mov dword ptr [esp+8],0
    L_0043c3dc:
        mov dword ptr [esp+0Ch],0
    L_0043c3e4:
        mov dword ptr [esp+10h],44200000h
    L_0043c3ec:
        mov dword ptr [esp+14h],43F00000h
    L_0043c3f4:
        call asm_FUN_0043bda0_0043bda0
    L_0043c3f9:
        pop edi
    L_0043c3fa:
        mov eax,1
    L_0043c3ff:
        pop ebx
    L_0043c400:
        add esp,10h
    L_0043c403:
        ret
    }
}
