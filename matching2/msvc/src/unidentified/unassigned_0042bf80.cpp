#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BF80..0x0042BF9A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042bf80() {
    __asm {
    L_0042bf80:
        push esi
    L_0042bf81:
        call asm_FUN_0042bc30_0042bc30
    L_0042bf86:
        test byte ptr [esp+4],1
    L_0042bf8b:
        je short L_0042bf96
    L_0042bf8d:
        push esi
    L_0042bf8e:
        call asm_free_004524a1
    L_0042bf93:
        add esp,4
    L_0042bf96:
        mov eax,esi
    L_0042bf98:
        ret 4
    }
}
