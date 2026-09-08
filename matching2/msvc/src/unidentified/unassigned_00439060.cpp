#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00439060..0x0043907A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00439060() {
    __asm {
    L_00439060:
        push esi
    L_00439061:
        call asm_FUN_00446220_00446220
    L_00439066:
        test byte ptr [esp+4],1
    L_0043906b:
        je short L_00439076
    L_0043906d:
        push esi
    L_0043906e:
        call asm_free_004524a1
    L_00439073:
        add esp,4
    L_00439076:
        mov eax,esi
    L_00439078:
        ret 4
    }
}
