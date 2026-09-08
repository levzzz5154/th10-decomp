#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040CE70..0x0040CE75: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ce70() {
    __asm {
    L_0040ce70:
        add eax,9A48h
    L_0040ce75:
        ret
    }
}
