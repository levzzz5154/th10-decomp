#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00463BC4..0x00463BE1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00463bc4() {
    __asm {
    L_00463bc4:
        fxch
    L_00463bc6:
        cmp dword ptr [data_00477388],1
    L_00463bcd:
        je short L_00463bd3
    L_00463bcf:
        fprem
    L_00463bd1:
        jmp short L_00463bd8
    L_00463bd3:
        call asm_FUN_00464b1c_00464b1c
    L_00463bd8:
        wait
        fnstsw ax
    L_00463bdb:
        wait
    L_00463bdc:
        sahf
    L_00463bdd:
        jp short L_00463bc6
    L_00463bdf:
        fstp st(1)
    L_00463be1:
        ret
    }
}
