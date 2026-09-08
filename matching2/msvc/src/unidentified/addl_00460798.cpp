#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460798..0x004607B8: ___addl
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_addl_00460798() {
    __asm {
    L_00460798:
        mov edx,dword ptr [esp+4]
    L_0046079c:
        push esi
    L_0046079d:
        mov esi,dword ptr [esp+0Ch]
    L_004607a1:
        lea ecx,[edx+esi]
    L_004607a4:
        xor eax,eax
    L_004607a6:
        cmp ecx,edx
    L_004607a8:
        jb short L_004607ae
    L_004607aa:
        cmp ecx,esi
    L_004607ac:
        jae short L_004607b1
    L_004607ae:
        xor eax,eax
    L_004607b0:
        inc eax
    L_004607b1:
        mov edx,dword ptr [esp+10h]
    L_004607b5:
        mov dword ptr [edx],ecx
    L_004607b7:
        pop esi
    L_004607b8:
        ret
    }
}
