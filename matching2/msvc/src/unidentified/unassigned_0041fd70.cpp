#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FD70..0x0041FD81: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0041fd70() {
    __asm {
    L_0041fd70:
        test esi,esi
    L_0041fd72:
        je short L_0041fd81
    L_0041fd74:
        push esi
    L_0041fd75:
        call asm_FUN_0041fb50_0041fb50
    L_0041fd7a:
        push esi
    L_0041fd7b:
        call asm_free_004524a1
    L_0041fd80:
        pop ecx
    L_0041fd81:
        ret
    }
}
