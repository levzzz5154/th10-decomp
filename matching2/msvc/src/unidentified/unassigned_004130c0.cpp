#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004130C0..0x004130C3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004130c0() {
    __asm {
    L_004130c0:
        add eax,0Ch
    L_004130c3:
        ret
    }
}
