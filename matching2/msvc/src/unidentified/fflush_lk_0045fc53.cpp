#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FC53..0x0045FC80: __fflush_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_fflush_lk_0045fc53() {
    __asm {
    L_0045fc53:
        push esi
    L_0045fc54:
        mov esi,dword ptr [esp+8]
    L_0045fc58:
        push esi
    L_0045fc59:
        call asm_flush_0045fbf6
    L_0045fc5e:
        test eax,eax
    L_0045fc60:
        pop ecx
    L_0045fc61:
        je short L_0045fc68
    L_0045fc63:
        or eax,0FFFFFFFFh
    L_0045fc66:
        pop esi
    L_0045fc67:
        ret
    L_0045fc68:
        test byte ptr [esi+0Dh],40h
    L_0045fc6c:
        je short L_0045fc7d
    L_0045fc6e:
        push dword ptr [esi+10h]
    L_0045fc71:
        call asm_commit_004614a9
    L_0045fc76:
        pop ecx
    L_0045fc77:
        neg eax
    L_0045fc79:
        sbb eax,eax
    L_0045fc7b:
        pop esi
    L_0045fc7c:
        ret
    L_0045fc7d:
        xor eax,eax
    L_0045fc7f:
        pop esi
    L_0045fc80:
        ret
    }
}
