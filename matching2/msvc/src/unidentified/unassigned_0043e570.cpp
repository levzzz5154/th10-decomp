#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E570..0x0043E570: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043e570() {
    __asm {
    L_0043e570:
        ret
    }
}
