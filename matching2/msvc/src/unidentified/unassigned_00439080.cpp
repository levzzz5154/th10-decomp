#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00439080..0x0043909B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00439080() {
    __asm {
    L_00439080:
        mov eax,esi
    L_00439082:
        call asm_FUN_0043a910_0043a910
    L_00439087:
        test byte ptr [esp+4],1
    L_0043908c:
        je short L_00439097
    L_0043908e:
        push esi
    L_0043908f:
        call asm_free_004524a1
    L_00439094:
        add esp,4
    L_00439097:
        mov eax,esi
    L_00439099:
        ret 4
    }
}
