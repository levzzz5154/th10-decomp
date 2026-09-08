#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00425070..0x0042508A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00425070() {
    __asm {
    L_00425070:
        push esi
    L_00425071:
        call asm_FUN_00424ed0_00424ed0
    L_00425076:
        test byte ptr [esp+4],1
    L_0042507b:
        je short L_00425086
    L_0042507d:
        push esi
    L_0042507e:
        call asm_free_004524a1
    L_00425083:
        add esp,4
    L_00425086:
        mov eax,esi
    L_00425088:
        ret 4
    }
}
