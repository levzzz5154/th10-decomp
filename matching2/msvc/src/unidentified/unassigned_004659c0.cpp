#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004659C0..0x004659CB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004659c0() {
    __asm {
    L_004659c0:
        push 465A60h
    L_004659c5:
        call asm_atexit_00452e0a
    L_004659ca:
        pop ecx
    L_004659cb:
        ret
    }
}
