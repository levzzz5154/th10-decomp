#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004659D0..0x004659DB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004659d0() {
    __asm {
    L_004659d0:
        push 465A70h
    L_004659d5:
        call asm_atexit_00452e0a
    L_004659da:
        pop ecx
    L_004659db:
        ret
    }
}
