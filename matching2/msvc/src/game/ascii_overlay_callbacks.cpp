#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C2C0..0x0043C303: FUN_0043c2c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c2c0_0043c2c0() {
    __asm {
    L_0043c2c0:
        sub esp,10h
    L_0043c2c3:
        mov eax,dword ptr [ecx+20h]
    L_0043c2c6:
        push ebx
    L_0043c2c7:
        mov ebx,dword ptr [ecx+18h]
    L_0043c2ca:
        shl ebx,18h
    L_0043c2cd:
        push edi
    L_0043c2ce:
        or ebx,eax
    L_0043c2d0:
        lea edi,[esp+8]
    L_0043c2d4:
        mov dword ptr [esp+8],42000000h
    L_0043c2dc:
        mov dword ptr [esp+0Ch],41800000h
    L_0043c2e4:
        mov dword ptr [esp+10h],43D00000h
    L_0043c2ec:
        mov dword ptr [esp+14h],43E80000h
    L_0043c2f4:
        call asm_FUN_0043bda0_0043bda0
    L_0043c2f9:
        pop edi
    L_0043c2fa:
        mov eax,1
    L_0043c2ff:
        pop ebx
    L_0043c300:
        add esp,10h
    L_0043c303:
        ret
    }
}


