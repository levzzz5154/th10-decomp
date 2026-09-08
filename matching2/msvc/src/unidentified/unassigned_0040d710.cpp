#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040D710..0x0040D72B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040d710() {
    __asm {
    L_0040d710:
        mov eax,esi
    L_0040d712:
        call asm_FUN_0040d530_0040d530
    L_0040d717:
        test byte ptr [esp+4],1
    L_0040d71c:
        je short L_0040d727
    L_0040d71e:
        push esi
    L_0040d71f:
        call asm_free_004524a1
    L_0040d724:
        add esp,4
    L_0040d727:
        mov eax,esi
    L_0040d729:
        ret 4
    }
}
