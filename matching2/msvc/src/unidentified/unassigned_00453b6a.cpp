#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453B6A..0x00453B6B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00453b6a() {
    __asm {
    L_00453b6a:
        pop ecx
    L_00453b6b:
        ret
    }
}
