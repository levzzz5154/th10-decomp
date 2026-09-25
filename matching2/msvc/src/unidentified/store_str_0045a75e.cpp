#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A75E..0x0045A77D: __store_str
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_store_str_0045a75e() {
    __asm {
    L_0045a75e:
        cmp dword ptr [eax],0
    L_0045a761:
        push esi
    L_0045a762:
        mov esi,edx
    L_0045a764:
        je short L_0045a77c
    L_0045a766:
        push edi
    L_0045a767:
        mov dl,byte ptr [esi]
    L_0045a769:
        test dl,dl
    L_0045a76b:
        je short L_0045a77b
    L_0045a76d:
        mov edi,dword ptr [ecx]
    L_0045a76f:
        mov byte ptr [edi],dl
    L_0045a771:
        inc dword ptr [ecx]
    L_0045a773:
        inc esi
    L_0045a774:
        dec dword ptr [eax]
    L_0045a776:
        cmp dword ptr [eax],0
    L_0045a779:
        jne short L_0045a767
    L_0045a77b:
        pop edi
    L_0045a77c:
        pop esi
    L_0045a77d:
        ret
    }
}
