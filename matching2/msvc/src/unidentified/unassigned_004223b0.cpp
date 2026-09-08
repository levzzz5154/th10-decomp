#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004223B0..0x004223CA: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004223b0() {
    __asm {
    L_004223b0:
        push esi
    L_004223b1:
        call asm_FUN_00422220_00422220
    L_004223b6:
        test byte ptr [esp+4],1
    L_004223bb:
        je short L_004223c6
    L_004223bd:
        push esi
    L_004223be:
        call asm_free_004524a1
    L_004223c3:
        add esp,4
    L_004223c6:
        mov eax,esi
    L_004223c8:
        ret 4
    }
}
