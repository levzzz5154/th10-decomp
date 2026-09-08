#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004051E0..0x004051E9: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004051e0() {
    __asm {
    L_004051e0:
        push eax
    L_004051e1:
        call asm_malloc_00452706
    L_004051e6:
        add esp,4
    L_004051e9:
        ret
    }
}
