#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405710..0x0040572A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00405710() {
    __asm {
    L_00405710:
        push esi
    L_00405711:
        call asm_Recovery_ReleaseRawPairAndReset_00405620
    L_00405716:
        test byte ptr [esp+4],1
    L_0040571b:
        je short L_00405726
    L_0040571d:
        push esi
    L_0040571e:
        call asm_free_004524a1
    L_00405723:
        add esp,4
    L_00405726:
        mov eax,esi
    L_00405728:
        ret 4
    }
}
