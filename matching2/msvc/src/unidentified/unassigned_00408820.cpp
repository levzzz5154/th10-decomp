#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408820..0x00408825: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00408820() {
    __asm {
    L_00408820:
        add eax,1068h
    L_00408825:
        ret
    }
}
