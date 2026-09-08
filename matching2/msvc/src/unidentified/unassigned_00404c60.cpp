#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404C60..0x00404C82: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00404c60() {
    __asm {
    L_00404c60:
        push esi
    L_00404c61:
        push edi
    L_00404c62:
        mov ecx,7
    L_00404c67:
        mov esi,eax
    L_00404c69:
        mov edi,edx
    L_00404c6b:
        rep movsd
    L_00404c6d:
        pop edi
    L_00404c6e:
        pop esi
    L_00404c6f:
        ret
    L_00404c70:
        push esi
    L_00404c71:
        push edi
    L_00404c72:
        mov edi,eax
    L_00404c74:
        add edi,1Ch
    L_00404c77:
        mov ecx,7
    L_00404c7c:
        mov esi,edx
    L_00404c7e:
        rep movsd
    L_00404c80:
        pop edi
    L_00404c81:
        pop esi
    L_00404c82:
        ret
    }
}
