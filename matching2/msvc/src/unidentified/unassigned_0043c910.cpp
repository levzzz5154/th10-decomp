#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C910..0x0043C921: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043c910() {
    __asm {
    L_0043c910:
        test esi,esi
    L_0043c912:
        je short L_0043c921
    L_0043c914:
        push esi
    L_0043c915:
        call asm_Recovery_ReleaseRawPair_0043cb00
    L_0043c91a:
        push esi
    L_0043c91b:
        call asm_free_004524a1
    L_0043c920:
        pop ecx
    L_0043c921:
        ret
    }
}
