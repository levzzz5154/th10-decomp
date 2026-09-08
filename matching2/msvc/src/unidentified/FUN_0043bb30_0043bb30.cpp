#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BB30..0x0043BB91: FUN_0043bb30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043bb30_0043bb30() {
    __asm {
    L_0043bb30:
        mov eax,dword ptr [esp+4]
    L_0043bb34:
        mov eax,dword ptr [eax+18h]
    L_0043bb37:
        sub esp,18h
    L_0043bb3a:
        test al,3
    L_0043bb3c:
        je short L_0043bb87
    L_0043bb3e:
        lea edx,[esp]
    L_0043bb41:
        push edx
    L_0043bb42:
        mov dword ptr [esp+0Ch],eax
    L_0043bb46:
        mov eax,dword ptr [data_00491c3c]
    L_0043bb4b:
        push 4
    L_0043bb4d:
        mov dword ptr [esp+8],18h
    L_0043bb55:
        mov dword ptr [esp+0Ch],10h
    L_0043bb5d:
        mov dword ptr [esp+14h],2
    L_0043bb65:
        mov dword ptr [esp+18h],0FFFFFC18h
    L_0043bb6d:
        mov dword ptr [esp+1Ch],3E8h
    L_0043bb75:
        mov ecx,dword ptr [eax]
    L_0043bb77:
        push eax
    L_0043bb78:
        call dword ptr [ecx+18h]
    L_0043bb7b:
        test eax,eax
    L_0043bb7d:
        jge short L_0043bb87
    L_0043bb7f:
        xor eax,eax
    L_0043bb81:
        add esp,18h
    L_0043bb84:
        ret 8
    L_0043bb87:
        mov eax,1
    L_0043bb8c:
        add esp,18h
    L_0043bb8f:
        ret 8
    }
}
